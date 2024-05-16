#ifndef TRAIN_H
#define TRAIN_H

#include "face.hpp"
#include <QThread>
#include <QMessageBox>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <QDebug>
#include <opencv2\opencv.hpp>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <math.h>
#include <fstream>
#include <sstream>
using namespace std;
using namespace cv;

#define SEPARATOR ';'

class train:public QThread
{
    Q_OBJECT
signals:
    //完成
    void finished();
public:
    explicit train(QObject *parent = nullptr);
    ~train();
    void run();
    //读取txt文件
    void read_csv(const string &, vector<Mat> &, vector<int> &, char);

};

#endif // TRAIN_H
