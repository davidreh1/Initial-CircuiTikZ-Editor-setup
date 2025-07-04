#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("CircuiTikZ Editor");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("CircuiTikZ Editor Team");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
