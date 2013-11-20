TEMPLATE = app

DESTDIR = ../bin

INCLUDEPATH += \
    ../include/

LIBS += \
    -L../bin \
    -lQtWui

unix:TARGETDEPS += ../bin/libQtWui.so
win32:TARGETDEPS += ../bin/QtWui.dll

MOC_DIR = .tmp/moc

OBJECTS_DIR = .tmp/obj

UI_DIR = .tmp/ui

SOURCES += \
    main.cpp \
    HangMan.cpp \
    Game.cpp

HEADERS += \
    HangMan.h \
    Game.h
