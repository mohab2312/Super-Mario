QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

RESOURCES += resources.qrc \
    Resources3.qrc \
    bg.qrc \
    homepage.qrc \
    lvl2.qrc \
    resources2.qrc

SOURCES += \
    Bullet.cpp \
Coin.cpp \
Enemy.cpp \
GameObject.cpp \
Level.cpp \
Mario.cpp \
Obstacle.cpp \
Platform.cpp \
Player.cpp \
PowerUp.cpp \
PrincessPeach.cpp \
main.cpp \
mainwindow.cpp \
    mysterybox.cpp \
    pitfall.cpp

HEADERS += \
    Bullet.h \
Coin.h \
Enemy.h \
GameObject.h \
Level.h \
Mario.h \
Obstacle.h \
Platform.h \
Player.h \
PowerUp.h \
PrincessPeach.h \
mainwindow.h \
    mysterybox.h \
    pitfall.h

FORMS += \
mainwindow.ui
