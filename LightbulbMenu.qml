import QtQuick 2.0
import QtQuick.Controls 2.3
import currentDevice 1.0
import threadSignals 1.0

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
        id: onOffBulbIcon
        width: 80
        height: 80
        font.family: onOff.name
        font.pointSize: 40
        color: "#808080"
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        text: "\ue800"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        MouseArea {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            anchors.centerIn: parent
            onClicked: Lightbulb.currDev.turnOnOff()

        }
    }


    Connections {
        target: Lightbulb.connTh
        onConnectionStateChanged: {
            console.log("conn state changed")
            if (Lightbulb.connTh.connectionState === ThreadSignal.CONNECTED)
                statusText.text = "Connected"
            else if (Lightbulb.connTh.connectionState === ThreadSignal.CONNECTING)
                statusText.text = "Connecting"
            else if (Lightbulb.connTh.connectionState === ThreadSignal.DISCONNECTED)
                statusText.text = "Disconnected"
        }
    }


    Connections {
        target: Lightbulb.currDev

        onActionStateChanged: {
            console.log("action state changed")
            console.log(Lightbulb.currDev.actionState)

            if (Lightbulb.currDev.actionState === Device.READ_ERROR)
                statusText.text = "Cannot read current lightbulb state"
            else if (Lightbulb.currDev.actionState === Device.WRITE_ERROR)
                statusText.text = "Cannot send command to the lightbulb"
            else if (Lightbulb.currDev.actionState === Device.WRITE_SUCCESS)
                statusText.text = "Command sent"
            else if (Lightbulb.currDev.actionState === Device.READ_SUCCESS)
            {
                statusText.text = "Got current state"
                console.log("\n got current state")
            }
            else
                statusText.text = "Unknown error occured"
        }

        onBulbStateChanged: {
            if (Lightbulb.currDev.bulbState)
                onOffBulbIcon.color = "#ffff00"
            else
                onOffBulbIcon.color = "#808080"
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
            anchors.centerIn: parent
            text: qsTr("Status bar")
        }
    }



}


