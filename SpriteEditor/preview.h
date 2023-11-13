#ifndef PREVIEW_H
#define PREVIEW_H

#include <QObject>
#include <QTimer>
#include <QImage>
#include "pixelcanvaslayers.h"

class Preview : public QObject
{
    Q_OBJECT
    PixelCanvasLayers* target;
    int playbackSpeed;
    int playLoop;
    int playing;
public:
    explicit Preview(QObject *parent = nullptr);

public slots:
    void setPlaybackSpeed(int);
    void startPlayback(int);
    void updatePreview();
    void reload();
private slots:
    void playbackLoop();
signals:
    void updateEditorWindow(const QImage& updateImage, int editingTarget);
    void updateFrameList(QList<QImage>);
    void playback(const QImage&);

};

#endif // PREVIEW_H
