/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    It contains all necessary information needed to form a pixel canvas class.
*/

#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include <QObject>
#include "pixel.h"

class PixelCanvas : public QObject
{
    Q_OBJECT
    Pixel pixel[32][32];
    int sizeOfCanvas = 32;

public:
    explicit PixelCanvas(QObject *parent = nullptr);

signals:

};

#endif // PIXELCANVAS_H
