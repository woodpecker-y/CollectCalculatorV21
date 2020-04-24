


/*
***********************************************************************************
*			
*���ܣ�ʹ��ϵͳʱ����Ϊ��׼Դʵ�ּ򵥵�PWM���� LED �������Ⱦ�����˸������
*
*
*
*˵����	1.����ʵ����˸��������
*    		2.�����������ڵĳ���
*     		3.����ƥ�����ǰ��ĵ�ƽ״̬ state
		4.�������������صĳ���
*
*
*By			:��ΰ
*Contact	:511328030@qq.com
*History	:2015/5/18 9:14:21
***********************************************************************************
*/
#ifndef _PULSE_H_
#define _PULSE_H_

#include "stm32f4xx_hal.h"
#include "TypeDef.h"
#include "stm32f4xx_hal_msp.h"


#ifdef _PULSE_C_
#define PULSE_EXT
#else 
#define PULSE_EXT extern
#endif 

#define PaulseLeaguer_Num	4		//�����Ա����  ���鳤��
typedef void (*FUNCReCall)(INT8U ); 	//�ص�������������

typedef struct
{
    INT8U	Enable;				//����������ñ�־
    INT32U	Ticks;					//ʱ�Ӹ����������ڼ�¼ϵͳ��ʱ��
    INT8U	PulseNum;				//�������������
    INT32U	Space;				//���ɨ������ϵͳʱ�ӻ��Դ˼��ʱ�䴦�������
    INT16U	CycleNum;				//����
    INT16U	Edge_Num;				//����������
    INT16U	CycleTick;				//�����ڼ�¼��
    INT8U	State;					//״̬��¼��  1˵����ǰ�������ڵĵ�һ�׶� 0˵���������ڵĵڶ��׶�

 //   void (*F_callback_P) (INT8U );
    FUNCReCall	F_callback_P; 			//�ص�����ָ��
}Pulse_Stru;

//��̬�ֲ���������
#ifdef _PULSE_C_

INT8U Leaguer_Limiter;
//ϵͳʱ��Դ�ҽ�
INT32U* Pulse_ClockTick= &SystemTick_ms;





#endif 

//ȫ�ֱ�������
PULSE_EXT Pulse_Stru Pulse_CTRL[PaulseLeaguer_Num];

PULSE_EXT void Init_PaulseFunction(void);	//ģ�鹦�ܳ�ʼ��
PULSE_EXT Pulse_Stru*  Pulse_Create(INT8U Enable,FUNCReCall f_callback);//����һ���������
PULSE_EXT void PulseLeaguer_SET(Pulse_Stru *Member,INT8U PulseNum,INT32U	Space,INT16U Edge_Num,INT16U CycleNum,INT16U CycleTick,INT8U	State);//�޸�ĳ��������ƵĲ���������
PULSE_EXT void PulseLeaguer_Enalbe(Pulse_Stru *Member,INT16U Enable);//ʹ��ĳ���������ģ��

PULSE_EXT void PulseCtrl_Executing(void);//������ƹ���ִ��

#endif



