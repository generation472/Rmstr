//------------------------------------------------------------------
#include "rlcmodule.h"
#include <QDebug>
#include <QThread>
#include <QtMath>
//------------------------------------------------------------------
RLCmodule::RLCmodule(QObject *parent) : QObject(parent)
{
	nameComprot = "";
	STATUSREAD = S_READ_SYNC_BYTE;
	timeOutWrite = idSynkByte = 0;
}
//------------------------------------------------------------------
RLCmodule::~RLCmodule()
{

}
//------------------------------------------------------------------
void RLCmodule::setNameComPort(QString nameComprot)
{
	this->nameComprot = nameComprot;
	serialPort->setPortName(this->nameComprot);

}
//------------------------------------------------------------------
void RLCmodule::nullTimeoutWrite()
{
	timeOutWrite = 0;
}
//------------------------------------------------------------------
bool RLCmodule::connectToRLC()
{

	if(serialPort->open(QIODevice::ReadWrite))
	{
		setSettings();
		if(readPakage())
		{
			return true;
		}
		else
		{
			serialPort->close();
		}

	}

	return false;
}
//------------------------------------------------------------------
void RLCmodule::disconnectFromRLC()
{
	serialPort->close();
}
//------------------------------------------------------------------
void RLCmodule::controlRLC(TCONTROLRLC c)
{

	if(!serialPort->isOpen())
	{
		return;
	}

	char com[1];
	com[0] = (quint8)c;

	qWarning()<< "-------------Отладочная информация ---------------------";
	qWarning() << "Comand : " << c;

	switch (c)
	{
	case M_C:
		readPakage();
		if(ImParam != 0)
		{
			serialPort->write(com, 1);
			if(!serialPort->waitForBytesWritten(100))
			{
				timeOutWrite++;
				if(timeOutWrite >= 3)
					break;
				controlRLC(c);
			}
		}
		break;
	case M_R:
		readPakage();
		if(ImParam != 2)
		{
			serialPort->write(com, 1);
			if(!serialPort->waitForBytesWritten(100))
			{
				timeOutWrite++;
				if(timeOutWrite >= 3)
					break;
				controlRLC(c);
			}
		}
		break;
	case M_L:
		readPakage();
		if(ImParam != 1)
		{
			serialPort->write(com, 1);
			if(!serialPort->waitForBytesWritten(100))
			{
				timeOutWrite++;
				if(timeOutWrite >= 3)
					break;
				controlRLC(c);
			}
		}
		break;
	default:
		serialPort->write(com, 1);
		if(!serialPort->waitForBytesWritten(100))
		{
			timeOutWrite++;
			if(timeOutWrite >= 3)
				break;
			controlRLC(c);
		}
		break;
	}

	qWarning() << "Mode" << ImParam;
}
//------------------------------------------------------------------
void RLCmodule::setSettings()
{
	if(serialPort->isOpen())
	{
		serialPort->setBaudRate(QSerialPort::Baud9600);
		serialPort->setDataBits(QSerialPort::Data8);
		serialPort->setStopBits(QSerialPort::OneStop);
		serialPort->setFlowControl(QSerialPort::NoFlowControl);
		serialPort->setParity(QSerialPort::NoParity);

	}
}
//------------------------------------------------------------------
bool RLCmodule::readPakage()
{
	SecParamValue = 0;
	ImParamValue = 0;

	if(!serialPort->isOpen())
	{
		return false;
	}

	bool ok = false;

	QTime timeout;
	timeout.start();
	serialPort->clear(QSerialPort::Input);
	QByteArray byteArray;
	STATUSREAD = S_READ_SYNC_BYTE;
	idSynkByte = 0;

	while (true)
	{

		if(serialPort->waitForReadyRead(50))
		{
			byteArray.push_back(serialPort->readAll());

			if(parsingPakage(byteArray))
			{
				ok = true;
			}

			if(STATUSREAD == S_STOP_READ )
			{
				if(ok == true)
				{
					break;
				}
				else
				{
					serialPort->clear();
					STATUSREAD = S_READ_SYNC_BYTE;
					idSynkByte = 0;
				}

			}

		}

		if(timeout.elapsed()/500 > 1)
		{
			ok = false;
			break;
		}

	}

	return ok;
}
//------------------------------------------------------------------
bool RLCmodule::isEnable()
{
	if(readPakage())
	{
		return true;
	}
	else
	{
		return false;
	}

}
//------------------------------------------------------------------
void RLCmodule::newSerialPort()
{
	serialPort = new QSerialPort();
}
//------------------------------------------------------------------
bool RLCmodule::parsingPakage(QByteArray PK)
{

	DEPACK DP;
	DEPACK DPmn;
	bool ok = false;

	quint8 CS = 0;

	forever
	{
		switch (STATUSREAD)
		{
		//==================================================
		case S_READ_SYNC_BYTE:
			ok = false;

			for(int i = 0; i < PK.size(); i++)
			{
				if((char)PK[i] ==  (char)0xAA)
				{
					ok = true;
					idSynkByte = i;
				}

			}

			if(!ok)
			{
				return false;
			}
			else
			{
				STATUSREAD = S_READ_PARS_21_BYTE;
			}
			break;
		//==================================================
		case S_READ_PARS_21_BYTE:

			if((PK.count() - idSynkByte) < 21)
			{
				return false;
			}

			//------------------------------//
			DP.str2b.b1 = PK[idSynkByte + 1];
			DP.str2b.b2 = PK[idSynkByte + 2];
			offset = (double)DP.uint16 / 100;
			//------------------------------//
			DP.uint8 = PK[idSynkByte + 3];
			Level = (double)DP.uint8 / 100;
			//------------------------------//
			DP.str2b.b1 = PK[idSynkByte + 4];
			DP.str2b.b2 = PK[idSynkByte + 5];
			DPmn.uint8 = PK[idSynkByte + 6];
			Frequency *= pow(10, DPmn.uint8);
			//------------------------------//
			Flags = PK[idSynkByte + 7];
			Mode = PK[idSynkByte + 8];
			Limit = PK[idSynkByte + 9];
			ImParam = PK[idSynkByte + 10];
			SecParam = PK[idSynkByte + 11];
			//------------------------------//
			DP.str4b.b1 = PK[idSynkByte + 12];
			DP.str4b.b2 = PK[idSynkByte + 13];
			DP.str4b.b3 = PK[idSynkByte + 14];
			DP.str4b.b4 = 0;
			DPmn.dop = PK[idSynkByte + 15];
			if(DPmn.dop > 127)
				DPmn.dop = DPmn.dop - 256;
			SecParamValue = (double)DP.uint32 * pow(10, DPmn.dop);
			//------------------------------//
			DP.str4b.b1 = PK[idSynkByte + 16];
			DP.str4b.b2 = PK[idSynkByte + 17];
			DP.str4b.b3 = PK[idSynkByte + 18];
			DP.str4b.b4 = 0;
			DPmn.dop = PK[idSynkByte + 19];
			if(DPmn.dop > 127)
				DPmn.dop = DPmn.dop - 256;
			ImParamValue = (double)DP.uint32 * pow(10, DPmn.dop);
			//------------------------------//
			OnChange = PK[idSynkByte + 20];
			this->CS = PK[idSynkByte + 21];

			STATUSREAD = S_READ_CS;
			break;
		//==================================================
		case S_READ_CS:


			for(int i = 0; i < 21; i++)
			{
				CS += PK[idSynkByte + i];
			}

			STATUSREAD = S_STOP_READ;
			break;
		//==================================================
		case S_STOP_READ:

			if(CS == this->CS)
			{
				//qWarning()<< "Count byte: " << PK.count();
				qWarning()<<"Param :" <<ImParamValue <<" " << SecParamValue;
				return true;
			}
			else
			{
				return false;
			}
			break;


		default:
			break;
		}
	}

}
//------------------------------------------------------------------
