import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

/*
Rectangle {
    width: 80
    height: 200

*/

    Gauge {
        id: gauge
        anchors.fill: parent
        anchors.margins: 10

        maximumValue: 100

        value: 65
        Behavior on value {
            NumberAnimation {
                duration: 50
               
            }
        }

        style: GaugeStyle {
            valueBar: Rectangle {
                implicitWidth: 16
                color: Qt.rgba(gauge.value / gauge.maximumValue, 0, 1 - gauge.value / gauge.maximumValue, 1)
            }
        }
    }
//}
