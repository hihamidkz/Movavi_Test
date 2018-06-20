#include "pyramid.h"

Pyramid::Pyramid() {layersCount = 1;}

Pyramid::Pyramid(QPixmap mainl)
{
    mainLayer = PyramidLayer(mainl, 1);
    currentLayer = mainLayer;
    layersCount = 1;
}

Pyramid::~Pyramid() { }

void Pyramid::setMainLayer(QPixmap pixmap)
{
    mainLayer = PyramidLayer(pixmap, 1);
    currentLayer = mainLayer;
}

void Pyramid::generateLayer(double coef)
{
    if (coef == 0) {
        currentLayer = mainLayer;
        return;
    }

    QPixmap newPixmap = mainLayer.getPixmap();
    currentLayer = PyramidLayer(newPixmap, coef);
}

void Pyramid::drawCurrentLayer(QWidget *wgt, QScrollArea *sa)
{
    currentLayer.drawLayer(wgt, sa);
}

QSize Pyramid::getCurrentLayerSize()
{
    return currentLayer.getSize();
}

int Pyramid::getLayersCount()
{
    QSize currentSize = mainLayer.getSize();
    double currentCoef = 2;

    while (currentSize.height() >= 100 && currentSize.width() >= 100)
    {
        currentSize /= 2;
        currentCoef *= 2;
        layersCount++;
    }

    return layersCount;
}
