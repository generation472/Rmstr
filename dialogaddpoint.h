//-------------------------------------------------------
#ifndef DIALOGADDPOINT_H
#define DIALOGADDPOINT_H
//-------------------------------------------------------
#include <QDialog>
#include "csys.h"
//-------------------------------------------------------
namespace Ui {
class dialogAddPoint;
}
//-------------------------------------------------------
/**
	\class dialogAddPoint
	\brief Класс диалог дабовления точки.<br>
		<h2>Диалог для добавления точек в БД</h2><br>
	Диалог реализует провверку вводных данных и добавление их в БД.
*/
class dialogAddPoint : public QDialog
{
	Q_OBJECT

public:
	/// \brief Конструктор
	/// \param parent, указатель на виджет родитель
	explicit dialogAddPoint(QWidget *parent = 0);
	/// \Деструктор
	~dialogAddPoint();

	TSTRPCONNECTION point;

signals:
		/// \brief Сигнал запроса добавить точку
		/// \param point, структура точки
		void signal_addPoint(TSTRPCONNECTION point);

private slots:
	/// \brief Нажатие кнопки добавить
	void on_pushButton_clicked();
	/// \brief Нажатие кнопки отмена
	void on_pushButton_2_clicked();

private:
	Ui::dialogAddPoint *ui;	///< Указатель точки


	// QWidget interface
protected:
	void showEvent(QShowEvent *event);
};
//-------------------------------------------------------
#endif // DIALOGADDPOINT_H
//-------------------------------------------------------
