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
* @date :2017/9/26 11:42
***************************************************************
*/ 
#ifndef _FY1000PRO_H_
#define _FY1000PRO_H_
 

#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "UART_RBC.h"
#include "COM_Server.h"
#include "updateparm.h"


 
#ifdef _FY1000PRO_C_
#define FY1000PRO_EXT
#else
#define FY1000PRO_EXT extern
#endif
 





typedef enum
{
	COMBack_OK =0X00,				//�豸ִ�гɹ�
	COMBack_FT =0X01,				//�豸ִ��ʧ��
	COMBack_NF =0X02,				//�豸��ѯʧ��
	COMBack_CE =0X03,				//�豸ͨ�Ŵ���
	
}COMBackStaType;					//�豸ͨ�ŷ���ִ�н��˵��


#define FY1000Pro_PackSize			UART_TO_FY1000PackSize_S
#define FY1000Pro_HeadSize			11			//���ݰ�ͷ��С
#define FY1000Pro_StartCode			0X59			//��ʼ��
#define FY1000Pro_ProtocolCode		0X57			//�汾��
#define FY1000Pro_BroadcastAddr		0XAAAAAAAA	//�㲥��ַ
#define FY1000Pro_EndCode			0XAA			//������




//��Դ�ǿ�FY-1000ͨ��Э���
#pragma pack(1)		//�ֽڶ���
typedef struct
{

	INT8U	Start;		//��ʼ�ַ�	1�ֽ�
	INT8U	Version;	//Э������	1�ֽ�
	INT32U	SN;		//��ƷID/SN	4�ֽ�
	INT8U	ConType;	//Э�����	1�ֽ�
	INT32U	Lenth;	//���ݳ���	4�ֽ�
}FY1000Pro_Head_Stru;



//1.	*��0X01����վ�����ն��豸���ݳ�������
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;			//���Ʊ�־
	INT8U	Dev_Type;			//�豸����
	INT32U	Dev_ID;			//�豸ID
	
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X01_Stru;


//2.	*��0X02����վ�����ն��豸���ݳ��������	
//�豸��ѯʧ��
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//���Ʊ�־
	INT8U	Dev_Type;				//�豸����
	INT32U	Dev_ID;				//�豸���
	INT8U	BackFlag;				//������־

	
	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0X02_N_Stru;
//�豸ͨ��ʧ��
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//���Ʊ�־
	INT8U	Dev_Type;				//�豸����
	INT32U	Dev_ID;				//�豸���
	INT8U	BackFlag;				//������־

	INT32U	ComTolNum;			//ͨ���ܴ���
	INT32U	ComSucNum; 	  		//ͨ�ųɹ�����
	INT32U	ComFauNum;	  		//����ͨ��ʧ�ܴ���
	
	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0X02_F_Stru;

//�豸���ճɹ����߷��سɹ�  ¥�����豸
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//���Ʊ�־
	INT8U	Dev_Type;				//�豸����
	INT32U	Dev_ID;				//�豸���
	INT8U	BackFlag;				//������־
	
	INT16U	Input_Temp;			//��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�

	INT32U	Instant_Current;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Current_Unit;		//��λ

	INT32U	Instant_Energy;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Energy_Unit;		//��λ

	INT32U	Total_Current;			//�ۼ�����4 �����ʽ BCD �����ʽ  HEX	X100
	INT8U	Total_Current_Unit;

	INT32U	Total_Code; 			//�ۼ����� �������
	INT8U	Total_Code_Unit;			//��λ �������

	INT32U	Total_Energy;			//�ۼ����� �������
	INT8U	Total_Energy_Unit;		//��λ �������

	INT32U	Work_Time;				//����ʱ��
	INT8U	STATE1; 				//�ȱ����״̬1
	INT8U	STATE2; 				//�ȱ����״̬1
	
	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0X02_D1_Stru;


