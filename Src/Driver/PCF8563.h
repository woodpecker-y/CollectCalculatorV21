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
* @date :2017/8/25 10:45
***************************************************************
*/ 
#ifndef _PCF8563_H_
#define _PCF8563_H_

#include "stm32f4xx_hal.h"
#include "TypeDef.h"
#include "M4_IIC2.h"
#include "RTC.h"


 
#ifdef _PCF8563_C_
#define PCF8563_EXT
#else
#define PCF8563_EXT extern
#endif
 
#define PCF8563_MEMADD_SIZE I2C_MEMADD_SIZE_8BIT

#define Adjust_delay	(1000UL*60*30)

#define PCF8563_ID		0X51        //оƬ��ַ1010001
#define PCF8563START	1
#define PCF8563STOP	0

//PCF8563�ӵ�ַ(�Ĵ���)�궨��
#define SECADD		0X02        //��
#define MINADD		0X03        //��
#define HOUADD		0X04        //ʱ
#define DAYADD		0X05        //��
#define WEEADD		0X06        //��
#define MONADD		0X07        //��
#define YEAADD		0X08        //��

#define MINALMADD		0X09        //�ֱ���
#define HOUALMADD		0X0A        //ʱ����
#define DAYALMADD		0X0B        //�ձ���
#define WEEALMADD		0X0C        //�ܱ���

#define CON1ADD		0X00        //���ƼĴ���
#define CON2ADD		0X01
#define CLKOADD		0X0D        //ʱ������Ĵ���
#define TIMCADD		0X0E        //��ʱ�����ƼĴ���
#define TIMNADD		0X0F        //��ʱ����ֵ�Ĵ���

#define FIRST_DAY_YEAR	2000        //������ʼ��



 
 




 
#ifdef _PCF8563_C_




#endif
 


PCF8563_EXT HAL_StatusTypeDef PCF8563_Set(RealClock_Str * RealTime);
PCF8563_EXT HAL_StatusTypeDef PCF8563_Read(RealClock_Str* RealTime);

 
 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
