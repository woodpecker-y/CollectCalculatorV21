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
* @author :��ΰ
* @date :2017/5/15 17:34
***************************************************************
*/ 
#define _COM_SERVER_C_
#include "COM_Server.h"
#include "main.h"
 



 


/*
 �������ƣ�INT8U SUMCheck_Input(INT8U *Msg,INT32U Lenth)
 �������ܣ�У��������Ӻ��������������ݵ�У��͸��ֽ�����������ֽڷ���
	INT8U *Msg   ����ָ��
	INT16S Lenth	 ���ݳ���
*/
INT8U SUMCheck_Input(INT8U *Msg,INT32U Lenth)
{
	INT16U buffer =0;
	INT8U Test =0;
	INT8U* MsgP;
	MsgP=Msg;
	while(Lenth--)
	{
		buffer=buffer +(*MsgP);
		MsgP++;
	};
	Test =buffer&0X00FF;

	return  Test;
}

/*
 �������ƣ� INT8U SUMCheck_Check(INT8U *Msg,INT32U Lenth)
 
 �������ܣ���У�����Ӻ���������������������ѭ��У���벢��������Ƿ���ڴ���
	INT8U *Msg   ����ָ��
	INT16S Lenth	 ���ݳ���
*/
INT8U SUMCheck_Check(INT8U *Msg,INT32U Lenth)
{
	INT8U ErrFlg=0;
	INT16U buffer =0;
	INT8U Test =0;
	INT8U* MsgP;
	MsgP=Msg;
	while(Lenth--)
	{
		buffer=buffer +(*MsgP);
		MsgP++;
	}
	Test =(buffer&0X00FF);
	if(Test != *MsgP) 
	{
		ErrFlg = Test;
	}
	else
	{
		ErrFlg = 0X00;
	}
	return  ErrFlg;
}




/*
��������:LittleANDBig_ModeCON2
��������:��һ��INT16U���ݽ��д�С��ģʽ�л�

*/
INT16U LittleANDBig_ModeCON2(INT16U*Input)
{
	INT16U DATAOUT =0;
	INT16U DATAIN =*Input;
	DATAOUT =((DATAIN&0X00FF )<<8)|((DATAIN&0XFF00 )>>8);
	return DATAOUT;
}


/*
��������:LittleANDBig_ModeCON4
��������:��һ��INT32U���ݽ��д�С��ģʽ�л�

*/
INT32U LittleANDBig_ModeCON4(INT32U*Input)
{
	INT32U DATAOUT =0;
	INT32U DATAIN =*Input;

	DATAOUT =((DATAIN&0X000000FF )<<24)|((DATAIN&0X0000FF00 )<<8)|((DATAIN&0X00FF0000 )>>8)|((DATAIN&0XFF000000 )>>24);
	return DATAOUT;
}





/*
UART_TO_FY188_CCB_Init_S ���ƿ��ʼ�� �����
*/
INT8U UART_TO_FY188_CCB_Init_S( void)
{
	INT8U BackVal =0;

	BackVal =UART_RBC_Creat(&UART_TO_FY188_CCB_S,UART_TO_FY188_Buffer_S,UART_TO_FY188BufferSize_S, UART_TO_FY188_InputPack_S, UART_TO_FY188_OutputPack_S,UART_TO_FY188PackSize_S ,UART3_TO_CCB_Tick, UART_TO_FY188_TimeOut_S);//���ƿ��ʼ��

	UART_RBC_InputHandle_Init( UART_TO_FY188_CCB_S,FY188_Pack_RxServer_S);//�������ҽ�
	UART_RBC_OutputHandle_Init( UART_TO_FY188_CCB_S,APP_TO_UART3_TXServer,&UART3_Busy);//�������ҽ�
	UART_RBC_Enable( UART_TO_FY188_CCB_S,ENABLE);	//ģ��ʹ��
	return BackVal;
}


