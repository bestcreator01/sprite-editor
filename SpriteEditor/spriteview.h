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
//    QVector<QImage> history;
//    int historyPointer;
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
    QColor customColor;

    // saves the file path of the recent saved file
    QString savedFile = "";

    bool isModified = false;
    bool isSaved = false;

    QJsonDocument jsonDoc;

public:
    SpriteView(DrawingTools& tools, PixelCanvas& canvas, QWidget *parent = nullptr);
    ~SpriteView();

signals:
    ///
    /// \brief getJSON signal to send the model (PixelCanvas) to generate JSON text
    ///
    void getJSON();

    ///
    /// \brief readJson
    /// \param jsonDoc
    ///
    void readJson(QJsonDocument jsonDoc);

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

    void sendCustomInformation(int x, int y, QColor color, int tool);

    ///
    /// \brief setPlaybackSpeed
    ///
    void setPlaybackSpeed(int);

    ///
    /// \brief playback
    ///
    void playback(int);

    ///
    /// \brief addFrame
    ///
    void addFrame();

    ///
    /// \brief deleteFrame
    ///
    void deleteFrame();

    ///
    /// \brief setEditingFrame
    ///
    void setEditingFrame(int);

    ///
    /// \brief clearPixels
    ///
    void clearPixels();

    ///
    /// \brief clearImage sends a signal to the model to clear all images (layers);
    ///
    void clearImage();

    ///
    /// \brief getLayerInfo sends a signal to the model to get all the layers from the model
    ///
    void getLayerInfo();
    ///
    /// \brief redo
    ///
    void redo(bool&, QImage&);
    ///
    /// \brief undo
    ///
    void undo(bool&, QImage&);
    ///
    /// \brief resetUndoRedo
    ///
    void resetUndoRedo(QImage);
    ///
    /// \brief clearUndoBuffer
    ///
    void clearUndoBuffer(QImage);

    ///
    /// \brief addExistingLayers
    /// \param image
    ///
    void addExistingLayers(QImage* image);

private slots:

    ///
    /// \brief on_newFile_clicked to be called when user clicks on new file button
    ///
    void on_newFile_clicked();

    ///
    /// \brief on_saveFile_clicked to be called when user clicks on save file button
    ///
    void on_saveFile_clicked();

    ///
    /// \brief on_loadFile_clicked to be called when user clicks on load file button
    ///
    void on_loadFile_clicked();

    ///
    /// \brief populateAllLayers grabs all the current layers (QImages) in the frame list and populates it in the
    /// layer QList of the view
    /// \param allLayers List of QImages
    ///
    void populateAllLayers(QList<QImage*> allLayers);


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
    /// \brief customColors
    ///
    void customColors();

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

    ///
    /// \brief resetUndoHistory
    ///
    void resetUndoHistory();


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
    /// \brief clearCanvas helper method for New File button. Asks the user if the user wants to save, discard
    ///  or cancel changes when the canvas is modified.
    ///
    void clearCanvas();

    ///
    /// \brief saveFile saves the file as a selected location. Emits a signal to the model for JSON data and writes
    /// that data in the selected name file at a selected location.
    ///
    void saveFile();

    ///
    /// \brief loadFile TODO
    ///
    void loadFile();

    ///
    /// \brief loadJSON TODO
    /// \return
    ///
    void loadJSON(const QJsonDocument& jsonDoc);

    void setDefaultFrame(int index);

    ///
    /// \brief clearAll clears all data of the canvas (layers, FPS values, QImage data)
    ///
    void clearAll();

    ///
    /// \brief clearFrameIcons
    ///
    void clearFrameIcons();

    ///
    /// \brief askToSave asks the user to save if the file is modified before loading a file
    ///
    void askToSave();

    ///
    /// \brief warnUser
    ///
    void warnUser();
};
#endif // SPRITEVIEW_H
