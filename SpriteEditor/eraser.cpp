#include "eraser.h"

Eraser::Eraser()
{

}

void Eraser::updatePixels(QImage &image, int x, int y)
{
    image.setPixel(x, y, qRgba(255, 255, 255, 0));
}
