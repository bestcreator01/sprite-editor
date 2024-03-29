/**
 * Author:     Crazy Broke Asians
 * Date:       Nov-16-2023
 * Course:     CS 3505, University of Utah
 * Assignment: A8: Sprite Editor
 * Reviewer:   Gloria Shin, Surbhi Saini, Seoin Kim, Monthon Paul, Atharv Kulkarni
 * File Contents
 *      It contains all necessary information needed to form a drawing tool.
*/
#include "drawingtools.h"
#include "qimage.h"

DrawingTools::DrawingTools(QObject* parent) : QObject(parent) {}

void DrawingTools::updatePixels(QImage &image, int x, int y, int color, int tool)
{
    switch (tool)
    {
    // pen
    case 0:
        pen.updatePixels(image, x, y, getQRgbColor(color));
        break;
    // eraser
    case 1:
        eraser.updatePixels(image, x, y);
        break;
    // spray
    case 2:
        spray.updatePixels(image, x, y, getQRgbColor(color));
        break;
    }
}

void DrawingTools::updateCustomPixels(QImage &image, int x, int y, QColor color, int tool)
{
    switch (tool)
    {
    // pen
    case 0:
        pen.updatePixels(image, x, y, color);
        break;
    // eraser
    case 1:
        eraser.updatePixels(image, x, y);
        break;
    // spray
    case 2:
        spray.updatePixels(image, x, y, color);
        break;
    }
}

QColor DrawingTools::getQRgbColor(int color)
{
    switch (color)
    {
    // red
    case 0:
        return qRgba(255,0,0, 1);
    // orange
    case 1:
        return qRgba(255,127,0, 1);
    // yellow
    case 2:
        return qRgba(255,255,0, 1);
    // green
    case 3:
        return qRgba(0,255,0, 1);
    // blue
    case 4:
        return qRgba(0,0,255, 1);
    // purple
    case 5:
        return qRgba(75,0,130, 1);
    // black
    case 6:
        return qRgba(0,0,0, 1);
    // white
    case 7:
        return qRgba(255,255,255, 1);
    }
}
