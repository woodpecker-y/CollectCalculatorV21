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
* @brief :������Ӧ����STM32F4ϵ��΢���Ƶ�UART1
*UART���Ͳ��� DMA ������ʽ����  ���ݷ������ڴ浽���裬������ɺ�ᴥ���������
*UART���ղ��� DMA ������ʽ����  ���ݷ��������赽�ڴ棬�������ý��տ����жϣ�ͨ����ѯ���б�־��ȷ���Ѿ����յ�������֡��������ֹ����֡��С��û������DMA��������
*
���ļ�����3���жϷ����� 
UART1 DMA��������жϷ�����
UART1 DMA��������жϷ�����
UARTȫ���жϷ�����
* 
* 
* 
*
* @author :
* @date :2017/5/7 7:26
***************************************************************
*/ 
#ifndef _M4_UART1_H_
#define _M4_UART1_H_
 

#include "Typedef.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"	
#include "DMA_AddCfg.h"
#include "kfifo.h"

 
#ifdef _M4_UART1_C_
#define M4_UART1_EXT
#else
#define M4_UART1_EXT extern
#endif
 


#define C_STDLibSupportUART1 1		//��׼��֧��ѡ�� 1֧�� 0��֧��  ע��ͨ�ô������ʱֻ��ռ��һ���˿�

#define U1TX_Pin GPIO_PIN_9
#define U1TX_GPIO_Port GPIOA
#define U1RX_Pin GPIO_PIN_10
#define U1RX_GPIO_Port GPIOA
 



M4_UART1_EXT UART_HandleTypeDef huart1;			//�����첽ͨ�ž��
M4_UART1_EXT DMA_HandleTypeDef hdma_usart1_rx;		//DMA���շ�����
M4_UART1_EXT DMA_HandleTypeDef hdma_usart1_tx;		//DMA���ͷ�����


/* DMA�������������*/
M4_UART1_EXT uint8_t UART1_RxBuffer[UART1_Amount]__attribute__((at(UART1_RX_DMA_ADD))); //���ջ�����
M4_UART1_EXT uint8_t UART1_TxBuffer[UART1_Amount]__attribute__((at(UART1_TX_DMA_ADD))); //���ջ�����

typedef enum
{
  UART_SUCCESS,
  UART_FAIL,
}uart_op_result;



#ifdef _M4_UART1_C_


void MX_USART1_DMA_Init(void);


#endif
 

M4_UART1_EXT	HAL_StatusTypeDef UART1_Busy;		//��������æ��־λ

M4_UART1_EXT	INT8U UART1_DMACONT;

M4_UART1_EXT void UART1_Cfg(void);
M4_UART1_EXT HAL_StatusTypeDef UART1_Transmit( uint8_t *pData, uint16_t Size);	//���ͷ�����������DMA����Ϸ�ʽ


M4_UART1_EXT void HAL_UART1_MspInit(UART_HandleTypeDef* huart);	//MSP�ҽӾ��
M4_UART1_EXT void HAL_UART1_MspDeInit(UART_HandleTypeDef* huart); //MSP�ҽӾ��


M4_UART1_EXT void USART1_IRQHandler(void);
M4_UART1_EXT void DMA2_Stream7_IRQHandler(void);		//UART1_TX ����жϷ�����
M4_UART1_EXT void DMA2_Stream5_IRQHandler(void);		//UART1_RX ����жϷ�����
M4_UART1_EXT void MX_USART1_UART_Init(void);
M4_UART1_EXT uart_op_result usart_fifo_start(UART_HandleTypeDef *uartHandle);
 

#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
