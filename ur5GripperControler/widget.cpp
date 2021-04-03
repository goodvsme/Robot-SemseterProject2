#include "widget.h"
#include "./ui_widget.h"
#include "iostream"
#include "ur5andgripper.h"
#include <vector>

#include<sstream>

#include <mysql.h>




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "127.0.0.1", "root", "Emil2000", "ur5Database", 3306, NULL, 0);

    if (conn)
    {

        ur5Bots.clear();

        string navn;
        string ip;
        string port;

        string query = "select UR5.navn,UR5.IP,Gripper.COM_port from UR5, Orders, Gripper where UR5.robot_id=Orders.robot_id and Orders.gripper_id=Gripper.gripper_id order by UR5.robot_id";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);

            while ((row = mysql_fetch_row(res))){
                navn = row[0];
                ip = row[1];
                port = row[2];


                //inputting the robots in list
                ur5AndGripper i(navn, ip, port, "Rubber");
                ur5Bots.push_back(i);
                ui->comboBox->addItem(QString::fromStdString(i.rName));
                //setting up the gui data from databace
                ui->urIP->setText(QString::fromStdString(ur5Bots[ui->comboBox->currentIndex()].tcpUR5IP));



            }

        }
        else
            cout << "Query failed: " << mysql_error(conn) << endl;










    }else{
        ur5Bots.clear();
        //inputting the robots in list
        ur5AndGripper Defult("Defult", "0.0.0.0", "/dev/ttyUSB0", "Defult");
        ur5Bots.push_back(Defult);


        //setting up the gui from Deafult
        ui->comboBox->addItem(QString::fromStdString(Defult.rName));
        ui->comboBox_F->addItem(QString::fromStdString(Defult.fName));

        ui->urIP->setText(QString::fromStdString(ur5Bots[ui->comboBox->currentIndex()].tcpUR5IP));
        ui->gUSB->setText(QString::fromStdString(ur5Bots[ui->comboBox->currentIndex()].usbPort));
    }

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    int h = size().height();
    int w = size().width();

    int ang = ur5Bots[ui->comboBox->currentIndex()].ang;

    //making the two pen's
    QPen blue;
    blue.setColor(QColor(26, 8, 95));
    blue.setWidth(52);
    blue.setCapStyle(Qt::RoundCap);

    QPen black;
    black.setColor(QColor(46, 52, 54));
    black.setWidth(52);
    black.setCapStyle(Qt::RoundCap);

    QPen red;
    red.setColor(QColor(204, 0, 0));
    red.setWidth(2);
    red.setCapStyle(Qt::FlatCap);

    QPen smallB;
    smallB.setColor(QColor(46, 52, 54));
    smallB.setWidth(2);
    smallB.setCapStyle(Qt::RoundCap);
    QBrush smallBIn;
    smallBIn.setColor(QColor(46, 52, 54));
    smallBIn.setStyle(Qt::SolidPattern);


    QPen smallBlue;
    smallBlue.setColor(QColor(26, 8, 95));
    smallBlue.setWidth(2);
    smallBlue.setCapStyle(Qt::RoundCap);
    QBrush smallBlueIn;
    smallBlueIn.setColor(QColor(26, 8, 95));
    smallBlueIn.setStyle(Qt::SolidPattern);


    //the right side of the gribber's points
    QPoint pRs((w/3)-27.5, h/3);
    QPoint pRs2(pRs.x()-62.5, pRs.y()-89.26);

    QPoint pRF0(pRs2.x()+(137.5*cos(M_PI*(0.5)+ang*(M_PI/180.0))), pRs2.y()+(137.5*sin(M_PI*(0.5)+ang*(M_PI/180.0))));
    QPoint pRF1(pRs.x()+(137.5*cos(M_PI*(0.5)+ang*(M_PI/180.0))), pRs.y()+(137.5*sin(M_PI*(0.5)+ang*(M_PI/180.0))));

    QPoint pRF2(pRF1.x()+12.5,pRF1.y());
    QPoint pRF3(pRF2.x(),pRF2.y()+137.5);
    QPoint pRF4(pRF3.x()-14.6625,pRF3.y()-11.125);
    QPoint pRF5(pRF1.x()-21.545,pRF1.y()+26.95);
    QPoint pRF6(pRF5.x(),pRF5.y()-26.95);

    QPoint pRF7(pRF2.x(),pRF5.y());
    QPoint pRF8(pRF2.x()+12.5,pRF3.y()-1);

    QRect rectR(pRF7,pRF8);


    QPolygon finger;
    finger << pRF1;
    finger << pRF2;
    finger << pRF3;
    finger << pRF4;
    finger << pRF5;
    finger << pRF6;


    QPainterPath path;
    path.addPolygon(finger);


    //the right side of the gribber's lines
    painter.setPen(black);
    painter.drawLine(pRF0, pRF1);


    painter.setPen(smallBlue);
    painter.drawRect(rectR);
    painter.fillRect(rectR,smallBlueIn);


    painter.setPen(smallB);
    painter.drawPolygon(finger);
    painter.fillPath(path, smallBIn);

    painter.setPen(blue);
    painter.drawLine(pRs, pRF1);
    painter.drawLine(pRs2, pRF0);



    //the left side of the gribber's points
    QPoint pLs((w/3)+27.5, h/3);
    QPoint pLs2(pLs.x()+62.5, pLs.y()-89.26);

    QPoint pLF0(pLs2.x()-(137.5*cos(M_PI*(0.5)+ang*(M_PI/180.0))), pLs2.y()+(137.5*sin(M_PI*(0.5)+ang*(M_PI/180.0))));
    QPoint pLF1(pLs.x()-(137.5*cos(M_PI*(0.5)+ang*(M_PI/180.0))), pLs.y()+(137.5*sin(M_PI*(0.5)+ang*(M_PI/180.0))));

    QPoint pLF2(pLF1.x()-12.5,pLF1.y());
    QPoint pLF3(pLF2.x(),pLF2.y()+137.5);
    QPoint pLF4(pLF3.x()+14.6625,pLF3.y()-11.125);
    QPoint pLF5(pLF1.x()+21.545,pLF1.y()+26.95);
    QPoint pLF6(pLF5.x(),pLF5.y()-26.95);

    QPoint pLF7(pLF2.x(),pLF5.y());
    QPoint pLF8(pLF2.x()-12.5,pLF3.y()-1);

    QRect rectL(pLF7,pLF8);

    QPolygon fingerL;
    fingerL << pLF1;
    fingerL << pLF2;
    fingerL << pLF3;
    fingerL << pLF4;
    fingerL << pLF5;
    fingerL << pLF6;


    QPainterPath pathL;
    pathL.addPolygon(fingerL);


    //the left side of the gribber's lines
    painter.setPen(black);
    painter.drawLine(pLF0, pLF1);


    painter.setPen(smallBlue);
    painter.drawRect(rectL);
    painter.fillRect(rectL,smallBlueIn);


    painter.setPen(smallB);
    painter.drawPolygon(fingerL);
    painter.fillPath(pathL, smallBIn);

    painter.setPen(blue);
    painter.drawLine(pLs, pLF1);
    painter.drawLine(pLs2, pLF0);


    //measuring line
    painter.setPen(red);
    QPoint pM1(pRF8.x()+3,pRF8.y());
    QPoint pM2=pLF8;

    QPoint pM3(pM1.x()-30,pM1.y());
    QPoint pM4(pM2.x()+30,pM2.y()+30);


    painter.drawLine(pM1, pM2);


    QRect rectText(pM3,pM4);

    int length = ((pM2.x()-pM1.x())*4.0)/10.0;

   string s = std::to_string(length) + " mm";
   char const *pchar = s.c_str();




    painter.drawText(rectText, Qt::AlignCenter, tr(pchar));




    //update Data from mudbus into x
    ur5Bots[ui->comboBox->currentIndex()].modbusUpdateCoords();

    ui->doubleSpinBox_X->setValue(ur5Bots[ui->comboBox->currentIndex()].TCP_coords[0]);
    ui->doubleSpinBox_Y->setValue(ur5Bots[ui->comboBox->currentIndex()].TCP_coords[1]);
    ui->doubleSpinBox_Z->setValue(ur5Bots[ui->comboBox->currentIndex()].TCP_coords[2]);
    ui->doubleSpinBox_RX->setValue(ur5Bots[ui->comboBox->currentIndex()].TCP_coords[3]);
    ui->doubleSpinBox_RY->setValue(ur5Bots[ui->comboBox->currentIndex()].TCP_coords[4]);
    ui->doubleSpinBox_RZ->setValue(ur5Bots[ui->comboBox->currentIndex()].TCP_coords[5]);

    ui->urIP->setText(QString::fromStdString(ur5Bots[ui->comboBox->currentIndex()].tcpUR5IP));
    ui->gUSB->setText(QString::fromStdString(ur5Bots[ui->comboBox->currentIndex()].usbPort));



    update();
}



void Widget::on_spinBox_ang_valueChanged(int arg1)
{
    ur5Bots[ui->comboBox->currentIndex()].ang = ui->spinBox_ang->value();
    //ui->spinBox_Fo->setValue(ui->comboBox->currentIndex());




}

void Widget::on_pushButton_clicked()
{
    //std::cout << ui->lineEdit_4->text().toStdString();
}



void Widget::on_ipCon_clicked()
{

}
