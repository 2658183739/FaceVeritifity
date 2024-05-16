QT       += core gui multimedia multimediawidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camerathread.cpp \
    main.cpp \
    faceverify.cpp \
    src/bif.cpp \
    src/eigen_faces.cpp \
    src/face_alignment.cpp \
    src/face_basic.cpp \
    src/facemark.cpp \
    src/facemarkAAM.cpp \
    src/facemarkLBF.cpp \
    src/facerec.cpp \
    src/fisher_faces.cpp \
    src/getlandmarks.cpp \
    src/lbph_faces.cpp \
    src/mace.cpp \
    src/predict_collector.cpp \
    src/regtree.cpp \
    src/trainFacemark.cpp \
    train.cpp \
    verityface.cpp

HEADERS += \
    camerathread.h \
    face.hpp \
    face/bif.hpp \
    face/face_alignment.hpp \
    face/facemark.hpp \
    face/facemarkAAM.hpp \
    face/facemarkLBF.hpp \
    face/facemark_train.hpp \
    face/facerec.hpp \
    face/mace.hpp \
    face/predict_collector.hpp \
    faceverify.h \
    src/face_alignmentimpl.hpp \
    src/face_utils.hpp \
    src/precomp.hpp \
    train.h \
    verityface.h

FORMS += \
    faceverify.ui \
    verityface.ui

INCLUDEPATH +=D:\opencv\opencv\build\include\
              D:\opencv\opencv\build\include\opencv\
              D:\opencv\opencv\build\include\opencv2

LIBS +=D:\opencv\opencv\build\x64\vc15\lib\opencv_world440.lib


msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    haarcascade_frontalface_alt2.xml \
    qss.qss
