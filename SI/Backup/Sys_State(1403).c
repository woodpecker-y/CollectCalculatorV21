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
* @brief :
* 
* 
* 
*
* @author :
* @date :2017/9/15 14:07
***************************************************************
*/ 
#define _SYS_STATE_C_
#include "Sys_State.h"
#include "main.h"



extern EventBits_t cli_dog;//������Ź�

void printenv(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT8U Type =SysPara.DeviceType;
	INT32U ReportMode =SysPara.SendMode;

	cli_printf("   �豸���:       %08X \r\n",SysPara.Device_SN);
	cli_printf("   SystemTick:     %ld \r\n",SystemTick_ms);
	cli_printf("   SystemTick(S):  %ld \r\n",SystemTick_ms/1000);
	cli_printf("   ϵͳʱ��:       %4d��%2d��%2d�� %2d:%2d:%2d\r\n",RTC_Time.Year,RTC_Time.Month,RTC_Time.Day,RTC_Time.Hour,RTC_Time.Minute,RTC_Time.Second);	
	cli_printf("\r\n");
	
	cli_printf("   �ϵ����:       %ld \r\n",PowerStateRecord.Times);	
	cli_printf("   ����ʱ��:       %4d��%2d��%2d�� %2d:%2d:%2d \r\n",PowerStateRecord.Year,PowerStateRecord.Month,PowerStateRecord.Day,PowerStateRecord.Hour,PowerStateRecord.Minute,PowerStateRecord.Second);	
	cli_printf("\r\n\r\n");

	switch(Type)
	{
		case Type_Meter:
		{
			cli_printf("   ϵͳ����:  %d    ������ �ɼ�ϵͳ\r\n",Type);	
		}break;

		case Type_MeterValve:
		{
			cli_printf("   ϵͳ����:  %d    �¿ؼ���һ�廯 ����ϵͳ\r\n",Type);	
		}break;	

		case Type_Valve:
		{
			cli_printf("   ϵͳ����:  %d    ͨ��ʱ������� ����ϵͳ\r\n",Type);	

		}break;

		default :
		{
			cli_printf("   ϵͳ����:  %d    δ����\r\n",Type);

		}break;
	}

	cli_printf("   �ն��ظ����:   %lu \r\n",SysPara.ReadSpace);		//�ն��豸�ظ���ȡ���
	cli_printf("   �ն�ѭ�����:   %lu \r\n",SysPara.LoopSpace);		//�ն��豸ѭ����ȡ���
	cli_printf("\r\n");

	switch(ReportMode)
	{
		case DevSendMode_Auto:
		{
			cli_printf("   �ϱ�ģʽ:  %d    �Զ��ϱ�\r\n",ReportMode);

		}break;

		case DevSendMode_Loop:
		{
			cli_printf("   �ϱ�ģʽ:  %d    ѭ���ϱ�\r\n",ReportMode);	

		}break;	

		default :
		{
			cli_printf("   �ϱ�ģʽ:  %d    δ����\r\n",ReportMode);
			

		}break;
	}
	cli_printf("   �ն��ϱ����:   %lu \r\n",SysPara.SendSpace);	
	cli_printf("\r\n\r\n");

	
	cli_printf("   ��ů��ʼʱ��:   %4d��%2d��%2d�� %2d:%2d:%2d  \r\n",SysPara.StartTime.Year,SysPara.StartTime.Month,SysPara.StartTime.Day,SysPara.StartTime.Hour,SysPara.StartTime.Minute,SysPara.StartTime.Second);
	cli_printf("   ��ů����ʱ��:   %4d��%2d��%2d�� %2d:%2d:%2d  \r\n",SysPara.FinalTime.Year,SysPara.FinalTime.Month,SysPara.FinalTime.Day,SysPara.FinalTime.Hour,SysPara.FinalTime.Minute,SysPara.FinalTime.Second);
	cli_printf("   ϵͳ��ůʱ��:   %f    PRD:%f \r\n",(FL32)CalculateProvideTimeCtrler.ProvideTime/3600,(FL32)CalculateProvideTimeCtrler.PassData/3600);
	cli_printf("\r\n");
	cli_printf("   ��̯����:       %lu ���� \r\n",SysPara.Apportion_T);	
	cli_printf("\r\n\r\n");

	
	cli_printf("   ��վ��ַ:       %3d.%3d.%3d.%3d:%5d \r\n",SysPara.IP1,SysPara.IP2,SysPara.IP3,SysPara.IP4,SysPara.PortNum);

	cli_printf("   ϵͳ�û�����:   %3d \r\n",MAXUser_Num);
	cli_printf("   ϵͳ�û�����:   %3d \r\n",SysPara.UserNum);

	cli_printf("   ϵͳ��������:   %3d \r\n",MAXBuldMeter_Num);
	cli_printf("   ϵͳ��������:   %3d \r\n",SysPara.BuldMeterNum);

	cli_printf("   ϵͳ�豸����:   %3d \r\n",MAXDevice_Num);
	
	cli_printf("   �û��豸����:   %3d \r\n\r\n",SysPara.DevNum);
	cli_printf("   ϵͳ�豸����:   %3d \r\n\r\n",SysPara.DevNum+SysPara.BuldMeterNum);
	

}



