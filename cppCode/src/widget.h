#ifndef WIDGET_H
#define WIDGET_H

//Files
#include "robotur5.h"
#include "gripper.h"

//UI
#include <QWidget>
#include <QPainter>
#include <QtMath>

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




private:
    void setup();
    std::unique_ptr<Ui::Widget> ui;
    void dataUpdate();
    void guiUpdate();
    void animation();




};
#endif // WIDGET_H
