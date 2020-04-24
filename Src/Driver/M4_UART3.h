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
* @brief :������Ӧ����STM32F4ϵ��΢���Ƶ�UART3
*UART���Ͳ��� DMA ������ʽ����  ���ݷ������ڴ浽���裬������ɺ�ᴥ���������
*UART���ղ��� DMA ������ʽ����  ���ݷ��������赽�ڴ棬�������ý��տ����жϣ�ͨ����ѯ���б�־��ȷ���Ѿ����յ�������֡��������ֹ����֡��С��û������DMA��������
*
���ļ�����3���жϷ����� 
UART3 DMA��������жϷ�����
UART3 DMA��������жϷ�����
UARTȫ���жϷ�����
* 
* 
* 
*
* @author :
* @date :2017/5/7 7:26
***************************************************************
*/ 
#ifndef _M4_UART3_H_
#define _M4_UART3_H_
 


#include "stm32f4xx_hal.h"
#include "stdio.h"	
#include "Typedef.h"
#include "DMA_AddCfg.h"

 
#ifdef _M4_UART3_C_
#define M4_UART3_EXT
#else
#define M4_UART3_EXT extern
#endif
 


#define C_STDLibSupportUART3	0		//��׼��֧��ѡ�� 1֧�� 0��֧��  ע��ͨ�ô������ʱֻ��ռ��һ���˿�

#define U3TX_Pin GPIO_PIN_8
#define U3TX_GPIO_Port GPIOD

#define U3RX_Pin GPIO_PIN_9
#define U3RX_GPIO_Port GPIOD
 



M4_UART3_EXT UART_HandleTypeDef huart3;			//�����첽ͨ�ž��
M4_UART3_EXT DMA_HandleTypeDef hdma_usart3_rx;		//DMA���շ�����
M4_UART3_EXT DMA_HandleTypeDef hdma_usart3_tx;		//DMA���ͷ�����



/* DMA�������������*/
M4_UART3_EXT uint8_t UART3_RxBuffer[UART3_Amount]__attribute__((at(UART3_RX_DMA_ADD)));//���ջ�����
M4_UART3_EXT uint8_t UART3_TxBuffer[UART3_Amount]__attribute__((at(UART3_TX_DMA_ADD))); //���ջ�����




//��˫���շ����ƹܽ�

#define COM3_CtrlPort	GPIOB
#define COM3_CtrlBit	GPIO_PIN_15
#define COM3_CtrlTX		(HAL_GPIO_WritePin(COM3_CtrlPort, COM3_CtrlBit, GPIO_PIN_SET))
#define COM3_CtrlRX		(HAL_GPIO_WritePin(COM3_CtrlPort, COM3_CtrlBit, GPIO_PIN_RESET))





#ifdef _M4_UART3_C_


void MX_USART3_DMA_Init(void);
void MX_USART3_UART_Init(void);

#endif
 

M4_UART3_EXT	HAL_StatusTypeDef UART3_Busy;		//��������æ��־λ


M4_UART3_EXT	INT8U UART3_DMACONT;
M4_UART3_EXT	INT32U UART3_DMAOUT;


M4_UART3_EXT void UART3_Cfg(void);
M4_UART3_EXT HAL_StatusTypeDef UART3_Transmit( uint8_t *pData, uint16_t Size);	//���ͷ�����������DMA����Ϸ�ʽ


M4_UART3_EXT void HAL_UART3_MspInit(UART_HandleTypeDef* huart);	//MSP�ҽӾ��
M4_UART3_EXT void HAL_UART3_MspDeInit(UART_HandleTypeDef* huart); //MSP�ҽӾ��


M4_UART3_EXT void USART3_IRQHandler(void);
M4_UART3_EXT void DMA1_Stream3_IRQHandler(void);		//UART3_TX ����жϷ�����
M4_UART3_EXT void DMA1_Stream1_IRQHandler(void);		//UART3_RX ����жϷ�����

 

#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
