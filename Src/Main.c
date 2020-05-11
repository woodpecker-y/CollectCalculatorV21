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
* @brief :������
* 
* 
* 
*
* @author :��ΰ
* @date :2017/8/23 17:24
***************************************************************
*/ 
#define _MAIN_C_

#include "main.h"
#include "stm32f4xx_hal.h"


extern int os_debug_enabled;		
extern int os_debug_level;



/*
	Task01
	ʵʱʱ�ӷ�����
*/
#define Task01_Prio				2			//�������ȼ�
#define Task01_StkSize 			2048 		//�����ջ��С	
TaskHandle_t Task01_Handle;					//������
void Task01_F(void const * argument);		//������
/*END */



/*
	Task02
*/
#define Task02_Prio				3			//�������ȼ�
#define Task02_StkSize 			128  		//�����ջ��С	
TaskHandle_t Task02_Handle;					//������
void Task02_F(void const * argument);		//������
/*END */



/*
	Task03
	�豸������Ӧ������
	
*/
#define Task03_Prio				4			//�������ȼ�
#define Task03_StkSize 			256  		//�����ջ��С	
TaskHandle_t Task03_Handle;					//������
void Task03_F(void const * argument);		//������
/*END */





/*
	Task04
	�豸��ʾ����
*/
#define Task04_Prio				5			//�������ȼ�
#define Task04_StkSize 			256  		//�����ջ��С	
TaskHandle_t Task04_Handle;					//������
void Task04_F(void const * argument);		//������
/*END */




/*
	Task05
	�첽����ͨ�Ž��շ���
*/
#define Task05_Prio				12			//�������ȼ�
#define Task05_StkSize 			256  		//�����ջ��С	
TaskHandle_t Task05_Handle;					//������
void Task05_F(void const * argument);		//������
/*END */


/*
	Task06
	�첽����ͨ�ŷ��ͷ���
*/
#define Task06_Prio				11			//�������ȼ�
#define Task06_StkSize 			256  		//�����ջ��С	
TaskHandle_t Task06_Handle;					//������
void Task06_F(void const * argument);		//������
/*END */


/*
	Task07
	�첽����ͨ�Ŵ������
*/
#define Task07_Prio				6			//�������ȼ�
#define Task07_StkSize 			256  		//�����ջ��С	
TaskHandle_t Task07_Handle;					//������
void Task07_F(void const * argument);		//������
/*END */



/*
	Task08
	Client ͨ��ͨ�����ͷ���
*/
#define Task08_Prio				4			//�������ȼ�
#define Task08_StkSize 			256  		//�����ջ��С	
TaskHandle_t Task08_Handle;					//������
void Task08_F(void const * argument);		//������
/*END */


/*
	Task09
	Clientͨ��ͨ�����߿��Ʒ���
*/
#define Task09_Prio				4			//�������ȼ�
#define Task09_StkSize 			256  		//�����ջ��С	
TaskHandle_t Task09_Handle;					//������
void Task09_F(void const * argument);		//������
/*END */


/*
	Task10
	Client ͨ��ͨ��1 �豸�㲥��ʱ��������
*/
#define Task10_Prio				2			//�������ȼ�
#define Task10_StkSize 			256  		//�����ջ��С	
TaskHandle_t Task10_Handle;					//������
void Task10_F(void const * argument);		//������


/*
	Task11
	�ɼ�������ͨ�ŷ��� ����

#define Task11_Prio				3			//�������ȼ�
#define Task11_StkSize 			256  		//�����ջ��С	
TaskHandle_t Task11_Handle;					//������
void Task11_F(void const * argument);		//������
*/

/*
	TaskCli
	�����ն�����
*/
#define TaskCli_Prio            1			//�������ȼ�
#define TaskCli_StkSize         2048  		//�����ջ��С	
TaskHandle_t TaskCli_Handle;                //������
void TaskCli(void const * argument);        //������



/*
	Task12
	�û���ʱ�����ϴ�����
*/
#define Task12_Prio				3			//�������ȼ�
#define Task12_StkSize 			256  		//�����ջ��С	
TaskHandle_t Task12_Handle;					//������
void Task12_F(void const * argument);       //������




/*
	Task13
	�û���ʱ�����ϴ�����
*/
#define Task13_Prio				2			//�������ȼ�
#define Task13_StkSize 			256  		//�����ջ��С	
TaskHandle_t Task13_Handle;					//������
void Task13_F(void const * argument);       //������








osTimerId Timer01Handle;						//��ʱ��1���
SemaphoreHandle_t Display_Semaphore;			//�������ź��� ����LCDˢ��
SemaphoreHandle_t UseSend_Semaphore;			//�������ź��� �û����� ��������
SemaphoreHandle_t EneryShare_Semaphore;			//�������ź��� ����ϵͳ������̯
SemaphoreHandle_t DataSave_Semaphore;			//�豸��ʷ���ݱ���



/*ϵͳ��ʱ������ط������� */
RealClock_Str  AlarmTime;						//�������崥����ʱʱ�� ȫ��

/* ��ʷ���ݱ������� */
AlarmClk_Stru* Alarm_DataSave;					//������ʷ���ݱ�������
void Alarm_DataSave_CallBack(void); 			//������ʷ���ݱ������崥���ص�����


/* �û�������ʱ��̯ */
AlarmClk_Stru* Alarm_UserShare;					//�����û����ݶ�ʱ��̯����
void Alarm_UserShare_CallBack(void); 			//�����û����ݶ�ʱ��̯���崥���ص�����

EventBits_t Iwdg_T1;
EventBits_t Iwdg_T2;
EventBits_t Iwdg_T5;
EventBits_t Iwdg_T6;
EventBits_t Iwdg_T7;

EventBits_t Iwdg_T8;
EventBits_t Iwdg_T9;
EventBits_t Iwdg_T10;





