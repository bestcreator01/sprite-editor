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

#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

SpriteView::SpriteView(DrawingTools& tools, Preview& preview, PixelCanvasLayers& layers, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteView)
{
    // default setup
    ui->setupUi(this);
    image = QImage(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    image.fill(qRgba(0,0,0,0));
    // Initialize history with blank image
    history.append(image);
    historyPointer = 0;
    ui->listWidget->setIconSize(QSize(50,50));
    addFrameClicked();

    // location and size of a canvas and a preview
    QRect canvasSquare = ui->pixelCanvas->geometry();
    x_offset = canvasSquare.topLeft().x();
    canvasWidth = canvasSquare.topRight().x() - x_offset;
    y_offset = canvasSquare.topLeft().y();
    canvasHeight = canvasWidth;

    previewXOffset = 850;
    previewYOffset = 60;
    previewWidth = 200;
    previewHeight = previewWidth;

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
    ui->colorOrange->setStyleSheet("background-color: rgb(255, 127, 0)");
    ui->colorYellow->setStyleSheet("background-color: rgb(255, 255, 0)");
    ui->colorGreen->setStyleSheet("background-color: rgb(0, 255, 0)");
    ui->colorBlue->setStyleSheet("background-color: rgb(0, 0, 255)");
    ui->colorPurple->setStyleSheet("background-color: rgb(75, 0, 130)");
    ui->colorBlack->setStyleSheet("background-color: rgb(0, 0, 0)");
    ui->colorWhite->setStyleSheet("background-color: rgb(255, 255, 255)");


    // when selecting the painting tools
    connect(ui->penButton, &QPushButton::clicked, this, &SpriteView::mouseToPen);
    connect(ui->eraserButton, &QPushButton::clicked, this, &SpriteView::mouseToEraser);
    connect(ui->sprayButton, &QPushButton::clicked, this, &SpriteView::mouseToSpray);
    connect(ui->penButton, &QPushButton::clicked, this, [=]() {this->currentTool = 0;});
    connect(ui->eraserButton, &QPushButton::clicked, this, [=]() {this->currentTool = 1;});
    connect(ui->sprayButton, &QPushButton::clicked, this, [=]() {this->currentTool = 2;});
    connect(ui->undoButton, &QPushButton::clicked, this, &SpriteView::undoButtonClicked);
    connect(ui->redoButton, &QPushButton::clicked, this, &SpriteView::redoButtonClicked);
    ui->undoButton->setEnabled(false);
    ui->redoButton->setEnabled(false);
    ui->undoButton->setStyleSheet("font-size: 14pt;");
    ui->redoButton->setStyleSheet("font-size: 14pt;");

    // when selecting the colors
    connect(ui->colorRed, &QPushButton::clicked, this, [=]() {this->currentColor = 0;});
    connect(ui->colorOrange, &QPushButton::clicked, this, [=]() {this->currentColor = 1;});
    connect(ui->colorYellow, &QPushButton::clicked, this, [=]() {this->currentColor = 2;});
    connect(ui->colorGreen, &QPushButton::clicked, this, [=]() {this->currentColor = 3;});
    connect(ui->colorBlue, &QPushButton::clicked, this, [=]() {this->currentColor = 4;});
    connect(ui->colorPurple, &QPushButton::clicked, this, [=]() {this->currentColor = 5;});
    connect(ui->colorBlack, &QPushButton::clicked, this, [=]() {this->currentColor = 6;});
    connect(ui->colorWhite, &QPushButton::clicked, this, [=]() {this->currentColor = 7;});

    // Preview logic
    connect(ui->deleteFrame, &QPushButton::clicked, this, &SpriteView::deleteFrameClicked);
    connect(ui->addFrame, &QPushButton::clicked, this, &SpriteView::addFrameClicked);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &SpriteView::selectEdit);
    connect(ui->fpsSlider, &QSlider::valueChanged, this, &SpriteView::onSliderChanged);
    connect(this, &SpriteView::addFrame, &layers, &PixelCanvasLayers::addLayer);
    connect(this, &SpriteView::deleteFrame, &layers, &PixelCanvasLayers::deleteLayer);
    connect(this, &SpriteView::setEditingFrame, &layers, &PixelCanvasLayers::setEditLayer);
    connect(&preview, &Preview::updateEditorWindow, this, &SpriteView::updateEditor);
    connect(&preview, &Preview::updateFrameList, this, &SpriteView::updateFrameList);
    connect(this, &SpriteView::Playback, &preview, &Preview::Playback);
    connect(this, &SpriteView::setPlaybackSpeed, &preview, &Preview::setPlaybackSpeed);
    connect(&layers, &PixelCanvasLayers::updateCanvas, this, [=](QImage frame){image = frame; update();});

    // inserting and removing coordinates for JSON serialization
    connect(&tools, &DrawingTools::updatedVectorCoordinates, this, &SpriteView::insertCoordinates);
    connect(&tools, &DrawingTools::removeVectorCoordinates, this, &SpriteView::removeCoordinates);

    // when drawing on canvas - retrieving the coordinates
    connect(this, &SpriteView::sendInformation, &layers, &PixelCanvasLayers::updatePixel);

}

