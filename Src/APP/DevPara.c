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
* @brief :���ļ����ڹ���ɼ�����Ͻͨ���豸�Ĳ���/״̬����
* 
* 
* 
*
* @author :��ΰ
* @date :2017/8/29 14:52
***************************************************************
*/ 
#define _DEVPARA_C_
#include "DevPara.h"
#include "main.h"



/*
	ϵͳ�豸�б��ʼ��
	����ϵͳ�ϵ���Flash���µ��ڴ�����
*/
HAL_StatusTypeDef SysDeviceList_Init(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	Errstate = ReadData_SPIFlash(SysDeviceList_Addr,(INT8U*)&SysDeviceList,sizeof(SysDeviceList_Stru));
	for( INT16U i=0;i<MAXDevice_Num;i++)
	{
		SysDeviceList.Device[i].Num =i;
	}
	return Errstate;
}
 



 /*
	ϵͳ�豸�б����
	���ڵ�ϵͳ���������仯�� ���ڴ����ݸ������洢��
*/
HAL_StatusTypeDef SysDeviceList_Update(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	Errstate = WriteData_SPIFlash(SysDeviceList_Addr,(INT8U*)&SysDeviceList,sizeof(SysDeviceList_Stru));
	return Errstate;
}



 /*
	ϵͳ�豸�б�Ĭ������
	��ϵͳ�����ظ�Ĭ�����ã����Ҹ������洢��
*/
HAL_StatusTypeDef SysDeviceList_Reset(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	for( INT16U i=0;i<MAXDevice_Num;i++)
	{
		SysDeviceList.Device[i].Num =i;
		SysDeviceList.Device[i].Type =DEFUNULL;
		SysDeviceList.Device[i].ID=0;
		SysDeviceList.Device[i].UserNum=0X00;
		SysDeviceList.Device[i].UserKEY=0;
		SysDeviceList.Device[i].COM_Type=0;
		

	}
	Errstate = SysDeviceList_Update();
	return Errstate;
	
}










