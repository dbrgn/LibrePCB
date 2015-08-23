#-------------------------------------------------
#
# Project created by QtCreator 2015-05-31T12:53:17
#
#-------------------------------------------------

TEMPLATE = lib
TARGET = librepcblibrary

# Set the path for the generated binary
GENERATED_DIR = ../../generated

# Use common project definitions
include(../../common.pri)

QT += core widgets xml sql printsupport

CONFIG += staticlib

INCLUDEPATH += \
    ../

HEADERS += \
    3dmdl/model3d.h \
    cat/componentcategory.h \
    cat/packagecategory.h \
    cmp/component.h \
    fpt/footprint.h \
    gencmp/gencompsignal.h \
    gencmp/gencompsymbvar.h \
    gencmp/gencompsymbvaritem.h \
    gencmp/genericcomponent.h \
    pkg/package.h \
    spcmdl/spicemodel.h \
    sym/symbol.h \
    sym/symbolellipse.h \
    sym/symbolpin.h \
    sym/symbolpinpreviewgraphicsitem.h \
    sym/symbolpolygon.h \
    sym/symbolpreviewgraphicsitem.h \
    sym/symboltext.h \
    library.h \
    librarybaseelement.h \
    libraryelement.h \
    libraryelementattribute.h \
    fpt/footprintpolygon.h \
    fpt/footprintellipse.h \
    fpt/footprinttext.h \
    fpt/footprintpad.h \
    cat/librarycategory.h \
    cat/categorytreemodel.h \
    cat/categorytreeitem.h \
    elements.h

SOURCES += \
    3dmdl/model3d.cpp \
    cat/componentcategory.cpp \
    cat/packagecategory.cpp \
    cmp/component.cpp \
    fpt/footprint.cpp \
    gencmp/gencompsignal.cpp \
    gencmp/gencompsymbvar.cpp \
    gencmp/gencompsymbvaritem.cpp \
    gencmp/genericcomponent.cpp \
    pkg/package.cpp \
    spcmdl/spicemodel.cpp \
    sym/symbol.cpp \
    sym/symbolellipse.cpp \
    sym/symbolpin.cpp \
    sym/symbolpinpreviewgraphicsitem.cpp \
    sym/symbolpolygon.cpp \
    sym/symbolpreviewgraphicsitem.cpp \
    sym/symboltext.cpp \
    library.cpp \
    librarybaseelement.cpp \
    libraryelement.cpp \
    libraryelementattribute.cpp \
    fpt/footprintpolygon.cpp \
    fpt/footprintellipse.cpp \
    fpt/footprinttext.cpp \
    fpt/footprintpad.cpp \
    cat/librarycategory.cpp \
    cat/categorytreemodel.cpp \
    cat/categorytreeitem.cpp

