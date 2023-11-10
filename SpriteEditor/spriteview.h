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
#include "drawingtools.h"
#include "pixelcanvaslayers.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteView; }
QT_END_NAMESPACE

class SpriteView : public QMainWindow
{
    Q_OBJECT
    const int sizeOfCanvas = 32;
    QImage image;

    // 0 - pen, 1 - eraser, 2 - spray, 3 - nothing clicked
    int currentTool = 3;

public:
    SpriteView(DrawingTools& tools, PixelCanvasLayers& layers, QWidget *parent = nullptr);
    ~SpriteView();

signals:
    ///
    /// \brief sendCoordinates - A signal to send coordinates to the tool classes.
    /// \param point - x and y coordinates
    ///
    void sendCoordinates(QPoint point);

    ///
    /// \brief sendPreviewUpdate - TODO
    ///
    void sendChangesOnCanvas();

private:
    Ui::SpriteView *ui;

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
    /// \brief updatePreview
    /// \param image
    ///
    void updatePreview(QImage& image);

    ///
    /// \brief paintPen
    /// \param image
    ///
    void paintPen(QImage& image);

    ///
    /// \brief paintEraser
    /// \param image
    ///
    void paintEraser(QImage& image);

    ///
    /// \brief paintSpray
    /// \param image
    ///
    void paintSpray(QImage& image);
};
#endif // SPRITEVIEW_H
