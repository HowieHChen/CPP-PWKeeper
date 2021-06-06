QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basedialog.cpp \
    basepage.cpp \
    forgetpwpage.cpp \
    iniservice.cpp \
    main.cpp \
    mainpage.cpp \
    passwordmanage.cpp \
    signinpage.cpp \
    signuppage.cpp \
    switchcontrol.cpp \
    userprofile.cpp

HEADERS += \
    basedialog.h \
    basepage.h \
    forgetpwpage.h \
    iniservice.h \
    mainpage.h \
    passwordmanage.h \
    signinpage.h \
    signuppage.h \
    switchcontrol.h \
    userprofile.h

FORMS += \
    basedialog.ui \
    basepage.ui \
    forgetpwpage.ui \
    mainpage.ui \
    signinpage.ui \
    signuppage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    Res/close.png \
    Res/hide.png
