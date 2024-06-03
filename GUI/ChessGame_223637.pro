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
INCLUDEPATH += GUI/include/ Network/include/ $$[QT_INSTALL_PREFIX]/src/3rdparty/zlib
CONFIG += c++14

SOURCES += GUI/source/actionbutton.cpp GUI/source/basepawnmodel.cpp GUI/source/bishoppawnmodel.cpp GUI/source/boardfield.cpp GUI/source/boardframefield.cpp GUI/source/boardview.cpp GUI/source/boardviewmodel.cpp GUI/source/congratulationsview.cpp GUI/source/constants.cpp GUI/source/gameview.cpp GUI/source/kingpawnmodel.cpp GUI/source/knightpawnmodel.cpp GUI/source/main.cpp GUI/source/pawnfield.cpp GUI/source/pawnpawnmodel.cpp GUI/source/pawnviemodel.cpp GUI/source/playerview.cpp GUI/source/queenpawnmodel.cpp GUI/source/rookpawnmodel.cpp GUI/source/utils.cpp GUI/source/BoardAdapter.cpp\
Network/source/Board.cpp Network/source/Command.cpp Network/source/CommandList.cpp Network/source/Engine.cpp Network/source/GameObject.cpp Network/source/GameObjectRegistry.cpp Network/source/InputManager.cpp Network/source/MemoryBitStream.cpp Network/source/NetworkManager.cpp Network/source/Piece.cpp Network/source/RandGen.cpp Network/source/RoboMath.cpp Network/source/ScoreBoardManager.cpp Network/source/SocketAddress.cpp Network/source/SocketAddressFactory.cpp Network/source/SocketUtil.cpp Network/source/StringUtils.cpp Network/source/TCPSocket.cpp Network/source/Timing.cpp Network/source/TurnData.cpp Network/source/UDPSocket.cpp

HEADERS += GUI/include/actionbutton.h GUI/include/basepawnmodel.h GUI/include/bishoppawnmodel.h GUI/include/boardfield.h GUI/include/boardframefield.h GUI/include/boardposition.h GUI/include/boardview.h GUI/include/boardviewmodel.h GUI/include/congratulationsview.h GUI/include/constants.h GUI/include/gameview.h GUI/include/kingpawnmodel.h GUI/include/knightpawnmodel.h GUI/include/pawnfield.h GUI/include/pawnpawnmodel.h GUI/include/pawnviewmodel.h GUI/include/playerview.h GUI/include/queenpawnmodel.h GUI/include/rookpawnmodel.h GUI/include/utils.h GUI/include/BoardAdapter.hpp\
Network/include/Board.hpp Network/include/Command.hpp Network/include/CommandList.hpp Network/include/Engine.hpp Network/include/GameObject.hpp Network/include/GameObjectRegistry.hpp Network/include/InputAction.hpp Network/include/InputManager.hpp Network/include/MemoryBitStream.hpp Network/include/NetworkManager.hpp Network/include/Piece.hpp Network/include/RandGen.hpp Network/include/RoboCatPCH.hpp Network/include/RoboCatShared.hpp Network/include/RoboMath.hpp Network/include/ScoreBoardManager.hpp Network/include/SocketAddress.hpp Network/include/SocketAddressFactory.hpp Network/include/SocketUtil.hpp Network/include/StringUtils.hpp Network/include/TCPSocket.hpp Network/include/Timing.hpp Network/include/TurnData.hpp Network/include/UDPSocket.hpp Network/include/WeightedTimedMovingAverage.hpp
LIBS += -lz
FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
