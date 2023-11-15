/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    It contains all necessary information needed to form the Pen tool.
*/

#ifndef PEN_H
#define PEN_H

#include <QImage>

///
/// \brief The Pen class - Represents the pen tool for updating pixels from an image.
///
class Pen
{
public:
    ///
    /// \brief Pen - default constructor for the Pen class
    ///
    Pen();

    ///
    /// \brief updatePixels - updates the image by drawing a pixel at (x,y)
    /// \param image - reference to the QImage being updated
    /// \param x - x coordinate of the pixel to be updated
    /// \param y - y coordinate of the pixel to be updated
    /// \param color - color to be applied to the pixel
    ///
    void updatePixels(QImage &image, int x, int y, QColor color);
};

#endif // PEN_H
