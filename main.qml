import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Light manager")
    Rectangle {
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


    Grid {
        id: foundLightbulbs
        width: parent.width-50
        height: parent.height-50
        anchors.centerIn: parent
        columns: parent.inPortrait ? 2 : 3
        rows: parent.inPortrait ? 6 : 3
        spacing: 10

        property int objectWidth: Math.round((width - spacing * (columns - 1)) / columns)
        property int objectHeight: Math.round((height - spacing * (rows - 1)) / rows)

        Repeater {
            model: Lightbulb.discoveredDevices

            Rectangle {
                id: lightObject
                width: parent.objectWidth
                height: parent.objectHeight
                color: "#fdab8f"
                border.width: 1
                radius: 5
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        Lightbulb.connectToDevice(modelData.devAddress)
                        viewLoader.source = "LightbulbMenu.qml"

                    }
                }

                Text {
                    id: bulbAddress
                    text: "Device address:\n" + modelData.bulbAddress
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 12
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height/5
                    anchors.horizontalCenter: lightObject

                }


            }

        }

        Loader {
            id: viewLoader
            anchors.fill: parent
        }
    }
    }
}
