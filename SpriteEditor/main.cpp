/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    This class contains default information to open a window.
*/

#include "spriteview.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawingTools t;
    PixelCanvas c;
    SpriteView w(t, c);
    w.show();
    return a.exec();
}
