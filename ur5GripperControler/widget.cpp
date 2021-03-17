#include "widget.h"
#include "./ui_widget.h"
#include "iostream"
#include "ur5andgripper.h"
#include <vector>




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ur5Bots.clear();
    ur5AndGripper i;
    ur5Bots.push_back(i);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    int h = size().height();
    int w = size().width();


    //making the two pen's
    QPen blue;
    blue.setColor(QColor(26, 8, 95));
    blue.setWidth(52);
    blue.setCapStyle(Qt::RoundCap);

    QPen black;
    black.setColor(QColor(131, 78, 160));
    black.setWidth(52);
    black.setCapStyle(Qt::RoundCap);



    //the right side of the gribber's points
    QPoint pRs((w/3)-27.5, h/3);
    QPoint pRs2(pRs.x()-62.5, pRs.y()-89.26);

    QPoint pR1(pRs.x()+(137.5*cos(M_PI*(0.5)+ang*(M_PI/180.0))), pRs.y()+(137.5*sin(M_PI*(0.5)+ang*(M_PI/180.0))));
    QPoint pR2(pRs2.x()+(137.5*cos(M_PI*(0.5)+ang*(M_PI/180.0))), pRs2.y()+(137.5*sin(M_PI*(0.5)+ang*(M_PI/180.0))));

    //the right side of the gribber's lines
    painter.setPen(black);
    painter.drawLine(pR1, pR2);
    painter.setPen(blue);
    painter.drawLine(pRs, pR1);
    painter.drawLine(pRs2, pR2);


    //the left side of the gribber's points
    QPoint pLs((w/3)+27.5, h/3);
    QPoint pLs2(pLs.x()+62.5, pLs.y()-89.26);

    QPoint pL1(pLs.x()-(137.5*cos(M_PI*(0.5)+ang*(M_PI/180.0))), pLs.y()+(137.5*sin(M_PI*(0.5)+ang*(M_PI/180.0))));
    QPoint pL2(pLs2.x()-(137.5*cos(M_PI*(0.5)+ang*(M_PI/180.0))), pLs2.y()+(137.5*sin(M_PI*(0.5)+ang*(M_PI/180.0))));

    //the left side of the gribber's lines
    painter.setPen(black);
    painter.drawLine(pL1, pL2);
    painter.setPen(blue);
    painter.drawLine(pLs, pL1);
    painter.drawLine(pLs2, pL2);



    //update Data from mudbus into x
    ui->doubleSpinBox_X->setValue(ur5Bots[0].modbusGetCoords()[0]);



    update();
}



void Widget::on_spinBox_ang_valueChanged(int arg1)
{
    ang = ui->spinBox_ang->value();




}

void Widget::on_pushButton_clicked()
{
    //std::cout << ui->lineEdit_4->text().toStdString();
}
