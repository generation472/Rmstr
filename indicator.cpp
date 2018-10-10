//---------------------------------------------------------
#include "indicator.h"
#include <QPainter>
//---------------------------------------------------------
Indicator::Indicator(QWidget *parent) : QWidget(parent)
{

	f_status = false;
}
//---------------------------------------------------------
Indicator::~Indicator()
{

}
//---------------------------------------------------------
void Indicator::slot_changeStatus(bool fl)
{
    f_status = fl;
    repaint();
}
//---------------------------------------------------------
void Indicator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    double x1, y1, x2, y2;
    QPainter painter(this);

    if(width() < height())
    {
        x2 = width();
        y2 = width();
    }
    else
    {
        x2 = height();
        y2 = height();
    }

    if(width() > x2)
    {
        x1 = (width() - x2) / 2;
    }
    else
    {
        x1 = 0;
    }

    if(height() > y2)
    {
        y1 = (height() - y2) / 2;
    }
    else
    {
        y1 = 0;
    }

    x1 += 5;
    y1 += 5;

    x2 -= 10;
    y2 -= 10;


    QRadialGradient radialGrad(QPointF(this->width()/2, this->height()/2), y2/2);

    if(f_status)
    {
        radialGrad.setColorAt(0, Qt::darkGreen);
        radialGrad.setColorAt(0.1, Qt::green);
        radialGrad.setColorAt(0.2, Qt::darkGreen);
        radialGrad.setColorAt(0.3, Qt::green);
        radialGrad.setColorAt(0.4, Qt::darkGreen);
        radialGrad.setColorAt(0.5, Qt::green);
        radialGrad.setColorAt(0.6, Qt::darkGreen);
        radialGrad.setColorAt(0.7, Qt::green);
        radialGrad.setColorAt(0.8, Qt::darkGreen);
        radialGrad.setColorAt(0.9, Qt::green);
        radialGrad.setColorAt(1.0, Qt::darkGreen);
    }
    else
    {
        radialGrad.setColorAt(0, Qt::darkRed);
        radialGrad.setColorAt(0.1, Qt::red);
        radialGrad.setColorAt(0.2, Qt::darkRed);
        radialGrad.setColorAt(0.3, Qt::red);
        radialGrad.setColorAt(0.4, Qt::darkRed);
        radialGrad.setColorAt(0.5, Qt::red);
        radialGrad.setColorAt(0.6, Qt::darkRed);
        radialGrad.setColorAt(0.7, Qt::red);
        radialGrad.setColorAt(0.8, Qt::darkRed);
        radialGrad.setColorAt(0.9, Qt::red);
        radialGrad.setColorAt(1.0, Qt::darkRed);
    }

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(radialGrad);
    painter.setPen((QPen(Qt::black, 2,  Qt::SolidLine)));


    painter.drawEllipse(QRect(x1, y1, x2 , y2));
}
//---------------------------------------------------------
