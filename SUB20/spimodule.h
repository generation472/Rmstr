//-------------------------------------------------------------------
#ifndef SPIMODULE_H
#define SPIMODULE_H
//-------------------------------------------------------------------
#include <QObject>
#include <QVector>
#include "libsub.h"
//-------------------------------------------------------------------
/// \brief Структура хранения указателей на sub20
typedef struct strsub
{
	QString subName;
	sub_device dev;
}TSTRSUB;

//-------------------------------------------------------------------
/**
	\class SPImodule
	\brief Класс модуля SUB-20.<br>
		<h2>Модуль управления SUB-20</h2><br>
	Модуль реализует следующий функционал:<br>
		- Поиск устройсв Sub-20
		- Отправка данных по SPI

*/
class SPImodule : public QObject
{
  Q_OBJECT
public:
	/// \brief Конструктор
	/// \param parent, указатель на объект родитель
  explicit SPImodule(QObject *parent = 0);
	/// \brief Деструктор
	~SPImodule();

	/// \brief Утсановки имени sub20.
	/// \param number, имя sub20
	void setNumberSub(QString number);
	/// \brief Поиск sub20
  void searchSub();
	/// \brief Получить имя устройства sub20
	/// \param ok, флаг выполнения функции
	/// \return Имя sub20
	QString getSubName(bool &ok);
	/// \brief Закрыть sub20
	void closeSub();
	/// \brief Открыть sub20
	bool openSub();

	/// \brief Проверить существование sub20
	/// \return возвращает активность устройства
	bool isEnabledSub();


	/// \brief Отправка данных по spi
	/// \param outByte данные для отправки
	/// \param sz кол-во отправляемыз байтов
	/// \param ss номер ss
	/// \return флаг успешной отправки
	bool transfer(QByteArray outByte, int sz, int ss);

	/// \brief Обработка запроса списка устройств sub20
	/// \return Список устройств sub20
	QStringList getSubList();


private:
	QString numberSub;						// Имя sub20
	QVector<TSTRSUB > vecDev;			// Вектор устройств sub20
	sub_device dev = nullptr;			// Устройство spi
	sub_handle handle = nullptr;	// Управляемое утройство spi
	bool fl_subActiv;							// Флаг активности sub20

};
//-------------------------------------------------------------------
#endif // SPIMODULE_H
//-------------------------------------------------------------------
