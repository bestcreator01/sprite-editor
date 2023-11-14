#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include <QObject>
#include <QImage>
#include <QList>
#include "drawingtools.h"

class PixelCanvas : public QObject
{
    Q_OBJECT
    QList<QImage*> layers;
    const int sizeOfCanvas = 32;
    int editLayer;
    int maxLayer;
    DrawingTools d;

public:
    explicit PixelCanvas(QObject *parent = nullptr);
    ~PixelCanvas();

signals:
    void updateCanvas(QImage);
    void updatePixelsByTools(QImage& image, int x, int y, int color, int tool);

public slots:
    void deleteLayer();
    void addLayer();
    void setEditLayer(int);
    const QImage& getPlaybackImage(int);
    QImage& getEditingImage();
    //void moveLayer(int, int);
    void setMax(int);
    const QList<QImage*> getLayers();
    int getMaxLayers();
    int getEditLayers();
    void updatePixel(int, int, int, int);
};

#endif // PIXELCANVAS_H
