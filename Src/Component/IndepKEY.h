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
* @author :
* @date :2016-12-10 15:23
***************************************************************
*/ 
#ifndef _INDEPKEY_H_
#define _INDEPKEY_H_

#include "stdio.h"
#include "stm32f4xx.h"
#include "TypeDef.h"
#include "Keyboard.h"


#ifdef _INDEPKEY_C_
#define INDEPKEY_EXT
#else
#define INDEPKEY_EXT extern
#endif
 
#define IndepKEY_Num			6	//�����Ա����

#define IndepKEY_ExtInitHOOK		1	//�궨���Ƿ�����ҽ��ⲿ��ʼ������



typedef void (*VOIDP)(void); 	//�ص�������������


typedef enum
{
	/* ������������ */
	DEFNULL =0x00,		//��Ч
	FallEdge =0x01,		//�½���
	LowLevel =0x02,		//�͵�ƽ
	UpEdge =0x04,		//������
	/* end*/
	
	/* ������ȡ״̬ */
	ReadStateON =0XAA,	//����״̬ "����������"
	ReadStateOFF =0X00	//����״̬ "����δ����"
	/* end*/
}IndepKEY_State;



typedef struct
{
	IndepKEY_State	TrigCondition;		//��������
	INT32U	FallEdge_Num;		    //�˲���������
	INT32U	LowLevel_NumFirst;		//�״���ʱ��������
	INT32U	LowLevel_Num;		    //��ʱ��������
	INT32U	UpEdge_Num;		    //�˲���������

}
IndepKEYPara_Stru;

typedef struct
{
	FunctionalState	Enable;		    	//��Ա�������ñ�־λ
	IndepKEYPara_Stru TrigPara;			//��������

	IndepKEY_State (*GetKeyStatus)(void);		//��ȡ����״̬ ����
	
	IndepKEY_State PreStatus;			    //�����Ƚ�״̬
	IndepKEY_State CurStatus;			    //������ǰ״̬
	
	IndepKEY_State TrigStatus;				//����״̬  ����������ֵ

	INT32U	FallEdge_Count;				//�˲�����������
	INT32U	LowLevel_CountFirst;			//��ʱ���������� �״�
	INT32U	LowLevel_Count;			    //��ʱ����������
	INT32U	UpEdge_Count;			    //�˲�����������
	void (*TrigOUT)(void);			    //��������

}IndepKEY_Stru;


#ifdef _INDEPKEY_C_

INT8U IndepKEY_Limiter;



	#if IndepKEY_ExtInitHOOK==1	//ʹ���ⲿ��ʼ�����Ӻ��� ���ҽ�

	VOIDP IndepKEY_ExtInitHooks =Keyboard_GPIO_Init;

	#endif


#endif

 //ȫ�ֱ�������
INDEPKEY_EXT  IndepKEY_Stru IndepKEY_Ctrler[IndepKEY_Num];    //��Ա������


INDEPKEY_EXT void IndepKEYFunction_Init(void);
INDEPKEY_EXT IndepKEY_Stru*  IndepKEY_Create(FunctionalState Enable, IndepKEYPara_Stru ParaS, IndepKEY_State (*InputHooks)(void),void (*OutPutHooks)(void));
INDEPKEY_EXT void IndepKEY_Enable(IndepKEY_Stru *Member,FunctionalState Enable);
INDEPKEY_EXT void IndepKEY_ScanServer(void)  ;


#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
