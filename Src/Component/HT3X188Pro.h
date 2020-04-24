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
* @author :
* @Creat date :2019/1/19 21:23
*************************************************************************************************
*/ 
#ifndef _HT3X188PRO_H_
#define _HT3X188PRO_H_
 
 
 /* Standard Include Files. */
 
#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h" 
 
#ifdef  Meter_HT2X_ENABLE
 
#ifdef _HT3X188PRO_C_
#define HT3X188PRO_EXT
#else
#define HT3X188PRO_EXT extern
#endif
 
 /* User Include Files */
#define HT2X188Pro_PackSize			UART_TO_HT2X188PackSize_S
#define HT2X188Pro_HeadSize			11				    //���ݰ�ͷ��С
#define HT2X188Pro_StartCode		0X68				//��ʼ��
#define HT2X188Pro_ProtocolCode		0X20				//�汾��
#define HT2X188Pro_EndCode			0X16				//������
 

 
#pragma pack(1)		//�ֽڶ���
typedef struct
{

	INT8U	Start;		//��ʼ�ַ�		1�ֽ�
	INT8U	Type;		//Э������		1�ֽ�
	INT32U	SN;			//��Ʒ���		4�ֽ�
	INT8U	FAdd1;		//�����ֽ�		1�ֽ�
	INT16U	FAdd2;		//�����ֽ�		1�ֽ�
	INT8U	ConType;	//��������		1�ֽ�
	INT8U	Lenth;		//���ݳ���		2�ֽ�
}HT2X188Pro_Head_Stru;
#pragma pack()			//�ֽڶ���



//HT2X-188 ������ͨ��Э���
#pragma pack(1)			//�ֽڶ���

typedef struct
{
	INT8U	Lead1;		//�����ַ�1 1�ֽ�
	INT8U	Lead2;		//�����ַ�2 1�ֽ�
	INT8U	Lead3;		//�����ַ�3 1�ֽ�
	INT8U	Lead4;		//�����ַ�4 1�ֽ�
	
	HT2X188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�־
	INT8U	SER;					//����2
	INT8U	Check;				//У���
	INT8U	End;					//������־
}HT2X188_Pack01S_Stru;					//�ٲ�ʵʱ����


typedef struct
{
	HT2X188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�ʶ
	INT8U	SER;					//���к�
	
	INT32U	CODE_Energy; 			//��ǰ����4�ֽ�		//2λС��
	INT8U	CODE_Energy_Unit;		//��ǰ������λ1�ֽ�
	
	INT32U	Total_Energy;			//��ǰ����4�ֽ�		//2λС��
	INT8U	Total_Energy_Unit;		//��ǰ������λ1�ֽ�

	INT32U	Instant_Energy; 		//�ȹ���4�ֽ�			//2λС��
	INT8U	Instant_Energy_Unit;	//�ȹ��ʵ�λ1�ֽ�

	INT32U	Instant_Current;        //����4�ֽ�			//4λС��
	INT8U	Instant_Current_Unit;   //���ٵ�λ1�ֽ�
	
	INT32U	Total_Current;			//�ۼ�����4�ֽ�		//2λС��
	INT8U	Total_Current_Unit;		//�ۼ�������λ1�ֽ�
	
	INT16U	Input_TempL;			//����¶� 3�ֽ�		//2λС��
	INT8U	Input_TempH;

	INT16U	Output_TempL;			//�����¶� 3�ֽ�		//2λС��
	INT8U	Output_TempH;
	
	INT16U	Work_Time_L;			//����ʱ�� 3�ֽ�		//û��С��λ
	INT8U	Work_Time_H;

	INT8U	Second; 				//ʵʱʱ��
	INT8U	Minute; 				//ʵʱʱ��
	INT8U	Hour;					//ʵʱʱ��
	INT8U	Day;					//ʵʱʱ��
	INT8U	Month;				    //ʵʱʱ��
	INT16U	Year;					//ʵʱʱ��

	INT8U	STATE1; 				//״̬
	INT8U	STATE2; 				//״̬
	
	INT8U	Check;				//У���
	INT8U	End;					//������־
}HT2X188_Pack129S_Stru;//����ʵʱ����





typedef union
{
	INT8U Data[HT2X188Pro_PackSize];
	struct
	{
		
		INT8U	Start;			//��ʼ�ַ�	1�ֽ�
		INT8U	Type;			//Э������	1�ֽ�
		INT32U	SN;			//��Ʒ���к�	4�ֽ�
		INT8U	FAdd1;		//�����ֽ�	1�ֽ�
		INT16U	FAdd2;		//�����ֽ�	1�ֽ�

		INT8U	ConType;		//��������	1�ֽ�
		
		INT8U	Lenth;		//���ݳ���	1�ֽ�
		INT8U	Available[HT2X188Pro_PackSize-HT2X188Pro_HeadSize];//��Ч����
	}DefaultPack;


	struct
	{
		
		INT8U	Start;		//��ʼ�ַ�	1�ֽ�
		INT8U	Type;		//Э������	1�ֽ�
		INT32U	SN;			//��Ʒ���к�	4�ֽ�
		INT8U	FAdd1;		//�����ֽ�	1�ֽ�
		INT16U	FAdd2;		//�����ֽ�	1�ֽ�

		INT8U	ConType;	//��������	1�ֽ�
		INT8U	Lenth;		//���ݳ���	1�ֽ�
		INT16U	Flag;		//���ݱ�־
		INT8U	Available[HT2X188Pro_PackSize-HT2X188Pro_HeadSize-2];//��Ч����
	}CheckPack;	


	HT2X188_Pack01S_Stru Pack0X01S;
	HT2X188_Pack129S_Stru Pack0X129S;
}HT2X188_Pack_Uni;



typedef union
{
	HT2X188_Pack01S_Stru Pack0X01S;

}HT2X188_Send_Uni;

#pragma pack()		//�ֽڶ���


 
 /*Local variable and declaration*/
#ifdef _HT3X188PRO_C_
 
INT8U HT2X188_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U HT2X188_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);

INT8U HT2X188_Pack_0X129_S(UART_RBC_Stru* PORT);
void HT2X188_Pack_0X01_S(UART_RBC_Stru* PORT); 
 
#endif
 
 
 /*Global interface and declaration*/ 
 
 
 
HT2X188PRO_EXT void HT2X188_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
HT2X188PRO_EXT INT8U HT2X188_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);



#endif
 
  
 
 
#endif
/* End of file */
/*
 @copy COPYRIGHT 2018 VanAn
 @TEMPLATE [20181215]    
*/




