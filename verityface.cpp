#include "verityface.h"
#include "ui_verityface.h"
#include "QDebug"
VerityFace::VerityFace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VerityFace)
{
    ui->setupUi(this);
}

VerityFace::~VerityFace()
{
    delete ui;
}

void VerityFace::on_pushButton_Sure_clicked()
{
    emit Send_Face(ui->lineEdit_Num->text(),ui->lineEdit_Name->text());
}

