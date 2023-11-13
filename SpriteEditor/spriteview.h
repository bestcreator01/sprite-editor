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
#include "pixelcanvaslayers.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteView; }
QT_END_NAMESPACE

class SpriteView : public QMainWindow
{
    Q_OBJECT
    const int sizeOfCanvas = 32;
    QImage image;
    QPoint mousePosition;

    // 0 - pen, 1 - eraser, 2 - spray
    int currentTool = 0;
   // Pen pen;

    // 0 - red, 1 - green, 2 - blue, 3 - black, 4 - nothing selected
    int currentColor = 3;

    int x_offset;
    int canvasWidth;
    int y_offset;
    int canvasHeight;

    QList<QListWidgetItem *> frameList;


public:
    SpriteView(DrawingTools& tools, Preview& preview, PixelCanvasLayers& layers, QWidget *parent = nullptr);
    ~SpriteView();

signals:
    ///
    /// \brief sendCoordinates - A signal to send coordinates to the tool classes.
    /// \param point - x and y coordinates
    ///
    void sendCoordinates(QImage& image, int x, int y, int color, int tool);

    ///
    /// \brief sendPreviewUpdate - TODO
    ///
    void sendChangesOnCanvas();

    void updateColor();

    void setPlaybackSpeed(int);
    void startPlayback(int);
    void addFrame();
    void deleteFrame();
    void setEditingFrame(int);

private:
    Ui::SpriteView *ui;

    void addItemToFrameList();
    void deleteFrameClicked();
    void addFrameClicked();
    void onSliderChanged(int value);
    void updateFrameList(QList<QImage>);
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
    /// \brief mouseMoveEvent - Handles mouse event whenever the user hovers over the canvas.
    /// \param event - the mouse moving event
    ///
    void mousePressEvent(QMouseEvent *event) override;

    ///
    /// \brief mouseReleaseEvent - TODO
    /// \param event - TODO
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
    /// \brief paintCanvas
    /// \param image
    ///
    void paintCanvas(QImage& image);

    ///
    /// \brief paintPreview
    ///
    void paintPreview(QImage& image);

    ///
    /// \brief updateCanvas
    /// \param image
    ///
    void updateCanvas(QImage& image);

    ///
    /// \brief updatePreview
    /// \param image
    ///
    void updatePreview(QImage& image);

    ///
    /// \brief paintSpray
    /// \param image
    ///
    void paintSpray(QImage& image, int x, int y);

    void setSprayPixels(QImage& image, int x, int y, QRgb color);

    int convertWorldToGrid_X(int x);

    int convertWorldToGrid_Y(int y);
};
#endif // SPRITEVIEW_H
