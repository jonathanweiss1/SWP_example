#include "mainwindow.h"
#include "tablecontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TableController controller;
    MainWindow w(&controller);
    //initTable has to be called after the gui (MainWindow) has connected itself to the controller
    controller.initTable();
    w.show();
    return a.exec();
}
