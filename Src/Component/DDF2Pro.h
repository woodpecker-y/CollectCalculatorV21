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
* @date :2018/8/19 11:10
***************************************************************
*/ 
#ifndef _DDF2PRO_H_
#define _DDF2PRO_H_


#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"

#ifdef Meter_DDF2_ENABLE

 
#ifdef _DDF2PRO_C_
#define DDF2PRO_EXT
#else
#define DDF2PRO_EXT extern
#endif
 

#define DDF2Pro_PackSize			UART_TO_DDF2PackSize_S
#define DDF2Pro_HeadSize			11				    //���ݰ�ͷ��С
#define DDF2Pro_StartCode		    0X68				//��ʼ��
#define DDF2Pro_ProtocolCode		0X41				//�汾��
#define DDF2Pro_EndCode			    0X16				//������



#pragma pack(1)		//�ֽڶ���
typedef struct
{

	INT8U	Start;		//��ʼ�ַ�		1�ֽ�
	INT8U	Type;		//Э������		1�ֽ�
	INT32U	SN;			//��Ʒ���		4�ֽ�
	INT16U	SNRE;		//Ԥ�����		2�ֽ�
	INT8U	FAdd2;		//�����ֽ�		1�ֽ�
	INT8U	ConType;	//��������		1�ֽ�
	INT8U	Lenth;		//���ݳ���		1�ֽ�
}DDF2Pro_Head_Stru;
#pragma pack()			//�ֽڶ���


//DDF2ͨ��Э��
#pragma pack(1)			//�ֽڶ���

//���ݳ��� ����
typedef struct
{
	INT8U	Lead1;		//�����ַ�1 1�ֽ�
	INT8U	Lead2;		//�����ַ�2 1�ֽ�
	INT8U	Lead3;		//�����ַ�3 1�ֽ�
	INT8U	Lead4;		//�����ַ�4 1�ֽ�
	
	DDF2Pro_Head_Stru  Head;
	
	INT16U	Flag;					//���ݱ�ʶ 0x902d 
	INT8U	SER;					//���ݱ�ʶ 2

	
	INT8U	Check;				    //У���
	INT8U	End;					//������־
}DDF2Pro_Pack01_Stru;				//ʵʱ����




typedef struct
{
	DDF2Pro_Head_Stru   Head;       //֡ͷ
	
	INT16U	Flag;					//���ݱ�ʶ
	INT8U	SER;					//���ݱ�ʶ 2

	
    INT8U   Reserve0[27];           //�����ֽ� �޷�ʶ��
    INT8U   IN;                     //�����־ ���ڱ�Ƿ��ŵ�λ����Ϣ  0X01 �ط� 0x00 ����״̬          0x03������
    INT8U   Reserve1[5];            //�����ֽ� �޷�ʶ��

	
	INT8U	Check;				    //У���
	INT8U	End;					//������־
}DDF2Pro_Pack02_Stru;               //����ʵʱ����


//���Ŷ�����������
typedef struct
{

	INT8U	Lead1;		//�����ַ�1 1�ֽ�
	INT8U	Lead2;		//�����ַ�2 1�ֽ�
	INT8U	Lead3;		//�����ַ�3 1�ֽ�
	INT8U	Lead4;		//�����ַ�4 1�ֽ�

	DDF2Pro_Head_Stru   Head;       //֡ͷ
	
	INT16U	Flag;					//���ݱ�ʶ         0xa017
	INT8U	SER;					//���ݱ�ʶ2        0x01

	
    INT8U   OUT;                    //�����־ ���ڱ�Ƿ��ŵĿ���״̬    0x55 ����          0XBB �ط�


	INT8U	Check;				    //У���
	INT8U	End;					//������־
}DDF2Pro_Pack03_Stru;               //���п�������


//���Ŷ������Ʒ�������
typedef struct
{
	DDF2Pro_Head_Stru   Head;       //֡ͷ
	
	INT16U	Flag;					//���ݱ�ʶ         0xa017
	INT8U	SER;					//���ݱ�ʶ2        0x01

	
    INT8U   IN0;                     //�����־0        0x00
    INT8U   IN1;                     //�����־1        0X01

	INT8U	Check;				    //У���
	INT8U	End;					//������־
}DDF2Pro_Pack04_Stru;               //����ִ�з��ؽ��






typedef union
{
	INT8U Data[DDF2Pro_PackSize];
	struct
	{
        DDF2Pro_Head_Stru  Head;
		INT8U	Available[DDF2Pro_PackSize-DDF2Pro_HeadSize];//��Ч����
	}DefaultPack;


	DDF2Pro_Pack01_Stru Pack_01;
	DDF2Pro_Pack02_Stru Pack_02;
	DDF2Pro_Pack03_Stru Pack_03;
	DDF2Pro_Pack04_Stru Pack_04;

	
}DDF2_Pack_Uni;


typedef union
{

    DDF2Pro_Pack01_Stru Pack_01;
    DDF2Pro_Pack03_Stru Pack_03;

}DDF2_Send_Uni;


#pragma pack()			       //�ֽڶ������




 
 


#ifdef _DDF2PRO_C_

INT8U DDF2_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U DDF2_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);



#endif
 




 
 

DDF2PRO_EXT void DDF2_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
DDF2PRO_EXT INT8U DDF2_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);

#endif

 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
