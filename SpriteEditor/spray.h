#ifndef SPRAY_H
#define SPRAY_H

#include "qimage.h"

class Spray
{
public:
    Spray();
    void updatePixels(QImage &image, int x, int y, QColor color);
};

#endif // SPRAY_H
