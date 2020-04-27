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
* @date :2017/8/30 8:56
***************************************************************
*/ 
#ifndef _PUBDEF_H_
#define _PUBDEF_H_
 


#include "TypeDef.h"
 
#ifdef _PUBDEF_C_
#define PUBDEF_EXT
#else
#define PUBDEF_EXT extern
#endif
 

/*
ϵͳĬ�ϲ������ݳ�ʼ��
*/
#define SYSTEM_BulidTime            0X20191020			//ϵͳ��������
#define SYSTEM_VERSION              20191020            //�ɼ�������汾�ţ�32λ�޷���������



#define Valve_U_TempChange          0					//ͨ�Ͽ������¶�����  "0":������  "1":����



/**/
#define MAXUser_Num                 (320)				//ϵͳ����û�����
#define MAXBuldMeter_Num			(20)                 //ϵͳ���¥���ȱ�����
#define MAXUserMeter_Num			(MAXUser_Num)		//ϵͳ����û��ȱ�����
#define MAXUserValve_Num			(0)	//ϵͳ����û�ͨ�Ͽ���������
#define MAXDevice_Num				(MAXBuldMeter_Num+MAXUserMeter_Num+MAXUserValve_Num)




#define RemoRebotCont			    10ul                    //����Զ��������ʱ ��λ��
#define USE_POWRELAY			    0                     	//�����Ƿ���������·���Ƽ̵���  "1":����  "0":������

#define FileTransOUT                90000ul                 //�ļ����䳬ʱ�˳�ʱ�� ����




/*ϵͳ�豸����ѡ��궨��*/
/*���θú궨�壬ϵͳ�н�����Ϊ���豸������Դ*/


#define Meter_B_ENABLE          //��ھ�¥�������� FY-188
#define Meter_U_ENABLE          //С�ھ��û������� FY-188
#define Valve_U_ENABLE          //����ͨ�Ͽ�����   FY-2000
#define Valve_UH_ENABLE         //����ͨ�Ͽ�����(��ˮ���Ʒ�) FY-2000


#define Meter_H_ENABLE          //����¥�������� HZ-188
//#define Meter_XY_ENABLE         //��ԴС�ھ�������XY-188

//#define Meter_HT2X_ENABLE       //��ͨС�ھ�������HT2X
//#define Meter_BRC_ENABLE        //ɽ����������С�ھ�������BRC
#define Meter_DDF2_ENABLE       //��ͨͨ�Ͽ����� DDF2

#define Valve_NWK_ENABLE        //������¥����Ԫ���ڷ�modbusЭ��



/*END*/



/*ϵͳ�豸����ö��*/

typedef enum
{
	/* �豸���� */

	DEFUNULL =0X00,		    //��Ч
	
#ifdef Meter_B_ENABLE
	Meter_B =0X01,			//��ھ�¥�������� FY-188
#endif	

#ifdef Meter_U_ENABLE
	Meter_U =0X02,          //С�ھ��û������� FY-188
#endif

#ifdef Valve_U_ENABLE
	Valve_U =0X03,			//����ͨ�Ͽ�����   FY-2000
#endif

#ifdef Valve_UH_ENABLE
	Valve_UH =0X04,		    //����ͨ�Ͽ�����(��ˮ���Ʒ�) FY-2000
#endif

#ifdef Meter_H_ENABLE
	Meter_H =0x05,		    //����¥�������� HZ-188
#endif

#ifdef Meter_XY_ENABLE
	Meter_XY =0x06,		    //��ԴС�ھ�������XY-188
#endif	

#ifdef Meter_HT2X_ENABLE
    Meter_HT2X =0x07,	    //��ͨС�ھ�������HT2X
    Meter_HT3X =0x0A,	    //��ͨС�ھ�������HT3X     �����豸���ͺ�HT2Xֻ��Ӵ���Ϳ����ֵ�����
#endif

#ifdef Meter_BRC_ENABLE
    Meter_BRC =0x08,	    //ɽ����������С�ھ�������BRC
#endif

#ifdef Meter_DDF2_ENABLE
    Meter_DDF2 =0x09,	    //��ͨͨ�Ͽ����� DDF2
#endif

#ifdef Valve_NWK_ENABLE
    Valve_NWK =0x0B,	    //������¥����Ԫ���ڷ�modbusЭ��
#endif

}SysDEV_Type;


