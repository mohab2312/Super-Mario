#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>

class Player;

class Level : public QGraphicsScene {
    Q_OBJECT
public:
    Level();
    void startGame();
    void updateHUD();

public slots:
    void updateGame();

private:
    Player* player;
    QGraphicsTextItem* scoreText;
    QGraphicsTextItem* healthText;
    QGraphicsTextItem* coinText;
    QGraphicsTextItem* startText;
    QTimer* timer;
};

#endif

