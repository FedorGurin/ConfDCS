# #####################################################################
# Automatically generated by qmake (2.01a) ?? 12. ??? 10:49:32 2008
# #####################################################################
TEMPLATE = app
CONFIG += qt thread console c++17
CONFIG += debug

TARGET = confDCS
DEPENDPATH += .
CONFIG +=build_all lib

# DEFINES +=ENG
#TRANSLATIONS = ui_eng.ts
CODECFORTR = utf8
QT += network \
    xml \    
 #   svg \
    widgets


#RC_ICONS = resource/red-puzzle.ico
#INCLUDEPATH +=  xml


# Input
HEADERS += \
    mainwindow.h \
    node.h \
    domParser.h \
    globalFunc/Vector3D_D.h \
    settingXML.h \
    globalFunc/mercator.h \    
    systemNode.h \
    unitNode.h \
    connectorNode.h \
    pinNode.h \
    wireNode.h \
    globalFunc/gl_func.h \
    formCurciut.h \
    interfaceNode.h \
    coordNode.h
   
    

FORMS +=\
    mainwindow.ui \
    formCurciut.ui
  

SOURCES += globalFunc/gl_func.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    domParser.cpp \
    globalFunc/Vector3D_D.cpp \
    globalFunc/Matrix3D_D.cpp \   
    globalFunc/mercator.cpp \  
    settingXML.cpp \
    systemNode.cpp \
    unitNode.cpp \
    connectorNode.cpp \
    pinNode.cpp \
    wireNode.cpp \
    formCurciut.cpp \
    interfaceNode.cpp \
    coordNode.cpp

DISTFILES += \
    README.md












