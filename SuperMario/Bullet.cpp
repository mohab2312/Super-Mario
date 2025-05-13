#include"Bullet.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <enemy.h>
#include <player.h>

Bullet::Bullet(): QObject(), QGraphicsRectItem() {
    setRect(0,0,10,20);
    QPen redPen(Qt::red);
    redPen.setWidth(3);
    QBrush redBrush(Qt::red);
    setPen(redPen);
    setBrush(redBrush);

    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50);
}

void Bullet::move() {

    setPos(x(), y() + 10);

    if(pos().y() > scene()->height()) {
        scene()->removeItem(this);
        delete this;
        return;
    }


    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (QGraphicsItem* item : colliding_items) {
        if (Player* player = dynamic_cast<Player*>(item)) {
            player->decreaseHealth(1);
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
}
void Bullet::setDirection(Direction d) {
    direction = d;
}

Direction Bullet::getDirection() const {
    return direction;
}


