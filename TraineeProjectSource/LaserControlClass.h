#pragma once
#include "DataLaserStruct.h"
#include <qvector.h>
#include "CommonLaserInterfaceClass.h"
#include "LaserPilotInterfaceClass.h"
#include "LaserPowerInterfaceClass.h"
#include "LaserPointerInterfaceClass.h"
#include "functional"
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

	CommonLaserInterfaceClass* LPilot1;
	CommonLaserInterfaceClass* LPilot2;
	CommonLaserInterfaceClass* LPilot3;

	CommonLaserInterfaceClass* LaserPointer;

	QTimer TimerToIterateLasers;
	QVector<CommonLaserInterfaceClass*> Lasers;
	quint8 LaserIterateCounter = 0;

	public slots:
	void IterateWorkingLaser();
	void SlotSwitchFireBeam(bool OnOff);
	void SlotSwitchPointerBeam(bool OnOff);
	void SlotSwitchPilotBeam(int Channel, bool OnOff);
	//void SlotSetBeamModulationFrequency(int Frequency);

	void SlotSwitchAllLasers(bool OnOff);
	void SlotStartIterateLasers(bool OnOff);
signals:
	void SignalTurnLaser1(bool OnOff);
	void SignalTurnLaser2(bool OnOff);
	void SignalTurnLaser3(bool OnOff);

};