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
* @date :2018/8/12 8:31
***************************************************************
*/ 
#define _BRC188PRO_C_
#include "BRC188Pro.h"
 #include "main.h"
#ifdef  Meter_BRC_ENABLE	

UART_TO_BRC188_QueueSend_Stru BRC188_Q_RX_Buffer;		//ͨ�ŷ��Ͷ��� ���ջ�����
UART_TO_BRC188_QueueSend_Stru* BRC188_Q_RX_BuffeP;	//ͨ�ŷ��Ͷ��� ���ջ�����P


/*
void BRC188_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
��������:Э��Ԥ�����������  �����ն��л����������ݽ��н��������������

*/
void BRC188_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
{
	INT8U Bufer;
	INT32U DataBdry =0;	//��Ч�������߽�
	BRC188_Pack_Uni* BRC188_RXPack =(BRC188_Pack_Uni*)(Ctrl_Point->InputPack);
	while (Ctrl_Point->Rx_Rear !=Ctrl_Point->Rx_Front) 
	{
	
		Bufer=Ctrl_Point->InputBuffer[Ctrl_Point->Rx_Rear];	//�ӽ��ջ�������ȡһ���ֽڵ�����
		
		if (*(Ctrl_Point->Ticks)- Ctrl_Point->RecPackTimeOut > Ctrl_Point->TimeOut)//֡���û���յ��µ����ݣ�����������һ֡��������
		{
			Ctrl_Point->RecPackState=0;	//������ڴ�����հ����ݱ�־
			Ctrl_Point->RecPackPoint=0;	//��ָ��
		}		
		switch(Ctrl_Point->RecPackState)
		{
			case 0:	//������ʼ��
			{
				if (Bufer == BRC188Pro_StartCode) 
				{ 
					Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
					Ctrl_Point->RecPackPoint +=1;
					Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
					Ctrl_Point->RecPackState=1;						//��ʼ�������ݰ�
					DataBdry =0;
					
				}
			}break;
			
			case 1:	//���հ汾��/�豸���ͷ�
			{		
				if ( Bufer == BRC188Pro_ProtocolCode)
				{

					Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
					Ctrl_Point->RecPackPoint +=1;
					Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
					Ctrl_Point->RecPackState=2;//��ʼ�������ݰ�	
				}
			}break;
			
			case 2://����SN ��1�ֽ�
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=3;//��ʼ�������ݰ�	
						
			}break;
			
			case 3://����SN ��2�ֽ�
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=4;//��ʼ�������ݰ�	


			}break;
	
			case 4:	//����SN ��3�ֽ�
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=5;//��ʼ�������ݰ�	

			}break;
			case 5:	//����SN ��4�ֽ�
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=6;//��ʼ�������ݰ� 

			}break;			

			case 6:	//����FAdd1
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=7;//��ʼ�������ݰ� 

					
			}break;	
			
			case 7://����FAdd2
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=8;//��ʼ�������ݰ� 			
			}break;
			
			case 8://���ս���FAdd3
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=9;//��ʼ�������ݰ� 	


			}break;

			case 9://����ConType
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=10;//��ʼ�������ݰ� 	
				
			}break;

			case 10:	//���ݳ���
			{

				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������

				if(BRC188_RXPack->DefaultPack.Lenth )	//�ж����������Ƿ����
				{
					Ctrl_Point->RecPackState=11;			//��ʼ�������ݰ�
				}
				else
				{
					Ctrl_Point->RecPackState=12;			//��ʼ�������ݰ�
				}
				DataBdry =BRC188_RXPack->DefaultPack.Lenth;
			}break;
		
			case 11:	//��Ч������
			{		


				Ctrl_Point->RecPackState=11;					//��ʼ�������ݰ�
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint] =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������

				DataBdry -=1;
				if(DataBdry ==0)
				{
					Ctrl_Point->RecPackState=12;
				}
				
			}break;

			case 12:	//У���
			{
				Ctrl_Point->RecPackState=13;					//��ʼ�������ݰ�
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint] =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				
			}break;
			
			case 13:	//������־
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackState=0; 
				
				if (Bufer ==BRC188Pro_EndCode)
				{
					BRC188_Pack_RxAnalyze_S(Ctrl_Point,BRC188_RXPack->DefaultPack.Lenth+BRC188Pro_HeadSize);
				}
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);
			}break;	
			
			default:	//����״̬,�ָ�״̬Ϊ0
			{
				Ctrl_Point->RecPackState=0;

			}break;
		}
		
		if (++Ctrl_Point->Rx_Rear >= UART_TO_BRC188BufferSize_S)
		{
			Ctrl_Point->Rx_Rear=0;
		}	

	}

}









