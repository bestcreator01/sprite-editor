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

#include "eraser.h"
#include "pen.h"
#include "spray.h"
#include "qrgb.h"
#include <QObject>
#include <QPoint>
#include <QSet>

class DrawingTools : public QObject {
public:
    explicit DrawingTools(QObject *parent = nullptr);
    int x, y;

public slots:
    virtual void updatePixels(QImage &Image, int x, int y, int color, int tool);

private:
    Q_OBJECT
    Pen pen;
    Eraser eraser;
    Spray spray;
    QRgb getQRgbColor(int color);
    QSet<QPair<int, int>> coordinates;
    void insertSprayedPixels(int x, int y);
signals:
    void updatedVectorCoordinates(QSet<QPair<int, int>> coordinates);
    void removeVectorCoordinates(int x, int y);
};

#endif // DRAWINGTOOLS_H