void userpara(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	INT16U userNum =0;
	
	if(argc !=2)
	{
		cli_printf("�����������...\r\n");
		cli_printf("userpa X\r\n");
	}
	else
	{
		userNum= atoi(argv[1]);
		if(userNum<MAXUser_Num)
		{
			cli_printf("�û�ID: %08lX\r\n\r\n",SysUserList.User[userNum].User_ID);
			cli_printf("%d��¥ %d��Ԫ %d�� %d��\r\n",SysUserList.User[userNum].Buld,SysUserList.User[userNum].Unit,SysUserList.User[userNum].Floor,SysUserList.User[userNum].Cell);
			cli_printf("�������:   %d\r\n",SysUserList.User[userNum].CellArea);
			cli_printf("��������:   %08lX\r\n",SysUserList.User[userNum].BuildMeter_ID);
		}
		else
		{
			cli_printf("�û���������Χ...\r\n");
		}
	}
}






void devicepara(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	INT16U devNum =0;
	
	if(argc !=2)
	{
		cli_printf("�����������...\r\n");
		cli_printf("devpa X\r\n");
	}
	else
	{
		devNum= atoi(argv[1]);
		if(devNum<MAXDevice_Num)
		{
			INT8U Type =0;
			Type =SysDeviceList.Device[devNum].Type;
			cli_printf("�豸����:  %d  \r\n",Type);
			switch (Type)
			{
				
				case Meter_B:
				{
					cli_printf("��ھ������� -FY188 \r\n");
				}break;
				case Meter_U:
				{
					cli_printf("С�ھ������� -FY188 \r\n");
				}break;			
				case Valve_U:
				{
					cli_printf("����ͨ�Ͽ����� -FY2000 \r\n");
				}break;	

				case Valve_UH:
				{
					cli_printf("���û�ˮͨ�Ͽ����� -FY2000 \r\n");
				}break; 
#ifdef Meter_H_ENABLE				
				case Meter_H:
				{
					cli_printf("���д�ھ������� -CJ188 \r\n");
				}break; 
#endif


#ifdef  Meter_XY_ENABLE					
				case Meter_XY:
				{
					cli_printf("��Դ XYС�ھ������� -CJ188 \r\n");
				}break; 			
#endif


#ifdef  Meter_HT2X_ENABLE					
                case Meter_HT2X:
                {
                    cli_printf("��ͨHT2XС�ھ������� -CJ188 \r\n");
                }break;             
#endif


#ifdef  Meter_BRC_ENABLE					
                case Meter_BRC:
                {
                    cli_printf("�������� BRCС�ھ������� -CJ188 \r\n");
                }break;             
#endif


#ifdef  Meter_DDF2_ENABLE					
                case Meter_DDF2:
                {
                    cli_printf("��ͨͨ�Ͽ����� -DDF2 \r\n");
                }break;             
#endif


				default :
				{
					cli_printf("�豸���Ͳ�ѯʧ��...\r\n");

				}break;

			}

			if(Type !=0)
			{
				INT16U userNum =0;
				INT32U UserKEY =0;
				cli_printf("�豸���:  %d\r\n",SysDeviceList.Device[devNum].Num);
				cli_printf("�豸����:  %08lX\r\n",SysDeviceList.Device[devNum].ID);

				userNum =SysDeviceList.Device[devNum].UserNum;
				UserKEY =SysDeviceList.Device[devNum].UserKEY;
				if( SysUserList.User[userNum].User_ID ==UserKEY)
				{
					cli_printf("�����û�:  %d\r\n",userNum);
					cli_printf("�û�����:  %08lx\r\n",UserKEY);
					cli_printf("%d��¥ %d��Ԫ %d�� %d��\r\n\r\n",SysUserList.User[userNum].Buld,SysUserList.User[userNum].Unit,SysUserList.User[userNum].Floor,SysUserList.User[userNum].Cell);
				}
				else
				{
					cli_printf("���������豸...\r\n\r\n",);
				}
			}
		}
		else
		{
			cli_printf("�û���������Χ...\r\n");
		}
	}
	
	
}



void userdata(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	INT16U userNum =0;
	
	if(argc !=2)
	{
		cli_printf("�����������...\r\n");
		cli_printf("userda X\r\n");
	}
	else
	{
		userNum= atoi(argv[1]);
		if(userNum<MAXUser_Num)
		{
			cli_printf("�û����:  %d\r\n",userNum);
			cli_printf("�û�����:  %08lX\r\n",SysUserList.User[userNum].User_ID);
			
			cli_printf("ʣ������:  %ld\r\n",UserData[userNum].Remain_Heat);
//			cli_printf("��������:  %ld\r\n",UserData[userNum].Total_Heat);
			cli_printf("��̯ʱ��:  %f\r\n",(FL32)UserData[userNum].Total_Time/3600);
			cli_printf("�ۼ�����:  %ld\r\n",UserData[userNum].Apportion_Energy);

		}
		else
		{
			cli_printf("�û���������Χ...\r\n");
		}
	}
	
	
}




