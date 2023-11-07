#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SpriteView; }
QT_END_NAMESPACE

class SpriteView : public QMainWindow
{
    Q_OBJECT

public:
    SpriteView(QWidget *parent = nullptr);
    ~SpriteView();

private:
    Ui::SpriteView *ui;
};
#endif // SPRITEVIEW_H
