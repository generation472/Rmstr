//----------------------------------------------------------
#ifndef WAUTOCONTROL_H
#define WAUTOCONTROL_H
//----------------------------------------------------------
#include <QWidget>
#include "csys.h"
#include "xlsxdocument.h"
//----------------------------------------------------------
using namespace QXlsx;
//----------------------------------------------------------
namespace Ui {
class wAutoControl;
}
//----------------------------------------------------------
/**
	\class wAutoControl
	\brief Класс виджет автоматической проверки.<br>
		<h2>Виджет отображения автоматической проверки.</h2><br>
	Виджет реализует следующие функции
		- Отображение процесса автоматической проверки
		- Отображение неисправных цепей
		- Сохранение несправных цепей

*/
class wAutoControl : public QWidget
{
	Q_OBJECT

public:
	/// \brief Конструктор
	/// \param parent, указатель на виджет родитель
	explicit wAutoControl(QWidget *parent = 0);
	/// \brief Деструктор
	~wAutoControl();

signals:
	/// \brief Сигнал управления автопроверкой
	/// \param status, статус автоматической проверки
	void signal_setStatusAutoControl(TSTATUSAUTOCHECK status);

	/// \brief Запрос проверки оборудования
	void signal_checkDeviceA();

public slots:
	/// \brief статус подключения оборудования
	/// \param status, статус оборудования
	void slot_statusDeviceA(TSTATUSDEVICE status);
	/// \brief Слот, результат проверки цепи
	/// \param link, струтктура цепи
	/// \param Im, измеренное значение
	/// \param Sec, дополнительный измереный параметр
	/// \param check, флаг проверки
	void slot_sentResult(TSTRLINKPOINT link, double Im, double Sec, bool check);
	/// \brief Слот статуса проверки
	/// \param status, статус автоматической проверки
	void slot_statusAutoCheck(TSTATUSAUTOCHECK status);
	/// \brief Установка размерности прогресс бара
	/// \param max, максимальное значение прогресс бара
	void slot_setRangeProgressBar(int max);
private slots:
	/// \brief Слот нажатие кнопки Старт
	void on_pbStart_clicked();
	/// \brief Слот нажатие кнопки Пауза
	void on_pbPause_clicked();
	/// \brief Слот нажатие кнопки Стоп
	void on_pbStop_clicked();
	/// \brief Слот нажатие кнопки "Сохранить"
	void on_pushButton_2_clicked();

private:
	Ui::wAutoControl *ui;		///< Указатель на форму класса
};
//----------------------------------------------------------
#endif // WAUTOCONTROL_H
//----------------------------------------------------------
