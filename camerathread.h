
#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H
#include <QMessageBox>
#include <QThread>
#include <QCamera>              //管理摄像头的大类
#include <QCameraInfo>          //管理摄像头设别表
#include <QCameraViewfinder>    //管理摄像头显示区域
#include <QCameraImageCapture>  //管理图片
#include <QTimer>
#include <QDebug>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <QFile>
#include <QDateTime>
#include "opencv2/imgproc/types_c.h"
#include "opencv2/face.hpp"
#include "opencv2/face/facerec.hpp"
#include <QDir>

#include <QFile>
#include <QTextStream>

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QCoreApplication>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QFont>

using namespace cv;
using namespace std;

using namespace cv::face;


class CameraThread : public QThread
{
    Q_OBJECT
public:
    CameraThread()
    {

        //打开序号为0的摄像头
        m_cap.open(0);
        if (!m_cap.isOpened()) {
            qDebug() << "Error: Cannot open camera";
        }


        //判断是否有文件,人脸识别模型，检测和识别用的
        if(!m_cascada.load("D:/research/CV/Opencv/haarcascade_frontalface_alt2.xml"))
        {
            QMessageBox::information(NULL,"失败", "人脸识别模型装载失败");
        }


        //实例化定时器，子线程中数据传输到中线程并显示出来
        m_timer = new QTimer(this);
        //绑定时间信号及获取图像帧的图像
        connect(m_timer,SIGNAL(timeout()),this,SLOT(readFarme()));
        //大概每秒24帧
        //开始定时器
        m_timer->start(42);

        //打卡模块
        // 定义 FisherFaceRecognizer 模型，训练用的模型
        m_model = LBPHFaceRecognizer::create();
        // 加载训练好的模型，自己训练的模型
        m_model->read("MyFaceLBPHModel.xml");

        if (m_model.empty())
        {
            qDebug() << "Error: Failed to load model!";
        }
        else
        {
            qDebug() << "Model loaded successfully!";
        }

        //录入时候的定时器，录入大概几秒，获取二十张灰色图像并保存，等待训练
        //实例化定时器
        m_Very_timer = new QTimer(this);

        //数据库的初始化部分
        //链接数据库
        m_db = QSqlDatabase::addDatabase("QMYSQL");
        m_db.setHostName("localhost");  // 主机名
        m_db.setDatabaseName("face");  // 数据库名
        m_db.setUserName("root");  // 用户名
        m_db.setPassword("31415926");  // 密码

    }
    ~CameraThread()
    {
        //释放摄像头
        m_cap.release();
    }
    void run() override
    {


    }


