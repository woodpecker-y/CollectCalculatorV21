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
* @brief :���ļ����ڲɼ�����ͨ���ն˵���ͨ�ŷ�������
* 
* 
* 
*
* @author :��ΰ
* @date :2017/9/5 14:11
***************************************************************
*/ 
#define _CLIENTAPP_C_
#include "ClientApp.h"
#include "NWKmodbus.h"


BaseType_t UART_TO_FY188_CCB_QueueSend(UART_TO_FY188_QueueSend_Stru *DATAIN)
{

	BaseType_t err;
	err =err;

	UART_TO_FY188_OutArray[UART_TO_FY188_OutRecord] =*DATAIN;
	UART_TO_FY188_OutArrayP[UART_TO_FY188_OutRecord] =&UART_TO_FY188_OutArray[UART_TO_FY188_OutRecord];

	
    //������Ϣ
    err = xQueueSend(UART_TO_FY188_Msg, &UART_TO_FY188_OutArrayP[UART_TO_FY188_OutRecord] , 20);
	UART_TO_FY188_OutRecord +=1;
	if(UART_TO_FY188_OutRecord >=UART_TO_FY188_Q_NUM)
	{
		UART_TO_FY188_OutRecord =0;
	}
	return err;
}



BaseType_t UART_TO_FY2000_CCB_QueueSend(UART_TO_FY2000_QueueSend_Stru *InPut)
{

	BaseType_t err;
	err =err;

	UART_TO_FY2000_OutArray[UART_TO_FY2000_OutRecord] =*InPut;
	UART_TO_FY2000_OutArrayP[UART_TO_FY2000_OutRecord] =&UART_TO_FY2000_OutArray[UART_TO_FY2000_OutRecord];

    //������Ϣ
    err = xQueueSend(UART_TO_FY2000_Msg, &UART_TO_FY2000_OutArrayP[UART_TO_FY2000_OutRecord], 20);
	UART_TO_FY2000_OutRecord +=1;
	if(UART_TO_FY2000_OutRecord >=UART_TO_FY2000_Q_NUM)
	{
		UART_TO_FY2000_OutRecord =0;
	}
	return err;

}






#ifdef Meter_H_ENABLE
BaseType_t UART_TO_HZCRL_CCB_QueueSend(UART_TO_HZCRL_QueueSend_Stru *DATAIN)
{

	BaseType_t err;
	err =err;

	UART_TO_HZCRL_OutArray[UART_TO_HZCRL_OutRecord] =*DATAIN;
	UART_TO_HZCRL_OutArrayP[UART_TO_HZCRL_OutRecord] =&UART_TO_HZCRL_OutArray[UART_TO_HZCRL_OutRecord];
	
	
	//������Ϣ
	err = xQueueSend(UART_TO_HZCRL_Msg, &UART_TO_HZCRL_OutArrayP[UART_TO_HZCRL_OutRecord], 20);
	UART_TO_HZCRL_OutRecord +=1;
	if(UART_TO_HZCRL_OutRecord >=UART_TO_HZCRL_Q_NUM)
	{
		UART_TO_HZCRL_OutRecord =0;
	}
	return err;
}
#endif




#ifdef Meter_XY_ENABLE

BaseType_t UART_TO_XY188_CCB_QueueSend(UART_TO_XY188_QueueSend_Stru *DATAIN)
{

	BaseType_t err;
	err =err;

	UART_TO_XY188_OutArray[UART_TO_XY188_OutRecord] =*DATAIN;
	UART_TO_XY188_OutArrayP[UART_TO_XY188_OutRecord] =&UART_TO_XY188_OutArray[UART_TO_XY188_OutRecord];

	
    //������Ϣ
    err = xQueueSend(UART_TO_XY188_Msg, &UART_TO_XY188_OutArrayP[UART_TO_XY188_OutRecord] , 20);
	UART_TO_XY188_OutRecord +=1;
	if(UART_TO_XY188_OutRecord >=UART_TO_XY188_Q_NUM)
	{
		UART_TO_XY188_OutRecord =0;
	}
	return err;
}
#endif



#ifdef Meter_HT2X_ENABLE

