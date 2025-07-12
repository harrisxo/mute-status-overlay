# 🎤 Mute Status Overlay - TeamSpeak 3 Plugin

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![TeamSpeak 3](https://img.shields.io/badge/TeamSpeak-3.0+-blue.svg)](https://teamspeak.com)
[![Windows](https://img.shields.io/badge/Windows-10%2B-green.svg)](https://www.microsoft.com/windows)

Ein TeamSpeak 3 Plugin, das ein verschiebbares "Always on Top" Fenster anzeigt, welches den Mute-Status deines Mikrofons und Kopfhörers überwacht. Perfekt für Streamer, Content Creator und GTA RP Spieler!

## ✨ Features

- 🎯 **Always on Top Fenster** - Bleibt immer im Vordergrund
- 🖱️ **Verschiebbar** - Klicke und ziehe das Fenster an die gewünschte Position
- ⚡ **Echtzeit-Updates** - Zeigt sofort Änderungen des Mute-Status an
- 🛡️ **EAC-kompatibel** - Keine externen Abhängigkeiten, nur Windows-APIs
- 📦 **Einfach zu installieren** - Einfache .ts3_plugin Datei
- 🎨 **Transparenter Hintergrund** - Nur Icons und Text sind sichtbar
- 📏 **Größenanpassung** - Ziehe die untere rechte Ecke zum Resizen
- 🖼️ **PNG-Icons** - Schöne Icons für Mikrofon und Kopfhörer


## 📥 Installation

### Option 1: Vorkompilierte Version (Empfohlen)

1. Lade die neueste `mute_status_overlay.ts3_plugin` Datei aus den [Releases](https://github.com/harrisxo/mute-status-overlay/releases) herunter
2. Kopiere die Datei in deinen TeamSpeak 3 Plugins-Ordner:
   - Windows: `%APPDATA%\TS3Client\plugins\`
3. Starte TeamSpeak 3 neu
4. Das Plugin wird automatisch geladen und das Overlay-Fenster erscheint

### Option 2: Selbst kompilieren

1. Stelle sicher, dass du einen C++ Compiler installiert hast (z.B. MinGW-w64)
2. Lade die TS3 SDK Header-Dateien herunter
3. Führe folgende Befehle aus:

```bash
make
make install
```


## 🎮 Verwendung

1. **Fenster verschieben**: Klicke und ziehe das Overlay-Fenster an die gewünschte Position
2. **Größe anpassen**: Ziehe die untere rechte Ecke zum Resizen
3. **Status anzeigen**: 
   - 🔴 Rote Icons = Muted
   - 🟢 Grüne Icons = Aktiv
4. **Automatische Updates**: Das Fenster aktualisiert sich automatisch bei Mute-Status-Änderungen


## 🔧 Technische Details

Das Plugin verwendet:
- **CLIENT_INPUT_MUTED** - Überwacht den Mikrofon-Mute-Status
- **CLIENT_OUTPUT_MUTED** - Überwacht den Kopfhörer-Mute-Status
- **Windows API** - Für das Overlay-Fenster (WS_EX_TOPMOST, WS_EX_LAYERED)
- **GDI+** - Für die grafische Darstellung und PNG-Icons
- **UpdateLayeredWindow** - Für echte Transparenz


## 🛡️ EAC-Kompatibilität

Das Plugin ist vollständig EAC-kompatibel, da es:
- Keine externen Bibliotheken verwendet
- Nur Windows-Standard-APIs nutzt
- Keine Netzwerk-Kommunikation außerhalb von TS3 durchführt
- Keine Datei-System-Zugriffe außerhalb des TS3-Plugins-Ordners hat


## 🚨 Troubleshooting

**Fenster erscheint nicht:**
- Stelle sicher, dass das Plugin in TS3 aktiviert ist
- Überprüfe, ob du mit einem TS3-Server verbunden bist
- Starte TS3 neu

**Fenster kann nicht verschoben werden:**
- Stelle sicher, dass du auf das Fenster klickst (nicht auf andere Fenster)
- Das Fenster sollte einen Mauszeiger anzeigen, wenn du darüber fährst

**Status wird nicht aktualisiert:**
- Überprüfe deine TS3-Audio-Einstellungen
- Stelle sicher, dass du die richtigen Audio-Geräte ausgewählt hast

**Icons werden nicht angezeigt:**
- Stelle sicher, dass die PNG-Dateien im Plugin-Ordner vorhanden sind
- Überprüfe die Berechtigungen im TS3-Plugins-Ordner


## 🛠️ Entwicklung

Das Plugin ist in C++ geschrieben und verwendet die offizielle TeamSpeak 3 Client SDK.

### Dateien:
- `mute_status_overlay.cpp` - Hauptimplementierung
- `package.ini` - Plugin-Konfiguration
- `Makefile` - Build-System
- `resources/` - PNG-Icons für Mikrofon und Kopfhörer

### Kompilierung:
```bash
make clean
make
```

### Projektstruktur:
```
mute-status-overlay/
├── mute_status_overlay.cpp    # Hauptquellcode
├── package.ini               # Plugin-Konfiguration
├── Makefile                  # Build-System
├── resources/                # PNG-Icons
│   ├── mic_active.png
│   ├── mic_muted.png
│   ├── headset_active.png
│   └── headset_muted.png
├── pluginsdk/                # TS3 SDK Header
└── docs/                     # Dokumentation
```


## 📄 Lizenz

Dieses Projekt steht unter der MIT-Lizenz - siehe die [LICENSE](LICENSE) Datei für Details.

## 🤝 Beitragen

Wir freuen uns über Beiträge! Bitte lies unsere [Contributing Guidelines](CONTRIBUTING.md) für Details.

## 📞 Support

Bei Problemen oder Fragen:
1. Überprüfe die [Troubleshooting](#-troubleshooting) Sektion
2. Stelle sicher, dass du die neueste Version verwendest
3. Überprüfe deine TeamSpeak 3 Version (Plugin ist für TS3 3.0+ entwickelt)
4. Erstelle ein [GitHub Issue](https://github.com/harrisxo/mute-status-overlay/issues)

## 🔗 Links

- [TeamSpeak 3 Client SDK](https://github.com/TeamSpeak-Systems/ts3client-plugin_interface)
- [TeamSpeak 3 Download](https://teamspeak.com/de/downloads/)
- [Changelog](CHANGELOG.md)


---

**Hinweis:** Dieses Plugin ist für den persönlichen Gebrauch auf GTA RP Servern gedacht. Es verwendet nur öffentliche APIs und verletzt keine Nutzungsbedingungen. 