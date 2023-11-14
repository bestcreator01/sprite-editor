#ifndef PREVIEW_H
#define PREVIEW_H

#include <QObject>
#include <QTimer>
#include <QImage>

class Preview : public QObject
{
    Q_OBJECT
    int playbackSpeed;
    int playLoop;
public:
    explicit Preview(QObject *parent = nullptr);

public slots:
    void setPlaybackSpeed(int);
    void Playback(int, QList<QImage *>);
    //void updatePreview();
private slots:
    void playbackLoop(QList<QImage *>);
signals:
    //void updateEditorWindow(const QImage& updateImage, int editingTarget);
    //void updateFrameList(QList<QImage>);
    void playback(const QImage&);

};

#endif // PREVIEW_H
