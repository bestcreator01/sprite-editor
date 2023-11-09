/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    It contains all necessary implementation needed to form a drawing tool.
*/

#include "drawingtools.h"
#include <QDebug>

DrawingTools::DrawingTools() {}

void DrawingTools::updatePixels(QPoint points)
{
    x = points.x();
    y = points.y();

    qDebug() << "This is from the tools class - x: " << x << ", y: " << y;
}
