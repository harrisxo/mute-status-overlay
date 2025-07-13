#include "ts3_functions.h"
#include "plugin_definitions.h"
#include "public_definitions.h"
#include <windows.h>
#include <string>
#include <shlobj.h> // Für AppData-Pfad
#include <gdiplus.h>
#include <shlwapi.h>
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "shlwapi.lib")
using namespace Gdiplus;

// Plugin info
static char* plugin_name = (char*)"Mute Status Overlay";
static char* plugin_version = (char*)"1.3";
static char* plugin_author = (char*)"Copyright (c) 2025 Aki Green // h710";
static char* plugin_description = (char*)"Zeigt ein Overlay für den Mute-Status von Mikrofon und/oder Kopfhörern.";

static struct TS3Functions ts3Functions;
static HWND overlayWindow = NULL;
static bool isDragging = false;
static POINT dragOffset;
static bool lastMicMuted = false;
static bool lastOutputMuted = false;
static uint64 currentScHandlerID = 0;

// Overlay-Einstellungen
// Setze overlayAlpha fest
static int overlayAlpha = 180; // Immer halbtransparent
static int overlayWidth = 120; // Breiter für zwei Icons
static int overlayHeight = 64; // Höhe für ein Icon

// --- Resize-Handle-Konstanten ---
#define RESIZE_HANDLE_SIZE 18
static bool isResizing = false;
static POINT resizeStartPt;
static int resizeStartW = 0, resizeStartH = 0;

#define INI_SECTION "Overlay"
#define INI_KEY_ALPHA "Alpha"
#define INI_KEY_WIDTH "Width"
#define INI_KEY_HEIGHT "Height"
#define INI_FILENAME "mute_status_overlay.ini"

static Gdiplus::Image* micActiveImg = nullptr;
static Gdiplus::Image* micMutedImg = nullptr;
static Gdiplus::Image* headsetActiveImg = nullptr;
static Gdiplus::Image* headsetMutedImg = nullptr;
static ULONG_PTR gdiplusToken;

// Hilfsfunktion: Plugin-Ordner ermitteln
std::wstring GetPluginDir() {
    wchar_t path[MAX_PATH];
    HMODULE hMod = NULL;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)GetPluginDir, &hMod);
    GetModuleFileNameW(hMod, path, MAX_PATH);
    PathRemoveFileSpecW(path);
    return std::wstring(path);
}

std::string GetSettingsPath() {
    char appdata[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appdata);
    std::string path = std::string(appdata) + "\\TS3Client\\plugins\\" + INI_FILENAME;
    return path;
}

void LoadSettings() {
    std::string path = GetSettingsPath();
    overlayAlpha = GetPrivateProfileIntA(INI_SECTION, INI_KEY_ALPHA, 200, path.c_str());
    overlayWidth = GetPrivateProfileIntA(INI_SECTION, INI_KEY_WIDTH, 120, path.c_str());
    overlayHeight = GetPrivateProfileIntA(INI_SECTION, INI_KEY_HEIGHT, 64, path.c_str());
    if (overlayAlpha < 50) overlayAlpha = 50;
    if (overlayAlpha > 255) overlayAlpha = 255;
    if (overlayWidth < 100) overlayWidth = 100;
    if (overlayWidth > 600) overlayWidth = 600;
    if (overlayHeight < 40) overlayHeight = 40;
    if (overlayHeight > 300) overlayHeight = 300;
}

void SaveSettings() {
    std::string path = GetSettingsPath();
    char buf[16];
    WritePrivateProfileStringA(INI_SECTION, INI_KEY_ALPHA, itoa(overlayAlpha, buf, 10), path.c_str());
    WritePrivateProfileStringA(INI_SECTION, INI_KEY_WIDTH, itoa(overlayWidth, buf, 10), path.c_str());
    WritePrivateProfileStringA(INI_SECTION, INI_KEY_HEIGHT, itoa(overlayHeight, buf, 10), path.c_str());
}

void UpdateMuteStatus();
void ApplyOverlaySettings();

