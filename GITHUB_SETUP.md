# 🚀 GitHub Setup Guide

Diese Anleitung hilft dir dabei, dein Mute Status Overlay Plugin auf GitHub zu veröffentlichen.

## 📋 Vorbereitung

### 1. GitHub Account erstellen
Falls du noch keinen GitHub Account hast:
1. Gehe zu [github.com](https://github.com)
2. Klicke auf "Sign up"
3. Folge den Anweisungen

### 2. Git installieren
Falls Git noch nicht installiert ist:
1. Lade Git von [git-scm.com](https://git-scm.com) herunter
2. Installiere es mit den Standard-Einstellungen

## 🔧 Repository erstellen

### 1. Neues Repository auf GitHub
1. Gehe zu [github.com](https://github.com)
2. Klicke auf das "+" Symbol oben rechts
3. Wähle "New repository"
4. Fülle die Felder aus:
   - **Repository name:** `mute-status-overlay`
   - **Description:** `TeamSpeak 3 Plugin für Mute-Status Overlay`
   - **Visibility:** Public (empfohlen)
   - **Initialize with:** Keine Optionen aktivieren
5. Klicke "Create repository"

### 2. Lokales Repository initialisieren
Öffne PowerShell/Command Prompt im Projektordner und führe aus:

```bash
# Git Repository initialisieren
git init

# Alle Dateien hinzufügen
git add .

# Ersten Commit erstellen
git commit -m "Initial commit: Mute Status Overlay Plugin v1.0.0"

# Remote Repository hinzufügen (ersetze USERNAME mit deinem GitHub Username)
git remote add origin https://github.com/USERNAME/mute-status-overlay.git

# Code hochladen
git branch -M main
git push -u origin main
```

## ⚙️ GitHub Features aktivieren

### 1. GitHub Pages aktivieren
1. Gehe zu deinem Repository auf GitHub
2. Klicke auf "Settings" (Tab)
3. Scrolle zu "Pages" (linke Seitenleiste)
4. Unter "Source" wähle "Deploy from a branch"
5. Wähle "gh-pages" Branch und "/(root)" Ordner
6. Klicke "Save"

### 2. Issues aktivieren
1. Gehe zu "Settings" → "Features"
2. Stelle sicher, dass "Issues" aktiviert ist
3. Optional: Aktiviere "Wikis" für zusätzliche Dokumentation

### 3. Branch Protection (optional)
1. Gehe zu "Settings" → "Branches"
2. Klicke "Add rule"
3. Gib "main" als Branch name pattern ein
4. Aktiviere "Require pull request reviews before merging"
5. Klicke "Create"

## 📦 Erste Release erstellen

### 1. Release vorbereiten
1. Stelle sicher, dass alle Änderungen committed sind
2. Aktualisiere die Version in `package.ini` falls nötig
3. Aktualisiere `CHANGELOG.md`

### 2. Release erstellen
1. Gehe zu deinem Repository auf GitHub
2. Klicke auf "Releases" (rechts)
3. Klicke "Create a new release"
4. Fülle die Felder aus:
   - **Tag version:** `v1.0.0`
   - **Release title:** `v1.0.0 - Initial Release`
   - **Description:** Kopiere den Inhalt aus dem Release Template
5. Klicke "Publish release"

## 🔄 Automatische Builds

Die GitHub Actions werden automatisch aktiviert, wenn du Code pushst. Du kannst sie hier überwachen:
1. Gehe zu deinem Repository
2. Klicke auf "Actions" Tab
3. Du siehst die Build-Status

## 📝 Repository anpassen

### 1. README anpassen
Ersetze in der `README.md` alle Vorkommen von `yourusername` mit deinem tatsächlichen GitHub Username.

### 2. Links aktualisieren
Aktualisiere alle Links in der Dokumentation:
- GitHub Issues: `https://github.com/USERNAME/mute-status-overlay/issues`
- Releases: `https://github.com/USERNAME/mute-status-overlay/releases`

## 🎯 Nächste Schritte

### 1. Community aufbauen
- Erstelle ein GitHub Discussion Board
- Teile das Projekt in relevanten Communities
- Erstelle Screenshots/Videos für die README

### 2. Versionierung
- Verwende [Semantic Versioning](https://semver.org/lang/de/)
- Erstelle regelmäßige Releases
- Halte die Changelog aktuell

### 3. Dokumentation
- Erweitere die README mit Screenshots
- Erstelle Video-Tutorials
- Dokumentiere die API (falls relevant)

## 🔗 Nützliche Links

- [GitHub Guides](https://guides.github.com/)
- [GitHub Pages](https://pages.github.com/)
- [GitHub Actions](https://docs.github.com/en/actions)
- [Semantic Versioning](https://semver.org/lang/de/)

## ❓ Hilfe

Falls du Probleme hast:
1. Überprüfe die GitHub Dokumentation
2. Suche nach ähnlichen Problemen auf Stack Overflow
3. Erstelle ein Issue in deinem Repository
4. Kontaktiere die GitHub Support Community 