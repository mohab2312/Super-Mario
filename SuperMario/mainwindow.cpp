#include "mainwindow.h"
#include "Mario.h"
#include "Bullet.h"
#include "Coin.h"
#include "Enemy.h"
#include "Player.h"
#include <QFont>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include "mysterybox.h"
#include <QRandomGenerator>

QList<Enemy*> enemies;
int level = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , score(0)
    , health(3)
    , coins(0)
    , isOnHomeScreen(true)
{
    // Enemy shoot timer
    QTimer* shootTimer = new QTimer(this);
    connect(shootTimer, &QTimer::timeout, this, [=]() {
        for (Enemy* enemy : enemies) {
            if (scene->items().contains(enemy)) {
                enemy->shoot();
            }
        }
    });
    shootTimer->start(2000);

    // Home screen
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

    // Game scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,3800,600);
    scene->addPixmap(QPixmap(":/images/Resources/images/level_1.png"));
    QGraphicsRectItem* bottomCover = new QGraphicsRectItem(0,235,4200,600);
    bottomCover->setBrush(QColor("#4C2F27"));
    bottomCover->setZValue(0);
    scene->addItem(bottomCover);

    // Player
    mario = new Player;
    mario->setZValue(1);
    mario->setPixmap(
        QPixmap(":/images/Resources/images/m1R.png")
            .scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)
        );
    mario->setPos(30,155);
    mario->setGroundLevel(155);
    mario->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->addItem(mario);

    // HUD labels
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setStyleSheet("QLabel { color: white; font: bold 14px; }");
    scoreLabel->move(10,10); scoreLabel->show();
    healthLabel = new QLabel("Health: 3", this);
    healthLabel->setStyleSheet("QLabel { color: white; font: bold 14px; }");
    healthLabel->move(10,30); healthLabel->show();
    coinLabel = new QLabel("Coins: 0", this);
    coinLabel->setStyleSheet("QLabel { color: white; font: bold 14px; }");
    coinLabel->move(10,50); coinLabel->show();

    // Coins (red)
    {
        QList<QPointF> coinPositions = {
            {655,145},{670,130},{690,130},{705,145},
            {1683,97},{1698,97},{1713,97},{1728,97},
            {1905,97},{1920,97},{1935,97},{1950,97},
            {2162,97},{2177,97},{2192,97},{2207,97}
        };
        for (auto& pos : coinPositions) {
            Coin* coin = new Coin();
            coin->setBrush(Qt::red);
            coin->setPen(Qt::NoPen);
            coin->setPos(pos);
            scene->addItem(coin);
        }
    }

    // MysteryBoxes (red)
    {
        QList<QPointF> boxPositions = {
            {400,80},{400,144},{1024,144},{1024,80},
            {1056,80},{1056,144},{1440,144},{1456,144},
            {1472,144},{1488,144},{2448,144},{2432,144},
            {2416,144},{2351,144},{2367,144},{2335,144},
            {2368,80},{2384,80},{2400,80},{2416,80}
        };
        for (auto& pos : boxPositions) {
            MysteryBox* box = new MysteryBox();
            box->setBrush(Qt::red);
            box->setPen(Qt::NoPen);
            box->setPos(pos);
            scene->addItem(box);
        }
    }

    // Enemies
    {
        QList<QPointF> positions = {
            {130,45},{310,35},{450,45},{590,35},
            {900,45},{1080,15},{1220,45},{1360,35}
        };
        for (auto& pos : positions) {
            Enemy* cloud = new Enemy();
            cloud->setPos(pos);
            scene->addItem(cloud);
            enemies.append(cloud);
        }
    }

    // Game-loop timer
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateGame);
}

MainWindow::~MainWindow() {}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
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

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (obj==view->viewport() && event->type()==QEvent::MouseButtonPress) {
        if (!isOnHomeScreen && mario) mario->setFocus();
    }
    return QMainWindow::eventFilter(obj,event);
}

void MainWindow::restartGame()
{
    scene->clear();
    enemies.clear();
    score=0; coins=0; health=3;

    scoreLabel->setText("Score: 0");
    coinLabel->setText("Coins: 0");
    healthLabel->setText("Health: 3");

    scene->addPixmap(QPixmap(":/images/Resources/images/level_1.png"));
    QGraphicsRectItem* bottomCover = new QGraphicsRectItem(0,235,4200,600);
    bottomCover->setBrush(QColor("#4C2F27"));
    bottomCover->setZValue(0);
    scene->addItem(bottomCover);

    // Player
    mario = new Player;
    mario->setZValue(1);
    mario->setPixmap(
        QPixmap(":/images/Resources/images/m1R.png")
            .scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)
        );
    mario->setPos(30,155);
    mario->setGroundLevel(155);
    mario->setFlag(QGraphicsItem::ItemIsFocusable);
    mario->setFocus();
    mario->setGameStarted(true);
    scene->addItem(mario);

    // MysteryBoxes (red)
    {
        QList<QPointF> boxPositions = {
            {400,80},{400,144},{1024,144},{1024,80},
            {1056,80},{1056,144},{1440,144},{1456,144},
            {1472,144},{1488,144},{2448,144},{2432,144},
            {2416,144},{2351,144},{2367,144},{2335,144},
            {2368,80},{2384,80},{2400,80},{2416,80}
        };
        for (auto& pos : boxPositions) {
            MysteryBox* box = new MysteryBox();
            box->setBrush(Qt::red);
            box->setPen(Qt::NoPen);
            box->setPos(pos);
            scene->addItem(box);
        }
    }

    // Coins (red)
    {
        QList<QPointF> coinPositions = {
            {655,145},{670,130},{690,130},{705,145},
            {1683,97},{1698,97},{1713,97},{1728,97},
            {1905,97},{1920,97},{1935,97},{1950,97},
            {2162,97},{2177,97},{2192,97},{2207,97}
        };
        for (auto& pos : coinPositions) {
            Coin* coin = new Coin();
            coin->setBrush(Qt::red);
            coin->setPen(Qt::NoPen);
            coin->setPos(pos);
            scene->addItem(coin);
        }
    }

    // Enemies
    {
        QList<QPointF> positions = {
            {130,45},{310,35},{450,45},{590,35},
            {900,45},{1080,15},{1220,45},{1360,35}
        };
        for (auto& pos : positions) {
            Enemy* cloud = new Enemy();
            cloud->setPos(pos);
            scene->addItem(cloud);
            enemies.append(cloud);
        }
    }

    gameTimer->start(16);
}

