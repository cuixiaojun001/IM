QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core5compat
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += ./net
INCLUDEPATH += ./mediator
LIBS += -lws2_32

SOURCES += \
    chatdialog.cpp \
    contactlistdialog.cpp \
    kernel.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mediator/INetMediator.cpp \
    mediator/TcpClientMediator.cpp \
    net/TcpClient.cpp \
    useritem.cpp

HEADERS += \
    chatdialog.h \
    contactlistdialog.h \
    kernel.h \
    logindialog.h \
    mainwindow.h \
    mediator/INetMediator.h \
    mediator/TcpClientMediator.h \
    net/INet.h \
    net/TcpClient.h \
    net/packdef.h \
    useritem.h

FORMS += \
    chatdialog.ui \
    contactlistdialog.ui \
    logindialog.ui \
    mainwindow.ui \
    useritem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource.qrc