// --- Neue/angepasste Includes ---
#include <windows.h>
#include <gdiplus.h>
#include <shlwapi.h>
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "shlwapi.lib")
using namespace Gdiplus;


// --- UpdateLayeredWindow-Buffer zeichnen ---
void RedrawOverlayWindow() {
    if (!overlayWindow) return;
    int w = overlayWidth, h = overlayHeight; // Dynamische Größe
    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h; // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    void* pvBits = nullptr;
    HDC hdcScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    HBITMAP hBmp = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0);
    HBITMAP hOldBmp = (HBITMAP)SelectObject(hdcMem, hBmp);
    // GDI+ auf den Backbuffer
    Gdiplus::Graphics graphics(hdcMem);
    graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
    // --- Alles transparent machen ---
    graphics.Clear(Gdiplus::Color(0,0,0,0));
    
    // --- Beide Icons nebeneinander zeichnen ---
    int iconSize = 48;
    int spacing = 8; // Abstand zwischen den Icons
    int totalWidth = iconSize * 2 + spacing;
    int startX = (w - totalWidth) / 2;
    int iconY = (h - iconSize) / 2;
    
    // --- Mikrofon-Icon (links) ---
    if (micActiveImg && micMutedImg) {
        Gdiplus::Image* micImg = lastMicMuted ? micMutedImg : micActiveImg;
        graphics.DrawImage(micImg, startX, iconY, iconSize, iconSize);
    }
    
    // --- Headset-Icon (rechts) ---
    if (headsetActiveImg && headsetMutedImg) {
        Gdiplus::Image* headsetImg = lastOutputMuted ? headsetMutedImg : headsetActiveImg;
        graphics.DrawImage(headsetImg, startX + iconSize + spacing, iconY, iconSize, iconSize);
    }
    
    // --- Buffer als Fensterinhalt setzen ---
    POINT ptSrc = {0,0};
    SIZE sizeWnd = {w,h};
    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    UpdateLayeredWindow(overlayWindow, hdcScreen, NULL, &sizeWnd, hdcMem, &ptSrc, 0, &blend, ULW_ALPHA);
    // Cleanup
    SelectObject(hdcMem, hOldBmp);
    DeleteObject(hBmp);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);
}

