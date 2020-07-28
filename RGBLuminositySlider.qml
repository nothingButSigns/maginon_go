import QtQuick 2.3
import QtQuick.Controls 2.3
import currentDevice 1.0
import threadSignals 1.0

Slider {
    id: luminositySlider
    orientation: Qt.Vertical
    snapMode: Slider.SnapOnRelease

    background: Rectangle {
        x: luminositySlider.leftPadding
        y: luminositySlider.topPadding + luminositySlider.availableHeight / 2 - height / 2
        implicitWidth: 10
        implicitHeight: 300
        width: luminositySlider.availableWidth
        height: implicitHeight
        radius: 8
        color: "#f4f6f4"
        border.width: 2
        border.color: "#000000"

        Rectangle {
            height: luminositySlider.visualPosition * parent.height
            width: parent.width
            color: "#3e4541"
            radius: 8
        }
    }

    handle: Rectangle {
        x: luminositySlider.leftPadding + luminositySlider.availableWidth / 2 - width / 2
        y: luminositySlider.topPadding + luminositySlider.visualPosition * (luminositySlider.availableHeight - height)
        color: luminositySlider.pressed ? "#ffffff" : "#000000"
        implicitWidth: 35
        implicitHeight: 25
        radius: 5
        border.width: 2
        border.color: "#121312"

    }

}


