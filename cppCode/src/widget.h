#ifndef WIDGET_H
#define WIDGET_H

//Files
//#include "robotur5.h"
//#include "gripper.h"
//#include "database.h"
#include "controller.h"

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
#include <stdio.h>

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

private slots:
    void on_calibrate_clicked();

    void on_clockwise_clicked();

    void on_counter_clicked();

    void on_stop_clicked();

    void on_spinBox_valueChanged(int arg1);

private:


    void guiUpdate();
    void animation();

    Ui::Widget *ui;

    Controller c;

};
#endif // WIDGET_H
