# Einfache Installation - Mute Status Overlay

## Schnellstart (Empfohlen)

### Schritt 1: Plugin herunterladen
Lade die Datei `mute_status_overlay_simple.ts3_plugin` herunter.

### Schritt 2: Plugin installieren
1. Öffne den Windows Explorer
2. Navigiere zu: `%APPDATA%\TS3Client\plugins\`
   - Falls der Ordner nicht existiert, erstelle ihn
3. Kopiere die `mute_status_overlay_simple.ts3_plugin` Datei in diesen Ordner

### Schritt 3: TeamSpeak 3 starten
1. Starte TeamSpeak 3
2. Verbinde dich mit einem Server
3. Das Overlay-Fenster erscheint automatisch in der oberen rechten Ecke

## Verwendung

### Fenster verschieben
- **Klicke und ziehe** das kleine schwarze Fenster an die gewünschte Position
- Das Fenster bleibt immer im Vordergrund

### Status-Anzeige
- 🔴 **Roter Kreis** = Muted (Stumm)
- 🟢 **Grüner Kreis** = Active (Aktiv)

### Automatische Updates
- Das Fenster aktualisiert sich automatisch
- Keine manuellen Aktionen erforderlich

## Troubleshooting

### Fenster erscheint nicht
1. **Plugin aktivieren:**
   - Gehe zu `Extras` → `Plugins`
   - Stelle sicher, dass "Mute Status Overlay (Simple)" aktiviert ist
   - Falls nicht, klicke auf "Aktivieren"

2. **TeamSpeak neu starten:**
   - Schließe TeamSpeak 3 komplett
   - Starte es neu
   - Verbinde dich mit einem Server

3. **Plugin-Ordner prüfen:**
   - Stelle sicher, dass die Datei in `%APPDATA%\TS3Client\plugins\` liegt
   - Der Dateiname muss exakt `mute_status_overlay_simple.ts3_plugin` sein

### Fenster kann nicht verschoben werden
- Stelle sicher, dass du auf das **schwarze Fenster** klickst
- Der Mauszeiger sollte sich ändern, wenn du über das Fenster fährst
- Klicke und halte die linke Maustaste gedrückt, dann ziehe

### Status wird nicht aktualisiert
1. **Audio-Einstellungen prüfen:**
   - Gehe zu `Einstellungen` → `Wiedergabe` und `Aufnahme`
   - Stelle sicher, dass die richtigen Geräte ausgewählt sind

2. **Mute-Tasten testen:**
   - Drücke deine Mute-Tasten
   - Das Overlay sollte sofort reagieren

## EAC-Kompatibilität

✅ **Vollständig EAC-kompatibel**
- Verwendet nur TeamSpeak 3 interne APIs
- Keine externen Bibliotheken
- Keine Netzwerk-Kommunikation außerhalb von TS3
- Keine Datei-System-Zugriffe

## Deinstallation

1. Gehe zu `Extras` → `Plugins`
2. Deaktiviere "Mute Status Overlay (Simple)"
3. Lösche die Datei `mute_status_overlay_simple.ts3_plugin` aus dem Plugins-Ordner
4. Starte TeamSpeak 3 neu

## Support

Bei Problemen:
1. Überprüfe die Troubleshooting-Sektion
2. Stelle sicher, dass du TeamSpeak 3 Version 3.0 oder höher verwendest
3. Teste das Plugin auf einem anderen TS3-Server

---

**Hinweis:** Dieses Plugin ist speziell für GTA RP Server mit EAC entwickelt und verletzt keine Nutzungsbedingungen. 