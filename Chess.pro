TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    chessboardmanager.cpp \
    chesspieces/bishop.cpp \
    chesspieces/chesspiece.cpp \
    chesspieces/king.cpp \
    chesspieces/knight.cpp \
    chesspieces/pawn.cpp \
    chesspieces/queen.cpp \
    chesspieces/rook.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    chessboardmanager.h \
    chesspieces/bishop.h \
    chesspieces/chesspiece.h \
    chesspieces/king.h \
    chesspieces/knight.h \
    chesspieces/pawn.h \
    chesspieces/queen.h \
    chesspieces/rook.h
