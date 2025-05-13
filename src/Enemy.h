#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>

class Player;

class Enemy : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Enemy();
    void onCollide(Player* player);
    void setDirection(int direction);
    int direction() const;
    void shoot();

private:
    int dir;
};

#endif
