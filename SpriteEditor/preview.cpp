#include "preview.h"

Preview::Preview(QObject *parent)
    : QObject{parent}
{
    playbackSpeed = 0;
    playLoop = 0;
}

void Preview::setPlaybackSpeed(int speed)
{
    playbackSpeed = speed;
}
void Preview::Playback(int play)
{
    if(play == 0) {
        return;
    } else {
        playbackLoop();
    }
}
void Preview::playbackLoop()
{
    target->getPlaybackImage(playLoop);
    //emit playback();
    playLoop++;
    if(playLoop == target->getMaxLayers())
        playLoop = 0;
    QTimer::singleShot(1000/playbackSpeed, this, SLOT(playbackLoop));
}

void Preview::updatePreview()
{
    emit updateEditorWindow(target->getEditingImage(), target->getEditLayers());
}
