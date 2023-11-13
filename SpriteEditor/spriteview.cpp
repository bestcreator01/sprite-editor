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

SpriteView::SpriteView(DrawingTools& tools, Preview& preview, PixelCanvasLayers& layers, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteView)

{
    ui->setupUi(this);
    image = QImage(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    image.fill(qRgba(0,0,0,0));
    ui->listWidget->setIconSize(QSize(50,50));
    addItemToFrameList();

    // allowing mouse moving events
    ui->pixelCanvas->setMouseTracking(true);

    // setting up drawing tool icons
    QIcon penIcon(":/icons/pen.PNG");
    QIcon eraserIcon(":/icons/eraser.png");
    QIcon sprayIcon(":/icons/spray.png");

    QIcon saveIcon(":/icons/save.png");
    QIcon newFileIcon(":/icons/newFile.png");
    QIcon loadIcon(":/icons/load.png");

    ui->penButton->setIcon(penIcon);
    ui->eraserButton->setIcon(eraserIcon);
    ui->sprayButton->setIcon(sprayIcon);

    ui->saveFile->setIcon(saveIcon);
    ui->newFile->setIcon(newFileIcon);
    ui->loadFile->setIcon(loadIcon);

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

    // when selecting the colors
    connect(ui->colorRed, &QPushButton::clicked, this, [=]() {this->currentColor = 0;});
    connect(ui->colorGreen, &QPushButton::clicked, this, [=]() {this->currentColor = 1;});
    connect(ui->colorBlue, &QPushButton::clicked, this, [=]() {this->currentColor = 2;});
    connect(ui->colorBlack, &QPushButton::clicked, this, [=]() {this->currentColor = 3;});

    // Preview logic
    connect(ui->deleteFrame, &QPushButton::clicked, this, &SpriteView::deleteFrameClicked);
    connect(ui->addFrame, &QPushButton::clicked, this, &SpriteView::addFrameClicked);
    connect(ui->listWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem * item){ emit setEditingFrame(item->data(0).toInt());});
    connect(ui->fpsSlider, &QSlider::valueChanged, this, &SpriteView::onSliderChanged);
    connect(&preview, &Preview::updateEditorWindow, this, &SpriteView::updateEditor);
    connect(&preview, &Preview::updateFrameList, this, &SpriteView::updateFrameList);
//    connect(this, &SpriteView::startPlayback, &preview, &Preview::startPlayback);
    connect(this, &SpriteView::setPlaybackSpeed, &preview, &Preview::setPlaybackSpeed);
    connect(this, &SpriteView::addFrame, &layers, &PixelCanvasLayers::addLayer);
    connect(this, &SpriteView::deleteFrame, &layers, &PixelCanvasLayers::deleteLayer);
    connect(this, &SpriteView::setEditingFrame, &layers, &PixelCanvasLayers::setEditLayer);

    // when drawing on canvas - retrieving the coordinates
    connect(this, &SpriteView::sendCoordinates, &tools, &DrawingTools::updatePixels);

    QRect canvasSquare = ui->pixelCanvas->geometry();
    x_offset = canvasSquare.topLeft().x();
    canvasWidth = canvasSquare.topRight().x() - x_offset;
    y_offset = canvasSquare.topLeft().y();
    canvasHeight = canvasWidth;
}

void SpriteView::addFrameClicked()
{
    addItemToFrameList();
    emit addFrame();
}

void SpriteView::deleteFrameClicked()
{
    if(frameList.size()==1)
        return;
    int id = ui->listWidget->currentItem()->data(0).toInt();
    delete frameList[id];
    for(int i = id; i < frameList.size() - 1; i++)
    {
        frameList[i] = frameList[i+1];
        frameList[i]->setData(0, i);
    }
    frameList.pop_back();
    emit deleteFrame();
}

void SpriteView::addItemToFrameList()
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setData(0, frameList.size());
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
    frameList.append(item);
}

void SpriteView::onSliderChanged(int value)
{
    ui->fpsLabel->setText(QString::number(value) + " FPS");
    emit setPlaybackSpeed(value);
//    emit startPlayback(value);
}

void SpriteView::updateEditor(const QImage &frameImage, int editingTarget)
{
    image = frameImage;
    QPixmap p = QPixmap::fromImage(frameImage.scaled(QSize(50, 50), Qt::KeepAspectRatio));
    frameList[editingTarget]->setIcon(QIcon(p));
    update();
}

void SpriteView::updateFrameList(QList<QImage> icons)
{
    ui->listWidget->clear();
    frameList = QList<QListWidgetItem*>();

    for(int i = 0; i < icons.size();i++){
        QListWidgetItem *item = new QListWidgetItem;
        item->setData(0, frameList.size());
        ui->listWidget->addItem(item);
        ui->listWidget->setCurrentItem(item);
        frameList.append(item);

        image = icons[i];
        QPixmap p = QPixmap::fromImage(image.scaled(QSize(50, 50), Qt::KeepAspectRatio));
        frameList[i]->setIcon(QIcon(p));
    }
}

void SpriteView::paintEvent(QPaintEvent *)
{
    paintCanvas(image);
    paintPreview(image);

    if (!mousePosition.isNull())
    {
        updatePreview(image);
        paintCanvas(image);
        paintPreview(image);
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
        ui->coordinates->setText(QString::number(convertWorldToGrid_X(mousePosition.x()))
                                 + ", " + QString::number(convertWorldToGrid_Y(mousePosition.y())));

        if (currentTool < 3){
            emit sendCoordinates(image, convertWorldToGrid_X(mousePosition.x()),
                                 convertWorldToGrid_Y(mousePosition.y()), currentColor, currentTool);
            update();
        }
    }
    else
    {
        ui->coordinates->clear();
    }
}

void SpriteView::mousePressEvent(QMouseEvent *event)
{
    mousePosition = event->pos();

    // Get the coordinates of the canvas square
    QRect canvasSquare = ui->pixelCanvas->geometry();

    // check if the mouse position is in the canvasSquare
    if(canvasSquare.contains(mousePosition))
    {
        ui->coordinates->setText(QString::number(convertWorldToGrid_X(mousePosition.x()))
                                 + ", " + QString::number(convertWorldToGrid_Y(mousePosition.y())));

        if (currentTool < 3){
            emit sendCoordinates(image, convertWorldToGrid_X(mousePosition.x()),
                                 convertWorldToGrid_Y(mousePosition.y()), currentColor, currentTool);
            update();
        }
    }
    else
    {
        ui->coordinates->clear();
    }
}

int SpriteView::convertWorldToGrid_X(int x){
    return (x - x_offset)*sizeOfCanvas/canvasWidth;
}

int SpriteView::convertWorldToGrid_Y(int y){
    return (y - y_offset)*sizeOfCanvas/canvasHeight;
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
    canvas.drawImage(QRect(x_offset, y_offset, canvasWidth, canvasHeight),QImage(":/background_pixel_image/bg_spritePixels.png"));
    canvas.drawImage(QRect(x_offset, y_offset, canvasWidth, canvasHeight), image);
    canvas.end();
}

void SpriteView::paintPreview(QImage& image)
{
    QPainter preview(this);

    preview.drawImage(QRect(850, 60, 200, 200),QImage(":/background_pixel_image/bg_spritePixels.png"));
    preview.drawImage(QRect(850, 60, 200, 200), image);
    preview.end();
}

void SpriteView::updatePreview(QImage& image)
{
    QPainter preview(this);
    preview.drawImage(QRect(850, 60, 200, 200), image);
    preview.end();
}

SpriteView::~SpriteView()
{
    delete ui;
}
