/******************************************************************************
  IPG Laser GmbH
  COPYRIGHT (c) 2006 IPG Laser GmbH ALL RIGHTS RESERVED
  This program may not be reproduced, in whole or in part in any
  form or any means whatsoever without the written permission of:

  IPG Laser GmbH
  Germany, 57299 Burbach, Siemensstrasse, 7.
  Tel: +49(0)2736-44200
  Fax: +49(0)2736-4420160

  IPG Photonics Corporation
  50 Old Webster Road 
  Oxford, MA 01540, USA 

  Project:            Laser_DLL (MFC)
  Filename:           HplEiEx.h
  Description:        
  Author:             Andrei Kukovinets
  Created:            11.05.2006
******************************************************************************/
#ifndef HPLEIEX_H
#define HPLEIEX_H
//-----------------------------------------------------------------------------
#define HEE_FUNCTION_NO_ERROR      0
#define HEE_INVALID_LASER_HANDLE  -1
#define HEE_FUNCTION_ERROR		  -2
//-----------------------------------------------------------------------------
uint16_t	Laser_Create();
int  	Laser_Delete( uint16_t dwLaser );
int		Laser_ConnectTo( uint16_t dwLaser, LPCSTR pszIpAddr, int iPort, uint16_t dwTimeOut );
int 	Laser_Disconnect( uint16_t dwLaser );
int		Laser_GetConnectionState( uint16_t dwLaser );

int 	Laser_UpdateLaserParam( uint16_t dwLaser );
int	    GetLP_Version( uint16_t dwLaser );
int 	GetLP_LaserType( uint16_t dwLaser );
char *  GetLP_LaserID( uint16_t dwLaser );
char *	GetLP_LaserSN( uint16_t dwLaser );
WORD	GetLP_Firmware1Version( uint16_t dwLaser );
WORD	GetLP_Firmware2Version( uint16_t dwLaser );
WORD	GetLP_Firmware3Version( uint16_t dwLaser );
WORD	GetLP_Firmware4Version( uint16_t dwLaser );
uint16_t	GetLP_LaserConfig( uint16_t dwLaser );
uint16_t	GetLP_LaserConfig2( uint16_t dwLaser );
uint16_t	GetLP_LaserConfig3( uint16_t dwLaser );
int		GetLP_LaserMode( uint16_t dwLaser );
int 	GetLP_Modules( uint16_t dwLaser );
float	GetLP_MaxPower( uint16_t dwLaser );
int		GetLP_BeamSwitchType( uint16_t dwLaser );
int 	GetLP_OpticalChannels( uint16_t dwLaser );
int 	GetLP_HardwiringVersion( uint16_t dwLaser );
int 	GetLP_HardwiringModules( uint16_t dwLaser );
int 	GetLP_LaserNumber( uint16_t dwLaser );
uint8_t*	GetLP_OpticalPath( uint16_t dwLaser );
int 	GetLP_MaxRampingTime( uint16_t dwLaser );
int 	GetLP_MaxLaserPrograms( uint16_t dwLaser );
int 	GetLP_MaxLaserProgramCommands( uint16_t dwLaser );
int		GetLP_ChillerType( uint16_t dwLaser );
int		GetLP_ChillerTemp1Min( uint16_t dwLaser );
int		GetLP_ChillerTemp1Max( uint16_t dwLaser );
int		GetLP_ChillerTemp2Min( uint16_t dwLaser );
int		GetLP_ChillerTemp2Max( uint16_t dwLaser );
uint16_t	GetLP_ModReservedDef_L( uint16_t dwLaser );
uint16_t	GetLP_ModReservedDef_H( uint16_t dwLaser );
int		GetLP_FieldBusProtocolType( uint16_t dwLaser );
int		GetLP_FreqSyntMin( uint16_t dwLaser );
int		GetLP_FreqSyntMax( uint16_t dwLaser );

