/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    It contains all necessary information needed to form a pixel class.
*/

#ifndef PIXEL_H
#define PIXEL_H

#include <QObject>

class Pixel : public QObject
{
//    Q_OBJECT
    int r;
    int g;
    int b;
public:
    explicit Pixel(QObject *parent = nullptr);



signals:

};

#endif // PIXEL_H
