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
* @brief :
* 
* 
* 
*
* @author :	��ΰ
* @date :2017/5/10 16:41
***************************************************************
*/ 
#define _M4_SPI1_C_
#include "M4_SPI1.h"
 


/* SPI1 init function */
void MX_SPI1_Init(void)
{

  SPI1_Handler.Instance = SPI1;
  SPI1_Handler.Init.Mode = SPI_MODE_MASTER;
  SPI1_Handler.Init.Direction = SPI_DIRECTION_2LINES;
  SPI1_Handler.Init.DataSize = SPI_DATASIZE_8BIT;
  SPI1_Handler.Init.CLKPolarity = SPI_POLARITY_HIGH;
  SPI1_Handler.Init.CLKPhase = SPI_PHASE_2EDGE;
  SPI1_Handler.Init.NSS = SPI_NSS_SOFT;
  SPI1_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  SPI1_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;
  SPI1_Handler.Init.TIMode = SPI_TIMODE_DISABLE;
  SPI1_Handler.Init.CRCCalculation = SPI_CRCCALCULATION_ENABLE;
  SPI1_Handler.Init.CRCPolynomial = 7;
  if (HAL_SPI_Init(&SPI1_Handler) != HAL_OK)
  {

  }

}




void HAL_SPI1_MspInit(SPI_HandleTypeDef* hspi)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	{

		__HAL_RCC_SPI1_CLK_ENABLE();

		/**SPI1 GPIO Configuration    
		PA5     ------> SPI1_SCK
		PA6     ------> SPI1_MISO
		PA7     ------> SPI1_MOSI 
		*/
		GPIO_InitStruct.Pin = SPI1CLK_Pin|SPI1DO_Pin|SPI1DI_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}

}




void HAL_SPI1_MspDeInit(SPI_HandleTypeDef* hspi)
{

	__HAL_RCC_SPI1_CLK_DISABLE();
	HAL_GPIO_DeInit(GPIOA, SPI1CLK_Pin|SPI1DO_Pin|SPI1DI_Pin);

}











//SPI5 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI1_ReadWriteByte(u8 TxData)
{
    u8 Rxdata;
    HAL_SPI_TransmitReceive(&SPI1_Handler,&TxData,&Rxdata,1, 1000);       
 	return Rxdata;          		    //�����յ�������		
}




//SPI�ٶ����ú���
//SPI�ٶ�=fAPB1/��Ƶϵ��
//@ref SPI_BaudRate_Prescaler:SPI_BAUDRATEPRESCALER_2~SPI_BAUDRATEPRESCALER_2 256
//fAPB1ʱ��һ��Ϊ45Mhz��
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
    __HAL_SPI_DISABLE(&SPI1_Handler);            //�ر�SPI
    SPI1_Handler.Instance->CR1&=0XFFC7;          //λ3-5���㣬�������ò�����
    SPI1_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//����SPI�ٶ�
    __HAL_SPI_ENABLE(&SPI1_Handler);             //ʹ��SPI
    
}



 
 




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
