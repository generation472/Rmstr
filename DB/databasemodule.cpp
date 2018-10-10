//------------------------------------------------------------------
#include "databasemodule.h"

#include "dialogaddpoint.h"

#include <QDebug>
#include <QFile>
#include <QMessageBox>
//------------------------------------------------------------------
DataBaseModule::DataBaseModule(QObject *parent) : QObject(parent)
{
	db = QSqlDatabase::addDatabase("QSQLITE");



	t_LinksPoint = "LinksPoints";
	t_PointConnection = "PointConnection";

}
//--------------------------------------------------------
DataBaseModule::~DataBaseModule()
{
	if(db.isOpen())
	{
		db.close();
	}
}
//--------------------------------------------------------
TSTRPCONNECTION DataBaseModule::getPoint(QString NamePoint, bool &ok)
{
    TSTRPCONNECTION Point;

	if(db.isOpen())
	{
		QSqlQuery query;
		QString strQuery;

		strQuery = "SELECT * FROM " + t_PointConnection + " WHERE NamePoint = '"+ NamePoint +"' ";

		if(query.exec(strQuery))
		{
			QSqlRecord rec = query.record();

			while(query.next())
			{
				Point.id = query.value(rec.indexOf("Id")).toInt();
				Point.NamePoint = query.value(rec.indexOf("NamePoint")).toString();
				Point.RG = query.value(rec.indexOf("RG")).toString();
				Point.CS = query.value(rec.indexOf("CS")).toString();
				Point.BusPlus = query.value(rec.indexOf("BusPlus")).toString();
				ok = true;
				return Point;
			}

		}

	}
	ok = false;
	return Point;
}
//--------------------------------------------------------
TSTRPCONNECTION DataBaseModule::getPoint(int ID, bool &ok)
{

	strPConnection Point;

	if(db.isOpen())
	{
		QSqlQuery query;
		QString strQuery;

		strQuery = "SELECT * FROM " + t_PointConnection + " WHERE Id = '"+ QString::number(ID) +"' ";

		if(query.exec(strQuery))
		{
			QSqlRecord rec = query.record();

			while(query.next())
			{
				Point.id = query.value(rec.indexOf("Id")).toInt();
				Point.NamePoint = query.value(rec.indexOf("NamePoint")).toString();
				Point.RG = query.value(rec.indexOf("RG")).toString();
				Point.CS = query.value(rec.indexOf("CS")).toString();
				Point.BusPlus = query.value(rec.indexOf("BusPlus")).toString();
				ok = true;
				return Point;
			}

		}

	}
	ok = false;
    return Point;
}
//--------------------------------------------------------
QVector<TSTRPCONNECTION> DataBaseModule::getVecPoint(bool &ok)
{
    QVector<TSTRPCONNECTION> vecPoint;
    TSTRPCONNECTION Point;

    if(db.isOpen())
    {
        QSqlQuery query;
        QString strQuery;

        strQuery = "SELECT * FROM " + t_PointConnection;

        if(query.exec(strQuery))
        {
            QSqlRecord rec = query.record();

            while(query.next())
            {
                Point.id = query.value(rec.indexOf("Id")).toInt();
                Point.NamePoint = query.value(rec.indexOf("NamePoint")).toString();
                Point.RG = query.value(rec.indexOf("RG")).toString();
                Point.CS = query.value(rec.indexOf("CS")).toString();
                Point.BusPlus = query.value(rec.indexOf("BusPlus")).toString();
                vecPoint.push_back(Point);
            }

            ok = true;
        }
        else
        {
            ok = false;

        }

    }
    else
    {
        ok = false;
    }



    return vecPoint;

}
//--------------------------------------------------------
bool DataBaseModule::insertPoint(TSTRPCONNECTION Point)
{

	if(db.isOpen())
	{

		QSqlQuery query;
		QString strQuery;

		strQuery = "INSERT INTO " + t_PointConnection + "(NamePoint, RG, CS, BusPlus)"
																										"VALUES('%1', '%2', '%3', '%4');";


		strQuery = strQuery.arg(Point.NamePoint)
											 .arg(Point.RG)
											 .arg(Point.CS)
											 .arg(Point.BusPlus);

		if(query.exec(strQuery))
			return true;
	}

	qWarning()<< "FALSE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	return false;
}
//--------------------------------------------------------
bool DataBaseModule::deletPoint(int ID)
{
	if(db.isOpen())
	{
        bool ok;
        QString namePoint = getPoint(ID, ok).NamePoint;


		QSqlQuery query;
		QString strQuery;

		strQuery = "DELETE FROM " + t_PointConnection + " WHERE Id = " + QString::number(ID);

		if(query.exec(strQuery))
		{
            if(ok)
            {
                deletLink(namePoint);
            }

			return true;
		}

	}
	return false;
}
//--------------------------------------------------------
bool DataBaseModule::deletPoint(QString NamePoint)
{

	if(db.isOpen())
	{       

		QSqlQuery query;
		QString strQuery;

		strQuery = "DELETE FROM " + t_PointConnection + " WHERE NamePoint = '" + NamePoint +"';";

		if(query.exec(strQuery))
		{
			deletLink(NamePoint);
			return true;
		}

	}
	return false;
}
//--------------------------------------------------------
bool DataBaseModule::updatePoint(TSTRPCONNECTION Point)
{
	if(db.isOpen())
	{
		bool ok;
		QString namePoint = getPoint(Point.id, ok).NamePoint;


		QSqlQuery query;
		QString strQuery;

		strQuery = "UPDATE " + t_PointConnection +
		" SET NamePoint ='%1', RG ='%2', CS ='%3', BusPlus ='%4' WHERE Id = " + QString::number(Point.id);

		strQuery = strQuery.arg(Point.NamePoint)
											 .arg(Point.RG)
											 .arg(Point.CS)
											 .arg(Point.BusPlus);


		if(query.exec(strQuery))
		{

            if(ok)
            {
                if(namePoint != Point.NamePoint)
                {
                    deletLink(namePoint);
                }
            }

			return true;
		}

	}

	return false;
}
//--------------------------------------------------------
QVector<TSTRPCONNECTION> DataBaseModule::getVecPoint(QString search, QString Column, bool &ok)
{

	QVector<TSTRPCONNECTION> vecPoint;
	TSTRPCONNECTION Point;

	if(db.isOpen())
	{
		QSqlQuery query;
		QString strQuery;

		strQuery = "SELECT * FROM " + t_PointConnection + " WHERE "+ Column +" LIKE '%"+ search +"%'";

		if(query.exec(strQuery))
		{
				QSqlRecord rec = query.record();

				while(query.next())
				{
						Point.id = query.value(rec.indexOf("Id")).toInt();
						Point.NamePoint = query.value(rec.indexOf("NamePoint")).toString();
						Point.RG = query.value(rec.indexOf("RG")).toString();
						Point.CS = query.value(rec.indexOf("CS")).toString();
						Point.BusPlus = query.value(rec.indexOf("BusPlus")).toString();
						vecPoint.push_back(Point);
				}

				ok = true;
		}
		else
		{
				ok = false;

		}

	}
	else
	{
		ok = false;
	}



	 return vecPoint;
}
//--------------------------------------------------------
TSTRLINKPOINT DataBaseModule::getLink(QString nameLink, bool &ok)
{
	strLinkPoint Link;

	if(db.isOpen())
	{
		QSqlQuery query;
		QString strQuery;

		strQuery = "SELECT * FROM " + t_LinksPoint + " WHERE NameLink = '"+ nameLink +"' ";

		if(query.exec(strQuery))
		{
			QSqlRecord rec = query.record();

			while(query.next())
			{
				Link.Id = query.value(rec.indexOf("Id")).toInt();
				Link.NameLink = query.value(rec.indexOf("NameLink")).toString();
				Link.IdPointMinus = query.value(rec.indexOf("IdPointMinus")).toInt();
				Link.IdPointPlus = query.value(rec.indexOf("IdPointPlus")).toInt();
				Link.ModeCheck = query.value(rec.indexOf("ModeCheck")).toString();
				Link.MinValue = query.value(rec.indexOf("MinValue")).toString();
				Link.MaxValue = query.value(rec.indexOf("MaxValue")).toString();
				Link.SecondValue = query.value(rec.indexOf("SecondValue")).toString();
				ok = true;
				return Link;
			}

			ok = true;
			return Link;
		}

	}
	ok = false;
	return Link;
}
//--------------------------------------------------------
bool DataBaseModule::insertLink(TSTRLINKPOINT Link)
{
	QString PointPluse;
	QString PointMinus;

	QStringList Points = Link.NameLink.split("-");
	if(Points.size() !=2)
		return false;

	PointPluse = Points[0];
	PointMinus = Points[1];

	bool ok1, ok2;
	strPConnection PointP = getPoint(PointPluse, ok1);
	strPConnection PointM = getPoint(PointMinus, ok2);


	if(ok1 != true || ok2 != true)
			return false;

	Link.IdPointPlus = PointP.id;
	Link.IdPointMinus = PointM.id;


	bool ok;
	QVector<TSTRLINKPOINT> VecLinks = getVecLinks(Link.NameLink, ok);
	if(ok)
	{
		for(TSTRLINKPOINT Slink: VecLinks)
		{
			if(Link.NameLink == Slink.NameLink && Link.ModeCheck == Slink.ModeCheck)
			{
				return false;
			}
		}
	}



	if(db.isOpen())
	{
		QSqlQuery query;
		QString strQuery;

		strQuery = "INSERT INTO " + t_LinksPoint + "(NameLink, IdPointPlus, IdPointMinus, ModeCheck, MinValue, MaxValue, SecondValue)"
																								"VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7');";

		strQuery = strQuery.arg(Link.NameLink)
											 .arg(Link.IdPointPlus)
											 .arg(Link.IdPointMinus)
											 .arg(Link.ModeCheck)
											 .arg(Link.MinValue)
											 .arg(Link.MaxValue)
											 .arg(Link.SecondValue);

		if(query.exec(strQuery))
			return true;

	}

	return false;

}
//--------------------------------------------------------
bool DataBaseModule::deletLink(QString nameLink)
{
	if(db.isOpen())
	{
		QSqlQuery query;
		QString strQuery;

		strQuery = "DELETE FROM " + t_LinksPoint + " WHERE NameLink LIKE '%" + nameLink +"%';";

		if(query.exec(strQuery))
		{
			return true;
		}
	}
	return false;

}
//--------------------------------------------------------
bool DataBaseModule::deletLink(int id)
{

    if(db.isOpen())
    {
        QSqlQuery query;
        QString strQuery;

        strQuery = "DELETE FROM " + t_LinksPoint + " WHERE Id = '"+QString::number(id) +"';";

        if(query.exec(strQuery))
        {
            return true;
        }
    }
    return false;
}
//--------------------------------------------------------
bool DataBaseModule::updateLink(TSTRLINKPOINT Link)
{
	if(db.isOpen())
	{

        //----------------Проверяем есть ли точки для этой связи ------------------------------
        QString PointPluse;
        QString PointMinus;

        QStringList Points = Link.NameLink.split("-");
        if(Points.size() !=2)
            return false;

        PointPluse = Points[0];
        PointMinus = Points[1];

        bool ok1, ok2;
        strPConnection PointP = getPoint(PointPluse, ok1);
        strPConnection PointM = getPoint(PointMinus, ok2);


				if(ok1 != true || ok2 != true)
							return false;

        Link.IdPointPlus = PointP.id;
        Link.IdPointMinus = PointM.id;


        //------------------Обновляем ----------------------------

		QSqlQuery query;
		QString strQuery;

		strQuery = "UPDATE " + t_LinksPoint +
        " SET NameLink ='%1', IdPointPlus ='%2', IdPointMinus ='%3', ModeCheck ='%4', MinValue ='%5', MaxValue ='%6', SecondValue ='%7' WHERE Id = '"+ QString::number(Link.Id) +"'; ";


        strQuery = strQuery.arg(Link.NameLink)
                           .arg(Link.IdPointPlus)
                           .arg(Link.IdPointMinus)
                           .arg(Link.ModeCheck)
                           .arg(Link.MinValue)
                           .arg(Link.MaxValue)
                           .arg(Link.SecondValue);


		if(query.exec(strQuery))
		{
			return true;
		}


	}

	return false;
}
//--------------------------------------------------------
QVector<TSTRLINKPOINT> DataBaseModule::getVecLinks(bool &ok)
{
    QVector<TSTRLINKPOINT> vecLinks;
	strLinkPoint Link;

	if(db.isOpen())
	{
		QSqlQuery query;
		QString strQuery;
		QSqlRecord rec;

		strQuery = "SELECT * FROM " + t_LinksPoint;

		if(query.exec(strQuery))
		{
			rec = query.record();
			while (query.next())
			{
				Link.Id = query.value(rec.indexOf("Id")).toInt();
				Link.NameLink = query.value(rec.indexOf("NameLink")).toString();
				Link.IdPointMinus = query.value(rec.indexOf("IdPointMinus")).toInt();
				Link.IdPointPlus = query.value(rec.indexOf("IdPointPlus")).toInt();
				Link.ModeCheck = query.value(rec.indexOf("ModeCheck")).toString();
				Link.MinValue = query.value(rec.indexOf("MinValue")).toString();
				Link.MaxValue = query.value(rec.indexOf("MaxValue")).toString();
				Link.SecondValue = query.value(rec.indexOf("SecondValue")).toString();
				vecLinks.push_back(Link);
			}

            ok = true;
		}
        else
        {
            ok = false;
        }

	}
    else
    {
        ok = false;
    }




	return vecLinks;
}
//--------------------------------------------------------
QVector<TSTRLINKPOINT> DataBaseModule::getVecLinks(QString nameLink, bool &ok)
{
    QVector<TSTRLINKPOINT> vecLinks;
    TSTRLINKPOINT Link;

	if(db.isOpen())
	{
		QSqlQuery query;
		QString strQuery;
		QSqlRecord rec;

		strQuery = "SELECT * FROM "+ t_LinksPoint +" WHERE NameLink LIKE '%"+ nameLink +"%'";



		if(query.exec(strQuery))
		{
			rec = query.record();
			while (query.next())
			{
				Link.Id = query.value(rec.indexOf("Id")).toInt();
				Link.NameLink = query.value(rec.indexOf("NameLink")).toString();
				Link.IdPointMinus = query.value(rec.indexOf("IdPointMinus")).toInt();
				Link.IdPointPlus = query.value(rec.indexOf("IdPointPlus")).toInt();
				Link.ModeCheck = query.value(rec.indexOf("ModeCheck")).toString();
				Link.MinValue = query.value(rec.indexOf("MinValue")).toString();
				Link.MaxValue = query.value(rec.indexOf("MaxValue")).toString();
				Link.SecondValue = query.value(rec.indexOf("SecondValue")).toString();
				vecLinks.push_back(Link);
			}

            ok = true;
		}
		else
		{
				ok = false;
		}

	}
    else
    {
        ok = false;
    }



	return vecLinks;
}
//--------------------------------------------------------
QVector<TSTRLINKPOINT> DataBaseModule::getVecLinks(QString search, QString Column, bool &ok)
{
	QVector<TSTRLINKPOINT> vecLinks;
	TSTRLINKPOINT Link;


	if(db.isOpen())
	{

		QSqlQuery query;
		QString strQuery;
		QSqlRecord rec;

		strQuery = "SELECT * FROM "+ t_LinksPoint +" WHERE "+ Column +" LIKE '%"+ search +"%'";

		if(query.exec(strQuery))
		{
			rec = query.record();
			while (query.next())
			{
				Link.Id = query.value(rec.indexOf("Id")).toInt();
				Link.NameLink = query.value(rec.indexOf("NameLink")).toString();
				Link.IdPointMinus = query.value(rec.indexOf("IdPointMinus")).toInt();
				Link.IdPointPlus = query.value(rec.indexOf("IdPointPlus")).toInt();
				Link.ModeCheck = query.value(rec.indexOf("ModeCheck")).toString();
				Link.MinValue = query.value(rec.indexOf("MinValue")).toString();
				Link.MaxValue = query.value(rec.indexOf("MaxValue")).toString();
				Link.SecondValue = query.value(rec.indexOf("SecondValue")).toString();
				vecLinks.push_back(Link);
			}

						ok = true;
		}
		else
		{
				ok = false;
		}


	}
	else
	{
		ok = false;
	}


	return vecLinks;
}
//--------------------------------------------------------
bool DataBaseModule::connectDB(QString nameDB)
{

	if(db.isOpen())
	{
		db.close();
	}


	QFile file(nameDB);

	if(file.exists())
	{
			db.setDatabaseName(nameDB);

			if(db.open())
			{


				/*
				//FIXME УДАЛИТЬ

				//Быстрое добавление точек
				TSTRPCONNECTION point;
				point.BusPlus = "0000000000000000";
				while(true)
				{
					dialogAddPoint *dp = new dialogAddPoint();
					dp->point = point;
					dp->exec();

					qWarning()<< dp->point.NamePoint;
					insertPoint(dp->point);
					point = dp->point;
					delete dp;
				}
			*/

			//	updateDataBase();
			//	resetID();
			//	resetPointid();
			//	updateIDPointLink();

				return true;
			}
			else
			{
				QMessageBox mb;
				mb.setWindowTitle("Ошибка БД");
				mb.setText(db.lastError().text());
				mb.exec();
			}

	}
	else
	{
		QMessageBox mb;
		mb.setText("Не найден файл БД");
		mb.exec();
	}


	return false;
}
//--------------------------------------------------------
void DataBaseModule::updateDataBase()
{

	if(db.isOpen())
	{

		//========================================================
		QSqlQuery query;
		QString strQuery;

		strQuery = "UPDATE " + t_PointConnection + " SET RG = '80' WHERE RG = '07';";

		if(query.exec(strQuery))
		{
			qWarning()<< "Execute ok";
		}
		else
		{
			qWarning()<< query.lastError().text();
		}
		//========================================================
		strQuery = "UPDATE " + t_PointConnection + " SET RG = '40' WHERE RG = '06';";

		if(query.exec(strQuery))
		{
			qWarning()<< "Execute ok";
		}
		else
		{
			qWarning()<< query.lastError().text();
		}
		//========================================================
		strQuery = "UPDATE " + t_PointConnection + " SET RG = '20' WHERE RG = '05';";

		if(query.exec(strQuery))
		{
			qWarning()<< "Execute ok";
		}
		else
		{
			qWarning()<< query.lastError().text();
		}
		//========================================================
		strQuery = "UPDATE " + t_PointConnection + " SET RG = '10' WHERE RG = '04';";

		if(query.exec(strQuery))
		{
			qWarning()<< "Execute ok";
		}
		else
		{
			qWarning()<< query.lastError().text();
		}
		//========================================================
		strQuery = "UPDATE " + t_PointConnection + " SET RG = '08' WHERE RG = '03';";

		if(query.exec(strQuery))
		{
			qWarning()<< "Execute ok";
		}
		else
		{
			qWarning()<< query.lastError().text();
		}
		//========================================================
		strQuery = "UPDATE " + t_PointConnection + " SET RG = '04' WHERE RG = '02';";

		if(query.exec(strQuery))
		{
			qWarning()<< "Execute ok";
		}
		else
		{
			qWarning()<< query.lastError().text();
		}
		//========================================================
		strQuery = "UPDATE " + t_PointConnection + " SET RG = '02' WHERE RG = '01';";

		if(query.exec(strQuery))
		{
			qWarning()<< "Execute ok";
		}
		else
		{
			qWarning()<< query.lastError().text();
		}
		//========================================================
		strQuery = "UPDATE " + t_PointConnection + " SET RG = '01' WHERE RG = '00';";

		if(query.exec(strQuery))
		{
			qWarning()<< "Execute ok";
		}
		else
		{
			qWarning()<< query.lastError().text();
		}
		//========================================================
	}


}
//--------------------------------------------------------
void DataBaseModule::resetID()
{

	QVector<TSTRLINKPOINT> vecLinks;
	TSTRLINKPOINT Link;


	if(db.isOpen())
	{

		QSqlQuery query;
		QString strQuery;
		QSqlRecord rec;

		strQuery = "SELECT * FROM "+ t_LinksPoint;

		if(query.exec(strQuery))
		{
			rec = query.record();
			while (query.next())
			{
				Link.Id = query.value(rec.indexOf("Id")).toInt();
				Link.NameLink = query.value(rec.indexOf("NameLink")).toString();
				Link.IdPointMinus = query.value(rec.indexOf("IdPointMinus")).toInt();
				Link.IdPointPlus = query.value(rec.indexOf("IdPointPlus")).toInt();
				Link.ModeCheck = query.value(rec.indexOf("ModeCheck")).toString();
				Link.MinValue = query.value(rec.indexOf("MinValue")).toString();
				Link.MaxValue = query.value(rec.indexOf("MaxValue")).toString();
				Link.SecondValue = query.value(rec.indexOf("SecondValue")).toString();
				vecLinks.push_back(Link);
			}
		}


		int autoincriment = 1;
		for(TSTRLINKPOINT link : vecLinks)
		{

			QSqlQuery query;
			QString strQuery;

			strQuery = "UPDATE " + t_LinksPoint +
					" SET Id = '%1', NameLink ='%2', IdPointPlus ='%3', IdPointMinus ='%4', ModeCheck ='%5', MinValue ='%6', MaxValue ='%7', SecondValue ='%8' WHERE Id = '"+ QString::number(link.Id) +"'; ";


					strQuery = strQuery.arg(autoincriment)
														 .arg(link.NameLink)
														 .arg(link.IdPointPlus)
														 .arg(link.IdPointMinus)
														 .arg(link.ModeCheck)
														 .arg(link.MinValue)
														 .arg(link.MaxValue)
														 .arg(link.SecondValue);

				if(query.exec(strQuery))
				{
					autoincriment++;
				}
				else
				{
					return;
				}

		}

	}

}
//--------------------------------------------------------
void DataBaseModule::resetPointid()
{
	QVector<TSTRPCONNECTION> vecPoints;
	TSTRPCONNECTION Point;


	if(db.isOpen())
	{

		QSqlQuery query;
		QString strQuery;
		QSqlRecord rec;

		strQuery = "SELECT * FROM "+ t_PointConnection;

		if(query.exec(strQuery))
		{
			rec = query.record();
			while (query.next())
			{
				Point.id = query.value(rec.indexOf("Id")).toInt();
				Point.NamePoint = query.value(rec.indexOf("NamePoint")).toString();
				Point.RG = query.value(rec.indexOf("RG")).toString();
				Point.CS = query.value(rec.indexOf("CS")).toString();
				Point.BusPlus = query.value(rec.indexOf("BusPlus")).toString();
				vecPoints.push_back(Point);
			}
		}


		int autoincriment = 1;
		for(TSTRPCONNECTION point : vecPoints)
		{

			QSqlQuery query;
			QString strQuery;

			strQuery = "UPDATE " + t_PointConnection +
					" SET Id = '%1', NamePoint = '%2', RG = '%3', CS = '%4', BusPlus = '%5' WHERE Id = '"+ QString::number(point.id) +"';";


					strQuery = strQuery.arg(autoincriment)
														 .arg(point.NamePoint)
														 .arg(point.RG)
														 .arg(point.CS)
														 .arg(point.BusPlus);

				if(query.exec(strQuery))
				{
					autoincriment++;
				}
				else
				{
					return;
				}

		}

	}


}
//--------------------------------------------------------
void DataBaseModule::updateIDPointLink()
{

	QVector<TSTRLINKPOINT> vecLinks;
	TSTRLINKPOINT Link;


	if(db.isOpen())
	{

		QSqlQuery query;
		QString strQuery;
		QSqlRecord rec;

		strQuery = "SELECT * FROM "+ t_LinksPoint;

		if(query.exec(strQuery))
		{
			rec = query.record();
			while (query.next())
			{
				Link.Id = query.value(rec.indexOf("Id")).toInt();
				Link.NameLink = query.value(rec.indexOf("NameLink")).toString();
				Link.IdPointMinus = query.value(rec.indexOf("IdPointMinus")).toInt();
				Link.IdPointPlus = query.value(rec.indexOf("IdPointPlus")).toInt();
				Link.ModeCheck = query.value(rec.indexOf("ModeCheck")).toString();
				Link.MinValue = query.value(rec.indexOf("MinValue")).toString();
				Link.MaxValue = query.value(rec.indexOf("MaxValue")).toString();
				Link.SecondValue = query.value(rec.indexOf("SecondValue")).toString();
				vecLinks.push_back(Link);
			}
		}


		for(TSTRLINKPOINT link : vecLinks)
		{

			QString PointPlus;
			QString PointMinus;
			bool ok = true;

			PointPlus = link.NameLink.split("-")[0];
			PointMinus = link.NameLink.split("-")[1];

			TSTRPCONNECTION pPlus = getPoint(PointPlus, ok);


			if(!ok)
				{
					qWarning()<< "Цепь плюс " + link.NameLink;
					continue;
				}


			TSTRPCONNECTION pMinus = getPoint(PointMinus, ok);
			if(!ok)
				{
					qWarning()<< "Цепь минус " + link.NameLink;
					continue;
				}


			QSqlQuery query;
			QString strQuery;

			strQuery = "UPDATE " + t_LinksPoint +
					" SET Id = '%1', NameLink ='%2', IdPointPlus ='%3', IdPointMinus ='%4', ModeCheck ='%5', MinValue ='%6', MaxValue ='%7', SecondValue ='%8' WHERE Id = '"+ QString::number(link.Id) +"'; ";


					strQuery = strQuery.arg(link.Id)
														 .arg(link.NameLink)
														 .arg(pPlus.id)
														 .arg(pMinus.id)
														 .arg(link.ModeCheck)
														 .arg(link.MinValue)
														 .arg(link.MaxValue)
														 .arg(link.SecondValue);

				if(!query.exec(strQuery))
				{
					qWarning()<< link.NameLink ;
				}


		}
	}

}
//--------------------------------------------------------
