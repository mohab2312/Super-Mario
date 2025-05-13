#include "Coin.h"
#include <QBrush>
#include <QPen>

Coin::Coin() {
    setZValue(1);
    setRect(0, 0, 15, 15);
    setBrush(Qt::transparent);
    setPen(QPen(Qt::NoPen));
}
