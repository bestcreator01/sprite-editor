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
#include <QPen>
#include <QMouseEvent>
#include <QPixmap>
#include <QListWidgetItem>
#include <QDebug>
#include "drawingtools.h"
#include "preview.h"
#include "pixelcanvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteView; }
QT_END_NAMESPACE

class SpriteView : public QMainWindow
{
    Q_OBJECT

    QImage image;
    QVector<QImage> history;
    int historyPointer;
    QPoint mousePosition;

    // location and size of a canvas and a preview
    const int sizeOfCanvas = 32;

    int x_offset;
    int canvasWidth;
    int y_offset;
    int canvasHeight;

    int previewXOffset;
    int previewYOffset;
    int previewWidth;
    int previewHeight;

    // default layer = 0;
    int currentLayer = 0;

    // 0 - pen, 1 - eraser, 2 - spray
    int currentTool = -1; // no drawing yet

    // 0 - red, 1 - orange, 2 - yellow, 3 - green, 4 - blue, 5 - purple, 6 - black, 7 - white
    int currentColor = 6; //default color

    QList<QListWidgetItem *> frameList;

public:
    SpriteView(DrawingTools& tools, Preview& preview, PixelCanvas& canvas, QWidget *parent = nullptr);
    ~SpriteView();

signals:
    ///
    /// \brief sendInformation - A signal to send coordinates to the tool classes.
    /// \param image
    /// \param x
    /// \param y
    /// \param color
    /// \param tool
    ///
    void sendInformation(int x, int y, int color, int tool);

    void updateColor();

    void setPlaybackSpeed(int);
    void Playback(int);
    void addFrame();
    void deleteFrame();
    void setEditingFrame(int);

private slots:
    void on_saveFile_clicked();

    void insertCoordinates(QSet<QPair<int, int> > coords);
    void removeCoordinates(QSet<QPair<int, int> > coords);
private:
    Ui::SpriteView *ui;

    void addToFrameList();
    void deleteFrameClicked();
    void addFrameClicked();
    void onSliderChanged(int value);
    void updateFrameList(QList<QImage>);
    void selectEdit(QListWidgetItem *);
    void updateEditor(const QImage &frameImage, int editingTarget);

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
    /// \brief undoButtonClicked - undo current change
    ///
    void undoButtonClicked();

    ///
    /// \brief redoButtonClicked - redo last undo action
    ///
    void redoButtonClicked();

    ///
    /// \brief paintCanvas
    /// \param image
    ///
    void paintCanvas(QImage& image);

    ///
    /// \brief paintPreview
    ///
    void paintPreview(QImage& image);

    //////////////////
    /// Helper methods
    //////////////////

    int convertWorldToGrid_X(int x);

    int convertWorldToGrid_Y(int y);

    void mouseEventHelper(QMouseEvent *event);

    void mouseToDrawingTools(QString imagepath);

    void paintLayer(QImage& image, int x, int y, int width, int height);

    QSet<QPair<int, int>> coordinates;

    QJsonDocument createJSON();
};
#endif // SPRITEVIEW_H
