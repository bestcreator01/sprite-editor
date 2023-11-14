#include "pixelcanvas.h"
#include <QDebug>

PixelCanvas::PixelCanvas(QObject* parent) : QObject(parent)
{
    maxLayer = 1;
    editLayer = 0;
    playbackSpeed = 0;
    playLoop = 0;
    layers = QList<QImage*>(maxLayer);
    layers[editLayer] = new QImage(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    layers[editLayer]->fill(qRgba(0,0,0,0));
}

PixelCanvas::~PixelCanvas()
{
    for(int i = 0; i < maxLayer; i++)
        delete layers[i];
}

void PixelCanvas::deleteLayer()
{
    delete layers[editLayer];
    layers.erase(layers.begin() + editLayer);
    maxLayer--;
    if(editLayer == maxLayer)
        editLayer = maxLayer-1;
    emit updateCanvas(getEditingImage());
}

void PixelCanvas::addLayer()
{
    QImage *newCanvas = new QImage(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    newCanvas->fill(qRgba(0,0,0,0));
    layers.push_back(newCanvas);
    maxLayer++;
    editLayer = maxLayer - 1;
    emit updateCanvas(getEditingImage());
}

void PixelCanvas::setEditLayer(int index)
{
    editLayer = index;
    emit updateCanvas(getEditingImage());
}

const QImage& PixelCanvas::getPlaybackImage(int FrameIndex)
{
    return *layers[FrameIndex];
}

QImage& PixelCanvas::getEditingImage()
{
    return *layers[editLayer];
}

void PixelCanvas::updatePixel(int x, int y, int color, int tool)
{
    emit updatePixelsByTools(getEditingImage(), x, y, color, tool);
    emit updateCanvas(getEditingImage());
}

void PixelCanvas::clearImage()
{
    for(auto layer:layers)
    {
        layer->fill(qRgba(0,0,0,0));
    }
}

void PixelCanvas::setMax(int max)
{
    maxLayer = max;
}

void PixelCanvas::Playback(int play)
{
    if(play == 0) {
        return;
    } else {
        playbackLoop();
    }
}
void PixelCanvas::playbackLoop()
{
    if (playbackSpeed == 0) {
        return;
    }
    emit playback(*layers[playLoop]);
    playLoop++;
    if(playLoop == maxLayer)
        playLoop = 0;
    QTimer::singleShot(1000/playbackSpeed, this, [=](){emit playbackLoop();});
}

void PixelCanvas::setSpeed(int speed)
{
   playbackSpeed = speed;
}

const QList<QImage*> PixelCanvas::getLayers()
{
    return layers;
}

int PixelCanvas::getMaxLayers()
{
    return maxLayer;
}

int PixelCanvas::getEditLayers()
{
    return editLayer;
}

