#ifndef PIXELCANVASLAYERS_H
#define PIXELCANVASLAYERS_H

#include <QObject>
#include <QImage>
#include <QList>
#include "pixelcanvas.h"
#include "drawingtools.h"

class PixelCanvasLayers : public QObject
{
    Q_OBJECT
    QList<QImage*> layers;
    int editLayer;
    int maxLayer;
    DrawingTools d;

public:
    explicit PixelCanvasLayers(QObject *parent = nullptr);
    //PixelCanvasLayers(int height, int width);
    ~PixelCanvasLayers();

signals:
    void updateCanvas(QImage);

public slots:
    void deleteLayer();
    void addLayer();
    void setEditLayer(int);
    const QImage& getPlaybackImage(int);
    QImage& getEditingImage();
    void moveLayer(int, int);
    void setMax(int);
    const QList<QImage*> getLayers();
    int getMaxLayers();
    int getEditLayers();
    void updatePixel(int, int, int, int);
};

#endif // PIXELCANVASLAYERS_H
