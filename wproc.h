//-------------------------------------------------------------
#ifndef WPROC_H
#define WPROC_H
//-------------------------------------------------------------
#include <QWidget>
#include <QStringListModel>
#include "xlsxdocument.h"

using namespace QXlsx;
//-------------------------------------------------------------
namespace Ui {
class wProc;
}
//-------------------------------------------------------------
/**
	\class wProc
	\brief Класс виджет просмотра протокола.<br>
		<h2>Виджет для просмотра протоколов проверки.</h2><br>

*/
class wProc : public QWidget
{
	Q_OBJECT

public:
	/// \brief Конструктор
	/// \param parent, указатель на виджет родитель
	explicit wProc(QWidget *parent = 0);
	/// \brief Деструктор
	~wProc();



public slots:
	/// \brief Слот установки настроек таблицы
	/// \param fl, флаг настройки таблицы
	void slot_setSettingsTable(bool fl);

private slots:
	/// \brief Слот выбора документа
	/// \param index, индекс выбранного документа для первой таблицы
	void on_listView1_clicked(const QModelIndex &index);
	/// \brief Слот выбора документа
	/// \param index, индекс выбранного документа для второйй таблицы
	void on_listView2_clicked(const QModelIndex &index);
	/// \brief Слот удаление протоколов
	void on_pushButton_clicked();
	/// \brief Слот удаление протоколов
	void on_pushButton_3_clicked();
	/// \brief Слот открытие документов
	void on_pushButton_2_clicked();
	/// \brief Слот открытие документов
	void on_pushButton_4_clicked();

private:
	QString nameDir;			//< Имя папки
	QStringListModel m1;	//< Модель списка
	QStringListModel m2;	//< Модель списка

	QString choosenNameDoc1;	//< Выбраный документ
	QString choosenNameDoc2;	//< Выбраный документ

	/// \brief Функция поиска документов
	void searchDoc();
	/// \brief Функция показа второй таблицы
	/// \param f, флаг активности второй таблицы
	void setViewTwoTable(bool f);

	Ui::wProc *ui;	///< Указатель на форму класа

protected:
	/// \brief Событие показа формы
	void showEvent(QShowEvent *event);
};
//-------------------------------------------------------------
#endif // WPROC_H
//-------------------------------------------------------------
