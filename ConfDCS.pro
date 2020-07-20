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
    svg \
    widgets


#RC_ICONS = resource/red-puzzle.ico
#INCLUDEPATH +=  xml


# Input
HEADERS += \
    mainwindow.h \
    Node.h \
    DomParser.h \
    globalFunc/Vector3D_D.h \
    SettingXML.h \
    globalFunc/mercator.h \    
    SystemNode.h \
    UnitNode.h \
    ConnectorNode.h \
    PinNode.h \
    WireNode.h \
    globalFunc/gl_func.h \
    formCurciut.h \
    InterfaceNode.h \
    CoordNode.h
   
    

FORMS +=\
    mainwindow.ui \
    formCurciut.ui
  

SOURCES += globalFunc/gl_func.cpp \
    main.cpp \
    mainwindow.cpp \
    Node.cpp \
    DomParser.cpp \
    globalFunc/Vector3D_D.cpp \
    globalFunc/Matrix3D_D.cpp \   
    globalFunc/mercator.cpp \  
    SettingXML.cpp \
    SystemNode.cpp \
    UnitNode.cpp \
    ConnectorNode.cpp \
    PinNode.cpp \
    WireNode.cpp \
    formCurciut.cpp \
    InterfaceNode.cpp \
    CoordNode.cpp












