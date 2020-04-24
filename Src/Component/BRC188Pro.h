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
* @date :2018/8/12 8:31
***************************************************************
*/ 
#ifndef _BRC188PRO_H_
#define _BRC188PRO_H_
 


#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"



 
#ifdef _BRC188PRO_C_
#define BRC188PRO_EXT
#else
#define BRC188PRO_EXT extern
#endif

#ifdef  Meter_BRC_ENABLE	

#define BRC188Pro_PackSize			UART_TO_BRC188PackSize_S
#define BRC188Pro_HeadSize			11				    //���ݰ�ͷ��С
#define BRC188Pro_StartCode		    0X68				//��ʼ��
#define BRC188Pro_ProtocolCode		0X25				//�汾��
#define BRC188Pro_EndCode			0X16				//������



 

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
}BRC188Pro_Head_Stru;
#pragma pack()			//�ֽڶ���



//XY-188 ������ͨ��Э���
#pragma pack(1)			//�ֽڶ���

typedef struct
{
	INT8U	Lead1;		//�����ַ�1 1�ֽ�
	INT8U	Lead2;		//�����ַ�2 1�ֽ�
	INT8U	Lead3;		//�����ַ�3 1�ֽ�
	INT8U	Lead4;		//�����ַ�4 1�ֽ�
	
	BRC188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�־
	INT8U	SER;					//����2
	INT8U	Check;				//У���
	INT8U	End;					//������־
}BRC188_Pack01S_Stru;					//�ٲ�ʵʱ����


typedef struct
{
	BRC188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�ʶ
	INT8U	SER;					//���к�
	
	INT32U	Total_Code; 			//����4�ֽ�
	INT8U	Total_Code_Unit;		//������λ1
	
	INT32U	Total_Energy;			//��ǰ����4�ֽ�		//2λС��
	INT8U	Total_Energy_Unit;		//��ǰ����1�ֽ�

	INT32U	Instant_Energy; 		//�ȹ���4�ֽ�			//2λС��
	INT8U	Instant_Energy_Unit;	//�ȹ��ʵ�λ1�ֽ�

	INT32U	Instant_Current;		//����4�ֽ�			//4λС��
	INT8U	Instant_Current_Unit;	//���ٵ�λ1�ֽ�
	
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
	
	INT8U	Check;				    //У���
	INT8U	End;					//������־
}BRC188_Pack129S_Stru;//����ʵʱ����





typedef union
{
	INT8U Data[BRC188Pro_PackSize];
	struct
	{
		
		INT8U	Start;			//��ʼ�ַ�	1�ֽ�
		INT8U	Type;			//Э������	1�ֽ�
		INT32U	SN;			//��Ʒ���к�	4�ֽ�
		INT8U	FAdd1;		//�����ֽ�	1�ֽ�
		INT16U	FAdd2;		//�����ֽ�	1�ֽ�

		INT8U	ConType;		//��������	1�ֽ�
		
		INT8U	Lenth;		//���ݳ���	1�ֽ�
		INT8U	Available[BRC188Pro_PackSize-BRC188Pro_HeadSize];//��Ч����
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
		INT8U	Available[BRC188Pro_PackSize-BRC188Pro_HeadSize-2];//��Ч����
	}CheckPack;	


	BRC188_Pack01S_Stru Pack0X01S;
	BRC188_Pack129S_Stru Pack0X129S;
}BRC188_Pack_Uni;



typedef union
{
	BRC188_Pack01S_Stru Pack0X01S;

}BRC188_Send_Uni;

#pragma pack()		//�ֽڶ���
 




 
#ifdef _BRC188PRO_C_


INT8U BRC188_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U BRC188_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);

INT8U BRC188_Pack_0X129_S(UART_RBC_Stru* PORT);
void BRC188_Pack_0X01_S(UART_RBC_Stru* PORT);


#endif
 
BRC188PRO_EXT void BRC188_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
BRC188PRO_EXT INT8U BRC188_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);


#endif

 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
