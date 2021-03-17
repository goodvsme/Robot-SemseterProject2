#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include "ur5andgripper.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //drawing
    virtual void paintEvent(QPaintEvent *event);

    int ang;
    vector<ur5AndGripper> ur5Bots;


private slots:
    void on_spinBox_ang_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