void devicedata(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	INT16U devNum =0;
	INT8U DevType =0;
	
	if(argc !=2)
	{
		cli_printf("�����������...\r\n");
		cli_printf("devda X\r\n");
	}
	else
	{
		devNum= atoi(argv[1]);
		if(devNum<MAXDevice_Num)
		{
			DevType =SysDeviceList.Device[devNum].Type;
			cli_printf("�豸���:%d\r\n",devNum);
			cli_printf("ID:      %08lX\r\n",SysDeviceList.Device[devNum].ID);

			
		switch(DevType)	
		{
			case Meter_B:
			{
				cli_printf("Meter_B      ��ھ������� -FY188 \r\n");
				cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device1.Input_Temp);
				cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device1.Output_Temp);
				cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device1.Instant_Current);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device1.Instant_Current_Unit);
				cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device1.Instant_Energy);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device1.Instant_Energy_Unit);
				cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device1.Total_Current);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device1.Total_Current_Unit);
				cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device1.Total_Code);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device1.Total_Code_Unit);
				cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device1.Total_Energy);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device1.Total_Energy_Unit);
				cli_printf("���ڱ��:    %lu\r\n",SysDevData[devNum].Device1.CycBot_Energy);

				cli_printf("��������:    %lu\r\n",SysDevData[devNum].Device1.Apportion_Energy);
				cli_printf("����ʱ��:    %lu\r\n",SysDevData[devNum].Device1.Work_Time);
				cli_printf("�ȱ�״̬1:   %02X\r\n",SysDevData[devNum].Device1.STATE1);
				cli_printf("�ȱ�״̬2:   %02X\r\n",SysDevData[devNum].Device1.STATE2);

				cli_printf("ͨ������:    %lu\r\n",SysDevStatus[devNum].Device1.ComTolNum);
				cli_printf("ͨѶ�ɹ�:    %lu\r\n",SysDevStatus[devNum].Device1.ComSucNum);
				cli_printf("ͨѶʧ��:    %lu\r\n",SysDevStatus[devNum].Device1.ComFauNum);				
			}break;

		
			case Meter_U:
			{
				cli_printf("Meter_U      С�ھ������� -FY188 \r\n");
				cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device2.Input_Temp);
				cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device2.Output_Temp);
				cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device2.Instant_Current);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device2.Instant_Current_Unit);
				cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device2.Instant_Energy);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device2.Instant_Energy_Unit);
				cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device2.Total_Current);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device2.Total_Current_Unit);
				cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device2.Total_Code);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device2.Total_Code_Unit);
				cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device2.Total_Energy);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device2.Total_Energy_Unit);
				cli_printf("����ʱ��:    %lu\r\n",SysDevData[devNum].Device2.Work_Time);
				cli_printf("�ȱ�״̬1:   %02X\r\n",SysDevData[devNum].Device2.STATE1);
				cli_printf("�ȱ�״̬2:   %02X\r\n",SysDevData[devNum].Device2.STATE2);

				cli_printf("ͨ������:    %lu\r\n",SysDevStatus[devNum].Device2.ComTolNum);
				cli_printf("ͨѶ�ɹ�:    %lu\r\n",SysDevStatus[devNum].Device2.ComSucNum);
				cli_printf("ͨѶʧ��:    %lu\r\n",SysDevStatus[devNum].Device2.ComFauNum);	
			}break;
			
			case Valve_U:
			{
				cli_printf("Valve_U        ����ͨ�Ͽ����� -FY2000 \r\n");
				cli_printf("�趨�¶ȱ�־:  %02X\r\n",SysDevData[devNum].Device3.Set_TCtrlFg);
				cli_printf("�趨�¶�:      %d\r\n",SysDevData[devNum].Device3.Set_Temp);
				
				cli_printf("�����¶ȱ�־:  %02X\r\n",SysDevData[devNum].Device3.LimtTE_Flag);
				cli_printf("�����趨�¶�:  %d\r\n",SysDevData[devNum].Device3.LimtTE_Value);
				
				cli_printf("��������:      %02X\r\n",SysDevData[devNum].Device3.ControlType);
				cli_printf("ǿ�ر�־:      %02X\r\n",SysDevData[devNum].Device3.ForceCtrlFlg);
				
				cli_printf("��ǰ�¶�:      %d\r\n",SysDevData[devNum].Device3.Cur_Temp);
				cli_printf("ƽ���¶�:      %d\r\n",SysDevData[devNum].Device3.Ave_Temp);
				
				cli_printf("��ˮ�¶�:      %d\r\n",SysDevData[devNum].Device3.Input_Temp);
				cli_printf("��ˮ�¶�:      %d\r\n",SysDevData[devNum].Device3.Output_Temp);
				
				cli_printf("����λ��:      %02X\r\n",SysDevData[devNum].Device3.ValvePosition);
				cli_printf("����ʱ��:      %lu\r\n",SysDevData[devNum].Device3.Cycle_OpTim);
				
				cli_printf("��̯����:      %lu\r\n",SysDevData[devNum].Device3.Apportion_Energy);
				cli_printf("���״̬:      %02X\r\n",SysDevData[devNum].Device3.Face_State);
				cli_printf("����״̬:      %02X\r\n",SysDevData[devNum].Device3.Valve_State);

				cli_printf("ͨ������:      %lu\r\n",SysDevStatus[devNum].Device3.ComTolNum);
				cli_printf("ͨѶ�ɹ�:      %lu\r\n",SysDevStatus[devNum].Device3.ComSucNum);
				cli_printf("ͨѶʧ��:      %lu\r\n",SysDevStatus[devNum].Device3.ComFauNum);	
			}break;
			
			case Valve_UH:
			{
				cli_printf("Valve_UH       ���û�ˮͨ�Ͽ����� -FY2000 \r\n");
				cli_printf("��������:      %02X\r\n",SysDevData[devNum].Device4.ControlType);
				cli_printf("ǿ�ر�־:      %02X\r\n",SysDevData[devNum].Device4.ForceCtrlFlg);
				cli_printf("����λ��:      %02X\r\n",SysDevData[devNum].Device4.ValvePosition);
				cli_printf("����ʱ��:      %lu\r\n",SysDevData[devNum].Device4.Cycle_OpTim);

				cli_printf("����״̬:      %02X\r\n",SysDevData[devNum].Device4.Valve_State);

				cli_printf("ͨ������:      %lu\r\n",SysDevStatus[devNum].Device4.ComTolNum);
				cli_printf("ͨѶ�ɹ�:      %lu\r\n",SysDevStatus[devNum].Device4.ComSucNum);
				cli_printf("ͨѶʧ��:      %lu\r\n",SysDevStatus[devNum].Device4.ComFauNum);	

			}break;
			
