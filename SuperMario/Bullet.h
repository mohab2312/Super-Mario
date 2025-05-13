#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>
#include <QObject>

enum Direction { Left, Right, Up, Down };
class Bullet: public QObject, public QGraphicsRectItem
{

    Q_OBJECT
public:
    Bullet();
    void setDirection(Direction d);
    Direction getDirection() const;
public slots:
    void move();
private:
    Direction direction;
};

#endif
