
#include "faceverify.h"

#include <QQmlApplicationEngine>
#include <QDebug>
#include <QCamera>              //管理摄像头的大类
#include <QCameraInfo>          //管理摄像头的设备表
#include <QCameraViewfinder>    //管理摄像头显示区域
#include <QCameraImageCapture>  //管理图片
#include <QDateTime>            //管理时间
#include <QString>              //管理字符串
#include "verityface.h"

#pragma execution_character_set("utf-8")

FaceVerify::FaceVerify()
{



}

FaceVerify::~FaceVerify()
{
    delete m_cthread;
}
//发送给qml显示
void FaceVerify::Get_image(QImage *image)
{
    emit SetImage(*image);
}

//打开摄像头
void FaceVerify::on_pushButton_Open_Camera_clicked(int num)
{
    //判断是打开还是关闭摄像头
     if(num ==  1)
     {
         m_cthread = new CameraThread();
         connect(m_cthread, &CameraThread::Set_image, this, &FaceVerify::Get_image);
     }
     else
     {

         //关闭摄像头之后把图像换成原始背景图像
         QImage imag;
         imag.load("D://research//CV//FaceVeritifity_qml//background.jpeg");
         //发送图像
         m_cthread->Set_image(&imag);


         disconnect(m_cthread, &CameraThread::Set_image, this, &FaceVerify::Get_image);
         delete m_cthread;
         m_cthread = nullptr;
     }
}

//打卡
void FaceVerify::on_pushButton_Card_clicked()
{
    // 先断开之前的连接
    disconnect(this, &FaceVerify::Send_Card, m_cthread, &CameraThread::Set_Card);
    disconnect(m_cthread, &CameraThread::Send_Card_Data, this, &FaceVerify::Show_Data);

    // 连接信号和槽
    connect(this, &FaceVerify::Send_Card, m_cthread, &CameraThread::Set_Card);
    connect(m_cthread, &CameraThread::Send_Card_Data, this, &FaceVerify::Show_Data);

    // 发送信号
    emit Send_Card();

}
//打卡数据显示
void FaceVerify::Show_Data(QSqlDatabase *m_db,QString num)
{
    if (!m_db->open())
    {
        qDebug() << "Failed to connect to database:";
    }
    else
    {
        qDebug() << "Connected to database!";

        // 执行检查并插入数据
        QSqlQuery query;
        query.prepare("SELECT * FROM record_info WHERE num = :facenum AND DATE(mtime) = CURDATE()");
        query.bindValue(":facenum", num);

        if (query.exec())
        {
            if (query.next())
            {
                // 如果有记录，表示今天已经签到
                QMessageBox::information(NULL, tr("提示 "), tr("今天已签到 "));

                // 读取数据库中的数据并显示在textEdit_data中
                QString data;
                QSqlRecord record = query.record();
                int numField = record.indexOf("num"); // 获取字段索引
                int timeField = record.indexOf("mtime");

                // 遍历查询结果
                do
                {
                    QString num = query.value(numField).toString(); // 获取编号
                    QString time = query.value(timeField).toDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取时间
                    data += "编号: " + num + ", 时间: " + time + "\n";
                } while (query.next());

                // 将数据显示在textEdit_data中
                //ui->textEdit_data->setText(data);
                emit setCardData(data);

            }
            else
            {
                QDateTime currentDateTime = QDateTime::currentDateTime();
                QString currentTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

                qDebug() << "Current time:" << currentTimeString;
                // 如果没有记录，表示今天还未签到，执行插入操作
                query.prepare("INSERT INTO record_info (num, id, mtime) VALUES (:facenum, :faceid, :facemtime)");
                query.bindValue(":facenum", num);
                query.bindValue(":faceid", num); // 使用相同的 num 作为 id
                query.bindValue(":facemtime", currentTimeString);


                if (query.exec())
                {
                    QMessageBox::information(NULL, tr("提示 "), tr("签到成功 "));
                }
                else
                {
                    QMessageBox::critical(NULL, tr("错误 "), tr("签到失败： ") ); // 显示错误信息
                }
            }

        }
        else
        {
            QMessageBox::critical(NULL, tr("错误"), tr("查询数据失败： "));
        }

        // 关闭数据库连接
        m_db->close();
    }


}

void FaceVerify::sendfacedata(const QString &num, const QString &name)
{
    qDebug()<<"main 接收";

    m_TempFaceNum = num;
    m_TempFaceName = name;

    //连接子线程设置录入界面
    connect(this, &FaceVerify::Veryfity_face, m_cthread, &CameraThread::Set_Verity_face);
    emit Veryfity_face(m_TempFaceNum,m_TempFaceName);



}

//训练模型
void FaceVerify::on_pushButton_Train_clicked()
{
    qDebug() << "训练中";
    m_train = new train();
    connect(m_train, &train::finished, this, &FaceVerify::Train_Finish);
    m_train->run();

}
//模型训练完
void FaceVerify::Train_Finish()
{
    delete m_train;
    QMessageBox::information(NULL,"训练", "训练完成");
}
