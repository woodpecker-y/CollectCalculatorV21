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
* @author :��ΰ
* @date :2017/10/15 17:04
***************************************************************
*/ 
#define _CALCULATE_C_
#include "Calculate.h"
#include "Main.h"




/*�ж�ƽ�����꺯��*/
INT8U LeapYear(INT16U year )
{
	for(TimConver.i=0;TimConver.i<year;TimConver.i++)
	{
	   if (((TimConver.i%400==0)||(TimConver.i%100!=0))&&((TimConver.i%4)==0))
	   {
			TimConver.j=TimConver.j+1;
	   }
	}
	if (((year%400==0)||(year%100!=0))&&((year%4)==0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




/*

��������:Con_Second (ShareTime_Str *TIME1,ShareTime_Str *TIME2)
��������: ��������ʱ���ļ��(S)
TIME1:����ʱ��
TIME2:֮ǰʱ��

TIME1-TIME2  >0˵�� TIME2ʱ����ǰ  ��֮�ں�

*/
INT32S Con_Second (RealClock_Str *TIME1,RealClock_Str *TIME2)
{

	INT32S second =0;//������������
	time_t T1;
	time_t T2;
	
	getTimeTick(&T1, TIME1);
	getTimeTick(&T2, TIME2);

	if(T1 >=T2)
	{
		second =T1-T2;
	}
	else
	{
		second =-(T2-T1);
	}
	return second;         //��������
}






/*

	���㹩ůʱ�䳤��
	@Pra  TimeSpace ���
	@TimeTicks  ʱ��Դ
	@ret ���ص�ʱ�� ��λ����
*/
INT32S CalculateProvideTimeServer(void)
{	
	INT32S TimeCord_Start;
	INT32S TimeCord_Final;
	INT32S TimeTotal =0;
	RealClock_Str DevsoftTime;

	DevsoftTime.Year =RTC_Time.Year;
	DevsoftTime.Month =RTC_Time.Month;
	DevsoftTime.Day =RTC_Time.Day;
	DevsoftTime.Hour =RTC_Time.Hour;
	DevsoftTime.Minute =RTC_Time.Minute;
	DevsoftTime.Second =RTC_Time.Second;

	TimeCord_Start =Con_Second (&DevsoftTime,&SysPara.StartTime);			//��ǰʱ��͹�ů��ʼʱ��Ƚ� 
	if(TimeCord_Start >=0)	//��ǰʱ���ڹ�ů��ʼʱ��֮��  
	{
	
		TimeCord_Final =Con_Second (&DevsoftTime,&SysPara.FinalTime);		//��ǰʱ��͹�ů����ʱ��Ƚ�
		
		if( TimeCord_Final >=0) //��ǰʱ���ڹ�ů����ʱ��֮��
		{
			TimeTotal =Con_Second (&SysPara.FinalTime,&SysPara.StartTime);
			CalculateProvideTimeCtrler.PassData =TimeCord_Final;			//��ů��֮��ʱ��
		}
		else		//��ǰʱ���ڹ�ů����
		{
			TimeTotal=TimeCord_Start;
			CalculateProvideTimeCtrler.PassData =0;					        //��ů��֮��ʱ��
		}
	}
	else		//��ǰʱ���ڹ�ů��ʼʱ��֮ǰ
	{
		CalculateProvideTimeCtrler.PassData= TimeCord_Start;				//��ů��֮ǰʱ��
		TimeTotal =0;
		
	}
	CalculateProvideTimeCtrler.ProvideTime =TimeTotal;
	return TimeTotal;	
	
}






/*

	�û��������ļ���
*/



void SystemEnergyValue_Cal(void)
{

	INT32U BuildMeterID=0;			//¥����ID	
	INT64U BuldMeterEnergyValue =0;	//���� ����ֵ
	FL32 e =0;					//��������
	INT32U Q =0;					//��ʽ��������
	FL32 SUM =0;					//��ĸ�����
	
	if( SysPara.DeviceType ==Type_Valve)	//ͨ��ʱ�����������ϵͳ
	{
	

		for( INT16U LoopBM =0;LoopBM<SysPara.BuldMeterNum;LoopBM++)	//��������м���
		{
			BuildMeterID =SysDeviceList.Device[LoopBM].ID;	//��¼����ID
            
			if( SysDeviceList.Device[LoopBM].Type ==Meter_B)	//�豸Ϊ��ھ�������� ��Դ188
			{
			
				BuldMeterEnergyValue = SysDevData[LoopBM].Device1.Apportion_Energy;					//������������
				/* ��׵�λ�л�*/
				if( SysDevData[LoopBM].Device1.Total_Energy_Unit ==MW_h)
				{
					BuldMeterEnergyValue = BuldMeterEnergyValue*1000UL;							//�����̯����ΪMwh ת��ΪKWH					
				}
				
			}
#ifdef Meter_H_ENABLE
			else if( SysDeviceList.Device[LoopBM].Type ==Meter_H)								//�豸Ϊ��ھ������� ����188
			{

				BuldMeterEnergyValue = SysDevData[LoopBM].Device5.Apportion_Energy;					//��������ֵ����
				/* ��׵�λ�л�*/
				if( SysDevData[LoopBM].Device5.Total_Energy_Unit ==MW_h)
				{
					BuldMeterEnergyValue = BuldMeterEnergyValue*1000UL;		//�����̯����ΪMwh ת��ΪKWH					
				}
			}
#endif
			Q =BuldMeterEnergyValue;
			SUM =0;
			
			//������ַ�ĸ	
			for( INT16U LoopUser=0;LoopUser<MAXUser_Num;LoopUser++)
			{
				if(SysUserList.User[LoopUser].BuildMeter_ID ==BuildMeterID)	//��֤��������ĺϷ���
				{
					UserData[LoopUser].Total_Heat =0XAAAA;			//ǿ�Ʒ�̯  ����Ժ��
					if(0XAAAA ==UserData[LoopUser].Total_Heat)		//��֤��̯�û����Ʊ�־��Ч��
					{
						e=((float)UserData[LoopUser].Total_Time)/((float)CalculateProvideTimeCtrler.ProvideTime);
						SUM =SUM+(e*SysUserList.User[LoopUser].CellArea);	
					}
				}				
			}
			
			SystemCal_DATA.SUM_Denom =SUM;	

			//��̯��������
			for( INT16U LoopUser=0;LoopUser<MAXUser_Num;LoopUser++)
			{
				if(SysUserList.User[LoopUser].BuildMeter_ID ==BuildMeterID)
				{
					 
					if(0XAAAA ==UserData[LoopUser].Total_Heat)		//��֤��̯�û����Ʊ�־��Ч��
					{
						e=((float)UserData[LoopUser].Total_Time)/((float)CalculateProvideTimeCtrler.ProvideTime);
						UserData[LoopUser].Apportion_Energy = (INT32U)(e*(FL32)SysUserList.User[LoopUser].CellArea*(FL32)Q/SystemCal_DATA.SUM_Denom);
					}
					else		//���û�û�н���  ��̯��������
					{
						UserData[LoopUser].Apportion_Energy = 0;
					}
				}
			}	
		}		
	}
}















 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
