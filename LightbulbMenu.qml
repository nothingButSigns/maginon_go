import QtQuick 2.3
import QtQuick.Controls 2.3
import currentDevice 1.0
import threadSignals 1.0

Rectangle {
    id: rectangle
    width: 350
    height: 470
    color: "#213c21"
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#213c21"
        }

        GradientStop {
            position: 0.6
            color: "#151916"
        }


        GradientStop {
            position: 1
            color: "#000000"
        }
    }
    anchors.fill: parent

    FontLoader {
        id: lightIcons
        source: "light_icons"
    }

    Text {

        id: onOffBulbIcon
        font.family: lightIcons.name
        font.pointSize: 50
        color: "#808080"
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.08
        text: "\ue802"
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        MouseArea {
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            onClicked: {
                if (!Lightbulb.currDev.bulbState)
                {
                    Lightbulb.currDev.turnOnOff()
                    Lightbulb.currDev.switchToWhite()
                }
                else
                    Lightbulb.currDev.turnOnOff()
            }

        }
    }

    Text {

        id: lightUp
        font.family: lightIcons.name
        font.pointSize: 20
        color: "#808080"
        anchors.top: parent.top
        anchors.topMargin: luminositySlider.anchors.topMargin - luminositySlider.height * 1.3
        text: "\ue803"
        anchors.horizontalCenterOffset: parent.width /2.5
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

    }

    Text {

        id: lightDown
        font.family: lightIcons.name
        font.pointSize: 20
        color: "#808080"
        anchors.top: parent.top
        anchors.topMargin: luminositySlider.anchors.topMargin - luminositySlider.height * 1.3

        text: "\ue801"
        anchors.horizontalCenterOffset: - parent.width /2.5
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

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
            {
                luminositySlider.enabled = true
                statusText.text = "Command sent succesfully"
            }
            else if (Lightbulb.currDev.actionState === Device.READ_SUCCESS)
            {
                statusText.text = "Got current state"
                console.log("\n got current state")
            }
            else
                statusText.text = "Unknown error occured"
        }

        onBulbStateChanged: {
            if (Lightbulb.currDev.bulbState) {
                luminositySlider.enabled = true
                onOffBulbIcon.color = "#ffff00"
            }
            else {
                luminositySlider.enabled = false
                onOffBulbIcon.color = "#808080"
            }
        }

        onLuminosityValChanged: {
            if(Lightbulb.currDev.luminosityVal === Device.UNKNOWN)
            {
                luminositySlider.enabled = false
                statusText.text = "Unknown luminosity value"
            }
            else
            {
                luminositySlider.value = Lightbulb.currDev.luminosityVal
            }
        }

    }




    LuminositySlider {
        id: luminositySlider
        width: 260
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
        bottomPadding: 6
        topPadding: 6
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.48

        stepSize: 1.0

        from: 1.0
        to: 5.0
        value: 1

        property bool moved: false

        enabled: true
        onMoved: moved = true
        onValueChanged: {
            if(moved) {
                enabled = false
                Lightbulb.currDev.changeLuminosity(value)

            }
        }
        
    }




}





/*##^##
Designer {
    D{i:0;height:470;width:350}
}
##^##*/
