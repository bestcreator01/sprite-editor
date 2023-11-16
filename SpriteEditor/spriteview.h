/**
 * Author:     Crazy Broke Asians
 * Date:       Nov-16-2023
 * Course:     CS 3505, University of Utah
 * Assignment: A8: Sprite Editor
 * File Contents
 *      It contains all necessary information needed to form the main window class.
*/
#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>
#include <QString>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>
#include "drawingtools.h"
#include "pixelcanvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteView; }
QT_END_NAMESPACE

///
/// \brief The SpriteView class - it takes care of all view elements.
///
class SpriteView : public QMainWindow
{
    Q_OBJECT

    // Initialize Images & mouse position
    QImage image;
    QImage previewImage;
    QPoint mousePosition;

    // location and size of a canvas and a preview
    const int sizeOfCanvas = 32;

    // Initialize Canvas values
    int canvasXOffset;
    int canvasYOffset;
    int canvasWidth;
    int canvasHeight;

    // Initialize Preveiw values
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
    QColor customColor;

    // Initialize Frame List & all the Layer frames
    QList<QListWidgetItem *> frameList;
    QList<QImage*> layers;

    // Saves the file path of the recent saved file
    QString savedFile = "";

    // For loading/saving files
    bool isModified = false;
    bool isSaved = false;

    QJsonDocument jsonDoc;

public:

    // The essential construtor we use in the view class
    SpriteView(DrawingTools &tools, PixelCanvas &canvas, QWidget *parent = nullptr);
    ~SpriteView();

signals:

    ///
    /// \brief getJSON - signal to send the model (PixelCanvas) to generate JSON text
    ///
    void getJSON();

    ///
    /// \brief readJson - signal to read the JSON Doc to translate to the Sprite Editor
    ///
    void readJson(QJsonDocument);

    ////////////////
    /// PixelCanvas
    ////////////////

    ///
    /// \brief sendInformation - a signal to send coordinates to the tool classes.
    /// \param x - x coordinate of the Canvas Image
    /// \param y - y coordinate of the Canvas Image
    /// \param color - Preset Color choosen from GUI
    /// \param tool - Specific tool to draw/erase on Canvas
    ///
    void sendInformation(int x, int y, int color, int tool);

    ///
    /// \brief sendInformation - a signal to send coordinates to the tool classes.
    /// \param x - x coordinate of the Canvas Image
    /// \param y - y coordinate of the Canvas Image
    /// \param color - Custom Color choosen from GUI
    /// \param tool - Specific tool to draw/erase on Canvas
    ///
    void sendCustomInformation(int x, int y, QColor color, int tool);

    ///
    /// \brief setFPSSpeed - send signal to model to set FPS speed
    ///
    void setFPSSpeed(int);

    ///
    /// \brief animation - send signal to start animation
    ///
    void animation(int);

    ///
    /// \brief addFrame - send signal to update Model on adding frame layers
    ///
    void addFrame();

    ///
    /// \brief deleteFrame - send signal to update Model on removing frame layers
    ///
    void deleteFrame();

    ///
    /// \brief setEditingFrame - send signal to Model to set the target frame to edit
    ///
    void setEditingFrame(int);

    ///
    /// \brief clearPixels - send signal to Model to clear Canvas pixels
    ///
    void clearPixels();

    ///
    /// \brief clearImage - sends a signal to the model to clear all images (layers);
    ///
    void clearImage();

    ///
    /// \brief getLayerInfo - sends a signal to the model to get all the layers from the model
    ///
    void getLayerInfo();

    ///
    /// \brief redo - send signal to Model do redo
    ///
    void redo(bool&, QImage&);

    ///
    /// \brief undo - send signal to Model do undo
    ///
    void undo(bool&, QImage&);

    ///
    /// \brief resetUndoRedo - send signal to rest Undo & Redo logic
    ///
    void resetUndoRedo(QImage);
    ///
    /// \brief clearUndoBuffer - send signal to clear Undo Images
    ///
    void clearUndoBuffer(QImage);

private slots:

    ///
    /// \brief on_newFile_clicked - to be called when user clicks on new file button
    ///
    void on_newFile_clicked();

    ///
    /// \brief on_saveFile_clicked - to be called when user clicks on save file button
    ///
    void on_saveFile_clicked();

    ///
    /// \brief on_loadFile_clicked - to be called when user clicks on load file button
    ///
    void on_loadFile_clicked();

    ///
    /// \brief populateAllLayers - grabs all the current layers (QImages) in the frame list and populates it in the
    /// layer QList of the view
    ///
    void populateAllLayers(QList<QImage *>);


private:

