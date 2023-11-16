/**
 * Author:     Crazy Broke Asians
 * Date:       Nov-16-2023
 * Course:     CS 3505, University of Utah
 * Assignment: A8: Sprite Editor
 * Reviewer:   Gloria Shin, Surbhi Saini, Seoin Kim, Monthon Paul, Atharv Kulkarni
 * File Contents
 *      It contains all necessary information needed to form the main window class.
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

    // Set Preview values to be in the ui
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

    QIcon palleteIcon(":/icons/pallete.png");

    ui->penButton->setIcon(penIcon);
    ui->eraserButton->setIcon(eraserIcon);
    ui->sprayButton->setIcon(sprayIcon);

    ui->saveFile->setIcon(saveIcon);
    ui->newFile->setIcon(newFileIcon);
    ui->loadFile->setIcon(loadIcon);

    ui->undoButton->setIcon(undoIcon);
    ui->redoButton->setIcon(redoIcon);

    ui->colorButton->setIcon(palleteIcon);

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
    connect(ui->penButton, &QPushButton::clicked, this, [=]() {currentTool = 0;});
    connect(ui->eraserButton, &QPushButton::clicked, this, [=]() {currentTool = 1;});
    connect(ui->sprayButton, &QPushButton::clicked, this, [=]() {currentTool = 2;});
    connect(ui->undoButton, &QPushButton::clicked, this, &SpriteView::undoButtonClicked);
    connect(ui->redoButton, &QPushButton::clicked, this, &SpriteView::redoButtonClicked);

    // when selecting the colors
    connect(ui->colorRed, &QPushButton::clicked, this, [=]() {currentColor = 0; customColor = nullptr;});
    connect(ui->colorOrange, &QPushButton::clicked, this, [=]() {currentColor = 1; customColor = nullptr;});
    connect(ui->colorYellow, &QPushButton::clicked, this, [=]() {currentColor = 2; customColor = nullptr;});
    connect(ui->colorGreen, &QPushButton::clicked, this, [=]() {currentColor = 3; customColor = nullptr;});
    connect(ui->colorBlue, &QPushButton::clicked, this, [=]() {currentColor = 4; customColor = nullptr;});
    connect(ui->colorPurple, &QPushButton::clicked, this, [=]() {currentColor = 5; customColor = nullptr;});
    connect(ui->colorBlack, &QPushButton::clicked, this, [=]() {currentColor = 6; customColor = nullptr;});
    connect(ui->colorWhite, &QPushButton::clicked, this, [=]() {currentColor = 7; customColor = nullptr;});
    connect(ui->colorButton, &QPushButton::clicked, this, &SpriteView::customColors);

    // Preview & FPS logic
    connect(ui->deleteFrame, &QPushButton::clicked, this, &SpriteView::deleteFrameClicked);
    connect(ui->addFrame, &QPushButton::clicked, this, &SpriteView::addFrameClicked);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &SpriteView::selectEdit);
    connect(ui->fpsSlider, &QSlider::valueChanged, this, &SpriteView::onSliderChanged);
    connect(this, &SpriteView::addFrame, &canvas, &PixelCanvas::addLayer);
    connect(this, &SpriteView::deleteFrame, &canvas, &PixelCanvas::deleteLayer);
    connect(this, &SpriteView::setEditingFrame, &canvas, &PixelCanvas::setEditLayer);
    connect(this, &SpriteView::setFPSSpeed, &canvas, &PixelCanvas::setSpeed);
    connect(this, &SpriteView::animation, &canvas, &PixelCanvas::animation);
    connect(&canvas, &PixelCanvas::updateCanvas, this, [=](QImage frame, int speed){image = frame; if (!speed) { previewImage = frame; } update();});
    connect(&canvas, &PixelCanvas::sendPlayback, this, [=](QImage frame){previewImage = frame; update();});

    // Undo Redo
    connect(this, &SpriteView::redo, &canvas, &PixelCanvas::redo);
    connect(this, &SpriteView::undo, &canvas, &PixelCanvas::undo);
    connect(this, &SpriteView::resetUndoRedo, &canvas, &PixelCanvas::resetUndoRedo);
    connect(this, &SpriteView::clearUndoBuffer, &canvas, &PixelCanvas::clearUndoBuffer);


    // JSON serialization and deserialization related connections
    connect(this, &SpriteView::getJSON, &canvas, &PixelCanvas::createJSON);
    connect(&canvas, &PixelCanvas::populatedJSON, this, [=](QJsonDocument doc){jsonDoc=doc;});
    connect(this, &SpriteView::readJson, &canvas, &PixelCanvas::loadJson);
    connect(&canvas, &PixelCanvas::updateFPS, this, &SpriteView::getSliderValue);
    connect(&canvas, &PixelCanvas::sendLayerIndex, this, &SpriteView::setDefaultFrame);
    connect(&canvas, &PixelCanvas::sendQIcons, this, &SpriteView::updateFrameList);

    // Clearing the canvas related connections
    connect(this, &SpriteView::getLayerInfo, &canvas, &PixelCanvas::getLayers);
    connect(&canvas, &PixelCanvas::allLayers, this, &SpriteView::populateAllLayers);

    // when drawing on canvas - retrieving the coordinates
    connect(this, &SpriteView::sendCustomInformation, &canvas, &PixelCanvas::updateCustomPixel);
    connect(&canvas, &PixelCanvas::updatePixelsByTools, &tools, &DrawingTools::updatePixels);
    connect(this, &SpriteView::sendInformation, &canvas, &PixelCanvas::updatePixel);
    connect(&canvas, &PixelCanvas::updatePixelsByToolsCustom, &tools, &DrawingTools::updateCustomPixels);
    connect(this, &SpriteView::clearImage, &canvas, &PixelCanvas::clearImage);
}

SpriteView::~SpriteView()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////
/// Save and Load file through JSON Serialization & Deserialization
//////////////////////////////////////////////////////////////////

void SpriteView::saveFile()
{
    // get the layers from the model
    emit getLayerInfo();

    // means user has not saved a file
    if (savedFile.isEmpty())
    {
        QString fileName = QFileDialog::getSaveFileName(
            this, "Save a File", QDir::homePath(), tr("SSP files (*.ssp)"));

        //user clicked "cancel"
        if(fileName == "")
        {
            return;
        }

        // set the selected file as the new savedFile
        savedFile = QFileInfo(fileName).absoluteFilePath();
    }

    QFile file(savedFile);

    // get the serialized JSON data
    emit getJSON();

    // write to the file
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

    if (!fileName.isEmpty())
    {
        savedFile = QFileInfo(fileName).absoluteFilePath();
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            QString jsonString = stream.readAll();
            file.close();

            QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

            if (!jsonDoc.isNull())
            {
                // send the jsonDoc to the pixelCanvas class
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

void SpriteView::on_saveFile_clicked()
{
    saveFile();
}

void SpriteView::on_loadFile_clicked()
{
    loadFile();
}

/////////////////////////////////////////
/// New File clicked - Clear the Canvas
////////////////////////////////////////

void SpriteView::on_newFile_clicked()
{
    clearCanvas();
}

void SpriteView::clearCanvas()
{
    if (isModified)
    {
        QMessageBox warningMessage;

        warningMessage.setText("WARNING!\n\nThis file has been modified. Do you "
                               "want to save your changes?");
        warningMessage.setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
                                          QMessageBox::Cancel);

        warningMessage.setIcon(QMessageBox::Warning);
        warningMessage.setWindowTitle("Unsaved Changes");
        int response = warningMessage.exec();

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
}

void SpriteView::clearAll()
{
    image.fill(qRgba(0, 0, 0, 0));
    previewImage.fill(qRgba(0, 0, 0, 0));

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

////////////////
/// PixelCanvas
////////////////

void SpriteView::customColors()
{
    QColorDialog colorDialog;
    customColor = colorDialog.getColor();
}

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
    }
    else
    {
        ui->addFrame->setEnabled(true);
        ui->deleteFrame->setEnabled(true);
    }

    ui->previewLabel->clear();

    emit setFPSSpeed(value);
    emit animation(value);
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
    resetUndoHistory();
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
void SpriteView::undoButtonClicked()
{
    bool enable = true;
    emit undo(enable, image);
    previewImage = image;

    ui->redoButton->setEnabled(true);
    if (!enable)
    {
        ui->undoButton->setEnabled(false);
    }
    updateEditor(image,currentLayer);
    update();
}

///
/// \brief SpriteView::redoButtonClicked - Redo user action
///
void SpriteView::redoButtonClicked()
{
    bool enable = true;
    emit redo(enable, image);
    previewImage = image;

    ui->undoButton->setEnabled(true);
    if (!enable)
    {
        ui->redoButton->setEnabled(false);
    }
    updateEditor(image, currentLayer);
    repaint();
}

///
/// \brief SpriteView::resetUndoHistory
///
void SpriteView::resetUndoHistory()
{
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
        // Convert mouse coordinates to grid coordinates
        int gridX = (mousePosition.x() - canvasXOffset)*sizeOfCanvas/canvasWidth;
        int gridY = (mousePosition.y() - canvasYOffset)*sizeOfCanvas/canvasHeight;

        isModified = true;
        isSaved = false;
        customColor == nullptr ? emit sendInformation(gridX, gridY, currentColor, currentTool) : emit sendCustomInformation(gridX, gridY, customColor, currentTool);

        update();

        emit clearUndoBuffer(image);
        ui->undoButton->setEnabled(true);
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
        // converted coordinates from world size to grid
        int gridX = (mousePosition.x() - canvasXOffset)*sizeOfCanvas/canvasWidth;
        int gridY = (mousePosition.y() - canvasYOffset)*sizeOfCanvas/canvasHeight;

        isModified = true;
        isSaved = false;
        ui->coordinates->setText(" " + QString::number(gridX) + ", " + QString::number(gridY));
        customColor == nullptr ? emit sendInformation(gridX, gridY, currentColor, currentTool) : emit sendCustomInformation(gridX, gridY, customColor, currentTool);
        update();
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
