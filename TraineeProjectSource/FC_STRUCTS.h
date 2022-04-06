#include <qobject.h>

#pragma once
struct AsmHeader
{
	quint32 MessageId;
	quint32 DeviceID;
	quint32 Reserv1 = 0;
	union {
		struct {
			quint32 L : 1;      //���� ������� ����� ���� ������
			quint32 reserv : 7;
			quint32 Length : 24;	    // ����� ������ ���������
		};
		quint32 Reserv2 = 0;
	};



	friend void operator<<(QDataStream& out, AsmHeader& HEADER);
};


