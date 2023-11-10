#include "pixelcanvaslayers.h"

PixelCanvasLayers::PixelCanvasLayers(QObject* parent) : QObject(parent) {}

void PixelCanvasLayers::deleteLayer()
{

}

void PixelCanvasLayers::addLayer()
{
//    PixelCanvas newCanvas;
//    layers.push_back(newCanvas);
}

void PixelCanvasLayers::updateChangesOnCanvas()
{
    // TODO: access to the layer which needs an update

    // TODO: needs to update the stack of drawingTools as well (for undo/redo)

    // update the preview
    emit updatePreview();
}
