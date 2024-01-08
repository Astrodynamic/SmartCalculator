import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "model"

ApplicationWindow {
  id: window

  width: 720
  height: 360
  minimumWidth: width
  maximumWidth: width
  minimumHeight: height
  maximumHeight: height

  title: "SmartCalulator 1.0"
  visible: true

  header: Label {
    id: _display

    property bool incorrect: false
    property alias bColor: _background.border.color

    width: parent.width
    padding: 20

    elide: Text.ElideLeft
    font {
      weight: Font.Medium
      pointSize: 14
    }
    horizontalAlignment: Text.AlignRight

    background: Rectangle {
      id: _background

      anchors {
        fill: parent
        margins: parent.padding / 2
      }

      color: "transparent"
      border {
        width: 1
        color: "dimgrey"
      }
      radius: 4
    }

    states: [
      State {
        name: "incorrect"
        when: _display.incorrect

        PropertyChanges {
          target: _display
          bColor: "red"
        }
      }
    ]
  }

  GridLayout {
    anchors {
      fill: parent
      margins: 10
    }

    columns: 7

    Repeater {
      model: ButtonModel {
        id: _model
      }
      delegate: Button {
        Layout.fillWidth: true
        Layout.fillHeight: true

        text: model.name
        font.pointSize: 12

        onClicked: {
          model.action(model.name)
        }
      }
    }
  }

  Dialog {
    id: _variable

    title: "Input x:"

    anchors.centerIn: parent
    modal: true

    TextField {
      id: _input

      width: parent.width
      horizontalAlignment: Text.AlignRight
      validator: DoubleValidator {}

      onTextChanged: {
        if (text === "") {
          text = "0"
        }
      }

      Component.onCompleted: textChanged()
    }

    standardButtons: Dialog.Ok | Dialog.Cancel

    onAccepted: {
      _model.clean(Calculation.calc(parseFloat(_input.text)))
    }
  }
}
