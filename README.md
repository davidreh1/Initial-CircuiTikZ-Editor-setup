# CircuiTikZ Editor

Ein grafischer Editor für elektronische Schaltkreise, der automatisch CircuiTikZ LaTeX-Code generiert.

![CircuiTikZ Editor](https://img.shields.io/badge/Qt-6.0+-green.svg)
![Platform](https://img.shields.io/badge/platform-Linux-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

## 🚀 Features

- ✅ **Grafischer Schaltkreis-Editor** - Drag & Drop Interface
- ✅ **Echtzeit TikZ-Generierung** - Sofortige LaTeX-Code-Erstellung
- ✅ **Elementbibliothek** - Widerstände, Kondensatoren, Spulen, Quellen
- ✅ **Grid-Snapping** - Präzise Platzierung auf Raster
- ✅ **Zoom & Pan** - Mausrad-Zoom und Navigation
- ✅ **Export-Funktionen** - .tex Dateien für LaTeX-Dokumente
- ⏳ **Verbindungen** - Automatische Draht-Verbindungen (geplant)
- ⏳ **Eigenschaften-Editor** - Element-Parameter bearbeiten (geplant)

## 📋 Systemanforderungen

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev qt6-tools-dev libqt6widgets6
```

### Fedora/CentOS
```bash
sudo dnf install gcc-c++ cmake qt6-qtbase-devel qt6-qttools-devel
```

### Arch Linux
```bash
sudo pacman -S base-devel cmake qt6-base qt6-tools
```

## 🔧 Installation

### 1. Repository klonen
```bash
git clone https://github.com/IhrUsername/circuitikz-editor.git
cd circuitikz-editor
```

### 2. Kompilieren
```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

### 3. Starten
```bash
./circuitikz-editor
```

## 🎯 Verwendung

### Grundlegende Bedienung
1. **Element auswählen** - Klicken Sie auf einen Button in der Toolbar
2. **Element platzieren** - Klicken Sie auf die gewünschte Position im Canvas
3. **TikZ-Code** - Wird automatisch im rechten Panel generiert
4. **Exportieren** - Menü → File → Export as TikZ

### Shortcuts
- `Ctrl+N` - Neue Schaltung
- `Ctrl+O` - Schaltung öffnen
- `Ctrl+S` - Schaltung speichern
- `Ctrl+E` - Als TikZ exportieren
- `Mausrad` - Zoom in/out
- `Linke Maustaste` - Element platzieren/auswählen

## 📖 TikZ Output Beispiel

```latex
\begin{circuitikz}[scale=1.0]
% Resistors
\draw (0.00,0.00) to[R, l=$R_1$] ++(2,0);
\draw (4.00,0.00) to[R, l=$R_2$] ++(2,0);

% Capacitors
\draw (2.00,-2.00) to[C, l=$C_1$] ++(2,0);

% Sources
\draw (0.00,-4.00) to[V, l=$V_1$] ++(0,-2);

% Ground connections
\node[ground] at (0.00,-6.00) {};
\end{circuitikz}
```

## 🏗️ Projektstruktur

```
circuitikz-editor/
├── CMakeLists.txt          # Build-Konfiguration
├── README.md               # Diese Datei
├── LICENSE                 # MIT Lizenz
├── src/
│   ├── main.cpp           # Hauptprogramm
│   ├── mainwindow.h/.cpp  # Hauptfenster
│   └── circuit/
│       ├── circuitelement.h/.cpp  # Schaltkreis-Elemente
│       ├── circuitcanvas.h/.cpp   # Zeichenfläche
│       └── tikzgenerator.h/.cpp   # TikZ-Code-Generator
├── tests/                  # Unit Tests (geplant)
└── docs/                   # Dokumentation
```

## 🔄 Entwicklung

### Dependencies
- **Qt6** - GUI Framework
- **CMake** - Build System
- **C++17** - Programmiersprache

### Build-Optionen
```bash
# Debug Build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release Build
cmake -DCMAKE_BUILD_TYPE=Release ..

# Mit Tests
cmake -DENABLE_TESTING=ON ..
```

### Beitragen
1. Fork des Repositories
2. Feature-Branch erstellen (`git checkout -b feature/AmazingFeature`)
3. Änderungen committen (`git commit -m 'Add some AmazingFeature'`)
4. Branch pushen (`git push origin feature/AmazingFeature`)
5. Pull Request erstellen

## 📚 CircuiTikZ Dokumentation

CircuiTikZ ist eine LaTeX-Bibliothek für das Zeichnen von elektronischen Schaltkreisen:
- [CircuiTikZ Manual](http://mirrors.ctan.org/graphics/pgf/contrib/circuitikz/doc/circuitikzmanual.pdf)
- [TikZ & PGF Manual](http://mirrors.ctan.org/graphics/pgf/base/doc/pgfmanual.pdf)

### LaTeX-Verwendung
```latex
\documentclass{article}
\usepackage{circuitikz}

\begin{document}
\begin{figure}[htbp]
\centering
% Hier den generierten TikZ-Code einfügen
\caption{Meine Schaltung}
\end{figure}
\end{document}
```

## 🐛 Bekannte Issues

- [ ] Verbindungen zwischen Elementen noch nicht implementiert
- [ ] Element-Eigenschaften noch nicht editierbar
- [ ] Undo/Redo-Funktionalität fehlt

## 📄 Lizenz

Dieses Projekt steht unter der MIT-Lizenz - siehe [LICENSE](LICENSE) Datei für Details.

## 🙏 Danksagungen

- [Qt Project](https://www.qt.io/) - Für das ausgezeichnete GUI-Framework
- [CircuiTikZ](https://github.com/circuitikz/circuitikz) - Für die LaTeX-Bibliothek
- [TikZ & PGF](https://github.com/pgf-tikz/pgf) - Für das Grafik-Framework

## 📞 Kontakt

Bei Fragen oder Vorschlägen können Sie gerne ein Issue erstellen oder eine Pull Request einreichen.

---

**Hinweis**: Dieses Projekt befindet sich in aktiver Entwicklung. Weitere Features werden kontinuierlich hinzugefügt.