#define APP_VECT_TAB_OFFSET    0x20000	//�ж�������ƫ��
int main(void)
{


	/* ����BootLoader��Ҫ�����ж�������ַ */
//	SCB->VTOR = FLASH_BASE | APP_VECT_TAB_OFFSET;
	 
    HAL_Init();							//HAL�����ʼ��
    SystemClock_Config();				//ϵͳʱ�ӳ�ʼ��

	SysLed_Cfg();						//ϵͳ����ָʾ�Ƴ�ʼ��
	SP706_Cfg();						//�ⲿ��λоƬSP706��ʼ��
	dogInit();							//�ػ����Ź������ʼ��
	SysBeep_Cfg();						//ϵͳ���������ܳ�ʼ��

	huart1.Init.BaudRate =115200;		
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.Parity =UART_PARITY_NONE;
	UART1_Cfg();						//ͨ���첽�˿�1��ʼ��

	int cli_res = cli_init();			//�����ն˼�����ģ���ʼ��
	
	huart2.Init.BaudRate =9600;
	huart2.Init.WordLength = UART_WORDLENGTH_9B;
	huart2.Init.Parity =UART_PARITY_EVEN;
	UART2_Cfg();						//ͨ���첽�˿�2��ʼ��

	
	huart3.Init.BaudRate =2400;
	huart3.Init.WordLength = UART_WORDLENGTH_9B;
	huart3.Init.Parity =UART_PARITY_EVEN;	
	UART3_Cfg();						//ͨ���첽�˿�3��ʼ��

	
	M4_CRC_PHY_Init();					//Ӳ��CRC��ʼ��


	IIC1_Cfg();							//IIC1Ӳ���ӿڳ�ʼ��
	FRAM_Init();						//����洢����ʼ��
	IIC2_Cfg();							//IIC2Ӳ���ӿڳ�ʼ��


	MX_FATFS_Init();                    //FATFS�ļ�ϵͳ��ʼ��
    
    


	/* ϵͳ���������ʼ��*/
	AlarmClk_Init();		

	/*
		���ݱ������崥���¼�
		���崴�� 
		@ʹ�� ��ֹ   
		@�ص�����   
		@���ڴ���ʹ��
		@ѭ��ʱ��  XX(����)
	*/
	Alarm_DataSave = AlarmClk_CreatOne( AlarmClk_Disable,Alarm_DataSave_CallBack,AlarmClk_Enable,60*24);
	AlarmTime.Year =2017;
	AlarmTime.Month =10;
	AlarmTime.Day =27;
	AlarmTime.Hour =23;
	AlarmTime.Minute = 55;
	AlarmTime.Second = 00;
	AlarmClk_ParaSet(Alarm_DataSave,&AlarmTime);
	AlarmClk_EnableCtrl(Alarm_DataSave,AlarmClk_Enable);





/*�첽�����շ���ͨ�������ʼ��*/
	UART_RBC_ControlerInit();
	
	UART_TO_FY1000_CCB_Init_S();											//FY1000ͨ���������˳�ʼ��
	UART_TO_FY2000_CCB_Init_S();											//FY2000ͨ���������˳�ʼ��
	UART_TO_FY188_CCB_Init_S();											    //FY188ͨ���������˳�ʼ��

#ifdef Meter_H_ENABLE
	UART_TO_HZCRL_CCB_Init_S();											    //HZ188ͨ���������˳�ʼ��
#endif

#ifdef  Meter_XY_ENABLE	    
	UART_TO_XY188_CCB_Init_S();											    //XY188ͨ���������˳�ʼ��
#endif    
	
#ifdef  Meter_HT2X_ENABLE	    
        UART_TO_HT2X188_CCB_Init_S();                                       //HT2X188ͨ���������˳�ʼ��
#endif  

#ifdef  Meter_BRC_ENABLE	    
        UART_TO_BRC188_CCB_Init_S();                                        //BRC188ͨ���������˳�ʼ��
#endif    

#ifdef  Meter_DDF2_ENABLE	    
        UART_TO_DDF2_CCB_Init_S();                                          //DDF2ͨ���������˳�ʼ��
#endif  

#ifdef  Valve_NWK_ENABLE	    
        UART_TO_NWK_CCB_Init_S();                                          //NWKͨ���������˳�ʼ��
#endif  

/*END*/





	W25QXX_Init();					                                        //Ƭ��Flash��ʼ��
	FlashID =W25QXX_ReadID();		                                        //��ȡFlashID


	PowerRelay_Init();				                                        //�������·���Ƽ̵�����ʼ��

	dbg_printf(DEBUG_INFO,"ϵͳ���ڳ�ʼ��......��ӭʹ��......\r\n\r\n");

	/*   ϵͳ������ʼ��......*/
	if( SysPara_Init() ==HAL_OK )
	{
		os_debug_enabled    = SysPara.DebugEnable;
		os_debug_level      = SysPara.DebugLevel;

		dbg_printf(DEBUG_INFO, "ϵͳ��������ʼ�����......\r\n");
		dbg_printf(DEBUG_DEBUG, "ϵͳ��������ַ:   %ld", SysPara_Addr);
		dbg_printf(DEBUG_DEBUG, "ϵͳ����������:   %d", sizeof(SysPara_Stru));	
		
	}
	else
	{
		dbg_printf(DEBUG_ERR,"ϵͳ������ʼ��ʧ��......\r\n");
		SysPara_Reset();
	}

	dbg_printf(DEBUG_INFO,"���Զ˿�UART1 %d  %c  %d  %d...", huart1.Init.BaudRate, 'N', 8, huart1.Init.StopBits);
	dbg_printf(DEBUG_DEBUG,"STM32F407VGT6...\r\n");


	if(FRAM_USED > FRAM_Size)
	{
		while(1)
		{
			dbg_printf(DEBUG_ERR,"FRAM ��������...\r\n");
			HAL_Delay(2000);
		}
	}


	switch(FlashID)
	{
		case 0XEF13 :
		{
			dbg_printf(DEBUG_INFO,"����Flash�ͺ�: W25Q80,���� 1M Byte\r\n");
		}break;
		
		case 0XEF14 :
		{
			dbg_printf(DEBUG_INFO,"����Flash�ͺ�: W25Q16,���� 2M Byte\r\n");
		}break;	
		
		case 0XEF15 :
		{
			dbg_printf(DEBUG_INFO,"����Flash�ͺ�: W25Q32,���� 4M Byte\r\n");
		}break;	

		case 0XEF16 :
		{
			dbg_printf(DEBUG_INFO,"����Flash�ͺ�: W25Q64,���� 8M Byte\r\n");
		}break;	

		case 0XEF17 :
		{
			dbg_printf(DEBUG_INFO,"����Flash�ͺ�: W25Q128,���� 16M Byte\r\n");
		}break;	
		
		case 0XEF18 :
		{
			dbg_printf(DEBUG_INFO,"����Flash�ͺ�: W25Q256,���� 32M Byte\r\n");
		}break;	
		default :
		{
			dbg_printf(DEBUG_INFO,"����Flash��ʼ��ʧ��\r\n");

		}break;
	}




	/*	 �û�������ʼ��......*/
	if( SysUserList_Init() ==HAL_OK)
	{
		GetSystemUserNum();
		dbg_printf(DEBUG_INFO,"�û���������ʼ�����......");
		dbg_printf(DEBUG_DEBUG,"�û�������ַ:   %ld",SysUserList_Addr);
		dbg_printf(DEBUG_DEBUG,"�û���������:   %d\r\n",sizeof(SysUserList_Stru));
	}
	else
	{
		dbg_printf(DEBUG_ERR,"�û���������ʼ��ʧ��......\r\n\r\n");
	}
	




	/*	 �豸������ʼ��......*/
	if( SysDeviceList_Init() ==HAL_OK)
	{
		GetSystemDevMessage();
		dbg_printf(DEBUG_INFO,"�豸��������ʼ�����......");
		dbg_printf(DEBUG_DEBUG,"�豸������ַ:   %ld",SysDeviceList_Addr);
		dbg_printf(DEBUG_DEBUG,"�豸��������:   %d\r\n",sizeof(SysDeviceList_Stru));
	}
	else
	{
		dbg_printf(DEBUG_ERR,"�豸��������ʼ��ʧ��......\r\n\r\n");
	}
	



	/*  �û����ݳ�ʼ�� */
	if( UserData_InitALL(MAXUser_Num) ==HAL_OK )
	{
		dbg_printf(DEBUG_INFO,"�û���������ʼ�����......");
		dbg_printf(DEBUG_DEBUG,"�û�����:       %d",MAXUser_Num);
		dbg_printf(DEBUG_DEBUG,"�û����ݵ�ַ:   %ld",UserData_Addr);
		dbg_printf(DEBUG_DEBUG,"�û���������:   %d\r\n",sizeof(UserData_Stru)*MAXUser_Num);

	}
	else
	{
		dbg_printf(DEBUG_ERR,"�û���������ʼ��ʧ��......\r\n");
	}



	
	
	/* �豸���ݳ�ʼ��*/
	if( SysDevData_InitALL(MAXDevice_Num) ==HAL_OK )
	{
		dbg_printf(DEBUG_INFO,"�豸��������ʼ�����......");
		dbg_printf(DEBUG_DEBUG,"�豸����:       %d",MAXDevice_Num);
		dbg_printf(DEBUG_DEBUG,"�豸���ݵ�ַ:   %ld",DevData_Addr);
		dbg_printf(DEBUG_DEBUG,"�豸��������:   %d\r\n",MAXDevice_Num*sizeof(SysDevData_Stru));
	}
	else
	{
		dbg_printf(DEBUG_ERR,"�豸��������ʼ��ʧ��......\r\n\r\n");
	}	



	dbg_printf(DEBUG_INFO,"�豸������ȫ����ʼ�����...");
	dbg_printf(DEBUG_INFO,"DEBUG_DEBUG:       %ld....\r\n",FRAM_USED);



	ID =HAL_GetREVID();
	dbg_printf(DEBUG_DEBUG,"HAL_GetREVID:%ld",ID);
	
	ID =HAL_GetDEVID();
	dbg_printf(DEBUG_DEBUG,"HAL_GetDEVID:%ld",ID);
	
	Get_ChipID( &ChipID);
	dbg_printf(DEBUG_DEBUG,"MCUchipID:%d %d %d \r\n\r\n",ChipID.Fourdata.ChipUniqueID[0],ChipID.Fourdata.ChipUniqueID[1],ChipID.Fourdata.ChipUniqueID[2]);

	
	Init_PaulseFunction();										//����������ƹ��ܳ�ʼ��
    Beep_Ctrler=Pulse_Create(0,BeepWork_RebackFun);				//����һ���������   ʹ��λ   �ص�����
	PulseLeaguer_SET(Beep_Ctrler, 1, 100, 3, 20, 0, 0);         //����ָ��  ��������  ɨ����(tick*X) ���ؿ��   ����    ���ڼ�����  ��ǰ״̬
	PulseLeaguer_Enalbe(Beep_Ctrler, 1);                        //ʹ��ĳ���������ģ��	


    LedBR_Ctrler=Pulse_Create(0,LEDBR_RebackFun);               //����һ���������   ʹ��λ   �ص�����
	PulseLeaguer_SET(LedBR_Ctrler, 2, 10, 8, 16, 0, 0);         //����ָ��  ��������  ɨ����(tick*X) ���ؿ��   ����    ���ڼ�����  ��ǰ״̬
	PulseLeaguer_Enalbe(LedBR_Ctrler, 1);                       //ʹ��ĳ���������ģ��	


	if(PCF8563_Read(&RTC_Time) ==HAL_OK)						//ʵʱʱ�Ӷ�ȡ
	{
		dbg_printf(DEBUG_INFO,"ʵʱʱ�ӳ�ʼ�����...\r\n");
	}
	else
	{
		dbg_printf(DEBUG_ERR,"ʵʱʱ�ӳ�ʼ������...\r\n\r\n");
	}
	
	PowerStateRecord_Init();									//�ϵ��¼������ʼ��
	PowerStateRecord_Update();								    //�ϵ��¼��������



	/*����ϵͳ��ʼ������*/

	portENTER_CRITICAL();	                                    //�����ٽ���
	dbg_printf(DEBUG_INFO,"ϵͳӲ��ʼ����ɣ�����ϵͳ������...\r\n");
	fy1000SendMetexInit();                                      //FY1000Send��������ʼ��
	ClientCH1SendMetexInit();	                                //�ն�ͨ��ͨ����������ʼ��
	
	KEY_OUT_Msg =xQueueCreate(BUTTONMSG_Q_NUM, sizeof(KEY_OUT_Stru));							            //����Ӧ���ڰ�������Ϣ����
    
	UART_TO_FY188_Msg =xQueueCreate(UART_TO_FY188_Q_NUM, sizeof(UART_TO_FY188_QueueSend_Stru*));	        //����Ӧ����UARTRBC����Ϣ����
	UART_TO_FY2000_Msg =xQueueCreate(UART_TO_FY2000_Q_NUM, sizeof(UART_TO_FY2000_QueueSend_Stru*));	        //����Ӧ����UARTRBC����Ϣ����
	UART_TO_FY1000_Msg =xQueueCreate(UART_TO_FY1000_Q_NUM, sizeof(UART_TO_FY1000_QueueSend_Stru*));	        //����Ӧ����UARTRBC����Ϣ����

    
#ifdef Meter_H_ENABLE
	UART_TO_HZCRL_Msg =xQueueCreate(UART_TO_HZCRL_Q_NUM, sizeof(UART_TO_HZCRL_QueueSend_Stru*));	        //����Ӧ����UARTRBC����Ϣ����
#endif

#ifdef Meter_XY_ENABLE
	UART_TO_XY188_Msg =xQueueCreate(UART_TO_XY188_Q_NUM, sizeof(UART_TO_XY188_QueueSend_Stru*));	        //����Ӧ����UARTRBC����Ϣ����
#endif

#ifdef Meter_HT2X_ENABLE
        UART_TO_HT2X188_Msg =xQueueCreate(UART_TO_HT2X188_Q_NUM, sizeof(UART_TO_HT2X188_QueueSend_Stru*));   //����Ӧ����UARTRBC����Ϣ����
#endif

#ifdef Meter_BRC_ENABLE
        UART_TO_BRC188_Msg =xQueueCreate(UART_TO_BRC188_Q_NUM, sizeof(UART_TO_BRC188_QueueSend_Stru*));      //����Ӧ����UARTRBC����Ϣ����
#endif

#ifdef Meter_DDF2_ENABLE
        UART_TO_DDF2_Msg =xQueueCreate(UART_TO_DDF2_Q_NUM, sizeof(UART_TO_DDF2_QueueSend_Stru*));            //����Ӧ����UARTRBC����Ϣ����
#endif

#ifdef Valve_NWK_ENABLE
        UART_TO_NWK_Msg = xQueueCreate(UART_TO_NWK_Q_NUM, sizeof(UART_TO_NWK_QueueSend_Stru*));               //����Ӧ����UARTRBC����Ϣ����
#endif



	
	ClientCH1_Msg =xQueueCreate(ClientCH1_Q_NUM, sizeof(ClientCH1_Queue_Stru*));        //����Ӧ�����ն�ͨ�ŵ���Ϣ����

	Display_Semaphore =xSemaphoreCreateCounting(8,0);                                   //����������LCDɨ��ļ������ź���
	UseSend_Semaphore =xSemaphoreCreateCounting(4,0);                                   //�����������ź��� �û����ݵķ�������
	EneryShare_Semaphore=xSemaphoreCreateCounting(4,0);                                 //�����������ź��� ����ϵͳ����������̯
						
	dbg_printf(DEBUG_DEBUG,"ϵͳ�ź�����ʼ�����...\r\n");
	
    //Task01
    xTaskCreate((TaskFunction_t )Task01_F,				//ʵʱʱ��  
                (const char*	)"RealTimeClk",   	    //��������
                (uint16_t	)Task01_StkSize,			//�����ջ
                (void*		)NULL,			            //�������
                (UBaseType_t	)Task01_Prio,		    //�������ȼ� 2
                (TaskHandle_t*	)&Task01_Handle);	    //������


    //Task02
    xTaskCreate((TaskFunction_t )Task02_F,				//�������  
                (const char*	)"PulseCTRL",   	    //��������
                (uint16_t	)Task02_StkSize,			//�����ջ
                (void*		)NULL,			            //�������
                (UBaseType_t	)Task02_Prio,		    //�������ȼ� 3
                (TaskHandle_t*	)&Task02_Handle);	    //������

    //Task03
    xTaskCreate((TaskFunction_t )Task03_F,				//����ɨ�������  
                (const char*	)"UI_KEY",   		    //��������
                (uint16_t	)Task03_StkSize,			//�����ջ
                (void*		)NULL,			            //�������
                (UBaseType_t	)Task03_Prio,		    //�������ȼ� 4
                (TaskHandle_t*	)&Task03_Handle);	    //������


    //Task04
    xTaskCreate((TaskFunction_t )Task04_F,				//Һ������������  
                (const char*	)"UI_LCD",   	        //��������
                (uint16_t	)Task04_StkSize,			//�����ջ
                (void*		)NULL,			            //�������
                (UBaseType_t	)Task04_Prio,		    //�������ȼ� 5
                (TaskHandle_t*	)&Task04_Handle);	    //������

    //Task05
    xTaskCreate((TaskFunction_t )Task05_F,				//�첽����ͨ�Ž��շ���  
                (const char*	)"UART_RBC_Rx",         //��������
                (uint16_t	)Task05_StkSize,			//�����ջ
                (void*		)NULL,			            //�������
                (UBaseType_t	)Task05_Prio,		    //�������ȼ� 12
                (TaskHandle_t*	)&Task05_Handle);	    //������


    //Task06
    xTaskCreate((TaskFunction_t )Task06_F,				//�첽����ͨ�ŷ��ͷ���  
                (const char*	)"UART_RBC_Tx",         //��������
                (uint16_t	)Task06_StkSize,			//�����ջ
                (void*		)NULL,			            //�������
                (UBaseType_t	)Task06_Prio,		    //�������ȼ� 11
                (TaskHandle_t*	)&Task06_Handle);	    //������


    //Task07
    xTaskCreate((TaskFunction_t )Task07_F,				//�첽����ͨ�ŷ�����  
                (const char*	)"UART_Packing",        //��������
                (uint16_t	)Task07_StkSize,			//�����ջ
                (void*		)NULL,			            //�������
                (UBaseType_t	)Task07_Prio,		    //�������ȼ� 6
                (TaskHandle_t*	)&Task07_Handle);	    //������


    //Task08
    xTaskCreate((TaskFunction_t )Task08_F,				//Client ͨ��ͨ��1 ���ͷ���  
                (const char*	)"ClientSend",          //��������
                (uint16_t	)Task08_StkSize,			//�����ջ
                (void*		)NULL,			            //�������
                (UBaseType_t	)Task08_Prio,		    //�������ȼ� 4
                (TaskHandle_t*	)&Task08_Handle);	    //������        


    //Task09
    xTaskCreate((TaskFunction_t )Task09_F,				//Client ͨ��ͨ��1 ���߿��Ʒ���  
                (const char*	)"ClientCtrler",        //��������
                (uint16_t	)Task09_StkSize,			//�����ջ
                (void*		)NULL,			            //�������
                (UBaseType_t	)Task09_Prio,		    //�������ȼ� 4
                (TaskHandle_t*	)&Task09_Handle);	    //������     

              
    //Task10
    xTaskCreate((TaskFunction_t )Task10_F,				//Client ͨ��ͨ��1 �豸�㲥��ʱ��������  
                (const char*	)"Task10_N",   	        //��������
                (uint16_t	)Task10_StkSize,			//�����ջ
                (void*		)NULL,			            //�������
                (UBaseType_t	)Task10_Prio,		    //�������ȼ� 2
                (TaskHandle_t*	)&Task10_Handle);	    //������ 



                
/*
    //Task11
    xTaskCreate((TaskFunction_t )Task11_F,				//������  
                (const char*	)"Task11_N",   	        //��������
                (uint16_t	)Task11_StkSize,			//�����ջ
                (void*		)NULL,			            //�������
                (UBaseType_t	)Task11_Prio,		    //�������ȼ�
                (TaskHandle_t*	)&Task11_Handle);	    //������                     
*/



	//TaskCli
	if(CLI_R_OK == cli_res)
	{
		xTaskCreate((TaskFunction_t )TaskCli,		    //�����ն�����  
					(const char*	)"TaskCli",   	    //��������
					(uint16_t	)TaskCli_StkSize,	    //�����ջ
					(void*		)NULL,			        //�������
					(UBaseType_t	)TaskCli_Prio,		//�������ȼ� 1
					(TaskHandle_t*	)&TaskCli_Handle);	//������     
	}



    //Task12  
    xTaskCreate((TaskFunction_t )Task12_F,				//�û����ݶ�ʱ�ϱ�����   
                (const char*	)"Userdata_Send",   	//��������
                (uint16_t	)Task12_StkSize,			//�����ջ
                (void*		)NULL,				        //�������
                (UBaseType_t	)Task12_Prio,			//�������ȼ� 3
                (TaskHandle_t*	)&Task12_Handle);		//������    


    //Task13  
    xTaskCreate((TaskFunction_t )Task13_F,				//�豸���ݼ���ϱ�����   
                (const char*	)"Devdata_Send",   	    //��������
                (uint16_t	)Task13_StkSize,			//�����ջ
                (void*		)NULL,				        //�������
                (UBaseType_t	)Task13_Prio,			//�������ȼ� 2
                (TaskHandle_t*	)&Task13_Handle);		//������   



		
	dbg_printf(DEBUG_INFO,"����ϵͳ���سɹ�...");
	dbg_printf(DEBUG_INFO,"ϵͳ��ʼ�����......��ӭʹ��...");	
	dbg_printf(DEBUG_INFO,"MakeInfo: %s %s \r\n\r\n",__DATE__,__TIME__); 
	portEXIT_CRITICAL();//�˳��ٽ����



	
    osKernelStart();
	/*����ϵͳ��ʼ������*/

	
    while (1){}
}