#ifdef Meter_H_ENABLE
			 case Meter_H:
			{
				cli_printf("Meter_H      ���д�ھ������� -CJ188 \r\n");
				cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device5.Input_Temp);
				cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device5.Output_Temp);
				
				cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device5.Instant_Current);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device5.Instant_Current_Unit);
				
				cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device5.Instant_Energy);				
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device5.Instant_Energy_Unit);
				
				cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device5.Total_Current);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device5.Total_Current_Unit);
				
				cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device5.Total_Code);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device5.Total_Code_Unit);
				
				cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device5.Total_Energy);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device5.Total_Energy_Unit);
				
				cli_printf("���ڱ��:    %lu\r\n",SysDevData[devNum].Device5.CycBot_Energy);
				cli_printf("��������:    %lu\r\n",SysDevData[devNum].Device5.Apportion_Energy);
				
				cli_printf("����ʱ��:    %lu\r\n",SysDevData[devNum].Device5.Work_Time);
				
				cli_printf("�ȱ�״̬1:   %02X\r\n",SysDevData[devNum].Device5.STATE1);
				cli_printf("�ȱ�״̬2:   %02X\r\n",SysDevData[devNum].Device5.STATE2);

				cli_printf("ͨ������:    %lu\r\n",SysDevStatus[devNum].Device5.ComTolNum);
				cli_printf("ͨѶ�ɹ�:    %lu\r\n",SysDevStatus[devNum].Device5.ComSucNum);
				cli_printf("ͨѶʧ��:    %lu\r\n",SysDevStatus[devNum].Device5.ComFauNum);					
			}break;
#endif


#ifdef  Meter_XY_ENABLE	
			case Meter_XY:
			{
				cli_printf("Meter_XY     ��ԴС�ھ������� -XY188 \r\n");
				cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device6.Input_Temp);
				cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device6.Output_Temp);
				
				cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device6.Instant_Current);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device6.Instant_Current_Unit);
				
				cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device6.Instant_Energy);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device6.Instant_Energy_Unit);
				
				cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device6.Total_Current);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device6.Instant_Current_Unit);
				
				cli_printf("���ۼ���:    %lu\r\n",SysDevData[devNum].Device6.Day_Energy);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device6.Day_Energy_Unit);
				
				cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device6.Total_Energy);
				cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device6.Total_Energy_Unit);
				
				cli_printf("����ʱ��:    %lu\r\n",SysDevData[devNum].Device6.Work_Time);
				
				cli_printf("�ȱ�״̬1:   %02X\r\n",SysDevData[devNum].Device6.STATE1);
				cli_printf("�ȱ�״̬2:   %02X\r\n",SysDevData[devNum].Device6.STATE2);

				cli_printf("ͨ������:    %lu\r\n",SysDevStatus[devNum].Device6.ComTolNum);
				cli_printf("ͨѶ�ɹ�:    %lu\r\n",SysDevStatus[devNum].Device6.ComSucNum);
				cli_printf("ͨѶʧ��:    %lu\r\n",SysDevStatus[devNum].Device6.ComFauNum);	
			}break;
#endif

#ifdef  Meter_HT2X_ENABLE

            case Meter_HT2X:
            {
                cli_printf("Meter_HT2X   ��ͨС�ھ������� -HT2X188 \r\n");
                cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device7.Input_Temp);
                cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device7.Output_Temp);
                
                cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device7.Instant_Current);
                cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device7.Instant_Current_Unit);
                
                cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device7.Instant_Energy);
                cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device7.Instant_Energy_Unit);
                
                cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device7.Total_Current);
                cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device7.Instant_Current_Unit);
                
                cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device7.Total_Code);
                cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device7.Total_Code_Unit);
                
                cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device7.Total_Energy);
                cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device7.Total_Energy_Unit);
                
                cli_printf("����ʱ��:    %lu\r\n",SysDevData[devNum].Device7.Work_Time);
                
                cli_printf("�ȱ�״̬1:   %02X\r\n",SysDevData[devNum].Device7.STATE1);
                cli_printf("�ȱ�״̬2:   %02X\r\n",SysDevData[devNum].Device7.STATE2);

                cli_printf("ͨ������:    %lu\r\n",SysDevStatus[devNum].Device7.ComTolNum);
                cli_printf("ͨѶ�ɹ�:    %lu\r\n",SysDevStatus[devNum].Device7.ComSucNum);
                cli_printf("ͨѶʧ��:    %lu\r\n",SysDevStatus[devNum].Device7.ComFauNum);  
            }break;
#endif

#ifdef  Meter_BRC_ENABLE
            
            case Meter_BRC:
            {
                cli_printf("Meter_BRC    ��������С�ھ������� -BRC188 \r\n");
                cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device8.Input_Temp);
                cli_printf("��ˮ�¶�:    %d\r\n",SysDevData[devNum].Device8.Output_Temp);
                
                cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device8.Instant_Current);
                cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device8.Instant_Current_Unit);
                
                cli_printf("˲ʱ����:    %lu\r\n",SysDevData[devNum].Device8.Instant_Energy);
                cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device8.Instant_Energy_Unit);
                
                cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device8.Total_Current);
                cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device8.Instant_Current_Unit);
                
                cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device8.Total_Code);
                cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device8.Total_Code_Unit);
                
                cli_printf("�ۼ�����:    %lu\r\n",SysDevData[devNum].Device8.Total_Energy);
                cli_printf("    ��λ:    %02X\r\n",SysDevData[devNum].Device8.Total_Energy_Unit);
                
                cli_printf("����ʱ��:    %lu\r\n",SysDevData[devNum].Device8.Work_Time);
                
                cli_printf("�ȱ�״̬1:   %02X\r\n",SysDevData[devNum].Device8.STATE1);
                cli_printf("�ȱ�״̬2:   %02X\r\n",SysDevData[devNum].Device8.STATE2);

                cli_printf("ͨ������:    %lu\r\n",SysDevStatus[devNum].Device8.ComTolNum);
                cli_printf("ͨѶ�ɹ�:    %lu\r\n",SysDevStatus[devNum].Device8.ComSucNum);
                cli_printf("ͨѶʧ��:    %lu\r\n",SysDevStatus[devNum].Device8.ComFauNum);  
            }break;
