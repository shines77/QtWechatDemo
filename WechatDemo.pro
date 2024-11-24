#-------------------------------------------------
#
# Project created by QtCreator 2024-11-20T11:06:25
#
#-------------------------------------------------

QT       += core gui
QT       += webenginewidgets webchannel
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WechatDemo
TEMPLATE = app
DESTDIR = bin

unix:UI_DIR = ../tmp/ui
win32:UI_DIR = tmp/ui

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += src

SOURCES += \
        src/wechat/Main.cpp \
        src/wechat/WxMainWindow.cpp \
        src/wechat/ChatPanel.cpp \
        src/wechat/ChatHistoryList.cpp \
    src/wechat/Component.cpp \
    src/wechat/ContactPanel.cpp \
    src/wechat/FriendList.cpp \
    src/wechat/IconHelper.cpp \
    src/wechat/MsgQueue.cpp \
    src/wechat/NavPanel.cpp \
    src/wechat/NotificationPanel.cpp \
    src/wechat/PushButtonEx.cpp \
    src/wechat/ChatTopToolbar.cpp \
    src/wechat/UserDetailDlg.cpp \
    src/wechat/AppInit.cpp \
    src/wechat/FavoritePanel.cpp \
    src/wechat/DataMgrPanel.cpp \
    src/wechat/UserPanel.cpp \
    src/wechat/UserProfiles.cpp \
    src/wechat/AppreciateDlg.cpp \
    src/wechat/CarouselPanel.cpp \
    src/wechat/BaseDlg.cpp \
    src/wechat/DynamicCard.cpp \
    src/wechat/BoderPanel.cpp \
    src/wechat/PopConfirm.cpp \
    src/wechat/Slider.cpp \
    src/wechat/TipWidget.cpp \
    src/wechat/IconfontPanel.cpp

HEADERS += \
        src/wechat/WxMainWindow.h \
        src/wechat/ChatPanel.h \
        src/wechat/ChatHistoryList.h \
    src/wechat/Component.h \
    src/wechat/ContactPanel.h \
    src/wechat/FriendList.h \
    src/wechat/IconHelper.h \
    src/wechat/MsgQueue.h \
    src/wechat/NavPanel.h \
    src/wechat/NotificationPanel.h \
    src/wechat/PushButtonEx.h \
    src/wechat/ChatTopToolbar.h \
    src/wechat/UserDetailDlg.h \
    src/wechat/Public.h \
    src/wechat/AppInit.h \
    src/wechat/FavoritePanel.h \
    src/wechat/DataMgrPanel.h \
    src/wechat/UserPanel.h \
    src/wechat/UserProfiles.h \
    src/wechat/AppreciateDlg.h \
    src/wechat/CarouselPanel.h \
    src/wechat/BaseDlg.h \
    src/wechat/DynamicCard.h \
    src/wechat/BoderPanel.h \
    src/wechat/PopConfirm.h \
    src/wechat/Slider.h \
    src/wechat/TipWidget.h \
    src/wechat/IconfontPanel.h

FORMS += \
        ui/WxMainWindow.ui \
    ui/AppreciateDlg.ui \
    ui/UserProfiles.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/WechatDemo.qrc

RC_FILE +=  \
    res/WechatDemo.rc
