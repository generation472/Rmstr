//---------------------------------------------------
#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H
//---------------------------------------------------
#include <QWidget>
//---------------------------------------------------
/**
	\class SwitchButton
	\brief Класс виджет кнопки.<br>
		<h2>Виджет реализует отображение кнопки</h2><br>

*/
class SwitchButton : public QWidget
{
	Q_OBJECT
public:
	/// \brief Конструктор
	/// \param parent, указатель на виджет родитель
	explicit SwitchButton(QWidget *parent = nullptr);

	/// \brief Установка флага
	/// \param fl, статус
	void setSwitch(bool fl);

private:
	bool m_switch;			///< Состояние кнопки
	QSize sizeWidget;		///< Размер виджета
signals:
	/// \brief Сигнал изменения состояния кнопки
	/// \param m_switch, состояние
	void signal_clicked(bool m_switch);
public slots:


protected:
	/// \brief Событие рисование кнопки
	void paintEvent(QPaintEvent *event);
	/// \brief Событие нажатие кнопки
	void mouseReleaseEvent(QMouseEvent *event);
};
//---------------------------------------------------
#endif // SWITCHBUTTON_H
//---------------------------------------------------
