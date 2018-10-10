//--------------------------------------------------------
#include "proc.h"
#include <QApplication>
#include <QDate>
#include <QFile>
//--------------------------------------------------------
Proc::Proc(QObject *parent) : QObject(parent)
{


	//========================Создание папки для сесии ===================
		QDir dir(QApplication::applicationDirPath()+"/Protocol");

		if(!dir.exists())
		{
				dir.setPath(QApplication::applicationDirPath());
				dir.mkdir("Protocol");
		}

		nameDir = QApplication::applicationDirPath()+"/Protocol";

		idNewDoc = 0;
/*
		newProc("test2.xlsx", "124511321");
		IdRow = 9;

		TSTRLINKPOINT link;
		QString Im;
		QString Sec;
		link.Id = 0;
		link.NameLink = "X8:A1-X8:A3";
		link.ModeCheck = "R";
		link.SecondValue = "0.11";
		link.MinValue = "100";
		link.MaxValue = "200";
		Im = "233.02";
		Sec = "0.0001";

		insertLink(link, Im, Sec);
		insertLink(link, Im, Sec);
		insertLink(link, Im, Sec);
		insertLink(link, Im, Sec);
		insertLink(link, Im, Sec);
*/
}
//--------------------------------------------------------
Proc::~Proc()
{

}
//--------------------------------------------------------
void Proc::newProc(QString name, QString techNumber)
{
	nameDoc = name + ".xlsx";
	idNewDoc = 0;
	countRemove = 1;
	checkNameDoc();
	Document xlsx;
	IdRow = 9;

	Format formatHcVc;                                                        ///Создание форматирования
	formatHcVc.setHorizontalAlignment(Format::AlignHCenter);                  ///Задаём горизонтальное форматирование
	formatHcVc.setVerticalAlignment(Format::AlignVCenter);                    ///Задаём вертикальное форматирование
	formatHcVc.setFontColor(Qt::black);
	formatHcVc.setFontBold(true);
	formatHcVc.setFontSize(15);
	formatHcVc.setTextWarp(true);

	xlsx.setColumnWidth(1, 6);
	xlsx.setRowHeight(8, 25);


	CellRange r(2,2,2,5);
	xlsx.write(r.firstRow(), r.firstColumn(),"Протокол проверки" , formatHcVc);
	xlsx.mergeCells(r, formatHcVc);

	formatHcVc.setFontBold(false);
	formatHcVc.setBorderStyle(Format::BorderThin);
	formatHcVc.setHorizontalAlignment(Format::AlignLeft);                  ///Задаём горизонтальное форматирование
	formatHcVc.setVerticalAlignment(Format::AlignVCenter);
	formatHcVc.setFontSize(13);
	CellRange r2(4,1,4,4);
	xlsx.write(r2.firstRow(), r2.firstColumn(), "Дата проверки:" , formatHcVc);
	xlsx.mergeCells(r2, formatHcVc);

	CellRange r3(4,5,4,6);
	xlsx.write(r3.firstRow(), r3.firstColumn(), QDate::currentDate().toString("dd.MM.yyyy"), formatHcVc);
	xlsx.mergeCells(r3, formatHcVc);


	CellRange r4(5,1,5,4);
	xlsx.write(r4.firstRow(), r4.firstColumn(), "Технологический номер:" , formatHcVc);
	xlsx.mergeCells(r4, formatHcVc);

	CellRange r5(5,5,5,6);
	xlsx.write(r5.firstRow(), r5.firstColumn(), techNumber, formatHcVc);
	xlsx.mergeCells(r5, formatHcVc);


	CellRange r6(7,1,7,6);
	formatHcVc.setBorderStyle(Format::BorderThin);
	xlsx.mergeCells(r6, formatHcVc);

	CellRange r7(7,7,7,8);
	xlsx.write(r7.firstRow(), r7.firstColumn(), "Измеренное значение", formatHcVc);
	xlsx.mergeCells(r7, formatHcVc);


	formatHcVc.setHorizontalAlignment(Format::AlignHCenter);
	formatHcVc.setTextWarp(true);
	formatHcVc.setFontSize(11);
	xlsx.setColumnWidth(2, 12);
	xlsx.setColumnWidth(3, 10);
	xlsx.setColumnWidth(4, 10);
	xlsx.setColumnWidth(5, 10);
	xlsx.setColumnWidth(6, 10);
	xlsx.setColumnWidth(7, 12);
	xlsx.setColumnWidth(8, 12);

	CellRange r8(8,1,8,1);
	xlsx.write(r8.firstRow(), r8.firstColumn(), "№", formatHcVc);
	xlsx.mergeCells(r8, formatHcVc);


	CellRange r9(8,2,8,2);
	xlsx.write(r9.firstRow(), r9.firstColumn(), "Имя цепи", formatHcVc);
	xlsx.mergeCells(r9, formatHcVc);

	CellRange r10(8,3,8,3);
	xlsx.write(r10.firstRow(), r10.firstColumn(), "Режим проверки", formatHcVc);
	xlsx.mergeCells(r10, formatHcVc);

	CellRange r11(8,4,8,4);
	xlsx.write(r11.firstRow(), r11.firstColumn(), "Мин. значение", formatHcVc);
	xlsx.mergeCells(r11, formatHcVc);

	CellRange r12(8,5,8,5);
	xlsx.write(r12.firstRow(), r12.firstColumn(), "Мак. Значение", formatHcVc);
	xlsx.mergeCells(r12, formatHcVc);

	CellRange r13(8,6,8,6);
	xlsx.write(r13.firstRow(), r13.firstColumn(), "Второй параметр", formatHcVc);
	xlsx.mergeCells(r13, formatHcVc);

	CellRange r14(8,7,8,7);
	xlsx.write(r14.firstRow(), r14.firstColumn(), "Первый параметр", formatHcVc);
	xlsx.mergeCells(r14, formatHcVc);

	CellRange r15(8,8,8,8);
	xlsx.write(r15.firstRow(), r15.firstColumn(), "Второй параметр", formatHcVc);
	xlsx.mergeCells(r15, formatHcVc);

	xlsx.saveAs(nameDir+ "/" + nameDoc);

}
//--------------------------------------------------------
void Proc::insertLink(TSTRLINKPOINT link, QString Im, QString Sec)
{
	Document xlsx(nameDir+ "/" + nameDoc);

	Format formatHcVc;                                                        ///Создание форматирования
	formatHcVc.setHorizontalAlignment(Format::AlignHCenter);                  ///Задаём горизонтальное форматирование
	formatHcVc.setVerticalAlignment(Format::AlignVCenter);                    ///Задаём вертикальное форматирование
	formatHcVc.setFontColor(Qt::black);
	formatHcVc.setFontBold(true);
	formatHcVc.setFontSize(11);
	formatHcVc.setBorderStyle(Format::BorderThin);

	CellRange r1(IdRow,1,IdRow,1);
	xlsx.write(r1.firstRow(), r1.firstColumn(), link.Id, formatHcVc);
	xlsx.mergeCells(r1, formatHcVc);

	CellRange r2(IdRow,2,IdRow,2);
	xlsx.write(r2.firstRow(), r2.firstColumn(), link.NameLink, formatHcVc);
	xlsx.mergeCells(r2, formatHcVc);

	CellRange r3(IdRow,3,IdRow,3);
	xlsx.write(r3.firstRow(), r3.firstColumn(), link.ModeCheck, formatHcVc);
	xlsx.mergeCells(r3, formatHcVc);

	CellRange r4(IdRow,4,IdRow,4);
	xlsx.write(r4.firstRow(), r4.firstColumn(), link.MinValue, formatHcVc);
	xlsx.mergeCells(r4, formatHcVc);

	CellRange r5(IdRow,5,IdRow,5);
	xlsx.write(r5.firstRow(), r5.firstColumn(), link.MaxValue, formatHcVc);
	xlsx.mergeCells(r5, formatHcVc);

	CellRange r6(IdRow,6,IdRow,6);
	xlsx.write(r6.firstRow(), r6.firstColumn(), link.SecondValue, formatHcVc);
	xlsx.mergeCells(r6, formatHcVc);

	CellRange r7(IdRow,7,IdRow,7);
	xlsx.write(r7.firstRow(), r7.firstColumn(), Im, formatHcVc);
	xlsx.mergeCells(r7, formatHcVc);

	CellRange r8(IdRow,8,IdRow,8);
	xlsx.write(r8.firstRow(), r8.firstColumn(), Sec, formatHcVc);
	xlsx.mergeCells(r8, formatHcVc);

	xlsx.save();
	IdRow++;
}
//--------------------------------------------------------
void Proc::checkNameDoc()
{

	QFile file;

	file.setFileName(nameDir+ "/" + nameDoc);

	if(file.exists())
	{
		if(idNewDoc > 0)
		{

			nameDoc.remove(8, countRemove);
			nameDoc.insert(8, "_"+ QString::number(idNewDoc));
		}
		else
		{

			nameDoc.insert(8, "_"+ QString::number(idNewDoc));
		}

		countRemove = QString::number(idNewDoc).count()+1;
		idNewDoc++;
		checkNameDoc();
	}
	else
	{
		return;
	}


}
//--------------------------------------------------------
