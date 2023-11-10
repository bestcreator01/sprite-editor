#ifndef ANIMATE_H
#define ANIMATE_H

#include <QObject>

class Animate : public QObject
{
    Q_OBJECT
public:
    explicit Animate(QObject *parent = nullptr);

signals:

};

#endif // ANIMATE_H
