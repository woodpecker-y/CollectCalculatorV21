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
* @brief :���ļ����ڹ���ɼ�����Ͻͨ���豸�Ĳ���/״̬����

* 
* 
* 
*
* @author :��ΰ
* @date :2017/8/29 14:52
***************************************************************
*/ 
#ifndef _DEVPARA_H_
#define _DEVPARA_H_
 

#include "TypeDef.h"
#include "PubDef.h"

#include "W25QXX.H"
#include "FRAM.H"


 
#ifdef _DEVPARA_C_
#define DEVPARA_EXT
#else
#define DEVPARA_EXT extern
#endif


/* ϵͳͨ���ն��豸���� �ṹ

���ڹ���ɼ�����������ͨ���ն��豸
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
    INT16U		Num;				//�����±꣬���ڿ��ټ���
	SysDEV_Type	Type;				//�豸����
	INT32U		ID;                 //�豸ID
	INT16U		UserNum;			//�û��б��±� �����ڿ��ټ���
	INT32U		UserKEY;			//�û����������ڱ�־�ɼ�������Χ�ڵ�Ψһʶ�����
	INT8U		COM_Type;			//ͨ������ �ò�������Ϊͨ�Žӿ�
	
}SysDevPara;


typedef struct
{
	SysDevPara		Device[MAXDevice_Num];
	INT16U          CRC16;		//У��ֵ
	
}SysDeviceList_Stru;
DEVPARA_EXT SysDeviceList_Stru SysDeviceList;	//ϵͳ�豸�б�


#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�


/*�豸����1���ݽṹ
�����ݱ䶯�ϴ�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	INT16U	Input_Temp;			    //��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�
	
	INT32U	Instant_Current;		//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Current_Unit;	//��λ
	
	INT32U	Instant_Energy;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Energy_Unit;		//��λ
	
	INT32U	Total_Current;			//�ۼ�����4 �����ʽ BCD �����ʽ  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//�ۼ����� �������
	INT8U	Total_Code_Unit;		//��λ �������
	
	INT32U	Total_Energy;			//�ۼ����� �������
	INT8U	Total_Energy_Unit;		//��λ �������

	INT32U	CycBot_Energy;			//���ڱ�ף����ڼ�¼���ڿ�ʼʱ������ֵ

	INT32U	Apportion_Energy;		//�����ڷ�̯����   ��ǰ���-���ڱ��
	
	INT32U	Work_Time;				//����ʱ��
	INT8U	STATE1;				    //�ȱ����״̬1
	INT8U	STATE2;				    //�ȱ����״̬1
	
	INT16U	CRC16;				    //У����
}Dev1Data_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�




/*
	�豸����1״̬���ݽṹ
*/
typedef struct
{

	INT32U		ComTolNum;		//�ȱ�ͨ���ܴ���
	INT32U		ComSucNum; 	  	//�ȱ�ͨ�ųɹ�����
	INT32U		ComFauNum;	  	//����ͨ��ʧ�ܴ���

}Dev1State_Stru;








/*�豸����2���ݽṹ
�����ݱ䶯�ϴ�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	INT16U	Input_Temp;			    //��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�
	
	INT32U	Instant_Current;        //˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Current_Unit;   //��λ
	
	INT32U	Instant_Energy;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Energy_Unit;    //��λ
	
	INT32U	Total_Current;			//�ۼ�����4 �����ʽ BCD �����ʽ  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//�ۼ����� �������
	INT8U	Total_Code_Unit;        //��λ �������
	
	INT32U	Total_Energy;			//�ۼ����� �������
	INT8U	Total_Energy_Unit;		//��λ �������
	
	INT32U	Work_Time;				//����ʱ��
	INT8U	STATE1;				    //�ȱ����״̬1
	INT8U	STATE2;				    //�ȱ����״̬2
	INT16U	CRC16;				    //У����
}Dev2Data_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

/*
	�豸����2״̬���ݽṹ
*/
typedef struct
{

	INT32U		ComTolNum;		//ͨ���ܴ���
	INT32U		ComSucNum; 	  	//ͨ�ųɹ�����
	INT32U		ComFauNum;	  	//ͨ������ʧ�ܴ���

}Dev2State_Stru;






