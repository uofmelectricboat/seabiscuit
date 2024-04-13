

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import seabiscuit2
import "../main.qml" as Main

Rectangle {
    width: Constants.width
    height: Constants.height
    color: Constants.backgroundColor

    Text {
        id: mphval
        x: 168
        y: 160
        width: 462
        height: 265
        text: Main.app_VCU_SPEED_MPH.toString()
        font.pixelSize: 200
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
    }

    Text {
        id: mphlabel
        x: 636
        y: 323
        width: 191
        height: 102
        text: qsTr("MPH")
        font.pixelSize: 80
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignBottom
    }

    Text {
        id: rpmval
        x: 991
        y: 160
        width: 552
        height: 210
        text: Main.app_VCU_ENGINE_SPEED_RPM.toString()
        font.pixelSize: 180
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
    }

    Text {
        id: rpmlabel
        x: 1549
        y: 268
        width: 191
        height: 102
        text: qsTr("RPM")
        font.pixelSize: 80
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignBottom
    }

    ProgressBar {
        id: progressBar
        x: 991
        y: 376
        width: 749
        height: 49
        value: 0.5
    }

    Item {
        id: item1
        x: 198
        y: 595
        width: 300
        height: 300

        Text {
            id: val1
            x: 77
            y: 89
            width: 147
            height: 122
            text: Main.app_VCU_BATTERY_CHARGE_PERCENTAGE.toString()
            font.pixelSize: 80
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: type1
            x: 8
            y: 8
            text: qsTr("BATT%")
            font.pixelSize: 30
        }

        Text {
            id: unit1
            x: 267
            y: 256
            text: qsTr("%")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignBottom
        }
    }

    Item {
        id: item2
        x: 504
        y: 595
        width: 300
        height: 300

        Text {
            id: val2
            x: 77
            y: 89
            width: 147
            height: 122
            text: Main.app_VCU_BATTERY_TEMPERATURE_DEGREES_C.toString()
            font.pixelSize: 80
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: type2
            x: 8
            y: 8
            text: qsTr("BATT TEMP")
            font.pixelSize: 30
        }

        Text {
            id: unit2
            x: 267
            y: 256
            text: qsTr("°C")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignBottom
        }
    }

    Item {
        id: item3
        x: 810
        y: 595
        width: 300
        height: 300

        Text {
            id: val3
            x: 77
            y: 89
            width: 147
            height: 122
            text: Main.app_VCU_MOTOR_TEMPERATURE_DEGREES_C.toString()
            font.pixelSize: 80
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: type3
            x: 8
            y: 8
            text: qsTr("MOTOR TEMP")
            font.pixelSize: 30
        }

        Text {
            id: unit3
            x: 258
            y: 256
            text: qsTr("°C")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignBottom
        }
    }

    Item {
        id: item4
        x: 1117
        y: 595
        width: 300
        height: 300

        Text {
            id: val4
            x: 77
            y: 89
            width: 147
            height: 122
            text: qsTr("12")
            font.pixelSize: 80
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: type4
            x: 8
            y: 8
            text: Main.app_VCU_BATTERY_POWER_KW.toString()
            font.pixelSize: 30
        }

        Text {
            id: unit4
            x: 248
            y: 256
            text: qsTr("kW")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignBottom
        }
    }

    Item {
        id: item5
        x: 1423
        y: 595
        width: 300
        height: 300

        Rectangle {
            id: background5
            anchors.fill: parent
            color: "#f74848"
        }

        Text {
            id: val5
            x: 77
            y: 89
            width: 147
            height: 122
            text: qsTr("BAD")
            font.pixelSize: 80
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: type5
            x: 8
            y: 8
            text: qsTr("WATER STATUS")
            font.pixelSize: 30
        }
    }
}
