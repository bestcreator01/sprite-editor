#ifndef SPRAY_H
#define SPRAY_H

#include <QObject>
#include <QPoint>

class Spray
{
    int r, g, b;
public:
    Spray();

public slots:
    void updatePixels(QPoint point, int r, int g, int b);
};

#endif // SPRAY_H
