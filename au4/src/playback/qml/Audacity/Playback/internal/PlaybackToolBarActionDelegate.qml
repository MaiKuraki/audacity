/*
* Audacity: A Digital Audio Editor
*/
import QtQuick 2.15
import QtQuick.Layouts 1.12

import Muse.Ui 1.0
import Muse.UiComponents 1.0

Item {
    id: root

    height: parent ? parent.height : implicitHeight
    width: parent ? parent.width : implicitWidth

    property var item

    property var navigationPanel: null
    property int navigationRow: 0

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 6
        anchors.rightMargin: 6

        spacing: 16

        VisibilityBox {
            id: visibilityButton

            Layout.alignment: Qt.AlignLeft

            navigation.panel: root.navigationPanel
            navigation.row: root.navigationRow
            navigation.column: 1
            accessibleText: titleLabel.text

            isVisible: root.item.checked

            onVisibleToggled: {
                root.item.checked = !root.item.checked
            }
        }

        StyledIconLabel {
            Layout.alignment: Qt.AlignLeft

            width: 36
            height: width

            iconCode: Boolean(root.item) ? root.item.icon : IconCode.NONE
        }

        StyledTextLabel {
            id: titleLabel

            Layout.fillWidth: true

            horizontalAlignment: Qt.AlignLeft
            text: Boolean(root.item) ? root.item.title : ""
        }
    }
}
