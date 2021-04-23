#ifndef WIDGET_H
#define WIDGET_H

//Files
#include "robotur5.h"
#include "gripper.h"

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



    vector<robotUR5> rob;



    virtual void paintEvent(QPaintEvent *event);

    ~Widget();




private slots:

    void dataUpdate();

    void on_clockwise_clicked();

    void on_counter_clicked();

    void on_stop_clicked();

    void on_junk_clicked();

private:
    void setup();

    void guiUpdate();
    void animation();

    gripper testgg;
    Ui::Widget *ui;
    QTimer *timer;


};
#endif // WIDGET_H
