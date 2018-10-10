//----------------------------------------------------------------------------
#ifndef RM_STR_H
#define RM_STR_H
//----------------------------------------------------------------------------
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QLabel>
//----------------------------------------------------------------------------
namespace Ui {
class RM_STR;
}
//----------------------------------------------------------------------------
#include "shedulerstr.h"
#include "devicestr.h"
#include "indicator.h"
#include "dialogsettings.h"
//----------------------------------------------------------------------------
/**
	\class  RM_STR
	\brief Главный класс приложения RM_STR<br>

	<h2>Главный клас приложения, наследуется от класса QMainWindow и содержит следующие элементы:</h2><br>
		- Меню программы
		- Панель инструментов (Tool bar)
		- Строка состояния (Status bar)
		- Центральный виджет
	<br>
		Основной задачей модуля является отображение визульных модулей и создание связей между функциональными модулями.<br>
		На центральный виджет установлен QStackedWidget, для реализации переключения модулей.<br>

	\version v.1.4.8
*/
class RM_STR : public QMainWindow
{
	Q_OBJECT

public:
	/// \brief Конструктор
	explicit RM_STR(QWidget *parent = 0);
	/// \brief Деструктор
	~RM_STR();


signals:
	/// \brief Сигнал изменения технологического номера
	/// \param number, технологический номер
	void signal_changeTechNumber(QString number);

	/// \brief Сигнал создать Qserialport для RLC
	void signal_creatQSerialPort();

	/// \brief Сигнал Включить/выключить RLC
	/// \param sw, флаг состояния оборудования
	void signal_switchRLC(bool sw);


private:
	Ui::RM_STR *ui;								///< Указатель на ui

	DeviceSTR *deviceSTR;					///< Модуль управления оборудование STR
	QThread thread;								///< Поток для deviceSTR
	ShedulerSTR *shedulerSTR;			///< Основной модуль работы пульта STR

	dialogSettings dSettings;			///< Объект настроек программы

	Indicator *indicatorBD;				///< Виджет индикатор БД
	QLabel *labelStatusDB;				///< Лабел индикатор БД

	QMovie *movie;              ///< Модуль анимации
	QLabel *movieLabel;         ///< Модуль показа анимации

	/// \brief Установка стилей
	void setStyleRm_STR();
private slots:
	/// \brief Слот работы RLC
	/// \param f, флаг состояния оборудования
	void slot_enableRLC(bool f);
	/// \brief Слот нажатия экшена Ручная проверка
	void on_manualCheck_triggered();
	/// \brief Слот нажатия экшена Автоматическая проверка
	void on_autoCheck_triggered();
	/// \brief Слот нажатия экшена Протокол
	void on_protocolCheck_triggered();
	/// \brief Слот нажатия экшена Настройка и редактирование БД
	void on_manageDB_triggered();
	/// \brief Слот нажатие кнопки "О программе"
	void on_action_triggered();
	/// \brief Слот нажатия кнопки "Настройка и оборудование"
	void on_action_2_triggered();
	/// \brief Слот нажатия кнопки включения/выключения RLC
	void slot_switchRLC(bool sw);
	/// \brief Слот нажатия кнопки включения/выключения SPI
	void slot_switchSPI(bool sw);
	/// \brief Слот нажатия кнопки выход
	void on_exit_triggered();
	/// \brief Слот изменения технологического номера
	/// \param arg1, технологический номер
	void on_lineTechNumber_textEdited(const QString &arg1);
	/// \brief Слот оповещения
	void slot_alert();

	// QWidget interface
protected:
	void resizeEvent(QResizeEvent *event);
};
//----------------------------------------------------------------------------
#endif // RM_STR_H
//----------------------------------------------------------------------------
