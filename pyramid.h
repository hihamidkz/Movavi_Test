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
    void setMainLayer(QPixmap pixmap);
    void addLayer(QPixmap, double);
    void buildPyramid();
    void drawCurrentLayer(QWidget *, QScrollArea *);

private:
    PyramidLayer mainLayer;
    PyramidLayer currentLayer;
    QVector<PyramidLayer> layers;
};

#endif // PYRAMID_H
