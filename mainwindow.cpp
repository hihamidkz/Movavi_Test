#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wgt = new QWidget;
    sa = new QScrollArea(this);

    sa->setGeometry(185, 70, 502, 502);
    QPixmap pixmap(500, 500);
    pixmap.fill();

    QPalette pal;
    pal.setBrush(wgt->backgroundRole(), QBrush(pixmap));
    wgt->setPalette(pal);
    wgt->setAutoFillBackground(true);
    wgt->setFixedSize(pixmap.width(), pixmap.height());
    sa->setWidget(wgt);

    pyr = Pyramid();

    box = new QComboBox(this);
    box->setGeometry(80, 70, 85, 27);

    layerLbl = new QLabel(this);
    layerLbl->setGeometry(20, 70, 60, 27);
    layerLbl->setText("Layer:");

    sizeTextLbl = new QLabel(this);
    sizeTextLbl->setGeometry(20, 97, 40, 27);
    sizeTextLbl->setText("Size: ");

    sizeLbl = new QLabel(this);
    sizeLbl->setGeometry(60, 97, 80, 27);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    ui->statusBar->showMessage("Open file");

    QString filename = QFileDialog::getOpenFileName(this, "Open file", QDir::currentPath(), "Images (*.png *.jpg)");
    QPixmap pixmap;
    if (filename.isNull()) {
        return;
    }

    if (!pixmap.load(filename)) {
        QMessageBox::warning(this, "Error", "Cannot open file");
        return;
    }

    ui->statusBar->clearMessage();
    pyr.setMainLayer(pixmap);
    pyr.buildPyramid();
    pyr.drawCurrentLayer(wgt, sa);

    QString size = QString::number(pyr.getCurrentLayerSize().width()) + QString::fromUtf8("x") + QString::number(pyr.getCurrentLayerSize().height());
    sizeLbl->setText(size);

    QStringList lst;
    for (int i = 0; i < pyr.getLayersCount(); i++) {
        lst << QString::number(i);
    }
    box->addItems(lst);
    connect(box, SIGNAL(currentIndexChanged(QString)), SLOT(comboBox_index_changed()));
}

void MainWindow::comboBox_index_changed()
{
    pyr.setCurrentLayer(box->currentText().toInt());
    pyr.drawCurrentLayer(wgt, sa);

    QString size = QString::number(pyr.getCurrentLayerSize().width()) + QString::fromUtf8("x") + QString::number(pyr.getCurrentLayerSize().height());
    sizeLbl->setText(size);
}
