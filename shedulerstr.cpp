//---------------------------------------------------------------
#include "shedulerstr.h"
#include <QApplication>
#include <QDate>
#include <QMessageBox>

#include "rm_str.h"
//---------------------------------------------------------------
ShedulerSTR::ShedulerSTR(QObject *parent) : QObject(parent)
{
	s_pathDB = s_nameComPortRLC = s_nameSUB_20 = "";
	settingsSTR = new QSettings("QtSOFT","RM_STR");

	statusAutoCheck = S_STOP;
	techNumber = "0000000000";
	autoControl = false;
}
//---------------------------------------------------------------
ShedulerSTR::~ShedulerSTR()
{

}
//---------------------------------------------------------------
void ShedulerSTR::slot_changeSettingsPathDB(QString path)
{
    setSettingsPathDB(path);
    if(DB.connectDB(path))
    {
        emit signal_connectedToDB(true);
    }
    else
    {
        emit signal_connectedToDB(false);
    }
}
//---------------------------------------------------------------
void ShedulerSTR::slot_getTable(QString nameTable)
{

    if(nameTable == DB.t_LinksPoint)
    {
        bool ok;
        QVector<TSTRLINKPOINT> table = DB.getVecLinks(ok);
        if(ok)
        {
            emit signal_sentTable(table);
        }
        else
        {
						emit signal_ErrorDB("Ошибка запроса");
        }




    }

    if(nameTable == DB.t_PointConnection)
    {
        bool ok;
        QVector<TSTRPCONNECTION> table = DB.getVecPoint(ok);
        if(ok)
        {
            emit signal_sentTable(table);
        }
        else
        {
						emit signal_ErrorDB("Ошибка запроса");
        }

    }


}
//---------------------------------------------------------------
void ShedulerSTR::slot_SaveLink(TSTRLINKPOINT Link)
{
  if(!DB.updateLink(Link))
  {
    emit signal_ErrorDB("Ошибка сохранения в БД");
	}
	else
	{
		emit signal_saveOK();
	}


}
//---------------------------------------------------------------
void ShedulerSTR::slot_SavePoint(TSTRPCONNECTION Point)
{
    if(!DB.updatePoint(Point))
    {
      emit signal_ErrorDB("Ошибка сохранения в БД");
    }
		else
		{
			emit signal_saveOK();
		}
}
//---------------------------------------------------------------
void ShedulerSTR::slot_DeleteRecord(int id, QString nameTable)
{

    if(nameTable == DB.t_LinksPoint)
    {
        if(!DB.deletLink(id))
        {
           emit signal_ErrorDB("Ошибка выполнения запроса");
        }
    }
    else
    {
        if(!DB.deletPoint(id))
        {
           emit signal_ErrorDB("Ошибка выполнения запроса");
        }
    }


}
//---------------------------------------------------------------
void ShedulerSTR::slot_addPoint(TSTRPCONNECTION Point)
{
	if(!DB.insertPoint(Point))
	{
		emit signal_ErrorDB("Ошибка выполнения запроса");
	}
}
//---------------------------------------------------------------
void ShedulerSTR::slot_addLink(TSTRLINKPOINT link)
{
	if(!DB.insertLink(link))
	{
		emit signal_ErrorDB("Ошибка выполнения запроса");
	}
}
//---------------------------------------------------------------
void ShedulerSTR::slot_getTable(QString nameTable, QString nameColumn, QString searchText)
{
	bool ok;
	if(nameTable == DB.t_LinksPoint)
	{

		QVector<TSTRLINKPOINT> table = DB.getVecLinks(searchText ,nameColumn, ok);
		if(ok)
		{
				emit signal_sentTable(table);
		}
		else
		{
				emit signal_ErrorDB("Ошибка запроса");
		}

	}
	else
	{

		QVector<TSTRPCONNECTION> table = DB.getVecPoint(searchText ,nameColumn, ok);
		if(ok)
		{
				emit signal_sentTable(table);
		}
		else
		{
				emit signal_ErrorDB("Ошибка запроса");
		}

	}

}
//---------------------------------------------------------------
void ShedulerSTR::slot_SetSettings(QString numberSub, QString numberPort, int delay)
{
	setSettingsSUB_20(numberSub);
	setSettingsComPortRLC(numberPort);
	setSettingsDelay(QString::number(delay));

}
//---------------------------------------------------------------
void ShedulerSTR::slot_SetSettings(bool table, bool error)
{

	twoTableProc = table;
	settingsSTR->setValue("Settings/twoTableProc", twoTableProc);
	soundError = error;
	settingsSTR->setValue("Settings/soundError", soundError);

	emit signal_setSettingsTable(table);
}
//---------------------------------------------------------------
void ShedulerSTR::slot_getTableLink()
{

	bool ok;
	QVector<TSTRLINKPOINT> table = DB.getVecLinks(ok);
	if(ok)
	{
			emit signal_sentTableLink(table);
	}
	else
	{

	}

}
//---------------------------------------------------------------
void ShedulerSTR::slot_checkLink(QString plus, QString minus)
{
	bool ok1, ok2;

	TSTRPCONNECTION PointP = DB.getPoint(plus, ok1);
	TSTRPCONNECTION PointM = DB.getPoint(minus, ok2);

	if(ok1 == false || ok2 == false)
	{
		QMessageBox mb;
		QString badPoint;
		if(!ok1)
			badPoint += " "+plus;
		if(!ok2)
			badPoint += " "+plus;
		mb.setText("В базе данных отсутствуют настройки для точек:" + badPoint + ".");
		mb.exec();
		emit signal_sentResult(0 , 0, false);
		return;
	}


	TSTRLINKPOINT link = DB.getLink(plus + "-" + minus, ok1);

	if(!ok1)
		return;

	checklink = link;

	emit signal_getValueFromPointM(PointP, PointM, link.ModeCheck);

}
//---------------------------------------------------------------
void ShedulerSTR::slot_getTableLink(QString searchText)
{
	bool ok;
	QVector<TSTRLINKPOINT> table = DB.getVecLinks(searchText, "NameLink", ok);
	if(ok)
	{
			emit signal_sentTableLink(table);
	}
	else
	{

	}




}
//---------------------------------------------------------------
void ShedulerSTR::slot_getValueFromPointM(double Im, double Sec)
{

	bool check = true;
	if(checklink.ModeCheck == "C")
	{
		Im = Im * pow(10, 12);

		if(checklink.MinValue.toDouble() > Im  || checklink.MaxValue.toDouble() < Im)
		{
			check = false;
		}

	}
	else
	{

		if(checklink.MinValue.toDouble() > Im  ||  checklink.MaxValue.toDouble() < Im)
		{
			check = false;
		}

		if(Sec > checklink.SecondValue.toDouble())
		{
			check = false;
		}

	}


	if(!check)
	{
		if(soundError)
		{
			QApplication::beep();
			emit signal_alert();
		}
	}

	emit signal_sentResult(Im, Sec, check);

}
//---------------------------------------------------------------
void ShedulerSTR::slot_getValueFromPointA(double Im, double Sec)
{

	bool check = true;
	if(checklink.ModeCheck == "C")
	{
		// Режим C
		Im = Im * pow(10, 12); // перевод в пикофарад

		if(checklink.MinValue.toDouble() > Im  || checklink.MaxValue.toDouble() < Im)
		{
			check = false;
		}

	}
	else
	{
		// Режим R
		if(checklink.MinValue.toDouble() > Im  ||  checklink.MaxValue.toDouble() < Im)
		{
			check = false;
		}

		if(Sec > checklink.SecondValue.toDouble())
		{
			check = false;
		}

	}

	if(!check)
	{
		if(soundError)
		{
			QApplication::beep();
			emit signal_alert();
		}
	}



	QString s;
	proc.insertLink(checklink, s.sprintf("%.3f", Im), s.sprintf("%.3f", Sec));
	emit signal_sentResult(checklink, Im, Sec, check);

	slot_setStatusAutoControl(statusAutoCheck);

}
//---------------------------------------------------------------
void ShedulerSTR::slot_setStatusAutoControl(TSTATUSAUTOCHECK status)
{
	bool ok;

	if(status == S_BEGIN && statusAutoCheck == S_PAUSE)
	{
		status = S_CONTINUE;
		emit signal_statusAutoCheck(S_CONTINUE);
	}


	switch (status)
	{
	case S_BEGIN:

			linksTable4Check.clear();
			linksTable4Check = DB.getVecLinks(ok);


			if(ok)	// Проверка выполнение запроса
			{
				IdCheckLink = 0;
				if(linksTable4Check.count() > 0)	// Проверка на пустую таблицу
				{
					checklink = linksTable4Check[IdCheckLink];

					proc.newProc("Протокол_"+ techNumber + "_Дата_" + QDate::currentDate().toString("dd_MM_yy")   , techNumber);

					bool f_pointPlus;
					bool f_pointMinus;

					TSTRPCONNECTION PointP = DB.getPoint(checklink.IdPointPlus, f_pointPlus);
					TSTRPCONNECTION PointM = DB.getPoint(checklink.IdPointMinus, f_pointMinus);


					emit signal_setRangeProgressBar(linksTable4Check.count());
					emit signal_statusAutoCheck(S_BEGIN);

					statusAutoCheck = S_CONTINUE;
					autoControl = true;

					if(f_pointPlus && f_pointMinus)
					{
						emit signal_getValueFromPointA(PointP, PointM, checklink.ModeCheck);
					}
					else
					{
						QMessageBox mb;
						mb.setText("В базе данных отсутствуют настройки точек для цепи : " + checklink.NameLink + ".");
						mb.exec();

						slot_setStatusAutoControl(statusAutoCheck);
					}



				}
			}

		break;
	case S_PAUSE:

		statusAutoCheck = S_PAUSE;
		emit signal_statusAutoCheck(S_PAUSE);

		break;
	case S_CONTINUE:

		IdCheckLink++;

		if(linksTable4Check.count() > IdCheckLink)
		{
			checklink = linksTable4Check[IdCheckLink];


			bool f_pointPlus;
			bool f_pointMinus;
			TSTRPCONNECTION PointP = DB.getPoint(checklink.IdPointPlus, f_pointPlus);
			TSTRPCONNECTION PointM = DB.getPoint(checklink.IdPointMinus, f_pointMinus);


			statusAutoCheck = S_CONTINUE;

			if(f_pointPlus && f_pointMinus)
			{
				emit signal_getValueFromPointA(PointP, PointM, checklink.ModeCheck);
			}
			else
			{
				QMessageBox mb;
				mb.setText("В базе данных отсутствуют настройки точек для цепи : " + checklink.NameLink + ".");
				mb.exec();

				slot_setStatusAutoControl(statusAutoCheck);
			}

		}
		else
		{
			statusAutoCheck = S_STOP;
			slot_setStatusAutoControl(statusAutoCheck);
		}

		break;
	case S_STOP:
		if(!autoControl)break;

		autoControl = false;
		statusAutoCheck = S_STOP;
		emit signal_statusAutoCheck(S_STOP);

		break;
	default:
		break;
	}






}
//---------------------------------------------------------------
void ShedulerSTR::slot_changeTechNumber(QString number)
{
	techNumber = number;
}
//---------------------------------------------------------------
void ShedulerSTR::readSettingsSTR()
{
	s_pathDB = settingsSTR->value("Settings/pathDB").toString();
	s_nameComPortRLC = settingsSTR->value("Settings/nameComPortRLC").toString();
	s_nameSUB_20 = settingsSTR->value("Settings/nameSUB_20").toString();
	s_delay = settingsSTR->value("Settings/delay").toString();
	twoTableProc = settingsSTR->value("Settings/twoTableProc").toBool();
	soundError = settingsSTR->value("Settings/soundError").toBool();

    if(DB.connectDB(s_pathDB))
    {
        emit signal_setPathDB(s_pathDB);
        emit signal_connectedToDB(true);
    }
    else
    {
        emit signal_connectedToDB(false);
    }


		emit signal_setSettingsTable(twoTableProc);
		emit signal_SetSettings(twoTableProc, soundError);
		emit signal_SetSettings(s_nameSUB_20, s_nameComPortRLC, s_delay.toInt());
}
//---------------------------------------------------------------
bool ShedulerSTR::isAutocontrol()
{
	return autoControl;
}
//---------------------------------------------------------------
void ShedulerSTR::setSettingsPathDB(QString nameDB)
{
	settingsSTR->setValue("Settings/pathDB", nameDB);
}
//---------------------------------------------------------------
void ShedulerSTR::setSettingsSUB_20(QString nameSUB_20)
{
	settingsSTR->setValue("Settings/nameSUB_20", nameSUB_20);
}
//---------------------------------------------------------------
void ShedulerSTR::setSettingsDelay(QString delay)
{
	settingsSTR->setValue("Settings/delay", delay);
}
//---------------------------------------------------------------
void ShedulerSTR::setSettingsComPortRLC(QString nameComPortRLC)
{
	settingsSTR->setValue("Settings/nameComPortRLC", nameComPortRLC);
}
//---------------------------------------------------------------