/*�豸����3���ݽṹ
�����ݱ䶯�ϴ�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

typedef struct
{

	INT8U	Set_TCtrlFg;		//ϵͳ�趨�¶�ǿ�Ʊ�־
	INT16U	Set_Temp;		//�趨�¶�

	INT8U	LimtTE_Flag;	//ϵͳ�����¶�ǿ�Ʊ�־
	INT16U	LimtTE_Value;	//�����趨�¶�

	INT8U	ControlType;	//��������
	
	INT8U	ForceCtrlFlg;	//ǿ�ƿ��Ʊ�־	
						//Force_NOR 	     =(INT8U)0X00,	//��ǿ��״̬		
						//Force_Close		=(INT8U)0XAA,	//ǿ�ƹط�
						//Force_Open		=(INT8U)0X55,	//ǿ�ƿ���

	INT16U	Cur_Temp;			//��ǰ�¶�
	INT16U	Ave_Temp;			//ƽ���¶�
	INT16U	Input_Temp;		//��ˮ�¶�
	INT16U	Output_Temp;		//��ˮ�¶�
	INT8U	ValvePosition;		//����λ��
	INT32U	Cycle_OpTim;		//���ڿ���ʱ��
	INT16U	Cycle_OpRat;		//���ڿ�������
	INT32U	Apportion_Energy; 	//��ǰ(��̯)����	
	INT8U	Face_State; 		//���״̬
	INT8U	Valve_State;		//����״̬

	INT16U	CRC16;		//У����
}Dev3Data_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�


/*
	�豸����3״̬���ݽṹ
*/
typedef struct
{

	INT32U		ComTolNum;		//ͨ���ܴ���
	INT32U		ComSucNum; 	  	//ͨ�ųɹ�����
	INT32U		ComFauNum;	  	//����ͨ��ʧ�ܴ���

}Dev3State_Stru;










/*�豸����4���ݽṹ
�����ݱ䶯�ϴ�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

typedef struct
{

	INT8U	ControlType;	//��������
	
	INT8U	ForceCtrlFlg;	//ǿ�ƿ��Ʊ�־	
						//Force_NOR 	     =(INT8U)0X00,	//��ǿ��״̬		
						//Force_Close		=(INT8U)0XAA,	//ǿ�ƹط�
						//Force_Open		=(INT8U)0X55,	//ǿ�ƿ���

	INT8U	ValvePosition;			//����λ��
	INT32U	Cycle_OpTim;			//���ڿ���ʱ��
	INT16U	Cycle_OpRat;			//���ڿ�������
	INT32U	Apportion_Energy;		//��ǰ(��̯)����	
	INT8U	Valve_State;			//����״̬	

	INT16U	CRC16;				//У����
}Dev4Data_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�


/*
	�豸����4״̬���ݽṹ
*/
typedef struct
{

	INT32U		ComTolNum;		//ͨ���ܴ���
	INT32U		ComSucNum; 	  	//ͨ�ųɹ�����
	INT32U		ComFauNum;	  	//����ͨ��ʧ�ܴ���

}Dev4State_Stru;




/*�豸����5���ݽṹ
�����ݱ䶯�ϴ�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	INT16U	Input_Temp;			//��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�
	
	INT32U	Instant_Current;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Current_Unit;		//��λ
	
	INT32U	Instant_Energy;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Energy_Unit;		//��λ
	
	INT32U	Total_Current;			//�ۼ�����4 �����ʽ BCD �����ʽ  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//�ۼ����� �������
	INT8U	Total_Code_Unit;			//��λ �������
	
	INT32U	Total_Energy;			//�ۼ����� �������
	INT8U	Total_Energy_Unit;		//��λ �������

	INT32U	CycBot_Energy;			//���ڱ�ף����ڼ�¼���ڿ�ʼʱ������ֵ

	INT32U	Apportion_Energy;		//�����ڷ�̯����   ��ǰ���-���ڱ��
	
	INT32U	Work_Time;				//����ʱ��
	INT8U	STATE1;				//�ȱ����״̬1
	INT8U	STATE2;				//�ȱ����״̬1
	
	INT16U	CRC16;				//У����
}Dev5Data_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

/*
	�豸����5״̬���ݽṹ
*/
typedef struct
{

	INT32U		ComTolNum;		//�ȱ�ͨ���ܴ���
	INT32U		ComSucNum; 	  	//�ȱ�ͨ�ųɹ�����
	INT32U		ComFauNum;	  	//����ͨ��ʧ�ܴ���

}Dev5State_Stru;