SpriteView::~SpriteView()
{
    delete ui;
}

void SpriteView::removeCoordinates(QSet<QPair<int, int>> coords)
{
    for(auto coord:coords)
    {
        coordinates.remove(std::make_pair(coord.first, coord.second));
    }
}

void SpriteView::insertCoordinates(QSet<QPair<int, int>> coords)
{
    for(auto coord:coords)
    {
        coordinates.insert(std::make_pair(coord.first, coord.second));
    }
}

void SpriteView::addFrameClicked()
{
    addToFrameList();
    emit addFrame();
}

void SpriteView::selectEdit(QListWidgetItem * item)
{
    emit setEditingFrame(item->data(0).toInt());
    editTarget = item->data(0).toInt();
}

void SpriteView::deleteFrameClicked()
{
    if(frameList.size() == 1)
        return;
    int id = ui->listWidget->currentItem()->data(0).toInt();
    delete frameList[id];
    for(int i = id; i < frameList.size() - 1; i++)
    {
        frameList[i] = frameList[i+1];
        frameList[i]->setData(0, i);
    }
    frameList.pop_back();
    editTarget = frameList.size() - 1;
    emit deleteFrame();
}

void SpriteView::addToFrameList()
{
    QListWidgetItem *item = new QListWidgetItem(QIcon(":/background_pixel_image/bg_spritePixels.png"),0);
    item->setData(0, frameList.size());
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
    frameList.append(item);
    editTarget = frameList.size() - 1;
}

