//--------------------------------------------------------
#ifndef WMANUALCONTROL_H
#define WMANUALCONTROL_H
//--------------------------------------------------------
#include <QWidget>
#include "csys.h"
//--------------------------------------------------------
namespace Ui {
class wManualControl;
}
//--------------------------------------------------------
/**
	\class wManualControl
	\brief Класс виджет ручной проверки.<br>
		<h2>Виджет отображения ручной проверки.</h2><br>
	Виджет реализует следующие функции
		- Отображение процесса ручной проверки
		- Отображение результата проверки

*/
class wManualControl : public QWidget
{
	Q_OBJECT

public:
	/// \brief Конструктор
	/// \param parent, указатель на виджет родитель
	explicit wManualControl(QWidget *parent = 0);
	/// \brief Деструктор
	~wManualControl();

signals:
	/// \brief Запрос таблицы цепей
	void signal_getTableLink();
	/// \brief Провести измерение
	/// \param plus, название точки по шине плюся
	/// \param minus, название точки по шине минус
	void signal_checkLink(QString plus, QString minus);
	/// \brief Запрос на получения записей по поиску
	/// \param searchText, строка поиска
	void signal_getTableLink(QString searchText);
	/// \brief Запрос проверки оборудования
	void signal_checkDeviceM();

public slots:
	/// \brief Слот получения таблицы цепей на Гуи
	/// \param linksTable, вектор цепей
	void slot_sentTable(QVector<TSTRLINKPOINT> linksTable);

	/// \brief Слот, результат проверки
	/// \param Im, измеренное значение
	/// \param Sec, дополнительный измереный параметр
	/// \param check, флаг проверки
	void slot_sentResult(double Im, double Sec, bool check);

	/// \brief статус подключения оборудования
	/// \param status, статус подключёного оборудования
	void slot_statusDeviceM(TSTATUSDEVICE status);

private:
	Ui::wManualControl *ui;	///< Указатель на форму класса
	int rowSelected;		///< Выбранная строка

protected:
	/// \brief Событие показа формы
	void showEvent(QShowEvent *event);
private slots:
	/// \brief Слот выбора строки
	/// \param row, строка
	/// \param column, столбец
	void on_tableWidget_cellClicked(int row, int column);
	/// \brief Нажатие кнопки провести измерение
	void on_pushButton_clicked();
	/// \brief Слот изменения значения поиска
	/// \param arg1, строка поиска
	void on_lineEdit_textEdited(const QString &arg1);
};
//--------------------------------------------------------
#endif // WMANUALCONTROL_H
//--------------------------------------------------------
