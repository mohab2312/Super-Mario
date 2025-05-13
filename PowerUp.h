#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"
using namespace std;

class PowerUp : public GameObject {
public:
    PowerUp();
    void onCollide(Player* player) override;
};

#endif