int	    GetLS_Version( uint16_t dwLaser );
float   GetLS_SetCurrent( uint16_t dwLaser );
float	GetLS_SetPower( uint16_t dwLaser );
float   GetLS_OutputPower( uint16_t dwLaser );
float	GetLS_SumOutputPower( uint16_t dwLaser );
float   GetLS_Temp( uint16_t dwLaser );
float   GetLS_TempMax( uint16_t dwLaser );
float   GetLS_TempMin( uint16_t dwLaser );
int	    GetLS_TempMaxModNum( uint16_t dwLaser );
int	    GetLS_TempMinModNum( uint16_t dwLaser );
float	GetLS_PCBTemp( uint16_t dwLaser );
uint16_t   GetLS_Status( uint16_t dwLaser );
uint16_t	GetLS_Status2( uint16_t dwLaser );
uint16_t   GetLS_Alarms( uint16_t dwLaser );
uint16_t	GetLS_Alarm2( uint16_t dwLaser );
uint16_t   GetLS_Warnings( uint16_t dwLaser );
__int64 GetLS_WorkTime( uint16_t dwLaser );
__int64 GetLS_EmissionTime( uint16_t dwLaser );
int	    GetLS_WorkTimeToday( uint16_t dwLaser );
int	    GetLS_EmissionTimeToday( uint16_t dwLaser );
WORD*	GetLS_PowerSupplyStatus( uint16_t dwLaser );
float*	GetLS_PowerSupplyCurrent( uint16_t dwLaser );
float*	GetLS_PowerSupplyVoltage( uint16_t dwLaser );
float*	GetLS_PowerSupplyTemp( uint16_t dwLaser );
float	GetLS_WaterFlow( uint16_t dwLaser );
uint16_t   GetLS_ModUnconnected_L( uint16_t dwLaser );
uint16_t   GetLS_ModUnconnected_H( uint16_t dwLaser );
uint16_t   GetLS_ModFail_L( uint16_t dwLaser );
uint16_t   GetLS_ModFail_H( uint16_t dwLaser );
uint16_t   GetLS_ModReserved_L( uint16_t dwLaser );
uint16_t   GetLS_ModReserved_H( uint16_t dwLaser );
uint16_t   GetLS_ModDisable_L( uint16_t dwLaser );
uint16_t   GetLS_ModDisable_H( uint16_t dwLaser );
uint16_t   GetLS_ModFatalDisabled_L( uint16_t dwLaser );
uint16_t   GetLS_ModFatalDisabled_H( uint16_t dwLaser );
float   GetLS_ChillerTemp1( uint16_t dwLaser );
float   GetLS_ChillerTemp2( uint16_t dwLaser );
float   GetLS_ChillerConductivity( uint16_t dwLaser );
uint16_t   GetLS_ChillerStatus( uint16_t dwLaser );
int	    GetLS_RiseTime( uint16_t dwLaser );
int	    GetLS_FallTime( uint16_t dwLaser );
int	    GetLS_ProgramNumber( uint16_t dwLaser );
int	    GetLS_ProgramEndCode( uint16_t dwLaser );
int	    GetLS_ProgramLineWithError( uint16_t dwLaser );
int	    GetLS_BeamSwitchSetChannel( uint16_t dwLaser );
WORD*	GetLS_BeamSwitchState( uint16_t dwLaser );
WORD*   GetLS_BeamSwitchScatteredLight( uint16_t dwLaser );
int	    GetLS_BeamSwitchScatteredLightAlarms( uint16_t dwLaser );
uint16_t   GetLS_ProtectGlassWarning( uint16_t dwLaser );
uint16_t   GetLS_ProtectGlassAlarm( uint16_t dwLaser );
SYSTEMTIME*	GetLS_LaserTime( uint16_t dwLaser );
int	    GetLS_HardwiringFirstNum( uint16_t dwLaser );
int	    GetLS_HardwiringActiveNum( uint16_t dwLaser );
uint16_t*  GetLS_HardwiringOutput( uint16_t dwLaser );
uint16_t*  GetLS_HardwiringInput( uint16_t dwLaser );
int		GetLS_FieldbusState( uint16_t dwLaser );
int		GetLS_FieldbusError( uint16_t dwLaser );
WORD*   GetLS_FieldbusInputs( uint16_t dwLaser );
WORD*   GetLS_FieldbusOutputs( uint16_t dwLaser );
int		GetLS_UControl( uint16_t dwLaser );
int		GetLS_SetFreqSynt( uint16_t dwLaser );
int		GetLS_MeasFreqSynt( uint16_t dwLaser );
float	GetLS_SetDutyCycle( uint16_t dwLaser );
float	GetLS_MeasDutyCycle( uint16_t dwLaser );

