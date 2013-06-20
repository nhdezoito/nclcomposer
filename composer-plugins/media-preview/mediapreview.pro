######################################################################
# Automatically generated by qmake (2.01a) Sat Jan 28 14:31:14 2012
######################################################################
include(../plugins-common.pri)

QT += phonon
QT += gui
QT += xml
CONFIG +=qtestlib


#TEMPLATE = app
TARGET = mediapreview
DEPENDPATH += .
INCLUDEPATH += .

release {
LIBS      +=    -L../ncl-textual-plugin/deps/QScintilla-gpl-2.6.3/Qt4Qt5/release \
                -lqscintilla2_telem
}else:debug {
LIBS      +=    -L../ncl-textual-plugin/deps/QScintilla-gpl-2.6.3/Qt4Qt5/debug \
                -lqscintilla2_telem
}

CODECFORTR = UTF-8
# Input
SOURCES += \
    mediapreviewfactory.cpp \
    audioplayer.cpp \
    imagview.cpp \
    gifview.cpp \
    textview.cpp \
    hypertextview.cpp \
    nclview.cpp \
    luaview.cpp \
    mediapreviewplugin.cpp \
    videoplayer.cpp

HEADERS += \
    mediapreviewfactory.h \
    mediapreviewplugin.h \
    audioplayer.h \
    imagview.h \
    gifview.h \
    textview.h \
    hypertextview.h \
    nclview.h \
    luaview.h \
    videoplayer.h

FORMS += \
    videoplayer.ui

RESOURCES += \
    media-preview.qrc
