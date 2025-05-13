#include "Player.h"
#include "Platform.h"
#include "Obstacle.h"
#include "Coin.h"
#include "MysteryBox.h"
#include "Pitfall.h"
#include "PowerUp.h"
#include "PrincessPeach.h"
#include "Enemy.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QPixmap>
#include <algorithm>

Player::Player(QGraphicsItem *parent)
    : QObject(nullptr)
    , QGraphicsPixmapItem(parent)
    , health(3)
    , score(0)
    , coins(0)
    , velocityX(0)
    , velocityY(0)
    , jumpsRemaining(2)
    , onGround(true)          // start “standing,” so no immediate fall
    , isGameStarted(false)
    , isright(false)
    , ismoving(false)
    , r(0)
    , l(0)
    , groundLevel(0)          // override in setup
{
    setPixmap(
        QPixmap(":/images/Resources/images/m1R.png")
            .scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

int Player::getHealth()    const { return health; }
int Player::getScore()     const { return score; }
int Player::getCoins()     const { return coins; }

void Player::addScore(int p)      { score = std::max(0, score + p); }
void Player::addCoin(int c)       { coins = std::max(0, coins + c); }
void Player::decreaseHealth(int a){ health = std::max(0, health - a); }
void Player::increaseHealth(int a){ health += a;         }

void Player::jump() {
    if (jumpsRemaining > 0) {
        velocityY     = -15;
        onGround      = false;
        jumpsRemaining--;
    }
}

void Player::moveLeft()  { isright=false;  ismoving=true; velocityX=-4; }
void Player::moveRight() { isright=true;   ismoving=true; velocityX=4; }
void Player::stopMoving(){ velocityX=0;    ismoving=false;      }

// void Player::updateMovement() {
//     if (!isGameStarted) return;

//     const double gravity = 1.0;
//     const double sceneW  = scene()->sceneRect().width();

//     // 1) Horizontal move + collision
//     if (velocityX != 0) {
//         setX(x()+velocityX);
//         if (x()<0) setX(0);
//         else if (x()+boundingRect().width()>sceneW)
//             setX(sceneW - boundingRect().width());

//         for (auto* it: collidingItems())
//             if (dynamic_cast<Platform*>(it)||dynamic_cast<Obstacle*>(it)) {
//                 setX(x()-velocityX);
//                 velocityX=0;
//                 break;
//             }
//     }

//     // 2) Gravity when in air
//     if (!onGround)
//         velocityY += gravity;

//     // 3) Vertical move
//     setY(y()+velocityY);

//     // 4) Land on groundLevel
//     if (y()>groundLevel) {
//         setY(groundLevel);
//         velocityY=0;
//         onGround=true;
//         jumpsRemaining=2;
//     }

//     // 5) Platform/Enemy collisions (stomping etc.)
//     bool landed=false;
//     for (auto* it: collidingItems()) {
//         if (auto* plat=dynamic_cast<Platform*>(it);
//             plat || dynamic_cast<Obstacle*>(it))
//         {
//             if (velocityY>0) {
//                 setY(it->y()-boundingRect().height());
//                 velocityY=0; onGround=true; jumpsRemaining=2; landed=true;
//             } else if (velocityY<0) {
//                 setY(it->y()+it->boundingRect().height());
//                 velocityY=0;
//             }
//         }
//         if (auto* enemy = dynamic_cast<Enemy*>(it)) {
//             if (velocityY>0) {
//                 scene()->removeItem(enemy);
//                 delete enemy;
//                 velocityY=-10;
//                 addScore(100);
//                 onGround=true; jumpsRemaining=2; landed=true;
//             } else {
//                 enemy->onCollide(this);
//             }
//         }
//     }



//     if (!landed && velocityY!=0)
//         onGround=false;
//     // ————————————————
//     // Resume walking animation if on ground and moving
//     if (onGround && velocityX != 0) {
//         if (isright) {
//             switch (++r % 7) {
//             case 0: setPixmap(QPixmap(":/images/m1R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 1: setPixmap(QPixmap(":/images/m2R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 2: setPixmap(QPixmap(":/images/m3R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 3: setPixmap(QPixmap(":/images/m4R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 4: setPixmap(QPixmap(":/images/m5R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 5: setPixmap(QPixmap(":/images/m6R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 6: setPixmap(QPixmap(":/images/m7R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             }
//         } else {
//             switch (++l % 7) {
//             case 0: setPixmap(QPixmap(":/images/m1L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 1: setPixmap(QPixmap(":/images/m2L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 2: setPixmap(QPixmap(":/images/m3L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 3: setPixmap(QPixmap(":/images/m4L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 4: setPixmap(QPixmap(":/images/m5L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 5: setPixmap(QPixmap(":/images/m6L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             case 6: setPixmap(QPixmap(":/images/m7L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation)); break;
//             }
//         }
//     }
//     // ————————————————

//     // 6) Coins, boxes, pitfalls, power‐ups, princess...
//     for (auto* it: collidingItems()) {
//         if (auto* c = dynamic_cast<Coin*>(it)) {
//             scene()->removeItem(c); delete c; addCoin(1); addScore(10);
//         }
//         else if (auto* b = dynamic_cast<MysteryBox*>(it)) {
//             scene()->removeItem(b); delete b; addScore(50);
//         }
//         else if (auto* pit = dynamic_cast<Pitfall*>(it)) {
//             decreaseHealth(1);
//             setPos(0,0);  // respawn at start
//         }
//         else if (auto* pow = dynamic_cast<PowerUp*>(it)) {
//             pow->onCollide(this);
//         }
//         else if (auto* peach = dynamic_cast<PrincessPeach*>(it)) {
//             peach->onCollide(this);
//         }
//     }
// }

void Player::updateMovement() {
    if (!isGameStarted) return;

    const double gravity = 1.0;
    const double sceneW  = scene()->sceneRect().width();

    // 1) Horizontal move + collision
    if (velocityX != 0) {
        setX(x() + velocityX);
        if (x() < 0) setX(0);
        else if (x() + boundingRect().width() > sceneW)
            setX(sceneW - boundingRect().width());

        for (auto* it : collidingItems())
            if (dynamic_cast<Platform*>(it) || dynamic_cast<Obstacle*>(it)) {
                setX(x() - velocityX);
                velocityX = 0;
                break;
            }
    }

    // 2) Gravity
    if (!onGround)
        velocityY += gravity;

    // 3) Vertical movement
    setY(y() + velocityY);

    // 4) Ground contact
    if (y() > groundLevel) {
        setY(groundLevel);
        velocityY = 0;
        onGround = true;
        jumpsRemaining = 2;
    }

    // 5) Platform/enemy collisions
    bool landed = false;
    for (auto* it : collidingItems()) {
        if (auto* plat = dynamic_cast<Platform*>(it); plat || dynamic_cast<Obstacle*>(it)) {
            if (velocityY > 0) {
                setY(it->y() - boundingRect().height());
                velocityY = 0; onGround = true; jumpsRemaining = 2; landed = true;
            } else if (velocityY < 0) {
                setY(it->y() + it->boundingRect().height());
                velocityY = 0;
            }
        }
        if (auto* enemy = dynamic_cast<Enemy*>(it)) {
            if (velocityY > 0) {
                scene()->removeItem(enemy);
                delete enemy;
                velocityY = -10;
                addScore(100);
                onGround = true; jumpsRemaining = 2; landed = true;
            } else {
                enemy->onCollide(this);
            }
        }
    }

    if (!landed && velocityY != 0)
        onGround = false;

    // 6) Animation (slowed down)
    if (onGround && velocityX != 0) {
        if (++animTick >= 5) {  // Change frame every 5 updates
            animTick = 0;
            animFrame = (animFrame + 1) % 7;

            QString path = QString(":/images/Resources/images/m%1%2.png")
                               .arg(animFrame + 1)
                               .arg(isright ? "R" : "L");

            setPixmap(QPixmap(path).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

    // 7) Items & objects
    for (auto* it : collidingItems()) {
        if (auto* c = dynamic_cast<Coin*>(it)) {
            scene()->removeItem(c); delete c; addCoin(1); addScore(10);
        } else if (auto* b = dynamic_cast<MysteryBox*>(it)) {
            scene()->removeItem(b); delete b; addScore(50);
        } else if (auto* pit = dynamic_cast<Pitfall*>(it)) {
            decreaseHealth(1);
            setPos(0, 0);  // respawn
        } else if (auto* pow = dynamic_cast<PowerUp*>(it)) {
            pow->onCollide(this);
        } else if (auto* peach = dynamic_cast<PrincessPeach*>(it)) {
            peach->onCollide(this);
        }
    }
}


void Player::keyPressEvent(QKeyEvent *ev) {
    if (!hasFocus()) setFocus();

    switch (ev->key()) {
    case Qt::Key_Right:
        moveRight();
        switch (++r % 7) {
        case 0: setPixmap(QPixmap(":/images/Resources/images/m1R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 1: setPixmap(QPixmap(":/images/Resources/images/m2R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 2: setPixmap(QPixmap(":/images/Resources/images/m3R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 3: setPixmap(QPixmap(":/images/Resources/images/m4R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 4: setPixmap(QPixmap(":/images/Resources/images/m5R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 5: setPixmap(QPixmap(":/images/Resources/images/m6R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 6: setPixmap(QPixmap(":/images/Resources/images/m7R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        }
        break;

    case Qt::Key_Left:
        moveLeft();
        switch (++l % 7) {
        case 0: setPixmap(QPixmap(":/images/Resources/images/m1L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 1: setPixmap(QPixmap(":/images/Resources/images/m2L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 2: setPixmap(QPixmap(":/images/Resources/images/m3L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 3: setPixmap(QPixmap(":/images/Resources/images/m4L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 4: setPixmap(QPixmap(":/images/Resources/images/m5L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 5: setPixmap(QPixmap(":/images/Resources/images/m6L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        case 6: setPixmap(QPixmap(":/images/Resources/images/m7L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));break;
        }
        break;

    case Qt::Key_Up:
        jump();
        if (isright)
            setPixmap(QPixmap(":/images/Resources/images/mJ1R.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        else
            setPixmap(QPixmap(":/images/Resources/images/mJ1L.png").scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        break;

    default:
        QGraphicsPixmapItem::keyPressEvent(ev);
    }
}

void Player::keyReleaseEvent(QKeyEvent *ev) {
    if (ev->isAutoRepeat() || !isGameStarted) return;
    if ((ev->key()==Qt::Key_Left  && velocityX<0) ||
        (ev->key()==Qt::Key_Right && velocityX>0))
        stopMoving();
}

bool Player::playerDied() const { return health<=0; }