BaseType_t UART_TO_HT2X188_CCB_QueueSend(UART_TO_HT2X188_QueueSend_Stru *DATAIN)
{

	BaseType_t err;
	err =err;

	UART_TO_HT2X188_OutArray[UART_TO_HT2X188_OutRecord] =*DATAIN;
	UART_TO_HT2X188_OutArrayP[UART_TO_HT2X188_OutRecord] =&UART_TO_HT2X188_OutArray[UART_TO_HT2X188_OutRecord];

	
    //������Ϣ
    err = xQueueSend(UART_TO_HT2X188_Msg, &UART_TO_HT2X188_OutArrayP[UART_TO_HT2X188_OutRecord] , 20);
	UART_TO_HT2X188_OutRecord +=1;
	if(UART_TO_HT2X188_OutRecord >=UART_TO_HT2X188_Q_NUM)
	{
		UART_TO_HT2X188_OutRecord =0;
	}
	return err;
}
#endif



#ifdef Meter_BRC_ENABLE

BaseType_t UART_TO_BRC188_CCB_QueueSend(UART_TO_BRC188_QueueSend_Stru *DATAIN)
{

	BaseType_t err;
	err =err;

	UART_TO_BRC188_OutArray[UART_TO_BRC188_OutRecord] =*DATAIN;
	UART_TO_BRC188_OutArrayP[UART_TO_BRC188_OutRecord] =&UART_TO_BRC188_OutArray[UART_TO_BRC188_OutRecord];

	
    //������Ϣ
    err = xQueueSend(UART_TO_BRC188_Msg, &UART_TO_BRC188_OutArrayP[UART_TO_BRC188_OutRecord] , 20);
	UART_TO_BRC188_OutRecord +=1;
	if(UART_TO_BRC188_OutRecord >=UART_TO_BRC188_Q_NUM)
	{
		UART_TO_BRC188_OutRecord =0;
	}
	return err;
}
#endif




#ifdef Meter_DDF2_ENABLE
BaseType_t UART_TO_DDF2_CCB_QueueSend(UART_TO_DDF2_QueueSend_Stru *DATAIN)
{

	BaseType_t err;
	err =err;

	UART_TO_DDF2_OutArray[UART_TO_DDF2_OutRecord] =*DATAIN;
	UART_TO_DDF2_OutArrayP[UART_TO_DDF2_OutRecord] =&UART_TO_DDF2_OutArray[UART_TO_DDF2_OutRecord];

	
    //������Ϣ
    err = xQueueSend(UART_TO_DDF2_Msg, &UART_TO_DDF2_OutArrayP[UART_TO_DDF2_OutRecord] , 20);
	UART_TO_DDF2_OutRecord +=1;
	if(UART_TO_DDF2_OutRecord >=UART_TO_DDF2_Q_NUM)
	{
		UART_TO_DDF2_OutRecord =0;
	}
	return err;
}
#endif



#ifdef Valve_NWK_ENABLE
BaseType_t UART_TO_NWK_CCB_QueueSend(UART_TO_NWK_QueueSend_Stru *DATAIN)
{

	BaseType_t err;
	err =err;

	UART_TO_NWK_OutArray[UART_TO_NWK_OutRecord] =*DATAIN;
	UART_TO_NWK_OutArrayP[UART_TO_NWK_OutRecord] =&UART_TO_NWK_OutArray[UART_TO_NWK_OutRecord];

	
    //������Ϣ
    err = xQueueSend(UART_TO_NWK_Msg, &UART_TO_NWK_OutArrayP[UART_TO_NWK_OutRecord] , 20);
	UART_TO_NWK_OutRecord +=1;
	if(UART_TO_NWK_OutRecord >=UART_TO_NWK_Q_NUM)
	{
		UART_TO_NWK_OutRecord =0;
	}
	return err;
}
#endif















osMutexId ClientCH1_QMutexHandle;		//ClientCH1_QueueSend  ������

BaseType_t ClientCH1_QueueSend( ClientCH1_Queue_Stru *Input)
{
	BaseType_t err;
	err =err;
	ClientCH1_OutArray[ClientCH1_Q_NUM_Record] = *Input;
	ClientCH1_OutArrayP[ClientCH1_Q_NUM_Record] =&ClientCH1_OutArray[ClientCH1_Q_NUM_Record];

    //������Ϣ
    err = xQueueSend(ClientCH1_Msg, &ClientCH1_OutArrayP[ClientCH1_Q_NUM_Record], 200);

	ClientCH1_Q_NUM_Record +=1;
	if(ClientCH1_Q_NUM_Record >=ClientCH1_Q_NUM)
	{
		ClientCH1_Q_NUM_Record =0;
	}
	return err;
}




/* 
	�ն�ͨ��ͨ����������ʼ��
*/
int ClientCH1SendMetexInit(void)
{
	osMutexDef(ClientCH1SendMutex);
	ClientCH1_QMutexHandle = osMutexCreate(osMutex(ClientCH1SendMutex));
	
	if(ClientCH1_QMutexHandle == NULL)
	{
		return -1;
	}
	return 0;
}






