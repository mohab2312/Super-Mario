#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QList>

class Player;
class Enemy;
class Coin;
class MysteryBox;
class Pitfall;
class Bullet;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void updateGame();
    void handlePlayerDeath();

private:
    void restartGame();

    QGraphicsScene *homeScene;
    QGraphicsScene *scene;
    QGraphicsView  *view;
    Player         *mario;
    QList<Enemy*>   enemies;

    QLabel *scoreLabel;
    QLabel *healthLabel;
    QLabel *coinLabel;

    QTimer  *gameTimer;
    int      score;
    int      health;
    int      coins;
    bool     isOnHomeScreen;
};

#endif // MAINWINDOW_H
