//-------------------------------------------------------------
#include "wproc.h"
#include "ui_wproc.h"
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QTextCodec>
#include <QApplication>
//-------------------------------------------------------------
wProc::wProc(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::wProc)
{
	ui->setupUi(this);

	ui->tW1->resizeColumnsToContents();
	ui->tW2->resizeColumnsToContents();

	nameDir = QApplication::applicationDirPath()+"/Protocol";

	ui->listView1->setModel(&m1);
	ui->listView2->setModel(&m2);

	searchDoc();

	setViewTwoTable(false);
	choosenNameDoc1 = "";
	choosenNameDoc2 = "";

}
//-------------------------------------------------------------
wProc::~wProc()
{
	delete ui;
}
//-------------------------------------------------------------
void wProc::setViewTwoTable(bool f)
{
	if(f)
	{
		ui->frame_2->show();
	}
	else
	{
		ui->frame_2->hide();
	}
}
//-------------------------------------------------------------
void wProc::slot_setSettingsTable(bool fl)
{

	setViewTwoTable(fl);
}
//-------------------------------------------------------------
void wProc::searchDoc()
{

	QStringList listFiles;
	QDir dir(QApplication::applicationDirPath() + "/Protocol/");

	if(dir.exists())
	{
			listFiles = dir.entryList(QStringList("*.xlsx"), QDir::Files);
	}
	else
	{
		return;
	}

	QStringList doc;
	for(QString str: listFiles)
	{
		Document xlsx(nameDir + "/" + str);

		if(xlsx.read(2,2).toString() == "Протокол проверки")
		{
			doc.push_back(str);

		}
	}

	m1.setStringList(doc);
	m2.setStringList(doc);


}
//-------------------------------------------------------------
void wProc::on_listView1_clicked(const QModelIndex &index)
{
	int rowDoc = 9;
	QString nameDoc = m1.data(index, Qt::DisplayRole).toString();
	choosenNameDoc1 = nameDoc;
	ui->tW1->clearContents();
	ui->tW1->setRowCount(0);
	Document xlsx(nameDir + "/" + nameDoc);

	while(true)
	{


		if(xlsx.read(rowDoc, 1).toString() == "")
		{
			break;
		}

		int row = ui->tW1->rowCount();
		ui->tW1->setRowCount(row +1);



		ui->tW1->setItem(row, 0, new QTableWidgetItem(xlsx.read(rowDoc, 1).toString()));
		ui->tW1->setItem(row, 1, new QTableWidgetItem(xlsx.read(rowDoc, 2).toString()));
		ui->tW1->setItem(row, 2, new QTableWidgetItem(xlsx.read(rowDoc, 3).toString()));
		ui->tW1->setItem(row, 3, new QTableWidgetItem(xlsx.read(rowDoc, 4).toString()));
		ui->tW1->setItem(row, 4, new QTableWidgetItem(xlsx.read(rowDoc, 5).toString()));
		ui->tW1->setItem(row, 5, new QTableWidgetItem(xlsx.read(rowDoc, 6).toString()));
		ui->tW1->setItem(row, 6, new QTableWidgetItem(xlsx.read(rowDoc, 7).toString()));
		ui->tW1->setItem(row, 7, new QTableWidgetItem(xlsx.read(rowDoc, 8).toString()));

		rowDoc++;

	}

	ui->tW1->resizeColumnsToContents();

}
//-------------------------------------------------------------
void wProc::on_listView2_clicked(const QModelIndex &index)
{
	int rowDoc = 9;
	QString nameDoc = m1.data(index, Qt::DisplayRole).toString();
	choosenNameDoc2 = nameDoc;
	ui->tW2->clearContents();
	ui->tW2->setRowCount(0);
	Document xlsx(nameDir + "/" + nameDoc);

	while(true)
	{


		if(xlsx.read(rowDoc, 1).toString() == "")
		{
			break;
		}

		int row = ui->tW2->rowCount();
		ui->tW2->setRowCount(row +1);



		ui->tW2->setItem(row, 0, new QTableWidgetItem(xlsx.read(rowDoc, 1).toString()));
		ui->tW2->setItem(row, 1, new QTableWidgetItem(xlsx.read(rowDoc, 2).toString()));
		ui->tW2->setItem(row, 2, new QTableWidgetItem(xlsx.read(rowDoc, 3).toString()));
		ui->tW2->setItem(row, 3, new QTableWidgetItem(xlsx.read(rowDoc, 4).toString()));
		ui->tW2->setItem(row, 4, new QTableWidgetItem(xlsx.read(rowDoc, 5).toString()));
		ui->tW2->setItem(row, 5, new QTableWidgetItem(xlsx.read(rowDoc, 6).toString()));
		ui->tW2->setItem(row, 6, new QTableWidgetItem(xlsx.read(rowDoc, 7).toString()));
		ui->tW2->setItem(row, 7, new QTableWidgetItem(xlsx.read(rowDoc, 8).toString()));

		rowDoc++;

	}

	ui->tW2->resizeColumnsToContents();
}
//-------------------------------------------------------------
void wProc::showEvent(QShowEvent *event)
{
	Q_UNUSED(event);
	searchDoc();
}
//-------------------------------------------------------------
void wProc::on_pushButton_clicked()
{
	if(choosenNameDoc1 != "")
	{
		QFile file(nameDir + "/" + choosenNameDoc1);

		if(file.remove())
		{
			searchDoc();
			choosenNameDoc1 = "";
			ui->tW1->clearContents();
			ui->tW1->setRowCount(0);
			ui->tW2->clearContents();
			ui->tW2->setRowCount(0);
		}
		else
		{
			QMessageBox mb;
			mb.setText("Ошибка удаления");
			mb.setWindowTitle("Ошибка");
			mb.exec();
		}
	}
	else
	{
		return;
	}

}
//-------------------------------------------------------------
void wProc::on_pushButton_3_clicked()
{
	if(choosenNameDoc2 != "")
	{
		QFile file(nameDir + "/" + choosenNameDoc2);

		if(file.remove())
		{
			searchDoc();
			choosenNameDoc2 = "";
			ui->tW1->clearContents();
			ui->tW1->setRowCount(0);
			ui->tW2->clearContents();
			ui->tW2->setRowCount(0);
		}
		else
		{
			QMessageBox mb;
			mb.setText("Ошибка удаления");
			mb.setWindowTitle("Ошибка");
			mb.exec();
		}
	}
	else
	{
		return;

	}
}
//-------------------------------------------------------------
void wProc::on_pushButton_2_clicked()
{

	QByteArray str = (nameDir).toUtf8();

	QTextCodec *codec_1251 = QTextCodec::codecForName("Windows-1251");

	QString string = codec_1251->toUnicode(str);
	QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(string)));
}
//-------------------------------------------------------------
void wProc::on_pushButton_4_clicked()
{
	QByteArray str = (nameDir).toUtf8();

	QTextCodec *codec_1251 = QTextCodec::codecForName("Windows-1251");

	QString string = codec_1251->toUnicode(str);
	QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(string)));
}
//-------------------------------------------------------------
