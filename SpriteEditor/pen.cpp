/**
 * Author:     Crazy Broke Asians
 * Date:       Nov-16-2023
 * Course:     CS 3505, University of Utah
 * Assignment: A8: Sprite Editor
 * File Contents
 *      It contains all necessary information needed to form the Pen tool.
*/
#include "pen.h"

Pen::Pen() {}

void Pen::updatePixels(QImage &image, int x, int y, QColor qColor)
{
    // Set the pixels to the colour set by the user
    image.setPixel(x, y, qColor.rgba());
}