/*�豸����6���ݽṹ
�����ݱ䶯�ϴ�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	INT16U	Input_Temp;			    //��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�
	
	INT32U	Instant_Current;        //˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Current_Unit;   //��λ
	
	INT32U	Instant_Energy;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Energy_Unit;    //��λ
	
	INT32U	Total_Current;			//�ۼ�����4 �����ʽ BCD �����ʽ  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Day_Energy; 			//��ǰ������4�ֽ�
	INT8U	Day_Energy_Unit;        //��ǰ��������λ1�ֽ�

	INT32U	Total_Energy;			//�ۼ����� �������
	INT8U	Total_Energy_Unit;		//��λ �������-

	INT32U	CycBot_Energy;			//���ڱ�ף����ڼ�¼���ڿ�ʼʱ������ֵ

	INT32U	Apportion_Energy;		//�����ڷ�̯����   ��ǰ���-���ڱ��
	
	INT32U	Work_Time;				//����ʱ��
	INT8U	STATE1;				    //�ȱ����״̬1
	INT8U	STATE2;				    //�ȱ����״̬1
	
	INT16U	CRC16;				    //У����
}Dev6Data_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

/*
	�豸����5״̬���ݽṹ
*/
typedef struct
{

	INT32U		ComTolNum;		//�ȱ�ͨ���ܴ���
	INT32U		ComSucNum; 	  	//�ȱ�ͨ�ųɹ�����
	INT32U		ComFauNum;	  	//����ͨ��ʧ�ܴ���

}Dev6State_Stru;




/*�豸����7���ݽṹ   ��ͨ������������
�����ݱ䶯�ϴ�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	INT16U	Input_Temp;			    //��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�
	
	INT32U	Instant_Current;        //˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Current_Unit;   //��λ
	
	INT32U	Instant_Energy;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Energy_Unit;    //��λ
	
	INT32U	Total_Current;			//�ۼ�����4 �����ʽ BCD �����ʽ  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//�ۼ����� �������
	INT8U	Total_Code_Unit;        //��λ �������

	INT32U	Total_Energy;			//�ۼ����� �������
	INT8U	Total_Energy_Unit;		//��λ �������

	INT32U	CycBot_Energy;			//���ڱ�ף����ڼ�¼���ڿ�ʼʱ������ֵ

	INT32U	Apportion_Energy;		//�����ڷ�̯����   ��ǰ���-���ڱ��
	
	INT32U	Work_Time;				//����ʱ��
	INT8U	STATE1;				    //�ȱ����״̬1
	INT8U	STATE2;				    //�ȱ����״̬1
	
	INT16U	CRC16;				    //У����
}Dev7Data_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

/*
	�豸����7״̬���ݽṹ
*/
typedef struct
{

	INT32U		ComTolNum;		//�ȱ�ͨ���ܴ���
	INT32U		ComSucNum; 	  	//�ȱ�ͨ�ųɹ�����
	INT32U		ComFauNum;	  	//����ͨ��ʧ�ܴ���

}Dev7State_Stru;






/*�豸����8���ݽṹ    ��������
�����ݱ䶯�ϴ�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	INT16U	Input_Temp;			    //��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�
	
	INT32U	Instant_Current;        //˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Current_Unit;   //��λ
	
	INT32U	Instant_Energy;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Energy_Unit;    //��λ
	
	INT32U	Total_Current;			//�ۼ�����4 �����ʽ BCD �����ʽ  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//�ۼ����� �������
	INT8U	Total_Code_Unit;        //��λ �������

	INT32U	Total_Energy;			//�ۼ����� �������
	INT8U	Total_Energy_Unit;		//��λ �������

	INT32U	CycBot_Energy;			//���ڱ�ף����ڼ�¼���ڿ�ʼʱ������ֵ

	INT32U	Apportion_Energy;		//�����ڷ�̯����   ��ǰ���-���ڱ��
	
	INT32U	Work_Time;				//����ʱ��
	INT8U	STATE1;				    //�ȱ����״̬1
	INT8U	STATE2;				    //�ȱ����״̬1
	
	INT16U	CRC16;				    //У����
}Dev8Data_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

/*
	�豸����5״̬���ݽṹ
*/
typedef struct
{

	INT32U		ComTolNum;		//�ȱ�ͨ���ܴ���
	INT32U		ComSucNum; 	  	//�ȱ�ͨ�ųɹ�����
	INT32U		ComFauNum;	  	//����ͨ��ʧ�ܴ���

}Dev8State_Stru;



/*�豸����9���ݽṹ ��ͨͨ�Ͽ����� DDF2
�����ݱ䶯�ϴ�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

typedef struct
{

	INT8U	ControlType;	//��������
	
	INT8U	ForceCtrlFlg;	//ǿ�ƿ��Ʊ�־	
						//Force_NOR 	     =(INT8U)0X00,	//��ǿ��״̬		
						//Force_Close		=(INT8U)0XAA,	//ǿ�ƹط�
						//Force_Open		=(INT8U)0X55,	//ǿ�ƿ���

	INT8U	ValvePosition;			//����λ��
	INT32U	Cycle_OpTim;			//���ڿ���ʱ��
	INT16U	Cycle_OpRat;			//���ڿ�������
	INT32U	Apportion_Energy;		//��ǰ(��̯)����	
	INT8U	Valve_State;			//����״̬	

	INT16U	CRC16;				//У����
}Dev9Data_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�


/*
	�豸����4״̬���ݽṹ
*/
typedef struct
{

	INT32U		ComTolNum;		//ͨ���ܴ���
	INT32U		ComSucNum; 	  	//ͨ�ųɹ�����
	INT32U		ComFauNum;	  	//����ͨ��ʧ�ܴ���

}Dev9State_Stru;