void TaskCli(void const * argument)
{
  /* Infinite loop */
	cli_main();
	osThreadTerminate(NULL);
}









/*��������*/
void vApplicationIdleHook(void)
{
	if( xTaskGetTickCount() !=SystemTick_ms)
	{
		SystemTick_ms	=xTaskGetTickCount();

		if(SystemTick_ms -SP706_Tick >ExWDT_CLs)
		{
			SP706_Tick =SystemTick_ms;
		}
	}
	/*����������ִ�з�����*/
	PulseCtrl_Executing();
}













/* 

Timer01Callback01 function
��ʱ��1�Ļص�����������

*/
void Timer01Callback(void const * argument)
{
	static INT32U LoopTimes =0;

    LoopTimes ++;
	IndepKEY_ScanServer();	//����ɨ�躯����ע���ɨ�����������û������ ע������ɨ����

	
	if(SystemTick_ms -LCD_light_Ct >LCD_OFF_TICKS)	//��ʱ��û�а���������ˢ��
	{
		LCD_BL_OFF;
	}
	else
	{
		if(LoopTimes >=400)		//ѭ������ʱ�� 400*5 =2000����
		{
			LoopTimes =0;
			xSemaphoreGive(Display_Semaphore);
			LCD_BL_ON;
		}
		
	}


}



/*
Task01_F function 
ʵʱʱ��


*/
void Task01_F(void const * argument)
{
	INT32U Times =0;
	INT32U Times1 =0;
	INT32U Times2 =0;
	
	static INT16U RealySt = 0;
	RealySt =SysPara.RelayRecord;

	PowerRelay_SET(RealySt);			//����·�̵�����������
	createIWDG( &Iwdg_T1, 30);		    //������Ź�����

	

    while(1)
    {

		feedIWDG(Iwdg_T1);
		Times +=1;
		Times1 +=1;
		Times2 +=1;
		
        LED_RUN_Toggle;

		if(Times >=30)
		{
			Times =0;
			PCF8563_Read(&RTC_Time);										//RTC��ȡ
			CalculateProvideTimeServer();									//��ůʱ�� �Լ���ů���ļ���
			UpDateSysDevStatusErr();										//ϵͳ�豸ͨ��״̬����
			
			if(CalculateProvideTimeCtrler.PassData >3600l*24*60)		    //��ůʱ�����2���º���й�ů�������е���
			{
				SysPara.StartTime.Year +=1;
				SysPara.FinalTime.Year +=1;
				SysPara_Update();
			}
			/* ��ů����Χ�ڵ��Զ�����*/
			if(
				((CalculateProvideTimeCtrler.PassData <=3600l*24*30)&&( CalculateProvideTimeCtrler.PassData >=-3600l*24*30))	//��ů������Чʱ����
			)
			{
				CalculateProvideTimeCtrler.LoopWorkFlg =ENABLE;		
			}
			else
			{
				CalculateProvideTimeCtrler.LoopWorkFlg =DISABLE;
			}
        }
        else
		{
			RTC_TimeTicks +=1;
		}

		/*ϵͳ��ʱ��λ����*/
        if( SysOnbootFlag ==1)
        {
        	
			dbg_printf(DEBUG_INFO,"��������ʱ %lu...",RemoRebotCont-(SystemTick_ms -SysOnbootdelay)/1000);				
			if( SystemTick_ms -SysOnbootdelay >RemoRebotCont*1000ul)		//10�����ʱ
			{
				SysOnbootFlag =0x00;
				NVIC_SystemReset();
			}
        }
        
        AlarmClk_ExecutServer();	//����������ִ�з�����
        
		/*ÿ10�����һ��ϵͳ�豸ͨ��״̬���*/
		if(Times1 >=10)			
        {
        	Times1 =0;
			SysStatus.Dev_ComStatus = GetDev_ComStatus();
            //dbg_printf(DEBUG_INFO,"����״̬ = %d\r\n",SysStatus.Dev_ComStatus);
			if(SysStatus.Dev_ComStatus == HAL_OK)
			{
				LED_Alarm_OFF;
			}
			else
			{
				LED_Alarm_ON;
			}
        }

        
        /*ÿ5�����һ���豸����״̬���*/
        if(Times2 >=5)			
		{
			Times2 =0;
            //dbg_printf(DEBUG_INFO,"����״̬ = %d\r\n", SysStatus.Syspara);
			if(SysStatus.Syspara == HAL_OK)
			{
				LED_Fault_OFF;
			}
			else
			{
				LED_Fault_ON;
			}
		}
		
		
        osDelay(1000);			//ע�����ʱʱ�䲻Ҫ�����޸� �������漰 RTC_TimeTicks�ĸ���
    }
}





/* 
	Task02_F function
	�������
*/
void Task02_F(void const * argument)
{

	INT32U Times =0;
	INT32U TimeLed =0;

	
	createIWDG( &Iwdg_T2, 20);			 //������Ź�����
    while(1)
    {
		feedIWDG(Iwdg_T2);
    	Times++;
    	if( Times>=4)
    	{
    		Times =0;
	    	LED_COM1_OFF;
	    	LED_COM2_OFF;
	    	LED_COM3_OFF;
    	}


		TimeLed +=1;
		if( TimeLed >=60)
		{

			TimeLed =0;
			PulseLeaguer_SET(LedBR_Ctrler, 4, 10, 8, 16, 0, 0); 	//�������幤��ָʾ�� ����
		}
    	osDelay(50);
	
    }
}





/* Task03_F function 
    ����ɨ�������
*/
void Task03_F(void const * argument)
{

	BaseType_t Err;
	KEY_OUT_Stru value;
	KEY_OUT_Stru pi;
	IndepKEYFunction_Init();											//�����������ܳ�ʼ��
	KeyboardApp_Init();												    //����Ӧ�ó�ʼ��  IndepKEYFunction_Init ��ʼ�����ҽӺ����ٴγ�ʼ��

	osStatus TimerErr;
	TimerErr =TimerErr;

    /* Create the timer(s) */
    /* definition and creation of Timer01 */
    osTimerDef(Timer01, Timer01Callback);								//����Ӧ���ڰ���ɨ��Ķ�ʱ��
    Timer01Handle = osTimerCreate(osTimer(Timer01), osTimerPeriodic, NULL);
    TimerErr =osTimerStart (Timer01Handle , 5 );	                    //��ʱ��ɨ����Ϊ5����/Ticks

	Err =Err;
    while(1)
    {
        Err =xQueueReceive(KEY_OUT_Msg, &pi, portMAX_DELAY);
        if(Err ==pdTRUE)
        {
			value =pi;
			PulseLeaguer_SET(Beep_Ctrler, 1, 10, 5, 10, 0, 0); 	        //����ָ��	��������  ɨ����(tick*X) ���ؿ��   ����	  ���ڼ�����  ��ǰ״̬
			LCD_light_Ct =SystemTick_ms;					            //�а�������ʱˢ�±��������
			
			Keyvalue.value =value.Button_Num;
			Keyvalue.resp =1;
			Menu_KeyManager();
			xSemaphoreGive(Display_Semaphore);
        }
        
        osDelay(100);
    }
}







/* Task04_F function */
void Task04_F(void const * argument)
{

	LCD_IOInit();										        //LCD����ܽų�ʼ��
	LCD_REST();										            //Һ����λ
	
	Lcd_Init();											        //Һ��������ʼ��
	Clear_VisionBUF();									        //�����ʾ������
	Refresh_Screen();									        //��Ļˢ��
	BaseType_t Err=pdTRUE;
	
	if(Display_Semaphore !=NULL)
	{
		xSemaphoreGive(Display_Semaphore);
	}

	
	GetbuildMeterMessage();	 							        //��ȡ������Ϣ
    while(1)
    {
		Err =xSemaphoreTake(Display_Semaphore,portMAX_DELAY);	//�ȴ���Ļˢ���ź���
		if(Err ==pdTRUE)
		{
			DisplayManager();
			Refresh_Screen();
		}
    	osDelay(50);
	
    }
}






/* Task05_F function 
�첽����ͨ�Ž��շ���

*/
void Task05_F(void const * argument)
{

	createIWDG( &Iwdg_T5, 25);			 //������Ź�����
	while(1)
	{
		feedIWDG(Iwdg_T5);
		UART_RBC_RXServer();
		osDelay(50);
	}
}

/* Task06_F function
�첽����ͨ�ŷ��ͷ���
*/
void Task06_F(void const * argument)
{
	createIWDG( &Iwdg_T6, 25);			 //������Ź�����
	while(1)
	{
		feedIWDG(Iwdg_T6);
		UART_RBC_TXServer();		    //�첽����ͨ�ŷ��ͷ���
		osDelay(200);
	}
}


/* Task07_F function
�첽����ͨ�ŷ�����  ���ɼ��� ���ݴ����


Э����
*/
void Task07_F(void const * argument)
{

	UART_TO_FY1000_QueueSend_Stru SendBuffer;
	if(FY_1000Send_Code_QInput(&SendBuffer,0XFE)==pdTRUE)
	{			
		dbg_printf(DEBUG_INFO,"��վ����ע������....");
	}
	else
	{
		dbg_printf(DEBUG_INFO,"��վ����ע������....");
	}
	createIWDG( &Iwdg_T7, 30);			                //������Ź�����


    while(1)
    {
		feedIWDG(Iwdg_T7);
		FY188_Pack_TxServer_S(UART_TO_FY188_CCB_S);		//FY-188�������

		FY2000_Pack_TxServer_S(UART_TO_FY2000_CCB_S);	//FY-2000�������
		FY1000_Pack_TxServer_S(UART_TO_FY1000_CCB_S);	//FY-1000�������

#ifdef Meter_H_ENABLE
		HZCRL_Pack_TxServer_S(UART_TO_HZCRL_CCB_S);		//����188�������
#endif

#ifdef  Meter_XY_ENABLE	        
		XY188_Pack_TxServer_S(UART_TO_XY188_CCB_S);		//XY-188�������
#endif

#ifdef  Meter_HT2X_ENABLE	        
        HT2X188_Pack_TxServer_S(UART_TO_HT2X188_CCB_S); //HT2X-188�������
#endif

#ifdef  Meter_BRC_ENABLE	        
        BRC188_Pack_TxServer_S(UART_TO_BRC188_CCB_S);   //BRC-188�������
#endif

#ifdef  Meter_DDF2_ENABLE	        
        DDF2_Pack_TxServer_S(UART_TO_DDF2_CCB_S);       //DDF2�������
#endif

#ifdef  Valve_NWK_ENABLE	        
        NWK_Pack_TxServer_S(UART_TO_NWK_CCB_S);         //NWK�������
        //dbg_printf(DEBUG_DEBUG,"--NWK--���");
#endif
    	osDelay(500);
    }
}






