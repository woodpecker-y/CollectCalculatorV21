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
* @brief :�ӱ���Դ������ͨ��Э�� FY188 ������
* 
* 
* 
*
* @author :
* @date :2017/5/24 9:37
***************************************************************
*/ 
#ifndef _FY188PRO_H_
#define _FY188PRO_H_
 


#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"



 
#ifdef _FY188PRO_C_
#define FY188PRO_EXT
#else
#define FY188PRO_EXT extern
#endif
 


#define FY188Pro_PackSize			UART_TO_FY188PackSize_S
#define FY188Pro_HeadSize			11				//���ݰ�ͷ��С
#define FY188Pro_StartCode		0X68				//��ʼ��
#define FY188Pro_ProtocolCode		0X25			//�汾��
#define FY188Pro_ProtocolCode_C	0X20				//�汾��
#define FY188Pro_BroadcastAddr		0XAAAAAAAA		//�㲥��ַ
#define FY188Pro_EndCode			0X16				//������


#pragma pack(1)		//�ֽڶ���
typedef struct
{

	INT8U	Start;			//��ʼ�ַ�		1�ֽ�
	INT8U	Type;			//Э������		1�ֽ�
	INT32U	SN;			//��Ʒ���к�		4�ֽ�
	INT8U	FAdd1;		//�����ֽ�		1�ֽ�
	INT16U	FAdd2;		//�����ֽ�		1�ֽ�
	INT8U	ConType;		//��������		1�ֽ�
	INT8U	Lenth;		//���ݳ���		2�ֽ�
}FY188Pro_Head_Stru;
#pragma pack()			//�ֽڶ���



//FY-188 ������ͨ��Э���
#pragma pack(1)			//�ֽڶ���

