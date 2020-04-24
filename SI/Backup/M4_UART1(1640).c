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
#define _M4_UART1_C_
#include "M4_UART1.h"
#include "main.h"

extern struct kfifo *kfifo_usart1_rx;


#if (C_STDLibSupportUART1==1)
/* ��׼��֧��*/	  
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)	
#pragma import(__use_no_semihosting)                            
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
	return ch;
}

/* �ض���fgetc���� */
int fgetc(FILE * f)
{
  uint8_t ch = 0;
	int len;

	
	if(kfifo_usart1_rx == NULL)
	{
		return -1;
	}
	
	len = kfifo_len(kfifo_usart1_rx);
	
	if(len > 0)
	{
		len = kfifo_get(kfifo_usart1_rx,&ch,1);
		if(len >0)
		{
			return ch;
		}
		else
		{
			return -1;
		}
	}
	return -1;
}

/*END*/

#endif





/* USART1 init function */
void MX_USART1_UART_Init(void)
{

	huart1.Instance = 		USART1;
//	huart1.Init.BaudRate = 	115200;
//	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = 	UART_STOPBITS_1;
//	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
}

 
 


/** 
  * Enable DMA controller clock
  */

void MX_USART1_DMA_Init(void) 
{

	/* DMA controller clock enable */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA2_Stream5_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 1, 0);		//UART1_RX
	HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);
	/* DMA2_Stream7_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 2, 0);		//UART1_TX
	HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);		

}




/*
 UART1 �첽ͨ������
*/
void UART1_Cfg(void)
{
	MX_USART1_DMA_Init();	//
	MX_USART1_UART_Init();
	
	HAL_UART_Receive_DMA(&huart1,UART1_RxBuffer,UART1_Amount);	//DMA��������
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);    				//ʹ�ܿ����ж�
}





void HAL_UART1_MspInit(UART_HandleTypeDef* huart)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Peripheral clock enable */
	 __HAL_RCC_USART1_CLK_ENABLE();
	
	 /**USART1 GPIO Configuration	 
	 PA9	 ------> USART1_TX
	 PA10	  ------> USART1_RX 
	 */
	 GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
	 GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	 GPIO_InitStruct.Pull = GPIO_PULLUP;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	 GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	 HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	 /* USART1 DMA Init */
	 /* USART1_TX Init */
	 hdma_usart1_tx.Instance = DMA2_Stream7;
	 hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
	 hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	 hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	 hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
	 hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	 hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	 hdma_usart1_tx.Init.Mode = DMA_NORMAL;
	 hdma_usart1_tx.Init.Priority = DMA_PRIORITY_HIGH;
	 hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	 if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
	 {
	   _Error_Handler(__FILE__, __LINE__);
	 }
	
	 __HAL_LINKDMA(huart,hdmatx,hdma_usart1_tx);
	
	 /* USART1_RX Init */
	 hdma_usart1_rx.Instance = DMA2_Stream5;
	 hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
	 hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	 hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	 hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
	 hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	 hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	 hdma_usart1_rx.Init.Mode = DMA_NORMAL;
	 hdma_usart1_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
	 hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	 if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
	 {
	   _Error_Handler(__FILE__, __LINE__);
	 }
	
	 __HAL_LINKDMA(huart,hdmarx,hdma_usart1_rx);



	/* Peripheral interrupt init */
	HAL_NVIC_SetPriority(USART1_IRQn, 6, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

	UART1_Busy =HAL_OK;


}





void HAL_UART1_MspDeInit(UART_HandleTypeDef* huart)
{
	/* Peripheral clock disable */
	__HAL_RCC_USART1_CLK_DISABLE();

	/**USART1 GPIO Configuration    
	PA9     ------> USART1_TX
	PA10     ------> USART1_RX 
	*/
	HAL_GPIO_DeInit(GPIOA, U1TX_Pin|U1RX_Pin);

	/* Peripheral DMA DeInit*/
	HAL_DMA_DeInit(huart->hdmatx);
	HAL_DMA_DeInit(huart->hdmarx);

	/* Peripheral interrupt DeInit*/
	HAL_NVIC_DisableIRQ(USART1_IRQn);

	UART1_Busy =HAL_OK;

}





/*
	UART1���ͷ�����
*/
HAL_StatusTypeDef UART1_Transmit(uint8_t* Buffer, uint16_t Num)
{
	HAL_StatusTypeDef back =HAL_OK;
	UART1_Busy =HAL_BUSY;
	memcpy(UART1_TxBuffer, Buffer,Num);//���������ݴ��ݸ�����ָ��
	back = HAL_UART_Transmit_DMA(&huart1,UART1_TxBuffer,Num);		//DMA���ݷ���
	return back;

}












/**
* @brief This function handles USART1 global interrupt.
*/

void USART1_IRQHandler(void)
{

  	HAL_StatusTypeDef BackVal=HAL_OK;
    uint32_t tmp_flag = 0;
    uint32_t temp =0;
    uint32_t UART1_Rxlenth =0;
	
	
    HAL_UART_IRQHandler(&huart1);
    tmp_flag =  __HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE);//��ȡ�˿ڿ����ж�
    if((tmp_flag != RESET))
    { 
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		
		/* ���´�������ͨ�Ų���	Ҳ���Է��մ˷�ʽͨ��FIFO�������ݴ���*/
		BackVal =BackVal;
		temp  = hdma_usart1_rx.Instance->NDTR;         						//��ȡʣ����ջ������Ĵ�С
		UART1_Rxlenth =  UART1_Amount - temp;   

		HAL_UART_DMAStop(&huart1);
		
		/*�����յ������ݷ��͵����ڶ���*/
		if(kfifo_usart1_rx != NULL)
		{
			kfifo_put( kfifo_usart1_rx, UART1_RxBuffer, UART1_Rxlenth);
		}
		
		LED_COM1_ON;
		/* end*/
		BackVal = HAL_UART_Receive_DMA(&huart1,UART1_RxBuffer,UART1_Amount);		//��������DMA ����
     }
}





/**
* @brief This function handles DMA2 stream5 global interrupt.
 UART1_RX ����жϷ�����
*/
void DMA2_Stream5_IRQHandler(void)
{

	HAL_DMA_IRQHandler(&hdma_usart1_rx);
	/* USER CODE BEGIN DMA2_Stream5_IRQn 1 */

	/* USER CODE END DMA2_Stream5_IRQn 1 */
}

/**
* @brief This function handles DMA2 stream7 global interrupt.
UART1_TX ����жϷ�����
*/
void DMA2_Stream7_IRQHandler(void)
{

	HAL_DMA_IRQHandler(&hdma_usart1_tx);
	/* USER CODE BEGIN DMA2_Stream7_IRQn 1 */

	UART1_Busy =HAL_OK;
	LED_COM1_ON;
	
	/* USER CODE END DMA2_Stream7_IRQn 1 */
}






 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
