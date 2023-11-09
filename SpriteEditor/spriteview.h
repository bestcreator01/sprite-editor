/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    It contains all necessary information needed to form the main window class.
*/

#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteView; }
QT_END_NAMESPACE

class SpriteView : public QMainWindow
{
    Q_OBJECT
    int sizeOfCanvas = 32;

public:
    SpriteView(QWidget *parent = nullptr);
    ~SpriteView();

private:
    Ui::SpriteView *ui;
    void paintEvent(QPaintEvent *);
};
#endif // SPRITEVIEW_H
