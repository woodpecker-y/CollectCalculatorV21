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
#define _M4_UART3_C_
#include "M4_UART3.h"
#include "main.h"



#if (C_STDLibSupportUART3==1)
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
	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
	USART3->DR = (uint8_t) ch;      
	return ch;
}
/*END*/

#endif





/* USART3 init function */
void MX_USART3_UART_Init(void)
{


	huart3.Instance = 		USART3;
//	huart3.Init.BaudRate = 	115200;
//	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = 	UART_STOPBITS_1;
//	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
	//	Error_Handler();
	}


	
	GPIO_InitTypeDef GPIO_InitStruct;
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/*Configure GPIO pins : LEDSD_Pin  */
	GPIO_InitStruct.Pin = COM3_CtrlBit;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(COM3_CtrlPort, &GPIO_InitStruct);	
	COM3_CtrlTX;
	


}

 
 


/** 
  * Enable DMA controller clock
  */

void MX_USART3_DMA_Init(void) 
{

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA1_Stream1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 1, 0);		//UART3_RX
	HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
	/* DMA1_Stream3_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 2, 0);		//UART3_TX
	HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);		

}




/*
 UART3 �첽ͨ������
*/
void UART3_Cfg(void)
{
	MX_USART3_DMA_Init();	//
	MX_USART3_UART_Init();
	
	HAL_UART_Receive_DMA(&huart3,UART3_RxBuffer,UART3_Amount);	//DMA��������
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);    				//ʹ�ܿ����ж�
}





void HAL_UART3_MspInit(UART_HandleTypeDef* huart)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_USART3_CLK_ENABLE();
  
	  /**USART3 GPIO Configuration	  
	  PD8	  ------> USART3_TX
	  PD9	  ------> USART3_RX 
	 */
    GPIO_InitStruct.Pin = U3TX_Pin|U3RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* Peripheral DMA init*/
  
    hdma_usart3_tx.Instance = DMA1_Stream3;
    hdma_usart3_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart3_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_tx.Init.Mode = DMA_NORMAL;
    hdma_usart3_tx.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_usart3_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart3_tx) != HAL_OK)
    {
//      Error_Handler();
    }

    __HAL_LINKDMA(huart,hdmatx,hdma_usart3_tx);
    
    hdma_usart3_rx.Instance = DMA1_Stream1;
    hdma_usart3_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_rx.Init.Mode = DMA_NORMAL;
    hdma_usart3_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    hdma_usart3_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart3_rx) != HAL_OK)
    {
//      Error_Handler();
    }

    __HAL_LINKDMA(huart,hdmarx,hdma_usart3_rx);

    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(USART3_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
	UART3_Busy =HAL_OK;

}





void HAL_UART3_MspDeInit(UART_HandleTypeDef* huart)
{

	/* Peripheral clock disable */
	__HAL_RCC_USART3_CLK_DISABLE();


    /**USART3 GPIO Configuration    
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX 
    */
	HAL_GPIO_DeInit(GPIOD, U3TX_Pin|U3RX_Pin);

	/* Peripheral DMA DeInit*/
	HAL_DMA_DeInit(huart->hdmatx);
	HAL_DMA_DeInit(huart->hdmarx);

	/* Peripheral interrupt DeInit*/
	HAL_NVIC_DisableIRQ(USART3_IRQn);
	
	UART3_Busy =HAL_OK;
	
}





/*
	UART3���ͷ�����
*/
HAL_StatusTypeDef UART3_Transmit(uint8_t* Buffer, uint16_t Num)
{

	HAL_StatusTypeDef back =HAL_OK;
	UART3_Busy =HAL_BUSY;
	memcpy(UART3_TxBuffer, Buffer,Num);//���������ݴ��ݸ�����ָ��
	back =HAL_UART_Transmit_DMA(&huart3,UART3_TxBuffer,Num);		//�����յ������ݷ���

	return back;
	 
}












/**
* @brief This function handles USART3 global interrupt.
*/