/*�豸����10���ݽṹ   ��ͨ������������
�����ݱ䶯�ϴ�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	INT16U	Input_Temp;			    //��ˮ�¶�
	INT16U	Output_Temp;			//��ˮ�¶�
	
	INT32U	Instant_Current;        //˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Current_Unit;   //��λ
	
	INT32U	Instant_Energy;			//˲ʱ����(����)4 �����ʽ �����ʽ  HEX  X100
	INT8U	Instant_Energy_Unit;    //��λ
	
	INT32U	Total_Current;			//�ۼ�����4 �����ʽ BCD �����ʽ  HEX  X100
	INT8U	Total_Current_Unit;
	
	INT32U	Total_Code;				//�ۼ����� �������
	INT8U	Total_Code_Unit;        //��λ �������

	INT32U	Total_Energy;			//�ۼ����� �������
	INT8U	Total_Energy_Unit;		//��λ �������

	INT32U	CycBot_Energy;			//���ڱ�ף����ڼ�¼���ڿ�ʼʱ������ֵ

	INT32U	Apportion_Energy;		//�����ڷ�̯����   ��ǰ���-���ڱ��
	
	INT32U	Work_Time;				//����ʱ��
	INT8U	STATE1;				    //�ȱ����״̬1
	INT8U	STATE2;				    //�ȱ����״̬1
	
	INT16U	CRC16;				    //У����
}Dev10Data_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

/*
	�豸����7״̬���ݽṹ
*/
typedef struct
{

	INT32U		ComTolNum;		//�ȱ�ͨ���ܴ���
	INT32U		ComSucNum; 	  	//�ȱ�ͨ�ųɹ�����
	INT32U		ComFauNum;	  	//����ͨ��ʧ�ܴ���

}Dev10State_Stru;



/*�豸����11���ݽṹ   ������¥����Ԫ���ڷ�NWKmodbusЭ��
�����ݱ䶯�ϴ�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	float	Input_Temp;                 //��ˮ�¶�
	float	Output_Temp;                //��ˮ�¶�
    float   EnterWater_Pressure;        //��ˮѹ��
    float   ReturnWater_Pressure;       //��ˮѹ��
    float   Room_Temp;                  //����
    float   Current_Valve_Open;         //��ǰ���ſ���ֵ
    float   SetValue_Open;              //���÷��ſ���ֵ
    float   Temp_Diff;                  //�²��趨ֵ
    float   ReturnTemp_Set;             //��ˮ�¶��趨ֵ
    float   PressureDiff_Set;           //ѹ���趨ֵ
    INT8U   Error;                      //������� 0Ϊ������1Ϊ��ת��2Ϊ��ˮ�¶ȴ�������·��3.��ˮ�¶ȴ�������·��4.��ˮѹ����������·��5��ˮѹ����������·
    INT8U   Software_Version;           //����汾��  100 ��Ϊ V1.0 
    INT8U   Run_Mode;                   //����ģʽ  0Ϊ����ģʽ��1Ϊ�²�ģʽ2Ϊ����ģʽ3Ϊѹ��ģʽ4.�͵ؿ���ģʽ��������磩5.4-20���ƿ���ģʽ����Ӳ��֧�֣�6 TIME
    INT8U   Address;                    //��ַ 1-247��Ĭ��Ϊ1
    INT8U   Motor_Steering;             //���ת�� 0Ϊ���򷧣�1Ϊ����
    INT8U   Adjust_Switch;              //�Զ��г�У�����أ�0�رգ�1Ϊ�򿪣�ֵΪ1ʱÿ���ϵ��Զ�У���г�
    INT8U   Adjust_Tigger;              //д0x5555����һ��
    INT8U   Dc_Motor_Speed;             //ֱ������ٶ�
    
	//INT16U	CRC16;				    //У����
    
}Dev11Data_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�

/*
	�豸����11״̬���ݽṹ
*/
typedef struct
{

	INT32U		ComTolNum;		//�ȱ�ͨ���ܴ���
	INT32U		ComSucNum; 	  	//�ȱ�ͨ�ųɹ�����
	INT32U		ComFauNum;	  	//����ͨ��ʧ�ܴ���

}Dev11State_Stru;






