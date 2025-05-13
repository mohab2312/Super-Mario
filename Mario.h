// Mario.h

#ifndef MARIO_H
#define MARIO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Mario : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Mario(QGraphicsItem* parent = nullptr);
    ~Mario() override = default;

protected:
    // If you handle key events here, override these:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    // Any other virtuals...
};

#endif // MARIO_H
