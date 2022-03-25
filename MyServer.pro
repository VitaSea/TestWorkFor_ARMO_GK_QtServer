QT += core gui network widgets
greaterThan(QT_MAJOR_VERSION, 4):

CONFIG += c++11

SOURCES += \
    main.cpp \
    server.cpp

HEADERS += \
    server.h

FORMS += \
    server.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
