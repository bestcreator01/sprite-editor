#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include <QObject>
#include <QImage>
#include <QList>
#include <QTimer>
#include "drawingtools.h"

class PixelCanvas : public QObject
{
    Q_OBJECT
    QList<QImage*> layers;
    const int sizeOfCanvas = 32;
    int editLayer;
    int maxLayer;
    int playbackSpeed;
    int playLoop;
    bool flag = true;
    DrawingTools tools;
    void playbackLoop();

public:
    explicit PixelCanvas(QObject *parent = nullptr);
    ~PixelCanvas();

signals:
    void updateCanvas(QImage);
    void playback(QImage);
    void updatePixelsByTools(QImage& image, int x, int y, int color, int tool);

public slots:
    void deleteLayer();
    void addLayer();
    void setEditLayer(int);
    QImage& getEditingImage();
    void Playback(int);
    void setSpeed(int);
    void updatePixel(int, int, int, int);
    void clearImage();
};

#endif // PIXELCANVAS_H
