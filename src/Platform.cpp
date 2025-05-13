#include "Platform.h"
#include <QPixmap>

Platform::Platform() {
    QPixmap originalPixmap(":/images/level_1.png");
    setPixmap(originalPixmap.scaled(1000, 1000, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

