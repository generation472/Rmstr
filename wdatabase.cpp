//-----------------------------------------------------------
#include "wdatabase.h"
#include "ui_wdatabase.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
//-----------------------------------------------------------
wDatabase::wDatabase(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::wDatabase)
{
	ui->setupUi(this);

    rowSelected = -1;
    movieLabel = new QLabel(this);
    movie = new QMovie(":/img/Load.gif");
    movieLabel->setMovie(movie);
    movieLabel->hide();
    movie->start();

		prepareTable();

		ui->saveAllRecord->hide();
}
//-----------------------------------------------------------
wDatabase::~wDatabase()
{

    delete ui;
}
//-----------------------------------------------------------
void wDatabase::slot_ErrorDB(QString str)
{

    movieLabel->hide();
	 /* QMessageBox msg;
    msg.setText(str);
		msg.exec();*/
		Q_UNUSED(str);
}
//-----------------------------------------------------------
void wDatabase::on_changeBD_clicked()
{
	QString nameDB = QFileDialog::getOpenFileName(this, "Выбрать базу данных", QApplication::applicationDirPath(),tr("DataBase (*.db *.sqlite3 *.db3)"));

	if(nameDB.isEmpty())
		return;

	ui->l_DB->setText(nameDB);
	ui->l_DB->setStatusTip(nameDB);
	emit signal_changeDB(nameDB);

}
//-----------------------------------------------------------
void wDatabase::slot_setPathDB(QString path)
{
    ui->l_DB->setText(path);
    ui->l_DB->setStatusTip(path);
}
//-----------------------------------------------------------
void wDatabase::slot_sentTable(QVector<TSTRLINKPOINT> linksTable)
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
    movieLabel->hide();
}
//-----------------------------------------------------------
void wDatabase::slot_sentTable(QVector<TSTRPCONNECTION> pointTable)
{
     ui->tableWidget->clearContents();
     ui->tableWidget->setRowCount(0);

		rowSelected = -1;
    for(TSTRPCONNECTION point: pointTable)
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(point.id));

        Qt::ItemFlags eFlags = id->flags();
        eFlags &= ~Qt::ItemIsEditable;
        id->setFlags(eFlags);
        id->setFlags(Qt::ItemIsEditable);

        ui->tableWidget->setItem(row, 0, id);
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(point.NamePoint));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(point.RG));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(point.CS));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(point.BusPlus));
    }

    ui->tableWidget->resizeColumnsToContents();
		movieLabel->hide();
}
//-----------------------------------------------------------
void wDatabase::slot_saveOK()
{
	movieLabel->hide();
	QMessageBox msg;
	msg.setText("Запись успешно сохранена");
	msg.exec();
}
//-----------------------------------------------------------
void wDatabase::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    getTable();
}
//-----------------------------------------------------------
void wDatabase::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    movieLabel->setGeometry(this->width()/2 - 100, this->height()/2 - 100, 200, 200);
}
//-----------------------------------------------------------
void wDatabase::on_nameTable_currentIndexChanged(int index)
{
		Q_UNUSED(index);
		prepareTable();
    getTable();
    rowSelected = -1;
}
//-----------------------------------------------------------
void wDatabase::prepareTable()
{

  ui->tableWidget->clear();
  ui->tableWidget->setRowCount(0);
  ui->tableWidget->setColumnCount(0);
	ui->nameColumn->clear();

	if(ui->nameTable->currentText() == "Таблица цепей")
	{
		ui->tableWidget->setColumnCount(6);
		ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("№"));
		ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя цепи"));
		ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Режим проверки"));
		ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Мин. Значение"));
		ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Макс. Значение"));
		ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Второй параметр"));

		QStringList listColumn;
		listColumn << "Имя цепи" << "Режим проверки" << "Мин. Значение" << "Макс. Значение" << "Второй параметр";
		ui->nameColumn->addItems(listColumn);
	}
	else
	{
		ui->tableWidget->setColumnCount(5);
		ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("№"));
		ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя точки"));
		ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Регистр"));
		ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Чип селект"));
		ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Адрес точки"));

		QStringList listColumn;
		listColumn << "Имя точки" << "Регистр" << "Чип селект" << "Адрес точки";
		ui->nameColumn->addItems(listColumn);
	}


	ui->tableWidget->resizeColumnsToContents();
}
//-----------------------------------------------------------
void wDatabase::getTable()
{
    rowSelected = -1;
    if(ui->nameTable->currentText() == "Таблица цепей")
    {
       movieLabel->show();
       emit signal_getTable("LinksPoints");
    }
    else
    {
        movieLabel->show();
        emit signal_getTable("PointConnection");
    }
}
//-----------------------------------------------------------
void wDatabase::on_saveRecord_clicked()
{
    if(rowSelected != -1)
    {
        if(ui->nameTable->currentText() == "Таблица цепей")
        {
            TSTRLINKPOINT link;
            link.Id = ui->tableWidget->item(rowSelected, 0)->text().toInt();
            link.IdPointMinus = 0;
            link.IdPointPlus = 0;
            link.NameLink = ui->tableWidget->item(rowSelected, 1)->text();
            link.ModeCheck = ui->tableWidget->item(rowSelected, 2)->text();
            link.MinValue = ui->tableWidget->item(rowSelected, 3)->text();
            link.MaxValue = ui->tableWidget->item(rowSelected, 4)->text();
            link.SecondValue = ui->tableWidget->item(rowSelected, 5)->text();

            emit signal_SaveLink(link);
        }
        else
        {
            TSTRPCONNECTION point;
            point.id = ui->tableWidget->item(rowSelected, 0)->text().toInt();
            point.NamePoint = ui->tableWidget->item(rowSelected, 1)->text();
            point.RG = ui->tableWidget->item(rowSelected, 2)->text();
            point.CS = ui->tableWidget->item(rowSelected, 3)->text();
            point.BusPlus = ui->tableWidget->item(rowSelected, 4)->text();

            emit signal_SavePoint(point);

        }


    }
}
//-----------------------------------------------------------
void wDatabase::on_tableWidget_cellClicked(int row, int column)
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

}
//-----------------------------------------------------------
void wDatabase::on_deleteRecord_clicked()
{
    if(rowSelected != -1)
    {
        if(ui->nameTable->currentText() == "Таблица цепей")
        {
            emit signal_DeleteRecord(ui->tableWidget->item(rowSelected, 0)->text().toInt(), "LinksPoints");
        }
        else
        {
            emit signal_DeleteRecord(ui->tableWidget->item(rowSelected, 0)->text().toInt(), "PointConnection");
        }

        getTable();
    }

}
//-----------------------------------------------------------
void wDatabase::on_addRecord_clicked()
{

	if(ui->nameTable->currentText() == "Таблица цепей")
	{
		dialogAddLink addLink;
		addLink.setWindowTitle("Добавить цепь");
		connect(&addLink, SIGNAL(signal_addLink(TSTRLINKPOINT)), this, SLOT(slot_addLink(TSTRLINKPOINT)));
		addLink.exec();

	}
	else
	{
		dialogAddPoint addPoint;
		addPoint.setWindowTitle("Добавить точку");
		connect(&addPoint, SIGNAL(signal_addPoint(TSTRPCONNECTION)), this, SLOT(slot_addPoint(TSTRPCONNECTION)));
		addPoint.exec();
	}


}
//-----------------------------------------------------------
void wDatabase::slot_addPoint(TSTRPCONNECTION point)
{
	emit signal_addPoint(point);
	getTable();
}
//-----------------------------------------------------------
void wDatabase::slot_addLink(TSTRLINKPOINT link)
{
	emit signal_addLink(link);
	getTable();
}
//-----------------------------------------------------------
void wDatabase::on_groupBox_3_clicked(bool checked)
{
	 if(!checked)
	 {
			getTable();
	 }
	 else
	 {
		 on_lineSearch_textChanged(ui->lineSearch->text());
	 }

}
//-----------------------------------------------------------
void wDatabase::on_lineSearch_textChanged(const QString &arg1)
{
	QString nameTable, nameColumn;

	if(ui->nameTable->currentText() == "Таблица цепей")
	{
		nameTable = "LinksPoints";

		switch (ui->nameColumn->currentIndex())
		{
		case 0:
			nameColumn = "NameLink";
			break;
		case 1:
			nameColumn = "ModeCheck";
			break;
		case 2:
			nameColumn = "MinValue";
			break;
		case 3:
			nameColumn = "MaxValue";
			break;
		case 4:
			nameColumn = "SecondValue";
			break;
		default:
			break;
		}
	}
	else
	{
		nameTable = "PointConnection";

		switch (ui->nameColumn->currentIndex())
		{
		case 0:
			nameColumn = "NamePoint";
			break;
		case 1:
			nameColumn = "RG";
			break;
		case 2:
			nameColumn = "CS";
			break;
		case 3:
			nameColumn = "BusPlus";
			break;
		default:
			break;
		}
	}

	emit signal_getTable(nameTable, nameColumn, arg1);
}
//-----------------------------------------------------------
void wDatabase::on_creatNewBD_clicked()
{

	QString nameFile = QFileDialog::getSaveFileName(this, "Сохранить БД", "",  tr("DB (*.db)"));

	QFile newFile(nameFile);

	QFile file(ui->l_DB->text());

	if(file.open(QIODevice::ReadOnly))
	{
		if(newFile.open(QIODevice::WriteOnly))
		{

			newFile.write(file.readAll());
			newFile.close();
			file.close();

		}

	}



}
//-----------------------------------------------------------
void wDatabase::on_deletBD_clicked()
{

	emit signal_changeDB("");

	QFile file(ui->l_DB->text());

	if(file.exists())
	{
		if(file.remove())
		{
			prepareTable();
		}
		else
		{
			qWarning() <<  file.errorString();
		}

	}

	ui->l_DB->setStatusTip("");
	ui->l_DB->setText("");

}
//-----------------------------------------------------------
void wDatabase::on_tabWidget_currentChanged(int index)
{
		Q_UNUSED(index);
		getTable();
}
//-----------------------------------------------------------
