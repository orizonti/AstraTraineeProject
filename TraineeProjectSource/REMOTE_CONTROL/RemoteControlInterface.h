#pragma once
#include "typeblocksenum.h"
#include "stateblocksenum.h"
#include "PassTwoCoordClass.h"
#include "RotateOperationContainer.h"

#include <QTimer>
#include "HandleControlInterface.h"
#include "DataDeviceStructureCommon.h"
#include "DataWeatherStructure.h"
#include "DataChillerStructure.h"
#include "DataLaserStruct.h"
#include "DataEngineStructure.h"
#include "DataCamerasStructure.h"
#include "RemoteControlProtocol.h"
#include "UDPEngineInterface.h"

enum error_port_work_modes { aiming_mode = 1, registration_mode = 2};
enum error_port_direction  { direct_to_all = 0, direct_to_channel1 = 1, direct_to_channel2 = 2, direct_to_channel3 = 3 };
class RemoteAimingWindowControl;

class RemoteAimingHandleInterface
{
public:
virtual	void SlotResetRotationBlocks() = 0;
virtual	void SlotSetActiveChannel(int Channel) = 0;
virtual	void SlotLoadDataFromFile(QString FileName) = 0;
virtual	void SlotSetMode(int Mode) = 0;
};

class RemoteAimingInterface : public PassTwoCoordClass, public RemoteAimingHandleInterface
{
public:
	typeblocksenum TypeBlock = typeblocksenum::RecieveErrorBlock;
	stateblocksenum StateBlock = stateblocksenum::BlockDisable;
    error_port_work_modes work_mode = aiming_mode;
	error_port_direction error_direction = direct_to_channel1;

	RemoteAimingWindowControl* ErrorPortWindowControl = 0;

	QPair<double, double> GetCoord();
	void SetCoord(QPair<double, double> Coord);
	bool isValid();

	QPair<double, double> RemoteAimingCoord;

	RemoteAimingInterface();
	~RemoteAimingInterface();
private:

public:
	void SlotResetRotationBlocks();
	void SlotSetActiveChannel(int Channel);
	void SlotLoadDataFromFile(QString FileName);
	void SlotSetMode(int Mode);

public:	
	RotateOperationContainer RemoteToBaseTransform;
	//QSerialPort PortCommonTimeSystem;

};


class RemoteControlInterface : public QObject
{
	Q_OBJECT
	public: 
	RemoteControlInterface(HandleControlInterface* Interface, QObject* parent = 0);
	RemoteAimingInterface AimingPort;
    MessageStruct<STATE_STRUCT> DEVICE_STATE;

	private:
	QTimer timerSendState; 

	void SendExecutionReply(int Result);

    UDPEngineInterface* UDPInterface;
	HandleControlInterface* DeviceControl;

	friend void operator>>(const DataDeviceStructure&  DeviceData,  RemoteControlInterface& RemoteControl);
	friend void operator>>(const DataLaserStruct&      LaserData,   RemoteControlInterface& RemoteControl);
	friend void operator>>(const DataEngineStructure&  EngineData,  RemoteControlInterface& RemoteControl);
	friend void operator>>(const DataCamerasStructure& CamerasData, RemoteControlInterface& RemoteControl);
	friend void operator>>(const DataWeatherStructure& WeatherData, RemoteControlInterface& RemoteControl);
	friend void operator>>(const DataChillerStructure& ChillerData, RemoteControlInterface& RemoteControl);

    public slots:
	void SlotPerformRemoteCommand(KLP_CMD_TYPES CMD_TYPE);
	void SlotSendStateToRemote();
};