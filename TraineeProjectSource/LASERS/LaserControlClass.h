#pragma once
#include "DataLaserStruct.h"
#include <qvector.h>
#include "LaserCommonInterface.h"
//#include "functional"
#include <QTimer>



class LaserControlClass: public QObject
{
	Q_OBJECT
public:
	LaserControlClass();
    ~LaserControlClass();
	typeblocksenum TypeBlock = typeblocksenum::LasersBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;


	QVector<DataLaserStruct> GetLasersState();

	LaserCommonInterface* LPilot1;
	LaserCommonInterface* LPilot2;
	LaserCommonInterface* LPilot3;
	LaserCommonInterface* LPower1;
	LaserCommonInterface* LPower2;
	LaserCommonInterface* LPower3;

	LaserCommonInterface* LaserPointer;

	QTimer TimerToIterateLasers;
	QVector<LaserCommonInterface*> Lasers;
	quint8 LaserIterateCounter = 0;


	public slots:
	void IterateWorkingLaser();
	void SlotSwitchPointerBeam(bool OnOff);
	void SlotSwitchPowerBeam(int Channel, bool OnOff);
	void SlotSwitchPilotBeam(int Channel, bool OnOff);

	void SlotSwitchAllLasers(bool OnOff);
	void SlotStartIterateLasers(bool OnOff);
signals:
	void SignalTurnLaser1(bool OnOff);
	void SignalTurnLaser2(bool OnOff);
	void SignalTurnLaser3(bool OnOff);

};