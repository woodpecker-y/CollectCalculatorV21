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



#ifdef _UART_RBC_C_
#define UART_RBC_EXT
#else
#define UART_RBC_EXT extern
#endif
 


#define Max_UART_RBC_NUM	3				//�궨��Э����������������

typedef  struct UART_RBC_Str 
{

    INT32U *Ticks;							//ʱ�ӻ�׼
    
    INT8U *InputBuffer; 						//�����������뻺����
    INT16U BufferSize;  						//�������뻺����������С

    INT16U Rx_Front;    					//���ջ�����ͷָ�� ָʾ��С���ջ������Ŀյ�ַ
    INT16U Rx_Rear;							//���ջ�����βָ�� ָʾ��С���ջ�������Ч���ݵ���С��ַ

    INT8U TimeOut;	 						//���ջ�����ʱ������Ĵ���
    INT32U RecPackTimeOut; 					//���ջ�����ʱ�������¼��


	void (*API_RxFunCal)(struct UART_RBC_Str *); 	//���赽Ӧ�ò�ص���������
    INT16U RecPackState; 					//���ݰ�����״̬
    INT16U RecPackNum; 						//���������ֽ���
    INT16U RecPackPoint; 					//����֡����ͷָ��

    INT8U *InputPack; 						//֡Ԥ���ػ�����
    INT16U PackSize;							//֡Ԥ���ػ��������ߴ�

}UART_RBC_Stru ;




#ifdef _UART_RBC_C_



#endif


UART_RBC_EXT HAL_StatusTypeDef UART_RBC_Creat(	UART_RBC_Stru* object,
							INT8U* InputBuffer,
							INT16U BufferSize,
							INT8U* InputPack,
							INT32U* TICK,
							INT8U TimeOut);



UART_RBC_EXT void UART_RBC_Rx_Init(UART_RBC_Stru* object, void (*IN)(UART_RBC_Stru *));
UART_RBC_EXT void UART_RBC_BufferIn(UART_RBC_Stru* object,const INT16U InputNum,INT8U* InputBuffer_P);
UART_RBC_EXT HAL_StatusTypeDef UART_RBC_RxServer(UART_RBC_Stru* object);












#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 

