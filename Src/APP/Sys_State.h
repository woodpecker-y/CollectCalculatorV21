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
* @date :2017/9/15 14:07
***************************************************************
*/ 
#ifndef _SYS_STATE_H_
#define _SYS_STATE_H_
 

#include "TypeDef.h"
#include "stm32f4xx_hal.h"

#include "PubDef.h"

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "debug.h"
#include <stdlib.h>




 
#ifdef _SYS_STATE_C_
#define SYS_STATE_EXT
#else
#define SYS_STATE_EXT extern
#endif
 




typedef struct
{
		INT8U	IPA1;			//IP��ַ1��
		INT8U	IPA2;			//IP��ַ2��
		INT8U	IPA3;			//IP��ַ3��
		INT8U	IPA4;			//IP��ַ4��
		INT16U	Port;			//�˿ں�	

		INT8U	IPB1;			//IP��ַ1��
		INT8U	IPB2;			//IP��ַ2��
		INT8U	IPB3;			//IP��ַ3��
		INT8U	IPB4;			//IP��ַ4��
		INT8U	CCID[20];		//�ֻ�����ʶ

		INT8U GPRS_Power_Flg;	//��Դ��־
		INT8U GPRS_ONOFF_Flg;	//���ػ���־
		INT8U SIMCard_State;		//�ֻ���״̬

		INT8U CSQ1;			//�ź�ǿ��1
		INT8U CSQ2;			//�ź�ǿ��2
}Ext_GPRS_Str;
SYS_STATE_EXT Ext_GPRS_Str GPRS_State;











void printenv(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);

void userpara(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void devicepara(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void userdata(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void devicedata(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void devicestatus(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);

void systemparareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void userparareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void deviceparareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void userdatareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void devicedatareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void sysdataresetall(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void settime(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void settime_s(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void settime_f(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void setsystype(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void Updatedebug(INT32U enable, INT32U level);
void devchange(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void changeDeviceNum(INT16U num);
void setsn(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void setread(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void setsend(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void setshare(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void powrelayctrl(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void ddf2ctrl(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);
void ClirateSet(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv);





 
#ifdef _SYS_STATE_C_




#endif
 




 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
