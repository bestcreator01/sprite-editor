#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include <QObject>
#include <QImage>
#include <QList>
#include <QTimer>
#include <QJsonDocument>
#include "drawingtools.h"

class PixelCanvas : public QObject
{
    Q_OBJECT

    // frame layers
    QList<QImage*> layers;

    // location and size of a canvas
    const int sizeOfCanvas = 32;

    QVector<QImage> history;

    int historyPointer;


    // Initialize values
    int editLayer;
    int maxLayer;
    int fpsSpeed;
    int playLoop;
    bool flag = true;

    // Initalize tools
    DrawingTools tools;

    ///
    /// \brief playbackLoop recursive animation loop
    ///
    void playbackLoop();

public:
    // Default Contructor
    explicit PixelCanvas(QObject *parent = nullptr);
    // Default Destructor
    ~PixelCanvas();

signals:
    ///
    /// \brief updateCanvas send a signal to view to update Canvas
    ///
    void updateCanvas(QImage, int);

    ///
    /// \brief sendPlayback send preveiw animation
    ///
    void sendPlayback(QImage);

    ///
    /// \brief updatePixelsByTools draw a pixel in Image
    /// \param image the Image being updated
    /// \param x position in Image
    /// \param y position in Image
    /// \param color special color of pixel
    /// \param tool spcific tool to draw on canvas
    ///
    void updatePixelsByTools(QImage& image, int x, int y, int color, int tool);

    ///
    /// \brief updatePixelsByTools draw a pixel in Image
    /// \param image the Image being updated
    /// \param x position in Image
    /// \param y position in Image
    /// \param color special color of pixel
    /// \param tool spcific tool to draw on canvas
    ///
    void updatePixelsByToolsCustom(QImage& image, int x, int y, QColor color, int tool);

    ///
    /// \brief allLayers send all the frame layers
    /// \param layers all the frames
    ///
    void allLayers(QList<QImage*> layers);

    ///
    /// \brief populatedJSON fill in Json Doc with details about PixelCanvas
    /// \param jsonDoc Json Doc that is being saved
    ///
    void populatedJSON(QJsonDocument jsonDoc);

    ///
    /// \brief updateFPS
    /// \param loadFPS
    ///
    void updateFPS(int loadFPS);

    ///
    /// \brief sendQIcons
    /// \param icons
    ///
    void sendQIcons(QList<QImage> icons);

    ///
    /// \brief sendLayerIndex
    /// \param index
    ///
    void sendLayerIndex(int index);

public slots:
    ///
    /// \brief deleteLayer delete a frame from layers
    ///
    void deleteLayer();
    ///
    /// \brief addLayer ad a frame to layers
    ///
    void addLayer();
    ///
    /// \brief setEditLayer set the editing target of a frame
    ///
    void setEditLayer(int);
    ///
    /// \brief getEditingImage get target
    /// \return
    ///
    QImage& getEditingImage();
    ///
    /// \brief redo
    /// \param enable
    /// \param image
    ///
    void redo(bool &enable, QImage &image);
    ///
    /// \brief undo
    /// \param enable
    /// \param image
    ///
    void undo(bool &enable, QImage &image);
    ///
    /// \brief resetUndoRedo
    /// \param image
    ///
    void resetUndoRedo(QImage image);
    ///
    /// \brief clearUndoBuffer
    ///
    void clearUndoBuffer(QImage);
    ///
    /// \brief playback
    ///
    void playback(int);
    ///
    /// \brief setSpeed
    ///
    void setSpeed(int);
    ///
    /// \brief updatePixel
    ///
    void updatePixel(int, int, int, int);
    ///
    /// \brief updatePixel
    ///
    void updateCustomPixel(int, int, QColor, int);
    ///
    /// \brief clearImage slot to clear the image data when new file is clicked from the view
    ///
    void clearImage();
    ///
    /// \brief getLayers slot to get all the layers and here, it emits a signal by passing in the layers List as a
    /// parameter.
    ///
    void getLayers();
    ///
    /// \brief createJSON serializes the data of the Pixel Canvas (x, y coordinates, color and frames information) in JSON
    /// format. Sends a signal to the view to write the JSON text in a file
    ///
    void createJSON();
    ///
    /// \brief loadJson
    /// \param jsonDoc
    ///
    void loadJson(QJsonDocument jsonDoc);

private:
    void modifyLayers(QImage* image);
    ///
    /// \brief setEditingImage
    /// \param image
    ///
    void setEditingImage(QImage image);
};

#endif // PIXELCANVAS_H
