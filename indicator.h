//---------------------------------------------------------
#ifndef INDICATOR_H
#define INDICATOR_H
//---------------------------------------------------------
#include <QWidget>
//---------------------------------------------------------
/**
   \class Indicator
	 \brief Класс виджет круглого индикатора.<br>
		<h2>Виджет реализует отображение круглого индикатора, красного и целёного цвета.</h2><br>
*/
class Indicator : public QWidget
{
    Q_OBJECT
public:
		/// \brief Конструктор
		/// \param parent, указатель на виджет родитель
    explicit Indicator(QWidget *parent = nullptr);
		/// \brief Деструктор
		~Indicator();

private:
		bool f_status;		///< Статус индикатора
public slots:
		/// \brief Слот изменения статуса
		/// \param fl, статус
    void slot_changeStatus(bool fl);


protected:
		/// \brief Событие рисования индикатора
    void paintEvent(QPaintEvent *event);


};
//---------------------------------------------------------
#endif // INDICATOR_H
//---------------------------------------------------------
