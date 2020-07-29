import QtQuick 2.3
import QtQuick.Controls 2.4

import currentDevice 1.0
import threadSignals 1.0

Slider {
    id: luminositySlider
    orientation: Qt.Horizontal
    snapMode: Slider.SnapAlways
    live: false
    enabled: true
    opacity: enabled ? 1.0 : 0.4

    background: Rectangle {
        y: luminositySlider.topPadding
        x: luminositySlider.leftPadding + luminositySlider.availableWidth / 2 - width / 2
        implicitWidth: 300
        implicitHeight: 10
        height: luminositySlider.availableHeight
        width: implicitWidth
        radius: 8
        color: luminositySlider.enabled ? "#3e4541" : "#333333"

        Rectangle {
            width: luminositySlider.visualPosition * parent.width
            height: parent.height
            color: luminositySlider.enabled ? "#f4f6f4" : "#808080"
            radius: 8
            border.width: 2
            border.color: "#000000"
        }
    }

    handle: Rectangle {
        y: luminositySlider.topPadding + luminositySlider.availableHeight / 2 - height / 2
        x: luminositySlider.leftPadding + luminositySlider.visualPosition * (luminositySlider.availableWidth - width)
        color: luminositySlider.enabled ? (luminositySlider.pressed ? "#ffffff" : "#000000") : "#333333"
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