#endif



#ifdef Meter_DDF2_ENABLE

		case Meter_DDF2:
		{
			cli_printf("Meter_DDF2     ��ͨͨ�Ͽ����� -DDF2 \r\n");
			cli_printf("����λ��:      %02X\r\n",SysDevData[devNum].Device9.ValvePosition);

			cli_printf("ͨ������:      %lu\r\n",SysDevStatus[devNum].Device9.ComTolNum);
			cli_printf("ͨѶ�ɹ�:      %lu\r\n",SysDevStatus[devNum].Device9.ComSucNum);
			cli_printf("ͨѶʧ��:      %lu\r\n",SysDevStatus[devNum].Device9.ComFauNum);	

		}break;
#endif
			default:
			{
				cli_printf("�豸���ݲ�ѯʧ��...\r\n");
				cli_printf("�����豸����...\r\n");
			}break;
		
		}
			
			
		}
		else
		{
			cli_printf("�û���������Χ...\r\n");
		}
	}
	
	
}










void devicestatus(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT8U   DeviceT =0;
	INT32U  COM_T =0;
	INT32U  COM_S =0;
	INT32U  COMBack_CE =0;
	INT32U  DeviceNums =0;

	cli_printf("%-15s%-15s%-15s%-15s%-15s\r\n\r\n","Num","Type","COM_T","COM_S","COMBack_CE");
	for(INT16U i=0; i<MAXDevice_Num;i++)
	{	
		feedIWDG(cli_dog);
		DeviceT =SysDeviceList.Device[i].Type;
		if(DeviceT !=DEFUNULL)
		{
			DeviceNums +=1;
			switch(DeviceT)
			{
				case Meter_B:
				{
					COM_T =SysDevStatus[i].Device1.ComTolNum;
					COM_S =SysDevStatus[i].Device1.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device1.ComFauNum;
				}break;

				case Meter_U:
				{
					COM_T =SysDevStatus[i].Device2.ComTolNum;
					COM_S =SysDevStatus[i].Device2.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device2.ComFauNum;
				}break;				
				case Valve_U:
				{
					COM_T =SysDevStatus[i].Device3.ComTolNum;
					COM_S =SysDevStatus[i].Device3.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device3.ComFauNum;
				}break;
				case Valve_UH:
				{
					COM_T =SysDevStatus[i].Device4.ComTolNum;
					COM_S =SysDevStatus[i].Device4.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device4.ComFauNum;
				}break;
#ifdef Meter_H_ENABLE				
				case Meter_H:
				{
					COM_T =SysDevStatus[i].Device5.ComTolNum;
					COM_S =SysDevStatus[i].Device5.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device5.ComFauNum;
				}break;
#endif
                
#ifdef  Meter_XY_ENABLE	
				case Meter_XY:
				{
					COM_T =SysDevStatus[i].Device6.ComTolNum;
					COM_S =SysDevStatus[i].Device6.ComSucNum;
					COMBack_CE =SysDevStatus[i].Device6.ComFauNum;
				}break;
#endif

#ifdef  Meter_HT2X_ENABLE	
                case Meter_HT2X:
                {
                    COM_T =SysDevStatus[i].Device7.ComTolNum;
                    COM_S =SysDevStatus[i].Device7.ComSucNum;
                    COMBack_CE =SysDevStatus[i].Device7.ComFauNum;
                }break;
#endif

#ifdef  Meter_BRC_ENABLE	
                case Meter_BRC:
                {
                    COM_T =SysDevStatus[i].Device8.ComTolNum;
                    COM_S =SysDevStatus[i].Device8.ComSucNum;
                    COMBack_CE =SysDevStatus[i].Device8.ComFauNum;
                }break;
#endif

#ifdef  Meter_DDF2_ENABLE	
                case Meter_DDF2:
                {
                    COM_T =SysDevStatus[i].Device9.ComTolNum;
                    COM_S =SysDevStatus[i].Device9.ComSucNum;
                    COMBack_CE =SysDevStatus[i].Device9.ComFauNum;
                }break;
#endif




				default :
				{
					COM_T =0;
					COM_S =0;
					COMBack_CE =0;
				}break;
			}
			cli_printf("%-15d%-15d%-15lu%-15lu%-15lu\r\n",i,DeviceT,COM_T,COM_S,COMBack_CE);
		}
	}
	cli_printf("��ѯ�豸������: %lu\r\n\r\n\r\n",DeviceNums);
	
}



void systemparareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{	
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL = SysPara_Reset();		//ϵͳ������ʼ��
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("ϵͳ ��������ʼ�����......\r\n");
	}
	else
	{
		cli_printf("ϵͳ ��������ʼ��ʧ��......\r\n");
	}

		
}

void userparareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{	
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL = SysUserList_Reset();	//�û������б��ʼ��
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("�û� ��������ʼ�����......\r\n");		
	}
	else
	{
		cli_printf("�û� ��������ʼ��ʧ��......\r\n");
	}

}

void deviceparareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{	
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL =SysDeviceList_Reset();		
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("�豸 ��������ʼ�����......\r\n");
	}
	else
	{
		cli_printf("�豸 ��������ʼ��ʧ��......\r\n");
	}
}

void userdatareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{	
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL =UserData_ResetALL(MAXUser_Num);
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("�û� ��������ʼ�����......\r\n");
	}
	else
	{
		cli_printf("�û� ��������ʼ��ʧ��......\r\n");
	}
}




void devicedatareset(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{	
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL =SysDevData_ResetALL(MAXDevice_Num);		//ϵͳ�豸���ݳ�ʼ��
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("�豸 ��������ʼ�����......\r\n");
	}
	else
	{
		cli_printf("�豸 ��������ʼ��ʧ��......\r\n");
	}
}



void sysdataresetall(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	HAL_StatusTypeDef TESTvAL =HAL_OK;	
	TESTvAL =SysPara_Reset();
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("ϵͳ ��������ʼ�����......\r\n");
	}
	else
	{
		cli_printf("ϵͳ ��������ʼ��ʧ��......\r\n");
	}

	TESTvAL =SysUserList_Reset();
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("�û� ��������ʼ�����......\r\n");		
	}
	else
	{
		cli_printf("�û� ��������ʼ��ʧ��......\r\n");
	}

	TESTvAL =SysDeviceList_Reset();
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("�豸 ��������ʼ�����......\r\n");
	}
	else
	{
		cli_printf("�豸 ��������ʼ��ʧ��......\r\n");
	}

	TESTvAL =UserData_ResetALL(MAXUser_Num);
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("�û� ��������ʼ�����......\r\n");
	}
	else
	{
		cli_printf("�û� ��������ʼ��ʧ��......\r\n");
	}	

	TESTvAL =SysDevData_ResetALL(MAXDevice_Num);
	if( TESTvAL ==HAL_OK )
	{
		cli_printf("�豸 ��������ʼ�����......\r\n");
	}
	else
	{
		cli_printf("�豸 ��������ʼ��ʧ��......\r\n");
	}


}