    Ui::SpriteView *ui;

    ////////////////
    /// PixelCanvas
    ////////////////

    ///
    /// \brief addToFrameList - add item to framelist
    ///
    void addToFrameList();

    ///
    /// \brief deleteFrameClicked - delete frame as well as QImage from model
    ///
    void deleteFrameClicked();

    ///
    /// \brief addFrameClicked - add frame and QImage to model
    ///
    void addFrameClicked();

    ///
    /// \brief customColors - grabs a Custom Color from the Color palette
    ///
    void customColors();

    ///
    /// \brief onSliderChanged - FPS slider when change
    ///
    void onSliderChanged(int);

    ///
    /// \brief getSliderValue - get the currend FPS Slider value
    ///
    void getSliderValue(int);

    ///
    /// \brief updateFrameList - is for JSON save, where it loads up Icons in JSON and insert it in framelist
    ///
    void updateFrameList(QList<QImage>);

    ///
    /// \brief selectEdit - select the frame with Image editing
    ///
    void selectEdit(QListWidgetItem *);

    ///
    /// \brief updateEditor - updates the select frame icon
    ///
    void updateEditor(const QImage&, int);

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
    /// \brief resetUndoHistory - clear history of undo/redo when selcting new frame
    ///
    void resetUndoHistory();


    ///////////////////////////
    /// Mouse and Paint methods
    ///////////////////////////

    ///
    /// \brief paintEvent - displays the background image for the Sprite Editor and draws transparent
    /// pixels on the background image.
    ///
    void paintEvent(QPaintEvent *) override;

    ///
    /// \brief mouseMoveEvent - handles mouse event whenever the user hovers over the canvas.
    ///
    void mouseMoveEvent(QMouseEvent *) override;

    ///
    /// \brief mousePressEvent - handles mouse event whenever the user clicks over the canvas.
    ///
    void mousePressEvent(QMouseEvent *) override;

    ///
    /// \brief mouseReleaseEvent - handles mouse event whenever the user unclicks the mouse.
    ///
    void mouseReleaseEvent(QMouseEvent *) override;

    ///
    /// \brief mouseToPen - changing the cursor to a pen.
    ///
    void mouseToPen();

    ///
    /// \brief mouseToEraser - changing the cursor to an eraser.
    ///
    void mouseToEraser();

    ///
    /// \brief mouseToSpray - changing the cursor to a sprayer.
    ///
    void mouseToSpray();

    ///
    /// \brief paintCanvas - paints the Image onto Canvas
    ///
    void paintCanvas(QImage&);

    ///
    /// \brief paintPreview - paints the Image onto Preview
    ///
    void paintPreview(QImage&);


    //////////////////
    /// Helper methods
    //////////////////

    ///
    /// \brief mouseEventHelper - help on updating the Canvas response to the Mouse
    ///
    void mouseEventHelper(QMouseEvent *);

    ///
    /// \brief mouseToDrawingTools - update mouse cursor to display right tool icon
    ///
    void mouseToDrawingTools(QString);

    ///
    /// \brief paintLayer - paint the Canvas or Preview on GUI
    /// \param image - specific background image
    /// \param x - x coordinate on the ui
    /// \param y - y coordinate on the ui
    /// \param width - the width of the Canvas or Preview
    /// \param height the heigth of the Canvas or Preview
    ///
    void paintLayer(QImage& image, int x, int y, int width, int height);

    ///
    /// \brief clearCanvas - helper method for New File button. Asks the user if the user wants to save, discard
    ///  or cancel changes when the canvas is modified.
    ///
    void clearCanvas();

    ///
    /// \brief saveFile - saves the file as a selected location. Emits a signal to the model for JSON data and writes
    /// that data in the selected name file at a selected location.
    ///
    void saveFile();

    ///
    /// \brief loadFile - load JSON file to the Sprite Editor, should update the Frame List, preview, & FPS slider
    ///
    void loadFile();

    ///
    /// \brief setDefaultFrame - set the Default Edit Frame to be the latest frame
    ///
    void setDefaultFrame(int);

    ///
    /// \brief clearAll - clears all data of the canvas (layers, FPS values, QImage data)
    ///
    void clearAll();

    ///
    /// \brief clearFrameIcons - clear all of the Frame List icons
    ///
    void clearFrameIcons();

    ///
    /// \brief askToSave - asks the user to save if the file is modified before loading a file
    ///
    void askToSave();

    ///
    /// \brief warnUser - warn Users to Save befor loading or new file
    ///
    void warnUser();
};
#endif // SPRITEVIEW_H
