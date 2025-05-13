// Mario.cpp

#include "Mario.h"
#include <QPixmap>
#include <QGraphicsScene>

Mario::Mario(QGraphicsItem* parent)
    : QObject(nullptr)               // QObject first
    , QGraphicsPixmapItem(parent)    // then QGraphicsPixmapItem
{
    // initial sprite, focus policy, etc.
    setPixmap(QPixmap(":/images/Resources/images/m1R.png")
                  .scaled(60,60,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

// Example stubs—merge in your real movement/animation logic:
void Mario::keyPressEvent(QKeyEvent* event) {
    // e.g. forward to your Player object, or implement directly here
    QGraphicsPixmapItem::keyPressEvent(event);
}

void Mario::keyReleaseEvent(QKeyEvent* event) {
    QGraphicsPixmapItem::keyReleaseEvent(event);
}
