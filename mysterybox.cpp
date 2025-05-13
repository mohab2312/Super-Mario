#include "MysteryBox.h"
#include <QBrush>
#include <QPen>

MysteryBox::MysteryBox() {
    setZValue(1);
    setRect(0, 0,15, 15);
    setBrush(Qt::transparent);
    setPen(QPen(Qt::NoPen));
    setZValue(0);
}