/*
INT8U BRC188_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize)
��������:ͨ�Ž����������Ӻ���
*/
INT8U BRC188_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize)
{
	INT8U CheckFlg =0;	//�����־
	INT16U ProtoNO =0;	//Э����
	BRC188_Pack_Uni* Packin =(BRC188_Pack_Uni*)Ctrl_Point->InputPack;	//ָ��任
	
	CheckFlg =SUMCheck_Check(((INT8U*)Ctrl_Point->InputPack),DataSize);
	if(CheckFlg !=0)//У������˳�����
	{
		return	CheckFlg;
	}
	else
	{

		ProtoNO =Packin->DefaultPack.ConType;//����Э�����
		CheckFlg =BRC188_Pack_Rx_S(Ctrl_Point,ProtoNO);
	}
	return CheckFlg;
}






/*

INT8U BRC188_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
��������:��Դ�ǿ�Э����շ�����
Ctrl_Point:���տ�����
Protocol: Э����
����ֵ: 0X00 Э������ 0X01 Э�鴦��������� 0XFF Э�鲻����
*/
INT8U BRC188_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
{

	INT8U ErrorFlg =0;
	BRC188_Pack_Uni* PackData =(BRC188_Pack_Uni*)(Ctrl_Point->InputPack);		   	//����ָ�뽻��
	INT8U Proto_RX =Protocol;
	INT16U DevNum =0;
	INT32U MeterID=0;

	INT8U DataBuffer=0;		//���ݻ�����
	INT16U DataBuffer2=0;	//���ݻ�����
	INT32U DataBuffer4=0;	//���ݻ�����

	INT16U TempL =0;
	INT8U TempH =0;

	INT16U WorkTime_L =0;
	INT8U WorkTime_H =0;
	
	switch (Proto_RX)
	{
		case 129:
		{
			if(BRC188_Pack_0X129_S(Ctrl_Point) ==0x00)			//����Э�鴦��
			{
				if(ClientCH1Ctrler.Device.Type ==Meter_BRC)		//��ھ�¥��������
				{
					MeterID =PackData->Pack0X129S.Head.SN;	//��ȡ�豸��ID
					DevNum =ClientCH1Ctrler.Device.Num;		//��ȡ�豸�±�
					
					if( SysDeviceList.Device[DevNum].ID ==MeterID)	//�豸���ҳɹ�
					{
						//���ۼ�����  
						DataBuffer4 =PackData->Pack0X129S.Total_Code;
						SysDevData[DevNum].Device8.Total_Code=BcdToHex4(&DataBuffer4);//�ۼ�����
						SysDevData[DevNum].Device8.Total_Code_Unit=PackData->Pack0X129S.Total_Code_Unit;//������λ


						//��ǰ����
						DataBuffer4 =PackData->Pack0X129S.Total_Energy;
						SysDevData[DevNum].Device8.Total_Energy =BcdToHex4(&DataBuffer4);//����ֵ
						SysDevData[DevNum].Device8.Total_Energy_Unit =PackData->Pack0X129S.Total_Energy_Unit;//������λ

						//�ȹ���
						DataBuffer4 =PackData->Pack0X129S.Instant_Energy;
						SysDevData[DevNum].Device8.Instant_Energy =BcdToHex4(&DataBuffer4);//�ȹ���
						SysDevData[DevNum].Device8.Instant_Energy_Unit =PackData->Pack0X129S.Instant_Energy_Unit;//�ȹ��ʵ�λ

						//˲ʱ����
						DataBuffer4 =PackData->Pack0X129S.Instant_Current;
						SysDevData[DevNum].Device8.Instant_Current =BcdToHex4(&DataBuffer4);//����
						SysDevData[DevNum].Device8.Instant_Current_Unit =PackData->Pack0X129S.Instant_Current_Unit;//���ٵ�λ

						//�ۼ������ɼ�
						DataBuffer4 =PackData->Pack0X129S.Total_Current;						
						SysDevData[DevNum].Device8.Total_Current =BcdToHex4(&DataBuffer4);//�ۼ�����
						SysDevData[DevNum].Device8.Total_Current_Unit =PackData->Pack0X129S.Total_Current_Unit;//�ۼ�����

						
						//��ˮ�¶Ȳɼ�
						DataBuffer2 =PackData->Pack0X129S.Input_TempL;
						TempL =BcdToHex2(&DataBuffer2);
						
						DataBuffer =PackData->Pack0X129S.Input_TempH;
						TempH =BcdToHex(DataBuffer);
						SysDevData[DevNum].Device8.Input_Temp =TempH*10000+TempL;

						//��ˮ�¶Ȳɼ�
						DataBuffer2 =PackData->Pack0X129S.Output_TempL;
						TempL =BcdToHex2(&DataBuffer2);
						
						DataBuffer =PackData->Pack0X129S.Output_TempH;
						TempH =BcdToHex(DataBuffer);
						SysDevData[DevNum].Device8.Output_Temp =TempH*10000+TempL;


						//����ʱ��
						DataBuffer2 =PackData->Pack0X129S.Work_Time_L;
						WorkTime_L =BcdToHex2(&DataBuffer2);
						DataBuffer =PackData->Pack0X129S.Work_Time_H;
						WorkTime_H =BcdToHex(DataBuffer);
						SysDevData[DevNum].Device8.Work_Time =WorkTime_H*10000UL+WorkTime_L;


						//�Ǳ�����״̬���
						//�Ǳ�״̬��һ���ֽ�
						SysDevData[DevNum].Device8.STATE1 =PackData->Pack0X129S.STATE1;//�Ǳ�״̬
	 
						//�Ǳ�״̬�ڶ����ֽ�
						SysDevData[DevNum].Device8.STATE2 =PackData->Pack0X129S.STATE2;//�Ǳ�״̬ 

						SysDevData[DevNum].Device8.Apportion_Energy =SysDevData[DevNum].Device8.Total_Energy -SysDevData[DevNum].Device8.CycBot_Energy;  //������������
						SysDevStatus[DevNum].Device8.ComSucNum +=1;
						SysDevStatus[DevNum].Device8.ComFauNum =0;

						if( SysDevData_Save(DevNum) ==HAL_OK)
						{
							dbg_printf(DEBUG_DEBUG,"�豸���ݱ���  ���: %d \r\n ",DevNum);
						}


						if( SysPara.DeviceType !=Type_Valve)	//��ͨ��ʱ��������ȼ���ϵͳ
						{
							INT16U UserNum =0;
							INT32U UserID =ClientCH1Ctrler.Device.UserKEY;
							
							if(GetUser_Num(UserID,&UserNum ) ==HAL_OK) //�û���ѯ�ɹ�
							{
								UserData[UserNum].Apportion_Energy =SysDevData[DevNum].Device2.Total_Energy; //�����ſ������ݴ��ݸ��û�
								 if(UserData_Save(UserNum) ==HAL_OK)
								 {
									dbg_printf(DEBUG_DEBUG,"�û����ݱ���  ���: %d \r\n ",UserNum);
								 }
							}						
						}


						/* ��̨ʵʱ����ת��  �Զ����� */
							//if((SysPara.SendMode ==DevSendMode_Auto)||(ClientCH1Ctrler.UaComFlg !=0))//�����ϱ�����Ϊ�Զ�����	�����ⲿ�������ݳ���
							
							if(( SysPara.SendMode ==DevSendMode_Auto)&&( ClientCH1Ctrler.UaComFlg ==0))//�����ϱ�����Ϊ�Զ����� �����ⲿ������Ч
							{
							
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.CtrlFlag=0XAA;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_Type =Meter_BRC;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID =MeterID;
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
								dbg_printf(DEBUG_DEBUG,"�豸�Զ���������ת��  ���: %d SN:%08X\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D2.Dev_ID);
							}
							}
						/* ��̨ʵʱ����ת�� �Զ�����END*/


						/* ��̨ʵʱ����ת��  Զ�̳��� */
							if( ClientCH1Ctrler.UaComFlg !=0)//�ⲿ�������ݳ��� 
							{
							
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;

							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.CtrlFlag=0XAA;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Dev_Type =Meter_BRC;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Dev_ID =MeterID;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.BackFlag =COMBack_OK;

							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Input_Temp =SysDevData[DevNum].Device8.Input_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Output_Temp =SysDevData[DevNum].Device8.Output_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Instant_Current =SysDevData[DevNum].Device8.Instant_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Instant_Current_Unit =SysDevData[DevNum].Device8.Instant_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Instant_Energy =SysDevData[DevNum].Device8.Instant_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Instant_Energy_Unit =SysDevData[DevNum].Device8.Instant_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Total_Current =SysDevData[DevNum].Device8.Total_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Total_Current_Unit =SysDevData[DevNum].Device8.Total_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Total_Code =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Total_Code_Unit =0;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Total_Energy =SysDevData[DevNum].Device8.Total_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Total_Energy_Unit =SysDevData[DevNum].Device8.Total_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Work_Time =SysDevData[DevNum].Device8.Work_Time;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.STATE1 =SysDevData[DevNum].Device8.STATE1;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.STATE2 =SysDevData[DevNum].Device8.STATE2;


							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0X02)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸Զ�̳�������ת��  ���: %d SN:%08X\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0X02_D2.Dev_ID);
							}
							}
						/* ��̨ʵʱ����ת�� Զ�̳���END*/						
						ClientCH1Ctrler.SignleCom =RESET;


						

					}
				}
			}
		}
		break;
		
		default :
		{
		   ErrorFlg =0XFF; 
		}break;

	}
	return ErrorFlg;
}







