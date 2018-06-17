#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPixmap>

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
