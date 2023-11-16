/**
 * Author:     Crazy Broke Asians
 * Date:       Nov-16-2023
 * Course:     CS 3505, University of Utah
 * Assignment: A8: Sprite Editor
 * Reviewer:   Gloria Shin, Surbhi Saini, Seoin Kim, Monthon Paul, Atharv Kulkarni
 * File Contents
 *      It contains all necessary information needed to form the Eraser tool.
*/
#include "eraser.h"

Eraser::Eraser() {}

void Eraser::updatePixels(QImage &image, int x, int y)
{
    // Set the pixels to the default transparent colour
    image.setPixel(x, y, qRgba(255, 255, 255, 0));
}
