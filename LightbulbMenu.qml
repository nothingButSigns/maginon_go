import QtQuick 2.0
import QtQuick.Controls 2.3

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

    FontLoader {
       id: onOff
       source: "on_off_sign"
    }

    Text {
        font.family: onOff.name
        font.pointSize: 40
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        text: "\ue800"
    }



}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
