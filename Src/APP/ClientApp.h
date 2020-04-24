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
* @brief :���ļ����ڲɼ�����ͨ���ն˵���ͨ�ŷ�������
* 
* 
* 
*
* @author :��ΰ
* @date :2017/9/5 14:11
***************************************************************
*/ 
#ifndef _CLIENTAPP_H_
#define _CLIENTAPP_H_
#include "cmsis_os.h"
#include "PubDef.h"

#include "Typedef.h"

#include "FY188Pro.h"
#include "FY2000Pro.h"
#include "HZCRL_XPro.h"
#include "XY188Pro.h"

#include "HT2X188PRO.h"
#include "BRC188PRO.h"
#include "DDF2PRO.h"
#include "NWKmodbus.h"



 
#ifdef _CLIENTAPP_C_
#define CLIENTAPP_EXT
#else
#define CLIENTAPP_EXT extern
#endif
 

#define ClientRepeatNum	3



typedef union
{
	FY188_Send_Uni FY188Data;
	FY2000_Send_Uni FY2000Data;
    
 #ifdef Meter_H_ENABLE
	HZCRL_Send_Uni HZCRLData;
 #endif

#ifdef Meter_XY_ENABLE    
	XY188_Send_Uni XY188Data;
#endif
    
#ifdef Meter_HT2X_ENABLE
	HT2X188_Pack_Uni HT2X188Data;
#endif
    
#ifdef Meter_BRC_ENABLE
	BRC188_Pack_Uni BRC188Data;
#endif
    
#ifdef Meter_DDF2_ENABLE
	DDF2_Pack_Uni   DDF2Data;
#endif

#ifdef Valve_NWK_ENABLE
	NWK_Pack_Uni   NWKData;
#endif
	
}ClientCH1_QSend_Uni;



typedef struct
{
    SysDevPara				Device;					//�豸����������
	HAL_StatusTypeDef		Busy;						//����״̬æ ��־λ
	INT32U				Ticks;						//ϵͳʱ�Ӽ�¼��¼�� ���� �豸���ظ�����
    HAL_StatusTypeDef		RetFlag;					//���سɹ���־ 
    
    INT8U				Repeat;					//���ն��ظ�����
	HAL_StatusTypeDef		CreatFlag;					//ͨ�Ŵ�����־
	FlagStatus				SignleCom;					//���δ��� ���ڹ㲥����  �ǹ㲥����ʱ�ñ�־��λ
	INT16U				UaComFlg;					//������� ���ڱ���첽ͨ�Żش�
	INT8U				Uapack;					//�첽�������� ���

	INT8U PackCreatFlag;								//����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;								//����Э�������� ������Ʋ���
	
	ClientCH1_QSend_Uni		SendData;					//����Э��������
}ClientCtrl_Stru;	//ͨ��״̬������


typedef struct
{
	INT16U Num;					//������¼��
	INT32U LoopSpace;				//�豸ѭ������ ���ʱ��	

}ClientLoopCtrl_Stru;	//ѭ�����տ�����







typedef struct
{
	SysDevPara			Device;
	
	FlagStatus			SignleCom;						    //���δ���
	INT16U			UaComFlg;						        //������� ���ڱ���Ƿ�Ϊ�첽��������  �첽�������� ��������Ϊ0XAAAA
	INT8U			Uapack;                                 //�첽�������� ���

	INT8U PackCreatFlag;								    //����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;								        //����Э�������� ������Ʋ���
	ClientCH1_QSend_Uni	SendData;						    //����Э��������

}ClientCH1_Queue_Stru;


CLIENTAPP_EXT ClientCtrl_Stru ClientCH1Ctrler;				//�����ն�ͨ�ſ�����
CLIENTAPP_EXT ClientLoopCtrl_Stru ClientReadCtrler;			//����ѭ�����տ�����
CLIENTAPP_EXT ClientLoopCtrl_Stru ClientSendCtrler;			//����ѭ�����Ϳ����� �û��豸���ݵ�ѭ���ϴ�



#define ClientCH1_Q_NUM		16						//�����ն�ͨ��ͨ��1��Ϣ���е�����
CLIENTAPP_EXT QueueHandle_t ClientCH1_Msg;				//�����ն�ͨ��ͨ��1��Ϣ����
CLIENTAPP_EXT ClientCH1_Queue_Stru ClientCH1_OutArray[ClientCH1_Q_NUM];		//�����ն�ͨ��ͨ��1�������
CLIENTAPP_EXT ClientCH1_Queue_Stru* ClientCH1_OutArrayP[ClientCH1_Q_NUM];	//�����ն�ͨ��ͨ��1�������ָ��


CLIENTAPP_EXT INT8U ClientCH1_Q_NUM_Record;					//��ջ������


CLIENTAPP_EXT ClientCH1_Queue_Stru ClientCH1_QueueBF;       	//��Ϣ���л��������
CLIENTAPP_EXT ClientCH1_Queue_Stru* ClientCH1_QueueBFP;       	//��Ϣ���л��������ָ��

