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
* @brief :���ļ����������豸6�������Լ���ʼ��
* 
* 
* 
*
* @author :��ΰ
* @date :2017/8/26 14:51
***************************************************************
*/ 
#define _KEYBOARD_C_
#include "Keyboard.h"



 


/*
 * �������ƣ�SystemButton_INT ( );
 * �������ܣ�ϵͳ������ʼ��
 * �������ݣ���
 * ������ݣ���
*/
/** Configure pins as 


*/
void Keyboard_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();


  /*Configure GPIO pins : KEY5_Pin KEY6_Pin KEY3_Pin KEY4_Pin */
  GPIO_InitStruct.Pin = KEY5_Pin|KEY6_Pin|KEY3_Pin|KEY4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);


  /*Configure GPIO pins : KEY1_Pin KEY2_Pin */
  GPIO_InitStruct.Pin = KEY1_Pin|KEY2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}
 




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
