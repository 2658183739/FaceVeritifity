QT += core gui multimedia multimediawidgets sql quick virtualkeyboard widgets quickcontrols2

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += c++17

SOURCES += \
        imageprovider.cpp \
        main.cpp \
        camerathread.cpp \
        faceverify.cpp \
        showimage.cpp \
        train.cpp \
        verityface.cpp \
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
        src/trainFacemark.cpp






RESOURCES += qml.qrc \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    at.txt \
    background.jpeg

HEADERS += \
    camerathread.h \
    face.hpp \
    faceverify.h \
    imageprovider.h \
    showimage.h \
    train.h \
    verityface.h \
    face/bif.hpp \
    face/face_alignment.hpp \
    face/facemark.hpp \
    face/facemarkAAM.hpp \
    face/facemarkLBF.hpp \
    face/facemark_train.hpp \
    face/facerec.hpp \
    face/mace.hpp \
    face/predict_collector.hpp \
    src/face_alignmentimpl.hpp \
    src/face_utils.hpp \
    src/precomp.hpp




INCLUDEPATH +=D:\opencv\opencv\build\include\
              D:\opencv\opencv\build\include\opencv\
              D:\opencv\opencv\build\include\opencv2\
              D:\research\CV\FaceVeritifity_qml\src\
              D:\research\CV\FaceVeritifity_qml\face

LIBS +=D:\opencv\opencv\build\x64\vc15\lib\opencv_world440.lib


msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
