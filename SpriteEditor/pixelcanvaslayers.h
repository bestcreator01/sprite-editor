#ifndef PIXELCANVASLAYERS_H
#define PIXELCANVASLAYERS_H

#include <QObject>
#include <QList>
#include "pixelcanvas.h"

class PixelCanvasLayers : public QObject
{
    Q_OBJECT
    QList<PixelCanvas> layers;

public:
    explicit PixelCanvasLayers(QObject *parent = nullptr);

signals:
    void updatePreview();

public slots:
    void deleteLayer();
    void addLayer();
    void updateChangesOnCanvas();

};

#endif // PIXELCANVASLAYERS_H
