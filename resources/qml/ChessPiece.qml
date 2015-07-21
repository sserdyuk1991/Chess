import QtQuick 2.0

Image {
    height : width

    property string src
    source: src

    MouseArea {
        anchors.fill: parent
        drag.target: parent

        property int startX
        property int startY

        onPressed: {
            startX = parent.x + mouseX
            startY = parent.y + mouseY
        }

        onReleased: {
            Engine.move(startX, startY, parent.x + mouseX, parent.y + mouseY)
        }
    }
}
