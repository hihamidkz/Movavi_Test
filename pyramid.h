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
    void generateLayer(double);
    void drawCurrentLayer(QWidget *, QScrollArea *);
    QSize getCurrentLayerSize();
    int getLayersCount();
private:
    PyramidLayer mainLayer;
    PyramidLayer currentLayer;
    int layersCount;
};

#endif // PYRAMID_H
