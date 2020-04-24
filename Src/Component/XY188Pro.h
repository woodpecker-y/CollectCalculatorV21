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
* @brief :�ӱ���Դ������188ͨ��Э�鴦����

* 
* 
* 
*
* @author :
* @date :2017/11/7 15:53
***************************************************************
*/ 
#ifndef _XY188PRO_H_
#define _XY188PRO_H_
 

#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"

#ifdef  Meter_XY_ENABLE	

 
#ifdef _XY188PRO_C_
#define XY188PRO_EXT
#else
#define XY188PRO_EXT extern
#endif
 


#define XY188Pro_PackSize			UART_TO_XY188PackSize_S
#define XY188Pro_HeadSize			11				    //���ݰ�ͷ��С
#define XY188Pro_StartCode		    0X68				//��ʼ��
#define XY188Pro_ProtocolCode		0X20				//�汾��
#define XY188Pro_EndCode			0X16				//������


 
 
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
}XY188Pro_Head_Stru;
#pragma pack()			//�ֽڶ���



//XY-188 ������ͨ��Э���
#pragma pack(1)			//�ֽڶ���

typedef struct
{
	INT8U	Lead1;		//�����ַ�1 1�ֽ�
	INT8U	Lead2;		//�����ַ�2 1�ֽ�
	INT8U	Lead3;		//�����ַ�3 1�ֽ�
	INT8U	Lead4;		//�����ַ�4 1�ֽ�
	
	XY188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�־
	INT8U	SER;					//����2
	INT8U	Check;				//У���
	INT8U	End;					//������־
}XY188_Pack01S_Stru;					//�ٲ�ʵʱ����


typedef struct
{
	XY188Pro_Head_Stru Head;
	INT16U	Flag;					//���ݱ�ʶ
	INT8U	SER;					//���к�
	
	INT32U	Day_Energy; 			//��ǰ������4�ֽ�		//2λС��
	INT8U	Day_Energy_Unit;			//��ǰ��������λ1�ֽ�
	
	INT32U	Total_Energy;			//��ǰ����4�ֽ�		//2λС��
	INT8U	Total_Energy_Unit;		//��ǰ����1�ֽ�

	INT32U	Instant_Energy; 			//�ȹ���4�ֽ�			//2λС��
	INT8U	Instant_Energy_Unit;		//�ȹ��ʵ�λ1�ֽ�

	INT32U	Instant_Current;			//����4�ֽ�			//4λС��
	INT8U	Instant_Current_Unit;		//���ٵ�λ1�ֽ�
	
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
	INT8U	Month;				//ʵʱʱ��
	INT16U	Year;					//ʵʱʱ��

	INT8U	STATE1; 				//״̬
	INT8U	STATE2; 				//״̬
	
	INT8U	Check;				//У���
	INT8U	End;					//������־
}XY188_Pack129S_Stru;//����ʵʱ����





typedef union
{
	INT8U Data[XY188Pro_PackSize];
	struct
	{
		
		INT8U	Start;			//��ʼ�ַ�	1�ֽ�
		INT8U	Type;			//Э������	1�ֽ�
		INT32U	SN;			//��Ʒ���к�	4�ֽ�
		INT8U	FAdd1;		//�����ֽ�	1�ֽ�
		INT16U	FAdd2;		//�����ֽ�	1�ֽ�

		INT8U	ConType;		//��������	1�ֽ�
		
		INT8U	Lenth;		//���ݳ���	1�ֽ�
		INT8U	Available[XY188Pro_PackSize-XY188Pro_HeadSize];//��Ч����
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
		INT8U	Available[XY188Pro_PackSize-XY188Pro_HeadSize-2];//��Ч����
	}CheckPack;	


	XY188_Pack01S_Stru Pack0X01S;
	XY188_Pack129S_Stru Pack0X129S;
}XY188_Pack_Uni;



typedef union
{
	XY188_Pack01S_Stru Pack0X01S;

}XY188_Send_Uni;

#pragma pack()		//�ֽڶ���



#ifdef _XY188PRO_C_


INT8U XY188_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U XY188_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);

INT8U XY188_Pack_0X129_S(UART_RBC_Stru* PORT);
void XY188_Pack_0X01_S(UART_RBC_Stru* PORT);

#endif
 




 
 

XY188PRO_EXT void XY188_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
XY188PRO_EXT INT8U XY188_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);

#endif

 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
