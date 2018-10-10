//-------------------------------------------------------
#include "dialogaddpoint.h"
#include "ui_dialogaddpoint.h"
#include <QLineEdit>
#include <QDebug>
//-------------------------------------------------------
dialogAddPoint::dialogAddPoint(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::dialogAddPoint)
{
	ui->setupUi(this);

	ui->tableWidget->resizeColumnsToContents();

	QRegExp rx("[A-Z0-9:]{1,7}");
	QValidator *validator = new QRegExpValidator(rx, this);
	QLineEdit *edit = new QLineEdit;

	edit->setValidator(validator);
	ui->tableWidget->setCellWidget(0, 0, edit);

	//==========================================
	QRegExp rx1("[0-9]{1,2}");
	validator = new QRegExpValidator(rx1, this);
	edit = new QLineEdit;

	edit->setValidator(validator);
	ui->tableWidget->setCellWidget(0, 1, edit);

	//==========================================
	QRegExp rx2("[S0-9]{1,3}");
	validator = new QRegExpValidator(rx2, this);
	edit = new QLineEdit;

	edit->setValidator(validator);
	ui->tableWidget->setCellWidget(0, 2, edit);

	//==========================================
	QRegExp rx3("[0-9]{1,16}");
	validator = new QRegExpValidator(rx3, this);
	edit = new QLineEdit;

	edit->setText("0000000000000000");
	edit->setValidator(validator);
	ui->tableWidget->setCellWidget(0, 3, edit);


}
//-------------------------------------------------------
dialogAddPoint::~dialogAddPoint()
{
	delete ui;
}
//-------------------------------------------------------
void dialogAddPoint::on_pushButton_clicked()
{

	point.id = 0;
	point.NamePoint = qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 0))->text();
	point.RG = qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 1))->text();
	point.CS = qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 2))->text();
	point.BusPlus = qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 3))->text();


	bool fl = true;

	if(point.NamePoint == "")
		fl = false;
	if(point.RG == "")
		fl = false;
	if(point.CS == "")
		fl = false;
	if(point.BusPlus == "")
		fl = false;

	if(!fl)
		return;

	emit signal_addPoint(point);

	close();
}
//-------------------------------------------------------
void dialogAddPoint::on_pushButton_2_clicked()
{
	close();
}
//-------------------------------------------------------
void dialogAddPoint::showEvent(QShowEvent *event)
{
	Q_UNUSED(event);
	/*
	//FIXME УДАЛИТЬ !!!!
	qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 3))->setText(point.BusPlus);
	qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 1))->setText(point.RG);
	qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 2))->setText(point.CS);
	*/
}
//-------------------------------------------------------
