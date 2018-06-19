#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pyramid.h"

#include <QMainWindow>
#include <QScrollArea>
#include <QComboBox>
#include <QLabel>

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
    void comboBox_index_changed();
    void fileComboBox_index_changed();

private:
    Ui::MainWindow *ui;
    QWidget *wgt;
    QScrollArea *sa;
    QComboBox *box;
    QComboBox *file;
    QLabel *layerLbl;
    QLabel *fileLbl;
    QLabel *sizeTextLbl;
    QLabel *sizeLbl;
    QMap<QString, Pyramid> pyramids;
    Pyramid currentPyr;

    void setLayersComboBox();
};

#endif // MAINWINDOW_H
