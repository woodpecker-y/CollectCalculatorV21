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
* @brief :���ļ����ڻ����Ǳ��CRL-G �Լ�CRL-Hϵ�г�����������ͨ��Э��
* 
* 
* 
*
* @author :
* @date :2017/10/9 14:01
***************************************************************
*/ 
#ifndef _HZCRL_XPRO_H_
#define _HZCRL_XPRO_H_
 

#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"
#include <string.h>

#ifdef Meter_H_ENABLE


typedef enum
{
    S_Start,                    //��ʼ��
    S_Type,                     //�Ǳ�����
    S_Address,                  //�Ǳ��ַ
    S_Ctr,                      //������
    S_Len,                      //����
    S_Data,                     //����
    S_Sum,                      //У��
    S_End                      //������
}recState_S;

#pragma pack(1)			        //�ֽڶ���

typedef struct
{
    INT8U	start;					//��ʼ��
    INT8U	type;					//�Ǳ�����
    INT8U	addPlace[3];			//��ַռλ����Ĭ��ȫ�㣬������
    INT32U	address;				//��ַ(SN)
    INT8U	ctr;                  //����Ӧ��
    INT8U	len;                  //���ݳ���
}HZCRL_Pack_Head_t;

typedef struct
{
    INT16U	datamark;				//���ݱ�ʶ
    INT8U	serialNum;				//���к�
    
    INT32U	settleEnergy;        	//����������
    INT8U	settleEnergy_Unit;    	//������������λ
    
    INT32U	totalEnergy;         	//��ǰ����
    INT8U	totalEnergy_Unit;     	//��ǰ������λ
    
    INT32U	instant_Energy;			//�ȹ���
    INT8U	instant_Energy_Unit;		//�ȹ��ʵ�λ
    
    INT32U	Current;				//����
    INT8U	Current_Unit;			//������λ
    
    INT32U	totalCurrent;			//�ۼ�����
    INT8U	totalCurrent_Unit;			//�ۼ�������λ
    
    INT8U	inputTempH;         	//��ˮ�¶ȸ�λ
    INT16U	inputTempL;         	//��ˮ�¶ȵ�λ
    
    INT8U	outputTempH;        	//��ˮ�¶ȸ�λ
    INT16U	outputTempL;        	//��ˮ�¶ȵ�λ
    
    INT8U	totalWorkH;         	//�ۼƹ���ʱ���λ
    INT16U	totalWorkL;         	//�ۼƹ���ʱ���λ
    
    INT16U	Year;					//�꣨ʵʱʱ�䣩
    INT8U	Month;				//�£�ʵʱʱ�䣩
    INT8U	Day;					//�գ�ʵʱʱ�䣩
    INT8U	Hour;					//ʱ��ʵʱʱ�䣩
    INT8U	Minute; 			    //�֣�ʵʱʱ�䣩
    INT8U	Second; 			    //�루ʵʱʱ�䣩 
    
    INT8U	state1;				//״̬1
    INT8U	state2;				//״̬2
}HZCRL_Pack_Value_t;

typedef struct
{
	HZCRL_Pack_Head_t Head;
	INT16U datamark;            //���ݱ�ʶ
    INT8U serialNum;            //���к�
	INT8U sum;				    //У���
	INT8U end;					//������־
}HZCRL_Pack01S_Stru;			//����ʵʱ����


typedef struct
{
	HZCRL_Pack_Head_t Head;     //Э��ͷ
	HZCRL_Pack_Value_t data;    //������ʵʱ����
	INT8U sum;				    //У���
	INT8U end;					//������־
}HZCRL_Pack01S_ACK_Stru;		//ʵʱ���ݷ���


typedef union
{
	HZCRL_Pack01S_Stru Pack0X01S;
}HZCRL_Send_Uni;

#pragma pack()		            //�ֽڶ���

#define Start_Mark  0x68        //��ʼ��
#define End_Mark    0x16        //������


 
#ifdef _HZCRL_XPRO_C_
#define HZCRL_XPRO_EXT
#else
#define HZCRL_XPRO_EXT extern
#endif
 




 
 




 
#ifdef _HZCRL_XPRO_C_






#endif
 




 
void HZCRL_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
INT8U HZCRL_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);
void HZCRL_Pack_0X01_S(UART_RBC_Stru* PORT);
INT8U HZCRL_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);

#endif
 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
