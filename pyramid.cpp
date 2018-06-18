#include "pyramid.h"

Pyramid::Pyramid() {layersCount = 1;}

Pyramid::Pyramid(QPixmap mainl)
{
    mainLayer = PyramidLayer(mainl, 1);
    currentLayer = mainLayer;
    layers.push_back(currentLayer);
    layersCount = 1;
}

Pyramid::~Pyramid() { }

void Pyramid::setMainLayer(QPixmap pixmap)
{
    mainLayer = PyramidLayer(pixmap, 1);
    currentLayer = mainLayer;
    layers.push_back(currentLayer);
}

void Pyramid::addLayer(QPixmap pixmap, double coef)
{
    PyramidLayer newLayer(pixmap, coef);
    layers.push_back(newLayer);
    layersCount++;
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

void Pyramid::setCurrentLayer(int number)
{
    currentLayer = layers[number];
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
    return layersCount;
}
