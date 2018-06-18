#include "pyramid.h"

Pyramid::Pyramid() { }

Pyramid::Pyramid(QPixmap mainl)
{
    mainLayer = PyramidLayer(mainl, 1);
    currentLayer = mainLayer;
}

Pyramid::~Pyramid() { }

void Pyramid::setMainLayer(QPixmap pixmap)
{
    mainLayer = PyramidLayer(pixmap, 1);
    currentLayer = mainLayer;
}

void Pyramid::addLayer(QPixmap pixmap, double coef)
{
    PyramidLayer newLayer(pixmap, coef);
    layers.push_back(newLayer);
}

void Pyramid::buildPyramid()
{
    QSize currentSize = mainLayer.getSize();
    double currentCoef = 2;

    while (currentSize.height() >= 360 && currentSize.width() >= 480)
    {
        currentSize /= 2;
        QPixmap newPixmap = mainLayer.getPixmap();
        addLayer(newPixmap, currentCoef);
        currentCoef *= 2;
    }
}

void Pyramid::drawCurrentLayer(QWidget *wgt, QScrollArea *sa)
{
    currentLayer.drawLayer(wgt, sa);
}
