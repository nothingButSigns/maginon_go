import QtQuick 2.3
import QtQuick.Controls 2.3
import currentDevice 1.0
import threadSignals 1.0

Slider {
    id: luminositySlider
    orientation: Qt.Horizontal
    snapMode: Slider.SnapOnRelease

    background: Rectangle {
        y: luminositySlider.topPadding
        x: luminositySlider.leftPadding + luminositySlider.availableWidth / 2 - width / 2
        implicitWidth: 300
        implicitHeight: 10
        height: luminositySlider.availableHeight
        width: implicitWidth
        radius: 8
        color: "#3e4541"

        Rectangle {
            width: luminositySlider.visualPosition * parent.width
            height: parent.height
            color: "#f4f6f4"
            radius: 8
            border.width: 2
            border.color: "#000000"
        }
    }

    handle: Rectangle {
        y: luminositySlider.topPadding + luminositySlider.availableHeight / 2 - height / 2
        x: luminositySlider.leftPadding + luminositySlider.visualPosition * (luminositySlider.availableWidth - width)
        color: luminositySlider.pressed ? "#ffffff" : "#000000"
        implicitWidth: 25
        implicitHeight: 35
        radius: 5
        border.width: 2
        border.color: "#121312"

    }

}

/*##^##
Designer {
    D{i:0;height:30;width:260}
}
##^##*/