// --- OverlayWndProc: WM_PAINT ersetzt durch RedrawOverlayWindow-Aufruf ---
LRESULT CALLBACK OverlayWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_LBUTTONDOWN: {
            POINT pt = { LOWORD(lParam), HIWORD(lParam) };
            isDragging = true;
            dragOffset.x = pt.x;
            dragOffset.y = pt.y;
            SetCapture(hwnd);
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (isDragging) {
                POINT scrPt; GetCursorPos(&scrPt);
                SetWindowPos(hwnd, NULL, scrPt.x - dragOffset.x, scrPt.y - dragOffset.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                return 0;
            }
            return 0;
        }
        case WM_LBUTTONUP:
            if (isDragging) {
                isDragging = false;
                ReleaseCapture();
                return 0;
            }
            return 0;
        case WM_PAINT:
            RedrawOverlayWindow();
            ValidateRect(hwnd, NULL);
            return 0;
        case WM_TIMER:
            if (wParam == 1) UpdateMuteStatus();
            return 0;
        case WM_DESTROY:
            KillTimer(hwnd, 1);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void ApplyOverlaySettings() {
    if (overlayWindow) {
        SetWindowPos(overlayWindow, NULL, 0, 0, overlayWidth, overlayHeight, SWP_NOMOVE | SWP_NOZORDER);
        InvalidateRect(overlayWindow, NULL, TRUE);
    }
}

void CreateOverlayWindow() {
    if (overlayWindow) return;
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = OverlayWndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "MuteStatusOverlay";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassEx(&wc);
    overlayWindow = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
        "MuteStatusOverlay",
        "Mute Status",
        WS_POPUP | WS_VISIBLE,
        100, 100, overlayWidth, overlayHeight,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );
    if (overlayWindow) {
        ApplyOverlaySettings();
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        SetWindowPos(overlayWindow, NULL, screenWidth - overlayWidth - 20, 20, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        SetTimer(overlayWindow, 1, 200, NULL); // 200ms polling
        InvalidateRect(overlayWindow, NULL, TRUE);
    }
}

void DestroyOverlayWindow() {
    if (overlayWindow) {
        KillTimer(overlayWindow, 1);
        DestroyWindow(overlayWindow);
        overlayWindow = NULL;
    }
    UnregisterClass("MuteStatusOverlay", GetModuleHandle(NULL));
}

void UpdateMuteStatus() {
    if (!overlayWindow || currentScHandlerID == 0) return;
    int inputMuted = 0, outputMuted = 0, inputHardware = 0, inputDeactivated = 0;
    ts3Functions.getClientSelfVariableAsInt(currentScHandlerID, CLIENT_INPUT_MUTED, &inputMuted);
    ts3Functions.getClientSelfVariableAsInt(currentScHandlerID, CLIENT_OUTPUT_MUTED, &outputMuted);
    ts3Functions.getClientSelfVariableAsInt(currentScHandlerID, CLIENT_INPUT_HARDWARE, &inputHardware);
    ts3Functions.getClientSelfVariableAsInt(currentScHandlerID, CLIENT_INPUT_DEACTIVATED, &inputDeactivated);
    bool micMuted = (inputMuted == MUTEINPUT_MUTED) || (inputHardware == HARDWAREINPUT_DISABLED) || (inputDeactivated == INPUT_DEACTIVATED);
    bool outputIsMuted = (outputMuted == MUTEOUTPUT_MUTED);
    if (micMuted != lastMicMuted || outputIsMuted != lastOutputMuted) {
        lastMicMuted = micMuted;
        lastOutputMuted = outputIsMuted;
        InvalidateRect(overlayWindow, NULL, TRUE);
    }
}

// WinAPI Einstellungsdialog
INT_PTR CALLBACK SettingsDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hSlider = NULL;
    static HWND hEditW = NULL, hEditH = NULL;
    switch (msg) {
        case WM_INITDIALOG: {
            hSlider = GetDlgItem(hwndDlg, 1001);
            hEditW = GetDlgItem(hwndDlg, 1002);
            hEditH = GetDlgItem(hwndDlg, 1003);
            SendMessageA(hSlider, TBM_SETRANGE, TRUE, MAKELPARAM(50, 255));
            SendMessageA(hSlider, TBM_SETPOS, TRUE, overlayAlpha);
            SetDlgItemInt(hwndDlg, 1002, overlayWidth, FALSE);
            SetDlgItemInt(hwndDlg, 1003, overlayHeight, FALSE);
            return TRUE;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == IDOK) {
                overlayAlpha = (int)SendMessageA(hSlider, TBM_GETPOS, 0, 0);
                overlayWidth = GetDlgItemInt(hwndDlg, 1002, NULL, FALSE);
                overlayHeight = GetDlgItemInt(hwndDlg, 1003, NULL, FALSE);
                SaveSettings();
                ApplyOverlaySettings();
                EndDialog(hwndDlg, IDOK);
                return TRUE;
            } else if (LOWORD(wParam) == IDCANCEL) {
                EndDialog(hwndDlg, IDCANCEL);
                return TRUE;
            }
            break;
        }
    }
    return FALSE;
}