#ifdef Meter_H_ENABLE
/*
UART_TO_HZCRL_CCB_Init_S ���ƿ��ʼ�� �����
*/
INT8U UART_TO_HZCRL_CCB_Init_S( void)
{
	INT8U BackVal =0;

	BackVal =UART_RBC_Creat(&UART_TO_HZCRL_CCB_S,UART_TO_HZCRL_Buffer_S,UART_TO_HZCRLBufferSize_S, UART_TO_HZCRL_InputPack_S, UART_TO_HZCRL_OutputPack_S,UART_TO_HZCRLPackSize_S ,UART3_TO_CCB_Tick, UART_TO_HZCRL_TimeOut_S);//���ƿ��ʼ��

	UART_RBC_InputHandle_Init( UART_TO_HZCRL_CCB_S,HZCRL_Pack_RxServer_S);//�������ҽ�
	UART_RBC_OutputHandle_Init( UART_TO_HZCRL_CCB_S,APP_TO_UART3_TXServer,&UART3_Busy);//�������ҽ�
	UART_RBC_Enable( UART_TO_HZCRL_CCB_S,ENABLE);	//ģ��ʹ��
	return BackVal;
}
#endif


/*
UART_TO_FY2000_CCB_Init_S ���ƿ��ʼ�� �����
*/
INT8U UART_TO_FY2000_CCB_Init_S( void)
{
	INT8U BackVal =0;

	BackVal =UART_RBC_Creat(&UART_TO_FY2000_CCB_S,UART_TO_FY2000_Buffer_S,UART_TO_FY2000BufferSize_S, UART_TO_FY2000_InputPack_S, UART_TO_FY2000_OutputPack_S,UART_TO_FY2000PackSize_S ,UART3_TO_CCB_Tick, UART_TO_FY2000_TimeOut_S);//���ƿ��ʼ��

	UART_RBC_InputHandle_Init( UART_TO_FY2000_CCB_S,FY2000_Pack_RxServer_S);//�������ҽ�
	UART_RBC_OutputHandle_Init( UART_TO_FY2000_CCB_S,APP_TO_UART3_TXServer,&UART3_Busy);//�������ҽ�
	UART_RBC_Enable( UART_TO_FY2000_CCB_S,ENABLE);	//ģ��ʹ��
	return BackVal;
}









/*
UART_TO_FY1000_CCB_Init_S ���ƿ��ʼ�� �����
*/
INT8U UART_TO_FY1000_CCB_Init_S( void)
{
	INT8U BackVal =0;

	BackVal =UART_RBC_Creat(&UART_TO_FY1000_CCB_S,UART_TO_FY1000_Buffer_S,UART_TO_FY1000BufferSize_S, UART_TO_FY1000_InputPack_S, UART_TO_FY1000_OutputPack_S,UART_TO_FY1000PackSize_S ,UART2_TO_CCB_Tick, UART_TO_FY1000_TimeOut_S);//���ƿ��ʼ��

	UART_RBC_InputHandle_Init( UART_TO_FY1000_CCB_S,FY1000_Pack_RxServer_S);//�������ҽ�
	UART_RBC_OutputHandle_Init( UART_TO_FY1000_CCB_S,APP_TO_UART2_TXServer,&UART2_Busy);//�������ҽ�
	UART_RBC_Enable( UART_TO_FY1000_CCB_S,ENABLE);	//ģ��ʹ��
	return BackVal;
}





#ifdef  Meter_XY_ENABLE	

