#include "pixelcanvas.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

PixelCanvas::PixelCanvas(QObject* parent) : QObject(parent)
{
    maxLayer = 1;
    editLayer = 0;
    fpsSpeed = 0;
    playLoop = 0;
    layers = QList<QImage*>(maxLayer);
    QImage *image = new QImage(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    layers[editLayer] = image;
    layers[editLayer]->fill(qRgba(0,0,0,0));
    resetUndoRedo(*image);
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



    emit updateCanvas(getEditingImage(), fpsSpeed);
}

void PixelCanvas::addLayer()
{
    // create a new layer
    QImage *newCanvas = new QImage(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    newCanvas->fill(qRgba(0,0,0,0));

    // add it to a layers list
    layers.push_back(newCanvas);

    // gets the size of layers
    maxLayer++;
    editLayer = maxLayer - 1;

    emit updateCanvas(getEditingImage(), fpsSpeed);
}

void PixelCanvas::setEditLayer(int index)
{
    // retrieve the index of the layer you are editing
    editLayer = index;
    emit updateCanvas(getEditingImage(), fpsSpeed);
}

QImage& PixelCanvas::getEditingImage()
{
    return *layers[editLayer];
}

void PixelCanvas::setEditingImage(QImage image)
{
    layers[editLayer] = new QImage(image.copy());
}

void PixelCanvas::redo(bool& enable, QImage &image)
{
    historyPointer++;

    if(historyPointer >= history.size() - 1){
        enable = false;
    }

    if(historyPointer >= history.size()){
        historyPointer = history.size() - 1;
    }
    image = history[historyPointer];
    setEditingImage(image);
}

void PixelCanvas::undo(bool& enable, QImage &image)
{
    if(historyPointer <= 1){
        enable = false;
    }
    historyPointer--;

    if(historyPointer < 0){
        historyPointer = 0;
    }
    image = history[historyPointer];
    setEditingImage(image);
}

void PixelCanvas::resetUndoRedo(QImage image)
{
    history.clear();
    historyPointer = 0;
    history.append(image);
}

void PixelCanvas::clearUndoBuffer(QImage image)
{
    while (history.size() > historyPointer+1)
    {
        history.removeAt(historyPointer+1);
    }
    // Append image after the user releases the mouse
    history.append(image);
    historyPointer++;
}


void PixelCanvas::updatePixel(int x, int y, int color, int tool)
{

    emit updatePixelsByTools(getEditingImage(), x, y, color, tool);
    emit updateCanvas(getEditingImage(), fpsSpeed);
}

void PixelCanvas::clearImage()
{
    for(auto layer:layers)
    {
        layer->fill(qRgba(0,0,0,0));
    }
}

void PixelCanvas::setSpeed(int speed)
{
    fpsSpeed = speed;
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
    if (fpsSpeed == 0)
    {
        emit updateCanvas(getEditingImage(), fpsSpeed);
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

    QTimer::singleShot(1000/fpsSpeed, this, [=](){emit playbackLoop();});

}

void PixelCanvas::getLayers()
{
    emit allLayers(layers);
}

void PixelCanvas::layerCount()
{
    emit layersCount(layers.count());
}

void PixelCanvas::createJSON()
{
    QJsonObject PixelCanvas;
    QJsonObject Frames;

    Frames.insert("LayerCount", layers.count());
    Frames.insert("FPS", fpsSpeed);

    QJsonArray Layers;
    QJsonArray layer;

    QJsonObject currentLayer;
    QJsonObject layerValues;

    QString currentLayerLabel = "Layer";

    for (int count = 0; count < layers.count(); count++)
    {
        currentLayerLabel += QString::number(count + 1);

        for (int x = 0; x < sizeOfCanvas; x++)
        {
            for (int y = 0; y < sizeOfCanvas; y++)
            {
                layerValues.insert("X", x);
                layerValues.insert("Y", y);

                QImage currentImage = *layers[count];
                QRgb color = currentImage.pixel(x, y);

                layerValues.insert("r", qRed(color));
                layerValues.insert("g", qGreen(color));
                layerValues.insert("b", qBlue(color));
                layerValues.insert("a", qAlpha(color));

                layer.push_back(layerValues);
            }
        }
        currentLayer.insert(currentLayerLabel, layer);
        currentLayerLabel = "Layer";
        layer = QJsonArray();
    }
    Layers.push_back(currentLayer);
    Frames.insert("Layers", Layers);
    PixelCanvas.insert("Frames", Frames);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(PixelCanvas);

    emit populatedJSON(jsonDoc);
}

void PixelCanvas::loadJson(QJsonDocument jsonDoc)
{
    layers.clear();
    maxLayer = 1;
    editLayer = 0;
    layers = QList<QImage*>(maxLayer);
    layers[editLayer] = new QImage(sizeOfCanvas, sizeOfCanvas, QImage::Format_ARGB32);
    layers[editLayer]->fill(qRgba(0,0,0,0));

    QJsonObject pixelCanvas = jsonDoc.object();

    QJsonObject framesObject = pixelCanvas.value("Frames").toObject();

    int layerCount = framesObject.value("LayerCount").toInt();
    int fps = framesObject.value("FPS").toInt();
    emit updateFPS(fps);

    QJsonArray layersArray = framesObject.value("Layers").toArray();

    QList<QImage> icons;
    QJsonObject layerObject = layersArray[0].toObject();

    for (int i = 0; i < layerCount - 1; i++)
    {
        addLayer();
    }

    QStringList keys = layerObject.keys();
    for (int j = 0; j < layerCount; j++)
    {
        QJsonArray pixelArray = layerObject.value(keys[j]).toArray();

        for (int k = 0; k < pixelArray.size(); ++k)
        {
            QJsonObject pixelObject = pixelArray[k].toObject();
            int x = pixelObject.value("X").toInt();
            int y = pixelObject.value("Y").toInt();
            int r = pixelObject.value("r").toInt();
            int g = pixelObject.value("g").toInt();
            int b = pixelObject.value("b").toInt();
            int a = pixelObject.value("a").toInt();

            layers.at(j)->setPixel(x, y, QColor(r, g, b, a).rgba());
        }

        icons.push_back(*layers.at(j));

    }
    emit sendLayerIndex(layerCount - 1);
    emit sendQIcons(icons);
}


