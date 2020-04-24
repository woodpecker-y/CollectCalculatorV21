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
* @date :2016/11/8 22:30
***************************************************************
*/ 
#ifndef _UART_RBC_H_
#define _UART_RBC_H_
 

#include "TypeDef.h"
#include "stm32f4xx_hal_msp.h"

 
#ifdef _UART_RBC_C_
#define UART_RBC_EXT
#else
#define UART_RBC_EXT extern
#endif
 


#define Max_UART_RBC_NUM	6       		//�궨��Э����������������

typedef  struct UART_RBC_Str 
{
	FunctionalState Enable;					//���ñ�־
    INT32U *Ticks;							//ʱ�ӻ�׼
    
    INT8U *InputBuffer; 					//�����������뻺����
    INT16U BufferSize;  					//�������뻺����������С

    INT16U Rx_Front;    					//���ջ�����ͷָ�� ָʾ��С���ջ������Ŀյ�ַ
    INT16U Rx_Rear;							//���ջ�����βָ�� ָʾ��С���ջ�������Ч���ݵ���С��ַ

    INT8U TimeOut;	 						//���ջ�����ʱ������Ĵ���
    INT32U RecPackTimeOut; 					//���ջ�����ʱ�������¼��



    INT8U RxPack_Mutex; 					//֡���տ����ź��� ��Э����봦��׶�ʱ���������ջ



	void (*API_RxFunCal)(struct UART_RBC_Str *); 	//���赽Ӧ�ò�ص���������
	
    INT16U RecPackState; 					//���ݰ�����״̬
    INT16U RecPackPoint; 					//����֡����ͷָ��

    INT8U *InputPack; 						//֡Ԥ���ػ�����
    INT16U PackSize;							//֡Ԥ���ػ��������ߴ�
    INT8U RecPack_Null; 						//֡�������ձ�־λ
    INT8U RecPack_Full; 						//֡����������־λ



	INT8U *OutputPack; 						//֡���ط�����
	INT16U OutputPackSize; 					//����֡���ݳ���
	
	void (*API_TxFunCal)(struct UART_RBC_Str *);	//Ӧ�ò㵽���跢�ͷ�������Ϊ�˱�֤���ݷ��͵���ȷ��ʱ�Ըú�������Ҫ�ж����߱�־״̬ ��SendBusy��

	HAL_StatusTypeDef* SendBusy;				//��������ռ�ÿ��Ʊ�־
	INT8U PackCreatFlag;						//����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;						//����Э�������� ������Ʋ���
	FunctionalState PackSendFlag;				//Э�鷢�������־ ���ñ�־��λ˵�������ݽ�Ҫ����
	

}UART_RBC_Stru ;





 
#ifdef _UART_RBC_C_

UART_RBC_Stru UART_RBC_Manager[Max_UART_RBC_NUM];
UART_RBC_EXT INT16U UART_RBC_Record;


#endif


UART_RBC_EXT void UART_RBC_ControlerInit(void);
UART_RBC_EXT INT8U UART_RBC_Creat( UART_RBC_Stru** UART_RBCMem,INT8U* InputBuffer,INT16U BufferSize,INT8U* InputPack,INT8U* OutputPack,INT16U PackSize,INT32U* TICK,INT8U TimeOut);
UART_RBC_EXT	void UART_RBC_OutputHandle_Init(UART_RBC_Stru* member, void(*Output)(UART_RBC_Stru *),HAL_StatusTypeDef *BUSY);

UART_RBC_EXT void UART_RBC_InputHandle_Init(UART_RBC_Stru* member, void (*IN)(UART_RBC_Stru *));

UART_RBC_EXT void UART_RBC_Enable(UART_RBC_Stru* member,FunctionalState Falg);
UART_RBC_EXT void UART_RBC_BufferInput(UART_RBC_Stru* member,INT16U InputNum,INT8U* InputBuffer_P);

UART_RBC_EXT void UART_RBC_TXServer(void);
UART_RBC_EXT void UART_RBC_RXServer(void);

 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
