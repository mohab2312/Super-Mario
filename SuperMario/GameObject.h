#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPixmapItem>


class Player;

class GameObject : public QGraphicsPixmapItem {
public:
    GameObject();
    virtual ~GameObject() {}

    virtual void onCollide(Player* player);
};

#endif

