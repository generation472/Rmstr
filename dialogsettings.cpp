//-------------------------------------------------------------
#include "dialogsettings.h"
#include "ui_dialogsettings.h"
#include <QDebug>
//-------------------------------------------------------------
dialogSettings::dialogSettings(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::dialogSettings)
{
	ui->setupUi(this);

	for(QSerialPortInfo port: QSerialPortInfo::availablePorts())
	{
		ui->serialPort->addItem(port.portName());
	}

}
//-------------------------------------------------------------
dialogSettings::~dialogSettings()
{
	delete ui;
}
//-------------------------------------------------------------
void dialogSettings::slot_setSubList(QStringList list)
{
	ui->numberSub->clear();
	for(QString name: list)
	{
		ui->numberSub->addItem(name);
	}

	ui->numberSub->setCurrentText(numberSub);
}
//-------------------------------------------------------------
void dialogSettings::slot_SetSettings(bool table, bool error)
{
	ui->soundError->setChecked(error);
	ui->twoTable->setChecked(table);
}
//-------------------------------------------------------------
void dialogSettings::slot_SetSettings(QString numberSub, QString numberPort, int ms)
{
	this->numberSub = numberSub;
	this->numberPort = numberPort;
	this->ms = ms;
}
//-------------------------------------------------------------
void dialogSettings::showEvent(QShowEvent *event)
{
	Q_UNUSED(event);
	emit signal_getSubList();

	ui->ms->setText(QString::number(ms));

	ui->serialPort->setCurrentText(numberPort);

}
//-------------------------------------------------------------
void dialogSettings::on_pushButton_clicked()
{
	QString numberSub = ui->numberSub->currentText();
	QString numberPort = ui->serialPort->currentText();
	int ms = ui->ms->text().toInt();

	this->numberPort = numberPort;
	this->numberSub = numberSub;
	this->ms = ms;


	emit signal_SetSettings(ui->twoTable->isChecked(), ui->soundError->isChecked());
	emit signal_SetSettings(numberSub, numberPort, ms);
	close();
}
//-------------------------------------------------------------
void dialogSettings::on_pushButton_2_clicked()
{
	close();
}
//-------------------------------------------------------------
