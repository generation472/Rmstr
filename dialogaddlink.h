//----------------------------------------------------------
#ifndef DIALOGADDLINK_H
#define DIALOGADDLINK_H
//----------------------------------------------------------
#include <QDialog>
#include "csys.h"
//----------------------------------------------------------
namespace Ui {
class dialogAddLink;
}
//----------------------------------------------------------
/**
	\class dialogAddLink
	\brief Класс диалог дабовления цепи.<br>
		<h2>Диалог для добавления цепей в БД</h2><br>
	Диалог реализует провверку вводных данных и добавление их в БД.

*/
class dialogAddLink : public QDialog
{
	Q_OBJECT

public:
	/// \brief Конструктор
	/// \param parent, указатель на виджет родитель
	explicit dialogAddLink(QWidget *parent = 0);
	/// \brief Деструктор
	~dialogAddLink();

signals:
	/// \brief Сигнал запроса на добавление данных а БД
	/// \param link, структура цепи
	void signal_addLink(TSTRLINKPOINT link);

private slots:
	/// \brief Слот кнопки добавит
	void on_pushButton_clicked();
	/// \brief Слот кнопки отмена
	void on_pushButton_2_clicked();


private:
	Ui::dialogAddLink *ui; ///< Указатель форму класса
};
//----------------------------------------------------------
#endif // DIALOGADDLINK_H
//----------------------------------------------------------
