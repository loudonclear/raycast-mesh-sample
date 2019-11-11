QT += gui
QT += xml

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += -msse2
#QMAKE_CXXFLAGS += -fopenmp
#LIBS += -fopenmp

SOURCES += main.cpp \
    tracer.cpp \
    scene/scene.cpp \
    BVH/BBox.cpp \
    BVH/BVH.cpp \
    scene/basiccamera.cpp \
    scene/shape/mesh.cpp \
    scene/shape/triangle.cpp

HEADERS += \
    tracer.h \
    scene/scene.h \
    BVH/BBox.h \
    BVH/BVH.h \
    BVH/IntersectionInfo.h \
    BVH/Log.h \
    BVH/Object.h \
    BVH/Ray.h \
    BVH/Stopwatch.h \
    scene/camera.h \
    scene/basiccamera.h \
    util/common.h \
    scene/shape/mesh.h \
    scene/shape/triangle.h \
    util/tiny_obj_loader.h \
    BVH/vector3.h
