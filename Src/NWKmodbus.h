


#ifndef _NWKMODBUS_H
#define _NWKMODBUS_H
#include "main.h"
#include "UART_RBC.h"
#include "PubDef.h"

#include "stm32f4xx_hal.h"
#include "Typedef.h "
#include "COM_Server.h"

#ifdef Valve_NWK_ENABLE
 
#ifdef _NWKmodbus_C_
#define NWK_EXT
#else
#define NWK_EXT extern
#endif
 


#define NWKPro_HeadSize				        2				    //���ݰ�ͷ��С
#define NWKPro_ACKProtocolCode03		    0X03				//03������
#define NWKPro_ACKProtocolCode06		    0X06				//06������
#define NWKPro_ACKProtocolSize  		    0X38				//�������ݳ���



#pragma pack(1)		//�ֽڶ���
typedef struct
{
	INT8U	Addr;		//��ʼ�ַ�		1�ֽ�
	INT8U	CMD;		//Э������		1�ֽ�
    
}NWK_Head_Stru;

#pragma pack()			//�ֽڶ���


//������ͨ��Э��
#pragma pack(1)			//�ֽڶ���
/*�豸����11���ݽṹ   ������¥����Ԫ���ڷ�NWKmodbusЭ��
�����ݱ䶯�ϴ�洢��FRAM
*/
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
    INT8U  Error;                      //������� 0Ϊ������1Ϊ��ת��2Ϊ��ˮ�¶ȴ�������·��3.��ˮ�¶ȴ�������·��4.��ˮѹ����������·��5��ˮѹ����������·
    INT8U  Software_Version;           //����汾��  100 ��Ϊ V1.0 
    INT8U  Run_Mode;                   //����ģʽ  0Ϊ����ģʽ��1Ϊ�²�ģʽ2Ϊ����ģʽ3Ϊѹ��ģʽ4.�͵ؿ���ģʽ��������磩5.4-20���ƿ���ģʽ����Ӳ��֧�֣�6 TIME
    INT8U  Address;                    //��ַ 1-247��Ĭ��Ϊ1
    INT8U  Motor_Steering;             //���ת�� 0Ϊ���򷧣�1Ϊ����
    INT8U  Adjust_Switch;              //�Զ��г�У�����أ�0�رգ�1Ϊ�򿪣�ֵΪ1ʱÿ���ϵ��Զ�У���г�
    INT8U  Adjust_Tigger;              //д0x5555����һ��
    INT8U  Dc_Motor_Speed;             //ֱ������ٶ�
}NWK_Pack_Value_t;





typedef struct
{
	NWK_Head_Stru       Head;           //01 03
    INT8U               lenth;
	NWK_Pack_Value_t    data;           //������ʵʱ����
	INT8U	            CRC16_H;        //CRC���ֽ� 44
	INT8U	            CRC16_L;        //CRC���ֽ� 03
}NWK_Pack_ACK_Stru;                     //ʵʱ���ݷ���




typedef union
{
	NWK_Pack_ACK_Stru   Pack;
}NWK_Pack_Uni;


//NWKͨ��Э�� ���ݳ��� ����
typedef struct
{
	NWK_Head_Stru  Head;                    //01 03
	
	INT8U	Register_Addr_H;				//�Ĵ�����ַ���ֽ� 00
	INT8U	Register_Addr_L;				//�Ĵ�����ַ���ֽ� 00
	
	INT8U	Register_Num_H;					//�Ĵ����������ֽ� 00
	INT8U	Register_Num_L;					//�Ĵ����������ֽ� 1C = 28(D)
	
	INT8U	CRC16_H;						//CRC���ֽ� 44
	INT8U	CRC16_L;                        //CRC���ֽ� 03
}NWK_Pack_Stru;//ʵʱ����

typedef union
{
    NWK_Pack_Stru Pack;
}NWK_Send_Uni;


#pragma pack() //�ֽڶ������




 
 


#ifdef _NWKmodbus_C_

INT8U NWK_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize);
INT8U NWK_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol);

#endif
 



NWK_EXT void NWK_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point );
NWK_EXT INT8U NWK_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point);


 
#endif

#endif


