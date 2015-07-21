import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Chess")
    visible: true
    width: 800
    height: 600

    Chessboard {
        objectName: "gameField"
        width: parent.height
    }

    ColumnLayout {
        x: parent.height
        width: parent.width - parent.height

        Button {
            id: startButton
            text: "Start"
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 25

            onClicked: {
                Engine.start()
                startButton.visible = false
                loadButton.visible = false
                prevButton.visible = false
                nextButton.visible = false
                stopButton.visible = true
                saveButton.visible = true
            }
        }

        Button {
            id: loadButton
            text: "Load"
            anchors.top: startButton.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5

            onClicked: loadDialog.open()

            FileDialog {
                id: loadDialog

                onAccepted: {
                    Engine.load(fileUrl)
                    prevButton.visible = true
                    nextButton.visible = true
                }
            }
        }

        Button {
            id: stopButton
            text: "Stop"
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 25
            visible: false

            onClicked: {
                Engine.stop()
                stopButton.visible = false
                saveButton.visible = false
                startButton.visible = true
                loadButton.visible = true
            }
        }

        Button {
            id: saveButton
            text: "Save"
            anchors.top: stopButton.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
            visible: false

            onClicked: saveDialog.open()

            FileDialog {
                id: saveDialog
                selectExisting: false

                onAccepted: Engine.save(fileUrl)
            }
        }

        Button {
            id: prevButton
            text: "Prev"
            anchors.top: saveButton.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
            visible: false

            onClicked: Engine.prev()
        }

        Button {
            id: nextButton
            text: "Next"
            anchors.top: prevButton.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
            visible: false

            onClicked: Engine.next()
        }
    }
}
