/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    It contains all necessary implementation needed to form a drawing tool.
*/

#include "drawingtools.h"
#include "qimage.h"
#include <QDebug>
#include <QColor>

DrawingTools::DrawingTools() {}

void DrawingTools::updatePixels(QImage &image, int x, int y, int color, int tool)
{
    switch (tool)
    {
        // Pen
        case 0:
            pen.updatePixels(image, x, y, getQRgbColor(color));
            break;
        // Eraser
        case 1:
            eraser.updatePixels(image, x, y);
            break;
        case 2:
            spray.updatePixels(image, x, y, getQRgbColor(color));
            break;
    }
}

QRgb DrawingTools::getQRgbColor(int color)
{
    switch (color)
    {
    // red
    case 0:
        return qRgb(255,0,0);
    // green
    case 1:
        return qRgb(0,255,0);
    // blue
    case 2:
        return qRgb(0,0,255);
    // black
    case 3:
        return qRgb(0,0,0);
    }
}
