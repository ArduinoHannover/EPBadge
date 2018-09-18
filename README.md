# E-Paper Badge

## Technische Daten
Auflösung: 264x176

## Programmieren
Benötigte Bibliotheken:

- [GxEPD](https://github.com/ZinggJM/GxEPD/)

### Bilder umwandeln

Am einfachsten online per [image2cpp](http://javl.github.io/image2cpp/), unten "Arduino Code" auswählen.
Zuvor am besten das Bild schon monochrom vorbereiten, bei S/W/R Bildern die einzelnen Farben separat speichern (etwa bei schwarzem Hintergrund eine Datei für weiß und eine für rot, einfacher im Positionieren wird es, wenn beide gleich groß sind).
Die Breite muss einem vielfachen von 8 entsprechen, die Höhe ist egal.

### Hochladen

Beim Flashen über einen FTDI-Adapter die Spannung auf 3.3V einstellen und den Badge auf "Off" schalten oder Badge auf "On" und die Stromversorgung vom FTDI offen lassen.

Zum Flashen des ESPs folgende Tastenkombination ausführen:

1. • drücken (gefüllter Kreis ist GPIO0)
2. ⏻ tippen (Power Taster ist Reset)
3. • loslassen (ESP ist nun im Bootloader Modus)
4. Arduino Upload starten
