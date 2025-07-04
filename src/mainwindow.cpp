#include "mainwindow.h"
#include "circuit/circuitcanvas.h"
#include "circuit/tikzgenerator.h"
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(nullptr)
    , splitter(nullptr)
    , canvas(nullptr)
    , tikzCodeEditor(nullptr)
    , elementToolbar(nullptr)
    , tikzGenerator(nullptr)
{
    setupUI();
    setupMenus();
    setupToolbars();
    
    // Initialize TikZ generator
    tikzGenerator = new TikzGenerator(this);
    
    // Connect canvas to TikZ code update
    connect(canvas, &CircuitCanvas::circuitChanged, 
            this, &MainWindow::updateTikZCode);
    
    setWindowTitle("CircuiTikZ Editor v1.0");
    resize(1200, 800);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget;
    setCentralWidget(centralWidget);
    
    // Create main splitter
    splitter = new QSplitter(Qt::Horizontal, this);
    
    // Create circuit canvas
    canvas = new CircuitCanvas(this);
    canvas->setMinimumSize(600, 400);
    
    // Create TikZ code editor
    tikzCodeEditor = new QTextEdit(this);
    tikzCodeEditor->setMinimumSize(300, 400);
    tikzCodeEditor->setPlainText("% TikZ code will appear here\n\\begin{circuitikz}\n\n\\end{circuitikz}");
    
    // Add widgets to splitter
    splitter->addWidget(canvas);
    splitter->addWidget(tikzCodeEditor);
    splitter->setSizes({800, 400});
    
    // Create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter);
    centralWidget->setLayout(mainLayout);
}

void MainWindow::setupMenus()
{
    // File Menu
    QMenu *fileMenu = menuBar()->addMenu("&File");
    
    QAction *newAction = new QAction("&New", this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::newCircuit);
    fileMenu->addAction(newAction);
    
    QAction *openAction = new QAction("&Open", this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::openCircuit);
    fileMenu->addAction(openAction);
    
    QAction *saveAction = new QAction("&Save", this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveCircuit);
    fileMenu->addAction(saveAction);
    
    fileMenu->addSeparator();
    
    QAction *exportAction = new QAction("Export as TikZ", this);
    exportAction->setShortcut(QKeySequence("Ctrl+E"));
    connect(exportAction, &QAction::triggered, this, &MainWindow::exportTikZ);
    fileMenu->addAction(exportAction);
    
    fileMenu->addSeparator();
    
    QAction *exitAction = new QAction("E&xit", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);
}

void MainWindow::setupToolbars()
{
    elementToolbar = addToolBar("Elements");
    
    QPushButton *resistorBtn = new QPushButton("Resistor", this);
    connect(resistorBtn, &QPushButton::clicked, this, &MainWindow::addResistor);
    elementToolbar->addWidget(resistorBtn);
    
    QPushButton *capacitorBtn = new QPushButton("Capacitor", this);
    connect(capacitorBtn, &QPushButton::clicked, this, &MainWindow::addCapacitor);
    elementToolbar->addWidget(capacitorBtn);
    
    QPushButton *inductorBtn = new QPushButton("Inductor", this);
    connect(inductorBtn, &QPushButton::clicked, this, &MainWindow::addInductor);
    elementToolbar->addWidget(inductorBtn);
    
    QPushButton *voltageBtn = new QPushButton("Voltage Source", this);
    connect(voltageBtn, &QPushButton::clicked, this, &MainWindow::addVoltageSource);
    elementToolbar->addWidget(voltageBtn);
    
    QPushButton *currentBtn = new QPushButton("Current Source", this);
    connect(currentBtn, &QPushButton::clicked, this, &MainWindow::addCurrentSource);
    elementToolbar->addWidget(currentBtn);
    
    QPushButton *groundBtn = new QPushButton("Ground", this);
    connect(groundBtn, &QPushButton::clicked, this, &MainWindow::addGround);
    elementToolbar->addWidget(groundBtn);
    
    statusBar()->showMessage("Ready");
}

void MainWindow::newCircuit()
{
    canvas->clearCircuit();
    updateTikZCode();
    statusBar()->showMessage("New circuit created", 2000);
}

void MainWindow::openCircuit()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "Open Circuit", "", "TikZ Files (*.tex);;All Files (*)");
    
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            tikzCodeEditor->setPlainText(in.readAll());
            statusBar()->showMessage("Circuit loaded", 2000);
        } else {
            QMessageBox::warning(this, "Error", "Could not open file");
        }
    }
}

void MainWindow::saveCircuit()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        "Save Circuit", "", "TikZ Files (*.tex);;All Files (*)");
    
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << tikzCodeEditor->toPlainText();
            statusBar()->showMessage("Circuit saved", 2000);
        } else {
            QMessageBox::warning(this, "Error", "Could not save file");
        }
    }
}

void MainWindow::exportTikZ()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        "Export TikZ", "", "LaTeX Files (*.tex)");
    
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "\\documentclass{article}\n";
            out << "\\usepackage{circuitikz}\n";
            out << "\\begin{document}\n";
            out << tikzCodeEditor->toPlainText();
            out << "\n\\end{document}\n";
            statusBar()->showMessage("TikZ exported", 2000);
        }
    }
}

void MainWindow::addResistor()
{
    canvas->setActiveElementType(ElementType::Resistor);
    statusBar()->showMessage("Click to place resistor");
}

void MainWindow::addCapacitor()
{
    canvas->setActiveElementType(ElementType::Capacitor);
    statusBar()->showMessage("Click to place capacitor");
}

void MainWindow::addInductor()
{
    canvas->setActiveElementType(ElementType::Inductor);
    statusBar()->showMessage("Click to place inductor");
}

void MainWindow::addVoltageSource()
{
    canvas->setActiveElementType(ElementType::VoltageSource);
    statusBar()->showMessage("Click to place voltage source");
}

void MainWindow::addCurrentSource()
{
    canvas->setActiveElementType(ElementType::CurrentSource);
    statusBar()->showMessage("Click to place current source");
}

void MainWindow::addGround()
{
    canvas->setActiveElementType(ElementType::Ground);
    statusBar()->showMessage("Click to place ground");
}

void MainWindow::updateTikZCode()
{
    if (tikzGenerator && canvas) {
        QString tikzCode = tikzGenerator->generateFromCanvas(canvas);
        tikzCodeEditor->setPlainText(tikzCode);
    }
}
