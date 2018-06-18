#ifndef PYRAMID_H
#define PYRAMID_H

#include "pyramidlayer.h"

#include <QPixmap>

class Pyramid
{
public:
    Pyramid();
    Pyramid(QPixmap);
    ~Pyramid();
    void setMainLayer(QPixmap);
    void addLayer(QPixmap, double);
    void buildPyramid();
    void drawCurrentLayer(QWidget *, QScrollArea *);
    void setCurrentLayer(int);
    QSize getCurrentLayerSize();
    int getLayersCount();
private:
    PyramidLayer mainLayer;
    PyramidLayer currentLayer;
    QVector<PyramidLayer> layers;
    int layersCount;
};

#endif // PYRAMID_H
