#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pyramid.h"

#include <QMainWindow>
#include <QScrollArea>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QLineEdit>

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
    void coefBtn_pushed();

private:
    Ui::MainWindow *ui;
    QWidget *wgt; // Widget for ScrollArea
    QWidget *layoutWgt; // Widget to set a layout
    QScrollArea *sa;
    QComboBox *box;
    QComboBox *file;
    QLabel *layerLbl;
    QLabel *fileLbl;
    QLabel *sizeTextLbl;
    QLabel *sizeLbl;
    QLabel *coefLbl;
    QLineEdit *coefTxt;
    QPushButton *coefBtn;
    QMap<QString, Pyramid> pyramids;
    QMap<double, QString> diags; // Pairs <diagonal, filename>
    Pyramid currentPyr;
    QHBoxLayout *hLayout1;
    QHBoxLayout *hLayout2;
    QVBoxLayout *vLayout;

    double currentCoef;
    void setLayersComboBox();
};

#endif // MAINWINDOW_H
