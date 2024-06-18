import QtQuick
import QtQuick.Controls
import com.company.PlayerController

Slider {
  id: progressSliders

  value: PlayerController.position / PlayerController.duration
  onMoved: PlayerController.setPosition(value * PlayerController.duration)

  background: Rectangle {
    implicitWidth: 10
    implicitHeight: 10
    color: "transparent"
    border.color: "lightgray"
    border.width: 1
    radius: 10

    Rectangle {
      width: parent.width
      height: parent.height
      color: "lightgray"
      border.color: "transparent"
      radius: 10
    }

    Rectangle {
      width: progressBar.position * parent.width
      height: parent.height
      color: "black"
      border.color: "transparent"
      radius: 10
    }
  }

  handle: Rectangle {
    x: progressBar.leftPadding + progressBar.visualPosition
       * (progressBar.availableWidth - width) - 5
    y: progressBar.topPadding + (progressBar.availableHeight - height) / 2
    width: 25
    height: 25
    radius: width / 2
    color: "black"
    border.color: "white"
    border.width: 2
  }
}