void USART3_IRQHandler(void)
{

  	HAL_StatusTypeDef BackVal=HAL_OK;
    uint32_t tmp_flag = 0;
    uint32_t temp =0;
    uint32_t UART3_Rxlenth =0;
	
	
    HAL_UART_IRQHandler(&huart3);
    tmp_flag =  __HAL_UART_GET_FLAG(&huart3,UART_FLAG_IDLE);//��ȡ�˿ڿ����ж�
    if((tmp_flag != RESET))
    { 
		__HAL_UART_CLEAR_IDLEFLAG(&huart3);
		/* ���´�������ͨ�Ų���	Ҳ���Է��մ˷�ʽͨ��FIFO�������ݴ���*/
		BackVal =BackVal;
		temp  = hdma_usart3_rx.Instance->NDTR;         							//��ȡʣ����ջ������Ĵ�С
		UART3_Rxlenth =  UART3_Amount - temp;   
		
	
		switch(ClientCH1Ctrler.Device.Type)
		{
			case Meter_B:
			{
				UART_RBC_BufferInput(UART_TO_FY188_CCB_S,UART3_Rxlenth,UART3_RxBuffer);
			}break;
            
			case Meter_U:
			{
				UART_RBC_BufferInput(UART_TO_FY188_CCB_S,UART3_Rxlenth,UART3_RxBuffer);

			}break;
			
			case Valve_U:		//��׼ͨ�Ϸ�
			case Valve_UH:		//��ˮͨ�Ϸ�
			{
				UART_RBC_BufferInput(UART_TO_FY2000_CCB_S,UART3_Rxlenth,UART3_RxBuffer);

			}break;

            
#ifdef Meter_H_ENABLE
			case Meter_H:
			{
				UART_RBC_BufferInput(UART_TO_HZCRL_CCB_S,UART3_Rxlenth,UART3_RxBuffer);
			}break;
#endif
            


#ifdef  Meter_XY_ENABLE	
            case Meter_XY:
            {
                UART_RBC_BufferInput(UART_TO_XY188_CCB_S,UART3_Rxlenth,UART3_RxBuffer);

            }break;
#endif
            
#ifdef  Meter_HT2X_ENABLE	
            case Meter_HT2X:
            {
                UART_RBC_BufferInput(UART_TO_HT2X188_CCB_S,UART3_Rxlenth,UART3_RxBuffer);

            }break;
#endif
	
            
#ifdef  Meter_BRC_ENABLE	
            case Meter_BRC:
            {
                UART_RBC_BufferInput(UART_TO_BRC188_CCB_S,UART3_Rxlenth,UART3_RxBuffer);

            }break;
#endif
            
            
#ifdef  Meter_DDF2_ENABLE	
            case Meter_DDF2:
            {
                UART_RBC_BufferInput(UART_TO_DDF2_CCB_S,UART3_Rxlenth,UART3_RxBuffer);

            }break;
#endif	
         


			default: 
            {
            
                UART_RBC_BufferInput(UART_TO_DDF2_CCB_S,UART3_Rxlenth,UART3_RxBuffer);
            }

            break;
		}


		
		HAL_UART_DMAStop(&huart3);												//�ر�DMA�����ٴ���������
		BackVal = HAL_UART_Receive_DMA(&huart3,UART3_RxBuffer,UART3_Amount);	//��������DMA ����
		/* end*/
     }
}





/**
* @brief This function handles DMA1 stream1 global interrupt.
 UART3_RX ����жϷ�����
*/
void DMA1_Stream1_IRQHandler(void)
{

	HAL_DMA_IRQHandler(&hdma_usart3_rx);
	/* USER CODE BEGIN DMA1_Stream5_IRQn 1 */
	/* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
* @brief This function handles DMA1 stream3 global interrupt.
UART3_TX ����жϷ�����
*/

void DMA1_Stream3_IRQHandler(void)
{

	HAL_DMA_IRQHandler(&hdma_usart3_tx);
	UART3_Busy =HAL_OK;
	LED_COM3_ON;
}






 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
