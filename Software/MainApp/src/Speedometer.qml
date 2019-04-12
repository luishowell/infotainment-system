import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0

    CircularGauge {
        id: speedo1
        objectName: id

        property int value: 0
        maximumValue : 100 
        
        property int minWidth: 100
        property int minHeight: 100
        property int maxWidth: 100
        property int maxHeight: 100
    
        //Component.onCompleted: forceActiveFocus()

        Behavior on value {
            NumberAnimation {
                duration: 1
            }
        }
        
    
        style: CircularGaugeStyle {
            id: style

            function degreesToRadians(degrees) {
                return degrees * (Math.PI / 180);
            }

            background: Item {
                Rectangle
                {
                    width: parent.width; height: parent.width;
                    border.width: 1
                    border.color: "lightGray"

                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "aliceblue" }
                        GradientStop { position: 1.0; color: "gainsboro" }
                    }
                }
            }

            tickmark: Rectangle {
                visible: styleData.value < 80 || styleData.value % 10 == 0
                implicitWidth: outerRadius * 0.02
                antialiasing: true
                implicitHeight: outerRadius * 0.06
                color: styleData.value >= 80 ? "#e34c22" : "#black"
            }

            minorTickmark: Rectangle {
          //visible: styleData.value < 80
                implicitWidth: outerRadius * 0.01
                antialiasing: true
                implicitHeight: outerRadius * 0.03
                color: styleData.value >= 80 ? "#e34c22" : "#black"
            }

            tickmarkLabel:  Text {
                font.pixelSize: Math.max(6, outerRadius * 0.1)
                text: styleData.value
                color: styleData.value >= 80 ? "#e34c22" : "#black"
                antialiasing: true
            }

            
        }

    }



