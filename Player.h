#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Platform;
class Obstacle;
class Coin;
class MysteryBox;
class Pitfall;
class PowerUp;
class PrincessPeach;
class Enemy;

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Player(QGraphicsItem *parent = nullptr);

    int  getHealth() const;
    int  getScore()  const;
    int  getCoins()  const;

    int animFrame = 0;
    int animTick = 0;

    void addScore(int points);
    void addCoin(int count);
    void decreaseHealth(int amount);
    void increaseHealth(int amount);

    void jump();
    void moveLeft();
    void moveRight();
    void stopMoving();

    // Start/stop the physics loop
    void setGameStarted(bool started) { isGameStarted = started; }
    // The Y-coordinate Mario should “walk” on
    void setGroundLevel(double y)    { groundLevel = y; }

    bool playerDied() const;

public slots:
    void updateMovement();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    // stats
    int   health;
    int   score;
    int   coins;

    // physics
    double velocityX;
    double velocityY;
    int    jumpsRemaining;
    bool   onGround;
    bool   isGameStarted;

    // animation state
    bool   isright;
    bool   ismoving;
    int    r;
    int    l;

    // fixed walking plane
    double groundLevel;
};

#endif // PLAYER_H
