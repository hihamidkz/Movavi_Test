#include "pyramid.h"

Pyramid::Pyramid() {}

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

int Pyramid::getLayersCount(double coef)
{
    QSize currentSize = mainLayer.getSize();
    double currentCoef = coef;
    layersCount = 1;

    while (currentSize.height() >= 100 && currentSize.width() >= 100)
    {
        currentSize /= coef;
        currentCoef *= coef;
        layersCount++;
    }

    return layersCount;
}
