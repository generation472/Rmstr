//--------------------------------------------------------
#include "wmanualcontrol.h"
#include "ui_wmanualcontrol.h"
#include "csys.h"
#define   BitIsSet(reg, bit) ((reg & (1<<bit)) != 0)
//--------------------------------------------------------
wManualControl::wManualControl(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::wManualControl)
{
	ui->setupUi(this);

	rowSelected = -1;

	ui->tableWidget->setColumnCount(6);
	ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("№"));
	ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя\nцепи"));
	ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Режим\nпроверки"));
	ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Мин.\nЗначение"));
	ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Макс.\nЗначение"));
	ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Второй\nпараметр"));


}
//--------------------------------------------------------
wManualControl::~wManualControl()
{
	delete ui;
}
//--------------------------------------------------------
void wManualControl::slot_sentTable(QVector<TSTRLINKPOINT> linksTable)
{
	ui->tableWidget->clearContents();
	ui->tableWidget->setRowCount(0);

	rowSelected = -1;

	for(TSTRLINKPOINT links: linksTable)
	{
			int row = ui->tableWidget->rowCount();
			ui->tableWidget->insertRow(row);

			QTableWidgetItem *id = new QTableWidgetItem(QString::number(links.Id));

			Qt::ItemFlags eFlags = id->flags();
			eFlags &= ~Qt::ItemIsEditable;
			id->setFlags(eFlags);
			id->setFlags(Qt::ItemIsEditable);

			ui->tableWidget->setItem(row, 0,id);
			ui->tableWidget->setItem(row, 1, new QTableWidgetItem(links.NameLink));
			ui->tableWidget->setItem(row, 2, new QTableWidgetItem(links.ModeCheck));
			ui->tableWidget->setItem(row, 3, new QTableWidgetItem(links.MinValue));
			ui->tableWidget->setItem(row, 4, new QTableWidgetItem(links.MaxValue));
			ui->tableWidget->setItem(row, 5, new QTableWidgetItem(links.SecondValue));
	}

	ui->tableWidget->resizeColumnsToContents();

}
//--------------------------------------------------------
void wManualControl::slot_sentResult(double Im, double Sec, bool check)
{

	if(check)
	{
		ui->Im->setStyleSheet("background-color: rgb(171, 255, 185)");
		ui->Sec->setStyleSheet("background-color: rgb(171, 255, 185)");
	}
	else
	{
		ui->Im->setStyleSheet("background-color: rgb(255, 39, 39);");
		ui->Sec->setStyleSheet("background-color: rgb(255, 39, 39);");
	}

	QString s;
	ui->Im->setText(s.sprintf("%.2f", Im));
	ui->Sec->setText(s.sprintf("%.3f", Sec));

	ui->pushButton->setEnabled(true);
}
//--------------------------------------------------------
void wManualControl::slot_statusDeviceM(TSTATUSDEVICE status)
{

		if( BitIsSet(status, 1))
		{
			return;
		}

		if(rowSelected == -1)
			return;

		ui->pushButton->setEnabled(false);

		emit signal_checkLink(ui->plus->text(), ui->minus->text());

		ui->Im->setStyleSheet("background-color: rgb(255, 255, 255);");
		ui->Sec->setStyleSheet("background-color: rgb(255, 255, 255);");
		ui->Sec->setText("");
		ui->Im->setText("");


}
//--------------------------------------------------------
void wManualControl::showEvent(QShowEvent *event)
{
	Q_UNUSED(event);
	emit signal_getTableLink();
}
//--------------------------------------------------------
void wManualControl::on_tableWidget_cellClicked(int row, int column)
{
	Q_UNUSED(column);


	if(rowSelected != -1)
	{
			int countColumn = ui->tableWidget->columnCount();

			for(int i = 0; i < countColumn; i++)
			{
					ui->tableWidget->item(rowSelected, i)->setBackground(Qt::white);
			}
	}


	rowSelected = row;
	int countColumn = ui->tableWidget->columnCount();

	for(int i = 0; i < countColumn; i++)
	{
			ui->tableWidget->item(rowSelected, i)->setBackground(QColor(252, 255, 176));
	}

	QStringList list = ui->tableWidget->item(rowSelected,1)->text().split("-");
	if(list.size() == 2)
	{
		ui->plus->setText(list[0]);
		ui->minus->setText(list[1]);
	}

	ui->Im->setStyleSheet("background-color: rgb(255, 255, 255);");
	ui->Sec->setStyleSheet("background-color: rgb(255, 255, 255);");
	ui->Sec->setText("");
	ui->Im->setText("");

	ui->mode->setText(ui->tableWidget->item(rowSelected,2)->text());
	ui->minValue->setText(ui->tableWidget->item(rowSelected, 3)->text());
	ui->maxValue->setText(ui->tableWidget->item(rowSelected, 4)->text());
	ui->secondValue->setText(ui->tableWidget->item(rowSelected, 5)->text());

}
//--------------------------------------------------------
void wManualControl::on_pushButton_clicked()
{
	emit signal_checkDeviceM();
}
//--------------------------------------------------------
void wManualControl::on_lineEdit_textEdited(const QString &arg1)
{

		emit signal_getTableLink(arg1);
}
//--------------------------------------------------------