typedef struct
{
	INT8U	Lead1;		//�����ַ�1 1�ֽ�
	INT8U	Lead2;		//�����ַ�2 1�ֽ�
	INT8U	Lead3;		//�����ַ�3 1�ֽ�
	INT8U	Lead4;		//�����ַ�4 1�ֽ�
	
	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�־
	INT8U	SER;					//����2
	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY188_Pack01S_Stru;					//�ٲ�ʵʱ����

typedef struct
{

	
	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�־
	INT8U	SER;					//����2
	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY188_Pack01C_Stru;					//�ٲ�ʵʱ����


typedef struct
{
	INT8U	Lead1;				//�����ַ�1 1�ֽ�
	INT8U	Lead2;				//�����ַ�2 1�ֽ�
	INT8U	Lead3;				//�����ַ�3 1�ֽ�
	INT8U	Lead4;				//�����ַ�4 1�ֽ�
	
	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�־
	INT8U	SER;					//У���
	INT8U	Second;				//ʵʱʱ�� ��
	INT8U	Minute;				//ʵʱʱ�� ��
	INT8U	Hour;					//ʵʱʱ�� ʱ
	INT8U	Day;					//ʵʱʱ�� ��
	INT8U	Month;				//ʵʱʱ�� ��
	INT16U	Year;					//ʵʱʱ�� ��		
	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY188_Pack04S_Stru;					//����ʵʱʱ��


typedef struct
{

	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�־
	INT8U	SER;					//У���
	INT8U	Second;				//ʵʱʱ�� ��
	INT8U	Minute;				//ʵʱʱ�� ��
	INT8U	Hour;					//ʵʱʱ�� ʱ
	INT8U	Day;					//ʵʱʱ�� ��
	INT8U	Month;				//ʵʱʱ�� ��
	INT16U	Year;					//ʵʱʱ�� ��		
	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY188_Pack04C_Stru;					//����ʵʱʱ��

typedef struct
{
	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�ʶ
	INT8U	SER;					//���к�
	INT32U	Total_Code; 			//����4�ֽ�
	INT8U	Total_Code_Unit;			//������λ1
	
	INT32U	Total_Energy;			//����4�ֽ�
	INT8U	Total_Energy_Unit;		//����1�ֽ�

	INT32U	Instant_Energy; 			//�ȹ���4�ֽ�
	INT8U	Instant_Energy_Unit;

	INT32U	Instant_Current;			//����4�ֽ�
	INT8U	Instant_Current_Unit;		//����1�ֽ�
	
	INT32U	Total_Current;			//�ۼ�����4�ֽ�
	INT8U	Total_Current_Unit;
	
	INT16U	Input_TempL;
	INT8U	Input_TempH;

	INT16U	Output_TempL;
	INT8U	Output_TempH;
	
	INT16U	Work_Time_L;			//����ʱ��1
	INT8U	Work_Time_H;

	INT8U	Second; 				//ʵʱʱ��
	INT8U	Minute; 				//ʵʱʱ��
	INT8U	Hour;					//ʵʱʱ��
	INT8U	Day;					//ʵʱʱ��
	INT8U	Month;				//ʵʱʱ��
	INT16U	Year;					//ʵʱʱ��

	INT8U	STATE1; 				//״̬
	INT8U	STATE2; 				//״̬
	
	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY188_Pack129S_Stru;//����ʵʱ����


typedef struct
{
	INT8U	Lead1;				//�����ַ�1 1�ֽ�
	INT8U	Lead2;				//�����ַ�2 1�ֽ�
	INT8U	Lead3;				//�����ַ�3 1�ֽ�
	INT8U	Lead4;				//�����ַ�4 1�ֽ�

	FY188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�ʶ
	INT8U	SER;					//���к�
	INT32U	Total_Code; 			//����4�ֽ�
	INT8U	Total_Code_Unit;			//������λ1
	
	INT32U	Total_Energy;			//����4�ֽ�
	INT8U	Total_Energy_Unit;		//����1�ֽ�

	INT32U	Instant_Energy; 			//�ȹ���4�ֽ�
	INT8U	Instant_Energy_Unit;

	INT32U	Instant_Current;			//����4�ֽ�
	INT8U	Instant_Current_Unit;		//����1�ֽ�
	
	INT32U	Total_Current;			//�ۼ�����4�ֽ�
	INT8U	Total_Current_Unit;
	
	INT16U	Input_TempL;
	INT8U	Input_TempH;

	INT16U	Output_TempL;
	INT8U	Output_TempH;
	
	INT16U	Work_Time_L;			//����ʱ��1
	INT8U	Work_Time_H;

	INT8U	Second; 				//ʵʱʱ��
	INT8U	Minute; 				//ʵʱʱ��
	INT8U	Hour;					//ʵʱʱ��
	INT8U	Day;					//ʵʱʱ��
	INT8U	Month;				//ʵʱʱ��
	INT16U	Year;					//ʵʱʱ��

	INT8U	STATE1; 				//״̬
	INT8U	STATE2; 				//״̬
	
	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY188_Pack129C_Stru;//����ʵʱ����





typedef union
{
	INT8U Data[FY188Pro_PackSize];
	struct
	{
		
		INT8U	Start;			//��ʼ�ַ�	1�ֽ�
		INT8U	Type;			//Э������	1�ֽ�
		INT32U	SN;			//��Ʒ���к�	4�ֽ�
		INT8U	FAdd1;		//�����ֽ�	1�ֽ�
		INT16U	FAdd2;		//�����ֽ�	1�ֽ�

		INT8U	ConType;		//��������	1�ֽ�
		
		INT8U	Lenth;		//���ݳ���	1�ֽ�
		INT8U	Available[FY188Pro_PackSize-FY188Pro_HeadSize];//��Ч����
	}DefaultPack;

	struct
	{
		
		INT8U	Start;			//��ʼ�ַ�	1�ֽ�
		INT8U	Type;			//Э������	1�ֽ�
		INT32U	SN;			//��Ʒ���к�	4�ֽ�
		INT8U	FAdd1;		//�����ֽ�	1�ֽ�
		INT16U	FAdd2;		//�����ֽ�	1�ֽ�

		INT8U	ConType;		//��������	1�ֽ�
		INT8U	Lenth;		//���ݳ���	1�ֽ�
		INT16U	Flag;			//���ݱ�־
		INT8U	Available[FY188Pro_PackSize-FY188Pro_HeadSize-2];//��Ч����
	}CheckPack;	


	FY188_Pack01S_Stru Pack0X01S;
	FY188_Pack04S_Stru Pack0X04S;
	FY188_Pack129S_Stru Pack0X129S;
	
	FY188_Pack01C_Stru Pack0X01C;
	FY188_Pack04C_Stru Pack0X04C;
	FY188_Pack129C_Stru Pack0X129C;

	
}FY188_Pack_Uni;


typedef union
{
	FY188_Pack01S_Stru Pack0X01S;
	FY188_Pack04S_Stru Pack0X04S;

}FY188_Send_Uni;



#pragma pack()		//�ֽڶ���


 
#ifdef _FY188PRO_C_
INT8U FY188_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U FY188_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);

INT8U FY188_Pack_0X129_S(UART_RBC_Stru* PORT);
void FY188_Pack_0X01_S(UART_RBC_Stru* PORT);
void FY188_Pack_0X04_S(UART_RBC_Stru* PORT);






#endif


FY188PRO_EXT void FY188_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
FY188PRO_EXT INT8U FY188_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);



















 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
