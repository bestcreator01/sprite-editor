#include "preview.h"

Preview::Preview(QObject *parent)
    : QObject{parent}
{
    playbackSpeed = 0;
    playLoop = 0;
}

void Preview::updateChangesOnCanvas()
{
    // TODO: access to the layer which needs an update

    // TODO: needs to update the stack of drawingTools as well (for undo/redo)
}

void Preview::setPlaybackSpeed(int speed)
{
    playbackSpeed = speed;
}
void Preview::startPlayback(int play)
{
    if(play && !playing){
        playing = true;
        playbackLoop();
    }else
        playing = play;
}
void Preview::playbackLoop()
{
    if(!playing)
        return;
    emit playback(target->getPlaybackImage(playLoop));
    playLoop++;
    if(playLoop == target->getMaxLayers()){
        playLoop = 0;
    }
    QTimer::singleShot(1000/playbackSpeed, this, [=](){ emit playbackLoop(); });
}

void Preview::updatePreview()
{
    emit updateEditorWindow(target->getEditingImage(), target->getEditLayers());
}

void Preview::reload()
{
    QList<QImage> icons;
    for(int i = 0; i < target->getLayers().size();i++){
        icons.append(target->getLayers()[i]->getImage());
    }
    emit updateFrameList(icons);
}