//�豸���ճɹ����߷��سɹ�  �û����豸
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//���Ʊ�־
	INT8U	Dev_Type;				//�豸����
	INT32U	Dev_ID;				    //�豸���
	INT8U	BackFlag;				//������־

	
	INT16U	Input_Temp;			    //��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�

	INT32U	Instant_Current;        //˲ʱ����(����)
	INT8U	Instant_Current_Unit;   //��λ

	INT32U	Instant_Energy;			//˲ʱ����(����)
	INT8U	Instant_Energy_Unit;		//��λ

	INT32U	Total_Current;			//�ۼ�����
	INT8U	Total_Current_Unit;

	INT32U	Total_Code; 			//�ۼ����� �������
	INT8U	Total_Code_Unit;			//��λ �������

	INT32U	Total_Energy;			//�ۼ����� �������
	INT8U	Total_Energy_Unit;		//��λ �������
	
	INT32U	Work_Time;				//����ʱ��
	INT8U	STATE1; 				//�ȱ����״̬1
	INT8U	STATE2; 				//�ȱ����״̬1
	

	
	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0X02_D2_Stru;

//�豸���ճɹ����߷��سɹ�  ͨ�Ͽ�����1
typedef struct
{
	FY1000Pro_Head_Stru Head;
	INT8U	CtrlFlag;				//���Ʊ�־
	INT8U	Dev_Type;				//�豸����
	INT32U	Dev_ID;				//�豸���
	INT8U	BackFlag;				//������־

	INT16U	Set_Temp;				//�����趨�¶�
	INT16U	Cur_Temp;				//��ǰ�¶�
	INT16U	Ave_Temp;				//ƽ���¶�
	INT16U	Input_Temp;			//��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�
	INT8U	ValvePosition;			//����λ��
	INT32U	Cycle_OpTim;			//���ڿ���ʱ��
	INT16U	Cycle_OpRat;			//���ڿ�������
	INT32U	Apportion_Energy;		//��ǰ(��̯)����	
	INT8U	Face_State; 			//���״̬
	INT8U	Valve_State;			//����״̬
	

	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0X02_D3_Stru;


//�豸���ճɹ����߷��سɹ�  ͨ�Ͽ�����2
typedef struct
{
	FY1000Pro_Head_Stru Head;
	INT8U	CtrlFlag;				//���Ʊ�־
	INT8U	Dev_Type;				//�豸����
	INT32U	Dev_ID;				    //�豸���
	INT8U	BackFlag;				//������־

	
	INT8U	ValvePosition;			//����λ��
	INT32U	Cycle_OpTim;			//���ڿ���ʱ��
	INT16U	Cycle_OpRat;			//���ڿ�������
	INT32U	Apportion_Energy;		//��ǰ(��̯)����	
	INT8U	Valve_State;			//����״̬	


	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0X02_D4_Stru;

//�豸���ճɹ����߷��سɹ�  ������¥�����ڷ�
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				    //���Ʊ�־
	INT8U	Dev_Type;				    //�豸����
	INT32U	Dev_ID;				        //�豸���
	INT8U	BackFlag;				    //������־
	
	float	Input_Temp;                 //��ˮ�¶�
	float	Output_Temp;                //��ˮ�¶�
    float   EnterWater_Pressure;        //��ˮѹ��
    float   ReturnWater_Pressure;       //��ˮѹ��
    float   Room_Temp;                  //����
    float   Current_Valve_Open;         //��ǰ���ſ���ֵ
    float   SetValue_Open;              //���÷��ſ���ֵ
    float   Temp_Diff;                  //�²��趨ֵ
    float   ReturnTemp_Set;             //��ˮ�¶��趨ֵ
    float   PressureDiff_Set;           //��ˮ�¶��趨ֵ
    INT16U  Error;                      //������� 0Ϊ������1Ϊ��ת��2Ϊ��ˮ�¶ȴ�������·��3.��ˮ�¶ȴ�������·��4.��ˮѹ����������·��5��ˮѹ����������·
    INT16U  Software_Version;           //����汾��  100 ��Ϊ V1.0 
    INT16U  Run_Mode;                   //����ģʽ  0Ϊ����ģʽ��1Ϊ�²�ģʽ2Ϊ����ģʽ3Ϊѹ��ģʽ4.�͵ؿ���ģʽ��������磩5.4-20���ƿ���ģʽ����Ӳ��֧�֣�6 TIME
    INT16U  Address;                    //��ַ 1-247��Ĭ��Ϊ1
    INT16U  Motor_Steering;             //���ת�� 0Ϊ���򷧣�1Ϊ����
    INT16U  Adjust_Switch;              //�Զ��г�У�����أ�0�رգ�1Ϊ�򿪣�ֵΪ1ʱÿ���ϵ��Զ�У���г�
    INT16U  Adjust_Tigger;              //д0x5555����һ��
    INT16U  Dc_Motor_Speed;             //ֱ������ٶ�

	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0X02_D5_Stru;


//��վ���Ͳɼ�����������
typedef struct
{
	FY1000Pro_Head_Stru Head;

	
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X03_Stru; 


//�ɼ������ؼ�����������
typedef struct
{
	FY1000Pro_Head_Stru Head;

	INT8U	State;			//�������
	INT8U	Check;		//У���
	INT8U	End;			//������־
}FY1000_Pack0X04_Stru;







//��վ�����û��¶���������
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;			//ȫ�ֿ��Ʊ�־
	
	INT8U	Dev_Type;			//�豸����
	INT32U	Dev_ID;			//�豸ID

	INT8U	Set_TCtrlFg;			//�趨�¶ȿ��Ʊ�־	
	INT16U	Set_Temp;			//�趨�¶�
	
	INT8U	LimtTE_Flag;		//�����¶��趨��־	
	INT16U	LimtTE_Value;		//�����趨�¶�
	
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X05_Stru;



typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;				//�������
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X06_Stru;


typedef struct
{
	FY1000Pro_Head_Stru Head;


	INT8U	Dev_Type;			//�豸����
	INT32U	Dev_ID;			//�豸ID
	INT32U	CycBot_Energy;		//���ڱ�ף����ڼ�¼���ڿ�ʼʱ������ֵ
	INT8U	CycBot_Energy_Unit;	//��λ �������
	
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X07_Stru;




typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;			//�������
	INT8U	Check;		//У���
	INT8U	End;			//������־
}FY1000_Pack0X08_Stru;




//��վ�㲥���Ϳ���/�ط�����
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlDemand;		//�����־
	
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X09_Stru;			//��վ���Ͳɼ����㲥���ط�����

typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;				//�������
	
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X0A_Stru;			//��վ���Ͳɼ����㲥���ط�����




//��վ�㲥���ͷ���ǿ��״̬����
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlDemand;		//�����־
	
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X0B_Stru;			//��վ���Ͳɼ����㲥���ط�����

typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;				//�������
	
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X0C_Stru;			//��վ���Ͳɼ����㲥���ط�����







//��վ�����û����ſ�������
typedef struct
{
	FY1000Pro_Head_Stru Head;
	INT8U	DevType;			//�豸����
	INT32U	DevID;			//�豸���
	
	INT8U	CtrlDemand;		//�����־
	INT8U	ForceFlag;			//ǿ�Ʊ�־
	
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X0D_Stru;			//��վ���Ͳɼ����㲥���ط�����





typedef struct
{

	FY1000Pro_Head_Stru Head;
	
	INT8U	DevType;			//�豸����
	INT32U	DevID;			    //�豸���	
	
	INT8U	State;				//�������

	INT8U	Check;			    //У���
	INT8U	End;				//������־
}FY1000_Pack0X0E_Stru;			//��վ���Ͳɼ����㲥���ط�����






//������������������
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	Num;			//�ۼ�ֵ

	INT8U	Check;		    //У���
	INT8U	End;			//������־
}FY1000_Pack0X11_Stru;	





typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	Num;			//�ۼ�ֵ
	
	INT8U	Check;		    //У���
	INT8U	End;			//������־
}FY1000_Pack0X12_Stru;	



typedef struct
{
	FY1000Pro_Head_Stru Head;
	

	INT16U	Year;			//2�ֽ�
	INT8U	Month;		    //1�ֽ�
	INT8U	Day;			//1�ֽ�	
	INT8U	Hour;			//1�ֽ�
	INT8U	Minute;		    //1�ֽ�		
	INT8U	Second;		    //1�ֽ�
	
	INT8U	Check;		    //У���
	INT8U	End;			//������־
}FY1000_Pack0X13_Stru;	



typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;			//�������
	
	INT8U	Check;		    //У���
	INT8U	End;			//������־
}FY1000_Pack0X14_Stru;	





typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CMD;			//�����־
	
	INT8U	Check;		//У���
	INT8U	End;			//������־
}FY1000_Pack0X15_Stru;	


typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	State;			//�������
	
	INT8U	Check;		//У���
	INT8U	End;			//������־
}FY1000_Pack0X16_Stru;	



//��վ���ͷ��Žɷ�״̬�л�����
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	DevType;			//�豸����
	INT32U	DevID;			//�豸���
	INT8U	CtrlDemand;		//�����־

	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X17_Stru;			


typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	DevType;			//�豸����
	INT32U	DevID;			//�豸���	
	INT8U	State;				//�������
	
	INT8U	Check;			//У���
	INT8U	End;				//������־

}FY1000_Pack0X18_Stru;			



typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	DevType;			//�豸����
	INT32U	DevID;			//�豸���	
	
	INT8U	Check;			//У���
	INT8U	End;				//������־

}FY1000_Pack0X19_Stru;			



typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	DevType;			//�豸����
	INT32U	DevID;			//�豸���
	INT8U	State;				//���Ʊ�־

	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X1A_Stru;	





//�ɼ�������GPRSģ�����վIP��ַ��������
typedef struct
{
	FY1000Pro_Head_Stru Head;
	INT64U	COMFlag;			//�������
	
	INT8U	IP1;				//IP��ַ1��
	INT8U	IP2;				//IP��ַ2��
	INT8U	IP3;				//IP��ַ3��
	INT8U	IP4;				//IP��ַ4��
	INT16U	PortNum;			//�˿ں�
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X40_Stru; 		

typedef struct
{
	FY1000Pro_Head_Stru Head;
	INT64U	COMFlag;			//�������
	
	INT8U	IP1;		//IP��ַ1��
	INT8U	IP2;		//IP��ַ2��
	INT8U	IP3;		//IP��ַ3��
	INT8U	IP4;		//IP��ַ4��
	INT16U	Port;		//�˿ں�
	
	INT8U	Check;	//У���
	INT8U	End;		//������־
}FY1000_Pack0X41_Stru; 		//�ɼ�������IP��ַ���÷�������



//GPRSģ�鷵��ͨ��״̬����

typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT64U	COMFlag;			//�������
	
	INT8U	IPA1;				//IP��ַ1��
	INT8U	IPA2;				//IP��ַ2��
	INT8U	IPA3;				//IP��ַ3��
	INT8U	IPA4;				//IP��ַ4��
	INT16U	Port;				//�˿ں�	
	INT8U	IPX;				//�����
	INT8U	IPB1;				//IP��ַ1��
	INT8U	IPB2;				//IP��ַ2��
	INT8U	IPB3;				//IP��ַ3��
	INT8U	IPB4;				//IP��ַ4��
	INT8U	CCID[20];			//�ֻ�����ʶ

	INT8U 	GPRS_Power_Flg;		//��Դ��־
	INT8U 	GPRS_ONOFF_Flg;	//���ػ���־
	INT8U 	SIMCard_State;		//�ֻ���״̬

	INT8U 	CSQ1; 			//�ź�ǿ��1
	INT8U 	CSQ2; 			//�ź�ǿ��2
	
	INT8U	Check;			//У���
	INT8U	End;				//������־
}FY1000_Pack0X43_Stru;






