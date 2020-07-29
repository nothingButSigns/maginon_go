import QtQuick 2.3
import QtQuick.Controls 2.3
import currentDevice 1.0

Rectangle {
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

    Connections {
        target: Lightbulb.currDev

        onActionStateChanged: {

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
            if(Lightbulb.currDev.RGBLuminosityVal === Device.R_UNKNOWN)
            {
                luminositySlider.enabled = false
                statusText.text = "Unknown RGB luminosity value"
            }
            else
            {
                luminositySlider.value = Lightbulb.currDev.RGBLuminosityVal
            }
        }
    }

    Text {

        id: onOffBulbIcon
        font.family: lightIcons.name
        font.pointSize: 50
        color: "#808080"
        anchors.top: parent.top
        text: "\ue802"
        anchors.topMargin: 30
        anchors.horizontalCenterOffset: -120
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        MouseArea {
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            onClicked: {
                Lightbulb.currDev.turnOnOff()
//                if (Lightbulb.currDev.rgbOn)
//                    Lightbulb.currDev.turnOnOff()
//                else
//                {
//                    Lightbulb.currDev.turnOnOff()
//                    Lightbulb.currDev.switchToRGB()
//                }
            }
        }
    }

    RGBLuminositySlider {
        id: luminositySlider
        width: 30
        height: 350
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        bottomPadding: 6
        topPadding: 6
        anchors.top: parent.top
        anchors.topMargin: rgbSlider.anchors.topMargin

        stepSize: 1.0

        from: 1.0
        to: 9.0
        value: 1

        property bool moved: false

        enabled: true
        onMoved: moved = true
        onValueChanged: {
            if(moved) {
                enabled = false
                Lightbulb.currDev.changeRGBLuminosity(value)
            }
        }
    }

    Text {

        id: lightUp
        font.family: lightIcons.name
        font.pointSize: 20
        color: "#808080"
        anchors.top: parent.top
        anchors.topMargin: luminositySlider.anchors.topMargin
        text: "\ue803"
        anchors.horizontalCenterOffset: luminositySlider.anchors.horizontalCenterOffset - 30
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
        anchors.topMargin: luminositySlider.anchors.topMargin + luminositySlider.height * 0.85
        text: "\ue801"
        anchors.horizontalCenterOffset: lightUp.anchors.horizontalCenterOffset
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

    }



    ColorSlider {
        id: rgbSlider
        anchors.right: parent.right
        anchors.rightMargin: 0

        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.15



        enabled: true
       // onValueChanged: Lightbulb.currDev.changeLuminosity(value)

    }


}
