#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QtMath>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMinimumSize(540, 690);
    this->setWindowTitle("Pyramid");

    currentCoef = 2;

    wgt = new QWidget;
    sa = new QScrollArea;

    layoutWgt = new QWidget(this);
    this->setCentralWidget(layoutWgt);

    hLayout1 = new QHBoxLayout;
    hLayout2 = new QHBoxLayout;
    vLayout = new QVBoxLayout;

    QPixmap pixmap(500, 500);
    pixmap.fill();

    QPalette pal;
    pal.setBrush(wgt->backgroundRole(), QBrush(pixmap));
    wgt->setPalette(pal);
    wgt->setAutoFillBackground(true);
    wgt->setFixedSize(pixmap.width(), pixmap.height());
    sa->setWidget(wgt);
    sa->setMinimumSize(502, 502);
    sa->setAlignment(Qt::AlignCenter);

    fileLbl = new QLabel;
    fileLbl->setText("File: ");

    file = new QComboBox;
    connect(file, SIGNAL(currentIndexChanged(QString)), SLOT(fileComboBox_index_changed()));

    box = new QComboBox;
    connect(box, SIGNAL(currentIndexChanged(int)), SLOT(comboBox_index_changed()));

    layerLbl = new QLabel;
    layerLbl->setText("Layer:");

    sizeTextLbl = new QLabel;
    sizeTextLbl->setText("Size: ");

    sizeLbl = new QLabel;

    coefLbl = new QLabel;
    coefLbl->setText("Coefficient of decrement: ");

    coefTxt = new QLineEdit;
    coefTxt->setMaximumWidth(100);
    coefTxt->setText("2");

    coefBtn = new QPushButton("Apply");
    connect(coefBtn, SIGNAL(clicked(bool)), SLOT(coefBtn_pushed()));

    hLayout1->addStretch(1);
    hLayout1->addWidget(fileLbl);
    hLayout1->addWidget(file);
    hLayout1->addWidget(layerLbl);
    hLayout1->addWidget(box);
    hLayout1->addWidget(sizeTextLbl);
    hLayout1->addWidget(sizeLbl);
    hLayout1->addStretch(1);

    hLayout2->addStretch();
    hLayout2->addWidget(coefLbl);
    hLayout2->addWidget(coefTxt);
    hLayout2->addWidget(coefBtn);
    hLayout2->addStretch();

    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addWidget(sa);
    vLayout->setSpacing(20);
    vLayout->setMargin(20);
    layoutWgt->setLayout(vLayout);
}

MainWindow::~MainWindow()
{
    delete vLayout;
    delete ui;
}

// Update Layers-ComboBox items
void MainWindow::setLayersComboBox()
{
    box->clear();

    QStringList lst;
    int count = currentPyr.getLayersCount(currentCoef);
    for (int i = 0; i < count; i++) {
        lst << QString::number(i);
    }
    box->addItems(lst);
}

void MainWindow::on_actionOpen_triggered()
{
    ui->statusBar->showMessage("Open file");

    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Open file",
                                                    QDir::currentPath(),
                                                    "Images (*.png *.jpg)");
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
    currentPyr = pyr;
    pyramids.insert(fname, pyr);

    double diag = sqrt(pow(pixmap.width(), 2) + pow(pixmap.height(), 2));
    diags.insert(diag, fname);

    file->clear();
    foreach (QString str, diags.values()) {
        file->addItem(str);
    }
    file->setCurrentText(fname);

    QString size = QString::number(pyr.getCurrentLayerSize().width())
            + QString::fromUtf8("x")
            + QString::number(pyr.getCurrentLayerSize().height());
    sizeLbl->setText(size);
}

void MainWindow::comboBox_index_changed()
{
    currentPyr.generateLayer(pow(currentCoef, box->currentIndex()));
    currentPyr.drawCurrentLayer(wgt, sa);

    QString size = QString::number(currentPyr.getCurrentLayerSize().width())
            + QString::fromUtf8("x")
            + QString::number(currentPyr.getCurrentLayerSize().height());
    sizeLbl->setText(size);
}

void MainWindow::fileComboBox_index_changed()
{
    if (file->currentText() == "")
        return;

    currentPyr = pyramids.find(file->currentText()).value();
    currentPyr.drawCurrentLayer(wgt, sa);

    setLayersComboBox();
    QString size = QString::number(currentPyr.getCurrentLayerSize().width())
            + QString::fromUtf8("x")
            + QString::number(currentPyr.getCurrentLayerSize().height());
    sizeLbl->setText(size);
}

void MainWindow::coefBtn_pushed()
{
    bool ok;
    currentCoef = coefTxt->text().toDouble(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid value");
        coefTxt->setText("2");
        currentCoef = 2;
        return;
    } else if (currentCoef <= 1) {
        QMessageBox::warning(this, "Error", "Coefficient must be greater than 1");
        coefTxt->setText("2");
        currentCoef = 2;
        return;
    }

    if (!pyramids.isEmpty())
        setLayersComboBox();
}
