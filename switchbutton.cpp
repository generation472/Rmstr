//---------------------------------------------------
#include "switchbutton.h"
#include <QPainter>
#include <QLinearGradient>
//---------------------------------------------------
SwitchButton::SwitchButton(QWidget *parent) : QWidget(parent)
{
	m_switch = false;
	sizeWidget.setWidth(135);
	sizeWidget.setHeight(55);
	this->setMinimumSize(sizeWidget);
	this->setMaximumSize(sizeWidget);


}
//---------------------------------------------------
void SwitchButton::setSwitch(bool fl)
{
	m_switch = fl;
	repaint();
}
//---------------------------------------------------
void SwitchButton::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	int w = width() -20;
	int h = height() - 20;
	int x = 10;
	int y = 10;
	float roundRect = 0;
	float roundRect2 = 0;

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);


	QLinearGradient gradient(x, y, w, h);
	if(m_switch)
	{
		gradient.setColorAt(0, Qt::darkGreen);
		gradient.setColorAt(1, Qt::green);
	}
	else
	{
		gradient.setColorAt(0, Qt::darkRed);
		gradient.setColorAt(1, Qt::red);
	}

	painter.setBrush(gradient);
	painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
	painter.drawRoundedRect(QRect(x, y, w, h), roundRect, roundRect);


	x += 5;
	y += 5;
	w -= 10;
	h -= 10;

	QFont font = painter.font();
	font.setPointSize (15);
	font.setBold(true);
	painter.setFont(font);

	painter.setBrush(QBrush(Qt::white));
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
	if(m_switch)
	{
		w /=2;
		x +=w;
		painter.drawRoundedRect(QRect(x, y, w, h), roundRect2, roundRect2);
		painter.setPen((QPen(Qt::black, 3,  Qt::SolidLine)));
		painter.drawText(QRect(x, y, w, h), Qt::AlignHCenter | Qt::AlignVCenter, "ON");
	}
	else
	{
		w /=2;
		painter.drawRoundedRect(QRect(x, y, w, h), roundRect2, roundRect2);
		painter.setPen((QPen(Qt::black, 3,  Qt::SolidLine)));
		painter.drawText(QRect(x, y, w, h), Qt::AlignHCenter | Qt::AlignVCenter, "OFF");
	}


}
//---------------------------------------------------
void SwitchButton::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	m_switch = !m_switch;
	repaint();
	emit signal_clicked(m_switch);
}
//---------------------------------------------------