/*
UART_TO_XY188_CCB_Init_S ���ƿ��ʼ�� �����
*/
INT8U UART_TO_XY188_CCB_Init_S( void)
{
	INT8U BackVal =0;

	BackVal =UART_RBC_Creat(&UART_TO_XY188_CCB_S,UART_TO_XY188_Buffer_S,UART_TO_XY188BufferSize_S, UART_TO_XY188_InputPack_S, UART_TO_XY188_OutputPack_S,UART_TO_XY188PackSize_S ,UART3_TO_CCB_Tick, UART_TO_XY188_TimeOut_S);//���ƿ��ʼ��

	UART_RBC_InputHandle_Init( UART_TO_XY188_CCB_S,XY188_Pack_RxServer_S);//�������ҽ�
	UART_RBC_OutputHandle_Init( UART_TO_XY188_CCB_S,APP_TO_UART3_TXServer,&UART3_Busy);//�������ҽ�
	UART_RBC_Enable( UART_TO_XY188_CCB_S,ENABLE);	//ģ��ʹ��
	return BackVal;
}
#endif




#ifdef  Meter_HT2X_ENABLE	

/*
UART_TO_HT2X188_CCB_Init_S ���ƿ��ʼ�� �����
*/
INT8U UART_TO_HT2X188_CCB_Init_S( void)
{
	INT8U BackVal =0;

	BackVal =UART_RBC_Creat(&UART_TO_HT2X188_CCB_S,UART_TO_HT2X188_Buffer_S,UART_TO_HT2X188BufferSize_S, UART_TO_HT2X188_InputPack_S, UART_TO_HT2X188_OutputPack_S,UART_TO_HT2X188PackSize_S ,UART3_TO_CCB_Tick, UART_TO_HT2X188_TimeOut_S);//���ƿ��ʼ��

	UART_RBC_InputHandle_Init( UART_TO_HT2X188_CCB_S,HT2X188_Pack_RxServer_S);//�������ҽ�
	UART_RBC_OutputHandle_Init( UART_TO_HT2X188_CCB_S,APP_TO_UART3_TXServer,&UART3_Busy);//�������ҽ�
	UART_RBC_Enable( UART_TO_HT2X188_CCB_S,ENABLE);	//ģ��ʹ��
	return BackVal;
}
#endif




#ifdef  Meter_BRC_ENABLE	

/*
UART_TO_BRC188_CCB_Init_S ���ƿ��ʼ�� �����
*/
INT8U UART_TO_BRC188_CCB_Init_S( void)
{
	INT8U BackVal =0;

	BackVal =UART_RBC_Creat(&UART_TO_BRC188_CCB_S,UART_TO_BRC188_Buffer_S,UART_TO_BRC188BufferSize_S, UART_TO_BRC188_InputPack_S, UART_TO_BRC188_OutputPack_S,UART_TO_BRC188PackSize_S ,UART3_TO_CCB_Tick, UART_TO_BRC188_TimeOut_S);//���ƿ��ʼ��

	UART_RBC_InputHandle_Init( UART_TO_BRC188_CCB_S,BRC188_Pack_RxServer_S);//�������ҽ�
	UART_RBC_OutputHandle_Init( UART_TO_BRC188_CCB_S,APP_TO_UART3_TXServer,&UART3_Busy);//�������ҽ�
	UART_RBC_Enable( UART_TO_BRC188_CCB_S,ENABLE);	//ģ��ʹ��
	return BackVal;
}

#endif



#ifdef  Meter_DDF2_ENABLE	

/*
UART_TO_DDF2_CCB_Init_S ���ƿ��ʼ�� �����
*/
INT8U UART_TO_DDF2_CCB_Init_S( void)
{
	INT8U BackVal =0;

	BackVal =UART_RBC_Creat(&UART_TO_DDF2_CCB_S,UART_TO_DDF2_Buffer_S,UART_TO_DDF2BufferSize_S, UART_TO_DDF2_InputPack_S, UART_TO_DDF2_OutputPack_S,UART_TO_DDF2PackSize_S ,UART3_TO_CCB_Tick, UART_TO_DDF2_TimeOut_S);//���ƿ��ʼ��

	UART_RBC_InputHandle_Init( UART_TO_DDF2_CCB_S, DDF2_Pack_RxServer_S);//�������ҽ�
	UART_RBC_OutputHandle_Init( UART_TO_DDF2_CCB_S, APP_TO_UART3_TXServer, &UART3_Busy);//�������ҽ�
	UART_RBC_Enable( UART_TO_DDF2_CCB_S,ENABLE);	//ģ��ʹ��
	return BackVal;
}

