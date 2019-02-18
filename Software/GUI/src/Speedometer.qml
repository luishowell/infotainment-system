import QtQuick 2.0
import QtQuick.Extras 1.4

CircularGauge {
    id: speedo1
    objectName: id

    property int value: 0
    maximumValue : 100 
    

    //property bool accelerating: false

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
    
    /*
    Connections{
        target: Diagnostics
        OnSpeedChanged: CircularGauge.value = dataToGauge
    }
    */
}
