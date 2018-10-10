//---------------------------------------------------------------
#ifndef SHEDULERSTR_H
#define SHEDULERSTR_H
//---------------------------------------------------------------
#include <QObject>
#include <QSettings>
#include "DB/databasemodule.h"
#include "Proc/proc.h"
#include "csys.h"
//---------------------------------------------------------------
/**
	\class ShedulerSTR
	\brief Оcновной модуль управления пультом STR.<br>
		<h2>Модуль управления пультом STR.</h2><br>
	Модуль реализует следущий функционал:<br>
		- Ручная проверки цепи
		- Автоматическая проверки цепи
		- Управление настройками программы
		- Управление созданием протокола
		- Управление запросами БД

*/
class ShedulerSTR : public QObject
{
	Q_OBJECT
public:
	/// \brief Конструктор
	/// \param parent, указатель на виджет родитель
	explicit ShedulerSTR(QObject *parent = nullptr);
	/// \brief Деструктор
	~ShedulerSTR();

    /// \brief Чтение настроек RM_STR
    void readSettingsSTR();

		/// \brief функция проверяет идёт ли сейчас автопроверка
		bool isAutocontrol();
signals:
    //-----------Сигналы для WidgetDatabase----------------
    /// \brief Сигнал установки пути БД на гуи
		/// \param path, путь
    void signal_setPathDB(QString path);
    /// \brief Сигнал подключения к БД
		/// \param fl, флаг подключения
    void signal_connectedToDB(bool fl);
    /// \brief Сигнал отправить таблицу цепей на Гуи
		/// \param linksTable, вектор цепей
		void signal_sentTable(QVector<TSTRLINKPOINT> linksTable);
    /// \brief Сигнал отправить таблицу точек на Гуи
		/// \param pointTable, вектор точек
		void signal_sentTable(QVector<TSTRPCONNECTION> pointTable);
    /// \brief Сигнал ошибка обработка запросы БД
		/// \brief str, сообщение
		void signal_ErrorDB(QString str);
		/// \brief Сигнал успешной записи данных
		void signal_saveOK();
		//-----------Сигналы для dialogSettings----------------
		/// \brief Сигнал для настройки номер sub, номер порта и задержки
		/// \param numberSub, имя sub20
		/// \param numberPort, имя порта rs232
		/// \param delay, задержка проверки цепи
		void signal_SetSettings(QString numberSub,QString numberPort,int delay);
		/// \brief Сигнал для установки настроек звука и отображения таблицы
		/// \param table, настройка отображение двух таблиц
		/// \param error, настройка уведомления
		void signal_SetSettings(bool table, bool error);
		//-----------Сигналы для WidgetManualControl----------------
		/// \brief Отправка таблицы на гуи
		/// \param linksTable, вектор цепей
		void signal_sentTableLink(QVector<TSTRLINKPOINT> linksTable);
		/// \brief Сигнал, результат проверки
		/// \param Im, измеренное значение
		/// \param Sec, дополнительный измереный параметр
		/// \param check, флаг проверки
		void signal_sentResult(double Im, double Sec, bool check);
		/// \brief Запрос проверки оборудования
		void signal_checkDeviceM();
		/// \brief статус подключения оборудования
		/// \param status, статус подключёного оборудования
		void signal_statusDeviceM(TSTATUSDEVICE status);
		//-----------Сигнал для wAutoControl----------------------
		/// \brief Сигнал, результат проверки цепи
		/// \param link, струтктура цепи
		/// \param Im, измеренное значение
		/// \param Sec, дополнительный измереный параметр
		/// \param check, флаг проверки
		void signal_sentResult(TSTRLINKPOINT link, double Im, double Sec, bool check);
		/// \brief Сигнал статуса проверки
		/// \param status, статус автоматической проверки
		void signal_statusAutoCheck(TSTATUSAUTOCHECK status);
		/// \brief Установка размерности прогресс бара
		/// \param max, максимальное значение прогресс бара
		void signal_setRangeProgressBar(int max);
		/// \brief Запрос проверки оборудования
		void signal_checkDeviceA();
		/// \brief статус подключения оборудования
		/// \param status, статус подключёного оборудования
		void signal_statusDeviceA(TSTATUSDEVICE status);

		//-----------Сигналы для DeviseSTR----------------------------
		/// \brief Сигнал запроса данных с точки для ручного режима
		/// \param PointP, структура точки на шине плюс
		/// \param PointM, структура точки на шине минус
		/// \param mode, режим проверки
		void signal_getValueFromPointM(TSTRPCONNECTION PointP, TSTRPCONNECTION PointM, QString mode);
		/// \brief Сигнал запроса данных с точки для авто режима
		/// \param PointP, структура точки на шине плюс
		/// \param PointM, структура точки на шине минус
		/// \param mode, режим проверки
		void signal_getValueFromPointA(TSTRPCONNECTION PointP, TSTRPCONNECTION PointM, QString mode);
		//-----------Сигналы для wProc----------------------------
		/// \brief Сигнал установки настроек для модуля протоколирования
		/// \param fl, настрока отображения модуля
		void signal_setSettingsTable(bool fl);

