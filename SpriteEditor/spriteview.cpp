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

SpriteView::SpriteView(DrawingTools& tools, PixelCanvas& canvas, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteView)
{
    // default setup
    ui->setupUi(this);
    image = QImage(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    previewImage = QImage(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    image.fill(qRgba(0,0,0,0));
    previewImage.fill(qRgba(0,0,0,0));

    // initialize history with blank image
    resetUndoHistory();
    ui->listWidget->setIconSize(QSize(50,50));
    addToFrameList();

    // location and size of a canvas and a preview
    QRect canvasSquare = ui->pixelCanvas->geometry();
    canvasXOffset = canvasSquare.topLeft().x();
    canvasYOffset = canvasSquare.topLeft().y();
    canvasWidth = canvasSquare.topRight().x() - canvasXOffset;
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

    QIcon undoIcon(":/icons/undo.png");
    QIcon redoIcon(":/icons/redo.png");

    ui->penButton->setIcon(penIcon);
    ui->eraserButton->setIcon(eraserIcon);
    ui->sprayButton->setIcon(sprayIcon);

    ui->saveFile->setIcon(saveIcon);
    ui->newFile->setIcon(newFileIcon);
    ui->loadFile->setIcon(loadIcon);

    ui->undoButton->setIcon(undoIcon);
    ui->redoButton->setIcon(redoIcon);

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
    connect(this, &SpriteView::addFrame, &canvas, &PixelCanvas::addLayer);
    connect(this, &SpriteView::deleteFrame, &canvas, &PixelCanvas::deleteLayer);
    connect(this, &SpriteView::setEditingFrame, &canvas, &PixelCanvas::setEditLayer);
    connect(this, &SpriteView::setPlaybackSpeed, &canvas, &PixelCanvas::setSpeed);
    connect(this, &SpriteView::playback, &canvas, &PixelCanvas::playback);
    connect(&canvas, &PixelCanvas::updateCanvas, this, [=](QImage frame, int speed){image = frame; if (!speed) { previewImage = frame; } update();});
    connect(&canvas, &PixelCanvas::sendPlayback, this, [=](QImage frame){previewImage = frame; update();});

    // Undo Redo
    connect(this, &SpriteView::redo, &canvas, &PixelCanvas::redo);
    connect(this, &SpriteView::undo, &canvas, &PixelCanvas::undo);
    connect(this, &SpriteView::resetUndoRedo, &canvas, &PixelCanvas::resetUndoRedo);
    connect(this, &SpriteView::clearUndoBuffer, &canvas, &PixelCanvas::clearUndoBuffer);


    // JSON serialization and deserialization
    connect(this, &SpriteView::getJSON, &canvas, &PixelCanvas::createJSON);
    connect(&canvas, &PixelCanvas::populatedJSON, this, [=](QJsonDocument doc){jsonDoc=doc;});
    connect(this, &SpriteView::readJson, &canvas, &PixelCanvas::loadJson);
    connect(&canvas, &PixelCanvas::updateFPS, this, &SpriteView::getSliderValue);
    connect(&canvas, &PixelCanvas::sendLayerIndex, this, &SpriteView::setDefaultFrame);
    connect(&canvas, &PixelCanvas::sendQIcons, this, &SpriteView::updateFrameList);
    connect(&canvas, &PixelCanvas::allLayers, this, &SpriteView::populateAllLayers);
    connect(this, &SpriteView::getLayerInfo, &canvas, &PixelCanvas::getLayers);

    // when drawing on canvas - retrieving the coordinates
    connect(this, &SpriteView::sendInformation, &canvas, &PixelCanvas::updatePixel);
    connect(&canvas, &PixelCanvas::updatePixelsByTools, &tools, &DrawingTools::updatePixels);
    //connect(this,  &SpriteView::clearPixels, &tools, &DrawingTools::clearCoordinates);
    connect(this, &SpriteView::clearImage, &canvas, &PixelCanvas::clearImage);
}

SpriteView::~SpriteView()
{
    delete ui;
}

////////////////////////////////////////
/// JSON Serialization & Deserialization
////////////////////////////////////////


void SpriteView::saveFile()
{
    emit getLayerInfo();

    if (savedFile.isEmpty())
    {
        QString fileName = QFileDialog::getSaveFileName(
            this, "Save a File", QDir::homePath(), tr("SSP files (*.ssp)"));
        if(fileName == "")
        {
            return;
        }
        savedFile = QFileInfo(fileName).absoluteFilePath();
    }

    QFile file(savedFile);
    emit getJSON();
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream stream(&file);
        stream << jsonDoc.toJson();
    }
    file.close();

    isModified = false;
    isSaved = true;
    resetUndoHistory();
}

void SpriteView::clearCanvas()
{
    if (isModified)
    {
        QMessageBox msgWarning;

        msgWarning.setText("WARNING!\n\nThis file has been modified. Do you "
                           "want to save your changes?");
        msgWarning.setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
                                      QMessageBox::Cancel);

        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Unsaved Changes");
        int response = msgWarning.exec();
        switch (response)
        {
        case QMessageBox::Save:
            saveFile();
            break;
        case QMessageBox::Discard:
            clearAll();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
    if(isSaved)
    {
        clearAll();
    }
}

void SpriteView::populateAllLayers(QList<QImage*> allLayers)
{
    layers.clear();
    for(auto layer:allLayers)
    {
        layers.append(layer);
    }
    layerCount = allLayers.count();
}

void SpriteView::clearAll()
{
    image.fill(qRgba(0, 0, 0, 0));
    previewImage.fill(qRgba(0, 0, 0, 0));

    //coordinates.clear();
    emit clearPixels();
    emit clearImage();

    clearFrameIcons();
    frameList.clear();
    ui->listWidget->clear();
    resetUndoHistory();
    ui->fpsSlider->setValue(0);

    addToFrameList();
    update();

    savedFile = "";
    isModified = false;
}

void SpriteView::askToSave()
{
    QMessageBox warningMessage;

    warningMessage.setText("WARNING!\n\nThis file has been modified. Do you "
                       "want to save your changes?");
    warningMessage.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);

    warningMessage.setIcon(QMessageBox::Warning);
    warningMessage.setWindowTitle("Unsaved Changes");
    int response = warningMessage.exec();
    switch (response)
    {
    case QMessageBox::Save:
        saveFile();
        break;
    case QMessageBox::Cancel:
        clearAll();
        break;
    default:
        break;
    }
}

void SpriteView::loadFile()
{
    if (isModified)
    {
        askToSave();
    }
    QString fileName = QFileDialog::getOpenFileName(this, "Open a File", QDir::homePath(), tr("SSP files (*.ssp)"));
    savedFile = QFileInfo(fileName).absoluteFilePath();

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            QString jsonString = stream.readAll();
            file.close();

            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

            if (!jsonDoc.isNull())
            {
                emit readJson(jsonDoc);
                isSaved = true;
            }
            else
            {
                warnUser();
                savedFile = "";
            }
        }
        else
        {
            warnUser();
            savedFile = "";
        }
    }
    resetUndoHistory();
}

