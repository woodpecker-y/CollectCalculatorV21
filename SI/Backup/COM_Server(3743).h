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
* @author :��ΰ
* @date :2017/5/15 17:34
***************************************************************
*/ 
#ifndef _COM_SERVER_H_
#define _COM_SERVER_H_
#include "stm32f4xx_hal_msp.h"
#include "TypeDef.h"
#include "M4_UART1.h"
#include "M4_UART2.h"
#include "M4_UART3.h"
#include "UART_RBC.h"
#include "cmsis_os.h"
#include "DMA_AddCfg.h"
#include "pubdef.h"


#ifdef _COM_SERVER_C_
#define COM_SERVER_EXT
#else
#define COM_SERVER_EXT extern
#endif
 




 



 
#ifdef _COM_SERVER_C_



INT32U* UART1_TO_CCB_Tick =(INT32U*)&SystemTick_ms;
INT32U* UART2_TO_CCB_Tick =(INT32U*)&SystemTick_ms;
INT32U* UART3_TO_CCB_Tick =(INT32U*)&SystemTick_ms;

void APP_TO_UART1_TXServer( UART_RBC_Stru* Ctrl_Point );
void APP_TO_UART2_TXServer( UART_RBC_Stru* Ctrl_Point );
void APP_TO_UART3_TXServer( UART_RBC_Stru* Ctrl_Point );

#endif

 
COM_SERVER_EXT INT8U SUMCheck_Input(INT8U *Msg,INT32U Lenth);
COM_SERVER_EXT INT8U SUMCheck_Check(INT8U *Msg,INT32U Lenth);

COM_SERVER_EXT INT16U LittleANDBig_ModeCON2(INT16U*Input);
COM_SERVER_EXT INT32U LittleANDBig_ModeCON4(INT32U*Input);





/*
	FY188������ͨ�ſ���ģ��
*/

#define UART_TO_FY188BufferSize_S		128							        //����������
#define UART_TO_FY188PackSize_S		(UART_TO_FY188BufferSize_S/4)
#define UART_TO_FY188_TimeOut_S		50
COM_SERVER_EXT UART_RBC_Stru *UART_TO_FY188_CCB_S;					        //�������ƿ�ָ��
COM_SERVER_EXT INT8U UART_TO_FY188_Buffer_S[UART_TO_FY188BufferSize_S];	    //���н��ջ�����
COM_SERVER_EXT INT8U UART_TO_FY188_InputPack_S[UART_TO_FY188PackSize_S];	//��ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_FY188_OutputPack_S[UART_TO_FY188PackSize_S];	//���ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_FY188_CCB_Init_S( void);







/*
	FY2000������ͨ�ſ���ģ��
*/
#define UART_TO_FY2000BufferSize_S		512							//����������
#define UART_TO_FY2000PackSize_S		(UART_TO_FY2000BufferSize_S/4)
#define UART_TO_FY2000_TimeOut_S		50
COM_SERVER_EXT UART_RBC_Stru *UART_TO_FY2000_CCB_S;					//�������ƿ�ָ��
COM_SERVER_EXT INT8U UART_TO_FY2000_Buffer_S[UART_TO_FY2000BufferSize_S];	//���н��ջ�����
COM_SERVER_EXT INT8U UART_TO_FY2000_InputPack_S[UART_TO_FY2000PackSize_S];	//��ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_FY2000_OutputPack_S[UART_TO_FY2000PackSize_S];//���ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_FY2000_CCB_Init_S( void);





/*
	FY1000�ն˲�ͨ�ſ���ģ��
*/

#define UART_TO_FY1000BufferSize_S		1024ul*4						//����������
#define UART_TO_FY1000PackSize_S		(UART_TO_FY1000BufferSize_S/8)
#define UART_TO_FY1000_TimeOut_S		50
COM_SERVER_EXT UART_RBC_Stru *UART_TO_FY1000_CCB_S;					//�������ƿ�ָ��
COM_SERVER_EXT INT8U UART_TO_FY1000_Buffer_S[UART_TO_FY1000BufferSize_S];	//���н��ջ�����
COM_SERVER_EXT INT8U UART_TO_FY1000_InputPack_S[UART_TO_FY1000PackSize_S];	//��ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_FY1000_OutputPack_S[UART_TO_FY1000PackSize_S];//���ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_FY1000_CCB_Init_S( void);



/*
	���� HZCRL������ͨ�ſ���ģ��
*/
#ifdef  Meter_H_ENABLE