/* Task08_F function
Client ͨ��ͨ��1 ���ͷ���  ���ݷ��ͷ������񣨲ɼ���-->�ӻ��豸  �ɼ�������������豸��

*/


void Task08_F(void const * argument)
{
	BaseType_t Err;
	Err =Err;
	UBaseType_t Num =0;
	
	ClientReadCtrler.Num =0;
	SysDEV_Type DeviceType;
	ClientCH1_Queue_Stru DevQueue;
	UART_TO_FY188_QueueSend_Stru		FY188_QueueSend;        //����������ͨ��Э�鷢�Ͷ��л�����
	UART_TO_FY2000_QueueSend_Stru	    FY2000_QueueSend;       //����ͨ�Ϸ�ͨ��Э��Э�鷢�Ͷ��л�����

	
    
#ifdef Meter_H_ENABLE
	UART_TO_HZCRL_QueueSend_Stru		HZCRL188_QueueSend;     //��������188ͨ��Э��ͨ��Э��Э�鷢�Ͷ��л�����
#endif
    
#ifdef  Meter_XY_ENABLE	 
	UART_TO_XY188_QueueSend_Stru		XY188_QueueSend;        //������Դ������ͨ��Э�鷢�Ͷ��л�����
#endif    

#ifdef  Meter_HT2X_ENABLE	 
	UART_TO_HT2X188_QueueSend_Stru		HT2X188_QueueSend;      //������ͨHT2X������ͨ��Э�鷢�Ͷ��л�����
#endif  	

#ifdef  Meter_BRC_ENABLE	 
    UART_TO_BRC188_QueueSend_Stru       BRC188_QueueSend;       //������������ BRC ������ͨ��Э�鷢�Ͷ��л�����
#endif 

#ifdef  Meter_DDF2_ENABLE	 
        UART_TO_DDF2_QueueSend_Stru     DDF2_QueueSend;         //��ͨͨ�Ϸ�ͨ��Э�鷢�Ͷ��л�����
#endif 

#ifdef  Valve_NWK_ENABLE	 
        UART_TO_NWK_QueueSend_Stru      NWK_QueueSend;          //������modbusЭ�鷢�Ͷ��л�����
#endif 

	if(SysPara.LoopSpace <1000)
	{
		SysPara.LoopSpace =3000;
	}
	ClientCH1Ctrler.CreatFlag =HAL_OK;
	SysStatus.ShareFlag =HAL_ERROR;			//��̯��־��λ

	createIWDG( &Iwdg_T8, 60);			    //������Ź�����

#if 0

    for(int i =8;i< 40;i++)
    {

    	SysDeviceList.Device[i].Type =Meter_HT3X;
    	SysDeviceList.Device[i].ID =0x05011768+i ;
    	SysDeviceList.Device[i].COM_Type =0x15 ;
    	SysDeviceList.Device[i].Num =i;
    	SysDeviceList.Device[i].UserNum =3;
	}
	
#endif
    while(1)
    {
		feedIWDG(Iwdg_T8);
    	if(ClientCH1Ctrler.Busy ==HAL_OK)                               //���߿��� 
    	{
			Num = uxQueueSpacesAvailable(ClientCH1_Msg);                //�õ�����ʣ���С
			if( (Num ==ClientCH1_Q_NUM)&&(SystemTick_ms -ClientReadCtrler.LoopSpace >SysPara.LoopSpace) )   //����û�ж���Э����Ҫ����  ͬʱ���ѭ�����ռ��������  ��ʱ���Դ����Զ������豸����
			{
				ClientCH1_QueueIN.Device=SysDeviceList.Device[ClientReadCtrler.Num];						//�����豸����
				
				DeviceType =ClientCH1_QueueIN.Device.Type;		            								//��ȡ�豸����

				
				ClientReadCtrler.Num +=1;
				if( ClientReadCtrler.Num >=MAXDevice_Num)               //ѭ������
				{
					ClientReadCtrler.Num =0;
				}

				
				if( CalculateProvideTimeCtrler.LoopWorkFlg ==ENABLE)    //�Զ��ֳ�����Ч
				{
					SysStatus.LoopCtrler +=1;
					if(SysStatus.LoopCtrler >=MAXDevice_Num)
					{
						SysStatus.ShareFlag =HAL_OK;
					}
					switch(DeviceType)      //ѡ���豸����
					{
						case Meter_B :      //��ھ������������� FY-188
						{
						    ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                  //��ȡ�豸���
							ClientCH1_QueueIN.UaComFlg =0;										//Э�鷵�� ��־��λ
							ClientCH1_QueueIN.Uapack=0;
							
							ClientCH1_QueueIN.SignleCom =SET;									//�ظ�����
							Err = FY_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);             //�������	
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"FY_188Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"FY_188Send_Code_QInput    ERR ");
							}
							
						}break;
						


						case Meter_U ://�û������������� FY-188
						{
						    ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;					//��ȡ�豸���
							ClientCH1_QueueIN.UaComFlg =0;                                      //Э�鷵�� ��־��λ
							ClientCH1_QueueIN.Uapack=0;
							ClientCH1_QueueIN.SignleCom =SET;									//�ظ�����
							Err = FY_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);				//�������	
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"FY_188Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"FY_188Send_Code_QInput    ERR ");
							}							
						}break;

						case Valve_U ://����ͨ�Ͽ�����
						{
							INT16U UserNum =0;
							INT16U DevNum =0;
							
							UserNum =ClientCH1_QueueIN.Device.UserNum;                                                          //��ȡ�û����
							DevNum =ClientCH1_QueueIN.Device.Num;
							ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                                  //�����豸����
							ClientCH1_QueueIN.UaComFlg =0;                                                                      //Э�鷵�� ��־��λ
							ClientCH1_QueueIN.Uapack=0;
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Head.DESN=ClientCH1_QueueIN.Device.Num;				//����DESN
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LoopTime=CalculateProvideTimeCtrler.ProvideTime;		//���ڹ�ůʱ��
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Apportion_Energy=UserData[UserNum].Apportion_Energy;	//������������/��������
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Remain_Heat=UserData[UserNum].Remain_Heat;			//����ʣ������
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Total_Heat=UserData[UserNum].Total_Heat;				//�����û���������
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.ControlType=SysDevData[DevNum].Device3.ControlType;   //�����������
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.ForceCtrlFlg=SysDevData[DevNum].Device3.ForceCtrlFlg; //����ǿ�ƿ��Ʊ�־
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Set_TCtrlFg=SysDevData[DevNum].Device3.Set_TCtrlFg;   //ϵͳ�趨�¶ȱ�־
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Set_Temp=SysDevData[DevNum].Device3.Set_Temp;			//ϵͳ�趨�¶�

							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LimtTE_Flag=SysDevData[DevNum].Device3.LimtTE_Flag;   //ϵͳ�����¶ȱ�־
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LimtTE_Value=SysDevData[DevNum].Device3.LimtTE_Value; //ϵͳ���������¶�
							ClientCH1_QueueIN.SignleCom =SET;
				 			Err =FY_2000Send_Code_QInput(&ClientCH1_QueueIN,59);										        //�������
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"FY_2000Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"FY_2000Send_Code_QInput    ERR ");
							}
						}break;

						case Valve_UH ://����ͨ�Ͽ����� ��ˮ����
						{
							INT16U UserNum =0;
							INT16U DevNum =0;
							
							UserNum =ClientCH1_QueueIN.Device.UserNum;												                //��ȡ�û����
							DevNum =ClientCH1_QueueIN.Device.Num;
							ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;											            //�����豸����
							ClientCH1_QueueIN.UaComFlg =0;														                    //Э�鷵�� ��־��λ
							ClientCH1_QueueIN.Uapack=0;
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Head.DESN =DevNum;								        //����DESN
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LoopTime =CalculateProvideTimeCtrler.ProvideTime;         //���ڹ�ůʱ��
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Apportion_Energy =UserData[UserNum].Apportion_Energy;		//������������/��������
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Remain_Heat =UserData[UserNum].Remain_Heat;			    //����ʣ������
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Total_Heat =UserData[UserNum].Total_Heat;				    //����������
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.ControlType =SysDevData[DevNum].Device4.ControlType;		//�����������
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.ForceCtrlFlg =SysDevData[DevNum].Device4.ForceCtrlFlg;    //����ǿ�ƿ��Ʊ�־
							
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Set_TCtrlFg =0;		//ϵͳ�趨�¶ȱ�־
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.Set_Temp =0;		    //ϵͳ�趨�¶�

							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LimtTE_Flag =0;		//ϵͳ�����¶ȱ�־
							ClientCH1_QueueIN.SendData.FY2000Data.Pack_59.LimtTE_Value =0;		//ϵͳ���������¶�
							ClientCH1_QueueIN.SignleCom =SET;
				 			Err =FY_2000Send_Code_QInput(&ClientCH1_QueueIN,59);		 	    //�������
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"FY_2000Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"FY_2000Send_Code_QInput    ERR ");
							}
						}break;

#ifdef Meter_H_ENABLE
						case Meter_H ://���д�ھ������������� CJ-T188
						{
						    ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                  //��ȡ�豸���
							ClientCH1_QueueIN.UaComFlg =0;                                      //Э�鷵�� ��־��λ
							ClientCH1_QueueIN.Uapack=0;
							ClientCH1_QueueIN.SignleCom =SET;									//�ظ�����
							Err = HZCRL_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);			//�������	
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"HZCRL_188Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"HZCRL_188Send_Code_QInput    ERR ");
							}
						}break;					
#endif


#ifdef Meter_XY_ENABLE
						case Meter_XY ://��Դ������������ XY-188
						{
						    ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;									//��ȡ�豸���
							ClientCH1_QueueIN.UaComFlg =0;													    //Э�鷵�� ��־��λ
							ClientCH1_QueueIN.Uapack=0;
							ClientCH1_QueueIN.SignleCom =SET;													//�ظ�����
							Err = XY_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);								//�������	
							if(Err ==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"XY_188Send_Code_QInput    OK ");
							}
							else
							{
								dbg_printf(DEBUG_DEBUG,"XY_188Send_Code_QInput    ERR ");
							}							
						}break;
#endif

#ifdef Meter_HT2X_ENABLE
                        case Meter_HT2X ://��ͨ������������ HT2X-188
                        {
                            ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                  //��ȡ�豸���
                            ClientCH1_QueueIN.UaComFlg =0;                                                      //Э�鷵�� ��־��λ
                            ClientCH1_QueueIN.Uapack=0;
                            ClientCH1_QueueIN.SignleCom =SET;                                                   //�ظ�����
                            Err = HT2X_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);                           //�������  
                            if(Err ==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"HT2X_188Send_Code_QInput    OK ");
                            }
                            else
                            {
                                dbg_printf(DEBUG_DEBUG,"HT2X_188Send_Code_QInput    ERR ");
                            }                           
                        }break;
                        
                        case Meter_HT3X ://��ͨ������������ HT2X-188
                        {
                            ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                  //��ȡ�豸���
                            ClientCH1_QueueIN.UaComFlg =0;                                                      //Э�鷵�� ��־��λ
                            ClientCH1_QueueIN.Uapack=0;
                            ClientCH1_QueueIN.SignleCom =SET;                                                   //�ظ�����
                            Err = HT2X_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);                           //�������  
                            if(Err ==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"HT3X_188Send_Code_QInput    OK ");
                            }
                            else
                            {
                                dbg_printf(DEBUG_DEBUG,"HT3X_188Send_Code_QInput    ERR ");
                            }                           
                        }break;
#endif

#ifdef Meter_BRC_ENABLE
                        case Meter_BRC ://��ͨ������������ BRC-188
                        {
                            ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                  //��ȡ�豸���
                            ClientCH1_QueueIN.UaComFlg =0;                                                      //Э�鷵�� ��־��λ
                            ClientCH1_QueueIN.Uapack=0;
                            ClientCH1_QueueIN.SignleCom =SET;                                                   //�ظ�����
                            Err = BRC_188Send_Code_QInput(&ClientCH1_QueueIN, 0X01);                            //�������  
                            if(Err ==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"BRC_188Send_Code_QInput    OK ");
                            }
                            else
                            {
                                dbg_printf(DEBUG_DEBUG,"BRC_188Send_Code_QInput    ERR ");
                            }                           
                        }break;
#endif

#ifdef Meter_DDF2_ENABLE
                        case Meter_DDF2 ://��ͨͨ�Ͽ�����DDF2
                        {
                            ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                  //��ȡ�豸���
                            ClientCH1_QueueIN.UaComFlg =0;                                                      //Э�鷵�� ��־��λ
                            ClientCH1_QueueIN.Uapack=0;
                            ClientCH1_QueueIN.SignleCom =SET;                                                   //�ظ�����
                            Err = DDF2_Send_Code_QInput(&ClientCH1_QueueIN, 0X01);                              //�������  
                            if(Err ==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"DDF2_Send_Code_QInput    OK ");
                            }
                            else
                            {
                                dbg_printf(DEBUG_DEBUG,"DDF2_Send_Code_QInput    ERR ");
                            }                           
                        }break;
