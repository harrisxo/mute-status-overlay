# Changelog

Alle wichtigen Änderungen an diesem Projekt werden in dieser Datei dokumentiert.

Das Format basiert auf [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
und dieses Projekt folgt [Semantic Versioning](https://semver.org/lang/de/).

## [1.1.0] - 2024-07-12

### Geändert
- Overlay zeigt jetzt **nur noch Icons** (Mikrofon und Kopfhörer, jeweils aktiv/muted)
- Jegliche Textanzeige im Overlay entfernt
- Fenstergröße ist kompakter und passt sich nur an die Icons an

## [1.3.0] - 2025-01-XX

### Geändert
- **Beide Icons (Mikrofon und Kopfhörer) werden wieder nebeneinander angezeigt**
- Fenstergröße angepasst für optimale Darstellung beider Icons
- Dynamische Fenstergröße basierend auf Icon-Anzahl und Abständen
- Verbesserte Icon-Positionierung mit gleichmäßigen Abständen

## [Unreleased]

### Geplant
- Verbesserte Fehlerbehandlung
- Mehrsprachige Unterstützung
- Zusätzliche Anpassungsoptionen

## [1.0.0] - 2024-12-19

### Hinzugefügt
- Initiale Version des Mute Status Overlay Plugins
- Always-on-Top Fenster mit Mikrofon- und Kopfhörer-Status
- Verschiebbares Overlay-Fenster
- Echtzeit-Updates des Mute-Status
- PNG-Icons für Mikrofon und Kopfhörer (aktiv/muted)
- Transparenter Hintergrund mit nur sichtbaren Icons und Text
- Größenanpassung durch Ziehen der unteren rechten Ecke
- EAC-kompatible Implementierung
- Automatische Installation über .ts3_plugin Paket

### Technische Details
- Verwendet Windows API für Overlay-Fenster
- GDI+ für PNG-Icon-Rendering
- Per-Pixel-Transparenz mit UpdateLayeredWindow
- TeamSpeak 3 Client SDK Integration
- Keine externen Abhängigkeiten

## [0.9.0] - Entwicklung

### Hinzugefügt
- Grundlegende Plugin-Struktur
- Mute-Status-Überwachung
- Einfaches Overlay-Fenster

### Geändert
- Mehrere Iterationen der UI-Implementierung
- Verbesserungen der Transparenz-Behandlung
- Optimierung der Icon-Darstellung 