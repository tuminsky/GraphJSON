import QtQuick 2.11
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import util.controller 1.0

ApplicationWindow {
  id: appWin
  visible: true
  width: 900
  height: 800

  Controller {
    id: controller

    onFailedOpen: {
      msgDialog.text = "Failed open file";
      msgDialog.open()
    }

    onJsonFailed: {
      msgDialog.text = "Incorrect format json";
      msgDialog.open()
    }

    onGraphvizFailed: {
      msgDialog.text = "Graphviz not found"
      msgDialog.open();
    }

    onSvgChanged: graphView.source = "data:image/svg+xml;utf8," + controller.svg
  }

  MessageDialog {
    id: msgDialog
    title: "Error"
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

    onAccepted: controller.json_to_graph(fileDialog.fileUrl.toString());
  }

  ScrollView {
    id: scrollView
    anchors.fill: parent

    ScrollBar.horizontal.policy: Qt.ScrollBarAlwaysOn
    ScrollBar.vertical.policy: Qt.ScrollBarAlwaysOn

    ScrollBar.horizontal.interactive: true
    ScrollBar.vertical.interactive: true

    Image {
      id: graphView
      anchors.fill: parent
      focus: true

      MouseArea {
        anchors.fill: parent

        onWheel: graphView.scale *= (wheel.angleDelta.y > 0) ? 1.25 : 0.75;
      }
    }
  }
}
