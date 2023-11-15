/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    It contains all necessary information needed to form the Eraser tool.
*/

#ifndef ERASER_H
#define ERASER_H

#include <QImage>

///
/// \brief The Eraser class - Represents the eraser tool for erasing pixels from an image.
///
class Eraser
{
public:
    ///
    /// \brief Eraser - default constructor for the Eraser class.
    ///
    Eraser();

    ///
    /// \brief updatePixels - - updates the image by erasing the pixel at (x,y)
    /// \param image - reference to the QImage being updated
    /// \param x - x coordinate of the pixel to be erased
    /// \param y - y coordinate of the pixel to be erased
    ///
    void updatePixels(QImage &image, int x, int y);
};

#endif // ERASER_H
