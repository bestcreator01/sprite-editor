#include "pen.h"

Pen::Pen()
{

}

void Pen::updatePixels(QImage &image, int x, int y, QColor qColor)
{
    image.setPixel(x, y, qColor.rgba());
}