#endif

#ifdef Valve_NWK_ENABLE
                        case Valve_NWK ://NWK������¥����Ԫ���ڷ�modbusЭ��
                        {
                            ClientCH1_QueueIN.Device=ClientCH1_QueueIN.Device;                                  //��ȡ�豸���
                            ClientCH1_QueueIN.UaComFlg =0;                                                      //Э�鷵�� ��־��λ
                            ClientCH1_QueueIN.Uapack=0;
                            ClientCH1_QueueIN.SignleCom =SET;                                                   //�ظ�����
                            Err = NWK_Send_Code_QInput(&ClientCH1_QueueIN, 0X03);                               //�������  
                            if(Err ==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG, "NWK_Send_Code_QInput    OK ");
                            }
                            else
                            {
                                dbg_printf(DEBUG_DEBUG, "NWK_Send_Code_QInput    ERR ");
                            }                           
                        }break;
#endif

						default: break;
					}
				}
			}
			else    //���ն˳���Э�鴥��  ��Ҫ������Э����зַ�
			{
                Err =xQueueReceive(ClientCH1_Msg, &ClientCH1_QueueBFP, 20);
                if(Err ==pdTRUE)
                {   
                	INT16U DevNum =0;
					INT8U DevType =0;
					
					ClientCH1_QueueBF =*ClientCH1_QueueBFP;
					
                    ClientCH1Ctrler.Device =ClientCH1_QueueBF.Device;       		    //�����ƽ�   �����������ƽ���ͨ��������  
					ClientCH1Ctrler.SignleCom =ClientCH1_QueueBF.SignleCom;			    //�����ظ����մ�������
					ClientCH1Ctrler.UaComFlg =ClientCH1_QueueBF.UaComFlg;			    //����Э���־
					ClientCH1Ctrler.Uapack=ClientCH1_QueueBF.Uapack;
					
					ClientCH1Ctrler.PackCreatFlag=ClientCH1_QueueBF.PackCreatFlag;		//����Э�鴥�����Ʊ�־
					ClientCH1Ctrler.PackINPort=ClientCH1_QueueBF.PackINPort;			//����Э��������
					ClientCH1Ctrler.SendData=ClientCH1_QueueBF.SendData;    			//����Э����Ч������  
					
					
					DevType	=ClientCH1Ctrler.Device.Type;				
                    DevNum =ClientCH1Ctrler.Device.Num;
                    
                    if(ClientCH1Ctrler.SignleCom ==SET)
                    {
                    	switch(DevType)	//�Գ����豸�����ͨ��״̬�ۼ�
	                    {
							case Meter_B:	//FY-188��ھ���
							{
								SysDevStatus[DevNum].Device1.ComTolNum +=1;

							}break;
							
							case Meter_U:   //FY-188С�ھ���
							{
								SysDevStatus[DevNum].Device2.ComTolNum +=1;

							}break;		

							case Valve_U:	//FY-2100ͨ�Ͽ����� 
							{
								SysDevStatus[DevNum].Device3.ComTolNum +=1;

							}break;	
							case Valve_UH:
							{		
								SysDevStatus[DevNum].Device4.ComTolNum +=1;
						
							}break;
#ifdef Meter_H_ENABLE
							case Meter_H:   //���� CJ-T188 ��ھ���
							{
								SysDevStatus[DevNum].Device5.ComTolNum +=1;

							}break;	
#endif

                            
#ifdef  Meter_XY_ENABLE
							case Meter_XY: //��Դ XY-188С�ھ���
							{
								SysDevStatus[DevNum].Device6.ComTolNum +=1;

							}break;	
#endif


#ifdef  Meter_HT2X_ENABLE
                            case Meter_HT2X: //��ͨ HT2X-188С�ھ���
                            {
                                SysDevStatus[DevNum].Device7.ComTolNum +=1;

                            }break; 
                            
                            case Meter_HT3X: //��ͨ HT2X-188С�ھ���
                            {
                                SysDevStatus[DevNum].Device10.ComTolNum +=1;

                            }break; 
#endif


#ifdef  Meter_BRC_ENABLE
                            case Meter_BRC: //�������� BRC-188С�ھ���
                            {
                                SysDevStatus[DevNum].Device8.ComTolNum +=1;

                            }break; 
#endif

#ifdef  Meter_DDF2_ENABLE
                            case Meter_DDF2: ////��ͨ DDF2ͨ�Ͽ�����
                            {
                                SysDevStatus[DevNum].Device9.ComTolNum +=1;

                            }break; 
#endif		
                            
#ifdef  Valve_NWK_ENABLE
                            case Valve_NWK: ////������NWK¥�����ڷ�modbusЭ��
                            {
                                SysDevStatus[DevNum].Device11.ComTolNum +=1;

                            }break; 
#endif	
							default :break;
	                    }
                    }
                    
					ClientCH1Ctrler.Busy =HAL_BUSY;
                    ClientCH1Ctrler.Repeat =0;
                 
                }
			}
    	}
    	
    	if(( ClientCH1Ctrler.Busy ==HAL_BUSY)&&(ClientCH1Ctrler.CreatFlag ==HAL_OK))   //���ߴ���ռ��״̬ ����Բ����лظ����ն��豸�����ظ�����
    	{
    		DevQueue.Device.Type =ClientCH1Ctrler.Device.Type;
            switch(DevQueue.Device.Type)
            {
            	case Meter_B ://��ھ�������������
				{
					
					FY188_QueueSend.ID =ClientCH1Ctrler.Device.ID;				    //�����豸���ID
					FY188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;	//����Э�鴴��������־
					FY188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;		    //����Э��������
					FY188_QueueSend.SendData =ClientCH1Ctrler.SendData;			    //����Э������
					
					Err =UART_TO_FY188_CCB_QueueSend(&FY188_QueueSend);		        //������Ϣ
					if( Err ==pdTRUE)
					{
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_FY188_CCB_QueueSend    OK ");
					}
				}break;

            	case Meter_U ://���ó�����������
				{
				
					FY188_QueueSend.ID =ClientCH1Ctrler.Device.ID;				    //�����豸���ID
					FY188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;	//����Э�鴴��������־
					FY188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;		    //����Э��������
					FY188_QueueSend.SendData =ClientCH1Ctrler.SendData;			    //����Э������

					Err =UART_TO_FY188_CCB_QueueSend(&FY188_QueueSend);		        //������Ϣ
					if( Err ==pdTRUE)
					{
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_FY188_CCB_QueueSend    OK ");
					}
					
				}break;	
				

            	case Valve_U ://����ͨ�Ͽ����� ��׼��
				{

					FY2000_QueueSend.ID =ClientCH1Ctrler.Device.ID;				    //�����豸���ID
					FY2000_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;	//����Э�鴴��������־
					FY2000_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;		//����Э��������
				
					FY2000_QueueSend.SendData =ClientCH1Ctrler.SendData;			//����Э������

					Err =UART_TO_FY2000_CCB_QueueSend(&FY2000_QueueSend);		    //������Ϣ
					if( Err ==pdTRUE)
					{
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_FY2000_CCB_QueueSend    OK ");
					}
				}break;	


				

            	case Valve_UH ://����ͨ�Ͽ����� ��ˮ��
				{

					FY2000_QueueSend.ID =ClientCH1Ctrler.Device.ID;				    //�����豸���ID
					FY2000_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;	//����Э�鴴��������־
					FY2000_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;		//����Э��������
					FY2000_QueueSend.SendData =ClientCH1Ctrler.SendData;			//����Э������

					Err =UART_TO_FY2000_CCB_QueueSend(&FY2000_QueueSend);		    //������Ϣ
					if( Err ==pdTRUE)
					{
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_FY2000_CCB_QueueSend    OK ");
					}
				}break;	

				
#ifdef Meter_H_ENABLE
                case Meter_H ://���г����������� ��ھ�
                {
                
                    HZCRL188_QueueSend.ID =ClientCH1Ctrler.Device.ID;                       //�����豸���ID
                    HZCRL188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;        //����Э�鴴��������־
                    HZCRL188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;              //����Э��������
                    HZCRL188_QueueSend.SendData =ClientCH1Ctrler.SendData;                  //����Э������

                    Err =UART_TO_HZCRL_CCB_QueueSend(&HZCRL188_QueueSend);                  //������Ϣ
                    if( Err ==pdTRUE)
                    {
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_HZCRL_CCB_QueueSend    OK ");
                    }
                    
                }break;     
#endif




#ifdef  Meter_XY_ENABLE                
            	case Meter_XY ://��Դ������������
				{
				
					XY188_QueueSend.ID =ClientCH1Ctrler.Device.ID;				    //�����豸���ID
					XY188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;	//����Э�鴴��������־
					XY188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;		    //����Э��������
					XY188_QueueSend.SendData =ClientCH1Ctrler.SendData;			    //����Э������

					Err =UART_TO_XY188_CCB_QueueSend(&XY188_QueueSend);		        //������Ϣ
					if( Err ==pdTRUE)
					{
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_XY188_CCB_QueueSend    OK ");
					}
					
				}break;
#endif				

#ifdef  Meter_HT2X_ENABLE                
                case Meter_HT2X ://��Դ������������
                case Meter_HT3X ://��Դ������������
                {
                
                    HT2X188_QueueSend.ID =ClientCH1Ctrler.Device.ID;                    //�����豸���ID
                    HT2X188_QueueSend.Type =ClientCH1Ctrler.Device.Type;                //�����豸���� ���ͺű��Ӧ 
                    HT2X188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;     //����Э�鴴��������־
                    HT2X188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;           //����Э��������
                    HT2X188_QueueSend.SendData =ClientCH1Ctrler.SendData;               //����Э������

                    Err =UART_TO_HT2X188_CCB_QueueSend(&HT2X188_QueueSend);             //������Ϣ
                    if( Err ==pdTRUE)
                    {
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        if(DevQueue.Device.Type == Meter_HT2X )
                        {
                            dbg_printf(DEBUG_DEBUG,"UART_TO_HT2X188_CCB_QueueSend    OK ");
                        }
                        else if(DevQueue.Device.Type == Meter_HT3X )
                        {
                            dbg_printf(DEBUG_DEBUG,"UART_TO_HT3X188_CCB_QueueSend    OK ");
                        }
                        
                    }
                    
                }break;
#endif	

#ifdef  Meter_BRC_ENABLE                
                case Meter_BRC ://��Դ������������
                {
                
                    BRC188_QueueSend.ID =ClientCH1Ctrler.Device.ID;                  //�����豸���ID
                    BRC188_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;   //����Э�鴴��������־
                    BRC188_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;         //����Э��������
                    BRC188_QueueSend.SendData =ClientCH1Ctrler.SendData;             //����Э������

                    Err =UART_TO_BRC188_CCB_QueueSend(&BRC188_QueueSend);            //������Ϣ
                    if( Err ==pdTRUE)
                    {
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_BRC188_CCB_QueueSend    OK ");
                    }
                    
                }break;
#endif	

#ifdef  Meter_DDF2_ENABLE                
                case Meter_DDF2 ://��ͨͨ�Ͽ�����DDF2
                {
                
                    DDF2_QueueSend.ID =ClientCH1Ctrler.Device.ID;                  //�����豸���ID
                    DDF2_QueueSend.COM_Type =ClientCH1Ctrler.Device.COM_Type;            
                    DDF2_QueueSend.PackCreatFlag =ClientCH1Ctrler.PackCreatFlag;   //����Э�鴴��������־
                    DDF2_QueueSend.PackINPort =ClientCH1Ctrler.PackINPort;         //����Э��������
                    DDF2_QueueSend.SendData =ClientCH1Ctrler.SendData;             //����Э������

                    Err =UART_TO_DDF2_CCB_QueueSend(&DDF2_QueueSend);              //������Ϣ
                    if( Err ==pdTRUE)
                    {
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_DDF2_CCB_QueueSend    OK ");
                    }
                    
                }break;
#endif	

#ifdef  Valve_NWK_ENABLE                
                case Valve_NWK ://������NWK
                {
                
                    NWK_QueueSend.ID                = ClientCH1Ctrler.Device.ID;            //�����豸���ID
                    //NWK_QueueSend.COM_Type          = ClientCH1Ctrler.Device.COM_Type;            
                    NWK_QueueSend.PackCreatFlag     = ClientCH1Ctrler.PackCreatFlag;        //����Э�鴴��������־
                    NWK_QueueSend.PackINPort        = ClientCH1Ctrler.PackINPort;           //����Э��������
                    NWK_QueueSend.SendData          = ClientCH1Ctrler.SendData;             //����Э������

                    Err =UART_TO_NWK_CCB_QueueSend(&NWK_QueueSend);                         //������Ϣ
                    if( Err ==pdTRUE)
                    {
                        ClientCH1Ctrler.Repeat +=1;
                        ClientCH1Ctrler.RetFlag =HAL_BUSY;
                        ClientCH1Ctrler.Ticks =SystemTick_ms;
                        ClientCH1Ctrler.CreatFlag =HAL_BUSY;
                        dbg_printf(DEBUG_DEBUG,"UART_TO_NWK_CCB_QueueSend    OK ");
                    }
                    
                }break;
#endif	

				default :break;
            }
    	}
    	osDelay(200);
    }
}







