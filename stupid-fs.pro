TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    commands/touch.cpp \
    Stmt.cpp \
    commands/rm.cpp \
    commands/cd.cpp \
    commands/cp.cpp \
    commands/ls.cpp \
    commands/mkdir.cpp \
    commands/mv.cpp \
    Node.cpp \
    Directory.cpp \
    File.cpp \
    Env.cpp \
    commands/rmdir.cpp \
    commands/pwd.cpp \
    Database.cpp

HEADERS += \
    commands/touch.h \
    Stmt.h \
    commands/rm.h \
    commands/cd.h \
    commands/cp.h \
    commands/ls.h \
    commands/mkdir.h \
    commands/mv.h \
    Node.h \
    Directory.h \
    File.h \
    Env.h \
    commands/rmdir.h \
    commands/pwd.h \
    Database.h
