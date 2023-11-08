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

void SpriteView::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawImage(QRect(200, 20, 640, 640),QImage(":/background_pixel_image/bg_spritePixels.png"));
    QPen pen(Qt::black);
    int offsetX = 180;
    int offsetY = 0;

    for(int i = 0; i < sizeOfCanvas; i++)
    {
        for(int j = 0; j < sizeOfCanvas; j++)
        {
            painter.setPen(pen);
            painter.drawRect(pixelSize + offsetX, pixelSize + offsetY, pixelSize, pixelSize);
            offsetX += pixelSize;
        }
        offsetY += pixelSize;
        offsetX = 180;
    }
}

SpriteView::~SpriteView()
{
    delete ui;
}

