//----------------------------------------------------------
#include "wautocontrol.h"
#include "ui_wautocontrol.h"
#include "csys.h"
#include <QDebug>
#include <QFileDialog>
#include <QDate>
#include <QMessageBox>

#define   BitIsSet(reg, bit) ((reg & (1<<bit)) != 0)
//----------------------------------------------------------
wAutoControl::wAutoControl(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::wAutoControl)
{
	ui->setupUi(this);


	ui->pbStart->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	ui->pbStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
	ui->pbPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));

	ui->pbPause->setEnabled(false);

	ui->tableWidget->resizeRowsToContents();
	ui->tableWidget->resizeColumnsToContents();
	ui->progressBar->setMinimum(0);
	ui->progressBar->setValue(0);
}
//----------------------------------------------------------
wAutoControl::~wAutoControl()
{
	delete ui;
}
//----------------------------------------------------------
void wAutoControl::slot_statusDeviceA(TSTATUSDEVICE status)
{

	if( BitIsSet(status, 1))
	{
		return;
	}
	emit signal_setStatusAutoControl(S_BEGIN);
}
//----------------------------------------------------------
void wAutoControl::slot_sentResult(TSTRLINKPOINT link, double Im, double Sec, bool check)
{
	QString str;

	ui->progressBar->setValue(ui->progressBar->value() + 1);

	if(check)
	{
		ui->okCheck->setText(QString::number(ui->okCheck->text().toInt()+1));
		ui->allCheck->setText(QString::number(ui->allCheck->text().toInt()+1));
	}
	else
	{
		ui->allCheck->setText(QString::number(ui->allCheck->text().toInt()+1));
		ui->badCheck->setText(QString::number(ui->badCheck->text().toInt()+1));

		int row = ui->tableWidget->rowCount();
		ui->tableWidget->setRowCount(row +1);


		ui->tableWidget->setItem(row, 0, new QTableWidgetItem(link.NameLink));
		ui->tableWidget->setItem(row, 1, new QTableWidgetItem(link.ModeCheck));
		ui->tableWidget->setItem(row, 2, new QTableWidgetItem(link.MinValue));
		ui->tableWidget->setItem(row, 3, new QTableWidgetItem(link.MaxValue));
		ui->tableWidget->setItem(row, 4, new QTableWidgetItem(link.SecondValue));
		ui->tableWidget->setItem(row, 5, new QTableWidgetItem(str.sprintf("%.3f", Im)));
		ui->tableWidget->setItem(row, 6, new QTableWidgetItem(str.sprintf("%.3f", Sec)));

		ui->tableWidget->resizeColumnsToContents();
	}


}
//----------------------------------------------------------
void wAutoControl::slot_statusAutoCheck(TSTATUSAUTOCHECK status)
{

	QMessageBox *ms;

	switch (status)
	{
	case S_PAUSE:
		ui->pbPause->setEnabled(false);
		ui->pbStart->setText(" Продолжить проверку ");
		ui->pbStart->setEnabled(true);
		break;

	case S_STOP:
		ui->pbStart->setText(" Начать проверку ");
		ui->pbPause->setEnabled(false);
		ui->pbStart->setEnabled(true);
		ms = new QMessageBox(this);
		ms->setText("Автоматическая проверка закончена.");
		ms->setWindowTitle("RM_STR");
		ms->exec();
		break;

	case S_CONTINUE:
		ui->pbStart->setText(" Идёт проверка ");
		ui->pbPause->setEnabled(true);
		ui->pbStart->setEnabled(false);
		break;

	case S_BEGIN:
		ui->progressBar->setValue(0);
		ui->pbStart->setText(" Идёт проверка ");
		ui->pbPause->setEnabled(true);
		ui->pbStart->setEnabled(false);
		ui->okCheck->setText("0");
		ui->badCheck->setText("0");
		ui->allCheck->setText("0");

		ui->tableWidget->clearContents();
		ui->tableWidget->setRowCount(0);
		break;


	default:
		break;
	}


}
//----------------------------------------------------------
void wAutoControl::slot_setRangeProgressBar(int max)
{
	ui->progressBar->setMaximum(max);
}
//----------------------------------------------------------
void wAutoControl::on_pbStart_clicked()
{
	emit signal_checkDeviceA();
}
//----------------------------------------------------------
void wAutoControl::on_pbPause_clicked()
{
	emit signal_setStatusAutoControl(S_PAUSE);
}
//----------------------------------------------------------
void wAutoControl::on_pbStop_clicked()
{
	emit signal_setStatusAutoControl(S_STOP);
}
//----------------------------------------------------------
void wAutoControl::on_pushButton_2_clicked()
{
	QString nameFile = QFileDialog::getSaveFileName(this, "Сохранить", "", tr("Doc (*.xlsx)"));

	Document doc;


	Format formatHcVc;                                                        ///Создание форматирования
	formatHcVc.setHorizontalAlignment(Format::AlignHCenter);                  ///Задаём горизонтальное форматирование
	formatHcVc.setVerticalAlignment(Format::AlignVCenter);                    ///Задаём вертикальное форматирование
	formatHcVc.setFontColor(Qt::black);
	formatHcVc.setFontBold(true);
	formatHcVc.setFontSize(15);
	formatHcVc.setTextWarp(true);

	doc.setColumnWidth(1, 6);
	doc.setRowHeight(8, 25);


	CellRange r(2,2,2,5);
	doc.write(r.firstRow(), r.firstColumn(),"Протокол проверки" , formatHcVc);
	doc.mergeCells(r, formatHcVc);

	formatHcVc.setFontBold(false);
	formatHcVc.setBorderStyle(Format::BorderThin);
	formatHcVc.setHorizontalAlignment(Format::AlignLeft);                  ///Задаём горизонтальное форматирование
	formatHcVc.setVerticalAlignment(Format::AlignVCenter);
	formatHcVc.setFontSize(13);
	CellRange r2(4,1,4,4);
	doc.write(r2.firstRow(), r2.firstColumn(), "Дата проверки:" , formatHcVc);
	doc.mergeCells(r2, formatHcVc);

	CellRange r3(4,5,4,6);
	doc.write(r3.firstRow(), r3.firstColumn(), QDate::currentDate().toString("dd.MM.yyyy"), formatHcVc);
	doc.mergeCells(r3, formatHcVc);



	CellRange r6(7,1,7,6);
	formatHcVc.setBorderStyle(Format::BorderThin);
	doc.mergeCells(r6, formatHcVc);

	CellRange r7(7,7,7,8);
	doc.write(r7.firstRow(), r7.firstColumn(), "Измеренное значение", formatHcVc);
	doc.mergeCells(r7, formatHcVc);


	formatHcVc.setHorizontalAlignment(Format::AlignHCenter);
	formatHcVc.setTextWarp(true);
	formatHcVc.setFontSize(11);
	doc.setColumnWidth(2, 12);
	doc.setColumnWidth(3, 10);
	doc.setColumnWidth(4, 10);
	doc.setColumnWidth(5, 10);
	doc.setColumnWidth(6, 10);
	doc.setColumnWidth(7, 12);
	doc.setColumnWidth(8, 12);

	CellRange r8(8,1,8,1);
	doc.write(r8.firstRow(), r8.firstColumn(), "№", formatHcVc);
	doc.mergeCells(r8, formatHcVc);


	CellRange r9(8,2,8,2);
	doc.write(r9.firstRow(), r9.firstColumn(), "Имя цепи", formatHcVc);
	doc.mergeCells(r9, formatHcVc);

	CellRange r10(8,3,8,3);
	doc.write(r10.firstRow(), r10.firstColumn(), "Режим проверки", formatHcVc);
	doc.mergeCells(r10, formatHcVc);

	CellRange r11(8,4,8,4);
	doc.write(r11.firstRow(), r11.firstColumn(), "Мин. значение", formatHcVc);
	doc.mergeCells(r11, formatHcVc);

	CellRange r12(8,5,8,5);
	doc.write(r12.firstRow(), r12.firstColumn(), "Мак. Значение", formatHcVc);
	doc.mergeCells(r12, formatHcVc);

	CellRange r13(8,6,8,6);
	doc.write(r13.firstRow(), r13.firstColumn(), "Второй параметр", formatHcVc);
	doc.mergeCells(r13, formatHcVc);

	CellRange r14(8,7,8,7);
	doc.write(r14.firstRow(), r14.firstColumn(), "Первый параметр", formatHcVc);
	doc.mergeCells(r14, formatHcVc);

	CellRange r15(8,8,8,8);
	doc.write(r15.firstRow(), r15.firstColumn(), "Второй параметр", formatHcVc);
	doc.mergeCells(r15, formatHcVc);


	for(int i = 0; i < ui->tableWidget->rowCount(); i++)
	{

		Format formatHcVc;                                                        ///Создание форматирования
		formatHcVc.setHorizontalAlignment(Format::AlignHCenter);                  ///Задаём горизонтальное форматирование
		formatHcVc.setVerticalAlignment(Format::AlignVCenter);                    ///Задаём вертикальное форматирование
		formatHcVc.setFontColor(Qt::black);
		formatHcVc.setFontBold(true);
		formatHcVc.setFontSize(11);
		formatHcVc.setBorderStyle(Format::BorderThin);

		CellRange r1(i+9,1,i+9,1);
		doc.write(r1.firstRow(), r1.firstColumn(), QString::number(i), formatHcVc);
		doc.mergeCells(r1, formatHcVc);

		CellRange r2(i+9,2,i+9,2);
		doc.write(r2.firstRow(), r2.firstColumn(), ui->tableWidget->item(i,0)->text(), formatHcVc);
		doc.mergeCells(r2, formatHcVc);

		CellRange r3(i+9,3,i+9,3);
		doc.write(r3.firstRow(), r3.firstColumn(), ui->tableWidget->item(i,1)->text(), formatHcVc);
		doc.mergeCells(r3, formatHcVc);

		CellRange r4(i+9,4,i+9,4);
		doc.write(r4.firstRow(), r4.firstColumn(), ui->tableWidget->item(i,2)->text(), formatHcVc);
		doc.mergeCells(r4, formatHcVc);

		CellRange r5(i+9,5,i+9,5);
		doc.write(r5.firstRow(), r5.firstColumn(), ui->tableWidget->item(i,3)->text(), formatHcVc);
		doc.mergeCells(r5, formatHcVc);

		CellRange r6(i+9,6,i+9,6);
		doc.write(r6.firstRow(), r6.firstColumn(), ui->tableWidget->item(i,4)->text(), formatHcVc);
		doc.mergeCells(r6, formatHcVc);

		CellRange r7(i+9,7,i+9,7);
		doc.write(r7.firstRow(), r7.firstColumn(), ui->tableWidget->item(i,5)->text(), formatHcVc);
		doc.mergeCells(r7, formatHcVc);

		CellRange r8(i+9,8,i+9,8);
		doc.write(r8.firstRow(), r8.firstColumn(), ui->tableWidget->item(i,6)->text(), formatHcVc);
		doc.mergeCells(r8, formatHcVc);

	}


	doc.saveAs(nameFile);
}
//----------------------------------------------------------