//�豸ͨ��ʧ��
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;			//���Ʊ�־
	INT8U	Dev_Type;			//�豸����
	INT32U	Dev_ID;				//�豸���
	INT8U	BackFlag;			//������־

	INT32U	ComTolNum;			//ͨ���ܴ���
	INT32U	ComSucNum; 	  		//ͨ�ųɹ�����
	INT32U	ComFauNum;	  		//����ͨ��ʧ�ܴ���
	
	INT8U	Check;				//У���
	INT8U	End;				//������־
}FY1000_Pack0XB0_F_Stru;



//�豸���ճɹ����߷��سɹ�  ¥�����豸
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//���Ʊ�־
	INT8U	Dev_Type;				//�豸����
	INT32U	Dev_ID;				//�豸���
	INT8U	BackFlag;				//������־
	
	INT16U	Input_Temp;			//��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�

	INT32U	Instant_Current;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Current_Unit;		//��λ

	INT32U	Instant_Energy;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Energy_Unit;		//��λ

	INT32U	Total_Current;			//�ۼ�����4 �����ʽ BCD �����ʽ  HEX	X100
	INT8U	Total_Current_Unit;

	INT32U	Total_Code; 			//�ۼ����� �������
	INT8U	Total_Code_Unit;			//��λ �������

	INT32U	Total_Energy;			//�ۼ����� �������
	INT8U	Total_Energy_Unit;		//��λ �������

	INT32U	Work_Time;				//����ʱ��
	INT8U	STATE1; 				//�ȱ����״̬1
	INT8U	STATE2; 				//�ȱ����״̬1

	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0XB0_D1_Stru;


