#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QPixmap>

using namespace std;

Enemy::Enemy() {
    setRect(0, 0, 50, 30);
    setBrush(Qt::NoBrush);
    setPen(Qt::NoPen);
}


void Enemy::onCollide(Player* player) {

    player->decreaseHealth(1);

    if (scene()) {
        scene()->removeItem(this);
    }
    delete this;
}

void Enemy::setDirection(int direction) {
    if (direction < 0) dir = -1;
    else if (direction > 0) dir = 1;
    else dir = 0;
}

int Enemy::direction() const {
    return dir;
}
void Enemy::shoot() {

    Bullet* bullet = new Bullet();
    bullet->setRect(0, 0, 6, 10);
    bullet->setBrush(Qt::cyan);
    bullet->setPos(x() + rect().width()/2 - 3, y() + rect().height());
    bullet->setDirection(Down);
    scene()->addItem(bullet);
}

