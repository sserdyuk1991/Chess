import QtQuick 2.0

Image {
    source: "/images/resources/images/chessboard.jpg"
    height: width

    property int squareSize: width / 8

    onSquareSizeChanged: Engine.setSquareSize()
}
