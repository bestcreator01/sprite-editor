#include "pixelcanvaslayers.h"

#include <QDebug>

PixelCanvasLayers::PixelCanvasLayers(QObject* parent) : QObject(parent)
{
    maxLayer = 1;
    editLayer = 0;
    layers = QList<QImage*>(maxLayer);
    layers[editLayer] = new QImage(32, 32, QImage::Format_ARGB32);
    layers[editLayer]->fill(qRgba(0,0,0,0));
}

PixelCanvasLayers::~PixelCanvasLayers()
{
    for(int i = 0; i < maxLayer; i++)
        delete layers[i];
}

void PixelCanvasLayers::deleteLayer()
{
    moveLayer(editLayer, maxLayer-1);
    delete layers[maxLayer-1];
    layers.pop_back();
    maxLayer--;
    if(editLayer == maxLayer)
        editLayer = maxLayer-1;
}

void PixelCanvasLayers::addLayer()
{
    QImage *newCanvas = new QImage(32, 32, QImage::Format_ARGB32);
    newCanvas->fill(qRgba(0,0,0,0));

    layers.push_back(newCanvas);
    maxLayer++;
    editLayer = maxLayer - 1;
    emit updateCanvas(getEditingImage());
}

void PixelCanvasLayers::moveLayer(int go, int to){
    QImage *temp = layers[go];
    for(int i = go; i < to; i++)
        layers[i] = layers[i+1];
    layers[to] = temp;
}

void PixelCanvasLayers::setEditLayer(int index)
{
    editLayer = index;
    emit updateCanvas(getEditingImage());
}

const QImage& PixelCanvasLayers::getPlaybackImage(int FrameIndex)
{
    return *layers[FrameIndex];
}

QImage& PixelCanvasLayers::getEditingImage()
{
    return *layers[editLayer];
}

void PixelCanvasLayers::updatePixel(int x, int y, int color, int tool)
{
    d.updatePixels(getEditingImage(), x, y, color, tool);
    emit updateCanvas(getEditingImage());
}

void PixelCanvasLayers::setMax(int max)
{
    maxLayer = max;
}

const QList<QImage*> PixelCanvasLayers::getLayers()
{
    return layers;
}

int PixelCanvasLayers::getMaxLayers()
{
    return maxLayer;
}

int PixelCanvasLayers::getEditLayers()
{
    return editLayer;
}

