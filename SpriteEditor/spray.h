/**
 * Author:     Crazy Broke Asians
 * Date:       Nov-16-2023
 * Course:     CS 3505, University of Utah
 * Assignment: A8: Sprite Editor
 * File Contents
 *      It contains all necessary information needed to form the Spray tool.
*/
#ifndef SPRAY_H
#define SPRAY_H

#include <QImage>

///
/// \brief The Spray class
///
class Spray
{
public:
    ///
    /// \brief Spray - default constructor for the Spray class
    ///
    Spray();

    ///
    /// \brief updatePixels - updates the image by drawing a pixel at (x,y)
    /// \param image - reference to the QImage being updated
    /// \param x - x coordinate of the pixel to be updated
    /// \param y - y coordinate of the pixel to be updated
    /// \param color - color to be applied to the pixel
    ///
    void updatePixels(QImage &image, int x, int y, QColor color);
};

#endif // SPRAY_H
