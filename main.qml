import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

Window {
    id: window
    visible: true
    title: qsTr("Light manager")

    flags: {
        setMaximumHeight(470)
        setMaximumWidth(350)
        setMinimumHeight(470)
        setMinimumWidth(350)
    }

    FontLoader {
        id: lightIcons
        source: "light_icons"
    }

    Rectangle {
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        color: "#2b5876"
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

        Connections {
            target: Lightbulb

            onDiscoveryFinished:
                statusText.text = "Discovery finished"
            onSearchingForDevices:
                statusText.text = "Searching for devices..."
            onDiscoveryCanceled:
                statusText = "Discovery canceled"
            onDiscoveryError:
                statusText = "Discovery error"
        }



        Grid {
            id: foundLightbulbs
            width: parent.width-25
            height: parent.height-70
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            columns: parent.inPortrait ? 2 : 3
            rows: parent.inPortrait ? 6 : 3
            spacing: 10

            property int objectWidth: Math.round((width - spacing * (columns - 1)) / columns)
            property int objectHeight: Math.round((height - spacing * (rows - 1)) / rows)

            Repeater {
                model: Lightbulb.discoveredDevices

                Item {
                    id: lightObject
                    width: parent.objectWidth
                    height: parent.objectHeight

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(Lightbulb.currDev)
                            {
                                viewLoader.source = "ControlPanel.qml"
                                Lightbulb.connectToDevice(modelData.bulbAddress)
                            }
                            else
                            {
                                Lightbulb.connectToDevice(modelData.bulbAddress)
                                viewLoader.source = "ControlPanel.qml"
                            }
                        }
                    }

                    Text {
                        id: lightDown
                        width: parent.width * 0.7
                        height: parent.height * 0.7
                        font.family: lightIcons.name
                        font.pointSize: 40
                        color: "#808080"
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        text: "\ue804"
                        anchors.horizontalCenter: parent.horizontalCenter
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter

                    }

                    Text {
                        id: bulbAddress
                        text: "Device address:\n" + modelData.bulbAddress
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 12
                        color: "#ffffff"
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: parent.height/5
                    }
                }

            }
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


            Rectangle {
                id: search
                height: 45
                width: parent.width / 4
                color: "black"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.top
                anchors.bottomMargin: 0
                visible: true


                Text {
                    id: searchIcon
                    height: parent.height
                    width: parent.width
                    color: "white"
                    font.family: lightIcons.name
                    font.pointSize: 25
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    text: "\ue806"
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignHCenter

                    MouseArea {
                        width: parent.width
                        height: parent.height
                        anchors.centerIn: parent

                        onClicked: Lightbulb.searchForDevices()
                    }
                }
            }
        }

    }
    Loader {
        id: viewLoader
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
    }

}
