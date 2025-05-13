#include "PrincessPeach.h"
#include "Player.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QFont>

using namespace std;

PrincessPeach::PrincessPeach() {

    setPixmap(QPixmap(":/images/princess.png"));
}

void PrincessPeach::onCollide(Player* player) {

    if (scene()) {

        QGraphicsTextItem* msg = scene()->addText("Level Complete!");
        msg->setDefaultTextColor(Qt::yellow);
        msg->setFont(QFont("Arial", 24));

        msg->setPos(player->x(), player->y() - 50);
    }

}
