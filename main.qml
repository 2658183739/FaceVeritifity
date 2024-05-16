import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.0


Window {
    id: window
    width: 1500
    height: 800
    visible: true
    title: qsTr("Hello World")

    Material.theme: Material.Grey
    Material.accent: Material.color("red")


    FaceVerifity_qml{
         id:facevery
         objectName: "facevery"

    }



      //设置向主界面发送数据的槽函数
      Connections {
                  target: facevery
                  function onSendfacedata(num,name){

                      console.log("qml接收")
                      console.log(num)
                      console.log(name)

                      camera.sendfacedata(num, name);
                      facevery.destroy()

                  }
              }

    //设置打开数据的槽函数
    Connections {
                target: camera
                function onSetCardData(res){
                    label_showdb.text = res
                    console.log("success")
                }
            }



    Column {
        id: column
        width: parent.width
        height: parent.height




        Row {
            id: row
            width: parent.width
            height: parent.height * 0.9


            Label {
                width: parent.width * 0.3
                id: label_showdb
                objectName: "label_showdb"
                text: qsTr("HelloWorld")
                Material.theme: Material.Light
                Material.accent: Material.Purple

            }



            Image{
                    id:img
                    width: parent.width * 0.7 - 10
                    height: parent.height - 10
                    source:"file:///D://research//CV//FaceVeritifity_qml//background.jpeg"
                    Material.theme: Material.Light
                    Material.accent: Material.Purple
                }
                Connections{
                    target: CodeImage
                    onCallQmlRefeshImg:{
                        img.source = "image://CodeImg/"+ Math.random()
                    }
                }


            }





        Row {
            id: row1
            width: parent.width
            height: parent.height * 0.1
            spacing: parent.width / 5


            Button {
                Material.theme: Material.Light
                Material.accent: Material.Purple

                id: button_verifityface
                objectName: "button_verifityface"
                text: qsTr("录入人脸")

                onClicked:
                {
                    //以这个文件作为主窗口在创建一个qml窗口，插件式
                    facevery.show()
                }


            }


            Button {
                id: button_openceramera
                objectName: "button_openceramera"
                text: qsTr("打开摄像头")
                Material.theme: Material.Light
                Material.accent: Material.Purple

                onClicked:
                {
                    if(text == "打开摄像头")
                    {
                        camera.on_pushButton_Open_Camera_clicked(1)
                        text = "关闭摄像头"
                    }
                    else
                    {
                        camera.on_pushButton_Open_Camera_clicked(0)
                        text = "打开摄像头"
                    }

                }



            }

            Button {
                id: button_train
                objectName: "button_train"
                text: qsTr("训练")
                Material.theme: Material.Light
                Material.accent: Material.Purple


            }

            Button {
                id: button_card
                objectName: "button_card"
                text: qsTr("打卡")
                Material.theme: Material.Light
                Material.accent: Material.Purple
                 onClicked:
                 {
                     camera.on_pushButton_Card_clicked()
                 }
            }
        }



    }









}
