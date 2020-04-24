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
* @brief :M4_CRC������������ļ�
* 
* 
* 
*
* @author :��ΰ
* @date :2017/8/25 8:52
***************************************************************
*/ 
#define _M4_CRC_C_
#include "M4_CRC.h"
#include "main.h"






/* CRC init function */
static void MX_CRC_Init(void)
{

  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}





void M4_CRC_PHY_Init(void)
{

	MX_CRC_Init();

}

/*

��������:ʹ��STM32CRCӲ������CRC32
ע������:1.��������Ϊuint32_t*


*/
uint32_t M4_CRC32_Calculate(uint32_t pBuffer[], uint32_t BufferLength)
{
	
	return HAL_CRC_Calculate(&hcrc, pBuffer,  BufferLength);
}




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