int updatetime(char **Parm)
{


	RealClock_Str Time;
	Time.Year =atoi(Parm[1]);
	Time.Month=atoi(Parm[2]);
	Time.Day=atoi(Parm[3]);
	Time.Hour=atoi(Parm[4]);
	Time.Minute=atoi(Parm[5]);
	Time.Second=atoi(Parm[6]);
	Time.Week=atoi(Parm[7]);

	/* ���·�������ַ */
	if(PCF8563_Set(&Time) ==HAL_OK)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


void settime(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	/* �жϲ��������Ƿ�Ϸ� */
	if(argc != 8)
	{
		cmd_printf("Set systemtime YYYY MM DD HH MM SS W");
		return;
	}
  
	/* ����ϵͳʱ��*/
	if (0 != updatetime(argv))
	{
		cmd_printf("Set system time fault...\r\n");
		cmd_printf("Plesse once again ...\r\n");

	}
	else
	{
		cmd_printf("Set system time success...");
	}
}


int updatetimes(char **Parm)
{


	SysPara.StartTime.Year =atoi(Parm[1]);
	SysPara.StartTime.Month=atoi(Parm[2]);
	SysPara.StartTime.Day=atoi(Parm[3]);
	SysPara.StartTime.Hour=atoi(Parm[4]);
	SysPara.StartTime.Minute=atoi(Parm[5]);
	SysPara.StartTime.Second=atoi(Parm[6]);

	/* ���·�������ַ */
	if(SysPara_Update()==HAL_OK)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int updatetimef(char **Parm)
{

	
	SysPara.FinalTime.Year =atoi(Parm[1]);
	SysPara.FinalTime.Month=atoi(Parm[2]);
	SysPara.FinalTime.Day=atoi(Parm[3]);
	SysPara.FinalTime.Hour=atoi(Parm[4]);
	SysPara.FinalTime.Minute=atoi(Parm[5]);
	SysPara.FinalTime.Second=atoi(Parm[6]);

	/* ���·�������ַ */
	if(SysPara_Update()==HAL_OK)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}




void settime_s(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	/* �жϲ��������Ƿ�Ϸ� */
	if(argc != 7)
	{
		cmd_printf("Set start time YYYY MM DD HH MM SS");
		return;
	}
  
	/* ����ʱ��*/
	if (0 != updatetimes(argv))
	{
		cmd_printf("Set start time fault...\r\n");
		cmd_printf("Plesse once again ...\r\n");

	}
	else
	{
		cmd_printf("Set start time success...");
	}
}
void settime_f(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	/* �жϲ��������Ƿ�Ϸ� */
	if(argc != 7)
	{
		cmd_printf("Set final time YYYY MM DD HH MM SS");
		return;
	}
  
	/* ����ʱ��*/
	if (0 != updatetimef(argv))
	{
		cmd_printf("Set final time fault...\r\n");
		cmd_printf("Plesse once again ...\r\n");
	}
	else
	{
		cmd_printf("Set final time success...");
	}
}


void setsystype(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT8U Type =0;
	
	if(argc != 2)		//�ж���������ĺϷ���
	{
		cmd_printf("systype [X] \r\n");
		return;
	}
	Type =atoi(argv[1]);
	/*�ж�ֵ�ĺϷ��� �����б��� */
	if((Type ==0)||(Type>3))		
	{
		cmd_printf("systype [X] \r\n");
		cmd_printf("The System type num is error Please once again.. \r\n");
		cmd_printf("The System type num is [1]/[2]/[3] \r\n");
	}
	/*��Ч����ֵ*/
	else						
	{

		SysPara.DeviceType =Type;
		if(SysPara_Update() ==HAL_OK)
		{
			cmd_printf("The System type is Seting OK ..  System Type NUM: %d\r\n",SysPara.DeviceType);
			switch(SysPara.DeviceType)
			{
				case Type_Meter:
				{
					cli_printf("   ϵͳ����:  %d    ������ �ɼ�ϵͳ\r\n",Type);	
				}break;

				case Type_MeterValve:
				{
					cli_printf("   ϵͳ����:  %d    �¿ؼ���һ�廯 ����ϵͳ\r\n",Type);	
				}break;	

				case Type_Valve:
				{
					cli_printf("   ϵͳ����:  %d    ͨ��ʱ������� ����ϵͳ\r\n",Type);	

				}break;

				default :
				{
					cli_printf("   ϵͳ����:  %d    δ����\r\n",Type);

				}break;
			}
			
			
		}
	}
	
}


void Updatedebug(INT32U enable, INT32U level)
{
	SysPara.DebugEnable =enable;
	SysPara.DebugLevel =level;
	SysPara_Update();
}







/*


*/
void devchange(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
	INT16U DevNum =0;
	INT32U DevID =0;
	INT32U DevID1 =0;
	INT32U DevID2 =0;
	
	if(argc != 3)		//�ж���������ĺϷ���
	{
		cmd_printf("devchange [X] [Y]\r\n");
		return;
	}
	DevID = atoi(argv[1]);
	DevID1 = HexToBcd4(&DevID);
	if(Getdevice_Num(DevID1,&DevNum) ==HAL_OK)
	{
		DevID = atoi(argv[2]);
		DevID2 = HexToBcd4(&DevID);

		SysDeviceList.Device[DevNum].ID =DevID2;
		if(SysDeviceList_Update() ==HAL_OK)
		{
			cmd_printf("���ݸ��³ɹ�...\r\n");

		}
		else
		{
			cmd_printf("���ݸ���ʧ��...\r\n");
		}
	}
	else
	{
		cmd_printf("���ݲ�ѯʧ��...\r\n");
	}
	
	

}


void changeDeviceNum(INT16U num)
{
	if( num >= MAXDevice_Num)
	{
		os_printf("Device num is too big...\r\n");
		return;
	}
	ClientReadCtrler.Num = num;
	os_printf("Device num change to %u\r\n",num);
}

	



/*


*/
void setsn(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT32U DevSN =0;
	INT32U DevSN1 =0;

	
	if(argc != 2)		//�ж���������ĺϷ���
	{
		cmd_printf("setsn [12345678]\r\n");
		return;
	}
	DevSN  = atoi(argv[1]);
	DevSN1 = HexToBcd4(&DevSN);
	SysPara.Device_SN =DevSN1;
	if(SysPara_Update()==HAL_OK)
	{
		cmd_printf("�豸������óɹ�...\r\n");
		cli_printf("�豸���:       %08X \r\n",SysPara.Device_SN);
	}
	else
	{
		cmd_printf("�豸�������ʧ��...\r\n");
	}
	
	

}






	



/*

�����ն˶�ȡ���
*/
void setread(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT32U Num =0;

	if(argc != 3)		//�ж���������ĺϷ���
	{
		cmd_printf("setread [Repeat space] [Loop space]\r\n");
		return;
	}
	Num  = atoi(argv[1]);
	if(( Num<2000)||(Num>1000*60*10))
	{
		cmd_printf("setread [Repeat space] 2000<->600000 ms\r\n");
		return;
	}
	SysPara.ReadSpace =Num;
	
	Num  = atoi(argv[2]);
	if(( Num<2000)||(Num>1000*60*10))
	{
		cmd_printf("setread [Loop space] 2000<->600000 ms\r\n");
		return;
	}
	SysPara.LoopSpace =Num;
	
	if(SysPara_Update()==HAL_OK)
	{
		cmd_printf("�ն˶�ȡ������óɹ�...\r\n");
		cli_printf("�ظ����:       %lu ms \r\n",SysPara.ReadSpace);
		cli_printf("ѭ�����:       %lu ms \r\n",SysPara.LoopSpace);
	}
	else
	{
		cmd_printf("����ʧ��...\r\n");
	}
}









	



/*

�����ն��ϱ�ģʽ �����
*/
void setsend(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT32U Mode =0;
	INT32U Num =0;

	if(argc != 3)		//�ж���������ĺϷ���
	{
		cmd_printf("setsend [ModeID] [XXXXX]\r\n");
		return;
	}

	

	Mode  = atoi(argv[1]);
	{
		if(Mode >2)
		{
			cmd_printf("ModeID  0:��Ч 1:Auto 2:Loop \r\n");
			return;
		}

	}
	Num  = atoi(argv[2]);
	if(( Num<5000)||(Num>1000*60*10))
	{
		cmd_printf("setsend [5000]<->[600000] ms\r\n");
		return;
	}

	SysPara.SendMode =Mode;
	SysPara.SendSpace =Num;
	if(SysPara_Update()==HAL_OK)
	{
		cmd_printf("�ն��ϱ�������óɹ�...\r\n");
		cli_printf("�ϱ�ģʽ:       %lu\r\n",SysPara.SendMode);
		cli_printf("�ϱ����:       %lu ms \r\n",SysPara.SendSpace);
	}
	else
	{
		cmd_printf("����ʧ��...\r\n");
	}
}










	



/*

����ϵͳ�ķ�̯���
*/
void setshare(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

	INT32U Num =0;

	if(argc != 2)		//�ж���������ĺϷ���
	{
		cmd_printf("setshare [XXXXX]\r\n");
		return;
	}
	Num  = atoi(argv[1]);
	if(( Num<10)||(Num>60*12))
	{
		cmd_printf("ShareSpace [10]<->[720] Minutes\r\n");
		return;
	}
	SysPara.Apportion_T =Num;
	if(SysPara_Update()==HAL_OK)
	{
		cmd_printf("��̯�������óɹ�...\r\n");
		cli_printf("��̯����:       %lu Minutes \r\n",SysPara.Apportion_T);
	}
	else
	{
		cmd_printf("����ʧ��...\r\n");
	}
}



void powrelayctrl(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{
    
    
	INT16U CMD=0;
    CMD =CMD;
	if(argc != 2)		//�ж���������ĺϷ���
	{
		cmd_printf("relay [X] X=on/off\r\n");
		return;
	}


#if (USE_POWRELAY==0) //�ж���Ŀ�Ƿ�������Զ�̶��͵繦��   
	cmd_printf("����Ŀδ��Ӹù���...\r\n");
	return;
#endif
    
#if (USE_POWRELAY==1) //�ж���Ŀ�Ƿ�������Զ�̶��͵繦��       
	if (!strcasecmp(argv[1], "on")) 
	{
		CMD =0X0A0A;
		
	} 
	else if (!strcasecmp(argv[1], "off")) 
	{
		CMD =0XA0A0;
	}
	
	if(SysPara.RelayRecord !=CMD)
	{
		SysPara.RelayRecord =CMD;
		PowerRelay_SET(CMD);			//����·�̵�����������
		if( SysPara_Update()==HAL_OK)
		{			
			cmd_printf("�ֶ������ɹ����豸������¼�ɹ�...\r\n");
		}
	}
#endif

}










void ddf2ctrl(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

    INT32U DevID =0;
    INT32U DevID1 =0;
    INT32U flag =0;
    INT16U DevNum =0;
    ClientCH1_Queue_Stru SendBuffer_DDF2;
    

    if(argc != 3)       //�ж���������ĺϷ���
    {
        cmd_printf("ddf2ctrl [12345678] [0/1]\r\n");
        return;
    }
    DevID = atoi(argv[1]);
    DevID1 = HexToBcd4(&DevID);

    flag =atoi(argv[2]);
    if(GetMeters_Num(DevID1,Meter_DDF2 ,&DevNum) ==HAL_OK) //�ɹ��ҵ��û��豸
    {
        if(0==flag)
        {
            dbg_printf(DEBUG_INFO,"�ֶ����� ���� %08X",DevID1);//MBUS�˿����ݷ���
            SendBuffer_DDF2.Device.Num=SysDeviceList.Device[DevNum].Num;
            SendBuffer_DDF2.Device.Type=SysDeviceList.Device[DevNum].Type;
            SendBuffer_DDF2.Device.ID=SysDeviceList.Device[DevNum].ID;
            SendBuffer_DDF2.Device.COM_Type=SysDeviceList.Device[DevNum].COM_Type;
            SendBuffer_DDF2.SignleCom =SET;
            SendBuffer_DDF2.UaComFlg =0XAAAA;                               //�������ظ���¼
            SendBuffer_DDF2.Uapack=0X0D;
            SendBuffer_DDF2.SendData.DDF2Data.Pack_03.OUT =0X55;   
            DDF2_Send_Code_QInput(&SendBuffer_DDF2,0x03);
            dbg_printf(DEBUG_INFO,"�豸����...");
        }
        else
        {
            dbg_printf(DEBUG_INFO,"�ֶ�����  �ر� %08X",DevID1);
            SendBuffer_DDF2.Device.Num=SysDeviceList.Device[DevNum].Num;
            SendBuffer_DDF2.Device.Type=SysDeviceList.Device[DevNum].Type;
            SendBuffer_DDF2.Device.ID=SysDeviceList.Device[DevNum].ID;
            SendBuffer_DDF2.Device.COM_Type=SysDeviceList.Device[DevNum].COM_Type;
            SendBuffer_DDF2.SignleCom =SET;
            SendBuffer_DDF2.UaComFlg =0XAAAA;                               //�������ظ���¼
            SendBuffer_DDF2.Uapack=0X0D;
            SendBuffer_DDF2.SendData.DDF2Data.Pack_03.OUT =0XBB; 
            
            DDF2_Send_Code_QInput(&SendBuffer_DDF2,0x03);
            dbg_printf(DEBUG_INFO,"�豸�ر�...");

        }
    }
    else
    {

        dbg_printf(DEBUG_INFO,"�豸��ѯʧ��...");

    }

}






void ClirateSet(char *pcWriteBuffer, int xWriteBufferLen,int argc, char **argv)
{

    INT32U rate =0;

    if(argc != 2)       //�ж���������ĺϷ���
    {
        dbg_printf(DEBUG_INFO,"clirate [xxxxxxxx]");
        return;
    }
    rate = atoi(argv[1]);


    if((rate <1200)||(rate >921600))
    {

        dbg_printf(DEBUG_INFO,"clirate Set the value error  1200<= x <= 921600");
        return;
    }

    dbg_printf(DEBUG_INFO,"clirate The rate value set success :  %d\r\n",rate);
    
    dbg_printf(DEBUG_INFO,"Please reset the serial communication rate and turn it back on..");
    dbg_printf(DEBUG_INFO,"If you want to restore the default settings[115200], please restart the device again.\r\n");
    dbg_printf(DEBUG_INFO,"THANK YOU, GOOD LUCK\r\n");


//    HAL_UART1_MspDeInit(&huart1);
    
    HAL_Delay(2500);
    
    huart1.Init.BaudRate =rate;		
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.Parity =UART_PARITY_NONE;		
    MX_USART1_UART_Init();  //ͨ���첽�˿�1��ʼ��

    



}










 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
