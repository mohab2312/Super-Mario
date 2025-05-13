#ifndef COIN_H
#define COIN_H
#include <QObject>
#include <QGraphicsRectItem>

class Coin : public QGraphicsRectItem, public QObject {
public:
    Coin();
};

#endif
