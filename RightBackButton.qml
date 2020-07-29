import QtQuick 2.3
import QtQuick.Controls 2.3
import QtQuick.Shapes 1.11


Item {
    id: rightBackButton
    width: parent.width / 4
    height: 50
    anchors.right: parent.right
    anchors.rightMargin: 0
    anchors.top: parent.top
    anchors.topMargin: 0
    visible: swipeView.currentIndex == 1 ? true : false
    
    Rectangle {
        width: comp2.height / 2
        height: width
        color: "black"
        anchors.right: parent.right
        anchors.rightMargin: comp2.anchors.rightMargin + comp2.width / 2 + 0.5
    }
    
    Rectangle {
        id: comp2
        height: base2.height
        width: height
        radius: height / 2
        anchors.right: parent.right
        anchors.rightMargin: base2.width - width / 2
        color: "black"
    }
    
    Rectangle {
        id: base2
        height: parent.height * 0.7
        width: height * 1.5
        anchors.right: parent.right
        anchors.rightMargin: 0
        color: "black"
    }
    
    Text {
        height: 35
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: parent.height * 0.20
        color: "#ffffff"
        text: ">>"
        verticalAlignment: Text.AlignBottom
        font.pointSize: 30
        
        MouseArea {
            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            onClicked: {
                viewLoader.source = ""
                viewLoader.source = "main.qml"
                viewLoader.source = ""
            }
        }
    }
    
    
}
