import QtQuick 2.3
import QtQuick.Controls 2.3
import QtQuick.Shapes 1.11

Item {
    id: rightNavigator
    width: parent.width
    height: parent.height - statusBar.height
    anchors.top: parent.top
    anchors.topMargin: 0
    anchors.left: parent.left
    anchors.leftMargin: 0
    visible: swipeView.currentIndex == 0 ? true : false
    
    
    Rectangle {
        width: moveToRGB.width
        height: width
        color: "black"
        radius: width/2
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: moveToRGB.height - height/2
        
        
    }
    Rectangle {
        width: moveToRGB.width /2
        height: width * 2
        color: "black"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: moveToRGB.height - height/2
        
    }
    
    Rectangle {
        id: moveToRGB
        height: 150
        width: 50
        color: "black"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        

        MouseArea {
            width: parent.width
            height: parent.height + parent.width / 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            onClicked: {
                if(Lightbulb.currDev.bulbState)
                    Lightbulb.currDev.switchToRGB()

                swipeView.setCurrentIndex(1)
            }
        }

        Text {
            x: 0
            y: 0
            width: parent.width
            height: 20
            color: "white"
            anchors.top: parent.top
            anchors.topMargin: 0
            text: qsTr("RGB")
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }
        
    }
    
    
}

/*##^##
Designer {
    D{i:0;height:450;width:350}
}
##^##*/
