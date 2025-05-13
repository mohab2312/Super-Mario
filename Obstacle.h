#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"
using namespace std;

class Obstacle : public GameObject {
public:
    Obstacle();
    void onCollide(Player* player) override;
};

#endif