void SpriteView::warnUser()
{
    QMessageBox warningMessage;
    warningMessage.setText("DISCLAIMER!\n\nFailed to open file");
    warningMessage.setStandardButtons(QMessageBox::Ok);

    warningMessage.setIcon(QMessageBox::Warning);
    warningMessage.setWindowTitle("Error!");
    warningMessage.exec();
}

void SpriteView::on_newFile_clicked()
{
    clearCanvas();
}

void SpriteView::on_saveFile_clicked()
{
    saveFile();
}

void SpriteView::on_loadFile_clicked()
{
    loadFile();
}


////////////////
/// PixelCanvas
////////////////

void SpriteView::addToFrameList()
{
    QListWidgetItem *item = new QListWidgetItem(QIcon(":/background_pixel_image/bg_spritePixels.png"),0);
    item->setData(0, frameList.size());
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
    frameList.append(item);
    currentLayer = frameList.size() - 1;
}

void SpriteView::deleteFrameClicked()
{
    if(frameList.size() == 1)
    {
        return;
    }

    // get the frame id
    int id = ui->listWidget->currentItem()->data(0).toInt();

    // delete the frame
    delete frameList[id];
    for(int i = id; i < frameList.size() - 1; i++)
    {
        frameList[i] = frameList[i+1];
        frameList[i]->setData(0, i);
    }
    frameList.pop_back();

    // update the current layer

    id == frameList.size() ? currentLayer = frameList.size() - 1 : currentLayer = id;

    emit deleteFrame();
    resetUndoHistory();
}

void SpriteView::addFrameClicked()
{
    qDebug() << "Add Frame";
    addToFrameList();
    emit addFrame();
    resetUndoHistory();
}

void SpriteView::getSliderValue(int value)
{
    ui->fpsSlider->setSliderPosition(value);
}