/*

��������:�Ӵ洢����ȡ��һ�豸����
*/
HAL_StatusTypeDef SysDevData_Read(INT16U ListNum,SysDevData_Stru* Value)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	INT16U Mem_Addr =ListNum*(sizeof(SysDevData_Stru))+DevData_Addr;   //�洢����ַ����
	INT16U Data_Size =sizeof(SysDevData_Stru);//�豸���ݴ���
	SysDevData_Stru Data;
	
	if(ListNum>=MAXDevice_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	if(ReadData_FRAM(Mem_Addr,(INT8U*)&Data,Data_Size) ==0)
	{
		memcpy((INT8U*)Value,  (INT8U*)&Data,Data_Size);//���������ݴ��ݸ�����ָ��
		ErrFlg =HAL_OK;
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

HAL_StatusTypeDef SysDevData_Update(INT16U ListNum,SysDevData_Stru* Value)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;		//�����־����
	INT16U Mem_Addr =ListNum*(sizeof(SysDevData_Stru))+DevData_Addr;   //�洢����ַ����
	INT16U Data_Size =sizeof(SysDevData_Stru);//�û��������ݴ���

	if(ListNum>=MAXDevice_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	if(WriteData_FRAM(Mem_Addr, (INT8U*)Value, Data_Size)==0)//д���������
	{
		ErrFlg =HAL_OK;
	}
	else
	{
		ErrFlg =HAL_ERROR;
	}
	return ErrFlg;
}


/*

	�������ܽ��ڴ����ݸ��µ��洢�� 
	�ڸ���֮ǰ�뱣֤�ڴ����ݵ���ȷ
*/

HAL_StatusTypeDef SysDevData_Save(INT16U ListNum)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;		//�����־����

	SysDevData_Stru UserPara_WriteBuf;
	if (ListNum>=MAXDevice_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	UserPara_WriteBuf =SysDevData[ListNum];
	ErrFlg =SysDevData_Update( ListNum,&UserPara_WriteBuf);
	return ErrFlg;
}



/*
��������:UserDara_InitALL(INT16U UserNum)
��������:��ϵͳ���������ϵ��ʼ�� (�Ӵ洢����ָ��λ�ö�ȡ����,��������������豸����)
����:��
����ֵ:  ����0X00;����ֵ  �쳣
*/

HAL_StatusTypeDef SysDevData_InitALL(INT16U Num)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	INT16U i =0;	//ѭ�����Ʊ���
	SysDevData_Stru UserDataB;

	if (Num>MAXDevice_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}

	for (i =0; i<Num;i++)
	{
		ErrFlg=SysDevData_Read(i,&UserDataB);
		if (ErrFlg ==HAL_OK )
		{
			SysDevData[i] =UserDataB;
		}
		else
		{
			ErrFlg =HAL_ERROR;
			break;
		}
	}
	return ErrFlg;
	
}




/*
��������:���û����ݻظ���������
*/

HAL_StatusTypeDef SysDevData_ResetALL(INT16U DevNum)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	Dev1Data_Stru DataBuffer1;
	Dev2Data_Stru DataBuffer2;
	Dev3Data_Stru DataBuffer3;
	Dev4Data_Stru DataBuffer4;
    
#ifdef Meter_H_ENABLE
	Dev5Data_Stru DataBuffer5;
#endif
#ifdef Valve_NWK_ENABLE
	Dev11Data_Stru DataBuffer11;
#endif
	SysDevData_Stru DevData;
	INT16U i =0;

	//�豸����1
	DataBuffer1.Input_Temp=0;
	DataBuffer1.Output_Temp=0;
	DataBuffer1.Instant_Current =0;
	DataBuffer1.Instant_Current_Unit =m3PreH;
	DataBuffer1.Instant_Energy =0;
	DataBuffer1.Instant_Energy_Unit =MW;
	DataBuffer1.Total_Current =0;
	DataBuffer1.Total_Current_Unit =m3;
	DataBuffer1.Total_Code =0;
	DataBuffer1.Total_Code_Unit =MW_h;
	DataBuffer1.Total_Energy =0;
	DataBuffer1.Total_Energy_Unit =MW_h;
	DataBuffer1.CycBot_Energy =0;		//���ڱ�ף����ڼ�¼���ڿ�ʼʱ������ֵ
	DataBuffer1.Apportion_Energy =0;		//��̯����(��ů���ڵķ�̯����)

	DataBuffer1.Work_Time =0;
	DataBuffer1.STATE1 =0;
	DataBuffer1.STATE2 =0;



	//�豸����2
	DataBuffer2.Input_Temp=0;
	DataBuffer2.Output_Temp=0;
	DataBuffer2.Instant_Current =0;
	DataBuffer2.Instant_Current_Unit =m3PreH;
	DataBuffer2.Instant_Energy =0;
	DataBuffer2.Instant_Energy_Unit =MW;
	DataBuffer2.Total_Current =0;
	DataBuffer2.Total_Current_Unit =m3;
	DataBuffer2.Total_Code =0;
	DataBuffer2.Total_Code_Unit =MW_h;
	DataBuffer2.Total_Energy =0;
	DataBuffer2.Total_Energy_Unit =MW_h;
	DataBuffer2.Work_Time =0;
	DataBuffer2.STATE1 =0;			//�ȱ����״̬ =0;	
	DataBuffer2.STATE2 =0;			//�ȱ����״̬ =0;	


	//�豸����3
	DataBuffer3.Set_TCtrlFg =TCFlag_OFF;
	DataBuffer3.Set_Temp =2000;
	
	DataBuffer3.LimtTE_Flag =TCFlag_OFF;
	DataBuffer3.LimtTE_Value =3000;
	
	DataBuffer3.ControlType =0X00;
	DataBuffer3.ForceCtrlFlg =Force_Nor;
	DataBuffer3.Cur_Temp =0;
	DataBuffer3.Ave_Temp =0;
	DataBuffer3.Input_Temp =0;
	DataBuffer3.Output_Temp =0;
	DataBuffer3.ValvePosition =Valve_Close;
	DataBuffer3.Cycle_OpTim =0;
	DataBuffer3.Cycle_OpRat =0;
	DataBuffer3.Apportion_Energy =0;	//��̯����
	DataBuffer3.Face_State =0;
	DataBuffer3.Valve_State =0;





	//�豸����4
	DataBuffer4.ControlType =0;
	DataBuffer4.ForceCtrlFlg =Force_Nor;
	DataBuffer4.ValvePosition =Valve_Open;
	DataBuffer4.Cycle_OpTim =0;
	DataBuffer4.Cycle_OpRat =0;
	DataBuffer4.Apportion_Energy =0;	//��̯����
	DataBuffer4.Valve_State =0;

#ifdef Meter_H_ENABLE
	//�豸����5
	DataBuffer5.Input_Temp=0;
	DataBuffer5.Output_Temp=0;
	DataBuffer5.Instant_Current =0;
	DataBuffer5.Instant_Current_Unit =m3PreH;
	DataBuffer5.Instant_Energy =0;
	DataBuffer5.Instant_Energy_Unit =MW;
	DataBuffer5.Total_Current =0;
	DataBuffer5.Total_Current_Unit =m3;
	DataBuffer5.Total_Code =0;
	DataBuffer5.Total_Code_Unit =MW_h;
	DataBuffer5.Total_Energy =0;
	DataBuffer5.Total_Energy_Unit =MW_h;
	DataBuffer5.CycBot_Energy=0;			//���ڱ�ף����ڼ�¼���ڿ�ʼʱ������ֵ
	DataBuffer5.Apportion_Energy=0;		    //�����ڷ�̯����   ��ǰ���-���ڱ��
	DataBuffer5.Work_Time =0;
	DataBuffer5.STATE1 =0;
	DataBuffer5.STATE2 =0;
#endif

#ifdef Meter_H_ENABLE
	//�豸����11
	DataBuffer11.Input_Temp             = 0;    //��ˮ�¶�
	DataBuffer11.Output_Temp            = 0;    //��ˮ�¶�
	DataBuffer11.EnterWater_Pressure    = 0;    //��ˮѹ��
	DataBuffer11.ReturnWater_Pressure   = 0;    //��ˮѹ��
	DataBuffer11.Room_Temp              = 0;    //����
	DataBuffer11.Current_Valve_Open     = 0;    //��ǰ���ſ���ֵ
	DataBuffer11.SetValue_Open          = 0;    //���÷��ſ���ֵ
	DataBuffer11.Temp_Diff              = 0;    //�²��趨ֵ
	DataBuffer11.ReturnTemp_Set         = 0;    //��ˮ�¶��趨ֵ
	DataBuffer11.PressureDiff_Set       = 0;    //ѹ���趨ֵ
	DataBuffer11.Error                  = 0;    //������� 0Ϊ������1Ϊ��ת��2Ϊ��ˮ�¶ȴ�������·��3.��ˮ�¶ȴ�������·��4.��ˮѹ����������·��5��ˮѹ����������·
	DataBuffer11.Software_Version       = 0;    //����汾��  100 ��Ϊ V1.0 
	DataBuffer11.Run_Mode               = 0;    //����ģʽ  0Ϊ����ģʽ��1Ϊ�²�ģʽ2Ϊ����ģʽ3Ϊѹ��ģʽ4.�͵ؿ���ģʽ��������磩5.4-20���ƿ���ģʽ����Ӳ��֧�֣�6 TIME
	DataBuffer11.Address                = 0;    //��ַ 1-247��Ĭ��Ϊ1
	DataBuffer11.Motor_Steering         = 0;    //���ת�� 0Ϊ���򷧣�1Ϊ����
	DataBuffer11.Adjust_Switch          = 0;    //�Զ��г�У�����أ�0�رգ�1Ϊ�򿪣�ֵΪ1ʱÿ���ϵ��Զ�У���г�
	DataBuffer11.Adjust_Tigger          = 0;    //д0x5555����һ��
    DataBuffer11.Dc_Motor_Speed         = 0;    //ֱ������ٶ�
#endif

	for(i =0; i<DevNum;i++)
	{
        SysDEV_Type DEVT =SysDeviceList.Device[i].Type;
        switch(DEVT)
        {
            case Meter_B:
            {
				DevData.Device1 =SysDevData[i].Device1 =DataBuffer1;
				ErrFlg=SysDevData_Update(i,&DevData);
            } break;
            case Meter_U:
            {
                 DevData.Device2=SysDevData[i].Device2 =DataBuffer2;
                 ErrFlg=SysDevData_Update(i,&DevData);
            } break; 
            case Valve_U:
            {
                DevData.Device3=SysDevData[i].Device3 =DataBuffer3;
                ErrFlg=SysDevData_Update(i,&DevData);
            } break;
            
            case Valve_UH:
#ifdef Meter_DDF2_ENABLE            
            case Meter_DDF2:
#endif            
            {
                DevData.Device4=SysDevData[i].Device4 =DataBuffer4;
                ErrFlg=SysDevData_Update(i,&DevData);
            } break;
            
#ifdef Meter_H_ENABLE
            case Meter_H:
            {
                DevData.Device5=SysDevData[i].Device5 =DataBuffer5;
                ErrFlg=SysDevData_Update(i,&DevData);
            } break;
#endif	
            
#ifdef Valve_NWK_ENABLE //NWK ������¥����Ԫ���ڷ�modbusЭ��
            case Valve_NWK:
            {
                DevData.Device11=SysDevData[i].Device11 =DataBuffer11;
                ErrFlg=SysDevData_Update(i,&DevData);
            } break;
#endif		
            default :
            {
                DevData.Device2=SysDevData[i].Device2 =DataBuffer2;
                ErrFlg=SysDevData_Update(i,&DevData);
            } break;

        }
		if ( ErrFlg==HAL_OK)
		{
			continue;
		}
		else
		{
			ErrFlg =HAL_ERROR;
			return ErrFlg;
		}
	}
	return ErrFlg;
	
}







