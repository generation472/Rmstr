//--------------------------------------------------------
#ifndef PROC_H
#define PROC_H
//--------------------------------------------------------
#include <QObject>
#include <QDir>
#include "xlsxdocument.h"
#include "csys.h"

using namespace QXlsx;
//--------------------------------------------------------
/**
	\class Proc
	\brief Класс модуля протоколов.<br>
		<h2>Модуль создания протоколов проверки.</h2><br>
	Модуль реализует следующий функционал:<br>
		- Создание протокола
		- Запись данных в протокол
	<br>
*/
class Proc : public QObject
{
	Q_OBJECT
public:
	/// \brief Конструктор
	/// \param parent, указатель на объект родитель
	explicit Proc(QObject *parent = nullptr);
	/// \brief Деструктор
	~Proc();

	/// \brief Функция создаёт новый файл протокола
	/// \param name, имя протокола
	/// \param techNumber, технологический номер
	void newProc(QString name, QString techNumber);
	/// \brief Функция записывает запись в документ
	/// \param link, структура цепи
	/// \param Im, измеренное значение параметра
	/// \param Sec, измеренное значение дополнительного параметра
	void insertLink(TSTRLINKPOINT link, QString Im, QString Sec);

private:
	QString nameDir;	///< Имя каталога
	QString nameDoc;	///< Имя документа
	int IdRow;				///< Номер строки для записи
	int idNewDoc;			///< Индекс для повторяющихся документов
	int countRemove;	///< Количество символов для удаления

	/// \brief Функция создания имени документа
	void checkNameDoc();
signals:

public slots:
};
//--------------------------------------------------------
#endif // PROC_H
//--------------------------------------------------------
