//-------------------------------------------------------------------------
#ifndef CSYS_H
#define CSYS_H
//-------------------------------------------------------------------------
#include <QObject>
//-------------------------------------------------------------------------
/// \brief Структура распаковки 2-х байт
struct t2Byte
{
	quint8 b1;		///< 1-ый байт
	quint8 b2;		///< 2-ой байт
};
//-------------------------------------------------------------------------
/// \brief Структура распаковки 4-х байт
struct t4Byte
{
	quint8 b1;		///< 1-ый байт
	quint8 b2;		///< 2-ой байт
	quint8 b3;		///< 2-ой байт
	quint8 b4;		///< 2-ой байт
};
//-------------------------------------------------------------------------
/// \brief Депак для распаковки данных
typedef union
{
	quint16 int16;
	quint32 int32;
	qint16 uint16;
	qint32 uint32;
	quint8 uint8;
	int dop;
	struct t4Byte str4b;
	struct t2Byte str2b;
}DEPACK;
//-------------------------------------------------------------------------
/// \brief Структура точки
typedef struct strPConnection
{
    int id;
    QString NamePoint;
    QString RG;
    QString CS;
    QString BusPlus;
}TSTRPCONNECTION;
//-------------------------------------------------------------------------
/// \brief Структура одной Цепи
typedef struct strLinkPoint
{
    int Id;
    QString NameLink;
    int IdPointPlus;
    int IdPointMinus;
    QString ModeCheck;
    QString MinValue;
    QString MaxValue;
    QString SecondValue;
}TSTRLINKPOINT;
//------------------------------------------------------------------
typedef enum
{
	S_OK = 0x01,
	S_N_OK = 0x02,
	S_RLC = 0x04,
	S_SUB20 = 0x08
}TSTATUSDEVICE;
//------------------------------------------------------------------
/// \brief Перечисление сатус авто-проверки
typedef enum
{
	S_BEGIN,
	S_PAUSE,
	S_CONTINUE,
	S_STOP
}TSTATUSAUTOCHECK;
//------------------------------------------------------------------
#endif // CSYS_H
//------------------------------------------------------------------
