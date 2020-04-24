#include "PubDef.h"
#ifdef Valve_NWK_ENABLE

#ifndef _NWKMODBUS_H
#define _NWKMODBUS_H
#include "main.h"
#include "UART_RBC.h"

 
#ifdef _DDF2PRO_C_
#define NWK_EXT
#else
#define NWK_EXT extern
#endif
 

#define NWKPro_PackSize				UART_TO_NWKPackSize_S
#define NWKPro_HeadSize				11				    //���ݰ�ͷ��С
#define NWKPro_StartCode			0X68				//��ʼ��
#define NWKPro_ProtocolCode		0X41				//�汾��
#define NWKPro_EndCode				0X16				//������



#pragma pack(1)		//�ֽڶ���
typedef struct
{

	INT8U	Addr;		//��ʼ�ַ�		1�ֽ�
	INT8U	CMD;		//Э������		1�ֽ�
}NWK_Head_Stru;
#pragma pack()			//�ֽڶ���


//NWKͨ��Э�� ���ݳ��� ����
#pragma pack(1)			//�ֽڶ���
typedef struct
{
	NWK_Head_Stru  Head;                    //01 03
	
	INT8U	Register_Addr_H;				//�Ĵ�����ַ���ֽ� 00
	INT8U	Register_Addr_L;				//�Ĵ�����ַ���ֽ� 00
	
	INT8U	Register_Num_H;					//�Ĵ����������ֽ� 00
	INT8U	Register_Num_L;					//�Ĵ����������ֽ� 1C = 28(D)
	
	INT8U	CRC16_H;						//CRC���ֽ� 44
	INT8U	CRC16_L;                        //CRC���ֽ� 03
}NWK_Pack_Stru;						//ʵʱ����


typedef union
{
//	INT8U Data[DDF2Pro_PackSize];
//	struct
//	{
//      DDF2Pro_Head_Stru  Head;
//		INT8U	Available[DDF2Pro_PackSize-DDF2Pro_HeadSize];//��Ч����
//	}DefaultPack;


	NWK_Pack_Stru Pack;
	
}NWK_Pack_Uni;


typedef union
{
    NWK_Pack_Stru Pack;
}NWK_Send_Uni;


#pragma pack()			       //�ֽڶ������




 
 


#ifdef _NWKmodbus_C_

INT8U NWK_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U NWK_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);

#endif
 


NWK_EXT void NWK_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
NWK_EXT INT8U NWK_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);


 
#endif

#endif


