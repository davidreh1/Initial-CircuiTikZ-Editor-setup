#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "circuit/circuitelement.h"

class CircuitCanvas;
class TikzGenerator;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newCircuit();
    void openCircuit();
    void saveCircuit();
    void exportTikZ();
    void addResistor();
    void addCapacitor();
    void addInductor();
    void addVoltageSource();
    void addCurrentSource();
    void addGround();
    void updateTikZCode();

private:
    void setupUI();
    void setupMenus();
    void setupToolbars();
    
    QWidget *centralWidget;
    QSplitter *splitter;
    CircuitCanvas *canvas;
    QTextEdit *tikzCodeEditor;
    QToolBar *elementToolbar;
    TikzGenerator *tikzGenerator;
};

#endif // MAINWINDOW_H