#define MAXDevTypeNum 11



typedef enum
{
	kW =0X17,               //���ʵ�λ	ǧ��
	kW_h =0X05,             //������λ 	ǧ��.ʱ
	MW=0X1A,                //���ʵ�λ	����
	MW_h=0X08,              //������λ	����.ʱ	
	m3PreH =0X35,           //������λ	������ÿСʱ
	m3 =0X2C,               //������λ	������
	GJ=0X11                 //������λ	G����
	
}MeterUnit_Type;



typedef enum
{
	Type_NotSet=0X00,			//��������δ����
	Type_Meter=0X01,			//���������ϵͳ
	Type_MeterValve=0X02,		//�¿ؼ���  ������
	Type_Valve=0X03             //ͨ��ʱ������� ֻ�з� û�б�

}DeviceType;


typedef enum
{
	DevSendMode_Nor=0,          //���Զ��ϱ�
	DevSendMode_Auto=1,         //�Զ������ϱ�
	DevSendMode_Loop=2,         //��ʱѭ���ϱ�
}DeviceSendType;                //�豸�����ϱ�����






typedef enum
{

	TCFlag_OFF  =0XFF,
	TCFlag_ON   =0XAA,

	Valve_Open	=(INT8U)0X0A,	//����	��������־
	Valve_Mid	=(INT8U)0X55,	//�м�״̬
	Valve_Close	=(INT8U)0XA0,	//�ط�	��������־

}Flag_Type;

typedef enum
{
	Force_Nor 	=(INT8U)0X00,	//��ǿ��״̬		
	Force_Close	=(INT8U)0XAA,	//ǿ�ƹط�
	Force_Open	=(INT8U)0X55,	//ǿ�ƿ���
}ValveForce_Type;



#include "UserPara.h"
#include "DevPara.h"


/* SPI Flash�洢����ַ�궨��*/
#define	SysPara_Addr                100UL                   //ϵͳ�����洢��ʼ��ַ
#define	SysUserList_Addr            4096UL*16ul             //�û�������¼�б���ʼ��ַ
#define	SysUserList_Size            (SysDeviceList_Addr - SysUserList_Addr)
#define	SysDeviceList_Addr			4096UL*32ul             //ϵͳ�豸��¼�б���ʼ��ַ
#define	SysDeviceList_Size			(SysOTAPara_Addr   -SysDeviceList_Addr)
#define	SysOTAPara_Addr				4096UL*64ul
#define	SysOTAPara_Size				(SysDownload_Temp_Addr -SysOTAPara_Addr)

#define	SysDownload_Temp_Addr       (4096UL*68ul)           //�ļ����ػ�������ʼ��ַ
#define	SysDownload_Temp_Size       (4096UL*256ul)          //�ļ����ػ�������С



/*  ����洢����ַ�궨��   */
#define	PowerState_Addr             (0)                     //�û������б��ַ
#define	UserData_Addr               (16ul)                  //�û������б��ַ
#define	DevData_Addr                (UserData_Addr+MAXUser_Num*sizeof(UserData_Stru)+32ul)  //�豸�������б���ʼ��ַ
#define	FRAM_USED                   (DevData_Addr+MAXDevice_Num*sizeof(SysDevData_Stru))


#define	LCD_OFF_TICKS               (120*1000ul)                                                         //����LCDϢ�� ��ʱ���



#ifdef _PUBDEF_C_




#endif
 




 
 




 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
