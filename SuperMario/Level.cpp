#include "Level.h"
#include "Mario.h"
#include "Coin.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Platform.h"
#include "PowerUp.h"
#include "PrincessPeach.h"
#include "Player.h"
#include <QFont>

using namespace std;

Level::Level() : QGraphicsScene() {

    setSceneRect(0, 0, 800, 600);

    player = nullptr;
    scoreText = nullptr;
    healthText = nullptr;
    coinText = nullptr;
    startText = nullptr;
    timer = nullptr;


    startText = addText("Press Enter to Start");
    startText->setDefaultTextColor(Qt::white);
    startText->setFont(QFont("Arial", 20));

    startText->setPos(width()/2 - startText->boundingRect().width()/2,
                      height()/2 - startText->boundingRect().height()/2);


    player = new Player();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    addItem(player);

    player->setPos(50, 536);
    scoreText = addText("Score: 0");
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setFont(QFont("Arial", 16));
    scoreText->setPos(10, 10);

    healthText = addText("Health: 0");
    healthText->setDefaultTextColor(Qt::white);
    healthText->setFont(QFont("Arial", 16));
    healthText->setPos(10, 30);

    coinText = addText("Coins: 0");
    coinText->setDefaultTextColor(Qt::white);
    coinText->setFont(QFont("Arial", 16));
    coinText->setPos(10, 50);


    updateHUD();
}

void Level::startGame() {

    if (startText) {
        removeItem(startText);
        delete startText;
        startText = nullptr;
    }


    for (int x = 0; x < 800; x += 64) {
        Platform* ground = new Platform();
        ground->setPos(x, 568);
        addItem(ground);
    }

    Platform* plat1 = new Platform();
    plat1->setPos(200, 400);
    addItem(plat1);
    Platform* plat2 = new Platform();
    plat2->setPos(300, 300);
    addItem(plat2);


    Coin* coin1 = new Coin();
    coin1->setPos(220, 370);
    addItem(coin1);
    Coin* coin2 = new Coin();
    coin2->setPos(320, 270);
    addItem(coin2);


    Enemy* enemy1 = new Enemy();
    enemy1->setPos(600, 536);
    addItem(enemy1);


    Obstacle* obs1 = new Obstacle();
    obs1->setPos(400, 536);
    addItem(obs1);


    PowerUp* power = new PowerUp();
    power->setPos(250, 368);
    addItem(power);


    PrincessPeach* princess = new PrincessPeach();
    princess->setPos(700, 536);
    addItem(princess);


    player->setPos(50, 536);
    player->setFocus();


    if (!timer) {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Level::updateGame);
    }
    timer->start(16);
}

void Level::updateHUD() {
    if (!player) return;

    scoreText->setPlainText(QString("Score: %1").arg(player->getScore()));
    healthText->setPlainText(QString("Health: %1").arg(player->getHealth()));
    coinText->setPlainText(QString("Coins: %1").arg(player->getCoins()));
}

void Level::updateGame() {
    if (!player) return;

    player->updateMovement();

    updateHUD();
}

