//------------------------------------------------------------------
#ifndef DATABASEMODULE_H
#define DATABASEMODULE_H
//------------------------------------------------------------------
#include <QObject>
#include <QtSql>
#include "csys.h"
//------------------------------------------------------------------
/**
	\class DataBaseModule
	\brief Класс модуля Базы данных. <br>
		<h2>Модуль связи с базой данных.</h2><br>
	Модуль реализует следующий функционал:<br>
		- Подключение к файлу БД
		-	Запись новых данных в таблицы
		- Чтение данных
		- Обновление данных в таблицах
		- Удаление записей из таблиц
	<br>
	База данных состоит из двух таблиц, таблица цепей и точек.<br>
	Таблица точек состоит из следующих полей:<br>
		- Имя точки, наименование контактов разъёмов
		- Регистр, значения для управляющего регистра
		- Чип селект, выбор  чип селект устройства SUB-20, возможные значения(SS1, SS2, SS3)
		- Адрес точки, значения для настройки точки по шине плюс, (значения по шине минус вычисляется автоматически)
	<br>
	Таблица цепей состоит из следующих полей:
		- Имя цепи, имя цепи состоит из двух точке, подключенных к шине плюс и к шине минус (С лево на право, шина плюс и шина минус).
		- Режим проверки, режим проверяемой цепи, R или C.
		- Мин. Значение, минимальное значение проверяемой цепи
		- Макс. Значение, максимальное значение проверяемой цепи.
		- Второй параметр, второй параметр проверяемой цепи



*/
class DataBaseModule : public QObject
{
	Q_OBJECT
public:
	/// \brief Конструтор
	/// \param parent указатель на объект родитель
	explicit DataBaseModule(QObject *parent = nullptr);
	/// \brief Деструтор
	~DataBaseModule();

	QString t_LinksPoint;		///< Имя таблицы Связей
	QString t_PointConnection;	///< Имя таблицы Точек

	/// \brief Функция получения точки по имени
	/// \param NamePoint имя точки
	/// \param ok флаг успешного выполнения функции
	TSTRPCONNECTION getPoint(QString NamePoint, bool &ok);
	/// \brief Функция получения точки по iD
	/// \param ID номер id точки
	/// \param ok флаг успешного выполнения функции
	TSTRPCONNECTION getPoint(int ID, bool &ok);
	/// \brief Получить все точки
	/// \param ok флаг успешного выполнения функции
	QVector<TSTRPCONNECTION> getVecPoint(bool &ok);
	/// \brief Получить вектор точек, Содержаший заданные строки
	/// \param ok флаг успешного выполнения функции
	/// \param search, строка поиска
	/// \param Column, стобец по которому ведётся поиск
	QVector<TSTRPCONNECTION> getVecPoint(QString search, QString Column, bool &ok);
	/// \brief Фукция для добавления точек в БД
	/// \param Point, добавляемая точка
	bool insertPoint(TSTRPCONNECTION Point);
	/// \brief Фукция для удаления точек из БД
	/// \param ID, номер точки
	bool deletPoint(int ID);
	/// \brief Фукция для удаления точек из БД
	/// \param NamePoint, имя точки
	bool deletPoint(QString NamePoint);
	/// \brief Функция для изменения точки
	/// \param Point, точка
	bool updatePoint(TSTRPCONNECTION Point);



	/// \brief Получить одну цепь
	/// \param ok флаг успешного выполнения функции
	/// \param nameLink, имя цепи
	TSTRLINKPOINT getLink(QString nameLink, bool &ok);
	/// \brief Добавить одну цепь
	/// \param Link, структура цепи
	bool insertLink(TSTRLINKPOINT Link);
	/// \brief Фукция для удаление цепей из БД
	/// \param nameLink, имя цепи
	bool deletLink(QString nameLink);
	/// \brief Фукция для удаление цепей из БД
	/// \param id, номер цепи
	bool deletLink(int id);
	/// \brief Функция для изменения цепи
	/// \param Link, цепь
	bool updateLink(TSTRLINKPOINT Link);
	/// \brief Получить весь вектор связей
	/// \param ok флаг успешного выполнения функции
	QVector<TSTRLINKPOINT> getVecLinks(bool &ok);
	/// \brief Получить вектор связей, Содержаший заданные строки
	/// \param ok флаг успешного выполнения функции
	/// \param nameLink, имя цепи
	QVector<TSTRLINKPOINT> getVecLinks(QString nameLink, bool &ok);
	/// \brief Получить вектор связей, Содержаший заданные строки
	/// \param ok флаг успешного выполнения функции
	/// \param search, строка поиска
	/// \param Column, стобец по которому ведётся поиск
	QVector<TSTRLINKPOINT> getVecLinks(QString search, QString Column, bool &ok);


	/// \brief Функция для подключения к БД
	/// \param nameDB Имя базы данных
	bool connectDB(QString nameDB);
private:
	QSqlDatabase db;			///< База данных


	//FIXME В release версии необходимо удалить данные функции
	/// \brief Функция для обновления значений таблицы точек
	///	исправление возможно будующих ошибок
	void updateDataBase();
	/// \brief Функция для обновления значений id с 1 для цепей
	void resetID();
	/// \brief Функция для обновления значений id с 1 для точек
	void resetPointid();
	/// \brief Функция обновления id точек для цепей
	void updateIDPointLink();

public slots:
};
//------------------------------------------------------------------
#endif // DATABASEMODULE_H
//------------------------------------------------------------------
