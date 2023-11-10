/*
Author:     Crazy Broke Asians
Date:       Nov-16-2023
Course:     CS 3505, University of Utah
Assignment: A8: Sprite Editor

File Contents
    This source file contains all necessary implementation for a main window.
*/

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QDebug>
#include "spriteview.h"
#include "ui_spriteview.h"

SpriteView::SpriteView(DrawingTools& tools, PixelCanvasLayers& layers, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteView)
{
    ui->setupUi(this);
    image = QImage(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);

    // allowing mouse moving events
    ui->pixelCanvas->setMouseTracking(true);

    // setting up drawing tool icons
    QIcon penIcon(":/icons/pen.PNG");
    QIcon eraserIcon(":/icons/eraser.png");
    QIcon sprayIcon(":/icons/spray.png");

    ui->penButton->setIcon(penIcon);
    ui->eraserButton->setIcon(eraserIcon);
    ui->sprayButton->setIcon(sprayIcon);

    // setting up color buttons
    ui->colorRed->setStyleSheet("background-color: rgb(255, 0, 0)");
    ui->colorGreen->setStyleSheet("background-color: rgb(0, 255, 0)");
    ui->colorBlue->setStyleSheet("background-color: rgb(0, 0, 255)");
    ui->colorBlack->setStyleSheet("background-color: rgb(0, 0, 0)");

    // when selecting the painting tools
    connect(ui->penButton, &QPushButton::clicked, this, &SpriteView::mouseToPen);
    connect(ui->eraserButton, &QPushButton::clicked, this, &SpriteView::mouseToEraser);
    connect(ui->sprayButton, &QPushButton::clicked, this, &SpriteView::mouseToSpray);
    connect(ui->penButton, &QPushButton::clicked, this, [=]() {this->currentTool = 0;});
    connect(ui->eraserButton, &QPushButton::clicked, this, [=]() {this->currentTool = 1;});
    connect(ui->sprayButton, &QPushButton::clicked, this, [=]() {this->currentTool = 2;});

    // when drawing on canvas - retrieving the coordinates
    connect(this, &SpriteView::sendCoordinates, &tools, &DrawingTools::updatePixels);

    // when you finish your drawing/erasing/spraying - update the changes
    connect(this, &SpriteView::sendChangesOnCanvas, &layers, &PixelCanvasLayers::updateChangesOnCanvas);
}

void SpriteView::paintEvent(QPaintEvent *)
{
    paintCanvas(image);
    paintPreview(image);

    if (!mousePosition.isNull())
    {
        updateCanvas(image);
        updatePreview(image);
    }
}

void SpriteView::mouseMoveEvent(QMouseEvent *event)
{
    mousePosition = event->pos();

    // Get the coordinates of the canvas square
    QRect canvasSquare = ui->pixelCanvas->geometry();

    // check if the mouse position is in the canvasSquare
    if(canvasSquare.contains(mousePosition))
    {
        ui->coordinates->setText(QString::number(mousePosition.x()) + ", " + QString::number(mousePosition.y()));
        emit sendCoordinates(mousePosition);
        update();
    }
    else
    {
        ui->coordinates->clear();
    }
}

void SpriteView::mouseReleaseEvent(QMouseEvent *)
{
    updatePreview(image);
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

void SpriteView::paintCanvas(QImage& image)
{
    QPainter canvas(this);
    image.fill(qRgba(0,0,0,0));
    canvas.drawImage(QRect(180, 60, 600, 600),QImage(":/background_pixel_image/bg_spritePixels.png"));
    canvas.drawImage(QRect(180, 60, 600, 600), image);
    canvas.end();
}

void SpriteView::paintPreview(QImage& image)
{
    QPainter preview(this);
    preview.drawImage(QRect(850, 60, 200, 200),QImage(":/background_pixel_image/bg_spritePixels.png"));
    preview.drawImage(QRect(850, 60, 200, 200), image);
    preview.end();
}

void SpriteView::updateCanvas(QImage& image)
{
    // pen
    if (currentTool < 3)
    {
        int pixelX = (mousePosition.x() - 180) / 20;
        int pixelY = (mousePosition.y() - 60) / 20;

        if (currentTool == 0)
        {
            paintPen(image);
        }
        // eraser
        else if (currentTool == 1)
        {
            paintEraser(image);
        }
        // spray
        else if (currentTool == 2)
        {
            paintSpray(image, pixelX, pixelY);
        }
        updatePreview(image);
    }
    else
    {
        // do nothing
    }
}

void SpriteView::updatePreview(QImage& image)
{
//    qDebug() << "is it here?";
//    QPainter updatedPreview(this);
//    updatedPreview.drawImage(QRect(850, 60, 200, 200), image);
//    updatedPreview.end();
//    qDebug() << "yes it is";
}

void SpriteView::paintPen(QImage &image)
{

}

void SpriteView::paintEraser(QImage &image)
{

}

void SpriteView::paintSpray(QImage &image, int x, int y)
{
    QPainter canvas(this);
    // updates QImage
    image.setPixel(x, y, qRgb(255,0,0));
    canvas.drawImage(QRect(180, 60, 600, 600), image);
    canvas.end();

//    // updates QPainter
//    QPainter spray(&image);
//    spray.setBrush(Qt::red);
//    spray.drawEllipse(mousePosition.x(), mousePosition.y(), 200, 200);
//    spray.end();
}

SpriteView::~SpriteView()
{
    delete ui;
}