void SpriteView::onSliderChanged(int value)
{
    ui->fpsLabel->setText(QString::number(value) + " FPS");
    if(value)
    {
        ui->addFrame->setEnabled(false);
        ui->deleteFrame->setEnabled(false);
    } else
    {
        ui->addFrame->setEnabled(true);
        ui->deleteFrame->setEnabled(true);
    }

    ui->previewLabel->clear();

    emit setPlaybackSpeed(value);
    emit playback(value);
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

        QPixmap pixmap = QPixmap::fromImage(QImage(":/background_pixel_image/bg_spritePixels.png").scaled(QSize(50, 50), Qt::KeepAspectRatio));
        QPainter painter(&pixmap);
        painter.drawPixmap(0, 0, QPixmap::fromImage(icons[i].scaled(QSize(50, 50), Qt::KeepAspectRatio)));
        painter.end();

        frameList[i]->setIcon(QIcon(pixmap));
    }
}

void SpriteView::clearFrameIcons()
{
    for (int i = 0; i < frameList.size(); i++)
    {
        QPixmap p = QPixmap::fromImage(image.scaled(QSize(50, 50), Qt::KeepAspectRatio));
        frameList[i]->setIcon(QIcon(p));
        //frameList[i]->setIcon(QIcon(":/background_pixel_image/bg_spritePixels.png"));
    }

}

void SpriteView::setDefaultFrame(int index)
{
    currentLayer = index;
    emit setEditingFrame(currentLayer);
}

void SpriteView::selectEdit(QListWidgetItem *item)
{
    currentLayer = item->data(0).toInt();
    emit setEditingFrame(currentLayer);
<<<<<<< HEAD
    resetUndoHistory();

    qDebug() << "Is it reaching here?";
    qDebug() << currentLayer << "Ha!";
=======
>>>>>>> 7ca12540f449485bf96a4b1c131dd7314bf43d12
}

void SpriteView::updateEditor(const QImage &frameImage, int editingTarget)
{
    QPixmap pixmap = QPixmap::fromImage(QImage(":/background_pixel_image/bg_spritePixels.png").scaled(QSize(50, 50), Qt::KeepAspectRatio));
    QPainter painter(&pixmap);
    painter.drawPixmap(0, 0, QPixmap::fromImage(frameImage.scaled(QSize(50, 50), Qt::KeepAspectRatio)));
    painter.end();

    frameList[editingTarget]->setIcon(QIcon(pixmap));
    update();
}

////////////////
/// Undo & Redo
////////////////

///
/// \brief SpriteView::undoButtonClicked - Undo user action
///

void SpriteView::undoButtonClicked(){
    bool enable = true;
    emit undo(enable, image);
    previewImage = image;

    ui->redoButton->setEnabled(true);
    if (!enable)
        ui->undoButton->setEnabled(false);
    updateEditor(image,currentLayer);
    update();
}

///
/// \brief SpriteView::redoButtonClicked - Redo user action
///
void SpriteView::redoButtonClicked(){
    bool enable = true;
    emit redo(enable, image);
    previewImage = image;

    ui->undoButton->setEnabled(true);
    if (!enable)
        ui->redoButton->setEnabled(false);
    updateEditor(image, currentLayer);
    repaint();
}

///
/// \brief SpriteView::resetUndoHistory
///
void SpriteView::resetUndoHistory() {
    emit resetUndoRedo(image);
    ui->undoButton->setEnabled(false);
    ui->redoButton->setEnabled(false);
}
///////////////////////////
/// Mouse and Paint methods
///////////////////////////

void SpriteView::paintEvent(QPaintEvent *)
{
    paintCanvas(image);
    paintPreview(previewImage);
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
    updateEditor(image, currentLayer);

    // Get the coordinates of the canvas square
    QRect canvasSquare = ui->pixelCanvas->geometry();

    // check if the mouse position is in the canvasSquare
    if (canvasSquare.contains(mousePosition))
    {
        int gridX = (mousePosition.x() - canvasXOffset)*sizeOfCanvas/canvasWidth;
        int gridY = (mousePosition.y() - canvasYOffset)*sizeOfCanvas/canvasHeight;

        ui->coordinates->setText(QString::number(gridX) + ", " + QString::number(gridY));

        isModified = true;
        isSaved = false;
        emit sendInformation(gridX, gridY, currentColor, currentTool);
        qDebug("mouse release");
        update();

        emit clearUndoBuffer(image);
        ui->undoButton->setEnabled(true);
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
    paintLayer(image, canvasXOffset, canvasYOffset, canvasWidth, canvasHeight);
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
        int gridX = (mousePosition.x() - canvasXOffset)*sizeOfCanvas/canvasWidth;
        int gridY = (mousePosition.y() - canvasYOffset)*sizeOfCanvas/canvasHeight;

        isModified = true;
        isSaved = false;
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
