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
#ifndef _M4_UART2_H_
#define _M4_UART2_H_
 

#include "Typedef.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"	
#include "DMA_AddCfg.h"

 
#ifdef _M4_UART2_C_
#define M4_UART2_EXT
#else
#define M4_UART2_EXT extern
#endif
 


#define C_STDLibSupportUART2	0		//��׼��֧��ѡ�� 1֧�� 0��֧��  ע��ͨ�ô������ʱֻ��ռ��һ���˿�

#define U2TX_Pin GPIO_PIN_2
#define U2TX_GPIO_Port GPIOA
#define U2RX_Pin GPIO_PIN_3
#define U2RX_GPIO_Port GPIOA
 



M4_UART2_EXT UART_HandleTypeDef huart2;			//�����첽ͨ�ž��
M4_UART2_EXT DMA_HandleTypeDef hdma_usart2_rx;		//DMA���շ�����
M4_UART2_EXT DMA_HandleTypeDef hdma_usart2_tx;		//DMA���ͷ�����

/* DMA�������������*/
M4_UART2_EXT uint8_t UART2_RxBuffer[UART2_Amount]__attribute__((at(UART2_RX_DMA_ADD)));//���ջ�����
M4_UART2_EXT uint8_t UART2_TxBuffer[UART2_Amount]__attribute__((at(UART2_TX_DMA_ADD))); //���ջ�����






#ifdef _M4_UART2_C_


void MX_USART2_DMA_Init(void);
void MX_USART2_UART_Init(void);

#endif
 

M4_UART2_EXT	HAL_StatusTypeDef UART2_Busy;		//��������æ��־λ

//M4_UART2_EXT	INT8U UART2_DMACONT;


M4_UART2_EXT void UART2_Cfg(void);
M4_UART2_EXT HAL_StatusTypeDef UART2_Transmit( uint8_t *pData, uint16_t Size);	//���ͷ�����������DMA����Ϸ�ʽ


M4_UART2_EXT void HAL_UART2_MspInit(UART_HandleTypeDef* huart);		//MSP�ҽӾ��
M4_UART2_EXT void HAL_UART2_MspDeInit(UART_HandleTypeDef* huart); 		//MSP�ҽӾ��


M4_UART2_EXT void USART2_IRQHandler(void);
M4_UART2_EXT void DMA1_Stream6_IRQHandler(void);		//UART2_TX ����жϷ�����
M4_UART2_EXT void DMA1_Stream5_IRQHandler(void);		//UART2_RX ����жϷ�����

 

#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
