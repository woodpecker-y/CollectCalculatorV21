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
* @date :2017/9/4 12:00
***************************************************************
*/ 
#ifndef _APP_UI_H_
#define _APP_UI_H_
 

#include "TypeDef.h"
#include "UC1698.h"
#include "String.h"



 
#ifdef _APP_UI_C_
#define APP_UI_EXT
#else
#define APP_UI_EXT extern
#endif
 


//�ն�״̬��ѯ�ṹ��

typedef struct
{
	char Data[2];
	INT8U Type;
}TerminalSTA_Stru;




//��Ļֵ��¼��
struct  SHOWMG
{
    INT8U    ra0;
    INT8U    ra1;
    INT8U    ra2;
    INT8U    ra3;
    INT8U    ra4;      //3
    INT8U    ra5;
    
};
APP_UI_EXT struct  SHOWMG ScreenRecord;

struct  PressIN_S
{
	unsigned	correct:8;		//������֤ͨ����־
	unsigned	PSWErr:8;		//������������־
	unsigned	password:16;   //������֤�м����
	unsigned	PSW1:16;		//�����޸�1
	unsigned	PSW2:16;		//�����޸�2

	unsigned	PSG1:4;       //������¼�м����
	unsigned	PSG2:4;

	unsigned	PSG3:4;
	unsigned	PSG4:4;

	unsigned	PSG5:4;
	unsigned	PSG6:4;

	unsigned	PSG7:4;
	unsigned	PSG8:4;

	unsigned	PSG9:4;
	unsigned	PSG10:4;

	unsigned	PSG11:4;
	unsigned	PSG12:4;

	unsigned	PSG13:4;
	unsigned	PSG14:4;

	unsigned	PSG15:4;
	unsigned	PSG16:4;

	unsigned	PSG17:4;
	unsigned	PSG18:4;	

	unsigned	PSG19:4;
	unsigned	PSG20:4;

	unsigned	PSG21:4;
	unsigned	PSG22:4;

	unsigned	PSG23:4;
	unsigned	PSG24:4;

	unsigned	PSG25:4;
	unsigned	PSG26:4;

	unsigned	PSG27:4;
	unsigned	PSG28:4;	

	unsigned	PSG29:4;
	unsigned	PSG30:4;	

	unsigned	PSG31:4;
	unsigned	PSG32:4;

	unsigned	PSG33:4;
	unsigned	PSG34:4;

	unsigned	PSG35:4;
	unsigned	PSG36:4;	

	unsigned	PSG37:4;
	unsigned	PSG38:4;

	unsigned	PSG39:4;
	unsigned	PSG40:4;	

	
	unsigned	C_Year:16;
	unsigned	C_Month:8;
	unsigned	C_Day:8;
	unsigned	C_Hour:8;
	unsigned	C_Minute:8;
	unsigned	C_Second:8;
	unsigned	C_Week:8;

	unsigned	S_Year:16;
	unsigned	S_Month:8;
	unsigned	S_Day:8;

	unsigned	F_Year:16;
	unsigned	F_Month:8;
	unsigned	F_Day:8;


	unsigned	Num_BuldMeter:16;	//������� 	ϵͳ����ʹ��
	unsigned	Num_User:16;		//�û���� 	ϵͳ����ʹ��
	unsigned	Num_Dev:16;		//�豸��� 	ϵͳ����ʹ��
	
	unsigned	User_ID:32;			//�û�������	�ɼ���Ψһʶ���־
	unsigned	Meter_ID:32;		//��Ʒ���к�	������������
	unsigned	Valve_ID:32;		//��Ʒ���к�	�¿ط��������

	unsigned	Buld:8;			//¥����
	unsigned	Unit:8;			//��Ԫ��
	unsigned	Floor:8;			//¥���
	unsigned	Cell:8;			//�����
	unsigned	CellArea:16;		//�������

	INT32U	Device_SN;	  		//�豸����
	unsigned	DeviceType:8;		//�豸����
	
	unsigned	ControlType:8;		//�ѿط�ʽ
	unsigned	COM_Ctrl:8; 		//ͨ�ſ���
	unsigned	IP1:8;				//IP
	unsigned	IP2:8;				//IP   
	unsigned	IP3:8;				//IP   
	unsigned	IP4:8;				//IP
	unsigned	PORT:32;//�˿ں�

	unsigned	UserNum:16;		//�û�����
	unsigned	UserNum_Pre:8;		//ϵͳ�û������ݴ���
	unsigned	ChannelUserNum:8;	//ͨ���û�����
	unsigned	MeterNum:8;		//�ȱ�����
	unsigned	MeterNum_Pre:8;		//ϵͳ�ȱ������ݴ���


	INT16U	Input_Temp;	//��ˮ�¶�
	INT16U	Output_Temp;	//��ˮ�¶�
	INT32U	Instant_Current;	//˲ʱ����
	INT32U	Instant_Energy;	//˲ʱ����
	INT32U	Total_Current;	//�ۼ�����
	INT32U	Total_Energy;	//�ۼ�����
	INT32U	Apportion_Energy;//��̯����
	INT32U	Working_Time;  //����ʱ��
	
	unsigned	FirstInFlag:8;//�״ν����־���輰�������õ���Ҫ��ȡ���������ý���
	unsigned	E2RomErr:8;//EERom�����־
	unsigned	FilterErr:8;//�û�����ʧ�ܱ�־
	
};
APP_UI_EXT struct  PressIN_S PressInData;


//����¼��

APP_UI_EXT INT16S  CursorRecord;     //��Ļ����ݴ���
APP_UI_EXT INT16U  CursorPRecord1;   //��Ļ����¼��
APP_UI_EXT INT16U  CursorPRecord2;   //��Ļ����¼��
APP_UI_EXT INT16U  CursorPRecord3;   //��Ļ����¼��
APP_UI_EXT INT16U  CursorPRecord4;   //��Ļ����¼��
APP_UI_EXT INT16U  CursorPRecord5;   //��Ļ����¼��
APP_UI_EXT INT16U  CursorPRecord6;   //��Ļ����¼��
APP_UI_EXT INT16U  CursorPRecord7;   //��Ļ����¼��
APP_UI_EXT INT16U  CursorPRecord8;   //��Ļ����¼��

 
 struct KEYMG
 {
	 unsigned	 flg; 	 //Ӧ�ð��������־
	 unsigned	 value;	 //Ӧ�ð���ֵ
	 unsigned	 resp;	 //Ӧ�ð�����Խλ����
 };
 APP_UI_EXT struct KEYMG Keyvalue;




 
#ifdef _APP_UI_C_




#endif
 



APP_UI_EXT void Menu_KeyManager(void);
APP_UI_EXT void DisplayManager(void);
APP_UI_EXT int setServerIP( uint8_t IP1, uint8_t IP2, uint8_t IP3, uint8_t IP4, uint16_t PORT );
APP_UI_EXT void getServerIP( uint8_t *IP1, uint8_t *IP2, uint8_t *IP3, uint8_t *IP4, uint16_t *PORT );


APP_UI_EXT INT32U LCD_light_Ct;			//LCD������� ����Ϣ��

 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
