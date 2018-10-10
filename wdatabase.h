//-----------------------------------------------------------
#ifndef WDATABASE_H
#define WDATABASE_H
//-----------------------------------------------------------
#include <QWidget>
#include <QFileDialog>
#include <QMovie>
#include <QLabel>

#include "csys.h"
#include "dialogaddpoint.h"
#include "dialogaddlink.h"
//-----------------------------------------------------------
namespace Ui {
class wDatabase;
}
//-----------------------------------------------------------
/**
	\class wDatabase

	\brief Класс виджет управления БД.<br>
		<h2>Виджет управления БД</h2><br>
	Виджет реализует следующие функции
		- Отображение таблиц цепей и точек
		- Добавления новых записей
		- Удаление запесей
		- Поиск по запесям
	<br>
*/
class wDatabase : public QWidget
{
	Q_OBJECT

public:
	/// \brief Конструктор
	/// \param parent, указатель на виджет родитель
	explicit wDatabase(QWidget *parent = 0);
	/// \brief Деструктор
	~wDatabase();

signals:
	/// \brief Запрос на изменение Базы данных
	/// \param name, имя базы
	void signal_changeDB(QString name);
	/// \brief Запрос на получение записей из таблицы
	/// \param nameTable, имя таблицы
	void signal_getTable(QString nameTable);
	/// \brief Запрос на получения записей по поиску
	/// \param nameTable, имя таблицы
	/// \param nameColumn, имя столбца
	/// \param searchText, строка поиска
	void signal_getTable(QString nameTable, QString nameColumn, QString searchText);
	/// \brief Запрос сохранить связь
	/// \param Link, структура цепи
	void signal_SaveLink(TSTRLINKPOINT Link);
	/// \brief Запрос сохранить точку
	/// \param Point, структура точки
	void signal_SavePoint(TSTRPCONNECTION Point);
	/// \brief Запрос удалить запись
	/// \param id, номер записи
	/// \param nameTable, имя таблицы
	void signal_DeleteRecord(int id, QString nameTable);
	/// \brief Запрос добавить точку в БД
	/// \param point, струтктура точки
	void signal_addPoint(TSTRPCONNECTION point);
	/// \brief Запрос добавить цепь в БД
	/// \param link, структура цепи
	void signal_addLink(TSTRLINKPOINT link);

public slots:
	/// \brief Слот отображения ошибки
	/// \param str, текст ошибки
	void slot_ErrorDB(QString str);
	/// \brief Слот установки пути БД на гуи
	/// \param path, путь к БД
	void slot_setPathDB(QString path);
	/// \brief Слот получения таблицы цепей на Гуи
	/// \param linksTable, вектор цепей
	void slot_sentTable(QVector<TSTRLINKPOINT> linksTable);
	/// \brief Слот получения таблицы точек на Гуи
	/// \param pointTable, вектор точек
	void slot_sentTable(QVector<TSTRPCONNECTION> pointTable);
	/// \brief Слот успешного сохранения записи
	void slot_saveOK();

private slots:
	/// \brief Слот изменения БД
	void on_changeBD_clicked();
	/// \brief Слот изменения имени таблицы
	/// \param index, индекс списка
	void on_nameTable_currentIndexChanged(int index);
	/// \brief Слот сохранение записи
	void on_saveRecord_clicked();
	/// \brief Слот выбор строки
	/// \param row, номер строки
	/// \param column, номер столбца
	void on_tableWidget_cellClicked(int row, int column);
	/// \brief Слот удаление записи
	void on_deleteRecord_clicked();
	/// \brief Слот добавления записи
	void on_addRecord_clicked();
	/// \brief Добавить точку
	/// \param point, структура точки
	void slot_addPoint(TSTRPCONNECTION point);
	/// \brief Добавить Цепь
	/// \param link, струтктура цепи
	void slot_addLink(TSTRLINKPOINT link);
	/// \brief Слот включения поиска
	/// \param checked, флаг активности поиска
	void on_groupBox_3_clicked(bool checked);
	/// \brief Слот изменения строки поиска
	/// \param arg1, строка поиска
	void on_lineSearch_textChanged(const QString &arg1);
	/// \brief	Слот сохранения БД
	void on_creatNewBD_clicked();
	/// \brief Слот удаления бд
	void on_deletBD_clicked();
	/// \brief Слот изменения таблицы
	/// \param index, индекс таблицы
	void on_tabWidget_currentChanged(int index);

private:
	Ui::wDatabase *ui;          ///< Указатель на гуи

	int rowSelected;            ///< Выбранная строка
	QMovie *movie;              ///< Модуль анимации
	QLabel *movieLabel;         ///< Модуль показа анимации

	/// \brief Функция подготавливает таблицу
	void prepareTable();
	/// \brief Функция запрос таблицы
	void getTable();

protected:
	/// \brief Событие показа виджета
	void showEvent(QShowEvent *event);
	/// \brief Событие изменение размера виджета
	void resizeEvent(QResizeEvent *event);
};
//-----------------------------------------------------------
#endif // WDATABASE_H
//-----------------------------------------------------------
