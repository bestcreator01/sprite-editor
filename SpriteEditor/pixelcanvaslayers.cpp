#include "pixelcanvaslayers.h"
#include <QDebug>

PixelCanvasLayers::PixelCanvasLayers(QObject* parent) : QObject(parent)
{
    height = 16;
    width = 16;
    maxLayer = 1;
    editLayer = 0;
    layers = QList<PixelCanvas*>(maxLayer);
    layers[editLayer] = new PixelCanvas(height, width);
}

PixelCanvasLayers::PixelCanvasLayers(int height, int width)
{
    this->height = height;
    this->width = width;
    maxLayer = 1;
    editLayer = 0;
    layers = QList<PixelCanvas*>(maxLayer);
    layers[editLayer] = new PixelCanvas(height, width);
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
    PixelCanvas *newCanvas = new PixelCanvas(height, width);
    layers.push_back(newCanvas);
    maxLayer++;
    editLayer = maxLayer - 1;
}

void PixelCanvasLayers::moveLayer(int go, int to){
    PixelCanvas *temp = layers[go];
    for(int i = go; i < to; i++)
        layers[i] = layers[i+1];
    layers[to] = temp;
}

void PixelCanvasLayers::setEditLayer(int index)
{
    editLayer = index;
}

const QImage& PixelCanvasLayers::getPlaybackImage(int FrameIndex)
{
    return layers[FrameIndex]->getImage();
}

const QImage& PixelCanvasLayers::getEditingImage()
{
    return layers[editLayer]->getImage();
}

PixelCanvas& PixelCanvasLayers::getCurrentLayer()
{
    return *layers[editLayer];
}

void PixelCanvasLayers::setMax(int max)
{
    maxLayer = max;
}

const QList<PixelCanvas*> PixelCanvasLayers::getLayers()
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