/*
	
��ȡ������Ϣ
	�ؽ�������Ϣ��

*/
HAL_StatusTypeDef GetbuildMeterMessage(void)
{
	HAL_StatusTypeDef ErrState =HAL_OK;
	
    INT16U 	Num =0;	
	INT32U	ID =0;		


	INT16U 	Meters =0;
	

	for( INT16U i=0;i<MAXBuldMeter_Num;i++)		//�����豸֮��������� ��ȡ�����ID���±�
	{
		if(
            (SysDeviceList.Device[i].Type ==Meter_B)
#ifdef Meter_H_ENABLE
        ||(SysDeviceList.Device[i].Type ==Meter_H)
#endif
        
        )	//�ж��豸����
		{
			Num =i;
			ID =SysDeviceList.Device[i].ID;		//�豸��Ŵ���
			
			BuildMeters[Meters].ID =ID;
			BuildMeters[Meters].Num =Num;
			
			Meters +=1;
			if(Meters >MAXBuldMeter_Num)
			{
				ErrState =HAL_ERROR;
				return ErrState;
			}
		}
	}

	for(INT16U A=0;A<MAXBuldMeter_Num;A++ )	//�����ö�����б��� ��������Ͻ�û���������
	{
		BuildMeters[A].Users=0;
	}
	
	for( INT16U i=0;i<MAXUser_Num;i++)					//���������û������� ��ѯ����
	{
		for(INT16U A=0;A<SysPara.BuldMeterNum;A++ )		//�����������ݱ�
		{
			if( SysUserList.User[i].BuildMeter_ID ==BuildMeters[A].ID)
			{
				BuildMeters[A].Users +=1;
			}
		}	
	}
	ErrState =HAL_OK;
	return ErrState;
}










