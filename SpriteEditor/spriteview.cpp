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

SpriteView::SpriteView(DrawingTools& tools, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteView)
{
    ui->setupUi(this);

    // allowing mouse moving events
    ui->pixelCanvas->setMouseTracking(true);

    // setting up drawing tool icons
    QIcon penIcon(":/icons/pen.PNG");
    QIcon eraserIcon(":/icons/eraser.png");
    QIcon sprayIcon(":/icons/spray.png");

    ui->penButton->setIcon(penIcon);
    ui->eraserButton->setIcon(eraserIcon);
    ui->sprayButton->setIcon(sprayIcon);

    // when selecting the painting tools
    connect(ui->penButton, &QPushButton::clicked, this, &SpriteView::mouseToPen);
    connect(ui->eraserButton, &QPushButton::clicked, this, &SpriteView::mouseToEraser);
    connect(ui->sprayButton, &QPushButton::clicked, this, &SpriteView::mouseToSpray);


    // when drawing on canvas - retrieving the coordinates
    connect(this, &SpriteView::sendCoordinates, &tools, &DrawingTools::updatePixels);
}

void SpriteView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QImage image(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    image.fill(qRgba(0,0,0,0));
    painter.drawImage(QRect(180, 10, 700, 700),QImage(":/background_pixel_image/bg_spritePixels.png"));
    painter.drawImage(QRect(180, 10, 700, 700), image);
}

void SpriteView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint mousePosition = event->pos();
    // Get the coordinates of the canvas square
    QRect canvasSquare = ui->pixelCanvas->geometry();
    // check if the mouse position is in the canvasSquare
    if(canvasSquare.contains(mousePosition))
    {
        ui->coordinates->setText(QString::number(mousePosition.x()) + ", " + QString::number(mousePosition.y()));
        emit sendCoordinates(event->pos());
    }
    else{
        ui->coordinates->clear();
    }
}

void SpriteView::mouseToPen()
{
    QIcon penIcon(":/icons/pen.PNG");
    QPixmap pixmap(penIcon.pixmap(penIcon.actualSize(QSize(32, 32))));
    QCursor c(pixmap, 0, -1);
    ui->pixelCanvas->setCursor(c);
}

void SpriteView::mouseToEraser()
{
    QIcon eraserIcon(":/icons/eraser.png");
    QPixmap pixmap(eraserIcon.pixmap(eraserIcon.actualSize(QSize(32, 32))));
    QCursor c(pixmap, 0, -1);
    ui->pixelCanvas->setCursor(c);
}

void SpriteView::mouseToSpray()
{
    QIcon sprayIcon(":/icons/spray.png");
    QPixmap pixmap(sprayIcon.pixmap(sprayIcon.actualSize(QSize(32, 32))));
    QCursor c(pixmap, 0, -1);
    ui->pixelCanvas->setCursor(c);
}


SpriteView::~SpriteView()
{
    delete ui;
}