/* Task09_F function
Client ͨ��ͨ��1 ���߿��Ʒ���     
*/
void Task09_F(void const * argument)
{
	BaseType_t err;
	err =err;

	if(( SysPara.ReadSpace<2000)||(SysPara.ReadSpace>1000*60*10))
	{
		SysPara.ReadSpace =3000;

	}
	createIWDG( &Iwdg_T9, 35);			 //������Ź�����

    while(1)
    {
		feedIWDG(Iwdg_T9);
    	if(ClientCH1Ctrler.Busy ==HAL_BUSY)		//ͨ��ռ��״̬���
    	{
    		if( SystemTick_ms -ClientCH1Ctrler.Ticks >SysPara.ReadSpace)
    		{
    			ClientCH1Ctrler.CreatFlag =HAL_OK;
    			if(ClientCH1Ctrler.SignleCom ==SET)	//��Ҫ�ظ�����
    			{
					if(ClientCH1Ctrler.RetFlag ==HAL_OK)
					{
						ClientCH1Ctrler.Busy =HAL_OK;
						ClientCH1Ctrler.CreatFlag =HAL_OK;
						ClientReadCtrler.LoopSpace =SystemTick_ms;
					}
					else if( ClientCH1Ctrler.Repeat >=ClientRepeatNum)	//����ʧ��
					{	
						UART_TO_FY1000_QueueSend_Stru SendBuffer_1000;
						INT16U DevNum =ClientCH1Ctrler.Device.Num;
						INT8U DevType =ClientCH1Ctrler.Device.Type;
						
						switch(DevType)
						{
							case Meter_B:
							{
								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//�Զ�����  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_B;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device1.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device1.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device1.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device1.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
                                       dbg_printf(DEBUG_WARNING,"�Զ� ����ʧ�ܣ�����:%d ���:%08lX...¥��������",DevType, ClientCH1Ctrler.Device.ID);
                                        
									}break;
									case 0XAAAA: //Զ�̳���
									{
										SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_B;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device1.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device1.ComTolNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device1.ComSucNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device1.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
                                        dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X01������:%d ���:%08lX...¥��������", DevType, ClientCH1Ctrler.Device.ID);
                                        
									}break;
									default:break;
								}
								
							}break;
							
							case Meter_U:
							{
								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//�Զ�����  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_U;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device2.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device2.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device2.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device2.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
										dbg_printf(DEBUG_WARNING,"�Զ� ����ʧ�ܣ�����:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									
									case 0XAAAA: //Զ�̳���
									{
										SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_U;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device2.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device2.ComTolNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device2.ComSucNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device2.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
										dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X01������:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);

									}break;
									default:break;
								}	
							}break;
							
							case Valve_U:
							{
								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//�Զ�����  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Valve_U;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device3.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device3.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device3.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device3.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
										dbg_printf(DEBUG_WARNING,"�Զ� ����ʧ�ܣ�����:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									
									case 0XAAAA: //Զ�̳���/����
									{
										switch(ClientCH1Ctrler.Uapack)
										{
											case 0X01: //�ն����ݳ���
											{
												SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Valve_U;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
												
												SysDevStatus[DevNum].Device3.ComFauNum +=1;
												SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device3.ComTolNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device3.ComSucNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device3.ComFauNum;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
                                                dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X01������:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                        DevType, ClientCH1Ctrler.Device.ID,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);

											}break;
											case 0X0D://���Ŷ�������
											{
												SendBuffer_1000.SendData.Pack_0X0E.DevType =Valve_U;
												SendBuffer_1000.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X0E.State =0X03;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X0E);
												dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X0D������:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                        DevType, ClientCH1Ctrler.Device.ID,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                        SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
											}break;
										}
									}break;
										
								}
							}break;	
							
							case Valve_UH:
							{

								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//�Զ�����  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Valve_UH;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device4.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device4.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device4.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device4.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
										dbg_printf(DEBUG_WARNING,"�Զ� ����ʧ�ܣ�����:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									
									case 0XAAAA: //Զ�̳���/����
									{
										switch(ClientCH1Ctrler.Uapack)
										{
											case 0X01: //�ն����ݳ���
											{
												SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Valve_UH;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
												
												SysDevStatus[DevNum].Device4.ComFauNum +=1;
												SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device4.ComTolNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device4.ComSucNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device4.ComFauNum;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
												dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X01������:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                    DevType, ClientCH1Ctrler.Device.ID,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);

											}break;
											case 0X0D://���Ŷ�������
											{
												SendBuffer_1000.SendData.Pack_0X0E.DevType =Valve_UH;
												SendBuffer_1000.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X0E.State =0X03;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X0E);												
												dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X0D������:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                    DevType, ClientCH1Ctrler.Device.ID,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                    SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
												
											}break;
										}
									}break;	
								}
							}break;	

							
#ifdef Meter_H_ENABLE
							case Meter_H:
							{
								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//�Զ�����  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_H;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device5.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device5.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device5.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device5.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);										
                                        dbg_printf(DEBUG_WARNING,"�Զ� ����ʧ�ܣ�����:%d ���:%08lX...¥��������",DevType, ClientCH1Ctrler.Device.ID);
                                        
									}break;
									
									case 0XAAAA: //Զ�̳���
									{
										SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_H;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device5.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device5.ComTolNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device5.ComSucNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device5.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);										
                                        dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X01������:%d ���:%08lX...¥��������", DevType, ClientCH1Ctrler.Device.ID);
                                        
									}break;
									default:break;
								}							
							}break;	
#endif



#ifdef  Meter_XY_ENABLE							
							case Meter_XY:
							{
								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//�Զ�����  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_XY;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device6.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device6.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device6.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device6.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);										
										dbg_printf(DEBUG_WARNING,"�Զ� ����ʧ�ܣ�����:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									
									case 0XAAAA: //Զ�̳���
									{
										SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_XY;
										SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device6.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device6.ComTolNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device6.ComSucNum;
										SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device6.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);										
										dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X01������:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                 DevType, ClientCH1Ctrler.Device.ID,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									default:break;
								}							
							}break;
#endif                        

                            
#ifdef  Meter_HT2X_ENABLE							
                            case Meter_HT2X:
                            case Meter_HT3X:
                            {
                                switch(ClientCH1Ctrler.UaComFlg)
                                {
                                    case 0: //�Զ�����  
                                    {
                                        SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =DevType;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
                                        
                                        SysDevStatus[DevNum].Device6.ComFauNum +=1;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device7.ComTolNum;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device7.ComSucNum;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device7.ComFauNum;
                                        FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);                                     
										dbg_printf(DEBUG_WARNING,"�Զ� ����ʧ�ܣ�����:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
                                    }break;
                                    
                                    case 0XAAAA: //Զ�̳���
                                    {
                                        SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
                                        SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =DevType;
                                        SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
                                        SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
                                        
                                        SysDevStatus[DevNum].Device6.ComFauNum +=1;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device7.ComTolNum;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device7.ComSucNum;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device7.ComFauNum;
                                        FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);                                     
                                        dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X01������:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                 DevType, ClientCH1Ctrler.Device.ID,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                 SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
                                    }break;
                                    default:break;
                                }                           
                            }break;
#endif                        

                                                        
#ifdef  Meter_BRC_ENABLE							
                            case Meter_BRC:
                            {
                                switch(ClientCH1Ctrler.UaComFlg)
                                {
                                    case 0: //�Զ�����  
                                    {
                                        SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_BRC;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
                                        
                                        SysDevStatus[DevNum].Device8.ComFauNum +=1;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device8.ComTolNum;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device8.ComSucNum;
                                        SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device8.ComFauNum;
                                        FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);                                     
										dbg_printf(DEBUG_WARNING,"�Զ� ����ʧ�ܣ�����:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
                                    }break;
                                    
                                    case 0XAAAA: //Զ�̳���
                                    {
                                        SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
                                        SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_BRC;
                                        SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
                                        SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
                                        
                                        SysDevStatus[DevNum].Device8.ComFauNum +=1;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device8.ComTolNum;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device8.ComSucNum;
                                        SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device8.ComFauNum;
                                        FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);                                     
                                        dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X01������:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                             DevType, ClientCH1Ctrler.Device.ID,\
                                                             SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                             SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                             SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                             SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
                                    }break;
                                    default:break;
                                }                           
                            }break;
#endif       

#ifdef  Meter_DDF2_ENABLE

							case Meter_DDF2:
							{

								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//�Զ�����  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Meter_DDF2;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;
										
										SysDevStatus[DevNum].Device4.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device9.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device9.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device9.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
										dbg_printf(DEBUG_WARNING,"�Զ� ����ʧ�ܣ�����:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                DevType, ClientCH1Ctrler.Device.ID,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
									}break;
									
									case 0XAAAA: //Զ�̳���/����
									{
										switch(ClientCH1Ctrler.Uapack)
										{
											case 0X01: //�ն����ݳ���
											{
												SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Meter_DDF2;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
												
												SysDevStatus[DevNum].Device9.ComFauNum +=1;
												SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device9.ComTolNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device9.ComSucNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device9.ComFauNum;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
												dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X01������:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                     DevType, ClientCH1Ctrler.Device.ID,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);

											}break;
											case 0X0D://���Ŷ�������
											{
												SendBuffer_1000.SendData.Pack_0X0E.DevType =Meter_DDF2;
												SendBuffer_1000.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X0E.State =0X03;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X0E);												
												dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X0D������:%d ���:%08lX...λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                     DevType, ClientCH1Ctrler.Device.ID,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Buld,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Unit,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Floor,\
                                                                     SysUserList.User[DevNum-MAXBuldMeter_Num].Cell);
												
											}break;
										}
									}break;	
								}
							}break;	
#endif

#ifdef  Valve_NWK_ENABLE
							case Valve_NWK:
							{

								switch(ClientCH1Ctrler.UaComFlg)
								{
									case 0:	//�Զ�����  
									{
										SendBuffer_1000.SendData.Pack_0XB0_F.CtrlFlag=0XAA;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_Type =Valve_NWK;
										SendBuffer_1000.SendData.Pack_0XB0_F.Dev_ID =ClientCH1Ctrler.Device.ID;
										SendBuffer_1000.SendData.Pack_0XB0_F.BackFlag=COMBack_CE;//COMBack_CE = 0x03�� 0x02:���ճɹ���0x03:�豸ͨ���쳣
										
										SysDevStatus[DevNum].Device11.ComFauNum +=1;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComTolNum =SysDevStatus[DevNum].Device11.ComTolNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComSucNum =SysDevStatus[DevNum].Device11.ComSucNum;
										SendBuffer_1000.SendData.Pack_0XB0_F.ComFauNum =SysDevStatus[DevNum].Device11.ComFauNum;
										FY_1000Send_Code_QInput(&SendBuffer_1000,0XB0);
                                        dbg_printf(DEBUG_WARNING,"�Զ� ����ʧ�ܣ�����:%d ���:%08lX...¥����Ԫ���ڷ�",DevType, ClientCH1Ctrler.Device.ID);
                                        
									}break;
									
									case 0XAAAA: //Զ�̳���/����
									{
										switch(ClientCH1Ctrler.Uapack)
										{
											case 0X01: //�ն����ݳ���
											{
												SendBuffer_1000.SendData.Pack_0X02_F.CtrlFlag=0XAA;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_Type =Valve_NWK;
												SendBuffer_1000.SendData.Pack_0X02_F.Dev_ID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X02_F.BackFlag=COMBack_CE;
												
												SysDevStatus[DevNum].Device11.ComFauNum +=1;
												SendBuffer_1000.SendData.Pack_0X02_F.ComTolNum =SysDevStatus[DevNum].Device11.ComTolNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComSucNum =SysDevStatus[DevNum].Device11.ComSucNum;
												SendBuffer_1000.SendData.Pack_0X02_F.ComFauNum =SysDevStatus[DevNum].Device11.ComFauNum;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X02);
												dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X01������:%d ���:%08lX...¥����Ԫ���ڷ�", DevType, ClientCH1Ctrler.Device.ID);

											}break;
											case 0X0D://���Ŷ�������
											{
												SendBuffer_1000.SendData.Pack_0X0E.DevType =Valve_NWK;
												SendBuffer_1000.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
												SendBuffer_1000.SendData.Pack_0X0E.State =0X03;
												FY_1000Send_Code_QInput(&SendBuffer_1000,0X0E);												
												dbg_printf(DEBUG_WARNING,"Զ�� ����ʧ�� 0X0D������:%d ���:%08lX...¥����Ԫ���ڷ�", DevType, ClientCH1Ctrler.Device.ID);
												
											}break;
										}
									}break;	
								}
							}break;	
