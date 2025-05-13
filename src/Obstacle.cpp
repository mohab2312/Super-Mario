#include "Obstacle.h"
#include "Player.h"
using namespace std;

Obstacle::Obstacle() {

    setPixmap(QPixmap(":/images/obstacle.png"));
}

void Obstacle::onCollide(Player* player) {

    player->decreaseHealth(1);

}
