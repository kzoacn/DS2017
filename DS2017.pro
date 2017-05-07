#-------------------------------------------------
#
# Project created by QtCreator 2017-04-07T14:41:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DS2017
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    adminwindow.cpp \
    minewindow.cpp

HEADERS  += mainwindow.h \
    src/lib/algo.hpp \
    src/lib/Date.hpp \
    src/lib/map.hpp \
    src/lib/set.hpp \
    src/lib/shared_ptr.hpp \
    src/lib/vector.hpp \
    src/Admin.hpp \
    src/FileManager.hpp \
    src/Station.hpp \
    src/Train.hpp \
    src/User.hpp \
    logindialog.h \
    src/RailwayMinistry.hpp \
    src/Ticket.hpp \
    adminwindow.h \
    src/CSVParser.hpp \
    minewindow.h \
    src/lib/exceptions.hpp \
    src/lib/utility.hpp \
    src/LoginManager.hpp \
    src/Log.hpp

FORMS    += mainwindow.ui \
    logindialog.ui \
    adminwindow.ui \
    minewindow.ui


