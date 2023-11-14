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

DrawingTools::DrawingTools(QObject* parent) : QObject(parent) {}

void DrawingTools::updatePixels(QImage &image, int x, int y, int color, int tool)
{
    switch (tool)
    {
    // pen
    case 0:
        pen.updatePixels(image, x, y, getQRgbColor(color));
        coordinates.insert(std::make_pair(x, y));
        emit updatedVectorCoordinates(coordinates);
        break;
    // eraser
    case 1:
        eraser.updatePixels(image, x, y);
        coordinates.remove(std::make_pair(x, y));
        emit removeVectorCoordinates(x, y);
        break;
    // spray
    case 2:
        spray.updatePixels(image, x, y, getQRgbColor(color));
        insertSprayedPixels(x, y);
        emit updatedVectorCoordinates(coordinates);
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
    // orange
    case 1:
        return qRgb(255,127,0);
    // yellow
    case 2:
        return qRgb(255,255,0);
    // green
    case 3:
        return qRgb(0,255,0);
    // blue
    case 4:
        return qRgb(0,0,255);
    // purple
    case 5:
        return qRgb(75,0,130);
    // black
    case 6:
        return qRgb(0,0,0);
    // white
    case 7:
        return qRgb(255,255,255);
    }
}

void DrawingTools::clearCoordinates()
{
    coordinates.clear();
}

void DrawingTools::insertSprayedPixels(int x, int y)
{
    coordinates.insert(std::make_pair(x, y));
    coordinates.insert(std::make_pair(x-1, y-1));
    coordinates.insert(std::make_pair(x-1, y));
    coordinates.insert(std::make_pair(x-1, y));
    coordinates.insert(std::make_pair(x-2, y));
    coordinates.insert(std::make_pair(x+1, y+1));
    coordinates.insert(std::make_pair(x, y+1));
    coordinates.insert(std::make_pair(x-1, y+1));
    coordinates.insert(std::make_pair(x-2, y+1));
    coordinates.insert(std::make_pair(x-3, y+1));
    coordinates.insert(std::make_pair(x, y+2));
    coordinates.insert(std::make_pair(x-1, y+2));
    coordinates.insert(std::make_pair(x-2, y+2));
    coordinates.insert(std::make_pair(x-1, y+3));
}

