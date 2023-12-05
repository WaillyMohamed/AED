QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AED_Arrhythmia_Detector.cpp \
    AED_Audio.cpp \
    AED_Device.cpp \
    main.cpp \
    aed_display.cpp

HEADERS += \
    AED_Arrhythmia_Detector.h \
    AED_Audio.h \
    AED_Device.h \
    aed_display.h

FORMS += \
    aed_display.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    AED_Design.png
