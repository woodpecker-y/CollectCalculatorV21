/*  
*************************************************************
*****************Tools Version 20161020**********************
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
* @brief :���ļ�����FY-1102��Ʒ��ϵͳ������״̬����
* 
* 
* 
*
* @author :��ΰ
* @date :2017/8/28 15:11
***************************************************************
*/ 
#define _SYSPARA_C_
#include "SysPara.h"
#include "main.h"


/*
	ϵͳ������ʼ��
	����ϵͳ�ϵ���Flash���µ��ڴ�����
*/
HAL_StatusTypeDef SysPara_Init(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	Errstate = ReadData_SPIFlash(SysPara_Addr,(INT8U*)&SysPara,sizeof(SysPara_Stru));
	SysStatus.Syspara =Errstate;
	return Errstate;
}
 



 /*
	ϵͳ����
����
	���ڵ�ϵͳ���������仯�� ���ڴ����ݸ������洢��
*/
HAL_StatusTypeDef SysPara_Update(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	Errstate = WriteData_SPIFlash(SysPara_Addr,(INT8U*)&SysPara,sizeof(SysPara_Stru));
	SysStatus.Syspara =Errstate;
	return Errstate;
}



 /*
	ϵͳ����Ĭ������
	��ϵͳ�����ظ�Ĭ�����ã����Ҹ������洢��
*/
HAL_StatusTypeDef SysPara_Reset(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	SysPara.Device_BU =SYSTEM_BulidTime;
	SysPara.Apportion_T =120;
	SysPara.BuldMeterNum =0;
	SysPara.UserNum =0;
	SysPara.DevNum =0;
	SysPara.DevNum_T =0;
	SysPara.IP1 =61;
	SysPara.IP2 =182;
	SysPara.IP3 =229;
	SysPara.IP4 =137;
	SysPara.PortNum =9245;
	
	SysPara.ReaportType=0X00;
	SysPara.ReportSpace =30;
	SysPara.ReportClock =1;
	
	SysPara.GPRS_COM =1;
	SysPara.MBUS_COM=2;
	SysPara.RF_BUS_COM=3;

	SysPara.PassWord =0X1000;
	SysPara.DeviceType =Type_Meter;

	SysPara.StartTime.Year =2017;
	SysPara.StartTime.Month=1;
	SysPara.StartTime.Day=1;
	SysPara.StartTime.Hour=0;
	SysPara.StartTime.Minute=0;
	SysPara.StartTime.Second=0;


	SysPara.FinalTime.Year =2017;
	SysPara.FinalTime.Month=3;
	SysPara.FinalTime.Day=10;
	SysPara.FinalTime.Hour=0;
	SysPara.FinalTime.Minute=0;
	SysPara.FinalTime.Second=0;


	SysPara.SendMode =DevSendMode_Loop;
	SysPara.ReadSpace =3000;
	SysPara.SendSpace =10*1000;
	SysPara.LoopSpace =3000;

	SysPara.DebugEnable =0;		//�ر�
	SysPara.DebugLevel =DEBUG_WARNING;

	SysPara.RelayRecord =0X0A0A;	//����·�̵���״̬�ͷ�

	Errstate = SysPara_Update();
	return Errstate;
	
}




/*
    �����û���� ��ѯ����Ӧ���͵��ն��豸
    @para UaerNum    �û���ţ��ϸ��Ӧ���������±�
    @Para TypeID   �豸����
    @Para Num       ��������ѯ�豸�������±�
    @ ret               HAL_OK �Ѿ��ɹ��ҵ���Ӧ�ն��豸
                            HAL_ERR       û���ҵ���Ӧ�ն��豸

*/
HAL_StatusTypeDef GetDeviceNum(INT16U UserNum, SysDEV_Type TypeID,INT16U* Num)
{
    HAL_StatusTypeDef Err =HAL_OK;

    SysUserPara_Stru User;
    *Num =0XFFFF;
    
    User =SysUserList.User[UserNum];
	
	
    for( INT16U i=0;i<MAXDevice_Num;i++)
    {
        if(SysDeviceList.Device[i].Type ==TypeID)
        {
            if(SysDeviceList.Device[i].UserKEY ==User.User_ID)
            {
                *Num =i;
                Err =HAL_OK;
                return Err;
            }
        }
    }
    Err =HAL_ERROR;
    return Err;
    
}








/*
��������:�����ϵ��¼����

*/

HAL_StatusTypeDef PowerStateRecord_Update(void)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;		//�����־����
	if(PCF8563_Read(&RTC_Time)==HAL_OK)
	{
		PowerStateRecord.Year =RTC_Time.Year;
		PowerStateRecord.Month=RTC_Time.Month;
		PowerStateRecord.Day=RTC_Time.Day;
		PowerStateRecord.Hour=RTC_Time.Hour;
		PowerStateRecord.Minute=RTC_Time.Minute;
		PowerStateRecord.Second=RTC_Time.Second;
		if(WriteData_FRAM(PowerState_Addr, (INT8U*)&PowerStateRecord, sizeof(PowerStateRecord ))==0)//д���������
		{
			ErrFlg =HAL_OK;
		}
	}
	else
	{
		ErrFlg =HAL_ERROR;
	}
	return ErrFlg;
}




/*
��������:��洢��д�뵥һ�û�������

*/

HAL_StatusTypeDef PowerStateRecord_Init(void)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;		//�����־����
	if(ReadData_FRAM(PowerState_Addr, (INT8U*)&PowerStateRecord, sizeof(PowerStateRecord ))==0)//д���������
	{
		PowerStateRecord.Times +=1;
		ErrFlg =HAL_OK;
	}
	else
	{
		PowerStateRecord.Year =0;
		PowerStateRecord.Month=0;
		PowerStateRecord.Day=0;
		PowerStateRecord.Hour=0;
		PowerStateRecord.Minute=0;
		PowerStateRecord.Second=0;
		PowerStateRecord.Times =0;
	}
	return ErrFlg;
}






 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
