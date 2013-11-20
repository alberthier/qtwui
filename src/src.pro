CONFIG += \
    warn_on \
    thread \
    qt \
    dll \
    debug

TEMPLATE = lib

TARGET = QtWui

DESTDIR = ../bin

#system(../scripts/create-include-files.rb)

QT += \
    core \
    network \
    xml

OBJECTS_DIR = .tmp/obj

UI_DIR = .tmp/ui

MOC_DIR = .tmp/moc

DEFINES += QTWUI_BUILD

include(http/http.pri)
include(kernel/kernel.pri)
include(webgets/webgets.pri)

INSTALLS += target

target.path = ../bin
DISTFILES += \
    ../javascript/prototype.js \
    ../javascript/qtwui.js \
    ../stylesheets/qtwui.css \
    ../stylesheets/qwuilabel.css \
    ../stylesheets/qwuimainwebget.css \
    ../stylesheets/qwuiscrollarea.css \
    ../stylesheets/qwuiwebget.css

INCLUDEPATH += ../include
