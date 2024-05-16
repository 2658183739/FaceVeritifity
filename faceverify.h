
#ifndef FACEVERIFY_H
#define FACEVERIFY_H

#include <QWidget>
#include "opencv2/opencv.hpp"

#include <QCamera>              //管理摄像头的大类
#include <QCameraInfo>          //管理摄像头设别表
#include <QCameraViewfinder>    //管理摄像头显示区域
#include <QCameraImageCapture>  //管理图片
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <vector>
#include <QDateTime>
#include <iostream>
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QSqlRecord>

#include "camerathread.h"
#include "train.h"
#include "verityface.h"
using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class FaceVerify; }
QT_END_NAMESPACE

class FaceVerify : public QWidget

{
    Q_OBJECT

public:
    FaceVerify(QWidget *parent = nullptr);
    ~FaceVerify();
    //处理摄像头数据的子线程
    CameraThread * m_cthread;
    //训练界面
    train *m_train;
    //录入界面
    VerityFace * m_verifity;
    //暂时存储录入的工号,姓名
    QString m_TempFaceNum;
    QString m_TempFaceName;



private slots:
    //打开摄像头
    void on_pushButton_Open_Camera_clicked();
    //打卡
    void on_pushButton_Card_clicked();
    //从子线程获取图像
    void Get_image(QImage *image);
    //录入
    void on_pushButton_face_clicked();
    //训练
    void on_pushButton_Train_clicked();
    //训练完成之后
    void Train_Finish();
    //录入之后主线程处理的
    void GetFaceNum(QString num,QString name)
    {
        m_TempFaceNum = num;
        m_TempFaceName = name;

        //连接子线程设置录入界面
        connect(this, &FaceVerify::Veryfity_face, m_cthread, &CameraThread::Set_Verity_face);
        emit Veryfity_face(m_TempFaceNum,m_TempFaceName);

        m_verifity->close();
        delete m_verifity;

    }
    //打卡之后主线程处理的
    void Show_Data(QSqlDatabase *m_db,QString num);


private:
    Ui::FaceVerify *ui;
signals:
    //从录入界面获取的数据传递给子线程
    void Veryfity_face(QString facenum,QString facename);
    //打卡
    void Send_Card();


};

#endif // FACEVERIFY_H