#endif

							default:break;

						}
						
						ClientCH1Ctrler.Busy =HAL_OK;
						ClientCH1Ctrler.CreatFlag =HAL_OK;
						ClientReadCtrler.LoopSpace =SystemTick_ms;
						
					}
					else
					{
						ClientCH1Ctrler.CreatFlag =HAL_OK;
					}
				}
				else		//����Ҫ�ظ����� �㲥����  �����ն������Ѿ�����
				{
				
					ClientCH1Ctrler.Busy =HAL_OK;
					ClientCH1Ctrler.CreatFlag =HAL_OK;
					ClientReadCtrler.LoopSpace =SystemTick_ms;
				}
    		}
    	}
    	osDelay(200);
    }
}









/* Task10_F function
Client ͨ��ͨ��1 �豸�㲥��ʱ��������
*/
void Task10_F(void const * argument)
{

	INT32U Time2 =0;

	HbInit();//��������ģ���ʼ��
	createIWDG( &Iwdg_T10, 60);			 //������Ź�����

	while(1)
	{
		feedIWDG(Iwdg_T10);
        
		/* �������� */
		HbMainTask();
		
		/*ͨ�Ͽ������㲥��ʱ*/
		Time2 +=1;
		if( Time2>=60)  //300��㲥��ʱ����һ��
		{
			Time2 =0;
			ClientCH1_Queue_Stru	DATAIN;
            
			DATAIN.Device.Type  = Valve_U;				//����豸����
			DATAIN.Device.ID    = 0XAAAAAAAA;				
			DATAIN.Device.Num   = 0;						
			DATAIN.SignleCom    = RESET;			    //����Ҫ�ӻ�����
            
			FY_2000Send_Code_QInput(&DATAIN,50);
		}
        
		osDelay(1000*5);
	}
}



/* Task11_F function ���ڲ�������Ԥ��
void Task11_F(void const * argument)
{
	BaseType_t err;
	err =err;
	INT32U Time1 =0;

    while(1)
    {
		Time1 +=1;
		if( Time1>=5)	
		{
			Time1 =0;

			
		}
    	osDelay(1000*60);

    	
    }
}
*/


/*
Task12_F function   
�û����ݶ�ʱ�ϱ����� 
*/
void Task12_F(void const * argument)
{
	BaseType_t Err;
//	UART_TO_FY1000_QueueSend_Stru SendBuffer;


	/**
	�û�������̯�Լ���ʱ�ϱ����崥���¼�
	���崴�� 
	@ʹ�� ��ֹ	 
	@�ص�����	
	@���ڴ���ʹ��
	@ѭ��ʱ��  XX(����)
	**/

	/* ϵͳ��С��̯�����޶�*/
	if(SysStatus.Syspara ==HAL_OK)
	{
		if(SysPara.Apportion_T <10)
		{
			SysPara.Apportion_T =10;
		}
	
	}
	else
	{
		SysPara.Apportion_T =120;
	}
	
	Alarm_UserShare = AlarmClk_CreatOne( AlarmClk_Disable,Alarm_UserShare_CallBack,AlarmClk_Enable,SysPara.Apportion_T);
	AlarmTime.Year = 2017; 
	AlarmTime.Month = 10;
	AlarmTime.Day = 15;
	AlarmTime.Hour = 00;
	AlarmTime.Minute = 00;
	AlarmTime.Second = 00;
	AlarmClk_ParaSet(Alarm_UserShare,&AlarmTime);
	AlarmClk_EnableCtrl(Alarm_UserShare,AlarmClk_Enable);


	while(1)
	{
		if(UseSend_Semaphore !=NULL)	//�ź�����Ч���ж�
		{
			Err =xSemaphoreTake(UseSend_Semaphore,portMAX_DELAY);	//�ȴ��û����ݷ�̯�ź���
			if(Err ==pdTRUE)
			{
				for(INT16U UserNum =0;UserNum <SysPara.UserNum;UserNum +=1)
				{
					if( UserData_Save(UserNum) ==HAL_OK)
					{
                        dbg_printf(DEBUG_INFO,"�û����ݱ���ɹ� ���:%d    �û�����:%08lX    DeviceID:%08lX", UserNum, SysUserList.User[UserNum].User_ID, ClientCH1Ctrler.Device.ID);
                        //dbg_printf(DEBUG_INFO,"�û����ݱ���ɹ� ���:%d    �û�����:%08lX    DeviceID:%08lX---λ����Ϣ %02d��¥-%d��Ԫ-%02d��-%02d��",\
                                                                                UserNum, SysUserList.User[UserNum].User_ID, ClientCH1Ctrler.Device.ID,\
                                                                                SysUserList.User[UserNum].Buld,\
                                                                                SysUserList.User[UserNum].Unit,\
                                                                                SysUserList.User[UserNum].Floor,\
                                                                                SysUserList.User[UserNum].Cell);
					}

					//ȡ���û����ݵ��ϴ�����  2017��11��10��
/*					SendBuffer.SendData.Pack_0X84.UaComFlg =0;
					SendBuffer.SendData.Pack_0X84.UserID =SysUserList.User[UserNum].User_ID;
					SendBuffer.SendData.Pack_0X84.RemainHeat =UserData[UserNum].Remain_Heat;
					SendBuffer.SendData.Pack_0X84.Total_Heat =UserData[UserNum].Total_Heat;
					SendBuffer.SendData.Pack_0X84.Apportion_Energy =UserData[UserNum].Apportion_Energy;
					SendBuffer.SendData.Pack_0X84.Total_Time =UserData[UserNum].Total_Time;
					Err =FY_1000Send_Code_QInput(&SendBuffer,0X84);
*/


					osDelay(1000*10);
					
				}
			}
		}
		osDelay(1000*20);
	}
}









/*
Task13_F function   
�豸���ݼ���ϱ�����  �Զ��ϱ����񣨲ɼ���-->������  �ɼ������س��յ������ݴ��Ϊ��Դ�ɼ���Э���ϱ�����������
*/
void Task13_F(void const * argument)
{

	SysDevPara		Device;
	SysDEV_Type	DeviceType;
	UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
	ClientSendCtrler.Num =0;
	INT16U DevNum =0;

	if(SysPara.SendSpace <5000)		//��С�ϱ��������
	{
		SysPara.SendSpace =5000;
	}
	osDelay(1000*60);				//�ϵ���ʱ1����

	while(1)
	{

		if( CalculateProvideTimeCtrler.LoopWorkFlg ==ENABLE)//�Զ��ֳ�����Ч
		{
			if(SysPara.SendMode ==DevSendMode_Loop)								//�����ϱ�����ȷ��
			{
				Device=SysDeviceList.Device[ClientSendCtrler.Num];				//�����豸����
				DeviceType =Device.Type;
				DevNum =ClientSendCtrler.Num;
				switch(DeviceType)
				{
					case Meter_B ://��ھ������������� FY-188
					{
						//ͨ��״̬�ж�
						if( (SysDevStatus[DevNum].Device1.ComTolNum !=0)&&(SysDevStatus[DevNum].Device1.ComSucNum !=0)&&(SysDevStatus[DevNum].Device1.ComFauNum ==0) )
						{
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_Type =Meter_B;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.BackFlag =COMBack_OK;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Input_Temp =SysDevData[DevNum].Device1.Input_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Output_Temp =SysDevData[DevNum].Device1.Output_Temp;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Current =SysDevData[DevNum].Device1.Instant_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Current_Unit =SysDevData[DevNum].Device1.Instant_Current_Unit;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy =SysDevData[DevNum].Device1.Instant_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy_Unit =SysDevData[DevNum].Device1.Instant_Energy_Unit;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Current =SysDevData[DevNum].Device1.Total_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Current_Unit =SysDevData[DevNum].Device1.Total_Current_Unit;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Code =SysDevData[DevNum].Device1.Total_Code;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Code_Unit =SysDevData[DevNum].Device1.Total_Code_Unit;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Energy =SysDevData[DevNum].Device1.Total_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Energy_Unit =SysDevData[DevNum].Device1.Total_Energy_Unit;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Work_Time =SysDevData[DevNum].Device1.Work_Time;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.STATE1 =SysDevData[DevNum].Device1.STATE1;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.STATE2 =SysDevData[DevNum].Device1.STATE2;
							
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComTolNum =SysDevStatus[DevNum].Device1.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComSucNum =SysDevStatus[DevNum].Device1.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComFauNum =SysDevStatus[DevNum].Device1.ComFauNum;
							
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸����ѭ������  ���: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_ID);
							}
							osDelay(SysPara.SendSpace);
						}
					}break;




					case Meter_U ://�û������������� FY-188
					{
						//ͨ��״̬�ж�
						if( (SysDevStatus[DevNum].Device2.ComTolNum !=0)&&(SysDevStatus[DevNum].Device2.ComSucNum !=0)&&(SysDevStatus[DevNum].Device2.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_Type =Meter_U;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.BackFlag =COMBack_OK;

							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Input_Temp =SysDevData[DevNum].Device2.Input_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Output_Temp =SysDevData[DevNum].Device2.Output_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current =SysDevData[DevNum].Device2.Instant_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current_Unit =SysDevData[DevNum].Device2.Instant_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy =SysDevData[DevNum].Device2.Instant_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy_Unit =SysDevData[DevNum].Device2.Instant_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current =SysDevData[DevNum].Device2.Total_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current_Unit =SysDevData[DevNum].Device2.Total_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code =SysDevData[DevNum].Device2.Total_Code;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code_Unit =SysDevData[DevNum].Device2.Total_Code_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy =SysDevData[DevNum].Device2.Total_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy_Unit =SysDevData[DevNum].Device2.Total_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Work_Time =SysDevData[DevNum].Device2.Work_Time;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE1 =SysDevData[DevNum].Device2.STATE1;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE2 =SysDevData[DevNum].Device2.STATE2;
							
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComTolNum =SysDevStatus[DevNum].Device2.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComSucNum =SysDevStatus[DevNum].Device2.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComFauNum =SysDevStatus[DevNum].Device2.ComFauNum;
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸����ѭ������  ���: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID);
							}
							osDelay(SysPara.SendSpace);

						}
					}break;
					
					case Valve_U ://����ͨ�Ͽ�����
					{
						if( (SysDevStatus[DevNum].Device3.ComTolNum !=0)&&(SysDevStatus[DevNum].Device3.ComSucNum !=0)&&(SysDevStatus[DevNum].Device3.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_Type =Valve_U;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.BackFlag =COMBack_OK;
							
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Set_Temp =SysDevData[DevNum].Device3.Set_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cur_Temp =SysDevData[DevNum].Device3.Cur_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Ave_Temp =SysDevData[DevNum].Device3.Ave_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Input_Temp =SysDevData[DevNum].Device3.Input_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Output_Temp =SysDevData[DevNum].Device3.Output_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.ValvePosition =SysDevData[DevNum].Device3.ValvePosition;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cycle_OpTim =SysDevData[DevNum].Device3.Cycle_OpTim;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cycle_OpRat =0;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Apportion_Energy =SysDevData[DevNum].Device3.Apportion_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Face_State =SysDevData[DevNum].Device3.Face_State;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Valve_State =SysDevData[DevNum].Device3.Valve_State;
							
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.ComTolNum =SysDevStatus[DevNum].Device3.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.ComSucNum =SysDevStatus[DevNum].Device3.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.ComFauNum =SysDevStatus[DevNum].Device3.ComFauNum;
							
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸����ѭ������  ���: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_ID);
							}
							osDelay(SysPara.SendSpace);
						}

					}break;

					case Valve_UH ://����ͨ�Ͽ����� ��ˮ����
					{
						if( (SysDevStatus[DevNum].Device4.ComTolNum !=0)&&(SysDevStatus[DevNum].Device4.ComSucNum !=0)&&(SysDevStatus[DevNum].Device4.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_Type =Valve_UH;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.BackFlag =COMBack_OK;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ValvePosition =SysDevData[DevNum].Device4.ValvePosition;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpTim =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpRat =0;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Apportion_Energy =SysDevData[DevNum].Device4.Apportion_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Valve_State =SysDevData[DevNum].Device4.Valve_State;

						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ComTolNum =SysDevStatus[DevNum].Device4.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ComSucNum =SysDevStatus[DevNum].Device4.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ComFauNum =SysDevStatus[DevNum].Device4.ComFauNum;

							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸����ѭ������  ���: %d SN:%08lX",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID);
							}						
							osDelay(SysPara.SendSpace);
						}

					}break;

#ifdef Meter_H_ENABLE					
					case Meter_H ://���д�ھ������������� CJ-T188
					{
						if( (SysDevStatus[DevNum].Device5.ComTolNum !=0)&&(SysDevStatus[DevNum].Device5.ComSucNum !=0)&&(SysDevStatus[DevNum].Device5.ComFauNum ==0) )
						{
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_Type =Meter_H;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.BackFlag =COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Input_Temp =SysDevData[DevNum].Device5.Input_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Output_Temp =SysDevData[DevNum].Device5.Output_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Current =SysDevData[DevNum].Device5.Instant_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Current_Unit =SysDevData[DevNum].Device5.Instant_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy =SysDevData[DevNum].Device5.Instant_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy_Unit =SysDevData[DevNum].Device5.Instant_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Current =SysDevData[DevNum].Device5.Total_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Current_Unit =SysDevData[DevNum].Device5.Total_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Code =SysDevData[DevNum].Device5.Total_Code =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Code_Unit =SysDevData[DevNum].Device5.Total_Code_Unit =MW_h;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Energy =SysDevData[DevNum].Device5.Total_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Energy_Unit =SysDevData[DevNum].Device5.Total_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Work_Time =SysDevData[DevNum].Device5.Work_Time;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.STATE1 =SysDevData[DevNum].Device5.STATE1;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.STATE2 =SysDevData[DevNum].Device5.STATE2;
							
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComTolNum =SysDevStatus[DevNum].Device5.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComSucNum =SysDevStatus[DevNum].Device5.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.ComFauNum =SysDevStatus[DevNum].Device5.ComFauNum;
							
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸����ѭ������  ���: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_ID);
							}
							osDelay(SysPara.SendSpace);

						}


					}break;
