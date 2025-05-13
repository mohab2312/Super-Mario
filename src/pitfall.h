#ifndef PITFALL_H
#define PITFALL_H

#include <QGraphicsRectItem>
#include <QPen>
#include <QBrush>

class Pitfall : public QGraphicsRectItem {
public:
    Pitfall(int x, int y, int width, int height);
};

#endif // PITFALL_H
