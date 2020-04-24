/*  
***************************************************************
*****************Tools Version 20161020************************
* @copy  COPYRIGHT 2016 Foryon*******************************  
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
* @brief :���ļ�Ϊ��������ĳ���Դ�ļ�
* 
* ����  ��  ��  ��  ʱ  �� ��ƥ���� �����ص�����   ����  ��  ��   ��ʱ����Ϊ��ʱ ������ƥ������  

����
Alarm.Year =0;
Alarm.Month =0;
Alarm.Day =0;
Alarm.Hour =12
Alarm.Minute =15    //��ζ��ÿ���12:15���崥��


Alarm.Year =0;
Alarm.Month =0;
Alarm.Day =17
Alarm.Hour =12
Alarm.Minute =15    //��ζ��ÿ�µ�17.12:15 ���崥��




* 
*
* @author :��ΰ
* @date :2017/9/1 13:28
***************************************************************
*/ 
#define _ALARMCLK_C_
#include "AlarmClk.h"
 




/*
	�����������ģ���ʼ��
	@para  ϵͳʵʱʱ�ӻ�ȡ�ص������ҽ�
*/
void AlarmClk_Init(void)
{
	for(int Loop =0;Loop<MaxAlarmClkNum;Loop++)
	{
		AlarmClkManager[Loop].Enable =AlarmClk_Disable;
		AlarmClkManager[Loop].Ready = AlarmClk_NorReady;
		AlarmClkManager[Loop].Callback_Func = NULL;
		AlarmClkManager[Loop].AlarmTime = 0;
		AlarmClkManager[Loop].MinuteType = AlarmClk_Disable;	//Ĭ�Ϸ����������ܹر�
	}
}


/*

	����һ������ģ���Ա

	@Enable :ʹ�ܱ�־
	@F_callback :�ص�����ע��
	@ TypeEna:�������������� ʹ��
	@interval:���Ӵ������������
	

*/
AlarmClk_Stru* AlarmClk_CreatOne( AlarmClk_Enum Enable,AlarmClkCallBack F_callback,AlarmClk_Enum TypeEna,time_t interval)
{
	if(AlarmClkRecord >= MaxAlarmClkNum)
	{
		return NULL;
	}
	AlarmClkManager[AlarmClkRecord].Enable = Enable;
	AlarmClkManager[AlarmClkRecord].Ready = AlarmClk_Ready;
	AlarmClkManager[AlarmClkRecord].MinuteType = TypeEna;
	AlarmClkManager[AlarmClkRecord].repeatInterval = interval*60;
	AlarmClkManager[AlarmClkRecord].Callback_Func = F_callback;
	AlarmClkRecord ++;
	return &AlarmClkManager[AlarmClkRecord - 1];	
}




/*
ģ���Ա��ʱ��������
@��ʱʱ�����

*/
int AlarmClk_ParaSet( AlarmClk_Stru* Member, RealClock_Str *Parameters )
{
	time_t parm;
	int time_res;
	time_res = getTimeTick(&parm,Parameters);
	if(-1 == time_res)
	{
		dbg_printf(DEBUG_ERR,"�����������������������");
		return -1;
	}
	Member->AlarmTime = parm;
	return 0;
}


/*
ģ���Ա
ʹ��/��ֹ ����

*/
void AlarmClk_EnableCtrl( AlarmClk_Stru* Member,AlarmClk_Enum Enable )
{
	Member->Enable = Enable;
}


void AlarmClk_ExecutServer(void)
{

	time_t CurrentTime;

	CurrentTime = RTC_TimeTicks;						//��ȡ��ǰϵͳʱ��

	for (int LOOP =0;LOOP<AlarmClkRecord;LOOP++)
	{
		/* δ����ʱ�� */
		if(AlarmClkManager[LOOP].Enable != AlarmClk_Enable)
		{
			continue;
		}

		/* �Ѿ���������ʱ�� */
		if(AlarmClkManager[LOOP].Ready != AlarmClk_Ready)
		{
			continue;
		}

		/* ʱ�Ӵ��� */
		if(CurrentTime >= AlarmClkManager[LOOP].AlarmTime)
		{
			/* �ж��Ƿ�Ϊ����ʱ�� */
			if(CurrentTime - AlarmClkManager[LOOP].AlarmTime > MAXALARMWAIT)
			{
				/* ���ڵĵ���ʱ��ֱ�Ӻ��ԣ�����ʱ��ֱ�������¸����� */
				if(AlarmClkManager[LOOP].MinuteType == AlarmClk_Disable)
				{
					/* ��ͨһ����ʱ�� */
					AlarmClkManager[LOOP].Ready = AlarmClk_NorReady;
				}
				else
				{
					/* �ظ�ʱ�����õ���һ������ */
					AlarmClkManager[LOOP].AlarmTime = CurrentTime + AlarmClkManager[LOOP].repeatInterval - ((CurrentTime - AlarmClkManager[LOOP].AlarmTime)%AlarmClkManager[LOOP].repeatInterval);
				}
				continue;
			}
			
			/* �����崥�� */
			if(AlarmClkManager[LOOP].MinuteType == AlarmClk_Disable)
			{
				/* ��ͨһ����ʱ�� */
				AlarmClkManager[LOOP].Ready = AlarmClk_NorReady;
			}
			else
			{
				AlarmClkManager[LOOP].AlarmTime += AlarmClkManager[LOOP].repeatInterval;
			}
			
			/* ִ�����ӻص����� */
			if(AlarmClkManager[LOOP].Callback_Func != NULL)
			{
				(*AlarmClkManager[LOOP].Callback_Func)();
			}
		}
	}
	
}


 
void printAllAlarm(void)
{
	RealClock_Str real;
	
	for(int LOOP =0;LOOP<AlarmClkRecord;LOOP++)
	{
		/* δ����ʱ�� */
		if(AlarmClkManager[LOOP].Enable != AlarmClk_Enable)
		{
			continue;
		}

		/* ��ӡ��������״̬������*/
		getRealTime(&AlarmClkManager[LOOP].AlarmTime,&real);
		os_printf("Alarm at:%d-%02d-%02d-%02d:%02d:%02d %s\r\n",real.Year,real.Month,real.Day,real.Hour,real.Minute,real.Second,AlarmClkManager[LOOP].Ready == AlarmClk_Ready ? "Enabled" : "Disabled");
	}
}



 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
