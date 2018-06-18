#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pyramid.h"

#include <QMainWindow>
#include <QScrollArea>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    QWidget *wgt;
    QScrollArea *sa;
    Pyramid pyr;
};

#endif // MAINWINDOW_H
