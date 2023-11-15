/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    It contains all necessary information needed to form a drawing tool.
*/

#ifndef DRAWINGTOOLS_H
#define DRAWINGTOOLS_H

#include "pen.h"
#include "eraser.h"
#include "spray.h"
#include "qrgb.h"
#include <QImage>
#include <QObject>
#include <QColor>
#include <QPoint>
#include <QSet>

class DrawingTools : public QObject {
public:
    explicit DrawingTools(QObject *parent = nullptr);

    ///
    /// \brief x, y - the x and y coordinates of a pixel
    ///
    int x, y;

public slots:
    ///
    /// \brief updatePixels - updates (x,y) pixel with the color and the tool
    /// \param image - reference to the QImage being updated
    /// \param x - x coordinate of the pixel to be updated
    /// \param y - y coordinate of the pixel to be updated
    /// \param color - color to be applied to the pixel
    /// \param tool - tool identifier to determine the drawing tool used
    ///
    virtual void updatePixels(QImage &image, int x, int y, int color, int tool);

    ///
    /// \brief clearCoordinates - clears the stored coordinates
    ///
    void clearCoordinates();
private:
    Q_OBJECT

    ///
    /// \brief pen - instance of the Pen class for drawing with a pen tool
    ///
    Pen pen;

    ///
    /// \brief eraser - instance of the Eraser class for erasing pixels
    ///
    Eraser eraser;

    ///
    /// \brief spray - instance of the Spray class for drawing with a spray tool
    ///
    Spray spray;

    ///
    /// \brief getQRgbColor - a QRgb color from a color parameter
    /// \param color - integer representing the color
    /// \return Qcolor - color in QColor format
    ///
    QColor getQRgbColor(int color);

    ///
    /// \brief coordinates - set to store the drawn coordinates
    ///
    QSet<QPair<int, int>> coordinates;

signals:
    ///
    /// \brief updatedVectorCoordinates
    /// \param coordinates
    ///
    void updatedVectorCoordinates(QSet<QPair<int, int>> coordinates);

    ///
    /// \brief removeVectorCoordinates
    /// \param x
    /// \param y
    ///
    void removeVectorCoordinates(int x, int y);
};

#endif // DRAWINGTOOLS_H
