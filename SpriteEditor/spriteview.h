#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteView; }
QT_END_NAMESPACE

class SpriteView : public QMainWindow
{
    Q_OBJECT
    int sizeOfCanvas = 32;
    int pixelSize = 20;
    int offsetSize = -20;

public:
    SpriteView(QWidget *parent = nullptr);
    ~SpriteView();

private:
    Ui::SpriteView *ui;
    void paintEvent(QPaintEvent *);
};
#endif // SPRITEVIEW_H
