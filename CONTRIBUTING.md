# Contributing to Mute Status Overlay

Vielen Dank für dein Interesse am Mute Status Overlay Plugin! Hier findest du Informationen, wie du zum Projekt beitragen kannst.

## Wie kann ich beitragen?

### 🐛 Bug Reports
- Verwende die GitHub Issues
- Beschreibe das Problem so detailliert wie möglich
- Füge Schritte zum Reproduzieren hinzu
- Gib deine TeamSpeak 3 Version an

### 💡 Feature Requests
- Erstelle ein GitHub Issue mit dem Label "enhancement"
- Beschreibe das gewünschte Feature
- Erkläre, warum es nützlich wäre

### 🔧 Code Contributions
1. Forke das Repository
2. Erstelle einen Feature-Branch: `git checkout -b feature/amazing-feature`
3. Mache deine Änderungen
4. Teste gründlich
5. Committe deine Änderungen: `git commit -m 'Add amazing feature'`
6. Push zum Branch: `git push origin feature/amazing-feature`
7. Erstelle einen Pull Request

## Entwicklungsumgebung

### Voraussetzungen
- Windows 10/11
- C++ Compiler (MinGW-w64 empfohlen)
- TeamSpeak 3 Client SDK
- Git

### Setup
1. Klone das Repository
2. Stelle sicher, dass die TS3 SDK Header-Dateien im `pluginsdk/` Ordner sind
3. Führe `make` aus, um zu kompilieren
4. Teste das Plugin in TeamSpeak 3

### Coding Standards
- Verwende aussagekräftige Variablen- und Funktionsnamen
- Kommentiere komplexe Logik
- Halte die EAC-Kompatibilität bei
- Teste auf verschiedenen Windows-Versionen

## Release Process

1. Aktualisiere die Version in `package.ini`
2. Erstelle Release Notes
3. Kompiliere das Plugin
4. Erstelle ein GitHub Release mit der `.ts3_plugin` Datei

## Fragen?

Falls du Fragen hast, erstelle einfach ein GitHub Issue oder kontaktiere uns über die verfügbaren Kanäle. 