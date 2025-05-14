// mainwindow.cpp
#include "mainwindow.h"
#include "Mario.h"
#include "Bullet.h"
#include "Coin.h"
#include "Enemy.h"
#include "Player.h"
#include "mysterybox.h"

#include <QFont>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QColor>
#include <QLabel>
#include <QMessageBox>
#include <QVector>
#include <QRectF>

QList<Enemy*> enemies;
int level = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , score(0)
    , health(3)
    , coins(0)
    , isOnHomeScreen(true)
{
    constexpr int H = Player::SPRITE_SIZE;
    constexpr int groundY1 = 250;
    constexpr int spawnY1  = groundY1 - H;

    // Enemy timer
    QTimer* shootTimer = new QTimer(this);
    connect(shootTimer, &QTimer::timeout, this, [=]() {
        for (Enemy* e : enemies)
            if (scene->items().contains(e))
                e->shoot();
    });
    shootTimer->start(2000);

    // Home scene
    homeScene = new QGraphicsScene(this);
    homeScene->setSceneRect(0,0,800,600);
    homeScene->addPixmap(QPixmap(":/images/Resources/images/background_mario"));
    auto* startText = homeScene->addText("Press ENTER to Start!", QFont("Arial",28,QFont::Bold));
    startText->setDefaultTextColor(Qt::white);
    startText->setPos(200,250);

    view = new QGraphicsView(this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(800,600);
    view->setScene(homeScene);
    setCentralWidget(view);
    view->viewport()->installEventFilter(this);

    // ── Level 1 ──
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,3800,600);
    scene->addPixmap(QPixmap(":/images/Resources/images/level_1.png"));

    // cover
    {
        auto* cover = new QGraphicsRectItem(0,235,4200,600);
        cover->setBrush(QColor("#4C2F27"));
        cover->setZValue(0);
        scene->addItem(cover);
    }

    // ground platform y=250
    {
        auto* plat = new QGraphicsRectItem(0,0,3800,5);
        plat->setPos(0, groundY1);
        plat->setBrush(Qt::red);
        plat->setPen(Qt::NoPen);
        scene->addItem(plat);

        Player::setPlatforms({ QRectF(0,groundY1,3800,5) });
    }

    // Mario (Level 1)
    mario = new Player;
    mario->setZValue(1);
    mario->setPixmap(QPixmap(":/images/Resources/images/m1R.png")
                         .scaled(H,H,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    mario->setPos(30, spawnY1);
    mario->setGroundLevel(groundY1);
    mario->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(mario);
    // no fall‐off connection here

    // HUD
    scoreLabel  = new QLabel("Score: 0", this);
    healthLabel = new QLabel("Health: 3", this);
    coinLabel   = new QLabel("Coins: 0", this);
    for (auto* L : {scoreLabel, healthLabel, coinLabel}) {
        L->setStyleSheet("QLabel { color: white; font: bold 14px; }");
        L->show();
    }
    scoreLabel->move(10,10);
    healthLabel->move(10,30);
    coinLabel->move(10,50);

    // Level 1 coins
    QList<QPointF> coins1 = {
        {655,145},{670,130},{690,130},{705,145},
        {1683,97},{1698,97},{1713,97},{1728,97},
        {1905,97},{1920,97},{1935,97},{1950,97},
        {2162,97},{2177,97},{2192,97},{2207,97}
    };
    for (auto& p : coins1) {
        auto* c = new Coin();
        c->setBrush(Qt::transparent);
        c->setPen(Qt::NoPen);
        c->setPos(p);
        scene->addItem(c);
    }

    // Level 1 mystery boxes
    QList<QPointF> boxes1 = {
        {400,80},{400,144},{1024,144},{1024,80},
        {1056,80},{1056,144},{1440,144},{1456,144},
        {1472,144},{1488,144},{2448,144},{2432,144},
        {2416,144},{2351,144},{2367,144},{2335,144},
        {2368,80},{2384,80},{2400,80},{2416,80}
    };
    for (auto& p : boxes1) {
        auto* b = new MysteryBox();
        b->setBrush(Qt::transparent);
        b->setPen(Qt::NoPen);
        b->setPos(p);
        scene->addItem(b);
    }

    // Level 1 enemies
    QList<QPointF> enemies1 = {
        {130,45},{310,35},{450,45},{590,35},
        {900,45},{1080,15},{1220,45},{1360,35}
    };
    for (auto& p : enemies1) {
        auto* e = new Enemy();
        e->setPos(p);
        scene->addItem(e);
        enemies.append(e);
    }

    // game loop
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateGame);
}

MainWindow::~MainWindow() {}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (isOnHomeScreen &&
        (event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter))
    {
        view->setScene(scene);
        mario->setFocus();
        mario->setGameStarted(true);
        gameTimer->start(16);
        isOnHomeScreen = false;
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (obj==view->viewport() && event->type()==QEvent::MouseButtonPress) {
        if (!isOnHomeScreen && mario) mario->setFocus();
    }
    return QMainWindow::eventFilter(obj,event);
}

void MainWindow::restartGame() {
    constexpr int H = Player::SPRITE_SIZE;
    constexpr int groundY1 = 250;
    constexpr int spawnY1  = groundY1 - H;

    scene->clear();
    enemies.clear();
    score = coins = 0;
    health = 3;
    scoreLabel->setText("Score: 0");
    coinLabel->setText("Coins: 0");
    healthLabel->setText("Health: 3");

    scene->addPixmap(QPixmap(":/images/Resources/images/level_1.png"));
    {
        auto* cover = new QGraphicsRectItem(0,235,4200,600);
        cover->setBrush(QColor("#4C2F27"));
        cover->setZValue(0);
        scene->addItem(cover);
    }

    // ground platform
    {
        auto* plat = new QGraphicsRectItem(0,0,3800,5);
        plat->setPos(0, groundY1);
        plat->setBrush(Qt::red);
        plat->setPen(Qt::NoPen);
        scene->addItem(plat);
        Player::setPlatforms({ QRectF(0,groundY1,3800,5) });
    }

    // reset Mario
    mario = new Player;
    mario->setZValue(1);
    mario->setPixmap(QPixmap(":/images/Resources/images/m1R.png")
                         .scaled(H,H,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    mario->setPos(30, spawnY1);
    mario->setGroundLevel(groundY1);
    mario->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(mario);
    mario->setFocus();
    mario->setGameStarted(true);

    // re-add coins, boxes, enemies same as constructor...

    gameTimer->start(16);
}

void MainWindow::handlePlayerDeath() {
    gameTimer->stop();
    QMessageBox::information(this,"Game Over","You lost the game!");
    restartGame();
}


void MainWindow::updateGame()
{
    mario->updateMovement();
    view->centerOn(mario);
    QList<MysteryBox*> boxesToRemove;

    QList<QGraphicsItem*> allItems = scene->items();
    QList<Coin*> coinsToRemove;

    for (QGraphicsItem* item : allItems) {
        Coin* coin = dynamic_cast<Coin*>(item);
        if (!coin) continue;

        QList<QGraphicsItem*> colliding = coin->collidingItems();
        for (QGraphicsItem* obj : colliding) {
            Player* player = dynamic_cast<Player*>(obj);
            if (player) {
                coinsToRemove.append(coin);
                coins++;
                break;
            }
        }
    }

    for (QGraphicsItem* item : allItems) {
        MysteryBox* box = dynamic_cast<MysteryBox*>(item);
        if (!box) continue;

        QList<QGraphicsItem*> colliding = box->collidingItems();
        for (QGraphicsItem* obj : colliding) {
            Player* player = dynamic_cast<Player*>(obj);
            if (player) {
                boxesToRemove.append(box);
                score += 10;
                break;
            }
        }
    }

    for (Coin* coin : coinsToRemove) {
        QGraphicsRectItem* skyBlueRect = new QGraphicsRectItem(0, 0, 15, 15);
        skyBlueRect->setPos(coin->pos());
        skyBlueRect->setZValue(0);
        QImage bgImage(":/images/Resources/images/level_1.png");
        QColor skyColor = bgImage.pixelColor(10, 10);
        skyBlueRect->setBrush(QBrush(skyColor));
        skyBlueRect->setPen(QPen(Qt::NoPen));
        scene->addItem(skyBlueRect);

        scene->removeItem(coin);
        coin->deleteLater();
    }

    for (MysteryBox* box : boxesToRemove) {
        QGraphicsRectItem* skyBlueRect = new QGraphicsRectItem(0, 0, 16, 16);
        skyBlueRect->setPos(box->pos());
        skyBlueRect->setZValue(0);
        QImage bgImage(":/images/Resources/images/level_1.png");
        QColor skyColor = bgImage.pixelColor(10, 10);
        skyBlueRect->setBrush(QBrush(skyColor));
        skyBlueRect->setPen(QPen(Qt::NoPen));
        scene->addItem(skyBlueRect);

        scene->removeItem(box);
        box->deleteLater();
    }


    health = mario->getHealth();

    scoreLabel->setText("Score: " + QString::number(score));
    coinLabel->setText("Coins: " + QString::number(coins));
    healthLabel->setText("Health: " + QString::number(health));

    for (QGraphicsItem* item : allItems) {
        Bullet* bullet = dynamic_cast<Bullet*>(item);
        if (!bullet) continue;

        bullet->moveBy(0, 5);

        if (bullet->y() >= 205) {
            scene->removeItem(bullet);
            delete bullet;
            continue;
        }

        QList<QGraphicsItem*> collidingItems = bullet->collidingItems();
        for (QGraphicsItem* colliding : collidingItems) {
            Player* player = dynamic_cast<Player*>(colliding);
            if (player) {
                player->decreaseHealth(1);
                health = player->getHealth();

                if (player->playerDied()) {
                    gameTimer->stop();
                    qDebug() << "Game over!";
                    QMessageBox::information(this, "Game Over", "You lost the game!");
                    restartGame();
                    return;
                }

                scene->removeItem(bullet);
                delete bullet;
                break;
            }
        }
    }

    if (mario->x() >= 3600) {
        gameTimer->stop();
        level = 2;
        QMessageBox::information(this, "Level Complete", "🎉 Congratulations! You've passed Level 1, continue to level 2!");

        // Clear current scene
        scene->clear();
        enemies.clear();

        // Reset score, coins, and health for the new level
        score = 0;
        coins = 0;
        health = 3;

        scoreLabel->setText("Score: 0");
        coinLabel->setText("Coins: 0");
        healthLabel->setText("Health: 3");

        // Create the Level 2 scene
        QGraphicsScene* level2Scene = new QGraphicsScene(this);
        level2Scene->setSceneRect(0, 0, 3800, 600);
        level2Scene->addPixmap(QPixmap(":/images/level_2.png"));

        // Add bottom cover to the new level scene
        QGraphicsRectItem* level2BottomCover = new QGraphicsRectItem(0, 235, 4200, 600);
        level2BottomCover->setBrush(QColor("#4C2F27"));
        level2BottomCover->setZValue(0);
        level2Scene->addItem(level2BottomCover);

        // Set the scene to the new level 2 scene
        view->setScene(level2Scene);

        // Recreate Mario for Level 2 and set starting position
        mario = new Player();
        QPixmap marioPixmap(":/images/m1R.png");
        mario->setZValue(1);
        mario->setPixmap(marioPixmap.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        mario->setPos(30, 155); // Starting position for Mario in Level 2
        mario->setFlag(QGraphicsItem::ItemIsFocusable);

        // Add Mario to the Level 2 scene
        level2Scene->addItem(mario);
        mario->setFocus(); // Focus on Mario
        view->centerOn(mario); // Center the view on Mario








        // Start the game timer again for Level 2
        gameTimer->start(16);
        return;
    }

}
