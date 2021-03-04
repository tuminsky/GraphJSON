import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import util.controller 1.0

ApplicationWindow {
  visible: true
  width: 700
  height: 900

  Controller {
    id: controller
    onFailedOpen: messageDialogFile.open()
    onJsonFailed: messageDialogFile.open()
  }

  MessageDialog {
    id: messageDialogFile
    title: "Error"
    text: "Failed open file"
  }

  MessageDialog {
    id: messageDialogJson
    title: "Error"
    text: "Incorrect format json"
  }

  menuBar: MenuBar {
    Menu {
      title: "File"

      Action {
        id: aOpen
        text: "Open"
        onTriggered: fileDialog.open()
      }
    }
  }

  FileDialog {
    id: fileDialog

    nameFilters: "*.json"

    onAccepted: {
      let file_path = fileDialog.fileUrl.toString().substr(8);
      controller.json_to_graph(file_path)
    }
  }

  ScrollView {
    anchors.fill: parent

    ScrollBar.horizontal.policy: Qt.ScrollBarAlwaysOn
    ScrollBar.vertical.policy: Qt.ScrollBarAlwaysOn

    Image {
      id: graphView
      anchors.fill: parent

      source: "data:image/svg+xml;utf8," + controller.svg

      MouseArea {
        anchors.fill: parent

        onWheel: graphView.scale *= (wheel.angleDelta.y > 0) ? 1.25 : 0.8;
      }
    }
  }
}
