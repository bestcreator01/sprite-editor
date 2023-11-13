#ifndef PIXELCANVASLAYERS_H
#define PIXELCANVASLAYERS_H

#include <QObject>
#include <QImage>
#include <QList>
#include "pixelcanvas.h"

class PixelCanvasLayers : public QObject
{
    Q_OBJECT
    QList<PixelCanvas*> layers;
    int editLayer;
    int maxLayer;
    int height;
    int width;

public:
    explicit PixelCanvasLayers(QObject *parent = nullptr);
    PixelCanvasLayers(int height, int width);
    ~PixelCanvasLayers();

public slots:
    void deleteLayer();
    void addLayer();
    void setEditLayer(int);
    const QImage& getPlaybackImage(int);
    const QImage& getEditingImage();
    PixelCanvas& getCurrentLayer();
    void moveLayer(int, int);
    void setMax(int);
    const QList<PixelCanvas*> getLayers();
    int getMaxLayers();
    int getEditLayers();
};

#endif // PIXELCANVASLAYERS_H