void ShowSettingsDialog() {
    HINSTANCE hInst = GetModuleHandle(NULL);
    // Dynamisch Dialog erstellen
    // (alternativ: Ressourcen nutzen, aber hier alles im Code)
    // Dialog mit Slider (Transparenz) und zwei Editfeldern (Breite/Höhe)
    // IDs: Slider=1001, EditW=1002, EditH=1003
    // Erstelle ein modales Dialogfenster
    // (Hier: CreateDialogIndirectParam wäre schöner, aber für Demo reicht MessageBox)
    // Wir nutzen ein einfaches Dialog-Template im Speicher
    // Für echte Projekte: Ressourcen nutzen!
    // Hier: MessageBox als Platzhalter
    //MessageBoxA(NULL, "Hier könnten Einstellungen wie Transparenz und Größe angepasst werden!", "Mute Status Overlay Einstellungen", MB_OK);
    // ---
    // Für Demo: Nutze ein echtes Dialogfenster mit WinAPI
    // (Hier: Dialog-Template im Speicher bauen)
    // ---
    // Für Demo: Nutze ein einfaches Dialogfenster
    // (Slider und Editfelder werden im WM_INITDIALOG gesetzt)
    // ---
    // Dialog-Template im Speicher bauen ist aufwendig, daher als Kompromiss:
    // Zeige ein Infofenster, dass die Werte in der INI gespeichert werden
    // und beim nächsten Start übernommen werden.
    // ---
    DialogBoxParamA(hInst, MAKEINTRESOURCEA(1), NULL, SettingsDlgProc, 0);
}

extern "C" {
    const char* ts3plugin_name() { return plugin_name; }
    const char* ts3plugin_version() { return plugin_version; }
    int ts3plugin_apiVersion() { return 26; }
    const char* ts3plugin_author() { return plugin_author; }
    const char* ts3plugin_description() { return plugin_description; }
    void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) { ts3Functions = funcs; }
    int ts3plugin_init() {
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
        std::wstring pluginDir = GetPluginDir();
        micActiveImg = new Gdiplus::Image((pluginDir + L"\\mute_status_overlay\\mic_active.png").c_str());
        if (micActiveImg->GetLastStatus() != Ok) MessageBoxA(NULL, "mic_active.png konnte nicht geladen werden!", "Fehler", MB_OK);
        micMutedImg = new Gdiplus::Image((pluginDir + L"\\mute_status_overlay\\mic_muted.png").c_str());
        if (micMutedImg->GetLastStatus() != Ok) MessageBoxA(NULL, "mic_muted.png konnte nicht geladen werden!", "Fehler", MB_OK);
        headsetActiveImg = new Gdiplus::Image((pluginDir + L"\\mute_status_overlay\\headset_active.png").c_str());
        if (headsetActiveImg->GetLastStatus() != Ok) MessageBoxA(NULL, "headset_active.png konnte nicht geladen werden!", "Fehler", MB_OK);
        headsetMutedImg = new Gdiplus::Image((pluginDir + L"\\mute_status_overlay\\headset_muted.png").c_str());
        if (headsetMutedImg->GetLastStatus() != Ok) MessageBoxA(NULL, "headset_muted.png konnte nicht geladen werden!", "Fehler", MB_OK);
        LoadSettings();
        return 0;
    }
    void ts3plugin_shutdown() {
        DestroyOverlayWindow();
        if (micActiveImg) { delete micActiveImg; micActiveImg = nullptr; }
        if (micMutedImg) { delete micMutedImg; micMutedImg = nullptr; }
        if (headsetActiveImg) { delete headsetActiveImg; headsetActiveImg = nullptr; }
        if (headsetMutedImg) { delete headsetMutedImg; headsetMutedImg = nullptr; }
        Gdiplus::GdiplusShutdown(gdiplusToken);
    }
    void ts3plugin_freeMemory(void* data) { free(data); }
    int ts3plugin_requestAutoload() { return 0; }
    void ts3plugin_onConnectStatusChangeEvent(uint64 scHandlerID, int newStatus, unsigned int /*errorNumber*/) {
        if (newStatus == 4 /*STATUS_CONNECTION_ESTABLISHED*/) {
            currentScHandlerID = scHandlerID;
            CreateOverlayWindow();
        } else if (newStatus == 5 /*STATUS_DISCONNECTED*/) {
            DestroyOverlayWindow();
            currentScHandlerID = 0;
        }
    }
    void ts3plugin_onUpdateClientEvent(uint64, anyID, anyID, const char*, const char*) {
        // Polling übernimmt jetzt das Update
    }
    // Einstellungen-Button aktivieren
    const char* ts3plugin_configureOffer() {
        return "1";
    }
    int ts3plugin_configure(void*, void*) {
        MessageBoxA(NULL, "Test", "Test", MB_OK);
        return 1;
    }
} 