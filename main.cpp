#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setMinimumSize(700, 600);
    w.setWindowTitle("Pyramid");
    w.show();

    return a.exec();
}
