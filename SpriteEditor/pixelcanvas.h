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
    QList<QImage*> layers;
    const int sizeOfCanvas = 32;
    int editLayer;
    int maxLayer;
    int fpsSpeed;
    int playLoop;
    bool flag = true;
    DrawingTools tools;
    void playbackLoop();

public:
    explicit PixelCanvas(QObject *parent = nullptr);
    ~PixelCanvas();

signals:
    void updateCanvas(QImage, int);
    void sendPlayback(QImage);
    void updatePixelsByTools(QImage& image, int x, int y, int color, int tool);
    void allLayers(QList<QImage*> layers);
    void layersCount(int count);
    void populatedJSON(QJsonDocument jsonDoc);

public slots:
    void deleteLayer();
    void addLayer();
    void setEditLayer(int);
    QImage& getEditingImage();
    void setEditingImage(QImage image);
    void playback(int);
    void setSpeed(int);
    void updatePixel(int, int, int, int);
    void clearImage();
    void getLayers();
    void layerCount();

    void storeExistingLayers(QImage* image);
    void createJSON();
};

#endif // PIXELCANVAS_H
