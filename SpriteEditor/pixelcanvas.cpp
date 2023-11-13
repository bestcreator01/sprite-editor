/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    This source file contains all necessary implementation for a pixel canvas object.
*/

#include "pixelcanvas.h"

//PixelCanvas::PixelCanvas(QObject *parent)
//    : QObject{parent}
//{
//    image = QImage(":/background_pixel_image/bg_spritePixels.png");
//}

PixelCanvas::PixelCanvas()
{
    image = QImage(":/background_pixel_image/bg_spritePixels.png");
}

const QImage& PixelCanvas::getImage(){
    return image;
}


