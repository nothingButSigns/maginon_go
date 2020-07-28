import QtQuick 2.3
import QtQuick.Controls 2.3
import currentDevice 1.0
import threadSignals 1.0

Item {
    width: 70
    height: 350

    Slider {
        id: rgbLuminositySlider
        width: 20
        height: parent.height
        //x: parent.width - width

        orientation: Qt.Vertical
        snapMode: Slider.SnapOnRelease
        bottomPadding: 6
        topPadding: 6

        stepSize: 1.0
        from: 1.0
        to: 13.0
        value: 1

        FontLoader {
            id: arrowHandle
            source: "light_icons"
        }

        background: Rectangle {
            y: rgbLuminositySlider.topPadding
            implicitWidth: 20
            implicitHeight: 300
            width: colorPalette.width / 2
            height: rgbLuminositySlider.availableHeight
            opacity: 0
        }


        handle: Text {
            y: rgbLuminositySlider.topPadding + rgbLuminositySlider.visualPosition * (rgbLuminositySlider.availableHeight - height)
            font.family: arrowHandle.name
            font.pointSize: 25
            color: "#ffffff"
            text: "\ue805"
        }

    }

    Rectangle {
        id: colorPalette
        x: rgbLuminositySlider.width
        y: rgbLuminositySlider.topPadding
        implicitWidth: 40
        implicitHeight: 300
        width: parent.width - rgbLuminositySlider.width
        height: rgbLuminositySlider.availableHeight
        radius: 8
        color: "#f4f6f4"


        Rectangle {
            height: parent.height / 13
            width: parent.width
            color: "#ff0000"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#24ff00"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: 2 * parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#ffe500"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: 3 * parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#1e0100"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: 4 * parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#e100c1"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: 5 * parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#ffffff"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: 6 * parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#0ce100"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: 7 * parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#e18b00"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: 8 * parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#e1d800"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: 9 * parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#00c9e1"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: 10 * parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#0700e1"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: 11 * parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#15001e"
            border.width: 2
            border.color: "#000000"
        }
        Rectangle {
            y: 12 * parent.height / 13
            height: parent.height / 13
            width: parent.width
            color: "#c5e100"
            border.width: 2
            border.color: "#000000"
        }
    }

}


/*##^##
Designer {
    D{i:0;height:300;width:60}
}
##^##*/
