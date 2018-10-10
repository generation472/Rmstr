//----------------------------------------------------------------------------
#include "rm_str.h"
#include "ui_rm_str.h"
#include <QMessageBox>
#include <QDebug>
//----------------------------------------------------------------------------
RM_STR::RM_STR(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::RM_STR)
{
	ui->setupUi(this);


	setWindowTitle("RM_STR v.1.4.8");

	movieLabel = new QLabel(this);
	movie = new QMovie(":/img/Load.gif");
	movieLabel->setMovie(movie);
	movieLabel->hide();
	movie->start();


	qRegisterMetaType<TSTRPCONNECTION>("TSTRPCONNECTION");
	qRegisterMetaType<TSTRPCONNECTION>("TSTRPCONNECTION");
	qRegisterMetaType<TSTATUSDEVICE>("TSTATUSDEVICE");


	ui->Date->display(QDate::currentDate().toString("dd.MM.yy"));
	deviceSTR = new DeviceSTR();
	shedulerSTR = new ShedulerSTR(this);
	indicatorBD = new Indicator();
	labelStatusDB = new QLabel();

	deviceSTR->moveToThread(&thread);
	thread.start(QThread::TimeCriticalPriority);




	//-------------------- Connect WidgetDatabase-------------------------
	connect(ui->wDB, SIGNAL(signal_changeDB(QString)), shedulerSTR, SLOT(slot_changeSettingsPathDB(QString)));
	connect(shedulerSTR, SIGNAL(signal_setPathDB(QString)), ui->wDB, SLOT(slot_setPathDB(QString)), Qt::DirectConnection);
	connect(shedulerSTR, SIGNAL(signal_connectedToDB(bool)), indicatorBD, SLOT(slot_changeStatus(bool)));
	connect(ui->wDB, SIGNAL(signal_getTable(QString)), shedulerSTR, SLOT(slot_getTable(QString)), Qt::DirectConnection);
	connect(shedulerSTR, SIGNAL(signal_sentTable(QVector<TSTRLINKPOINT>)), ui->wDB, SLOT(slot_sentTable(QVector<TSTRLINKPOINT>)));
	connect(shedulerSTR, SIGNAL(signal_sentTable(QVector<TSTRPCONNECTION>)), ui->wDB, SLOT(slot_sentTable(QVector<TSTRPCONNECTION>)));
	connect(ui->wDB, SIGNAL(signal_SaveLink(TSTRLINKPOINT)), shedulerSTR, SLOT(slot_SaveLink(TSTRLINKPOINT)));
	connect(shedulerSTR, SIGNAL(signal_saveOK()), ui->wDB, SLOT(slot_saveOK()));
	connect(ui->wDB, SIGNAL(signal_SavePoint(TSTRPCONNECTION)), shedulerSTR, SLOT(slot_SavePoint(TSTRPCONNECTION)));
	connect(ui->wDB, SIGNAL(signal_DeleteRecord(int,QString)), shedulerSTR, SLOT(slot_DeleteRecord(int,QString)));
	connect(shedulerSTR, SIGNAL(signal_ErrorDB(QString)), ui->wDB, SLOT(slot_ErrorDB(QString)));
	connect(ui->wDB, SIGNAL(signal_addPoint(TSTRPCONNECTION)), shedulerSTR, SLOT(slot_addPoint(TSTRPCONNECTION)), Qt::DirectConnection);
	connect(ui->wDB, SIGNAL(signal_addLink(TSTRLINKPOINT)), shedulerSTR, SLOT(slot_addLink(TSTRLINKPOINT)), Qt::DirectConnection);
	connect(ui->wDB, SIGNAL(signal_getTable(QString,QString,QString)), shedulerSTR, SLOT(slot_getTable(QString,QString,QString)));
	//-------------------- Connect WidgetManualControl---------------------------------
	connect(ui->wManControl, SIGNAL(signal_getTableLink()), shedulerSTR, SLOT(slot_getTableLink()));
	connect(shedulerSTR, SIGNAL(signal_sentTableLink(QVector<TSTRLINKPOINT>)), ui->wManControl, SLOT(slot_sentTable(QVector<TSTRLINKPOINT>)));
	connect(ui->wManControl, SIGNAL(signal_checkLink(QString,QString)), shedulerSTR, SLOT(slot_checkLink(QString,QString)));
	connect(shedulerSTR, SIGNAL(signal_getValueFromPointM(TSTRPCONNECTION,TSTRPCONNECTION,QString)), deviceSTR, SLOT(slot_getValueFromPointM(TSTRPCONNECTION,TSTRPCONNECTION,QString)),Qt::QueuedConnection);
	connect(deviceSTR, SIGNAL(signal_getValueFromPointM(double,double)), shedulerSTR, SLOT(slot_getValueFromPointM(double,double)));
	connect(shedulerSTR, SIGNAL(signal_sentResult(double,double,bool)), ui->wManControl, SLOT(slot_sentResult(double,double,bool)));
	connect(ui->wManControl, SIGNAL(signal_getTableLink(QString)), shedulerSTR, SLOT(slot_getTableLink(QString)));
	connect(ui->wManControl, SIGNAL(signal_checkDeviceM()), shedulerSTR, SIGNAL(signal_checkDeviceM()));
	//--------------------- Connect WidgetAutoControl------------------------------------
	connect(ui->pAutoControl, SIGNAL(signal_setStatusAutoControl(TSTATUSAUTOCHECK)), shedulerSTR, SLOT(slot_setStatusAutoControl(TSTATUSAUTOCHECK)));
	connect(shedulerSTR, SIGNAL(signal_getValueFromPointA(TSTRPCONNECTION,TSTRPCONNECTION,QString)), deviceSTR, SLOT(slot_getValueFromPointA(TSTRPCONNECTION,TSTRPCONNECTION,QString)));
	connect(deviceSTR, SIGNAL(signal_getValueFromPointA(double,double)), shedulerSTR, SLOT(slot_getValueFromPointA(double,double)));
	connect(shedulerSTR, SIGNAL(signal_sentResult(TSTRLINKPOINT,double,double,bool)), ui->pAutoControl, SLOT(slot_sentResult(TSTRLINKPOINT,double,double,bool)));
	connect(shedulerSTR, SIGNAL(signal_statusAutoCheck(TSTATUSAUTOCHECK)), ui->pAutoControl, SLOT(slot_statusAutoCheck(TSTATUSAUTOCHECK)));
	connect(shedulerSTR, SIGNAL(signal_setRangeProgressBar(int)), ui->pAutoControl, SLOT(slot_setRangeProgressBar(int)));

	connect(ui->pAutoControl, SIGNAL(signal_checkDeviceA()), shedulerSTR, SIGNAL(signal_checkDeviceA()));
	connect(shedulerSTR, SIGNAL(signal_checkDeviceA()), deviceSTR, SLOT(slot_checkDeviceA()));
	connect(deviceSTR, SIGNAL(signal_statusDeviceA(TSTATUSDEVICE)), shedulerSTR, SIGNAL(signal_statusDeviceA(TSTATUSDEVICE)));
	connect(shedulerSTR, SIGNAL(signal_statusDeviceA(TSTATUSDEVICE)), ui->pAutoControl, SLOT(slot_statusDeviceA(TSTATUSDEVICE)));


	//-------------------- Connect OtherConnects---------------------------------
	connect(ui->b_rlc, SIGNAL(signal_clicked(bool)), this, SLOT(slot_switchRLC(bool)));
	connect(ui->b_sub, SIGNAL(signal_clicked(bool)), this, SLOT(slot_switchSPI(bool)));
	connect(this, SIGNAL(signal_creatQSerialPort()), deviceSTR, SLOT(slot_creatSerialPort()));
	connect(this, SIGNAL(signal_switchRLC(bool)), deviceSTR, SLOT(slot_switchRLC(bool)));
	connect(deviceSTR, SIGNAL(signal_enableRLC(bool)), this, SLOT(slot_enableRLC(bool)));
	connect(this, SIGNAL(signal_changeTechNumber(QString)), shedulerSTR, SLOT(slot_changeTechNumber(QString)));



	dSettings.setWindowTitle("Настройки");
	connect(&dSettings, SIGNAL(signal_getSubList()), deviceSTR, SLOT(slot_getSubList()), Qt::QueuedConnection);
	connect(deviceSTR, SIGNAL(signal_setSubList(QStringList)), &dSettings, SLOT(slot_setSubList(QStringList)), Qt::QueuedConnection);
	connect(&dSettings, SIGNAL(signal_SetSettings(QString,QString,int)), deviceSTR, SLOT(slot_SetSettings(QString,QString,int)));
	connect(&dSettings, SIGNAL(signal_SetSettings(QString,QString,int)), shedulerSTR, SLOT(slot_SetSettings(QString,QString,int)));
	connect(shedulerSTR, SIGNAL(signal_SetSettings(QString,QString,int)), deviceSTR, SLOT(slot_SetSettings(QString,QString,int)));
	connect(shedulerSTR, SIGNAL(signal_SetSettings(QString,QString,int)), &dSettings, SLOT(slot_SetSettings(QString,QString,int)));
	connect(shedulerSTR, SIGNAL(signal_SetSettings(bool,bool)), &dSettings, SLOT(slot_SetSettings(bool,bool)));
	connect(&dSettings, SIGNAL(signal_SetSettings(bool,bool)), shedulerSTR, SLOT(slot_SetSettings(bool,bool)));
	connect(shedulerSTR, SIGNAL(signal_checkDeviceM()), deviceSTR, SLOT(slot_checkDeviceM()));

	connect(shedulerSTR, SIGNAL(signal_setSettingsTable(bool)), ui->pProtocol, SLOT(slot_setSettingsTable(bool)));
	connect(deviceSTR, SIGNAL(signal_statusDeviceM(TSTATUSDEVICE)), shedulerSTR, SIGNAL(signal_statusDeviceM(TSTATUSDEVICE)));
	connect(shedulerSTR, SIGNAL(signal_statusDeviceM(TSTATUSDEVICE)), ui->wManControl, SLOT(slot_statusDeviceM(TSTATUSDEVICE)));

	connect(shedulerSTR, SIGNAL(signal_alert()), this, SLOT(slot_alert()));
	emit signal_creatQSerialPort();

	indicatorBD->setMaximumSize(30,30);
	indicatorBD->setMinimumSize(30,30);
	labelStatusDB->setText("База данных:");
	ui->statusBar->addPermanentWidget(labelStatusDB);
	ui->statusBar->addPermanentWidget(indicatorBD);
	shedulerSTR->readSettingsSTR();



	setStyleRm_STR();


}
//----------------------------------------------------------------------------
RM_STR::~RM_STR()
{

	if(thread.isRunning())
	{
		thread.terminate();
		thread.wait();
	}

	delete deviceSTR;
	delete ui;
}
//----------------------------------------------------------------------------
void RM_STR::setStyleRm_STR()
{

	ui->Date->setStyleSheet("background-color: black;"
													"border-width: 4px;"
													"border-style: solid;"
													"border-color: rgb(135,206,235);"
													"border-radius: 9px;"
													"color: rgb(0,255,0);"
													);


	ui->lineTechNumber->setStyleSheet("background-color: black;"
																		"border-width: 4px;"
																		"border-style: solid;"
																		"border-color: rgb(135,206,235);"
																		"border-radius: 9px;"
																		"color: rgb(0,255,0);");


	/**



	TimeLCD->setStyleSheet("border-color: black;"
													"color: rgb(0,255,0);"
													"border-width: 0px;"
													);
"background-color: black;"
													 "border-width: 4px;"
													 "border-style: solid;"
													 "border-color: white;"
													 "border-radius: 9px;"
**/

}
//----------------------------------------------------------------------------
void RM_STR::slot_enableRLC(bool f)
{
	ui->b_rlc->setSwitch(f);
	movieLabel->hide();
}
//----------------------------------------------------------------------------
void RM_STR::on_manualCheck_triggered()
{
	if(!shedulerSTR->isAutocontrol())
		ui->stackedWidget->setCurrentIndex(0);
}
//----------------------------------------------------------------------------
void RM_STR::on_autoCheck_triggered()
{
	ui->stackedWidget->setCurrentIndex(1);
}
//----------------------------------------------------------------------------
void RM_STR::on_protocolCheck_triggered()
{
	if(!shedulerSTR->isAutocontrol())
		ui->stackedWidget->setCurrentIndex(2);
}
//----------------------------------------------------------------------------
void RM_STR::on_manageDB_triggered()
{
	if(!shedulerSTR->isAutocontrol())
		ui->stackedWidget->setCurrentIndex(3);
}
//----------------------------------------------------------------------------
void RM_STR::on_action_triggered()
{
	QMessageBox::about(this, tr("О программе RM_STR"),
						 tr("<h2>RM_STR version v.1.4.8 </h2>"
						 "<p>Copyright © ТОПАЗ 2018"
						 "<p>RM_STR организует управление пульта RM_STR:<br>"
						 "-Проверка электромонтажа в ручном режиме<br>"
						 "-Проверка электромонтажа в автоматическом режиме<br>"
						 "-Составление протокола по оканчанию проверки в автоматическом режиме<br>"
						 "-Просмотр протокола"
							 ));
}
//----------------------------------------------------------------------------
void RM_STR::on_action_2_triggered()
{
	if(!shedulerSTR->isAutocontrol())
	{
		slot_switchRLC(false);
		slot_switchSPI(false);
		deviceSTR->searchSub();
		dSettings.exec();
	}

}
//----------------------------------------------------------------------------
void RM_STR::slot_switchRLC(bool sw)
{

		emit signal_switchRLC(sw);
		movieLabel->show();

}
//----------------------------------------------------------------------------
void RM_STR::slot_switchSPI(bool sw)
{
	if(sw)	// Включить Sub20
	{
		if(deviceSTR->switchSPI(true))		// Если не включился
		{
			ui->b_sub->setSwitch(true);
		}
		else
		{
			ui->b_sub->setSwitch(false);	// Отключаю кнопку
		}

	}
	else
	{
		deviceSTR->switchSPI(false);
		ui->b_sub->setSwitch(false);
	}

}
//----------------------------------------------------------------------------
void RM_STR::on_exit_triggered()
{
	if(!shedulerSTR->isAutocontrol())
		close();
}
//----------------------------------------------------------------------------
void RM_STR::on_lineTechNumber_textEdited(const QString &arg1)
{
	emit signal_changeTechNumber(arg1);
}
//----------------------------------------------------------------------------
void RM_STR::slot_alert()
{
	QApplication::alert(this);
}
//----------------------------------------------------------------------------
void RM_STR::resizeEvent(QResizeEvent *event)
{
	Q_UNUSED(event);
	movieLabel->setGeometry(this->width()/2 - 100, this->height()/2 - 100, 200, 200);
}
//----------------------------------------------------------------------------
