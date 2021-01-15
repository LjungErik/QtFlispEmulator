QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    filereaderservice.cpp \
    flispcomputerwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    memorytablemodel.cpp \
    memorywidget.cpp \
    monitorservice.cpp \
    iogroupwidget.cpp \
    main.cpp \
    programtablemodel.cpp \
    programwidget.cpp \
    registrygroupwidget.cpp

HEADERS += \
    filereaderservice.h \
    flispcomputerwindow.h \
    mainwindow.h \
    memorytablemodel.h \
    memorywidget.h \
    monitorservice.h \
    iogroupwidget.h \
    programtablemodel.h \
    programwidget.h \
    registrygroupwidget.h

FORMS += \
    flispcomputerwindow.ui \
    mainwindow.ui \
    iogroupwidget.ui \
    memorywidget.ui \
    programwidget.ui \
    registrygroupwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logic/release/ -llogic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logic/debug/ -llogic
else:unix: LIBS += -L$$OUT_PWD/../logic/ -llogic

INCLUDEPATH += $$PWD/../logic
DEPENDPATH += $$PWD/../logic

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../logic/release/liblogic.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../logic/debug/liblogic.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../logic/release/logic.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../logic/debug/logic.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../logic/liblogic.a