//�豸���ճɹ����߷��سɹ�  �û����豸
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//���Ʊ�־
	INT8U	Dev_Type;				//�豸����
	INT32U	Dev_ID;				//�豸���
	INT8U	BackFlag;				//������־
	
	INT16U	Input_Temp;			//��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�

	INT32U	Instant_Current;			//˲ʱ����(����)
	INT8U	Instant_Current_Unit;		//��λ

	INT32U	Instant_Energy;			//˲ʱ����(����)
	INT8U	Instant_Energy_Unit;		//��λ

	INT32U	Total_Current;			//�ۼ�����
	INT8U	Total_Current_Unit;

	INT32U	Total_Code; 			//�ۼ����� �������
	INT8U	Total_Code_Unit;			//��λ �������

	INT32U	Total_Energy;			//�ۼ����� �������
	INT8U	Total_Energy_Unit;		//��λ �������
	
	INT32U	Work_Time;				//����ʱ��
	INT8U	STATE1; 				//�ȱ����״̬1
	INT8U	STATE2; 				//�ȱ����״̬1

	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0XB0_D2_Stru;

//�豸���ճɹ����߷��سɹ�  ͨ�Ͽ�����1
typedef struct
{
	FY1000Pro_Head_Stru Head;

	
	INT8U	CtrlFlag;				//���Ʊ�־
	INT8U	Dev_Type;				//�豸����
	INT32U	Dev_ID;				//�豸���
	INT8U	BackFlag;				//������־

	INT16U	Set_Temp;				//�����趨�¶�
	INT16U	Cur_Temp;				//��ǰ�¶�
	INT16U	Ave_Temp;				//ƽ���¶�
	INT16U	Input_Temp;			//��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�
	INT8U	ValvePosition;			//����λ��
	INT32U	Cycle_OpTim;			//���ڿ���ʱ��
	INT16U	Cycle_OpRat;			//���ڿ�������
	INT32U	Apportion_Energy;		//��ǰ(��̯)����	
	INT8U	Face_State; 			//���״̬
	INT8U	Valve_State;			//����״̬

	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0XB0_D3_Stru;


//�豸���ճɹ����߷��سɹ�  ͨ�Ͽ�����2
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				//���Ʊ�־
	INT8U	Dev_Type;				//�豸����
	INT32U	Dev_ID;				//�豸���
	INT8U	BackFlag;				//������־

	
	INT8U	ValvePosition;			//����λ��
	INT32U	Cycle_OpTim;			//���ڿ���ʱ��
	INT16U	Cycle_OpRat;			//���ڿ�������
	INT32U	Apportion_Energy;		//��ǰ(��̯)����	
	INT8U	Valve_State;			//����״̬	


	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0XB0_D4_Stru;

//�豸���ճɹ����߷��سɹ�  ͨ�Ͽ�����2
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U	CtrlFlag;				    //���Ʊ�־
	INT8U	Dev_Type;				    //�豸����
	INT32U	Dev_ID;				        //�豸���
	INT8U	BackFlag;				    //������־
	
	float	Input_Temp;                 //��ˮ�¶�
	float	Output_Temp;                //��ˮ�¶�
    float   EnterWater_Pressure;        //��ˮѹ��
    float   ReturnWater_Pressure;       //��ˮѹ��
    float   Room_Temp;                  //����
    float   Current_Valve_Open;         //��ǰ���ſ���ֵ
    float   SetValue_Open;              //���÷��ſ���ֵ
    float   Temp_Diff;                  //�²��趨ֵ
    float   ReturnTemp_Set;             //��ˮ�¶��趨ֵ
    float   PressureDiff_Set;           //��ˮ�¶��趨ֵ
    INT16U  Error;                      //������� 0Ϊ������1Ϊ��ת��2Ϊ��ˮ�¶ȴ�������·��3.��ˮ�¶ȴ�������·��4.��ˮѹ����������·��5��ˮѹ����������·
    INT16U  Software_Version;           //����汾��  100 ��Ϊ V1.0 
    INT16U  Run_Mode;                   //����ģʽ  0Ϊ����ģʽ��1Ϊ�²�ģʽ2Ϊ����ģʽ3Ϊѹ��ģʽ4.�͵ؿ���ģʽ��������磩5.4-20���ƿ���ģʽ����Ӳ��֧�֣�6 TIME
    INT16U  Address;                    //��ַ 1-247��Ĭ��Ϊ1
    INT16U  Motor_Steering;             //���ת�� 0Ϊ���򷧣�1Ϊ����
    INT16U  Adjust_Switch;              //�Զ��г�У�����أ�0�رգ�1Ϊ�򿪣�ֵΪ1ʱÿ���ϵ��Զ�У���г�
    INT16U  Adjust_Tigger;              //д0x5555����һ��
    INT16U  Dc_Motor_Speed;             //ֱ������ٶ�

	INT8U	Check;				//У���
	INT8U	End;					//������־
}FY1000_Pack0XB0_D5_Stru;

