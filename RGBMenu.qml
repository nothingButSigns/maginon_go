import QtQuick 2.3
import QtQuick.Controls 2.3

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
            onClicked: Lightbulb.currDev.turnOnOff()

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

        enabled: true
        //onValueChanged: Lightbulb.currDev.changeLuminosity(value)
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
