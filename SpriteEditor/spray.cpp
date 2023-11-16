/**
 * Author:     Crazy Broke Asians
 * Date:       Nov-16-2023
 * Course:     CS 3505, University of Utah
 * Assignment: A8: Sprite Editor
 * Reviewer:   Gloria Shin, Surbhi Saini, Seoin Kim, Monthon Paul, Atharv Kulkarni
 * File Contents
 *      It contains all necessary information needed to form the Spray tool.
*/
#include <random>
#include "spray.h"

Spray::Spray() {}

void Spray::updatePixels(QImage &image, int x, int y, QColor color)
{
    for (int i = 0; i < 5; ++i)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> xValue(x-2, x+2);
        std::uniform_int_distribution<int> yValue(y-2, y+2);

        int whiteXValue = xValue(gen);
        int whiteYValue = yValue(gen);

        image.setPixel(whiteXValue, whiteYValue, color.rgba());
    }
}