//	��0XBA�����������������ļ� / �����������ļ��� / �������ļ����ؽ���
typedef struct
{

	FY1000Pro_Head_Stru Head;
	INT8U	EOH;				//���ݰ�����
	INT8U	NUM;				//���ݰ����
	INT8U	ByteF[512];			//�ļ���
	INT16U   CRC16;			//�ļ���У���־
	INT8U	Check;			//����У���
	INT8U	End;				//������־		
}FY1000_Pack0XBA_Stru;


//	��0XBB���ɼ�������汾�Ų�ѯ
typedef struct
{

	FY1000Pro_Head_Stru Head;

	INT8U	Check;			//����У���
	INT8U	End;				//������־		
}FY1000_Pack0XBB_Stru;


//	��0XBF������������ɼ������������ļ�
typedef struct
{

	FY1000Pro_Head_Stru Head;
	
	INT8U	NUM;				//�������·������
	INT8U  	Ack;				//Ӧ���־
	INT8U	Check;			//����У���
	INT8U	End;				//������־		
}FY1000_Pack0XBF_Stru;

/* ��ѯ����汾�ŷ��� */
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT32U Version;				//�汾�ţ�32λintֵ��
	INT8U Check;				//����У���
	INT8U End;					//������־		
}FY1000_Pack0XBC_Stru;

/* �ļ�����ָ���·� */
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U CMD;					//�ļ��������ͣ�0x01BOOT��0x02Ӧ�ã�0x03������
	INT8U Check;				//����У���
	INT8U End;					//������־		
}FY1000_Pack0XBD_Stru;

/* �ļ�����Ӧ�� */
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U RESULT;				//���������0x01�ɹ���0x02ʧ�ܣ�
	INT8U Check;				//����У���
	INT8U End;					//������־		
}FY1000_Pack0XBE_Stru;


/* �ɼ���ע������� */
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U Check;				//����У���
	INT8U End;					//������־		
}FY1000_Pack0XFE_Stru;


/*������ ע�᷵��*/
typedef struct
{
	FY1000Pro_Head_Stru Head;
	
	INT8U Check;				//����У���
	INT8U End;					//������־		
}FY1000_Pack0XFF_Stru;




