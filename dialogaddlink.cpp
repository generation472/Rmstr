//----------------------------------------------------------
#include "dialogaddlink.h"
#include "ui_dialogaddlink.h"
#include "QLineEdit"
//----------------------------------------------------------
dialogAddLink::dialogAddLink(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::dialogAddLink)
{
	ui->setupUi(this);

	ui->tableWidget->resizeColumnsToContents();


	QRegExp rx("[A-Z0-9:-]{1,15}");
	QValidator *validator = new QRegExpValidator(rx, this);
	QLineEdit *edit = new QLineEdit;

	edit->setValidator(validator);
	ui->tableWidget->setCellWidget(0, 0, edit);

	//==========================================
	QRegExp rx1("[RC]{1,1}");
	validator = new QRegExpValidator(rx1, this);
	edit = new QLineEdit;

	edit->setValidator(validator);
	ui->tableWidget->setCellWidget(0, 1, edit);

	//==========================================
	QRegExp rx2("[0-9.]{1,20}");
	validator = new QRegExpValidator(rx2, this);
	edit = new QLineEdit;

	edit->setValidator(validator);
	ui->tableWidget->setCellWidget(0, 2, edit);

	//==========================================
	QRegExp rx3("[0-9.]{1,20}");
	validator = new QRegExpValidator(rx3, this);
	edit = new QLineEdit;

	edit->setValidator(validator);
	ui->tableWidget->setCellWidget(0, 3, edit);

	//==========================================
	QRegExp rx4("[0-9.]{1,20}");
	validator = new QRegExpValidator(rx4, this);
	edit = new QLineEdit;

	edit->setValidator(validator);
	ui->tableWidget->setCellWidget(0, 4, edit);

}
//----------------------------------------------------------
dialogAddLink::~dialogAddLink()
{
	delete ui;
}
//----------------------------------------------------------
void dialogAddLink::on_pushButton_clicked()
{
		TSTRLINKPOINT link;



		link.Id = 0;
		link.NameLink =  qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 0))->text();
		link.ModeCheck =  qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 1))->text();
		link.MinValue =  qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 2))->text();
		link.MaxValue =  qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 3))->text();
		link.SecondValue =  qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(0, 4))->text();
		link.IdPointMinus = 0;
		link.IdPointPlus = 0;


		bool fl = true;

		if(link.NameLink == "")
			fl = false;
		if(link.ModeCheck == "")
			fl = false;
		if(link.MinValue == "")
			fl = false;
		if(link.MaxValue == "")
			fl = false;

		if(!fl)
			return;


		emit signal_addLink(link);
		close();

}
//----------------------------------------------------------
void dialogAddLink::on_pushButton_2_clicked()
{
		close();
}
//----------------------------------------------------------