/*
�ɼ���FY188���ݷ��� ����װ�뺯��
��������
*/
BaseType_t FY_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort )
{
	BaseType_t err;
	
	osMutexWait(ClientCH1_QMutexHandle, osWaitForever);
	DataBuffer_P->PackCreatFlag =ENABLE;
	DataBuffer_P->PackINPort =PackPort;
	err =ClientCH1_QueueSend(DataBuffer_P);	//������Ϣ
	osMutexRelease(ClientCH1_QMutexHandle);
	
	return err;
}



/*
�ɼ���FY2000���ݷ��� ����װ�뺯��
��������
*/
BaseType_t FY_2000Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort )
{
	BaseType_t err;
	osMutexWait(ClientCH1_QMutexHandle, osWaitForever);
	DataBuffer_P->PackCreatFlag =ENABLE;
	DataBuffer_P->PackINPort =PackPort;
	err =ClientCH1_QueueSend(DataBuffer_P);	//������Ϣ
	osMutexRelease(ClientCH1_QMutexHandle);
	
	return err;
}





/*
�ɼ���HZCRL_188���ݷ��� ����װ�뺯��
��������
*/
BaseType_t HZCRL_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort )
{
	BaseType_t err;

	osMutexWait(ClientCH1_QMutexHandle, osWaitForever);
	DataBuffer_P->PackCreatFlag =ENABLE;
	DataBuffer_P->PackINPort =PackPort;
	err =ClientCH1_QueueSend(DataBuffer_P);	//������Ϣ
	osMutexRelease(ClientCH1_QMutexHandle);

	
	return err;
}






/*
�ɼ���XY188���ݷ��� ����װ�뺯��
��������
*/
BaseType_t XY_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort )
{
	BaseType_t err;
	
	osMutexWait(ClientCH1_QMutexHandle, osWaitForever);
	DataBuffer_P->PackCreatFlag =ENABLE;
	DataBuffer_P->PackINPort =PackPort;
	err =ClientCH1_QueueSend(DataBuffer_P);	//������Ϣ
	osMutexRelease(ClientCH1_QMutexHandle);
	
	return err;
}


/*
�ɼ���HT2X188���ݷ��� ����װ�뺯��
��������
*/
BaseType_t HT2X_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort )
{
	BaseType_t err;
	
	osMutexWait(ClientCH1_QMutexHandle, osWaitForever);
	DataBuffer_P->PackCreatFlag =ENABLE;
	DataBuffer_P->PackINPort =PackPort;
	err =ClientCH1_QueueSend(DataBuffer_P);	//������Ϣ
	osMutexRelease(ClientCH1_QMutexHandle);
	
	return err;
}


/*
�ɼ���BRC188���ݷ��� ����װ�뺯��
��������
*/
BaseType_t BRC_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort )
{
	BaseType_t err;
	
	osMutexWait(ClientCH1_QMutexHandle, osWaitForever);
	DataBuffer_P->PackCreatFlag =ENABLE;
	DataBuffer_P->PackINPort =PackPort;
	err =ClientCH1_QueueSend(DataBuffer_P);	//������Ϣ
	osMutexRelease(ClientCH1_QMutexHandle);
	
	return err;
}



/*
�ɼ���DDF2���ݷ��� ����װ�뺯��
��������
*/
BaseType_t DDF2_Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort )
{
	BaseType_t err;
	
	osMutexWait(ClientCH1_QMutexHandle, osWaitForever);
	DataBuffer_P->PackCreatFlag =ENABLE;
	DataBuffer_P->PackINPort =PackPort;
	err =ClientCH1_QueueSend(DataBuffer_P);	//������Ϣ
	osMutexRelease(ClientCH1_QMutexHandle);
	
	return err;
}





/*
�ɼ��� ������NWK��Ԫ���ڷ�modbus�� ���ݷ��� ����װ�뺯��
��������
*/
BaseType_t NWK_Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort )
{
	BaseType_t err;
	
	osMutexWait(ClientCH1_QMutexHandle, osWaitForever);
	DataBuffer_P->PackCreatFlag =ENABLE;
	DataBuffer_P->PackINPort =PackPort;
	err =ClientCH1_QueueSend(DataBuffer_P);	//������Ϣ
	osMutexRelease(ClientCH1_QMutexHandle);
	
	return err;
}






 
 




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
