CONFIG -= qt

TARGET = logic
TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    parser/memfilereader.cpp \
    processor/programcommand.cpp \
    processor/programstate.cpp \
    processor/registers.cpp \
    processor/io.cpp \
    processor/instructions.cpp \
    processor/memory.cpp \
    processor/processorstate.cpp \
    processor/cpu.cpp \

HEADERS += \
    model.h \
    parser/memfilereader.h \
    processor/programcommand.h \
    processor/programstate.h \
    processor/registers.h \
    processor/io.h \
    processor/instructions.h \
    processor/memory.h \
    processor/processorstate.h \
    processor/cpu.h \
