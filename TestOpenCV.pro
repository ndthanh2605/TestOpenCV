#-------------------------------------------------
#
# Project created by QtCreator 2015-10-31T02:23:36
#
#-------------------------------------------------

QT       += core widgets

TARGET = TestOpenCV
TEMPLATE = app


SOURCES += main.cpp \
    ImageAcquisition/imagemanager.cpp \
    FeatureExtraction/colorfeatureextractor.cpp \
    FeatureExtraction/texturefeatureextractor.cpp \
    FeatureExtraction/shapefeatureextractor.cpp \
    Training/artificialneutralnetwork.cpp \
    FeatureExtraction/featuremanager.cpp \
    mainwindow.cpp

HEADERS += \
    ImageAcquisition/imagemanager.h \
    FeatureExtraction/colorfeatureextractor.h \
    FeatureExtraction/texturefeatureextractor.h \
    FeatureExtraction/shapefeatureextractor.h \
    Training/artificialneutralnetwork.h \
    FeatureExtraction/featuremanager.h \
    mainwindow.h

INCLUDEPATH += D:/opencv_249/build_mingw_texture.cpp/install/include

LIBS += -LD:\\opencv_249\\build_mingw_texture.cpp\\install\\x64\\mingw\\bin \
    libopencv_core249 \
    libopencv_highgui249 \
    libopencv_imgproc249 \
    libopencv_features2d249 \
    libopencv_calib3d249 \
    libopencv_legacy249 \
    libopencv_ml249

FORMS += \
    mainwindow.ui
