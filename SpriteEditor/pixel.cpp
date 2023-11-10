/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    This source file contains all necessary implementation for a pixel object.
*/

#include "pixel.h"

Pixel::Pixel(QObject *parent)
    : QObject{parent}, r(0), g(0), b(0)
{

}

