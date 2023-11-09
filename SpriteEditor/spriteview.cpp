/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    This source file contains all necessary implementation for a main window.
*/

#include "spriteview.h"
#include "ui_spriteview.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QPixmap>

SpriteView::SpriteView( QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteView)
{
    ui->setupUi(this);

    QIcon penIcon(":/icons/pen.PNG");
    QIcon eraserIcon(":/icons/eraser.png");
    QIcon sprayIcon(":/icons/spray.png");

    ui->penButton->setIcon(penIcon);
    ui->eraserButton->setIcon(eraserIcon);
    ui->sprayButton->setIcon(sprayIcon);
}

///
/// \brief SpriteView::paintEvent Displays the background image for the Sprite Editor and draws transparent
/// pixels on the background image.
///
void SpriteView::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QImage image(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    image.fill(qRgba(0,0,0,0));
    painter.drawImage(QRect(180, 10, 700, 700),QImage(":/background_pixel_image/bg_spritePixels.png"));
    painter.drawImage(QRect(180, 10, 700, 700), image);
}

SpriteView::~SpriteView()
{
    delete ui;
}

