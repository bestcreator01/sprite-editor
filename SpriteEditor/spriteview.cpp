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
}

void SpriteView::paintEvent(QPaintEvent *) {
    QPixmap bgPicture;
    bgPicture.load(":/background_pixel_image/bg_spritePixels.png");
    QPainter painter(&bgPicture);
    QPen pen(Qt::black);
    int offsetX = offsetSize;
    int offsetY = 65;

    for(int i = 0; i < sizeOfCanvas; i++)
    {
        for(int j = 0; j < sizeOfCanvas; j++)
        {
            painter.setPen(pen);
            painter.drawRect(pixelSize + offsetX, pixelSize + offsetY, pixelSize, pixelSize);
            offsetX += pixelSize;
        }
        offsetY += pixelSize;
        offsetX = offsetSize;
    }
    ui->label->setPixmap(bgPicture);
}

SpriteView::~SpriteView()
{
    delete ui;
}

