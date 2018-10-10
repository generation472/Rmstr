//-------------------------------------------------------------
#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H
//-------------------------------------------------------------
#include <QDialog>
#include <QSerialPortInfo>
//-------------------------------------------------------------
namespace Ui {
class dialogSettings;
}
//-------------------------------------------------------------
/**
	\class dialogSettings
	\brief Класс диалог настроек программы RM_STR.<br>
		<h2>Диалог для настройки программы RM_STR.</h2><br>
	Диалог содержит управлени слдеующими настройками:
		- Настройка порта для RLC-метра
		- Настройка выбора sub20
		- Настройка задержек проверки цепи
		- Настройка показа двух таблиц протоколов
		- Настройка уведомления неисправностей цепи

*/
class dialogSettings : public QDialog
{
	Q_OBJECT

public:
	/// \brief Конструктор
	/// \param parent, указатель на виджет родитель
	explicit dialogSettings(QWidget *parent = 0);
	/// \brief Деструктор
	~dialogSettings();

signals:
	/// \brief Сигнал для установки настроек звука и отображения таблицы
	/// \param table, флаг показа двух таблиц
	/// \param error, флаг включений уведомлений
	void signal_SetSettings(bool table, bool error);
	/// \brief Сигнал Запрос списка sub20
	void signal_getSubList();
	/// \brief Передача настроек
	/// \param numberSub, Имя sub20
	/// \param numberPort, Номер порта
	/// \param ms, Задержки в мс
	void signal_SetSettings(QString numberSub, QString numberPort, int ms);

public slots:
	/// \brief Слот установки списка sub20
	/// \param list, список sub20
	void slot_setSubList(QStringList list);
	/// \brief Слот для установки настроек звука и отображения таблицы
	/// \param table, флаг показа двух таблиц
	/// \param error, флаг включений уведомлений
	void slot_SetSettings(bool table, bool error);
	/// \brief Установка настроек
	/// \param numberSub, Имя sub20
	/// \param numberPort, Номер порта
	/// \param ms, Задержки в мс
	void slot_SetSettings(QString numberSub, QString numberPort, int ms);



private:
	Ui::dialogSettings *ui;	///< Указатель на форму класса

	QString numberSub;			///< Номер sub20
	QString numberPort;			///< Имя порта rs232
	int ms;									///< Задержки проверки цепи


protected:
	/// \brief Событие показа диалога
	void showEvent(QShowEvent *event);
private slots:
	/// \brief Слот нажатия кнопки "Ок"
	void on_pushButton_clicked();
	/// \brief Слот нажатия кнопки "Отмена"
	void on_pushButton_2_clicked();
};
//-------------------------------------------------------------
#endif // DIALOGSETTINGS_H
//-------------------------------------------------------------