typedef union
{
	INT8U Data[FY1000Pro_PackSize];
	struct
	{
		INT8U	Start;		//��ʼ�ַ�	1�ֽ�
		INT8U	Version;	//Э������	1�ֽ�
		INT32U	SN;		//��Ʒ���к�	4�ֽ�
		INT8U	ConType;	//Э�����	1�ֽ�
		INT32U	Lenth;	//���ݳ���	1�ֽ�
		INT8U	Available[FY1000Pro_PackSize-FY1000Pro_HeadSize];//��Ч������
	}DefaultPack;	
	
	FY1000_Pack0X01_Stru		Pack_0X01;
	
	FY1000_Pack0X02_N_Stru	Pack_0X02_N;
	FY1000_Pack0X02_F_Stru	Pack_0X02_F;
	FY1000_Pack0X02_D1_Stru	Pack_0X02_D1;
	FY1000_Pack0X02_D2_Stru	Pack_0X02_D2;
	FY1000_Pack0X02_D3_Stru	Pack_0X02_D3;
	FY1000_Pack0X02_D4_Stru	Pack_0X02_D4;
	
	FY1000_Pack0X03_Stru		Pack_0X03;
	FY1000_Pack0X04_Stru		Pack_0X04;

	FY1000_Pack0X05_Stru		Pack_0X05;
	FY1000_Pack0X06_Stru		Pack_0X06;

	FY1000_Pack0X07_Stru		Pack_0X07;
	FY1000_Pack0X08_Stru		Pack_0X08;

	FY1000_Pack0X40_Stru		Pack_0X40;	
	FY1000_Pack0X41_Stru		Pack_0X41;	

	FY1000_Pack0X43_Stru		Pack_0X43;	

	FY1000_Pack0X09_Stru		Pack_0X09;
	FY1000_Pack0X0A_Stru		Pack_0X0A;

	FY1000_Pack0X0B_Stru		Pack_0X0B;
	FY1000_Pack0X0C_Stru		Pack_0X0C;

	
	FY1000_Pack0X0D_Stru		Pack_0X0D;
	FY1000_Pack0X0E_Stru		Pack_0X0E;

	FY1000_Pack0X11_Stru		Pack_0X11;
	FY1000_Pack0X12_Stru		Pack_0X12;
	
	FY1000_Pack0X13_Stru		Pack_0X13;
	FY1000_Pack0X14_Stru		Pack_0X14;

	FY1000_Pack0X15_Stru		Pack_0X15;
	FY1000_Pack0X16_Stru		Pack_0X16;

	FY1000_Pack0X17_Stru		Pack_0X17;
	FY1000_Pack0X18_Stru		Pack_0X18;

	FY1000_Pack0X19_Stru		Pack_0X19;
	FY1000_Pack0X1A_Stru		Pack_0X1A;

	FY1000_Pack0XB0_F_Stru	Pack_0XB0_F;
	FY1000_Pack0XB0_D1_Stru	Pack_0XB0_D1;
	FY1000_Pack0XB0_D2_Stru	Pack_0XB0_D2;
	FY1000_Pack0XB0_D3_Stru	Pack_0XB0_D3;
	FY1000_Pack0XB0_D4_Stru	Pack_0XB0_D4;
    FY1000_Pack0XB0_D5_Stru	Pack_0XB0_D5;

	FY1000_Pack0XBA_Stru	Pack_0XBA;
	FY1000_Pack0XBF_Stru		Pack_0XBF;
	FY1000_Pack0XBD_Stru	Pack_0XBD;

	FY1000_Pack0XFE_Stru		Pack_0XFE;
	FY1000_Pack0XFF_Stru		Pack_0XFF;

	FY1000_Pack0XBB_Stru		Pack_0XBB;

}FY1000_Pack_Uni;



