import QtQuick 2.3
import QtQuick.Controls 2.3
import QtQuick.Shapes 1.11
import currentDevice 1.0

Rectangle {
    width: 350
    height: 470
    color: "#2b5876"
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#151916"
        }

        GradientStop {
            position: 1
            color: "#52825e"
        }
    }
    anchors.fill: parent

    Connections {
        target: Lightbulb.currDev

        onRgbEnabled: {
            swipeView.currentIndex = 1
        }
    }

    SwipeView {
        id: swipeView
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        currentIndex: 0
        enabled: true

        Item {
            id: whiteLightMenu
            Loader {
                source: "LightbulbMenu.qml"
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
            }
        }

        Item {
            id: rgbLightMenu
            Loader {
                source: "RGBMenu.qml"
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
            }
        }


    }
    RightNavigator {
        id: rightNavigator
    }

    LeftNavigator {
        id: leftNavigator
    }

    LeftBackButton {
        id: leftBackButton
    }


    RightBackButton {
        id: rightBackButton
    }

    Rectangle {
        id: statusBar
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
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
        }
    }



}
