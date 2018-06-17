#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPixmap qpm(500, 500);
    QPainter pnt(this);

    qpm.fill(Qt::white);
    pnt.drawPixmap(150, 50, qpm.width(), qpm.height(), qpm);
    Q_UNUSED(event);
}

void MainWindow::on_actionOpen_triggered()
{
    ui->statusBar->showMessage("Open file");

    QString filename = QFileDialog::getOpenFileName(this, "Open file", QDir::currentPath(), "Images (*.png *.jpg)");
    QImage imageFile;
    if (!filename.isNull()) {
        if (!imageFile.load(filename)) {
            QMessageBox::warning(this, "Error", "Cannot open file");
        }
    }
    ui->statusBar->clearMessage();
}
