# -------------------------------------------------
# Project created by QtCreator 2010-03-12T13:06:44
# -------------------------------------------------

QT += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 silent

TEMPLATE = lib
TARGET = ComposerCore

VERSION = 1.0
CONFIG += dll

# Uses FORCERELEASE variable because CONFIG and SUBDIR force three executions
# if qmake and the last one does not preserves CONFIG from command line.
contains(FORCERELEASE, true) {
  CONFIG += qt warn_on release
  CONFIG -= debug
  DEFINES += QT_NO_DEBUG_OUTPUT QT_NO_DEBUG_WARNING
  message ("core.pro RELEASE build!")
}
else {
  CONFIG += qt warn_on debug console
  CONFIG -= release
  message ("core.pro DEBUG build!")
}

debug: DESTDIR = $${PWD}/../../bin/debug/
release: DESTDIR = $${PWD}/../../bin/release
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

contains(NO_DEBUG_OUTPUT, true) {
    DEFINES += QT_NO_DEBUG_OUTPUT QT_NO_DEBUG_WARNING
}

macx:CONFIG += lib_bundle

macx {
  INSTALLBASE = /Library/Frameworks
}
else:unix {
 isEmpty(PREFIX) {
    PREFIX = /usr/local
  } 
  INSTALLBASE = $${PREFIX}
}
else:win32 {
  INSTALLBASE = C:/Composer
}

DEFINES += EXT_DEFAULT_PATH=\"\\\"$$PREFIX\\\"\"

DEFINES += COMPOSERCORE_LIBRARY

SOURCES += \
    modules/PluginControl.cpp \
    modules/MessageControl.cpp \
    modules/LanguageControl.cpp \
    modules/ProjectControl.cpp \
    model/Entity.cpp \
    model/Project.cpp \
    util/Utilities.cpp \
    util/AttributeReferences.cpp \
    modules/ProjectReader.cpp \
    util/ComposerSettings.cpp \
    util/Commands.cpp
    # model/Model.cpp

HEADERS_MAN += \
    modules/PluginControl.h \
    modules/MessageControl.h \
    modules/LanguageControl.h \
    modules/ProjectControl.h \
    modules/ProjectReader.h

HEADERS_EXTENSIONS += \
    extensions/ILanguageProfile.h \
    extensions/IDocumentParser.h \
    extensions/IPlugin.h \
    extensions/IPluginFactory.h \
    extensions/IPreferencesPage.h

HEADERS_UTIL += \
    util/ComposerCoreControl_global.h \
    util/Singleton.h \
    util/AttributeReferences.h \
    util/Utilities.h \
    util/ComposerSettings.h \
    util/Commands.h

HEADERS_EXCEPTION +=  \
    model/exception/EntityNotFound.h \
    model/exception/ParentNotFound.h \
    model/exception/CreationFailed.h

HEADERS_MODEL += \
    model/Entity.h \
    model/Project.h
    #model/Model.h

HEADERS = \
    $$HEADERS_MAN \
    $$HEADERS_EXTENSIONS \
    $$HEADERS_UTIL \
    $$HEADERS_EXCEPTION \
    $$HEADERS_MODEL

headers_man.files = $$HEADERS_MAN
headers_extensions.files = $$HEADERS_EXTENSIONS
headers_util.files = $$HEADERS_UTIL
headers_exception.files = $$HEADERS_EXCEPTION
headers_model.files = $$HEADERS_MODEL

INCLUDEPATH += .

macx { 
    QMAKE_FRAMEWORK_BUNDLE_NAME = $$TARGET
    headers_man.path = core/modules
    headers_extensions.path = core/extensions
    headers_util.path = core/util
    headers_exception.path=core/model/exception
    headers_model.path = core/model
    QMAKE_BUNDLE_DATA += headers_man headers_extensions \
                         headers_util headers_exception headers_model
    QMAKE_BUNDLE_DATA.path = $$INSTALLBASE
    target.path = $$INSTALLBASE
    INSTALLS += target

    QMAKE_CXXFLAGS += -mmacosx-version-min=10.7 -std=c++11 -stdlib=libc++
    LIBS += -mmacosx-version-min=10.7 -stdlib=libc++
}
else:unix {
    target.path = $$INSTALLBASE/lib/composer
    HEADERS_PATH_UNIX = $$INSTALLBASE/include/composer

    headers_model.path = $$HEADERS_PATH_UNIX/core/model
    headers_man.path = $$HEADERS_PATH_UNIX/core/modules
    headers_extensions.path = $$HEADERS_PATH_UNIX/core/extensions
    headers_util.path = $$HEADERS_PATH_UNIX/core/util
    headers_exception.path = $$HEADERS_PATH_UNIX/core/model/exception

    INSTALLS += headers_man headers_util headers_model \
                headers_extensions headers_exception target
}else:win32 {
    target.path = $$INSTALLBASE
    HEADERS_PATH_UNIX = $$INSTALLBASE/include/composer

    headers_model.path = $$HEADERS_PATH_UNIX/core/model
    headers_man.path = $$HEADERS_PATH_UNIX/core/modules
    headers_extensions.path = $$HEADERS_PATH_UNIX/core/extensions
    headers_util.path = $$HEADERS_PATH_UNIX/core/util
    headers_exception.path = $$HEADERS_PATH_UNIX/core/model/exception

    INSTALLS += headers_man headers_util headers_model \
                headers_extensions headers_exception target
}