/*
	
	��ȡϵͳʵ���û�����
*/
void GetSystemUserNum(void)
{
	INT16U UserNum =0;

	for( INT16U L=0;L<MAXUser_Num;L++)		//�����û�List
	{
		if(SysUserList.User[L].User_ID !=0)
		{
			UserNum +=1;
		}
	}
	SysPara.UserNum =UserNum;			//�û���������
}



/*
	
	��ȡϵͳʵ���豸����

	���иú��� ����� ��������  �û��豸����  ϵͳ�豸������
*/
void GetSystemDevMessage(void)
{

	INT16U DeviceNum =0;
	for( INT16U L=0;L<MAXDevice_Num;L++)		//�����豸List
	{
		if(SysDeviceList.Device[L].UserKEY !=0)
		{
			DeviceNum +=1;
		}
	}
	SysPara.DevNum =DeviceNum;				//�û��豸��������


	DeviceNum =0;
	for( INT16U i=0;i<MAXBuldMeter_Num;i++)		//�����豸֮��������� ��ȡ�����ID���±�
	{
		if(
            (SysDeviceList.Device[i].Type ==Meter_B)
#ifdef Meter_H_ENABLE
        ||(SysDeviceList.Device[i].Type ==Meter_H)
#endif
        )	//�ж��豸����
		{
			DeviceNum +=1;
		}
	}
	SysPara.BuldMeterNum =DeviceNum;			//¥��������
	
	SysPara.DevNum_T =SysPara.BuldMeterNum +SysPara.DevNum;	//ϵͳ�豸����������
}