    //图像数据类型转换
    QImage MatImageToQt(const cv::Mat &src)
    {
        if(src.type() == CV_8UC1)
        {
            QImage qImage(src.cols,src.rows,QImage::Format_Indexed8);
            qImage.setColorCount(256);
            for(int i = 0; i < 256; i ++)
            {
                qImage.setColor(i,qRgb(i,i,i));
            }
            uchar *pSrc = src.data;
            for(int row = 0; row < src.rows; row ++)
            {
                uchar *pDest = qImage.scanLine(row);
                memcmp(pDest,pSrc,src.cols);
                pSrc += src.step;
            }
            return qImage;
        }
        else if(src.type() == CV_8UC3)
        {
            const uchar *pSrc = (const uchar*)src.data;
            QImage qImage(pSrc,src.cols,src.rows,src.step,QImage::Format_RGB888);
            return qImage.rgbSwapped();
        }
        else if(src.type() == CV_8UC4)
        {
            const uchar *pSrc = (const uchar*)src.data;
            QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32);
            return qImage.copy();
        }
        else
        {
            return QImage();
        }
    }

    //人脸检测
    void Check(Mat &image, Mat &gray)
    {
        //直方图均匀化（改善图像的对比度和亮度）
        Mat equalizedImg;
        equalizeHist(gray,equalizedImg);
        int flags = CASCADE_SCALE_IMAGE; //检测多个人

        Size minFeatureSize(30,30);
        float searchScaleFactor = 1.1f; //默认1.1倍
        int minNeighbors = 4;

        m_cascada.detectMultiScale(equalizedImg,m_faces,searchScaleFactor,minNeighbors,flags,minFeatureSize);
        m_current_people = m_faces.size();
        //检测到的个数
        //qDebug() << "检测到人脸的个数：" << m_faces.size() << endl;
        QString str;
        str.setNum(m_faces.size());
        //qDebug() << m_current_people << endl;

//        //画矩形框
        Mat face;
//        for(int i = 0; i < m_faces.size(); i++)
//        {
//            if(m_faces[i].height > 0 && m_faces[i].width >0 )
//            {
//                face = gray(m_faces[i]);
//                m_text_lb = Point(m_faces[i].x,m_faces[i].y);
//                rectangle(image, m_faces[i], Scalar(50, 50, 150), 2, 8, 0); //线太细了会导致在QLabel上面丢失线框


//            }
//            int iP = Predict(image);

//        }



        // 画矩形框和显示姓名
        for(int i = 0; i < m_faces.size(); i++)
        {
            string name; // 从数据库中获取姓名
            if(m_faces[i].height > 0 && m_faces[i].width >0 )
            {
                face = gray(m_faces[i]);
                m_text_lb = Point(m_faces[i].x,m_faces[i].y);
                rectangle(image, m_faces[i], Scalar(50, 50, 150), 2, 8, 0); // 画矩形框

                //灰度图
                Mat tImagGray;
                cvtColor(image, tImagGray, COLOR_BGR2GRAY);
                // 识别人脸
                int id = Predict(tImagGray);


                if (!m_db.open())
                {
                    qDebug() << "Failed to connect to database:" ;
                }

                // 执行查询语句
                QSqlQuery query;
                QString queryString = QString("SELECT name FROM staff_info WHERE num = %1").arg(id);
                if (!query.exec(queryString))
                {
                    qDebug() << "Failed to execute query:";
                    m_db.close();
                }

                // 处理查询结果
                if (query.next())
                {
                    name = query.value(0).toString().toUtf8().constData();
                    m_db.close();
                }
                else
                {
                    m_db.close();
                    name = "Unknown";
                }
            }
                qDebug() << name.data();
                // 在图像上显示姓名
                Point textPosition(m_faces[i].x, m_faces[i].y - 10); // 文本位置在矩形框上方一点
                putText(image, name.data(), textPosition, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1, LINE_AA);


        }

        m_faces.clear();
    }



    // 裁剪出的脸部区域的图像
    cv::Mat cropFace(const cv::Mat& faceImg, const cv::Rect& faceRect) {
        // 不再进行颜色空间转换，直接使用输入的 faceImg
        cv::Mat frame_gray = faceImg;

        // 确保矩形区域在图像范围内
        if (faceRect.x >= 0 && faceRect.y >= 0 &&
            faceRect.x + faceRect.width <= frame_gray.cols &&
            faceRect.y + faceRect.height <= frame_gray.rows)
        {
            // 使用区域选择功能提取矩形区域
            cv::Mat faceROI = frame_gray(faceRect).clone(); // 使用 clone() 来复制图像区域
            return faceROI;
        }
        else
        {
            // 处理矩形区域超出图像范围的情况
            // 这里可以选择合适的处理方式，比如调整矩形区域的大小或者放弃处理该脸部区域
            return cv::Mat();
        }
    }



    // 在文本文件末尾添加数据
    void appendToTextFile(const QString& filename, const QString& data)
    {
        QFile file(filename);
        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream out(&file);
            out << data << "\n";
            file.close();
        }
        else
        {
            qDebug() << "Failed to open file for appending.";
        }
    }

    //预测功能，检测输入的图像中的人脸是否在训练集中
    int Predict(Mat src_image)
    {
        Mat face_test;
        int ispredict = 0;
        //截取的ROI人脸尺寸调整
        if (src_image.rows >= 120)
        {
            //改变图像大小，使用双线性差值
            resize(src_image, face_test, Size(92, 112));

        }
        //判断是否正确检测ROI
        if (!face_test.empty())
        {
            //测试图像应该是灰度图
            ispredict = m_model->predict(face_test);
        }
        //cout << ispredict << endl;
        return ispredict;
    }


signals:
    //向主线程传输图像
    void Set_image(QImage *image);
    //打卡之后设置ui部分和数据库部分
    void Send_Card_Data(QSqlDatabase *m_db,QString num);

