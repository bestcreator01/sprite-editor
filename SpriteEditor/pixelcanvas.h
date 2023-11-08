#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include <QObject>
#include "pixel.h"

class PixelCanvas : public QObject
{
    Q_OBJECT
    Pixel pixel[32][32];
    int sizeOfCanvas = 32;

public:
    explicit PixelCanvas(QObject *parent = nullptr);

signals:

};

#endif // PIXELCANVAS_H
