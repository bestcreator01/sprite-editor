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
void Preview::Playback(int play, QList<QImage *> layers)
{
    if(play == 0) {
        return;
    } else {
        playbackLoop(layers);
    }
}
void Preview::playbackLoop(QList<QImage *> layers)
{
    emit playback(*layers[playLoop]);
    playLoop++;
    if(playLoop == layers.size() - 1)
        playLoop = 0;
    QTimer::singleShot(1000/playbackSpeed, this, SLOT(playbackLoop));
}

//void Preview::updatePreview()
//{
//    emit updateEditorWindow(target->getEditingImage(), target->getEditLayers());
//}
