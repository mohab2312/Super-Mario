#ifndef PRINCESSPEACH_H
#define PRINCESSPEACH_H

#include "GameObject.h"

class PrincessPeach : public GameObject {
public:
    PrincessPeach();
    void onCollide(Player* player) override;
};

#endif
