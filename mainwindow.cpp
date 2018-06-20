#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMinimumSize(570, 650);
    this->setWindowTitle("Pyramid");

    wgt = new QWidget;
    sa = new QScrollArea(this);

    sa->setGeometry(40, 110, 502, 502);
    QPixmap pixmap(500, 500);
    pixmap.fill();

    QPalette pal;
    pal.setBrush(wgt->backgroundRole(), QBrush(pixmap));
    wgt->setPalette(pal);
    wgt->setAutoFillBackground(true);
    wgt->setFixedSize(pixmap.width(), pixmap.height());
    sa->setWidget(wgt);

    fileLbl = new QLabel(this);
    fileLbl->setGeometry(40, 60, 40, 27);
    fileLbl->setText("File: ");

    file = new QComboBox(this);
    file->setGeometry(75, 60, 150, 27);
    connect(file, SIGNAL(currentIndexChanged(QString)), SLOT(fileComboBox_index_changed()));

    box = new QComboBox(this);
    box->setGeometry(300, 60, 85, 27);
    connect(box, SIGNAL(currentIndexChanged(int)), SLOT(comboBox_index_changed()));

    layerLbl = new QLabel(this);
    layerLbl->setGeometry(250, 60, 60, 27);
    layerLbl->setText("Layer:");

    sizeTextLbl = new QLabel(this);
    sizeTextLbl->setGeometry(400, 60, 40, 27);
    sizeTextLbl->setText("Size: ");

    sizeLbl = new QLabel(this);
    sizeLbl->setGeometry(450, 60, 80, 27);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Update Layers-ComboBox items
void MainWindow::setLayersComboBox()
{
    box->clear();

    QStringList lst;
    int count = currentPyr.getLayersCount();
    for (int i = 0; i < count; i++) {
        lst << QString::number(i);
    }
    box->addItems(lst);
}

void MainWindow::on_actionOpen_triggered()
{
    ui->statusBar->showMessage("Open file");

    QString filename = QFileDialog::getOpenFileName(this, "Open file", QDir::currentPath(), "Images (*.png *.jpg)");
    QPixmap pixmap;
    if (filename.isNull()) {
        return;
    }

    QFileInfo fi(filename);
    QString fname = fi.fileName();
    if (pyramids.find(fname) != pyramids.end()) {
        QMessageBox::warning(this, "Error", "File \"" + fname + "\" already exists");
        return;
    }

    if (!pixmap.load(filename)) {
        QMessageBox::warning(this, "Error", "Cannot open file " + fname);
        return;
    }

    ui->statusBar->clearMessage();

    Pyramid pyr = Pyramid();
    pyr.setMainLayer(pixmap);
    pyr.drawCurrentLayer(wgt, sa);
    currentPyr = pyr;
    pyramids.insert(fname, pyr);

    double diag = sqrt(pow(pixmap.width(), 2) + pow(pixmap.height(), 2));
    diags.insert(diag, fname);

    file->clear();
    foreach (QString str, diags.values()) {
        file->addItem(str);
    }
    file->setCurrentText(fname);

    QString size = QString::number(pyr.getCurrentLayerSize().width()) + QString::fromUtf8("x") + QString::number(pyr.getCurrentLayerSize().height());
    sizeLbl->setText(size);
}

void MainWindow::comboBox_index_changed()
{
    currentPyr.generateLayer(box->currentText().toInt() * 2);
    currentPyr.drawCurrentLayer(wgt, sa);

    QString size = QString::number(currentPyr.getCurrentLayerSize().width()) + QString::fromUtf8("x") + QString::number(currentPyr.getCurrentLayerSize().height());
    sizeLbl->setText(size);
}

void MainWindow::fileComboBox_index_changed()
{
    if (file->currentText() == "")
        return;

    currentPyr = pyramids.find(file->currentText()).value();
    currentPyr.drawCurrentLayer(wgt, sa);

    setLayersComboBox();
    QString size = QString::number(currentPyr.getCurrentLayerSize().width()) + QString::fromUtf8("x") + QString::number(currentPyr.getCurrentLayerSize().height());
    sizeLbl->setText(size);
}
