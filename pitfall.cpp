#include "Pitfall.h"

Pitfall::Pitfall(int x, int y, int width, int height)
    : QGraphicsRectItem(x, y, width, height) // Call base constructor properly
{
    setZValue(-1);
    setBrush(QBrush(Qt::red));
    setPen(QPen(Qt::NoPen));
}
