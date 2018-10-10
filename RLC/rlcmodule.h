//------------------------------------------------------------------
#ifndef RLCMODULE_H
#define RLCMODULE_H
//------------------------------------------------------------------
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QTime>
#include "csys.h"
//------------------------------------------------------------------
/// \brief Команды для RLC-метра
typedef enum
{
	M_UP = 0x06,					///< Кнопка вверх
	M_RIGHT = 0x01,				///< Кнопка вправо
	M_LEFT = 0x09,				///< Кнопка влево
	M_DOWN = 0x04,				///< Кнопка вниз
	M_C = 0x0B,						///< Кнопка режим C
	M_R = 0x03,						///< Кнопка режим R
	M_L = 0x07,						///< Кнопка режим L
	M_MENU = 0x00,				///< Кнопка меню
	M_OFFSET = 0x0C,			///< Кнопка смещение
	M_FREQUENCY = 0x0D,		///< Кнопка частота
	M_LEVEL = 0x0E,				///< Кнопка уровень
	M_LIMIT = 0x0F,				///< Кнопка предел
	M_ENTER = 0x05				///< Кнопка ввод
}TCONTROLRLC;
/// \brief Перечисление для парсирования данных
typedef enum
{
	S_READ_SYNC_BYTE,			///< Поиск байта синхронизации
	S_READ_PARS_21_BYTE,	///< Чтения 21 байта
	S_READ_CS,						///< Расчёт контрольной суммы
	S_STOP_READ						///< Окончание проверки
}TSTATUSREAD;
//------------------------------------------------------------------
/**
	\class RLCmodule
	\brief Класс модуля RLC-метра.<br>
		<h2>Модуль управления RLC-метром E7-20.</h2><br>
	Модуль реализует следующий функционал:<br>
		- Отправка управляющих команд RLC-метра по RS232
		- Считывания данх по с RLC-метра по RS232

*/
class RLCmodule : public QObject
{
	Q_OBJECT
public:
	/// \brief Конструктор
	/// \param parent, указатель на объект родитель
	explicit RLCmodule(QObject *parent = nullptr);
	/// \brief Деструтор
	~RLCmodule();

	/// \brief установка имени ком порта
	/// \param nameComprot, имя порта RS232
	void setNameComPort(QString nameComprot);
	/// \brief Обнуление тайм оута для записи
	void nullTimeoutWrite();
	/// \brief Подключиться к RLC
	bool connectToRLC();
	/// \brief Отключиться от RLC
	void disconnectFromRLC();
	/// \brief Функция контроля RLC
	void controlRLC(TCONTROLRLC c);
	/// \brief Чтение пакета данных
	bool readPakage();
	/// \Функция проверки RLC метра
	bool isEnable();
	/// \brief Получить измеряемыЙ параметр
	double getImParam()
	{
			return ImParamValue;
	}
	/// \brief Получить доп измеряемое значение
	double getSecParam()
	{
			return SecParamValue;
	}

	/// \brief Создание порта
	void newSerialPort();

private:
	double offset;						///< Значение смещение
	double Level;							///< Уровень измерительного сигнала
	double Frequency;					///< Частота измерения в Hz
	qint8 Flags;							///< Байт флагов
	qint8 Mode;								///< Режим работы прибора
	qint8 Limit;							///< Предел измерений
	qint8 ImParam;						///< Измеряемый параметр	(C, L, R ...)
	qint8 SecParam;						///< Дополнительно измеряемый параметр (Q, D ...)
	double SecParamValue;			///< Дополнительное измеряемое значение
	double ImParamValue;			///< Измеряемое значение (R значение в Om, C значение в F)
	qint8 OnChange;						///< Байт фдагов редактирования
	quint8 CS;								///< Контрольная сумма

	int timeOutWrite;					///< Тайм оут для записи даных
	int idSynkByte;						///< Номер байта синхронизации
	TSTATUSREAD STATUSREAD;		///< Статус чтения пакета
	QByteArray pakageRLC;			///< Считаный пакет
	QString nameComprot;			///< Имя ком порта
	QSerialPort *serialPort;	///< Порт RS232

	/// \brief Настройка ком порта
	void setSettings();
	/// \brief Парсинг данных
	/// \param PK байты для парсинга
	/// \return флаг успешного парсинга
	bool parsingPakage(QByteArray PK);

};
//------------------------------------------------------------------
#endif // RLCMODULE_H
//------------------------------------------------------------------
