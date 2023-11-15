#ifndef PEN_H
#define PEN_H

#include "qimage.h"

class Pen
{
public:
    Pen();
    void updatePixels(QImage &image, int x, int y, QColor color);
};

#endif // PEN_H
