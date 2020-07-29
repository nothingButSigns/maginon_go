import QtQuick 2.3
import QtQuick.Controls 2.3
import QtQuick.Shapes 1.11

Item {
    id: leftNavigator
    width: parent.width
    height: parent.height - statusBar.height
    anchors.top: parent.top
    anchors.topMargin: 0
    anchors.left: parent.left
    anchors.leftMargin: 0
    visible: swipeView.currentIndex == 1 ? true : false
    
    Rectangle {
        width: moveToWhite.width
        height: width
        color: "black"
        radius: width/2
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: moveToWhite.height - height/2
        
    }
    Rectangle {
        width: moveToWhite.width /2
        height: width * 2
        color: "black"
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: moveToWhite.height - height/2
        
    }
    
    Rectangle {
        id: moveToWhite
        height: 150
        width: 50
        color: "black"
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        
        
        Text {
            width: parent.width
            height: 20
            color: "White"
            anchors.top: parent
            anchors.topMargin: 0
            text: qsTr("White\ncolor")
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }
        
        MouseArea {
            width: parent.width
            height: parent.height + parent.width / 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            onClicked: {
                if(Lightbulb.currDev.bulbState)
                    Lightbulb.currDev.switchToWhite()

                swipeView.setCurrentIndex(0)
            }
        }
        
    }
}
