import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4


Rectangle {
    width: 80
    height: 200
    border.width: 1
    border.color: "lightGray"

    gradient: Gradient {
        GradientStop { position: 0.0; color: "aliceblue" }
        GradientStop { position: 1.0; color: "gainsboro" }
    }

    Gauge {
    

        id: gauge
        anchors.fill: parent
        anchors.margins: 10

        maximumValue: 100

        property int myVal
        value: myVal
        Behavior on value {
            NumberAnimation {
                duration: 50
               
            }
        }

        font.weight: Font.Bold
    
        style: GaugeStyle {
            tickmark: Item {
                implicitWidth: 18
                implicitHeight: 1

                Rectangle {
                    color: "gray"
                    anchors.fill: parent
                    anchors.leftMargin: 3
                    anchors.rightMargin: 3
                }
            }
            minorTickmark: Item {
                implicitWidth: 14
                implicitHeight: 1

                Rectangle {
                    color: "gray"
                    anchors.fill: parent
                    anchors.leftMargin: 2
                    anchors.rightMargin: 4
                }
            }
            valueBar: Rectangle {
                implicitWidth: 16
                color: Qt.rgba(gauge.value / gauge.maximumValue, 0, 1 - gauge.value / gauge.maximumValue, 1)
            }
        }
    }
}
