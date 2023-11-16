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
#include <QString>
#include <QVector>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QListWidgetItem>
#include <QJsonDocument>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include "drawingtools.h"
#include "pixelcanvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteView; }
QT_END_NAMESPACE

class SpriteView : public QMainWindow
{
    Q_OBJECT

    QImage image;
    QImage previewImage;
    QVector<QImage> history;
    int historyPointer;
    QPoint mousePosition;

    // location and size of a canvas and a preview
    const int sizeOfCanvas = 32;

    int canvasXOffset;
    int canvasYOffset;
    int canvasWidth;
    int canvasHeight;

    int previewXOffset;
    int previewYOffset;
    int previewWidth;
    int previewHeight;

    // default layer = 0;
    int currentLayer = 0;

    // 0 - pen, 1 - eraser, 2 - spray
    int currentTool = -1; // not selected yet

    // 0 - red, 1 - orange, 2 - yellow, 3 - green, 4 - blue, 5 - purple, 6 - black, 7 - white
    int currentColor = 6; //default color

    QList<QListWidgetItem *> frameList;
    QList<QImage*> layers;
    int layerCount = 1;

public:
    SpriteView(DrawingTools& tools, PixelCanvas& canvas, QWidget *parent = nullptr);
    ~SpriteView();

public slots:
    void populateAllLayers(QList<QImage *> allLayers);
signals:
    void getJSON();
    void readJson(QJsonDocument jsonDoc);
//    void updateColor();

    ////////////////
    /// PixelCanvas
    ////////////////

    ///
    /// \brief sendInformation - A signal to send coordinates to the tool classes.
    /// \param image
    /// \param x
    /// \param y
    /// \param color
    /// \param tool
    ///
    void sendInformation(int x, int y, int color, int tool);
    void setPlaybackSpeed(int);
    void playback(int);
    void addFrame();
    void deleteFrame();
    void setEditingFrame(int);
    void clearPixels();
    void clearImage();
    void getLayerInfo();
    void setEditingImage(QImage);

    void addExistingLayers(QImage* image);

private slots:
    ////////////////////////////////////////
    /// JSON Serialization & Deserialization
    ////////////////////////////////////////

    // autogenerated slots - need to modify it soon
    void on_newFile_clicked();
    void on_saveFile_clicked();
    void on_loadFile_clicked();

    void insertCoordinates(QSet<QPair<int, int> > coords);
    void removeCoordinates(int x, int y);

private:
    Ui::SpriteView *ui;

    ////////////////
    /// PixelCanvas
    ////////////////

    ///
    /// \brief SpriteView::addToFrameList add item to framelist
    ///
    void addToFrameList();

    ///
    /// \brief SpriteView::deleteFrameClicked delete frame as well as QImage from model
    ///
    void deleteFrameClicked();

    ///
    /// \brief SpriteView::addFrameClicked add frame and QImage to model
    ///
    void addFrameClicked();

    ///
    /// \brief SpriteView::onSliderChanged FPS slider
    /// \param value change for the slider
    ///
    void onSliderChanged(int value);

    ///
    /// \brief TODO
    /// \param
    ///
    void getSliderValue(int value);

    ///
    /// \brief SpriteView::updateFrameList this is for JSON save, where I believe it loads up Icons in JSON and insert it in framelist
    /// \param icons
    ///
    void updateFrameList(QList<QImage>);

    ///
    /// \brief SpriteView::selectEdit select the frame with Image editing
    /// \param item selected item
    ///
    void selectEdit(QListWidgetItem *);

    ///
    /// \brief SpriteView::updateEditor this updates the frame editor icon
    /// \param frameImage updated image
    /// \param editingTarget the target edit select
    ///
    void updateEditor(const QImage &frameImage, int editingTarget);

    ////////////////
    /// Undo & Redo
    ////////////////

    ///
    /// \brief undoButtonClicked - undo current change
    ///
    void undoButtonClicked();

    ///
    /// \brief redoButtonClicked - redo last undo action
    ///
    void redoButtonClicked();


    ///////////////////////////
    /// Mouse and Paint methods
    ///////////////////////////

    ///
    /// \brief paintEvent - Displays the background image for the Sprite Editor and draws transparent
    /// pixels on the background image.
    ///
    void paintEvent(QPaintEvent *) override;

    ///
    /// \brief mouseMoveEvent - Handles mouse event whenever the user hovers over the canvas.
    /// \param event - the mouse moving event
    ///
    void mouseMoveEvent(QMouseEvent *event) override;

    ///
    /// \brief mousePressEvent - Handles mouse event whenever the user clicks over the canvas.
    /// \param event - the mouse pressing event
    ///
    void mousePressEvent(QMouseEvent *event) override;

    ///
    /// \brief mouseReleaseEvent - Handles mouse event whenever the user unclicks the mouse.
    /// \param event - the mouse release event
    ///
    void mouseReleaseEvent(QMouseEvent *event) override;

    ///
    /// \brief mouseToPen - Changing the cursor to a pen.
    ///
    void mouseToPen();

    ///
    /// \brief mouseToEraser - Changing the cursor to an eraser.
    ///
    void mouseToEraser();

    ///
    /// \brief mouseToSpray - Changing the cursor to a sprayer.
    ///
    void mouseToSpray();

    ///
    /// \brief paintCanvas TODO
    /// \param image
    ///
    void paintCanvas(QImage& image);

    ///
    /// \brief paintPreview TODO
    ///
    void paintPreview(QImage& image);


    //////////////////
    /// Helper methods
    //////////////////

    ///
    /// \brief mouseEventHelper TODO
    /// \param event
    ///
    void mouseEventHelper(QMouseEvent *event);

    ///
    /// \brief mouseToDrawingTools TODO
    /// \param imagepath
    ///
    void mouseToDrawingTools(QString imagepath);

    ///
    /// \brief paintLayer TODO
    /// \param image
    /// \param x
    /// \param y
    /// \param width
    /// \param height
    ///
    void paintLayer(QImage& image, int x, int y, int width, int height);

    ///
    /// \brief clearCanvas TODO
    ///
    void clearCanvas();

    ///
    /// \brief saveFile TODO
    ///
    void saveFile();

    ///
    /// \brief loadFile TODO
    ///
    void loadFile();

    ///
    /// \brief coordinates TODO
    ///
    QSet<QPair<int, int>> coordinates;

    ///
    /// \brief createJSON TODO
    /// \return
    ///
    QJsonDocument createJSON();

    ///
    /// \brief loadJSON TODO
    /// \return
    ///
    void loadJSON(const QJsonDocument& jsonDoc);

    void setDefaultFrame(int index);

    // TODO
    QString savedFile = "";
    bool isClear;
    bool isModified = false;
    bool isSaved = false;
    void clearAll();
    void clearFrameIcons();
    QJsonDocument jsonDoc;
};
#endif // SPRITEVIEW_H