#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef union
{

    Dev1Data_Stru Device1;	//FY-188 ��ھ��ȱ�
    Dev2Data_Stru Device2;	//FY-188 С�ھ��ȱ�
    Dev3Data_Stru Device3;	//FY-2000ͨ�Ͽ�����
    Dev4Data_Stru Device4;	//FY-2000ͨ�Ͽ����� ��ˮ��
	Dev5Data_Stru Device5;	//����CJ-T188 ��ھ��ȱ�
	Dev6Data_Stru Device6;	//��Դ�������ó����������� XY-188
	Dev7Data_Stru Device7;	//��ͨ������������ -188
    Dev8Data_Stru Device8;  //ɽ���������������������� -188
    Dev9Data_Stru Device9;  //��ͨͨ�Ͽ����� DDF2
    Dev10Data_Stru Device10;	//��ͨ������������ -188
    Dev11Data_Stru Device11;	//������¥����Ԫ���ڷ�NWKmodbusЭ��
    
}SysDevData_Stru;
#pragma pack()		//�ֽڶ���ģʽ ��ʡ�洢�ռ�







typedef union
{
    Dev1State_Stru Device1;	//FY-188 ��ھ��ȱ�
    Dev2State_Stru Device2;	//FY-188 С�ھ��ȱ�
    Dev3State_Stru Device3;	//FY-2000ͨ�Ͽ�����
    Dev4State_Stru Device4;	//FY-2000ͨ�Ͽ����� ��ˮ��
	Dev5State_Stru Device5;	//����CJ-T188 ��ھ��ȱ�
	Dev6State_Stru Device6;	//��Դ�������ó����������� XY-188

    Dev7State_Stru Device7;	//��ͨ������������ -188
    Dev8State_Stru Device8;	//ɽ���������������������� -188
    Dev9State_Stru Device9;  //��ͨͨ�Ͽ����� DDF2
    Dev10State_Stru Device10;  //��ͨ������������ -188
    Dev11State_Stru Device11;  //������¥����Ԫ���ڷ�NWKmodbusЭ��
    
}SysDevState_Stru;






DEVPARA_EXT SysDevData_Stru  SysDevData[MAXDevice_Num];	//ϵͳ�豸ʵʱ������
DEVPARA_EXT SysDevState_Stru  SysDevStatus[MAXDevice_Num];	//ϵͳ�豸״̬������
DEVPARA_EXT INT8U	SysDevStatusErr[MAXDevice_Num];			//ϵͳ�豸����״̬������


#ifdef _DEVPARA_C_




#endif
 


HAL_StatusTypeDef SysDeviceList_Init(void);
HAL_StatusTypeDef SysDeviceList_Update(void);
HAL_StatusTypeDef SysDeviceList_Reset(void);

HAL_StatusTypeDef SysDevData_Read(INT16U ListNum,SysDevData_Stru* Value);
HAL_StatusTypeDef SysDevData_Update(INT16U ListNum,SysDevData_Stru* Value);
HAL_StatusTypeDef SysDevData_Save(INT16U ListNum);
HAL_StatusTypeDef SysDevData_InitALL(INT16U UserNum);
HAL_StatusTypeDef SysDevData_ResetALL(INT16U DevNum);


/*

*/
typedef struct
{

    INT16U 	Num;				//�豸�б��±����ڿ��ټ���
	INT32U	ID;				    //�豸���
	INT16U   Users;         	//��������û�����

}BuildMeter_Stru;


DEVPARA_EXT BuildMeter_Stru BuildMeters[MAXBuldMeter_Num];
DEVPARA_EXT HAL_StatusTypeDef GetbuildMeterMessage(void);
DEVPARA_EXT HAL_StatusTypeDef GetMeters_Num(INT32U ID,SysDEV_Type Type,INT16U* Num);
DEVPARA_EXT HAL_StatusTypeDef GetMeters_Num_Build(INT32U ID,SysDEV_Type Type,INT16U* Num);


DEVPARA_EXT HAL_StatusTypeDef GetMeters_Num_FromUserID(INT32U ID,INT16U* Num);

DEVPARA_EXT void UpDateSysDevStatusErr(void);

DEVPARA_EXT void GetSystemUserNum(void);

DEVPARA_EXT void GetSystemDevMessage(void);
DEVPARA_EXT HAL_StatusTypeDef Getdevice_Num(INT32U ID,INT16U* Num);
DEVPARA_EXT HAL_StatusTypeDef GetDev_ComStatus(void);





#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
