/**
 * Author:     Crazy Broke Asians
 * Date:       Nov-16-2023
 * Course:     CS 3505, University of Utah
 * Assignment: A8: Sprite Editor
 * File Contents
 *      It contains all necessary implementation of the PixelCanvas Model.
*/
#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include <QObject>
#include <QImage>
#include <QList>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

///
/// \brief The PixelCanvas class
///
class PixelCanvas : public QObject
{
    Q_OBJECT

    // frame layers & History of Images
    QList<QImage*> layers;
    QVector<QImage> history;
    int historyPointer;

    // location and size of a canvas
    const int sizeOfCanvas = 32;

    // Initialize values
    int editLayer;
    int maxLayer;
    int fpsSpeed;
    int playLoop;
    bool resetAnimation = true;

    ///
    /// \brief animationLoop - recursive play animation in preview logic
    ///
    void animationLoop();

    ///
    /// \brief modifyLayers
    /// \param image
    ///
    void modifyLayers(QImage* image);

    ///
    /// \brief setEditingImage
    /// \param image
    ///
    void setEditingImage(QImage image);

public:
    // Default Contructor, initialize objects
    explicit PixelCanvas(QObject *parent = nullptr);

    // Default Destructor
    ~PixelCanvas();

signals:
    ///
    /// \brief updateCanvas - send a signal to view to update Canvas
    ///
    void updateCanvas(QImage, int);

    ///
    /// \brief sendPlayback - send preveiw animation
    ///
    void sendPlayback(QImage);

    ///
    /// \brief updatePixelsByTools - draw a pixel in Image
    /// \param image - the Image being updated
    /// \param x - position in Image
    /// \param y - position in Image
    /// \param color - preset color of pixel
    /// \param tool - spcific tool to draw on canvas
    ///
    void updatePixelsByTools(QImage& image, int x, int y, int color, int tool);

    ///
    /// \brief updatePixelsByTools - draw a pixel in Image
    /// \param image - the Image being updated
    /// \param x - position in Image
    /// \param y - position in Image
    /// \param color - custom color of pixel
    /// \param tool - spcific tool to draw on canvas
    ///
    void updatePixelsByToolsCustom(QImage& image, int x, int y, QColor color, int tool);

    ///
    /// \brief allLayers - send all the frame layers
    ///
    void allLayers(QList<QImage *>);

    ///
    /// \brief populatedJSON - fill in Json Doc with details about PixelCanvas
    ///
    void populatedJSON(QJsonDocument);

    ///
    /// \brief updateFPS - send signal for FPS number to be updated in SpriteView
    ///
    void updateFPS(int);

    ///
    /// \brief sendQIcons - send Icon Image to be updated in SpriteView
    ///
    void sendQIcons(QList<QImage>);

    ///
    /// \brief sendLayerIndex - send Layer Edit to the SpriteView
    ///
    void sendLayerIndex(int);

public slots:

    ///
    /// \brief deleteLayer - delete a frame from layers
    ///
    void deleteLayer();

    ///
    /// \brief addLayer - add a frame to layers
    ///
    void addLayer();

    ///
    /// \brief setEditLayer - set the editing target of a frame
    ///
    void setEditLayer(int);

    ///
    /// \brief getEditingImage - get editing target frame
    /// \return recent frame being edited
    ///
    QImage& getEditingImage();

    ///
    /// \brief redo - redo logic for updating recent editing frame to forword state
    /// \param enable - flag to set the redo button to disable / enable
    /// \param image -  curret image
    ///
    void redo(bool&, QImage&);

    ///
    /// \brief undo - undo logic for updating recent editing frame to previous state
    ///
    void undo(bool&, QImage&);

    ///
    /// \brief resetUndoRedo - reset the variables for undo and redo
    ///
    void resetUndoRedo(QImage);

    ///
    /// \brief clearUndoBuffer - clear the history for the current frame
    ///
    void clearUndoBuffer(QImage);

    ///
    /// \brief animation - start the call for animating frames
    ///
    void animation(int);

    ///
    /// \brief setSpeed - set the FPS speed
    ///
    void setSpeed(int);

    ///
    /// \brief updatePixel - update Image by adding Pixel color at a specific coordinate
    /// \param x - x coordinate
    /// \param y - y coordinate
    /// \param color - preset pixel color
    /// \param tool - sprite tool to add to Image
    ///
    void updatePixel(int x, int y, int color, int tool);

    ///
    /// \brief updatePixel - update Image by adding Pixel color at a specific coordinate
    /// \param x - x coordinate
    /// \param y - y coordinate
    /// \param color - custom pixel color
    /// \param tool - sprite tool to add to Image
    ///
    void updateCustomPixel(int x, int y, QColor color, int tool);

    ///
    /// \brief clearImage - to clear the image data when new file is clicked from the view
    ///
    void clearImage();

    ///
    /// \brief getLayers - to get all the layers and here, it emits a signal by passing in the layers List as a
    /// parameter.
    ///
    void getLayers();

    ///
    /// \brief createJSON - serializes the data of the Pixel Canvas (x, y coordinates, color and frames information) in JSON
    /// format. Sends a signal to the view to write the JSON text in a file
    ///
    void createJSON();

    ///
    /// \brief loadJson - load Json file to the SpriteEditor, by clearing or Updating the Model side & View side
    ///
    void loadJson(QJsonDocument);
};

#endif // PIXELCANVAS_H
