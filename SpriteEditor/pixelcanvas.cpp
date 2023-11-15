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
    // delete the layer
    delete layers[editLayer];
    layers.erase(layers.begin() + editLayer);
    maxLayer--;

    // set the edit Layer to be the max Layer
    if(editLayer == maxLayer)
        editLayer = maxLayer-1;

    emit updateCanvas(getEditingImage());
}

void PixelCanvas::addLayer()
{
    // create a new layer
    QImage *newCanvas = new QImage(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    newCanvas->fill(qRgba(0,0,0,0));

    // add it to a layers list
    layers.push_back(newCanvas);

    // ??
    maxLayer++;
    editLayer = maxLayer - 1;

    emit updateCanvas(getEditingImage());
}

void PixelCanvas::setEditLayer(int index)
{
    // retrieve the index of the layer you are editing
    editLayer = index;
    if (playbackSpeed == 0)
        emit updateCanvas(getEditingImage());
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
        layer->fill(qRgba(0,0,0,0));
}

void PixelCanvas::setSpeed(int speed)
{
    playbackSpeed = speed;
    // flags are for stoping the previous fps speed
    flag ? flag = false : flag = true;
}

void PixelCanvas::playback(int play)
{
    if (play == 0)
    {
        return;
    }
    playbackLoop();
}

void PixelCanvas::playbackLoop()
{
    // Base Cases: stop animation if speed is 0
    if (playbackSpeed == 0)
    {
        emit updateCanvas(getEditingImage());
        return;
    }
    // stop previous animation
    if(flag)
    {
        flag = false;
        return;
    }
    emit sendPlayback(*layers[playLoop]);
    playLoop++;

    // goes back to the first layer
    if(playLoop == maxLayer)
    {
        playLoop = 0;
    }

    QTimer::singleShot(1000/playbackSpeed, this, [=](){emit playbackLoop();});

}

void PixelCanvas::getLayers()
{
    emit allLayers(layers);
}

void PixelCanvas::layerCount()
{
    emit layersCount(layers.count());
}

