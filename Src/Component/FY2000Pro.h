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
* @brief :���ļ�����FY-2000ϵ�в�Ʒ��������ͨ��Э��
* 
* 
* 
*
* @author :��ΰ
* @date :2017/9/5 16:30
***************************************************************
*/ 
#ifndef _FY2000PRO_H_
#define _FY2000PRO_H_


#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"


 
#ifdef _FY2000PRO_C_
#define FY2000PRO_EXT
#else
#define FY2000PRO_EXT extern
#endif
 

#define FY2000Pro_PackSize			UART_TO_FY2000PackSize_S
#define FY2000Pro_HeadSize			12			//���ݰ�ͷ��С
#define FY2000Pro_StartCode			0X3A			//��ʼ��
#define FY2000Pro_ProtocolCode			0X70			//�汾��
#define FY2000Pro_BroadcastAddr		0XAAAAAAAA	//�㲥��ַ
#define FY2000Pro_EndCode			0XAA			//������


#pragma pack(1)		//�ֽڶ���
typedef struct
{
	INT8U	Start;		//��ʼ�ַ�	1�ֽ�
	INT8U	Version;	//Э��汾��	1�ֽ�
	INT32U	SN;		//��Ʒ���к�	4�ֽ�
	INT16U	DESN;	//�����ֽ�	1�ֽ�
	INT16U	GN;		//��Ʒ���	2�ֽ�
	INT8U	ConType;	//��������	1�ֽ�
	INT8U	Lenth;	//���ݳ���	1�ֽ�
}FY2000Pro_Head_Stru;
#pragma pack()		//�ֽڶ���



/*
	ͨ�Ż�����������ݽṹ ������
	�������հ��ͷ��Ͱ�
*/
#pragma pack(1)		//�ֽڶ���

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year;		//��
	INT8U	Month;	//��
	INT8U	Day;		//��
	INT8U	Hour;		//ʱ
	INT8U	Minute; //��
	INT8U	Second; //��
	INT8U	Week;	//��
	
	INT8U	Check;	//У���
	INT8U	End;	//������־
}FY2000_Pack50_Stru;


typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Delay;	//��ʱʱ��
	INT8U	Check;	//У���
	INT8U	End;	//������־
}FY2000_Pack51_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Delay;	//��ʱʱ��
	INT8U	Check;	//У���
	INT8U	End;		//������־
}FY2000_Pack52_Stru;


typedef struct
{
	FY2000Pro_Head_Stru Head;

	INT8U	 ValveCtrlDemandFlg;	//������������
	INT8U	CtrlFlg;	//���Ʊ�־
	
	INT8U	Check;	//У���
	INT8U	End;	//������־

}FY2000_Pack53_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT8U	 ValveCtrlDemandFlg;	//������������
	INT8U	CtrlFlg;	//���Ʊ�־
	INT8U	Check;	//У���
	INT8U	End;	//������־
}FY2000_Pack54_Stru;



typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year;		//��
	INT8U	Month;	//��
	INT8U	Day;		//��
	INT8U	Hour;		//ʱ
	INT8U	Minute; 	//��
	INT8U	Second; 	//��
	INT8U	Week;	//��
	
	INT8U	Check;	//У���
	INT8U	End;		//������־
}FY2000_Pack55_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	DATA;	//��ʱʱ��
	INT8U	Check;	//У���
	INT8U	End;		//������־
}FY2000_Pack56_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	DATA;	//������
	INT8U	Check;	//У���
	INT8U	End;		//������־
}FY2000_Pack57_Stru;	


typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year;			//2�ֽ�
	INT8U	Month;		//1�ֽ�
	INT8U	Day;			//1�ֽ� 
	INT8U	Hour;			// 1�ֽ�
	INT8U	Minute; 		//1�ֽ� 	
	INT8U	Second; 		//1�ֽ� 
	INT16U	ShareNO;		//2�ֽڷ�̯���
	INT8U	ShareCycle;		//��̯����
	INT8U	Check;		//У���
	INT8U	End;			//������־
}FY2000_Pack58_Stru;




