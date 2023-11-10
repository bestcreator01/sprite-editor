#ifndef PIXELCANVASLAYERS_H
#define PIXELCANVASLAYERS_H

#include <QObject>
#include <QList>
#include <pixelcanvas.h>

class PixelCanvasLayers
{
    QList<PixelCanvas> layers;

public:
    PixelCanvasLayers();

public slots:
    void deleteLayer();
    void addLayer();
    void updatePreview();
};

#endif // PIXELCANVASLAYERS_H