typedef union
{
	FY1000_Pack0X02_N_Stru		Pack_0X02_N;
	FY1000_Pack0X02_F_Stru		Pack_0X02_F;
	FY1000_Pack0X02_D1_Stru		Pack_0X02_D1;
	FY1000_Pack0X02_D2_Stru		Pack_0X02_D2;
	FY1000_Pack0X02_D3_Stru		Pack_0X02_D3;
	FY1000_Pack0X02_D4_Stru		Pack_0X02_D4;
	FY1000_Pack0X02_D5_Stru		Pack_0X02_D5;
    
	FY1000_Pack0X04_Stru		Pack_0X04;
	
	FY1000_Pack0X06_Stru		Pack_0X06;

	FY1000_Pack0X08_Stru		Pack_0X08;
	
	FY1000_Pack0X0A_Stru		Pack_0X0A;
	
	FY1000_Pack0X0C_Stru		Pack_0X0C;

	FY1000_Pack0X0E_Stru		Pack_0X0E;

	FY1000_Pack0X12_Stru		Pack_0X12;
	FY1000_Pack0X14_Stru		Pack_0X14;	

	FY1000_Pack0X16_Stru		Pack_0X16;	
	FY1000_Pack0X18_Stru		Pack_0X18;	
	FY1000_Pack0X1A_Stru		Pack_0X1A;	
	
	FY1000_Pack0X40_Stru		Pack_0X40;


	FY1000_Pack0XB0_F_Stru		Pack_0XB0_F;
	FY1000_Pack0XB0_D1_Stru		Pack_0XB0_D1;
	FY1000_Pack0XB0_D2_Stru		Pack_0XB0_D2;
	FY1000_Pack0XB0_D3_Stru		Pack_0XB0_D3;
	FY1000_Pack0XB0_D4_Stru		Pack_0XB0_D4;
    FY1000_Pack0XB0_D5_Stru	    Pack_0XB0_D5;

	
	FY1000_Pack0XBF_Stru		Pack_0XBF;
	FY1000_Pack0XBC_Stru 	    Pack_0XBC;
	FY1000_Pack0XBE_Stru		Pack_0XBE;
	FY1000_Pack0XFE_Stru		Pack_0XFE;

}FY1000_Send_Uni;



#pragma pack()		//�ֽڶ���

typedef struct
{
	INT8U PackCreatFlag;				//����Э�鴴����־ ������Ʋ���
	INT8U PackINPort;				//����Э�������� ������Ʋ���
	FY1000_Send_Uni SendData;			//����������
	
}UART_TO_FY1000_QueueSend_Stru;




#define UART_TO_FY1000_Q_NUM		32					//���巢����Ϣ���е�����
FY1000PRO_EXT QueueHandle_t UART_TO_FY1000_Msg;				//Э���������Ϣ���о��
FY1000PRO_EXT UART_TO_FY1000_QueueSend_Stru UART_TO_FY1000_OutArray[UART_TO_FY1000_Q_NUM];
FY1000PRO_EXT UART_TO_FY1000_QueueSend_Stru* UART_TO_FY1000_OutArrayP[UART_TO_FY1000_Q_NUM];

FY1000PRO_EXT INT8U UART_TO_FY1000_OutRecord;	//��ջ������

FY1000PRO_EXT BaseType_t UART_TO_FY1000_CCB_QueueSend(UART_TO_FY1000_QueueSend_Stru *InPut);


#ifdef _FY1000PRO_C_
INT8U FY1000_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT32U DataSize);
INT8U FY1000_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);



UART_TO_FY1000_QueueSend_Stru FY1000_Q_RX_Buffer;		//ͨ�ŷ��Ͷ��� ���ջ�����
UART_TO_FY1000_QueueSend_Stru* FY1000_Q_RX_BufferP;		//ͨ�ŷ��Ͷ��� ���ջ�����



#endif
 






 
FY1000PRO_EXT void          FY1000_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
FY1000PRO_EXT INT8U         FY1000_Pack_TxServer_S( UART_RBC_Stru* Ctrl_Point );
FY1000PRO_EXT BaseType_t    FY_1000Send_Code_QInput( UART_TO_FY1000_QueueSend_Stru*DataBuffer_P, INT8U PackPort );
FY1000PRO_EXT int           fy1000SendMetexInit(void);




#pragma pack(1)		//�ֽڶ���

typedef struct
{
	INT8U State;	//����״̬
	INT8U EOH;	//���ݰ�����
	INT8U NUM;	//�ļ����
	INT8U ErrorNum;
	INT32U TickCount;
	INT32U PackAddr;	//Flashд���ַ

}FileTrans_Stru;
FY1000PRO_EXT	FileTrans_Stru FileTransCrtl;
#pragma pack()		//�ֽڶ���




FY1000PRO_EXT INT16U SerReg_Flg;		//ϵͳע����  �ղ���ϵͳ�ظ�����ʱ ʼ�շ���ע������

#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