void SpriteView::onSliderChanged(int value)
{
    ui->fpsLabel->setText(QString::number(value) + " FPS");
    emit setPlaybackSpeed(value);
    //emit Playback(value);
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

    for(int i = 0; i < icons.size(); i++)
    {
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

///
/// \brief SpriteView::undoButtonClicked - Undo user action
///
void SpriteView::undoButtonClicked(){
    if(historyPointer <= 1){
        ui->undoButton->setEnabled(false);
    }
    historyPointer--;
    ui->redoButton->setEnabled(true);

    if(historyPointer < 0){
        historyPointer = 0;
    }
    image = history[historyPointer];
    repaint();
}

///
/// \brief SpriteView::redoButtonClicked - Redo user action
///
void SpriteView::redoButtonClicked(){
    historyPointer++;
    ui->undoButton->setEnabled(true);

    if(historyPointer >= history.size() - 1){
        ui->redoButton->setEnabled(false);
    }

    if(historyPointer >= history.size()){
        historyPointer = history.size() - 1;
    }
    image = history[historyPointer];
    repaint();
}

////////////////////////////
/// Mouse and Paint methods
///////////////////////////

void SpriteView::paintEvent(QPaintEvent *)
{
    paintCanvas(image);
    paintPreview(image);
}

void SpriteView::mouseMoveEvent(QMouseEvent *event)
{
    mouseEventHelper(event);
}

void SpriteView::mousePressEvent(QMouseEvent *event)
{
    mouseEventHelper(event);
}

void SpriteView::mouseReleaseEvent(QMouseEvent *event)
{
    mousePosition = event->pos();
    updateEditor(image, editTarget);

    // Get the coordinates of the canvas square
    QRect canvasSquare = ui->pixelCanvas->geometry();

    // check if the mouse position is in the canvasSquare
    if (canvasSquare.contains(mousePosition))
    {
        int gridX = (mousePosition.x() - x_offset)*sizeOfCanvas/canvasWidth;
        int gridY = (mousePosition.y() - y_offset)*sizeOfCanvas/canvasHeight;

        ui->coordinates->setText(QString::number(gridX) + ", " + QString::number(gridY));


        emit sendInformation(gridX, gridY, currentColor, currentTool);
        qDebug("mouse release");
        update();

        while (history.size() > historyPointer+1)
        {
            history.removeAt(historyPointer+1);

            // Append image after the user releases the mouse
            history.append(image);
            historyPointer++;
            ui->undoButton->setEnabled(true);
        }
    }
    else
    {
        ui->coordinates->clear();
    }
}

void SpriteView::mouseToPen()
{    
    mouseToDrawingTools(":/icons/pen.PNG");
}

void SpriteView::mouseToEraser()
{
    mouseToDrawingTools(":/icons/eraser.png");
}

void SpriteView::mouseToSpray()
{    
    mouseToDrawingTools(":/icons/spray.png");
}

void SpriteView::paintCanvas(QImage& image)
{
    paintLayer(image, x_offset, y_offset, canvasWidth, canvasHeight);
}

void SpriteView::paintPreview(QImage& image)
{
    paintLayer(image, previewXOffset, previewYOffset, previewWidth, previewHeight);
}

/////////////////////
/// Helper methods
/////////////////////

void SpriteView::mouseEventHelper(QMouseEvent *event)
{
    mousePosition = event->pos();

    // Get the coordinates of the canvas square
    QRect canvasSquare = ui->pixelCanvas->geometry();

    // check if the mouse position is in the canvasSquare
    if(canvasSquare.contains(mousePosition))
    {
        // coverted coordinates from world size to grid
        int gridX = (mousePosition.x() - x_offset)*sizeOfCanvas/canvasWidth;
        int gridY = (mousePosition.y() - y_offset)*sizeOfCanvas/canvasHeight;

        ui->coordinates->setText(QString::number(gridX) + ", " + QString::number(gridY));
        emit sendInformation(gridX, gridY, currentColor, currentTool);
        update();
    }
    else
    {
        ui->coordinates->clear();
    }
}

void SpriteView::mouseToDrawingTools(QString imagepath)
{
    QIcon toolIcon(imagepath);
    QPixmap pixmap(toolIcon.pixmap(toolIcon.actualSize(QSize(32, 32))));
    QCursor c(pixmap, 0, -1);
    ui->pixelCanvas->setCursor(c);
}

void SpriteView::paintLayer(QImage& image, int x, int y, int width, int height)
{
    QPainter layer(this);
    layer.drawImage(QRect(x, y, width, height), QImage(":/background_pixel_image/bg_spritePixels.png"));
    layer.drawImage(QRect(x, y, width, height), image);
    layer.end();
}

QJsonDocument SpriteView::createJSON()
{
    QJsonObject PixelCanvas;
    PixelCanvas.insert("Height" , sizeOfCanvas);
    PixelCanvas.insert("Width" , sizeOfCanvas);
    QJsonObject pixel;
    QJsonArray pixelArray;
    for(auto c: coordinates)
    {
        pixel.insert("X", c.first);
        pixel.insert("Y", c.second);
        QRgb color = image.pixel(c.first, c.second);

        qDebug() << color;
        pixel.insert("r", qRed(color));
        pixel.insert("g", qGreen(color));
        pixel.insert("b", qBlue(color));
        pixelArray.push_back(pixel);
    }
    PixelCanvas.insert("pixel", pixelArray);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(PixelCanvas);
    qDebug () << jsonDoc.toJson();
    return jsonDoc;
}


void SpriteView::on_saveFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save a File", QDir::homePath(), tr("SSP files (*.ssp)"));

    QFile file(QFileInfo(fileName).absoluteFilePath());

    QJsonDocument jsonDoc = createJSON();
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        stream << jsonDoc.toJson();
    }
    file.close();
}