		/// \brief Сигнал alert
		void signal_alert();


public slots:
    //-----------Слоты для WidgetDatabase----------------
    /// \brief Слот установки пути для БД
		/// \param path, путь
    void slot_changeSettingsPathDB(QString path);
    /// \brief Слот запроса таблицы
		/// \param nameTable, имя таблицы
    void slot_getTable(QString nameTable);
    /// \brief Обработка запрос сохранить связь
		/// \param Link, структура цепи
    void slot_SaveLink(TSTRLINKPOINT Link);
    /// \brief Обработка запроса сохранить точку
		/// \param Point, структура точки
    void slot_SavePoint(TSTRPCONNECTION Point);
    /// \brief Обработка запроса удалить запись
		/// \param id, номер записи
		/// \param nameTable, ими таблицы
    void slot_DeleteRecord(int id, QString nameTable);
		/// \brief Обработка запроса добавить точку
		/// \param Point, структура точки
		void slot_addPoint(TSTRPCONNECTION Point);
		/// \brief Обработка запроса добавить цепь
		/// \param link, структура цепи
		void slot_addLink(TSTRLINKPOINT link);
		/// \brief Обработка запроса на получения записей по поиску
		/// \param nameTable, имя таблицы
		/// \param nameColumn, имя столбца
		/// \param searchText, строка поиска
		void slot_getTable(QString nameTable, QString nameColumn, QString searchText);
		//-----------Слоты для dialogSettings----------------
		/// \brief Слот установки настроек
		/// \param numberSub, имя sub20
		/// \param numberPort, имя порта rs232
		/// \param delay, задержки
		void slot_SetSettings(QString numberSub,QString numberPort,int delay);
		/// \brief Слот для установки настроек звука и отображения таблицы
		/// \param table, настройка отображение двух таблиц
		/// \param error, настройка уведомления
		void slot_SetSettings(bool table, bool error);
		//-----------Слоты для WidgetManualControl----------------
		/// \brief Обработка запроса получить всю талицу цепей
		void slot_getTableLink();
		/// \brief Провести измерение
		/// \param plus, имя точки на шине плюс
		/// \param minus, имя точки на шине минус
		void slot_checkLink(QString plus, QString minus);
		/// \brief Запрос на получения записей по поиску
		/// \param searchText, строка поиска
		void slot_getTableLink(QString searchText);
		//-----------Слоты для DeviseSTR----------------------------
		/// \brief Измеренное значение для русного режима
		/// \param Im, измеренное значение
		/// \param Sec, дополнительное измеренное значение
		void slot_getValueFromPointM(double Im, double Sec);
		/// \brief Измеренное значение для авто режима
		/// \param Im, измеренное значение
		/// \param Sec, дополнительное измеренное значение
		void slot_getValueFromPointA(double Im, double Sec);

		//-----------Слоты для wAutoControl------------------------
		/// \brief Слот установки статуса автоматической проверки
		/// \param status, статус подключёного оборудования
		void slot_setStatusAutoControl(TSTATUSAUTOCHECK status);
		/// \brief Слот изменения технологического номера
		/// \param number технологический номер
		void slot_changeTechNumber(QString number);


private:
	Proc proc;																///< Модуль протоколирования
	QString techNumber;												///< Технологический номер

	DataBaseModule DB;												///< Модуль базы данных
	QSettings *settingsSTR;										///< Настройки программы RM_STR

	QString s_pathDB;													///< Путь к базе данных
	QString s_nameComPortRLC;									///< Имя порта RS232
	QString s_nameSUB_20;											///< Имя SUB-20
	QString s_delay;													///< Задержки
	bool twoTableProc;												///< Показ двух таблиц в протоколе
	bool soundError;													///< Звуковой сигнал для ошибок

	bool autoControl;													///< Статус работы автоматической проверки


	TSTATUSAUTOCHECK statusAutoCheck;					///< Статус команд для автоматической проверки

	QVector<TSTRLINKPOINT> linksTable4Check;	///< Цепи для автоматической проверки
	int IdCheckLink;													///< Id проверяемой цепи
	TSTRLINKPOINT checklink;									///< Проверяемая цепь


	/// \brief Сохранение настроек Базы данных
	/// \param nameDB, путь базы данных
	void setSettingsPathDB(QString nameDB);
	/// \brief Сохранение настроек имя порта RS232
	/// \param nameComPortRLC, имя порта RS232
	void setSettingsComPortRLC(QString nameComPortRLC);
	/// \brief Сохранение настроек имя sub-20
	/// \param nameSUB_20, имя sub20
	void setSettingsSUB_20(QString nameSUB_20);
	/// \brief Сохранение настроек задержки
	/// \param delay, настройка задержки проверки
	void setSettingsDelay(QString delay);


};
//---------------------------------------------------------------
#endif // SHEDULERSTR_H
//---------------------------------------------------------------
