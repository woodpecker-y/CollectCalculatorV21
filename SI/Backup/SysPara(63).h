/*  
***************************************************************
*****************Tools Version 20161020************************
* @copy  COPYRIGHT 2016 Foryon  
*
* @file :
* @version :
* @function :
* 
* 
* 
* 
* 
* 
* @brief :
* 
* 
* 
*
* @author :��ΰ
* @date :2017/8/28 15:11
***************************************************************
*/ 
#ifndef _SYSPARA_H_
#define _SYSPARA_H_
 

#include "TypeDef.h"
#include "PubDef.h"

#include "W25QXX.H"
#include "RTC.H"
 
#ifdef _SYSPARA_C_
#define SYSPARA_EXT
#else
#define SYSPARA_EXT extern
#endif
 




//*****************************************************************************************
//ϵͳ����������

//����ϵͳ��������ģ��
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	INT32U	Reserved0[10];			//Ԥ���ռ�
	INT32U	Device_BU;				//�豸����������ڣ����ڸ���	
	INT32U	Device_SN;				//�豸������ţ�Ҳ����ͨ�ź���			
	INT32U	Apportion_T;			//��̯���� ��λ ����			
		
	INT16U	BuldMeterNum;			//¥��������		
	INT16U	UserNum;				//�û�������
	INT16U	DevNum;				    //�û��豸������
	INT16U	DevNum_T;				//ϵͳ���豸����
	
	INT8U	IP1;					//��վIP��ַ1		
	INT8U	IP2;					//��վIP��ַ2			
	INT8U	IP3;					//��վIP��ַ3			
	INT8U	IP4;					//��վIP��ַ4			
	INT16U	PortNum;				//��վ�˿ں�

	INT8U	ReaportType;			//�û������Զ��ϱ�����
	INT16U	ReportSpace;			//�û����ݼ���ϱ������λ ����
	INT16U	ReportClock;			//��ʱ�ϱ�ʱ��� ÿ(1 2 3 4 6 8 12)Сʱ�����ϱ�

	
	
	INT8U	GPRS_COM;			//GPRSͨ�Ŷ˿�			
	INT8U	MBUS_COM;			//MBUSͨ�Ŷ˿�
	INT8U	RF_BUS_COM;			//��Ƶ��ͨ�Ŷ˿�

	
	INT16U	PassWord;				//��������			
	INT8U	DeviceType;			//�豸����  ������������
	
	RealClock_Str	StartTime;			//��ů��ʼʱ��
	RealClock_Str 	FinalTime;			//��ů����ʱ��



	INT32U	SendMode;				//�豸�����ϱ�ģʽ
	INT32U	ReadSpace;				//�豸ͨ�ż��ʱ��
	INT32U	SendSpace;				//�豸����ѭ���ϱ����ʱ��


	INT32U	DebugEnable;			//ϵͳ����ʹ�ܱ�־
	INT32U	DebugLevel;			//ϵͳ������Ϣ��ӡ����
	
	INT32U	LoopSpace;				//�豸ѭ�����ռ��ʱ��	  ���������豸֮���ͨ���л�ʱ��


	INT16U	RelayRecord; 			//�������·�̵���״̬��¼

	INT8U	Reserved[1018];			//Ԥ���ռ�	

	
	INT8U	CRC16H;//CRCУ��
	INT8U	CRC16L;//CRCУ��
}SysPara_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

SYSPARA_EXT SysPara_Stru SysPara;




//����ϵͳ�ϵ��������ģ��
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	INT16U	Year;
	INT8U	Month;
	INT8U	Day;
	INT8U	Hour;
	INT8U	Minute;
	INT8U	Second;	
	INT32U	Times;
	
	INT8U	CRC16H;//CRCУ��
	INT8U	CRC16L;//CRCУ��
}PowerState_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

SYSPARA_EXT PowerState_Stru PowerStateRecord;

HAL_StatusTypeDef PowerStateRecord_Init(void);
HAL_StatusTypeDef PowerStateRecord_Update(void);



//����ϵͳ�ϵ��������ģ��
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	HAL_StatusTypeDef	Dev_ComStatus;		//ϵͳ�豸ͨ��״̬
	HAL_StatusTypeDef	ShareFlag;			//��̯���Ʊ�־   ���ڱ��ϵͳ�ϵ���Ƿ��������������̯
	INT32U			LoopCtrler;			//ѭ��������
	HAL_StatusTypeDef	Syspara;			//ϵͳ����״̬
	HAL_StatusTypeDef	Userpara;			//�û�����״̬
	HAL_StatusTypeDef	Devpara;			//�豸����״̬

	
}SysState_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�



SYSPARA_EXT SysState_Stru SysStatus;			//ϵͳ״̬









 
#ifdef _SYSPARA_C_




#endif
 


SYSPARA_EXT HAL_StatusTypeDef SysPara_Init(void);
SYSPARA_EXT HAL_StatusTypeDef SysPara_Update(void);
SYSPARA_EXT HAL_StatusTypeDef SysPara_Reset(void);
SYSPARA_EXT HAL_StatusTypeDef GetDeviceNum(INT16U UserNum, SysDEV_Type TypeID,INT16U* Num);



#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
