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
* @brief :
* 
* 
* 
*
* @author :
* @date :2016-10-20 17:49
***************************************************************
*/ 
#define _PULSE_C_
#include "Pulse.h"

/*
* �������ƣ�Init_PaulseFunction(void)
* �������ܣ���ʼ���������巢�������ϵ��ϵͳ������Ҫ����Ҫ���ص�������������г�ʼ��
* �βκ��壺void
*/
void Init_PaulseFunction(void)
{
	INT8U i;
	for(i = 0;i < PaulseLeaguer_Num;i ++)
	{
		Pulse_CTRL[i].Enable =0;
	}
	
}

/*
	��������:PulseLeaguer_Enalbe(Pulse_Stru *Member,INT16U Enable)
	��������:���Դ����Ķ�ʱ������  ���û��߹ر�
	����:TRUE
*/
void PulseLeaguer_Enalbe(Pulse_Stru *Member,INT16U Enable)
{
	Member->Enable = Enable;
}

/*


*/
/*
* ��������:	Pulse_Stru*  Pulse_Create(INT16U interval,INT8U Enable,FUNCReCall f_callback)
* ��������:	����������Ƴ�Ա����������Ӧ�������ú���Ϊ����ӿں���
* �βκ���:	Enable�����ñ�־��CallBack_P:�ص�����ָ��
* ����ֵ  ���ص�����ָ������
*/
Pulse_Stru*  Pulse_Create(INT8U 	Enable, FUNCReCall f_callback)
{
	if(Leaguer_Limiter >= PaulseLeaguer_Num)
	{
		return 0;
	}
	Pulse_CTRL[Leaguer_Limiter].Enable = Enable;
	Pulse_CTRL[Leaguer_Limiter].F_callback_P = f_callback;
	Leaguer_Limiter ++;
	return &Pulse_CTRL[Leaguer_Limiter - 1];	
}

/*
	��������:PulseLeaguer_Enalbe(Pulse_Stru *Member,INT16U Enable)
	��������:���Դ������������������ֵ������
	����:TRUE
*/
void PulseLeaguer_SET(Pulse_Stru *Member,INT8U PulseNum,INT32U	Space,INT16U Edge_Num,INT16U CycleNum,INT16U CycleTick,INT8U	State)
{
	Member->PulseNum = PulseNum;	//��������  0XFFʱ��������������
	Member->Space = Space;			//ɨ����
	Member->CycleNum = CycleNum;	//����  �����
	Member->Edge_Num = Edge_Num;	//����  �����
	Member->CycleTick = CycleTick;		//���ڼ�����
	Member->State = State;			//״̬��¼��
}





void PulseCtrl_Executing(void)
{
	INT8U LOOP =0;
	for (LOOP =0;LOOP<PaulseLeaguer_Num;LOOP++)
	{
		if (Pulse_CTRL[LOOP].Enable !=0)	//����
		{
			if (Pulse_CTRL[LOOP].PulseNum !=0)		//����û�з���
			{
				if ( (*Pulse_ClockTick-Pulse_CTRL[LOOP].Ticks)>=Pulse_CTRL[LOOP].Space)//ɨ�����ڵ�
				{
					Pulse_CTRL[LOOP].Ticks =*Pulse_ClockTick;
					
					if(Pulse_CTRL[LOOP].CycleTick<=Pulse_CTRL[LOOP].Edge_Num)
					{
						Pulse_CTRL[LOOP].State =1;
					}
					else
					{
						Pulse_CTRL[LOOP].State =0;
					}
					Pulse_CTRL[LOOP].CycleTick +=1;
					if( Pulse_CTRL[LOOP].CycleTick >Pulse_CTRL[LOOP].CycleNum)
					{
						Pulse_CTRL[LOOP].CycleTick =0;
						if (Pulse_CTRL[LOOP].PulseNum !=0XFF)
						{
							Pulse_CTRL[LOOP].PulseNum -=1;
						}					
					}
					(*Pulse_CTRL[LOOP].F_callback_P)(Pulse_CTRL[LOOP].State);
				}
			}
		}
	}	
}


/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/





