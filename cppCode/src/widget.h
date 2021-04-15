#ifndef WIDGET_H
#define WIDGET_H

//UI
#include <QWidget>
#include <QPainter>
#include <QtMath>

//ALL
#include <memory>
#include <vector>
#include <string>

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


private:
    std::unique_ptr<Ui::Widget> ui;
    void animation();
    void guiUpdate();

};
#endif // WIDGET_H
