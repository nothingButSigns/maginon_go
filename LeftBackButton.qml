import QtQuick 2.3
import QtQuick.Controls 2.3
import QtQuick.Shapes 1.11


Item {
    id: leftBackButton
    width: parent.width / 4
    height: 50
    anchors.left: parent.left
    anchors.leftMargin: 0
    anchors.top: parent.top
    anchors.topMargin: 0
    visible: swipeView.currentIndex == 0 ? true : false
    
    
    Rectangle {
        width: comp.height / 2
        height: width
        color: "black"
        anchors.left: parent.left
        anchors.leftMargin: comp.anchors.leftMargin + comp.width / 2 - 1
    }
    
    Rectangle {
        id: comp
        height: base.height
        width: height
        radius: height / 2
        anchors.left: parent.left
        anchors.leftMargin: base.width - width / 2
        color: "black"
    }
    
    Rectangle {
        id: base
        height: parent.height * 0.7
        width: height * 1.5
        anchors.left: parent.left
        anchors.leftMargin: 0
        color: "black"
    }
    
    Text {
        height: 35
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: parent.height * 0.20
        color: "#ffffff"
        text: "<<"
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