/*
BRC188_���������

*/
INT8U BRC188_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point)
{

	BaseType_t Err = HAL_ERROR;

	/* ���߿���״̬��� */

	/* ���ն������� */
	Err =xQueueReceive(UART_TO_BRC188_Msg,&BRC188_Q_RX_BuffeP,5);
	if( Err != pdTRUE)
	{
		return HAL_ERROR;
	}

	/* ���ƴ��������ݲ���� */
	BRC188_Q_RX_Buffer =*BRC188_Q_RX_BuffeP;
	Ctrl_Point->PackCreatFlag =BRC188_Q_RX_Buffer.PackCreatFlag;
	Ctrl_Point->PackINPort =BRC188_Q_RX_Buffer.PackINPort;
	
	/* ����������־��� ���߿���״̬��� */
	if(Ctrl_Point->PackCreatFlag != ENABLE)
	{
		return HAL_ERROR;
	}
	Ctrl_Point->PackCreatFlag =DISABLE;

	/* ���Э����ʶ�� */
	switch(Ctrl_Point->PackINPort)
	{
		case 0X01:
		{
			BRC188_Pack_0X01_S(Ctrl_Point);

		}break;

		default:
		{
			Ctrl_Point->PackINPort =0;
		}
		break;
	}
	return HAL_OK;
}


