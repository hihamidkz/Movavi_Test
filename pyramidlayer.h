#ifndef PYRAMIDLAYER_H
#define PYRAMIDLAYER_H

#include <QPixmap>
#include <QScrollArea>

class PyramidLayer
{
public:
    PyramidLayer();
    PyramidLayer(QPixmap, double);
    ~PyramidLayer();
    void drawLayer(QWidget *, QScrollArea *);
    QSize getSize();
    QPixmap getPixmap();

private:
    QPixmap pixmap;
    QSize size;
    double coef; // Compression coefficient
};

#endif // PYRAMIDLAYER_H
