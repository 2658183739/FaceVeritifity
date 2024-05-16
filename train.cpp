#include "train.h"


train::train(QObject *parent):QThread(parent)
{
    //run();
}

train::~train()
{

}

void train::run()
{
    qDebug()<<"启动训练线程";
    //读取你的CSV文件路径.
    string fn_csv = "D:\\research\\CV\\Opencv\\at.txt";

    // 2个容器来存放图像数据和对应的标签
    vector<Mat> images;
    vector<int> labels;
    try
    {
        read_csv(fn_csv, images, labels,SEPARATOR); //从csv文件中批量读取训练数据
    }
    catch (cv::Exception& e)
    {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        exit(1);
    }
    // 如果没有读取到足够图片，也退出.
    if (images.size() <= 1) {
        qDebug() << "至少需要两张图片才能运行,请添加更多的图片到您的数据集";
    }

    for (int i = 0; i < images.size(); i++)
    {
        //cout<<images.size();
        if (images[i].size() != Size(92, 112))
        {
            cout << i << endl;
            cout << images[i].size() << endl;
        }

    }
    // 下面的几行代码仅仅是从你的数据集中移除最后一张图片，作为测试图片
    Mat testSample = images[images.size() - 1];
    int testLabel = labels[labels.size() - 1];
    images.pop_back();//删除最后一张照片，此照片作为测试图片
    labels.pop_back();//删除最有一张照片的labels
    //调用其中的成员函数train()来完成分类器的训练
    Ptr<face::LBPHFaceRecognizer> model = face::LBPHFaceRecognizer::create();
    model->train(images, labels);
    model->save("MyFaceLBPHModel.xml");

    // 下面对测试图像进行预测，predictedLabel是预测标签结果
    //注意predict()入口参数必须为单通道灰度图像，如果图像类型不符，需要先进行转换
    //predict()函数返回一个整形变量作为识别标签
    int predictedLabel = model->predict(testSample);//加载分类器

    string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);

    cout << result_message << endl;
    qDebug()<<"训练完成";
    emit finished();
}

/**
 * @brief 使用CSV文件去读图像和标签
 * @param filename
 * @param images
 * @param labels
 * @param separator
 */
void train::read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';')
{
    std::ifstream file(filename.c_str(), ifstream::in);//c_str()函数可用可不用，无需返回一个标准C类型的字符串
    if (!file)
    {
        qDebug() << "No valid input file was given, please check the given filename.";
    }
    string line, path, classlabel;
    while (getline(file, line)) //从文本文件中读取一行字符，未指定限定符默认限定符为“/n”
    {
        stringstream liness(line);//这里采用stringstream主要作用是做字符串的分割
        getline(liness, path, separator);//读入图片文件路径以分好作为限定符
        getline(liness, classlabel);//读入图片标签，默认限定符
        if (!path.empty() && !classlabel.empty()) //如果读取成功，则将图片和对应标签压入对应容器中
        {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
        qDebug() << "path:" << path.data() << endl << "label:"  << classlabel.data() << endl;
    }
}
