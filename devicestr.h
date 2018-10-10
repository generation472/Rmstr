//--------------------------------------------------
#ifndef DEVICESTR_H
#define DEVICESTR_H
//--------------------------------------------------
#include <QObject>
#include <QThread>

#include "RLC/rlcmodule.h"
#include "SUB20/spimodule.h"

//--------------------------------------------------
/**
	\class DeviceSTR
	\brief Класс модуля оборудование пульта STR.<br>
		<h2>Модуль управления оборудованием пульта STR.</h2><br>
	Потоковый модуль, является надстройкой для модуля RLCmodule и SPImodule, реализует следующий функционал:<br>
	- Управление SUB-20.
	- Управление RLC E7-20.
	- Подключение к точкам цепи  и считывания данных.

*/
class DeviceSTR : public QObject
{
	Q_OBJECT
public:
	/// \brief Конструктор
	/// \param parent, указатель на объект родитель
	explicit DeviceSTR(QObject *parent = nullptr);
	/// \brief Деструктор
	~DeviceSTR();

	/// \brief Функция поиска Sub-20
	void searchSub();
	/// \brief Функция включить/выключить RLC
	/// \param sw, статус оборудования
	bool switchRLC(bool sw);
	/// \brief Включить/выключить SPI
	/// \param sw, статус оборудования
	bool switchSPI(bool sw);
signals:
	/// \brief Сигнал работы RLC
	/// \param f, статус оборудования
	void signal_enableRLC(bool f);
	/// \brief Установка списка Sub20
	/// \param list, список sub20
	void signal_setSubList(QStringList list);
	/// \brief Измеренное значение для ручного режима
	/// \param Im, измеренное значение
	/// \param Sec, дополнительное измеряемое значение
	void signal_getValueFromPointM(double Im, double Sec);
	/// \brief Измеренное значение для авто режима
	/// \param Im, измеренное значение
	/// \param Sec, дополнительное измеряемое значение
	void signal_getValueFromPointA(double Im, double Sec);
	/// \brief статус подключения оборудования в ручном режиме
	/// \param status, состояния подключёного оюорудования
	void signal_statusDeviceM(TSTATUSDEVICE status);
	/// \brief статус подключения оборудования в автоматическом режиме
	/// \param status, состояния подключёного оюорудования
	void signal_statusDeviceA(TSTATUSDEVICE status);

public slots:
	/// \brief Включить/выключить RLC
	/// \param sw, статус оборудования
	void slot_switchRLC(bool sw);
	/// \brief Обработка запроса получить список sub20
	void slot_getSubList();

	/// \brief Слот настройка оборудования
	/// \param numberSub, номер sub20
	/// \param numberPort, имя порта
	/// \param ms, задержка проверки
	void slot_SetSettings(QString numberSub, QString numberPort, int ms);
	/// \brief Обработка запроса произвести измерение цепи
	/// \param PointP, струтктура точки на шине плюс
	/// \param PointM, струтктура точки на шине минус
	/// \param mode, режим проверки
	void slot_getValueFromPointM(TSTRPCONNECTION PointP, TSTRPCONNECTION PointM, QString mode);
	/// \brief Обработка запроса произвести измерение цепи
	/// \param PointP, струтктура точки на шине плюс
	/// \param PointM, струтктура точки на шине минус
	/// \param mode, режим проверки
	void slot_getValueFromPointA(TSTRPCONNECTION PointP, TSTRPCONNECTION PointM, QString mode);
	/// \brief Сигнал создание QSerialPort в потоке
	void slot_creatSerialPort();

	/// \brief Слот проверки оборудования для ручного режима
	void slot_checkDeviceM();
	/// \brief Слот проверки оборудования для авто режима
	void slot_checkDeviceA();

private:
	RLCmodule RLC;		///< Модуль управления RLC E7-20
	SPImodule SPI;		///< Модуль управления SUB-20

	int delayCheck;		///< Задержка

	/// \brief Расчёт значения для точки минус
	/// \param Point, точка для преобразования
	/// \return адрес значения по шине минус
	QString getValuePointMinus(TSTRPCONNECTION Point);
	/// \brief Функция настройка точки
	/// \param Point, струтктура точки
	bool connectPoint(TSTRPCONNECTION Point);

	/// \brief Перевод строки в hex
	/// \param str, строка для преоброзования
	/// \param count, кол-во байт
	/// \return Массив байт
	QByteArray strTohex(QString str, int count);
};
//--------------------------------------------------
#endif // DEVICESTR_H
//--------------------------------------------------
