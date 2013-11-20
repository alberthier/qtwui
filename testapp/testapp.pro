CONFIG += \
    debug \
    qt \
    warn_on

TEMPLATE = app

QT += \
    core \
    xml

DESTDIR = ../bin

OBJECTS_DIR = .tmp/obj

UI_DIR = .tmp/ui

MOC_DIR = .tmp/moc

SOURCES += \
    main.cpp \
    TestWebget.cpp

HEADERS += \
    TestWebget.h

INCLUDEPATH += \
    ../include

LIBS += \
    -L../bin \
    -lQtWui

unix:TARGETDEPS += ../lib/libQtWui.so
win32:TARGETDEPS += ../lib/QtWui.dll
