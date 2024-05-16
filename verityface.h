#ifndef VERITYFACE_H
#define VERITYFACE_H

#include <QWidget>

namespace Ui {
class VerityFace;
}

class VerityFace : public QWidget
{
    Q_OBJECT

public:
    explicit VerityFace(QWidget *parent = nullptr);
    ~VerityFace();

private slots:
    //确认
    void on_pushButton_Sure_clicked();
signals:
    //发送录入员工信息
    void Send_Face(QString face_num,QString face_name);
private:
    Ui::VerityFace *ui;
};

#endif // VERITYFACE_H
