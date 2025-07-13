# 🎤 Mute Status Overlay - TeamSpeak 3 Plugin

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![TeamSpeak 3](https://img.shields.io/badge/TeamSpeak-3.0+-blue.svg)](https://teamspeak.com)
[![Windows](https://img.shields.io/badge/Windows-10%2B-green.svg)](https://www.microsoft.com/windows)

Ein TeamSpeak 3 Plugin, das ein verschiebbares "Always on Top" Fenster anzeigt, welches den Mute-Status deines Mikrofons und Kopfhörers überwacht. **Ab Version 1.1.0 zeigt das Overlay nur noch Icons – kein Text mehr!**

## ✨ Features

- **Always on Top Fenster** - Bleibt immer im Vordergrund
- **Verschiebbar** - Klicke und ziehe das Fenster an die gewünschte Position
- **Echtzeit-Updates** - Zeigt sofort Änderungen des Mute-Status an
- **EAC-kompatibel** - Keine externen Abhängigkeiten, nur Windows-APIs
- **Einfach zu installieren** - Einfache .ts3_plugin Datei
- **Transparenter Hintergrund** - Nur Icons sind sichtbar (kein Text)
- **Größenanpassung** - Ziehe die untere rechte Ecke zum Resizen
- **PNG-Icons** - Schöne Icons für Mikrofon und Kopfhörer.


## 📥 Installation

### Für Endnutzer

1. Lade die neueste `mute_status_overlay.ts3_plugin` Datei aus den [Releases](https://github.com/harrisxo/mute-status-overlay/releases) herunter.
2. **Doppelklicke** die Datei. TeamSpeak 3 öffnet sich und fragt, ob du das Plugin installieren möchtest.
3. Bestätige die Installation und starte TeamSpeak 3 neu.

### Für Entwickler

- Das Plugin wird mit Visual Studio (Windows) gebaut.
- Öffne die Projektdatei und baue die DLL.
- Erstelle das `.ts3_plugin` Paket mit dem offiziellen TeamSpeak Plugin SDK Tool.
- Weitere Infos: [TeamSpeak Plugin SDK](https://github.com/TeamSpeak-Systems/ts3client-plugin_interface)


## 🎮 Verwendung

1. **Fenster verschieben**: Klicke und ziehe das Overlay-Fenster an die gewünschte Position
2. **Größe anpassen**: Ziehe die untere rechte Ecke zum Resizen
3. **Status anzeigen**: 
   - 🔴 Rotes Icon = Muted
   - 🟢 Grünes Icon = Aktiv
4. **Automatische Updates**: Das Fenster aktualisiert sich automatisch bei Mute-Status-Änderungen

**Hinweis:** Ab Version 1.1 wird **kein Text** mehr angezeigt – nur noch die Icons!


## 🗑️ Deinstallation

### Methode 1: Über TeamSpeak (empfohlen)
1. **TeamSpeak komplett schließen** (auch aus dem System-Tray)
2. **TeamSpeak neu starten**
3. **Extras → Optionen → Addons/Plugins**
4. **Plugin finden und auf "Deinstallieren" klicken**

### Methode 2: Manuell (falls Methode 1 nicht funktioniert)
1. **TeamSpeak komplett schließen** (auch aus dem System-Tray)
2. **Plugin-Ordner öffnen:**
   ```
   %APPDATA%\TeamSpeak 3 Client\plugins\
   ```
3. **Den Ordner `mute_status_overlay` löschen**

### Wichtiger Hinweis
Falls beim Deinstallieren über TeamSpeak die DLL-Datei im Plugin-Ordner bleibt, liegt das daran, dass sie noch von TeamSpeak geladen ist. In diesem Fall:
- **TeamSpeak komplett schließen** und dann erneut deinstallieren
- Oder **Methode 2** verwenden (manuell löschen)


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
- Die installierten Dateien sollten sich unter **\AppData\Roaming\TS3Client\plugins befinden

**Fenster kann nicht verschoben werden:**
- Stelle sicher, dass du auf das Fenster klickst (nicht auf andere Fenster)
- Das Fenster sollte einen Mauszeiger anzeigen, wenn du darüber fährst
- Am besten direkt auf eines der Icons klicken und halten

**Status wird nicht aktualisiert:**
- Überprüfe deine TS3-Audio-Einstellungen
- Stelle sicher, dass du die richtigen Audio-Geräte ausgewählt hast

**Icons werden nicht angezeigt:**
- Stelle sicher, dass die PNG-Dateien im Plugin-Ordner vorhanden sind (**\AppData\Roaming\TS3Client\plugins)
- Überprüfe die Berechtigungen im TS3-Plugins-Ordner


## 🛠️ Entwicklung

Das Plugin ist in C++ geschrieben und verwendet die offizielle TeamSpeak 3 Client SDK.

### Dateien:
- `mute_status_overlay.cpp` - Hauptimplementierung
- `package.ini` - Plugin-Konfiguration
- `Makefile` - Build-System
- `resources/` - PNG-Icons für Mikrofon und Kopfhörer
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

Ich freue mich über Feedback! Bitte lies die [Contributing Guidelines](CONTRIBUTING.md) für Details.

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