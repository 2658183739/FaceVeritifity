#ifndef VERITYFACE_H
#define VERITYFACE_H

#include <QWidget>


class VerityFace : public QObject
{
    Q_OBJECT

public:
    VerityFace();
    ~VerityFace();

private slots:
    //确认
    void on_pushButton_Sure_clicked();
signals:
    //发送录入员工信息
    void Send_Face(QString face_num,QString face_name);


};

#endif // VERITYFACE_H
