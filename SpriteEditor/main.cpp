#include "spriteview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpriteView w;
    w.show();
    return a.exec();
}
