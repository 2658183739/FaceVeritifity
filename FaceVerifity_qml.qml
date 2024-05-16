import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.0


Window {
    id:faceverifity
    width: 320;
    height: 240
    visible: false
    color: "lightblue"
    Material.theme: Material.Light
    Material.accent: Material.Purple

    signal sendfacedata(string num,string name)

    Column {
        id: column
        width: parent.width
        height: parent.height

        Row {
            id: row
            width: parent.width * 0.3
            height: parent.height * 0.3

            Label {
                id: label
                width: parent.width * 2
                height: parent.height * 4
                Material.theme: Material.Light
                Material.accent: Material.Purple
                font.pixelSize: 30
                text: qsTr("输入工号：")
            }

            TextEdit {
                Material.theme: Material.Light
                Material.accent: Material.Purple
                id: textEdit_num
                width: parent.width * 2
                height: parent.height * 4
                text: qsTr("输入工号")
                font.pixelSize: 30
            }
        }

        Row {
            id: row1
            width: parent.width * 0.3
            height: parent.height * 0.3



            Label {
                id: label1
                width: parent.width * 2
                height: parent.height * 4
                //anchors.left: parent.left //基于父控件靠左对齐
                text: qsTr("输入姓名：")
                font.pixelSize: 30
            }

            TextEdit {
                Material.theme: Material.Light
                Material.accent: Material.Purple
                id: textEdit_name
                width: parent.width * 2
                height: parent.height * 4
                text: qsTr("输入姓名")
                font.pixelSize: 30
            }
        }

        Row {
            id: row2
            width: parent.width
            height: parent.height * 0.3

            Button {

                id: button
                objectName: "button"
                width: parent.width
                height: parent.height
                anchors.fill: parent
                text: qsTr("开始录入")
                Material.theme: Material.Light
                Material.accent: Material.Purple
                onClicked:
                {
                    //向主界面发送数据
                    faceverifity.sendfacedata(textEdit_num.text,textEdit_name.text)
                    console.log("已发送")
                }

            }
        }
    }



}