typedef struct
{
	FY2000Pro_Head_Stru Head;
	
	INT16U	DATA;			//������
	INT32U	LoopTime;		//���ڹ�ůʱ��
	INT32U	Apportion_Energy;//���ڷ�̯���� ʹ������
	INT32U	Remain_Heat;	//ʣ������
	INT32U	Total_Heat; 	//�û���������
	
	INT8U	ControlType;	//�ѿ�����
	
	INT8U	ForceCtrlFlg;	//ǿ�ƿ��Ʊ�־
	
	INT8U	Set_TCtrlFg;		//ϵͳ�¶��趨��־
	INT16U	Set_Temp;		//ϵͳ�趨�¶�

	INT8U	LimtTE_Flag;	//�����¶��趨��־
	INT16U	LimtTE_Value;	//�����趨�¶�	
	

	INT16U	Year_S; 		//2�ֽ�
	INT8U	Month_S;		//1�ֽ�
	INT8U	Day_S;		//1�ֽ� 
	INT8U	Hour_S; 		//1�ֽ�
	INT8U	Minute_S;		//1�ֽ� 	
	INT8U	Second_S;		//1�ֽ�

	INT16U	Year_F; 		//2�ֽ�
	INT8U	Month_F;		//1�ֽ�
	INT8U	Day_F;		//1�ֽ� 
	INT8U	Hour_F; 		//1�ֽ�
	INT8U	Minute_F;		//1�ֽ� 	
	INT8U	Second_F;		//1�ֽ� 


	INT8U	Buld;			//¥����
	INT8U	Unit;			//��Ԫ��
	INT8U	Floor;			//¥���
	INT8U	Cell;			//�����
	INT16U	CellArea;		//�������


	INT8U	Check;		//У���
	INT8U	End;			//������־
}FY2000_Pack59_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year;		//��
	INT8U	Month;	//��
	INT8U	Day;		//��
	INT8U	Hour;		//ʱ
	INT8U	Minute; //��
	INT8U	Second; //��
	INT8U	Week;	//��		
	INT8U	Check;	//У���
	INT8U	End;		//������־
}FY2000_Pack60_Stru;


typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year_S; //2�ֽ�
	INT8U	Month_S;	//1�ֽ�
	INT8U	Day_S;	//1�ֽ� 
	INT8U	Hour_S; // 1�ֽ�
	INT8U	Minute_S;	//1�ֽ� 	
	INT8U	Second_S;	//1�ֽ�

	INT16U	Year_F; //2�ֽ�
	INT8U	Month_F;	//1�ֽ�
	INT8U	Day_F;	//1�ֽ� 
	INT8U	Hour_F; //1�ֽ�
	INT8U	Minute_F;	//1�ֽ� 	
	INT8U	Second_F;	//1�ֽ�
	
	INT8U	TimeSetFlag;	//��̯����
	INT8U	Check;		//У���
	INT8U	End;			//������־
}FY2000_Pack61_Stru;		
typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	DATA;	//��������

	INT8U	Check;	//У���
	INT8U	End;		//������־
}FY2000_Pack62_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT8U	Buld;		//¥��
	INT8U	Unit;		//��Ԫ��
	INT8U	Floor;		//¥���
	INT8U	Cell;		//�����
	INT16U	CellArea;	//�������
	
	INT8U	Check;	//У���
	INT8U	End;		//������־
}FY2000_Pack63_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT8U	CtrlFlg;	//���Ʊ�־
	INT8U	Check;	//У���
	INT8U	End;	//������־
}FY2000_Pack128_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	Year;	//��
	INT8U	Month;	//��
	INT8U	Day;	//��
	INT8U	Hour;	//ʱ
	INT8U	Minute; //��
	INT8U	Second; //��
	INT8U	Week;	//��
	INT16U	CtrlFlg;	//���Ʊ�־
	
	INT8U	Check;	//У���
	INT8U	End;	//������־
}FY2000_Pack129_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	CtrlFlg;	//���Ʊ�־
	
	INT8U Buld; //¥��
	INT8U Unit; //��Ԫ��
	INT8U Floor;	//¥���
	INT8U Cell; //�����
	INT16U CellArea;	//�������
	
	INT8U	Check;	//У���
	INT8U	End;	//������־
}FY2000_Pack130_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	CtrlFlg;	//���Ʊ�־
	INT8U	Check;	//У���
	INT8U	End;	//������־
}FY2000_Pack131_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT8U	Month;		//��
	INT8U	Day;			//��
	INT8U	Hour;			//ʱ
	INT8U	Minute; 	//��
	
	INT8U	Buld;			//¥��
	INT8U	Unit;			//��Ԫ
	INT8U	Floor;			//¥��
	INT8U	Cell;			//�����
	INT16U	CellArea;		//�������
	
	INT8U	Set_TCtrlFg;		//ϵͳ�¶��趨��־
	INT16U	Set_Temp;		//�趨�¶�
	
	INT16U	Cur_Temp;		//��ǰ�¶�
	INT16U	Ave_Temp;		//ƽ���¶�
	INT16U	Input_Temp; //��ˮ�¶�
	INT16U	Output_Temp;	//��ˮ�¶�
	
	INT8U	Valve_POS;		//����λ��
	
	INT32U	Cycle_OpTim;	//���ڿ���ʱ��
	INT16U	Cycle_OpRat;	//���ڿ�������
	INT32U	Total_OpTim;	//�ۼƿ���ʱ��
	
	INT8U	Face_State; 	//���״̬
	INT8U	Valve_STate;	//����״̬
	
	INT8U	Check;		//У���
	INT8U	End;			//������־
}FY2000_Pack132_Stru;

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	CtrlFlg;	//���Ʊ�־
	INT8U	Check;	//У���
	INT8U	End;	//������־
}FY2000_Pack133_Stru;	

