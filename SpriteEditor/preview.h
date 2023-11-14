#ifndef PREVIEW_H
#define PREVIEW_H

#include <QObject>
#include <QTimer>
#include <QImage>
#include "pixelcanvas.h"

class Preview : public QObject
{
    Q_OBJECT
    int playbackSpeed;
    int playLoop;
    PixelCanvas *target;
public:
    explicit Preview(QObject *parent = nullptr);

public slots:
    void setPlaybackSpeed(int);
    void Playback(int);
    void updatePreview();
private slots:
    void playbackLoop();
signals:
    void updateEditorWindow(const QImage& updateImage, int editingTarget);
    void updateFrameList(QList<QImage>);
    void playback(const QImage&);

};

#endif // PREVIEW_H
