QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AudioPlayer
TEMPLATE = app

CONFIG += c++11

SOURCES += \
        main.cpp \
        audioplayer.cpp

HEADERS += \
        audioplayer.h

FORMS += \
        audioplayer.ui

RESOURCES += \
    buttons.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