/*
	����/����˽����Ǳ���ʵʱ����
*/
INT8U BRC188_Pack_0X129_S(UART_RBC_Stru* PORT)
{

	BRC188_Pack_Uni* PackData =(BRC188_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X00;
	
	if ((PackData->Pack0X129S.Head.Start==0X68)&&(PackData->Pack0X129S.Head.Type ==0X20))	//�ڴ��ж�֡ͷ�ĺϷ���
	{
		if ((PackData->Pack0X129S.Flag==0X1F90)&&( PackData->Pack0X129S.SER==0X00))
		{
			BackVal =0X00;
		}
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}


/*
	����/������ٲ�ʵʱ��������
*/
void BRC188_Pack_0X01_S(UART_RBC_Stru* PORT)
{

	BRC188_Pack_Uni* PackData =(BRC188_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT8U PackSize =0;
	

	PackData->Pack0X01S.Lead1=0XFE;			//ͬ����	
	PackData->Pack0X01S.Lead2=0XFE;			//ͬ����	
	PackData->Pack0X01S.Lead3=0XFE;			//ͬ����	
	PackData->Pack0X01S.Lead4=0XFE;			//ͬ����	
		
	PackData->Pack0X01S.Head.Start =0X68;
	PackData->Pack0X01S.Head.Type =0X20;

	PackData->Pack0X01S.Head.SN =BRC188_Q_RX_Buffer.ID;
	PackData->Pack0X01S.Head.FAdd1=0X00;
	PackData->Pack0X01S.Head.FAdd2=0X1111;

	PackData->Pack0X01S.Head.ConType =0X01;

	PackData->Pack0X01S.Head.Lenth =sizeof(BRC188_Pack01S_Stru)-BRC188Pro_HeadSize-2-4;//ʵ����Ч����������
	PackSize =sizeof(BRC188_Pack01S_Stru)-2;	//У�����ݳ��ȼ���
	


	PackData->Pack0X01S.Flag =0X901F;
	PackData->Pack0X01S.SER =0X00;
	
	PackData->Pack0X01S.Check =SUMCheck_Input((INT8U*)PackData+4,PackSize-4);
	PackData->Pack0X01S.End =0X16;
	
	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE;
}
#endif





 
 




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
