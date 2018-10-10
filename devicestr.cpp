//--------------------------------------------------
#include "devicestr.h"
#include "csys.h"


//--------------------------------------------------
DeviceSTR::DeviceSTR(QObject *parent) : QObject(parent)
{
	delayCheck = 0;

}
//--------------------------------------------------
DeviceSTR::~DeviceSTR()
{

}
//--------------------------------------------------
void DeviceSTR::searchSub()
{
	SPI.searchSub();
}
//--------------------------------------------------
bool DeviceSTR::switchRLC(bool sw)
{
	if(sw)
	{
		if(RLC.connectToRLC())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		RLC.disconnectFromRLC();
		return false;
	}

}
//--------------------------------------------------
bool DeviceSTR::switchSPI(bool sw)
{

	if(sw)
	{
		if(SPI.openSub())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{

		SPI.closeSub();
		return true;
	}

}
//--------------------------------------------------
void DeviceSTR::slot_switchRLC(bool sw)
{
		if(switchRLC(sw))
		{
			emit signal_enableRLC(true);
		}
		else
		{
			emit signal_enableRLC(false);
		}
}
//--------------------------------------------------
void DeviceSTR::slot_getSubList()
{
	emit signal_setSubList(SPI.getSubList());
}
//--------------------------------------------------
void DeviceSTR::slot_SetSettings(QString numberSub, QString numberPort, int ms)
{

	SPI.setNumberSub(numberSub);
	RLC.setNameComPort(numberPort);
	delayCheck = ms;
}
//--------------------------------------------------
void DeviceSTR::slot_getValueFromPointM(TSTRPCONNECTION PointP, TSTRPCONNECTION PointM, QString mode)
{
	connectPoint(PointP);	// Настрока точки плюс

	PointM.BusPlus = getValuePointMinus(PointM);
	connectPoint(PointM); // Настрока точки минус


	if(mode == "C")								// Выбор режима RLC
	{
			RLC.nullTimeoutWrite();
			RLC.controlRLC(M_C);
	}
	else
	{
			RLC.nullTimeoutWrite();
			RLC.controlRLC(M_R);
	}

	QThread::msleep(delayCheck);	// Задержка

	RLC.readPakage();							// Чтение пакета

	double Im = RLC.getImParam();
	double Sec = RLC.getSecParam();

	PointP.BusPlus = "0000000000000000";		// Обнуляем точки
	PointM.BusPlus = "0000000000000000";		// Обнуляем точки
	connectPoint(PointP);
	connectPoint(PointM);

	emit signal_getValueFromPointM(Im, Sec);

}
//--------------------------------------------------
void DeviceSTR::slot_getValueFromPointA(TSTRPCONNECTION PointP, TSTRPCONNECTION PointM, QString mode)
{
	connectPoint(PointP);	// Настрока точки плюс

	PointM.BusPlus = getValuePointMinus(PointM);
	connectPoint(PointM); // Настрока точки минус


	if(mode == "C")								// Выбор режима RLC
	{
			RLC.nullTimeoutWrite();
			RLC.controlRLC(M_C);
	}
	else
	{
			RLC.nullTimeoutWrite();
			RLC.controlRLC(M_R);
	}

	QThread::msleep(delayCheck);	// Задержка

	RLC.readPakage();							// Чтение пакета

	double Im = RLC.getImParam();
	double Sec = RLC.getSecParam();

	PointP.BusPlus = "0000000000000000";		// Обнуляем точки
	PointM.BusPlus = "0000000000000000";		// Обнуляем точки
	connectPoint(PointP);
	connectPoint(PointM);

	emit signal_getValueFromPointA(Im, Sec);

}
//--------------------------------------------------
void DeviceSTR::slot_creatSerialPort()
{
	RLC.newSerialPort();
}
//--------------------------------------------------
void DeviceSTR::slot_checkDeviceM()
{

	TSTATUSDEVICE  status = S_OK;

	bool ok = true;
	if(!SPI.isEnabledSub())
	{
		status = (TSTATUSDEVICE)((int)status |  (int)S_SUB20);
		ok = false;
	}

	if(!RLC.isEnable())
	{
		status = (TSTATUSDEVICE)((int)status |  (int)S_RLC);
		ok = false;
	}

	if(!ok)
	{
		status = (TSTATUSDEVICE)((int)status |  (int)S_N_OK);
	}

	emit signal_statusDeviceM(status);
}
//--------------------------------------------------
void DeviceSTR::slot_checkDeviceA()
{
	TSTATUSDEVICE  status = S_OK;

	bool ok = true;
	if(!SPI.isEnabledSub())
	{
		status = (TSTATUSDEVICE)((int)status |  (int)S_SUB20);
		ok = false;
	}

	if(!RLC.isEnable())
	{
		status = (TSTATUSDEVICE)((int)status |  (int)S_RLC);
		ok = false;
	}

	if(!ok)
	{
		status = (TSTATUSDEVICE)((int)status |  (int)S_N_OK);
	}

	emit signal_statusDeviceA(status);
}
//--------------------------------------------------
QString DeviceSTR::getValuePointMinus(TSTRPCONNECTION Point)
{
	QString valueMinus = "";

	int size = Point.BusPlus.size()/2;

	for(int i = 0; i < size; i++)
	{
		QString tmp = Point.BusPlus.left(2);
		if(tmp != "00")
		{

			tmp = tmp.sprintf("%2d", tmp.toInt()<<1);
			tmp = tmp.replace(" ", "0");
		}
		valueMinus += tmp;
		Point.BusPlus = Point.BusPlus.right(Point.BusPlus.size()-2);
	}


	return valueMinus;
}
//--------------------------------------------------
bool DeviceSTR::connectPoint(TSTRPCONNECTION Point)
{
	int SS = -1;

	//--1 Шаг - Настройка RG
	QByteArray ba = strTohex(Point.RG, 1);
	SPI.transfer(ba, 1, 0);

	//--2 Шаг - Настройка точки
	if(Point.CS == "SS1")
			SS = 1;
	if(Point.CS == "SS2")
			SS = 2;
	if(Point.CS == "SS3")
			SS = 3;

	ba = strTohex(Point.BusPlus, 8);
	SPI.transfer(ba, 8, SS);

	return true;
}
//--------------------------------------------------
QByteArray DeviceSTR::strTohex(QString str, int count)
{

	QByteArray ba;
	bool ok;

	int c = (count *2) - str.count();

	if(c > 0)
	{
			for(int i = 0; i < c; i++)
				str.insert(0,"0");
	}

	for(int i = 0; i < count; i++)
	{
			ba.push_back(str.right(2).toUInt(&ok, 16));
			str = str.left(str.count()-2);
	}

	return ba;

}
//--------------------------------------------------
