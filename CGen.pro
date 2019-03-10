#-------------------------------------------------
#
# Project created by QtCreator 2019-03-10T03:15:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = CGen
TEMPLATE = app
INCLUDEPATH += /opt/local/include

LIBS += -L/opt/local/lib

LIBS += -lopencv_calib3d \
-lopencv_contrib \
-lopencv_core \
-lopencv_features2d \
-lopencv_flann \
-lopencv_gpu \
-lopencv_highgui \
-lopencv_imgproc \
-lopencv_legacy \
-lopencv_ml \
-lopencv_objdetect \
-lopencv_video

SOURCES += main.cpp\
        dialog.cpp \
    Tree.cpp


HEADERS  += dialog.h \
    Tree.h


FORMS    += dialog.ui

RESOURCES += \
    Images.qrc



