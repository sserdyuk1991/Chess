import QtQuick 2.0

Image {
    height : width

    property string src
    source: src

    MouseArea {
        anchors.fill: parent
        drag.target: parent
        drag.maximumX: parent.parent.width
        drag.maximumY: parent.parent.height

        property int startX
        property int startY

        onPressed: {
            console.log(parent.parent.width, parent.parent.height)
            startX = parent.x + mouseX
            startY = parent.y + mouseY
        }

        onReleased: {
            Engine.move(startX, startY, parent.x + mouseX, parent.y + mouseY)
        }
    }
}
