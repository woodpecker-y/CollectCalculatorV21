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
* @date :2017/8/24 18:51
***************************************************************
*/ 
#ifndef _FRAM_H_
#define _FRAM_H_
 

#include "M4_IIC1.h"
#include "Typedef.h"
#include "CRC16.h"
#include "string.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"

 
#ifdef _FRAM_C_
#define FRAM_EXT
#else
#define FRAM_EXT extern
#endif
 

#define FRAM_WP_Pin GPIO_PIN_5
#define FRAM_WP_GPIO_Port GPIOB
#define FRAM_WP_Enable	(HAL_GPIO_WritePin(FRAM_WP_GPIO_Port, FRAM_WP_Pin, GPIO_PIN_SET))
#define FRAM_WP_Disable	(HAL_GPIO_WritePin(FRAM_WP_GPIO_Port, FRAM_WP_Pin, GPIO_PIN_RESET))




#define	FRAM_ID		    0X50			//�����ӵ�ַ
#define	FRAM_Size			(1024*32ul)	    //�洢����  8K�ֽ�
#define 	FRAM_DaBuf_Size		(1024*2ul)		//����FRAM ��д��������С
#define 	FRAM_RW_Timeout	(1000ul)		//����FRAM ��д��ʱʱ�� ��λ����
#define	FRAM_MEMADD_SIZE	I2C_MEMADD_SIZE_16BIT	//����洢����ַ����

 




 
#ifdef _FRAM_C_


INT8U tempbuf[FRAM_DaBuf_Size];

#endif
 



FRAM_EXT void FRAM_Init(void);
FRAM_EXT HAL_StatusTypeDef FRAM_Write(INT16U addr,INT16U Length,INT8U* DATA); //�����ӵ�ַ  ���ݳ���  ����ָ��
FRAM_EXT HAL_StatusTypeDef FRAM_Read(INT16U addr,INT16U Length,INT8U* DATA);//�����ӵ�ַ  ���ݳ���  ����ָ��
FRAM_EXT INT8U ReadData_FRAM(INT16U FM_Addr,INT8U *dstp,INT16U Byte_num);
FRAM_EXT INT8U WriteData_FRAM(INT16U FM_Addr,INT8U *srcp,INT16U Byte_num);





 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