#define UART_TO_HZCRLBufferSize_S   256							//����������
#define UART_TO_HZCRLPackSize_S		(UART_TO_FY188BufferSize_S/4)
#define UART_TO_HZCRL_TimeOut_S		50


COM_SERVER_EXT UART_RBC_Stru *UART_TO_HZCRL_CCB_S;					//�������ƿ�ָ��
COM_SERVER_EXT INT8U UART_TO_HZCRL_Buffer_S[UART_TO_HZCRLBufferSize_S];	//���н��ջ�����
COM_SERVER_EXT INT8U UART_TO_HZCRL_InputPack_S[UART_TO_HZCRLPackSize_S];	//��ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_HZCRL_OutputPack_S[UART_TO_HZCRLPackSize_S];	//���ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_HZCRL_CCB_Init_S( void);
#endif





/*
	��Դ 188������ͨ�ſ���ģ��
*/
#ifdef  Meter_XY_ENABLE	

#define UART_TO_XY188BufferSize_S       256							//����������
#define UART_TO_XY188PackSize_S         (UART_TO_XY188BufferSize_S/4)
#define UART_TO_XY188_TimeOut_S         50


COM_SERVER_EXT UART_RBC_Stru *UART_TO_XY188_CCB_S;					        //�������ƿ�ָ��
COM_SERVER_EXT INT8U UART_TO_XY188_Buffer_S[UART_TO_XY188BufferSize_S];	    //���н��ջ�����
COM_SERVER_EXT INT8U UART_TO_XY188_InputPack_S[UART_TO_XY188PackSize_S];	//��ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_XY188_OutputPack_S[UART_TO_XY188PackSize_S];	//���ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_XY188_CCB_Init_S( void);
#endif






/*
	��ͨ 188������ͨ�ſ���ģ��
*/
#ifdef  Meter_HT2X_ENABLE

#define UART_TO_HT2X188BufferSize_S		256							//����������
#define UART_TO_HT2X188PackSize_S		(UART_TO_HT2X188BufferSize_S/4)
#define UART_TO_HT2X188_TimeOut_S		50

	
COM_SERVER_EXT UART_RBC_Stru *UART_TO_HT2X188_CCB_S;					        //�������ƿ�ָ��
COM_SERVER_EXT INT8U UART_TO_HT2X188_Buffer_S[UART_TO_HT2X188BufferSize_S];	    //���н��ջ�����
COM_SERVER_EXT INT8U UART_TO_HT2X188_InputPack_S[UART_TO_HT2X188PackSize_S];	//��ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_HT2X188_OutputPack_S[UART_TO_HT2X188PackSize_S];	//���ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_HT2X188_CCB_Init_S( void);
#endif




/*
	�������� BRC������ͨ�ſ���ģ��
*/
#ifdef  Meter_BRC_ENABLE

#define UART_TO_BRC188BufferSize_S		256							//����������
#define UART_TO_BRC188PackSize_S		(UART_TO_BRC188BufferSize_S/4)
#define UART_TO_BRC188_TimeOut_S		50

	
COM_SERVER_EXT UART_RBC_Stru *UART_TO_BRC188_CCB_S;					            //�������ƿ�ָ��
COM_SERVER_EXT INT8U UART_TO_BRC188_Buffer_S[UART_TO_BRC188BufferSize_S];	    //���н��ջ�����
COM_SERVER_EXT INT8U UART_TO_BRC188_InputPack_S[UART_TO_BRC188PackSize_S];	    //��ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_BRC188_OutputPack_S[UART_TO_BRC188PackSize_S];	    //���ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_BRC188_CCB_Init_S( void);
#endif


/*
	��ͨͨ�Ͽ����� DDF2������ͨ�ſ���ģ��
*/
#ifdef  Meter_DDF2_ENABLE	

#define UART_TO_DDF2BufferSize_S		256							//����������
#define UART_TO_DDF2PackSize_S		    (UART_TO_DDF2BufferSize_S/4)
#define UART_TO_DDF2_TimeOut_S		    50


COM_SERVER_EXT UART_RBC_Stru *UART_TO_DDF2_CCB_S;					        //�������ƿ�ָ��
COM_SERVER_EXT INT8U UART_TO_DDF2_Buffer_S[UART_TO_DDF2BufferSize_S];	    //���н��ջ�����
COM_SERVER_EXT INT8U UART_TO_DDF2_InputPack_S[UART_TO_DDF2PackSize_S];	    //��ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_DDF2_OutputPack_S[UART_TO_DDF2PackSize_S];	    //���ڶ�ջ������
COM_SERVER_EXT INT8U UART_TO_DDF2_CCB_Init_S( void);
#endif










#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