void MainWindow::handlePlayerDeath()
{
    gameTimer->stop();
    QMessageBox::information(this,"Game Over","You lost the game!");
    restartGame();
}

void MainWindow::updateGame()
{
    // 1) Physics
    mario->updateMovement();

    // 2) Center view
    view->centerOn(mario);

    // 3) Coin collisions
    {
        auto allItems = scene->items();
        QList<Coin*> coinsToRemove;
        for (auto* item : allItems) {
            if (Coin* coin = dynamic_cast<Coin*>(item)) {
                for (auto* obj : coin->collidingItems()) {
                    if (dynamic_cast<Player*>(obj)) {
                        coinsToRemove.append(coin);
                        coins++;
                        break;
                    }
                }
            }
        }
        for (auto* coin : coinsToRemove) {
            QGraphicsRectItem* rect = new QGraphicsRectItem(0,0,15,15);
            rect->setPos(coin->pos());
            rect->setZValue(0);
            QImage bg(":/images/Resources/images/level_1.png");
            rect->setBrush(bg.pixelColor(10,10));
            rect->setPen(Qt::NoPen);
            scene->addItem(rect);

            scene->removeItem(coin);
            coin->deleteLater();
        }
    }

    // 4) MysteryBox collisions
    {
        auto allItems = scene->items();
        QList<MysteryBox*> boxesToRemove;
        for (auto* item : allItems) {
            if (MysteryBox* box = dynamic_cast<MysteryBox*>(item)) {
                for (auto* obj : box->collidingItems()) {
                    if (dynamic_cast<Player*>(obj)) {
                        boxesToRemove.append(box);
                        score += 10;
                        break;
                    }
                }
            }
        }
        for (auto* box : boxesToRemove) {
            QGraphicsRectItem* rect = new QGraphicsRectItem(0,0,16,16);
            rect->setPos(box->pos());
            rect->setZValue(0);
            QImage bg(":/images/Resources/images/level_1.png");
            rect->setBrush(bg.pixelColor(10,10));
            rect->setPen(Qt::NoPen);
            scene->addItem(rect);

            scene->removeItem(box);
            box->deleteLater();
        }
    }

    // 5) Update HUD
    health = mario->getHealth();
    scoreLabel->setText("Score: " + QString::number(score));
    coinLabel->setText("Coins: " + QString::number(coins));
    healthLabel->setText("Health: " + QString::number(health));

    // 6) Bullet movement & collisions
    {
        auto allItems = scene->items();
        for (auto* item : allItems) {
            if (Bullet* bullet = dynamic_cast<Bullet*>(item)) {
                bullet->moveBy(0,5);
                if (bullet->y() >= 205) {
                    scene->removeItem(bullet);
                    delete bullet;
                    continue;
                }
                for (auto* obj : bullet->collidingItems()) {
                    if (Player* p = dynamic_cast<Player*>(obj)) {
                        p->decreaseHealth(1);
                        if (p->playerDied()) {
                            gameTimer->stop();
                            QMessageBox::information(this,"Game Over","You lost the game!");
                            restartGame();
                            return;
                        }
                        scene->removeItem(bullet);
                        delete bullet;
                        break;
                    }
                }
            }
        }
    }

    // 7) Level completion → Level 2
    if (mario->x() >= 3600) {
        gameTimer->stop();
        level = 2;
        QMessageBox::information(this,"Level Complete",
                                 "🎉 Congratulations! You've passed Level 1, continue to level 2!");

        // clear and reset
        scene->clear();
        enemies.clear();
        score = 0; coins = 0; health = 3;
        scoreLabel->setText("Score: 0");
        coinLabel->setText("Coins: 0");
        healthLabel->setText("Health: 3");

        // build level 2
        QGraphicsScene* level2Scene = new QGraphicsScene(this);
        level2Scene->setSceneRect(0,0,3800,600);
        level2Scene->addPixmap(QPixmap(":/images/Resources/images/level_2.png"));
        QGraphicsRectItem* cover2 = new QGraphicsRectItem(0,235,4200,600);
        cover2->setBrush(QColor("#4C2F27"));
        cover2->setZValue(0);
        level2Scene->addItem(cover2);
        view->setScene(level2Scene);

        // new Mario
        mario = new Player;
        mario->setZValue(1);
        mario->setPixmap(
            QPixmap(":/images/Resources/images/m1R.png")
                .scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)
            );
        mario->setPos(30,155);
        mario->setGroundLevel(155);
        mario->setFlag(QGraphicsItem::ItemIsFocusable);
        level2Scene->addItem(mario);
        mario->setFocus();
        view->centerOn(mario);

        gameTimer->start(16);
    }
}