typedef struct
{
	FY2000Pro_Head_Stru Head;
	INT16U	CtrlFlg;	//�������
	
	INT8U	Check;	//У���
	INT8U	End;		//������־
}FY2000_Pack134_Stru;



typedef union
{
	INT8U Data[FY2000Pro_PackSize];
	struct
	{
		INT8U	Start;		//��ʼ�ַ�		1�ֽ�
		INT8U	Version;	//Э��汾��		1�ֽ�
		INT32U	SN;		    //��Ʒ���к�		4�ֽ�
		INT16U	DESN;	    //�������		2�ֽ�
		INT16U	GN;		    //��Ʒ���		2�ֽ�
		INT8U	ConType;	//��������		1�ֽ�
		INT8U	Lenth;	    //���ݳ���		1�ֽ�
		INT8U	Available[FY2000Pro_PackSize-FY2000Pro_HeadSize];//��Ч����
	}DefaultPack;

	FY2000_Pack50_Stru Pack_50;
	FY2000_Pack51_Stru Pack_51;
	FY2000_Pack52_Stru Pack_52;
	FY2000_Pack53_Stru Pack_53;
	FY2000_Pack54_Stru Pack_54;
	FY2000_Pack55_Stru Pack_55;
	FY2000_Pack56_Stru Pack_56;
	FY2000_Pack57_Stru Pack_57;
	FY2000_Pack58_Stru Pack_58;
	FY2000_Pack59_Stru Pack_59;
	FY2000_Pack60_Stru Pack_60;
	FY2000_Pack61_Stru Pack_61;
	FY2000_Pack62_Stru Pack_62;
	FY2000_Pack63_Stru Pack_63;
	FY2000_Pack128_Stru Pack_128;
	FY2000_Pack129_Stru Pack_129;
	FY2000_Pack130_Stru Pack_130;
	FY2000_Pack131_Stru Pack_131;
	FY2000_Pack132_Stru Pack_132;
	FY2000_Pack133_Stru Pack_133;
	FY2000_Pack134_Stru Pack_134;
	
}FY2000_Pack_Uni;


typedef union
{

	FY2000_Pack50_Stru Pack_50;
	FY2000_Pack51_Stru Pack_51;
	FY2000_Pack52_Stru Pack_52;
	FY2000_Pack53_Stru Pack_53;
	FY2000_Pack54_Stru Pack_54;
	FY2000_Pack55_Stru Pack_55;
	FY2000_Pack56_Stru Pack_56;
	FY2000_Pack57_Stru Pack_57;
	FY2000_Pack58_Stru Pack_58;
	FY2000_Pack59_Stru Pack_59;
	FY2000_Pack60_Stru Pack_60;
	FY2000_Pack61_Stru Pack_61;
	FY2000_Pack62_Stru Pack_62;
	FY2000_Pack63_Stru Pack_63;
}FY2000_Send_Uni;


#pragma pack()		//�ֽڶ���


 
 




 
#ifdef _FY2000PRO_C_

INT8U FY2000_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U FY2000_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);



#endif
 




FY2000PRO_EXT void FY2000_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
FY2000PRO_EXT INT8U FY2000_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);













 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
