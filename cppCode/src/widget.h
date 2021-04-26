#ifndef WIDGET_H
#define WIDGET_H

//Files
#include "robotur5.h"
#include "gripper.h"
#include "database.h"

//UI
#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <QTimer>

//ALL
#include <memory>
#include <vector>
#include <string>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT


public:
    Widget(QWidget *parent = nullptr);


    virtual void paintEvent(QPaintEvent *event);



    ~Widget();


    gripper g;
    vector<robotUR5> robots;
    vector<string> gripperports;
    vector<gripper> grippers;

private slots:

    void dataUpdate();

    void on_clockwise_clicked();

    void on_counter_clicked();

    void on_stop_clicked();

    void on_junk_clicked();

    void on_pushButton_clicked();

private:
    void setup();

    void guiUpdate();
    void animation();

    Ui::Widget *ui;
    QTimer *timer;
    database d;

};
#endif // WIDGET_H