#endif					

					
#ifdef  Meter_XY_ENABLE	
					case Meter_XY ://�û������������� XY-188
					{
						//ͨ��״̬�ж�
						if( (SysDevStatus[DevNum].Device6.ComTolNum !=0)&&(SysDevStatus[DevNum].Device6.ComSucNum !=0)&&(SysDevStatus[DevNum].Device6.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_Type =Meter_XY;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.BackFlag =COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Input_Temp =SysDevData[DevNum].Device6.Input_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Output_Temp =SysDevData[DevNum].Device6.Output_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current =SysDevData[DevNum].Device6.Instant_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current_Unit =SysDevData[DevNum].Device6.Instant_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy =SysDevData[DevNum].Device6.Instant_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy_Unit =SysDevData[DevNum].Device6.Instant_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current =SysDevData[DevNum].Device6.Total_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current_Unit =SysDevData[DevNum].Device6.Total_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code_Unit =0;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy =SysDevData[DevNum].Device6.Total_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy_Unit =SysDevData[DevNum].Device6.Total_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Work_Time =SysDevData[DevNum].Device6.Work_Time;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE1 =SysDevData[DevNum].Device6.STATE1;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE2 =SysDevData[DevNum].Device6.STATE2;
							
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComTolNum =SysDevStatus[DevNum].Device6.ComTolNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComSucNum =SysDevStatus[DevNum].Device6.ComSucNum;
						//	FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComFauNum =SysDevStatus[DevNum].Device6.ComFauNum;
						
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸����ѭ������  ���: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID);
							}
							osDelay(SysPara.SendSpace);

						}
					}break;
#endif

#ifdef  Meter_HT2X_ENABLE	
                    case Meter_HT2X ://�û������������� HT2X
                    case Meter_HT3X ://�û������������� HT3X
                    {
                        //ͨ��״̬�ж�
                        if( (SysDevStatus[DevNum].Device7.ComTolNum !=0)&&(SysDevStatus[DevNum].Device7.ComSucNum !=0)&&(SysDevStatus[DevNum].Device7.ComFauNum ==0) )
                        {
                        
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.CtrlFlag=0X00;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_Type =DeviceType;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID =Device.ID;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.BackFlag =COMBack_OK;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Input_Temp =SysDevData[DevNum].Device7.Input_Temp;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Output_Temp =SysDevData[DevNum].Device7.Output_Temp;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current =SysDevData[DevNum].Device7.Instant_Current;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current_Unit =SysDevData[DevNum].Device7.Instant_Current_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy =SysDevData[DevNum].Device7.Instant_Energy;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy_Unit =SysDevData[DevNum].Device7.Instant_Energy_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current =SysDevData[DevNum].Device7.Total_Current;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current_Unit =SysDevData[DevNum].Device7.Total_Current_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code =0;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code_Unit =0;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy =SysDevData[DevNum].Device7.Total_Energy;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy_Unit =SysDevData[DevNum].Device7.Total_Energy_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Work_Time =SysDevData[DevNum].Device7.Work_Time;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE1 =SysDevData[DevNum].Device7.STATE1;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE2 =SysDevData[DevNum].Device7.STATE2;
                            
                        //  FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComTolNum =SysDevStatus[DevNum].Device6.ComTolNum;
                        //  FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComSucNum =SysDevStatus[DevNum].Device6.ComSucNum;
                        //  FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.ComFauNum =SysDevStatus[DevNum].Device6.ComFauNum;
                        
                            if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"�豸����ѭ������  ���: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID);
                            }
                            osDelay(SysPara.SendSpace);

                        }
                    }break;
#endif

#ifdef  Meter_BRC_ENABLE	
                    case Meter_BRC ://�û������������� BRC
                    {
                        //ͨ��״̬�ж�
                        if( (SysDevStatus[DevNum].Device8.ComTolNum !=0)&&(SysDevStatus[DevNum].Device8.ComSucNum !=0)&&(SysDevStatus[DevNum].Device8.ComFauNum ==0) )
                        {
                        
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.CtrlFlag=0X00;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_Type =Meter_BRC;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID =Device.ID;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.BackFlag =COMBack_OK;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Input_Temp =SysDevData[DevNum].Device8.Input_Temp;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Output_Temp =SysDevData[DevNum].Device8.Output_Temp;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current =SysDevData[DevNum].Device8.Instant_Current;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Current_Unit =SysDevData[DevNum].Device8.Instant_Current_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy =SysDevData[DevNum].Device8.Instant_Energy;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy_Unit =SysDevData[DevNum].Device8.Instant_Energy_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current =SysDevData[DevNum].Device8.Total_Current;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Current_Unit =SysDevData[DevNum].Device8.Total_Current_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code =0;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Code_Unit =0;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy =SysDevData[DevNum].Device8.Total_Energy;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Total_Energy_Unit =SysDevData[DevNum].Device8.Total_Energy_Unit;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Work_Time =SysDevData[DevNum].Device8.Work_Time;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE1 =SysDevData[DevNum].Device8.STATE1;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.STATE2 =SysDevData[DevNum].Device8.STATE2;
                              
                            if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"�豸����ѭ������  ���: %d SN:%08lX\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID);
                            }
                            osDelay(SysPara.SendSpace);

                        }
                    }break;
#endif


#ifdef Meter_DDF2_ENABLE
					case Meter_DDF2 ://����ͨ�Ͽ����� ��ˮ����
					{
						if( (SysDevStatus[DevNum].Device9.ComTolNum !=0)&&(SysDevStatus[DevNum].Device9.ComSucNum !=0)&&(SysDevStatus[DevNum].Device9.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.CtrlFlag=0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_Type =Meter_DDF2;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID =Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.BackFlag =COMBack_OK;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ValvePosition =SysDevData[DevNum].Device9.ValvePosition;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpTim =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpRat =0;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Apportion_Energy =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Valve_State =0;

							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸����ѭ������  ���: %d SN:%08lX",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID);
							}						
							osDelay(SysPara.SendSpace);
						}

					}break;
					
#endif	
                    
#ifdef Valve_NWK_ENABLE
					case Valve_NWK ://������¥����Ԫ���ڷ�modbusЭ��
					{
						if( (SysDevStatus[DevNum].Device11.ComTolNum !=0)&&(SysDevStatus[DevNum].Device11.ComSucNum !=0)&&(SysDevStatus[DevNum].Device11.ComFauNum ==0) )
						{
						
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.CtrlFlag               = 0X00;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Dev_Type               = Valve_NWK;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Dev_ID                 = Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.BackFlag               = COMBack_OK;

                            //������  //bytes_reverse( (unsigned char *)&temp, 2); ����С��ģʽ �ֽڵ���
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Input_Temp             = (UINT16)(SysDevData[DevNum].Device11.Input_Temp*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Output_Temp            = (UINT16)(SysDevData[DevNum].Device11.Output_Temp*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.EnterWater_Pressure    = (UINT16)(SysDevData[DevNum].Device11.EnterWater_Pressure*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.ReturnWater_Pressure   = (UINT16)(SysDevData[DevNum].Device11.ReturnWater_Pressure*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Room_Temp              = (UINT16)(SysDevData[DevNum].Device11.Room_Temp*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Current_Valve_Open     = (UINT16)(SysDevData[DevNum].Device11.Current_Valve_Open*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.SetValue_Open          = (UINT16)(SysDevData[DevNum].Device11.SetValue_Open*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Temp_Diff              = (UINT16)(SysDevData[DevNum].Device11.Temp_Diff*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.ReturnTemp_Set         = (UINT16)(SysDevData[DevNum].Device11.ReturnTemp_Set*100);
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.PressureDiff_Set       = (UINT16)(SysDevData[DevNum].Device11.PressureDiff_Set*100);
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Error                  = SysDevData[DevNum].Device11.Error;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Software_Version       = SysDevData[DevNum].Device11.Software_Version;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Run_Mode               = SysDevData[DevNum].Device11.Run_Mode;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Address                = SysDevData[DevNum].Device11.Address;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Motor_Steering         = SysDevData[DevNum].Device11.Motor_Steering;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Adjust_Switch          = SysDevData[DevNum].Device11.Adjust_Switch;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Adjust_Tigger          = SysDevData[DevNum].Device11.Adjust_Tigger;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D5.Dc_Motor_Speed         = SysDevData[DevNum].Device11.Dc_Motor_Speed;

							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸����ѭ������  ���: %d SN:%08lX",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID);
							}						
							osDelay(SysPara.SendSpace);
						}

					}break;
					
#endif	
					default: break;
				}
				
				ClientSendCtrler.Num +=1;
				if( ClientSendCtrler.Num >=MAXDevice_Num) //ѭ������
				{
					ClientSendCtrler.Num =0;
				}
			}
		}
		osDelay(500);
	}
}






/*
	//������ʷ���ݱ������崥���ص�����
*/
void Alarm_DataSave_CallBack(void)
{
	RealClock_Str real;
	getRealTime(&RTC_TimeTicks,&real);
	dbg_printf(DEBUG_INFO,"��ʷ���ݱ������崥��:%d-%02d-%02d-%02d:%02d:%02d",real.Year,real.Month,real.Day,real.Hour,real.Minute,real.Second);
	SaveLog();		//��ʷ���ݱ��������
}







/*
//�����û����ݶ�ʱ��̯���崥���ص�����
*/
void Alarm_UserShare_CallBack(void)
{
	if(CalculateProvideTimeCtrler.LoopWorkFlg ==ENABLE)		//ʱ�����ں���
	{
		if( SysPara.DeviceType ==Type_Valve)	//ͨ��ʱ�����������ϵͳ
		{
			if(SysStatus.ShareFlag ==HAL_OK)		//�ж��Ƿ��Ѿ���ѵ���
			{
			
			//	if(SysStatus.Dev_ComStatus ==HAL_OK)
				if(1)
				{
					dbg_printf(DEBUG_INFO,"ͨ��ʱ��������ȼ���ϵͳ�����������̯����...");
					SystemEnergyValue_Cal();		//ͨ��ʱ�� ������̯����
					dbg_printf(DEBUG_INFO,"������̯���...");
				}
				else
				{
					dbg_printf(DEBUG_INFO,"ϵͳ�豸ͨ���쳣��ȡ�����η�̯...");
				}
			}
			else
			{
				dbg_printf(DEBUG_INFO,"ϵͳ���ݻ�ȡ��,�ȴ��´η�̯...");
			}
		}
		if(UseSend_Semaphore !=NULL)	//�ź�����Ч���ж�
		{
			dbg_printf(DEBUG_INFO,"�û����ݶ�ʱ�ϱ����崥����%d",RTC_TimeTicks);
			xSemaphoreGive(UseSend_Semaphore);
		}
	}
}


















/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    while(1) 
    {
    }
    /* USER CODE END Error_Handler_Debug */ 
}













/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: dbg_printf("Wrong parameters value: file %s on line %d", file, line) */
  /* USER CODE END 6 */
 dbg_printf(DEBUG_EMERG,"Wrong parameters value: file %s on line %d", file, line);

}



















/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