CLIENTAPP_EXT ClientCH1_Queue_Stru ClientCH1_QueueIN;       	//��Ϣ�Զ����� ���뻺��
//CLIENTAPP_EXT SemaphoreHandle_t ClientCH1Semaphore;			//ͨ��ռ��/�ȴ����ն�ֵ�ź���





#ifdef _CLIENTAPP_C_




#endif
 





typedef struct
{
	INT8U PackCreatFlag;			//����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;				//����Э�������� ������Ʋ���
	INT32U ID;						//�豸���

	ClientCH1_QSend_Uni SendData;	//����������
}UART_TO_FY188_QueueSend_Stru;

#define UART_TO_FY188_Q_NUM		4						//���巢����Ϣ���е�����
CLIENTAPP_EXT QueueHandle_t UART_TO_FY188_Msg;					//Э���������Ϣ���о��
CLIENTAPP_EXT UART_TO_FY188_QueueSend_Stru UART_TO_FY188_OutArray[UART_TO_FY188_Q_NUM];
CLIENTAPP_EXT UART_TO_FY188_QueueSend_Stru* UART_TO_FY188_OutArrayP[UART_TO_FY188_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_FY188_OutRecord;	//��ջ������
CLIENTAPP_EXT BaseType_t UART_TO_FY188_CCB_QueueSend(UART_TO_FY188_QueueSend_Stru *DATAIN);











typedef struct
{
	INT8U PackCreatFlag;				//����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;				//����Э�������� ������Ʋ���
	INT32U ID;						//�豸���
	ClientCH1_QSend_Uni	SendData;    	//����������

}UART_TO_FY2000_QueueSend_Stru;

#define UART_TO_FY2000_Q_NUM		4						//���巢����Ϣ���е�����
CLIENTAPP_EXT QueueHandle_t UART_TO_FY2000_Msg;					//Э���������Ϣ���о��
CLIENTAPP_EXT UART_TO_FY2000_QueueSend_Stru UART_TO_FY2000_OutArray[UART_TO_FY2000_Q_NUM];
CLIENTAPP_EXT UART_TO_FY2000_QueueSend_Stru* UART_TO_FY2000_OutArrayP[UART_TO_FY2000_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_FY2000_OutRecord;	//��ջ������
CLIENTAPP_EXT BaseType_t UART_TO_FY2000_CCB_QueueSend(UART_TO_FY2000_QueueSend_Stru *InPut);



#ifdef Meter_H_ENABLE

typedef struct
{
	INT8U PackCreatFlag;			    //����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;				    //����Э�������� ������Ʋ���
	INT32U ID;						    //�豸���
	
	ClientCH1_QSend_Uni	SendData;    	//����������
}UART_TO_HZCRL_QueueSend_Stru;

#define UART_TO_HZCRL_Q_NUM		4						//���巢����Ϣ���е�����
CLIENTAPP_EXT QueueHandle_t UART_TO_HZCRL_Msg;					//Э���������Ϣ���о��
CLIENTAPP_EXT UART_TO_HZCRL_QueueSend_Stru UART_TO_HZCRL_OutArray[UART_TO_HZCRL_Q_NUM];
CLIENTAPP_EXT UART_TO_HZCRL_QueueSend_Stru* UART_TO_HZCRL_OutArrayP[UART_TO_HZCRL_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_HZCRL_OutRecord;	//��ջ������
CLIENTAPP_EXT BaseType_t UART_TO_HZCRL_CCB_QueueSend(UART_TO_HZCRL_QueueSend_Stru *DATAIN);
#endif






#ifdef Meter_XY_ENABLE

typedef struct
{
	INT8U PackCreatFlag;			//����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;				//����Э�������� ������Ʋ���
	INT32U ID;						//�豸���

	ClientCH1_QSend_Uni SendData;		//����������
}UART_TO_XY188_QueueSend_Stru;

#define UART_TO_XY188_Q_NUM		4						//���巢����Ϣ���е�����
CLIENTAPP_EXT QueueHandle_t UART_TO_XY188_Msg;					//Э���������Ϣ���о��
CLIENTAPP_EXT UART_TO_XY188_QueueSend_Stru UART_TO_XY188_OutArray[UART_TO_XY188_Q_NUM];
CLIENTAPP_EXT UART_TO_XY188_QueueSend_Stru* UART_TO_XY188_OutArrayP[UART_TO_XY188_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_XY188_OutRecord;	//��ջ������
CLIENTAPP_EXT BaseType_t UART_TO_XY188_CCB_QueueSend(UART_TO_XY188_QueueSend_Stru *DATAIN);
CLIENTAPP_EXT BaseType_t XY_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
CLIENTAPP_EXT BaseType_t HZCRL_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
#endif



#ifdef Meter_HT2X_ENABLE

typedef struct
{
	INT8U PackCreatFlag;				//����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;				    //����Э�������� ������Ʋ���
	INT32U ID;						    //�豸���
	INT8U Type;                         //�豸���Ͳ���

	ClientCH1_QSend_Uni SendData;		//����������
}UART_TO_HT2X188_QueueSend_Stru;

#define UART_TO_HT2X188_Q_NUM		4						//���巢����Ϣ���е�����
CLIENTAPP_EXT QueueHandle_t UART_TO_HT2X188_Msg;					//Э���������Ϣ���о��
CLIENTAPP_EXT UART_TO_HT2X188_QueueSend_Stru UART_TO_HT2X188_OutArray[UART_TO_HT2X188_Q_NUM];
CLIENTAPP_EXT UART_TO_HT2X188_QueueSend_Stru* UART_TO_HT2X188_OutArrayP[UART_TO_HT2X188_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_HT2X188_OutRecord;	//��ջ������
CLIENTAPP_EXT BaseType_t UART_TO_HT2X188_CCB_QueueSend(UART_TO_HT2X188_QueueSend_Stru *DATAIN);
CLIENTAPP_EXT BaseType_t HT2X_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
#endif





#ifdef Meter_BRC_ENABLE

typedef struct
{
	INT8U PackCreatFlag;			//����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;				//����Э�������� ������Ʋ���
	INT32U ID;						//�豸���

	ClientCH1_QSend_Uni SendData;	//����������
}UART_TO_BRC188_QueueSend_Stru;

#define UART_TO_BRC188_Q_NUM		4						//���巢����Ϣ���е�����
CLIENTAPP_EXT QueueHandle_t UART_TO_BRC188_Msg;					//Э���������Ϣ���о��
CLIENTAPP_EXT UART_TO_BRC188_QueueSend_Stru UART_TO_BRC188_OutArray[UART_TO_BRC188_Q_NUM];
CLIENTAPP_EXT UART_TO_BRC188_QueueSend_Stru* UART_TO_BRC188_OutArrayP[UART_TO_BRC188_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_BRC188_OutRecord;	//��ջ������
CLIENTAPP_EXT BaseType_t UART_TO_BRC188_CCB_QueueSend(UART_TO_BRC188_QueueSend_Stru *DATAIN);
CLIENTAPP_EXT BaseType_t BRC_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
#endif




#ifdef Meter_DDF2_ENABLE

typedef struct
{
	INT8U PackCreatFlag;            //����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;				//����Э�������� ������Ʋ���
	INT32U ID;						//�豸���
	INT8U COM_Type;                 //ǰ������

	ClientCH1_QSend_Uni SendData;		                        //����������
}UART_TO_DDF2_QueueSend_Stru;

#define UART_TO_DDF2_Q_NUM		4						        //���巢����Ϣ���е�����
CLIENTAPP_EXT QueueHandle_t UART_TO_DDF2_Msg;					//Э���������Ϣ���о��
CLIENTAPP_EXT UART_TO_DDF2_QueueSend_Stru UART_TO_DDF2_OutArray[UART_TO_DDF2_Q_NUM];
CLIENTAPP_EXT UART_TO_DDF2_QueueSend_Stru* UART_TO_DDF2_OutArrayP[UART_TO_DDF2_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_DDF2_OutRecord;	//��ջ������
CLIENTAPP_EXT BaseType_t UART_TO_DDF2_CCB_QueueSend(UART_TO_DDF2_QueueSend_Stru *DATAIN);
CLIENTAPP_EXT BaseType_t DDF2_Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
#endif




#ifdef Valve_NWK_ENABLE
typedef struct
{
	INT8U PackCreatFlag;            //����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;				//����Э�������� ������Ʋ���
	INT32U ID;						//�豸���
	INT8U COM_Type;                 //ǰ������

	ClientCH1_QSend_Uni SendData;		                        //����������
}UART_TO_NWK_QueueSend_Stru;

#define UART_TO_NWK_Q_NUM		4						        //���巢����Ϣ���е�����
CLIENTAPP_EXT QueueHandle_t UART_TO_NWK_Msg;					//Э���������Ϣ���о��
CLIENTAPP_EXT UART_TO_NWK_QueueSend_Stru UART_TO_NWK_OutArray[UART_TO_NWK_Q_NUM];
CLIENTAPP_EXT UART_TO_NWK_QueueSend_Stru* UART_TO_NWK_OutArrayP[UART_TO_NWK_Q_NUM];

CLIENTAPP_EXT INT8U UART_TO_NWK_OutRecord;	//��ջ������
CLIENTAPP_EXT BaseType_t UART_TO_NWK_CCB_QueueSend(UART_TO_NWK_QueueSend_Stru *DATAIN);
CLIENTAPP_EXT BaseType_t NWK_Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
#endif






CLIENTAPP_EXT BaseType_t ClientCH1_QueueSend( ClientCH1_Queue_Stru *Input);
CLIENTAPP_EXT BaseType_t FY_188Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );
CLIENTAPP_EXT BaseType_t FY_2000Send_Code_QInput(ClientCH1_Queue_Stru*DataBuffer_P,INT8U PackPort );






CLIENTAPP_EXT int ClientCH1SendMetexInit(void);




#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