/*
	�����豸ID ��ȡ�豸���±�
*/
HAL_StatusTypeDef GetMeters_Num_Build(INT32U ID,SysDEV_Type Type,INT16U* Num)
{
	for( INT16U A=0;A<MAXBuldMeter_Num;A++)
	{
		if(SysDeviceList.Device[A].Type ==Type)
		{
			if(SysDeviceList.Device[A].ID ==ID)
			{
				*Num =A;
				return HAL_OK;
			}
		}
	}
	return HAL_ERROR;
}







/*
	�����豸ID ��ȡ�豸���±�
*/
HAL_StatusTypeDef GetMeters_Num(INT32U ID,SysDEV_Type Type,INT16U* Num)
{
	for( INT16U A=0;A<MAXDevice_Num;A++)
	{
		if(SysDeviceList.Device[A].Type ==Type)
		{
			if(SysDeviceList.Device[A].ID ==ID)
			{
				*Num =A;
				return HAL_OK;
			}
		}
	}
	return HAL_ERROR;
}




/*
	�����豸ID ��ȡ�豸���±�
*/
HAL_StatusTypeDef Getdevice_Num(INT32U ID,INT16U* Num)
{
	for( INT16U A=0;A<MAXDevice_Num;A++)
	{
		{
			if(SysDeviceList.Device[A].ID ==ID)
			{
				*Num =A;
				return HAL_OK;
			}
		}
	}
	return HAL_ERROR;
}




/*
	�����û���ID��ȡ��һ��ƥ���豸 ���豸�б����
*/
HAL_StatusTypeDef GetMeters_Num_FromUserID(INT32U ID,INT16U* Num)
{
	for( INT16U A=0;A<MAXUser_Num;A++)
	{
		if(SysDeviceList.Device[A].UserKEY ==ID)
		{
			*Num =A;
			return HAL_OK;
		}
	}
	return HAL_ERROR;
}



void UpDateSysDevStatusErr(void)
{
	INT8U Type=0;
	for(INT16U i =0;i<MAXDevice_Num;i++)
	{
		Type =SysDeviceList.Device[i].Type;
		switch(Type)
		{
			case Meter_B :	//��ھ������� ��ԴЭ��188
			{
				if( SysDevStatus[i].Device1.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}
			}break;

			case Meter_U://���������� ��ԴЭ��188
			{
				if( SysDevStatus[i].Device2.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}

			}break;		

			case Valve_U://ͨ�Ͽ����� FY2000
			{
				if( SysDevStatus[i].Device3.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}

			}break;	

			case Valve_UH://��ˮͨ�Ͽ����� FY2000
			{
				if( SysDevStatus[i].Device4.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}

			}break;			
#ifdef Meter_H_ENABLE
			case Meter_H://��ھ������� ����188
			{
				if( SysDevStatus[i].Device5.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}
			}break;	
#endif
#ifdef  Meter_XY_ENABLE	
			case Meter_XY://С�ھ������� XY-188
			{
				if( SysDevStatus[i].Device6.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}
			}break;	
#endif
#ifdef  Valve_NWK_ENABLE	
			case Valve_NWK://NWK������modbusЭ��
			{
				if( SysDevStatus[i].Device11.ComFauNum !=0)
				{
					SysDevStatusErr[i] =0X01;
				
				}
				else
				{
					SysDevStatusErr[i] =0X00;
				}
			}break;	
#endif
			default :break;
		}

	}
}




/*
	��ȡϵͳ�豸ͨ��״̬ �ܱ�����־
*/
HAL_StatusTypeDef GetDev_ComStatus(void)
{
	for(INT16U loop =0;loop<MAXDevice_Num;loop++)
	{
		if(SysDevStatusErr[loop] !=0X00)
		{
			return HAL_ERROR;
		}
	}

	return HAL_OK;
}


 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