public slots:
    //摄像头读取函数
    void readFarme()
    {
        //读取一帧图像
        m_cap.read(m_src_image) ;
        //处理一下数据，人脸检测
        //生成灰度图
        Mat dst_gray;
        cvtColor(m_src_image, dst_gray, COLOR_BGR2GRAY);
        Check(m_src_image, dst_gray);

        //转换图像数据类型
        QImage imag = MatImageToQt(m_src_image);

        //发送图像
        Set_image(&imag);
    }

    //执行二十次检测人脸并保存下来的功能
    void Verity()
    {
        //判断目前摄像头中的脸有几个
        if (!m_facenum.isEmpty())
        {
            //如果目前只有一个人
            if(m_current_people == 1)
            {
                qDebug() << m_executionCount;
                //裁剪出人脸区域
                Mat faceROI = cropFace(m_src_image, m_faces[0]);
                if (!faceROI.empty())
                {
                    // 调整裁剪后的脸部图像大小
                    cv::Mat resizedFace;
                    cv::resize(faceROI, resizedFace, cv::Size(92, 112));

                    // 将调整大小后的脸部图像存储在 m_src_image 中
                    m_src_image = resizedFace.clone();
                } else
                {
                    qDebug() << "裁剪后的脸部图像为空！ ";
                }

                //存储的地址
                QString dir_str = "D:\\research\\CV\\Opencv\\facedata\\" + m_facenum + "\\" + QString::number(m_executionCount) + ".jpg";
                //用来判断这个地址的文件夹是否存在
                QString is_dir = "D:\\research\\CV\\Opencv\\facedata\\" + m_facenum;
                qDebug() << dir_str;
                QDir dir(is_dir);
                if (!dir.exists())
                {
                    if (!dir.mkpath("."))
                    {
                        qDebug() << "default ";
                    }
                }

                //扣的脸部的图像如果不为空
                if (!faceROI.empty())
                {
                    string filename = dir_str.toStdString();
                    // 将彩色图像转换为灰度图像
                    cv::Mat frame_gray;
                    cv::cvtColor(faceROI, frame_gray, cv::COLOR_BGR2GRAY);
                    //存储图像
                    imwrite(filename, frame_gray);
                    //在存储训练集需要的图片的地址的txt里也更新地址
                    QString csvsave = "D:/research/CV/Opencv/facedata/" + m_facenum + "/" + QString::number(m_executionCount) + ".jpg" + ";" + m_facenum ;
                    //存放要训练的模型的图片的地址的txt
                    QString csvfilename = "D:\\research\\CV\\Opencv\\at.txt";
                    //添加数据
                    appendToTextFile(csvfilename, csvsave);
                    m_executionCount++; // 每次执行计数器加一

                } else
                {
                    qDebug() << "脸部图像为空，无法写入文件！ ";
                }

                //存储20张之后
                if (m_executionCount >= 20)
                {
                    m_executionCount = 0;
                    m_Very_timer->stop();
                }

            }

        }
        else
        {
            QMessageBox::about(NULL, "提示", "请输入工号！");
            m_executionCount = 0;
            m_Very_timer->stop();
            //delete m_Very_timer;
        }
    }

    //录入脸
    void Set_Verity_face(QString facenum,QString facename)
    {
        m_facenum = facenum;
        m_facename = facename;
        qDebug()<< QSqlDatabase::drivers();
        //判断数据库是否开着
        if (!m_db.open())
        {
            qDebug() << "Failed to connect to database:" ;
        } else
        {
            qDebug() << "Connected to database!";
        }

        //查找全部，看数量以便添加id
        QSqlQuery countQuery("SELECT COUNT(*) FROM staff_info");

        if (countQuery.exec() && countQuery.next())
        {
            int rowCount = countQuery.value(0).toInt(); // 获取数据条数
            int newId = rowCount + 1; // 新的 ID 就是数据条数加一

            QSqlQuery query;
            query.prepare("INSERT INTO staff_info (num, id, name) VALUES (:facenum, :faceid, :facename)");
            query.bindValue(":facenum", m_facenum);
            query.bindValue(":faceid", newId); // 使用新的 ID
            query.bindValue(":facename", m_facename);

            if (query.exec())
            {
                qDebug() << "Data inserted into database successfully!";
            }
            else
            {
                qDebug() << "Failed to insert data into database:" ;
            }
        }
        else
        {
            qDebug() << "Failed to retrieve row count from database:" ;
        }


        //关闭数据库
        m_db.close();

        qDebug() << "开始录入\n";

        //绑定时间信号及获取图像帧的图像
        connect(m_Very_timer, SIGNAL(timeout()), this, SLOT(Verity()));
        //开始定时器
        m_Very_timer->start(200);
    }

    //设置打卡部分
    void Set_Card()
    {
        Mat gray;
        cvtColor(m_src_image, gray, CV_BGR2GRAY); // 将输入图像转换为灰度图像
        vector<Rect> faces; // 存放检测到的人脸矩形的向量容器

        // 使用级联分类器检测人脸
        m_cascada.detectMultiScale(gray, faces, 1.1, 4, 0, Size(30, 30), Size(500, 500));

        // 遍历检测到的每张人脸
        for (size_t i = 0; i < faces.size(); i++)
        {
            Rect faceRect = faces[i]; // 获取当前人脸的矩形框
            // 从灰度图像中提取当前人脸区域
            Mat faceROI = gray(faceRect);

            // 检查人脸区域是否为空
            if (!faceROI.empty())
            {
                // 调用 Predict 函数对人脸进行预测
                int temp = Predict(faceROI);
                qDebug() << "预测结果:" << temp;

                // 发送打卡数据，然后让主线程在数据库中查找
                Send_Card_Data(&m_db,QString::number(temp));

            }
        }
        faces.clear();


    }





private:
    //声明opencv的视频类
    cv::VideoCapture m_cap;
    //更新显示的定时器
    QTimer *m_timer;
    //录入的定时器
    QTimer *m_Very_timer;
    //声明Mat类图像变量，存储当前摄像头前的图像
    cv::Mat m_src_image;
    //检测的分类器
    CascadeClassifier m_cascada;

    //矩形框的点
    Point m_text_lb;
    //人脸个数
    vector<Rect> m_faces;
    // 声明一个录入计数器变量
    int m_executionCount = 0;
    //工号和姓名
    QString m_facenum;
    QString m_facename;
    //识别的模型
    Ptr<LBPHFaceRecognizer> m_model;
    //当前镜头前识别出的人数
    int m_current_people = 0;
    //数据库
    QSqlDatabase m_db;
};

#endif // CAMERATHREAD_H