int		Laser_GuideLaserOn( uint16_t dwLaser, int iNum, BOOL bGL );
int		Laser_PowerOn( uint16_t dwLaser, BOOL bPowerOn );
int		Laser_SetCurrent( uint16_t dwLaser, float fIld );
int		Laser_SetPower( uint16_t dwLaser, float fPwr );
int		Laser_SetBeamSwitchChannel( uint16_t dwLaser, int iChannel );
int		Laser_EmissionOn( uint16_t dwLaser, BOOL bEmission );
int		Laser_AnalogOn( uint16_t dwLaser, BOOL bAnalog );
int		Laser_ExternalOn( uint16_t dwLaser, BOOL bExternal );
int		Laser_LaserReset( uint16_t dwLaser );
int		Laser_DeleteEvents( uint16_t dwLaser );
int		Laser_SetRiseTime( uint16_t dwLaser, UINT nRiseTime );
int		Laser_SetFallTime( uint16_t dwLaser, UINT nFallTime );
char*	Laser_GetLogFilesList( uint16_t dwLaser, const char* szPath );
int		Laser_GetLogFile( uint16_t dwLaser, const char* szPath, const char* szPathForSave );
int	    Laser_GetIPConfig( uint16_t dwLaser, uint16_t* pAddr, uint16_t* pMask, uint16_t* pGateway );
int	    Laser_SetIPConfig( uint16_t dwLaser, uint16_t dwAddr, uint16_t dwMask, uint16_t dwGateway );
int	    Laser_GetResetCriticalErrorsCodeNum( uint16_t dwLaser );
int	    Laser_ResetCriticalErrors( uint16_t dwLaser, __wchar_t const* szCode );
int		Laser_SetFieldBusByteOrder( uint16_t dwLaser, BOOL bFieldBusByteOrder);
int		Laser_SetQCWMode( uint16_t dwLaser, BOOL bQCWMode );
int		Laser_SetFreq( uint16_t dwLaser, uint16_t dwFreq );
int		Laser_ReadLaserProgram( uint16_t dwLaser, int iNumber, WORD* pBuffer, int iSize );
int		Laser_WriteLaserProgram( uint16_t dwLaser, int iNumber, WORD* pBuffer );
int		Laser_StartLaserProgram( uint16_t dwLaser, int iNumber );
int		Laser_StopLaserProgram( uint16_t dwLaser );
int		Laser_EnableEventsAccumulate( uint16_t dwLaser, BOOL bAccum );
HANDLE	Laser_GetReceiveSystemEvent( uint16_t dwLaser );
int		Laser_GetEventsCount( uint16_t dwLaser );
int		Laser_GetEvents( uint16_t dwLaser,uint16_t *dwBuffer, int iSize );
int		Laser_ReadLastEvents( uint16_t dwLaser, SYSTEMTIME* pTime );
int		Laser_GetLastEvents( uint16_t dwLaser, uint16_t * dwBuffer, int iSize );
int     Laser_DeleteEvents( uint16_t dwLaser );
int		Laser_GetInfoEventsState( uint16_t dwLaser );
int		Laser_SetInfoEventsState( uint16_t dwLaser, BOOL bEnable );
int		Laser_SetNumbers( uint16_t dwLaser, uint8_t* pLN );
int		Laser_SetTime( uint16_t dwLaser, SYSTEMTIME* pTime );
int		Laser_DisableModules( uint16_t dwLaser, uint16_t* dw );
int		Laser_GetInterbusInfo( uint16_t dwLaser, WORD* pIbi, int iSize );
//-----------------------------------------------------------------------------
#endif //HPLEIEX_H
//-----------------------------------------------------------------------------
