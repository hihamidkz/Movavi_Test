#include "pyramidlayer.h"

PyramidLayer::PyramidLayer() { }

PyramidLayer::PyramidLayer(QPixmap mainlayer, double comp_coef)
{
    coef = comp_coef;

    pixmap = mainlayer.scaled(mainlayer.size() / coef);
    size = pixmap.size();
}

PyramidLayer::~PyramidLayer() { }

void PyramidLayer::drawLayer(QWidget *drawWgt, QScrollArea *sArea)
{
    pixmap = pixmap.scaled(size * coef);
    QPalette pal;
    pal.setBrush(drawWgt->backgroundRole(), QBrush(pixmap));

    drawWgt->setPalette(pal);
    drawWgt->setAutoFillBackground(true);
    drawWgt->setFixedSize(pixmap.width(), pixmap.height());
    sArea->setWidget(drawWgt);
}

QSize PyramidLayer::getSize()
{
    return size;
}

QPixmap PyramidLayer::getPixmap()
{
    return pixmap;
}
