import QtQuick 2.15
import QtQuick.Controls 2.15
import prototype2 1.0
import QtCharts 2.3
import QtQuick3D 1.15
import QtWebView 1.14
import QtSensors 5.9
import QtQuickUltralite.Extras 1.7
import FlowView 1.0
import QtQuick.Studio.Components 1.0

Rectangle {
    width: 1024
    height: 600
    opacity: 1
    visible: true
    color: "#060c24"
    focus: false
    antialiasing: false
    layer.samples: 2
    layer.effect: line1
    enabled: true
    layer.enabled: false
    layer.mipmap: false
    layer.textureSize.height: 1
    layer.textureSize.width: 1
    layer.smooth: false
    scale: 1
    transformOrigin: Item.Center

    clip: false

    ChartView {
        id: line
        x: 20
        y: 86
        width: 250
        height: 180
        LineSeries {
            name: "LineSeries"
            XYPoint {
                x: 0
                y: 2
            }

            XYPoint {
                x: 1
                y: 1.2
            }

            XYPoint {
                x: 2
                y: 3.3
            }

            XYPoint {
                x: 5
                y: 2.1
            }
        }
    }

    ChartView {
        id: line1
        x: 276
        y: 86
        width: 250
        height: 180
        LineSeries {
            name: "LineSeries"
            XYPoint {
                x: 0
                y: 2
            }

            XYPoint {
                x: 1
                y: 1.2
            }

            XYPoint {
                x: 2
                y: 3.3
            }

            XYPoint {
                x: 5
                y: 2.1
            }
        }
    }

    ChartView {
        id: line2
        x: 532
        y: 86
        width: 250
        height: 180
        LineSeries {
            name: "LineSeries"
            XYPoint {
                x: 0
                y: 2
            }

            XYPoint {
                x: 1
                y: 1.2
            }

            XYPoint {
                x: 2
                y: 3.3
            }

            XYPoint {
                x: 5
                y: 2.1
            }
        }
    }

    Switch {
        id: switch2
        x: 50
        y: 422
        width: 140
        height: 40
        text: qsTr("Switch")
        padding: 6
        font.capitalization: Font.AllUppercase
        font.pointSize: 10
        font.bold: true
    }

    Switch {
        id: switch3
        x: 50
        y: 468
        width: 140
        height: 40
        text: qsTr("Switch")
        padding: 6
        font.capitalization: Font.AllUppercase
        font.pointSize: 10
        font.bold: true
    }

    Switch {
        id: switch1
        x: 50
        y: 376
        width: 140
        height: 40
        text: qsTr("Switch")
        padding: 6
        font.capitalization: Font.AllUppercase
        font.pointSize: 10
        font.bold: true
    }

    Rectangle {
        id: rectangle
        x: 284
        y: 342
        width: 399
        height: 200
        visible: true
        color: "#00ffffff"
        border.color: "#ffffff"
    }

    Text {
        id: text1
        x: 304
        y: 357
        width: 359
        height: 171
        color: "#ffffff"
        text: qsTr("Text")
        font.pixelSize: 12
        styleColor: "#ffffff"
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:7}D{i:13}D{i:19}D{i:20}D{i:21}
}
##^##*/

