import QtQuick 2.0
import QtQuick.Controls 2.3

Rectangle {
    width: 640
    height: 480
    color: "#2b5876"
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#2b5876"
        }

        GradientStop {
            position: 1
            color: "#4e4376"
        }
    }
    anchors.fill: parent

    FontLoader {
       id: onOff
       source: "on_off_sign"
    }

    Text {
        width: 80
        height: 80
        font.family: onOff.name
        font.pointSize: 40
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        text: "\ue800"

        MouseArea {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            anchors.centerIn: parent
            onClicked: Lightbulb.executeCommand(1)

        }
    }

    Text {
        width: 80
        height: 80
        font.family: onOff.name
        font.pointSize: 40
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        text: "\ue800"

        MouseArea {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            anchors.centerIn: parent
            onClicked: Lightbulb.executeCommand(2)
        }
    }

    Connections {
        target: Lightbulb.connTh

        onRandomStringChanged: {
            statusText.text = Lightbulb.connTh.randomString
            console.log("signal occured")
        }

    }

    Rectangle {
        height: 20
        width: parent.width
        color: "black"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        Text {
            id: statusText
            height: parent.height
            width: 100
            color: "white"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            text: qsTr("status bar")
        }
    }



}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
