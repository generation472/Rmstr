//-------------------------------------------------------------------
#include "spimodule.h"
#include <QThread>
#include <QDebug>
//-------------------------------------------------------------------
SPImodule::SPImodule(QObject *parent) : QObject(parent)
{
	fl_subActiv = false;
	numberSub = "";
	handle = 0;
	searchSub();
}
//-------------------------------------------------------------------
SPImodule::~SPImodule()
{
	if(fl_subActiv)
	{
		sub_close(handle);
	}
}
//-------------------------------------------------------------------
void SPImodule::setNumberSub(QString number)
{
	numberSub = number;
}
//-------------------------------------------------------------------
void SPImodule::searchSub()
{

	char tmp[32];
	if(fl_subActiv)
	{
		sub_close(handle);
	}
	vecDev.clear();

	dev = nullptr;


	dev = sub_find_devices(dev);

	while (dev)
	{
		TSTRSUB sub20;
		handle = sub_open(dev);

		sub20.dev = dev;
		sub_get_product_id(handle, tmp, sizeof (tmp));

		if(QString(tmp) == "SUB-20")
		{

			 sub_get_serial_number(handle, tmp, sizeof (tmp));
			 sub20.subName = QString(tmp);
			 vecDev.push_back(sub20);
		}

		sub_close(handle);
		handle = 0;
		dev = sub_find_devices(dev);
	}


}
//-------------------------------------------------------------------
QString SPImodule::getSubName(bool &ok)
{

	if(fl_subActiv)
	{
		char tmp[32];
		sub_get_serial_number(handle, tmp, sizeof (tmp));
		ok = true;
		return QString(tmp);
	}
	else
	{
		fl_subActiv = false;
		ok = false;
		return "";
	}

}
//-------------------------------------------------------------------
void SPImodule::closeSub()
{
	if(fl_subActiv)
	{
		sub_close(handle);
		fl_subActiv = false;
		handle = 0;
	}
}
//-------------------------------------------------------------------
bool SPImodule::openSub()
{
	closeSub();


	for(TSTRSUB s: vecDev)
	{
		if(s.subName == numberSub)
		{
			handle = sub_open(s.dev);

			if(isEnabledSub())
			{
				fl_subActiv =true;
				sub_spi_config(handle,SPI_ENABLE|SPI_CPOL_RISE|SPI_SMPL_SETUP|SPI_MSB_FIRST|SPI_CLK_125KHZ,NULL);
				return true;
			}

		}
	}

	return false;
}
//-------------------------------------------------------------------
bool SPImodule::transfer(QByteArray outByte, int sz, int ss)
{
	char out[sz];
	char in[sz];

	for(int i = 0; i < sz; i++)
	{
		out[i]= outByte[i];
	}

	if(fl_subActiv)
	{

		if(isEnabledSub())
		{
			if(sub_spi_transfer(handle, out, in, sz, SS_CONF(ss, SS_LO)))
			{
				qWarning()<<"Eror transfer" ;
				return false;
			}
			else
			{
					std::reverse(outByte.begin(), outByte.end());
					qWarning()<< "--------------Отправка по SPI-----------";
					qWarning()<<"Transfer = " << outByte.toHex();
					QByteArray tmp;
					for(int i = 0; i < sz; i++)
					{
						tmp.push_back(in[i]);
					}
					std::reverse(tmp.begin(), tmp.end());

					qWarning()<<"GetDate = " << tmp.toHex();
					qWarning()<< "----------------------------------------";
			}

			return true;

		}
		else
		{
			fl_subActiv = false;
			return false;
		}

	}

	return false;
}
//-------------------------------------------------------------------
bool SPImodule::isEnabledSub()
{
	char tmp[32];

	if(handle != 0)
	{
		sub_get_product_id(handle, tmp, sizeof (tmp));
	}

	if(QString(tmp) == "SUB-20")
	{
		fl_subActiv = true;
	}
	else
	{
		fl_subActiv = false;
	}

	return fl_subActiv;
}
//-------------------------------------------------------------------
QStringList SPImodule::getSubList()
{
	QStringList listSub20;

	for(TSTRSUB devSub: vecDev)
	{
		listSub20.push_back(devSub.subName);
	}

	return listSub20;
}
//-------------------------------------------------------------------
