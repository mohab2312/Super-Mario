#include "PowerUp.h"
#include "Player.h"
#include <QGraphicsScene>

using namespace std;

PowerUp::PowerUp() {

    setPixmap(QPixmap(":/images/powerup.png"));
}

void PowerUp::onCollide(Player* player) {

    player->increaseHealth(1);

    if (scene()) {
        scene()->removeItem(this);
    }
    delete this;
}