#endif


#ifdef  Valve_NWK_ENABLE	
/*
UART_TO_NWK_CCB_Init_S ���ƿ��ʼ�� �����
*/
INT8U UART_TO_NWK_CCB_Init_S( void)
{
	INT8U BackVal =0;

	BackVal =UART_RBC_Creat(&UART_TO_NWK_CCB_S, UART_TO_NWK_Buffer_S, UART_TO_NWKBufferSize_S, UART_TO_NWK_InputPack_S, \
                            UART_TO_NWK_OutputPack_S, UART_TO_NWKPackSize_S, UART3_TO_CCB_Tick, UART_TO_NWK_TimeOut_S);//���ƿ��ʼ��

	UART_RBC_InputHandle_Init( UART_TO_NWK_CCB_S, NWK_Pack_RxServer_S);//�������ҽ�
	UART_RBC_OutputHandle_Init( UART_TO_NWK_CCB_S, APP_TO_UART3_TXServer, &UART3_Busy);//�������ҽ�
	UART_RBC_Enable(UART_TO_NWK_CCB_S, ENABLE);	//ģ��ʹ��
	return BackVal;
}

#endif







/*
APP_TO_UART1 ���ͷ�����
*/
void APP_TO_UART1_TXServer( UART_RBC_Stru* Ctrl_Point )
{
	INT16U DataLenth =0;
	INT8U* Addr;
	HAL_StatusTypeDef BackVal =HAL_OK;
	
	if( Ctrl_Point->PackSendFlag ==ENABLE)
	{
		DataLenth =Ctrl_Point->OutputPackSize;			//���ݷ��Ͱ�����
		Addr =Ctrl_Point->OutputPack;				//���ͻ�������ַ
		BackVal = UART1_Transmit( Addr, DataLenth);	//���ͷ�����������DMA����Ϸ�ʽ
		if( BackVal ==HAL_OK )
		{
			Ctrl_Point->PackSendFlag =DISABLE;		//��־��λ
		}	
	}
}



/*
APP_TO_UART2 ���ͷ�����
*/
void APP_TO_UART2_TXServer( UART_RBC_Stru* Ctrl_Point )
{
	INT16U DataLenth =0;
	INT8U* Addr;
	HAL_StatusTypeDef BackVal =HAL_OK;
	
	if( Ctrl_Point->PackSendFlag ==ENABLE)
	{
		DataLenth =Ctrl_Point->OutputPackSize;	//���ݷ��Ͱ�����
		Addr =Ctrl_Point->OutputPack;	//���ͻ�������ַ
		BackVal = UART2_Transmit( Addr, DataLenth);	//���ͷ�����������DMA����Ϸ�ʽ
		if( BackVal ==HAL_OK )
		{
			Ctrl_Point->PackSendFlag =DISABLE;	//��־��λ
		}	
	}
}


/*
APP_TO_UART3 ���ͷ�����
*/
void APP_TO_UART3_TXServer( UART_RBC_Stru* Ctrl_Point )
{
	INT16U DataLenth =0;
	INT8U* Addr;
	HAL_StatusTypeDef BackVal =HAL_OK;
	
	if( Ctrl_Point->PackSendFlag ==ENABLE)
	{
		DataLenth =Ctrl_Point->OutputPackSize;	//���ݷ��Ͱ�����
		Addr =Ctrl_Point->OutputPack;	//���ͻ�������ַ
		BackVal = UART3_Transmit( Addr, DataLenth);	//���ͷ�����������DMA����Ϸ�ʽ
		if( BackVal ==HAL_OK )
		{
			Ctrl_Point->PackSendFlag =DISABLE;	//��־��λ
		}	
	}
}





/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
