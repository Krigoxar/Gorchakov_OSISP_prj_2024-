#-------------------------------------------------
#
# Project created by QtCreator 2019-07-04T19:02:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessGame_223637
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        actionbutton.cpp \
        basepawnmodel.cpp \
        bishoppawnmodel.cpp \
        boardfield.cpp \
        boardframefield.cpp \
        boardview.cpp \
        boardviewmodel.cpp \
        congratulationsview.cpp \
        constants.cpp \
        gameview.cpp \
        kingpawnmodel.cpp \
        knightpawnmodel.cpp \
        main.cpp \
        pawnfield.cpp \
        pawnpawnmodel.cpp \
        pawnviemodel.cpp \
        playerview.cpp \
        queenpawnmodel.cpp \
        rookpawnmodel.cpp \
        utils.cpp \
        Board.cpp \
        Command.cpp \
        CommandList.cpp \
        Engine.cpp \
        GameObject.cpp \
        GameObjectRegistry.cpp \
        InputManager.cpp \
        MemoryBitStream.cpp \
        NetworkManager.cpp \
        Piece.cpp \
        RandGen.cpp \
        RoboMath.cpp \
        ScoreBoardManager.cpp \
        SocketAddress.cpp \
        SocketAddressFactory.cpp \
        SocketUtil.cpp \
        StringUtils.cpp \
        TCPSocket.cpp \
        Timing.cpp \
        TurnData.cpp \
        UDPSocket.cpp \
        additional-sourcefile.cpp \
        main.cpp

HEADERS += \
        actionbutton.h \
        basepawnmodel.h \
        bishoppawnmodel.h \
        boardfield.h \
        boardframefield.h \
        boardposition.h \
        boardview.h \
        boardviewmodel.h \
        congratulationsview.h \
        constants.h \
        gameview.h \
        helpers.h \
        kingpawnmodel.h \
        knightpawnmodel.h \
        pawnfield.h \
        pawnpawnmodel.h \
        pawnviewmodel.h \
        playerview.h \
        queenpawnmodel.h \
        rookpawnmodel.h \
        utils.h \
        Board.hpp \
        Command.hpp \
        CommandList.hpp \
        Engine.hpp \
        GameObject.hpp \
        GameObjectRegistry.hpp \
        InputAction.hpp \
        InputManager.hpp \
        MemoryBitStream.hpp \
        NetworkManager.hpp \
        Piece.hpp \
        RandGen.hpp \
        RoboCatPCH.hpp \
        RoboCatShared.hpp \
        RoboMath.hpp \
        ScoreBoardManager.hpp \
        SocketAddress.hpp \
        SocketAddressFactory.hpp \
        SocketUtil.hpp \
        StringUtils.hpp \
        TCPSocket.hpp \
        Timing.hpp \
        TurnData.hpp \
        UDPSocket.hpp \
        WeightedTimedMovingAverage.hpp

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
