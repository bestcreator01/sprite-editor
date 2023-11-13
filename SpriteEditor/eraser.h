#ifndef ERASER_H
#define ERASER_H

#include "qimage.h"
class Eraser
{
public:
    Eraser();
    void updatePixels(QImage &image, int x, int y);
};

#endif // ERASER_H
