
#include "faceverify.h"

#include <QApplication>
#include <opencv2/opencv.hpp>
using namespace cv;
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString qssPath = QString("D:/research/CV/Opencv/qss.qss").arg(a.applicationDirPath());
    QFile file(qssPath);
    if(file.open(QFile::ReadOnly))
    {
        a.setStyleSheet(file.readAll());//在main()中
        //this->setStyleSheet(file.readAll());//在MainWidget中

    }
    file.close();


    FaceVerify w;
    w.show();
    return a.exec();
}
