#include "spray.h"

Spray::Spray()
{

}

void Spray::updatePixels(QImage &image, int x, int y, QRgb color)
{
    // calculated pixel coordinates from mouse position
    int pixelX = (x - 180) / 20;
    int pixelY = (y - 60) / 20;

    image.setPixel(x, y, color);
    image.setPixel(x, y, color);
    image.setPixel(x-1, y-1, color);
    image.setPixel(x-1, y, color);
    image.setPixel(x-2, y, color);
    image.setPixel(x, y, color);
    image.setPixel(x+1, y+1, color);
    image.setPixel(x, y+1, color);
    image.setPixel(x-1, y+1, color);
    image.setPixel(x-2, y+1, color);
    image.setPixel(x-3, y+1, color);
    image.setPixel(x, y+2, color);
    image.setPixel(x-1, y+2, color);
    image.setPixel(x-2, y+2, color);
    image.setPixel(x-1, y+3, color);
}
