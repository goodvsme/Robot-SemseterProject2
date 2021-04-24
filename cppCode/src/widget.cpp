#include "widget.h"
#include "./ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(dataUpdate()));
    timer->start(50);
    setup();

}

void Widget::setup(){


    robots = d.getRobots();
    grippers = d.getGrippers();

    for(unsigned long i = 0; i<robots.size();i++){
        robots[i].modbusConnect();
        robots[i].modbusUpdateCoords();
    }
}


void Widget::paintEvent(QPaintEvent *event)
{

    //dataUpdate();
    guiUpdate();

    animation();

    update();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dataUpdate()
{
    robots[0].modbusConnect();
    robots[0].modbusUpdateCoords();
    robots[0].modbusDisconnect();

    grippers[0].readSerial();
}

void Widget::guiUpdate()
{

    ui->doubleSpinBox_X->setValue(robots[0].TCP_Coords[0]);
    ui->doubleSpinBox_Y->setValue(robots[0].TCP_Coords[1]);
    ui->doubleSpinBox_Z->setValue(robots[0].TCP_Coords[2]);
    ui->doubleSpinBox_XX->setValue(robots[0].TCP_Coords[3]);
    ui->doubleSpinBox_YY->setValue(robots[0].TCP_Coords[4]);
    ui->doubleSpinBox_ZZ->setValue(robots[0].TCP_Coords[5]);



    //testgg.dataIn[0]


    //ui->label->setText(QString::fromStdString(robots[0].robotName));
    ui->label->setText(QString::fromStdString(grippers[0].portCOM));

}


void Widget::animation()
{
    QPainter painter(this);

    int h = size().height();
    int w = size().width();

    int ang = 0;//ur5Bots[ui->comboBox->currentIndex()].ang;

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

    std::string s = std::to_string(length) + " mm";
    char const *pchar = s.c_str();




    painter.drawText(rectText, Qt::AlignCenter, tr(pchar));
}


void Widget::on_clockwise_clicked()
{
    grippers[0].sendmsg('1');
}

void Widget::on_counter_clicked()
{
    grippers[0].sendmsg('2');
}

void Widget::on_stop_clicked()
{
    grippers[0].sendmsg('0');
}

void Widget::on_junk_clicked()
{
    grippers[0].sendmsg('a');
}
