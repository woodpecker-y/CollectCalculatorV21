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
* @date :2017/9/1 13:28
***************************************************************
*/ 
#ifndef _ALARMCLK_H_
#define _ALARMCLK_H_
 

#include"TypeDef.h"
#include"string.h"
#include "RTC.h"
#include "time.h"
#include "debug.h"

 
#ifdef _ALARMCLK_C_
#define ALARMCLK_EXT
#else
#define ALARMCLK_EXT extern
#endif
 



#define MaxAlarmClkNum	6		//�궨�����嶨ʱ�����
#define MAXALARMWAIT  10		//������ڶ�����Ϊ����ʱ��
typedef void (*AlarmClkCallBack)(void);



typedef enum
{
	 AlarmClk_Enable =(INT8U)0X01,
	 AlarmClk_Disable =(INT8U)0X00,
	 AlarmClk_Ready =(INT8U)0x02,
	 AlarmClk_NorReady =(INT8U)0x03
}AlarmClk_Enum;


typedef struct
{
	INT16U	Year;
	INT8U	Month;
	INT8U	Day;
	INT8U	Hour;
	INT8U	Minute;
	INT8U	MinuteDiv;	//��������
}AlarmTime_Stru;
 
 

typedef struct
{
	AlarmClk_Enum Enable;		//ʹ�ܱ�־
	AlarmClk_Enum	Ready;		//������־,����������ͬһ���������屻��δ���

	AlarmClk_Enum	MinuteType;	//�ظ�����������
	time_t repeatInterval;	//�ظ�����ʱ��ʱ��
	time_t	AlarmTime;		//��ʱʱ��

	AlarmClkCallBack Callback_Func;//�ص�����
	
}AlarmClk_Stru;


typedef AlarmTime_Stru (*SystemTimegeting)(void);	//ϵͳʵʱʱ���ȡ����ָ��



#ifdef _ALARMCLK_C_

AlarmTime_Stru	CurrentTime;		//ϵͳ��ǰʱ��
SystemTimegeting CurrentTimeget;	//��ȡ��ǰϵͳʱ�������

INT8U AlarmClkRecord;
AlarmClk_Stru AlarmClkManager[MaxAlarmClkNum];

#endif
 



ALARMCLK_EXT void AlarmClk_Init(void);
ALARMCLK_EXT AlarmClk_Stru* AlarmClk_CreatOne( AlarmClk_Enum Enable,AlarmClkCallBack F_callback,AlarmClk_Enum TypeEna,time_t interval);

ALARMCLK_EXT int AlarmClk_ParaSet( AlarmClk_Stru* Member, RealClock_Str *Parameters );
ALARMCLK_EXT void AlarmClk_EnableCtrl(AlarmClk_Stru* Member,AlarmClk_Enum Enable  );
ALARMCLK_EXT void AlarmClk_ExecutServer(void);
ALARMCLK_EXT void printAllAlarm(void);





 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
