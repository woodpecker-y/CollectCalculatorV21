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
* @brief :���ļ�����FY-1000ϵ���ȼ����ɼ���֮���ͨ��

* 
* 
* 
*
* @author :
* @date :2017/9/26 11:42
***************************************************************
*/ 
#define _FY1000PRO_C_
#include "FY1000Pro.h"
#include "Main.h"
#include "check.h"


osMutexId fy1000SendMutexHandle;//FY-1000Э����з��ͻ���


INT8U  NWK_0X1B_Register_Addr   = 0; //���շ������·�������ָ��ļĴ�����ַ ���������� �Ա����淴����������ʹ��
INT16U NWK_0X1B_Data            = 0; //���շ������·�������ָ������� ���������� �Ա����淴����������ʹ��

/*
��������:ProtocolCon_Rx_ForyonV20( INT8U PortNum )
��������:Э��Ԥ�����������  �����ն��л����������ݽ��н��������������

*/
void FY1000_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
{
	INT8U Bufer;
	INT32U DataBdry =0;	//��Ч�������߽�
	FY1000_Pack_Uni* FY1000_RXPack =(FY1000_Pack_Uni*)(Ctrl_Point->InputPack);
	while (Ctrl_Point->Rx_Rear !=Ctrl_Point->Rx_Front) 
	{
		Bufer=Ctrl_Point->InputBuffer[Ctrl_Point->Rx_Rear]; //�ӽ��ջ�������ȡһ���ֽڵ�����
		if (*(Ctrl_Point->Ticks)- Ctrl_Point->RecPackTimeOut > Ctrl_Point->TimeOut)//֡���û���յ��µ����ݣ�����������һ֡��������
		{
			Ctrl_Point->RecPackState=0; //������ڴ�����հ����ݱ�־
			Ctrl_Point->RecPackPoint=0; //��ָ��
		}	
		switch(Ctrl_Point->RecPackState)
		{
			case 0:	//������ʼ��
			{
				if (Bufer == FY1000Pro_StartCode) 
				{ 
					Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
					Ctrl_Point->RecPackPoint +=1;
					Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
					Ctrl_Point->RecPackState=1; 					//��ʼ�������ݰ�
					DataBdry =0;

				}
			}break;
			
			case 1:	//����Э������
			{		
				if ( Bufer == FY1000Pro_ProtocolCode)
				{
					Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
					Ctrl_Point->RecPackPoint +=1;
					Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
					Ctrl_Point->RecPackState=2; 					//��ʼ�������ݰ�

				}
			}break;
			
			case 2://����SN ��1�ֽ�
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=3; 					//��ʼ�������ݰ�

			}break;
			
			case 3://����SN ��2�ֽ�
			{		
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=4; 					//��ʼ�������ݰ�
			}break;
	
			case 4:	//����SN ��3�ֽ�
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=5; 					//��ʼ�������ݰ�

			}break;
			case 5:	//����SN ��4�ֽ�
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=6; 					//��ʼ�������ݰ�

			}break;			

			case 6:	//����TYPE
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=7; 					//��ʼ�������ݰ�

			}break;	

			case 7:	//���ݳ��ȵ�1�ֽ�
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=8; 					//��ʼ�������ݰ�

			}break;	

			case 8:	//���ݳ��ȵ�2�ֽ�
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=9; 					//��ʼ�������ݰ�

			}break;	

			case 9:	//���ݳ��ȵ�3�ֽ�
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=10; 					//��ʼ�������ݰ�

			}break;	

			case 10:	//���ݳ��ȵ�4�ֽ�
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������

				if(FY1000_RXPack->DefaultPack.Lenth )	//�ж����������Ƿ����
				{
					Ctrl_Point->RecPackState=11;			//��Ч���ݰ���������
				}
				else
				{
					Ctrl_Point->RecPackState=12;			//��ʼ�������ݰ�  ��Ч���ݰ�û������
				}
				DataBdry =FY1000_RXPack->DefaultPack.Lenth;

			}break;	

		
			case 11:	//��Ч������
			{		

				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=11; 					//��ʼ�������ݰ�

				
				DataBdry -=1;
			//	if ( (FY1000_RXPack->DefaultPack.Lenth + FY1000Pro_HeadSize)==Ctrl_Point->RecPackPoint)
				if(DataBdry ==0)
				{
					Ctrl_Point->RecPackState=12;
				}

			}break;

			case 12:	//У���
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=13; 					//��ʼ�������ݰ�	
			}break;
			
			case 13:	//������־
			{
			
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				
				
				if (Bufer ==FY1000Pro_EndCode)
				{
					FY1000_Pack_RxAnalyze_S(Ctrl_Point,FY1000_RXPack->DefaultPack.Lenth+FY1000Pro_HeadSize);
				}
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);
				Ctrl_Point->RecPackState=0; 
				
			}break;	
			
			default:	//����״̬,�ָ�״̬Ϊ0
			{
				Ctrl_Point->RecPackState=0;

			}break;
		}
		
		if (++Ctrl_Point->Rx_Rear >= UART_TO_FY1000BufferSize_S)
		{
			Ctrl_Point->Rx_Rear=0;
		}		
	}	
	
	/* �޲���ϵͳ������ʹ��   ������ϵͳ�����½��� ������������ 	*/
	//	FY1000_Pack_TxServer_S(Ctrl_Point); 	//���������
}






 
 
 
 
  
/*

��������:void	RXPack_AnalyzeForyonV10(INT8U PortNum,INT16U DataNum)
��������:ͨ�Ž����������Ӻ���
*/
INT8U FY1000_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT32U DataSize)
{
	INT8U CheckFlg =0;  //�����־
	INT8U ProtoNO =0;  //Э����
	FY1000_Pack_Uni* Packin =(FY1000_Pack_Uni*)Ctrl_Point->InputPack;	 //ָ��任

	CheckFlg =SUMCheck_Check(((INT8U*)Ctrl_Point->InputPack),DataSize);
	if(CheckFlg !=0)//У������˳�����
	{
		return  CheckFlg;
	}
	else
	{
		ProtoNO =Packin->DefaultPack.ConType;//����Э�����
		CheckFlg =FY1000_Pack_Rx_S(Ctrl_Point,ProtoNO);
	}
	return CheckFlg;
}







/*
(0X01����վ�����û��ն��豸���ݳ�������
*/
INT8U  FY1000_Pack_0X01(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if ( PackData->Pack_0X01.Head.SN ==SysPara.Device_SN)
	{
		if((PackData->Pack_0X01.CtrlFlag ==0X00)||(PackData->Pack_0X01.CtrlFlag ==0XAA))
		{
			BackVal =0X00;		
		}
	}
	return BackVal;
}



void FY1000_Pack_0X02_N(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X02_N.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X02_N.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X02_N.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X02_N.Head.ConType =0X02;

	PackData->Pack_0X02_N.Head.Lenth =sizeof(FY1000_Pack0X02_N_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������

	PackData->Pack_0X02_N.CtrlFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_N.CtrlFlag;
	PackData->Pack_0X02_N.Dev_Type=FY1000_Q_RX_Buffer.SendData.Pack_0X02_N.Dev_Type;
	PackData->Pack_0X02_N.Dev_ID=FY1000_Q_RX_Buffer.SendData.Pack_0X02_N.Dev_ID;
	PackData->Pack_0X02_N.BackFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_N.BackFlag;


	PackSize =sizeof(FY1000_Pack0X02_N_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X02_N.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X02_N.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 

}




void FY1000_Pack_0X02_F(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X02_F.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X02_F.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X02_F.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X02_F.Head.ConType =0X02;

	PackData->Pack_0X02_F.Head.Lenth =sizeof(FY1000_Pack0X02_F_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������

	PackData->Pack_0X02_F.CtrlFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_F.CtrlFlag;
	PackData->Pack_0X02_F.Dev_Type=FY1000_Q_RX_Buffer.SendData.Pack_0X02_F.Dev_Type;
	PackData->Pack_0X02_F.Dev_ID=FY1000_Q_RX_Buffer.SendData.Pack_0X02_F.Dev_ID;
	PackData->Pack_0X02_F.BackFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_F.BackFlag;

	PackData->Pack_0X02_F.ComTolNum=FY1000_Q_RX_Buffer.SendData.Pack_0X02_F.ComTolNum;
	PackData->Pack_0X02_F.ComSucNum=FY1000_Q_RX_Buffer.SendData.Pack_0X02_F.ComSucNum;
	PackData->Pack_0X02_F.ComFauNum=FY1000_Q_RX_Buffer.SendData.Pack_0X02_F.ComFauNum;

	PackSize =sizeof(FY1000_Pack0X02_F_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X02_F.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X02_F.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 

}



void FY1000_Pack_0X02_A1(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X02_D1.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X02_D1.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X02_D1.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X02_D1.Head.ConType =0X02;

	PackData->Pack_0X02_D1.Head.Lenth =sizeof(FY1000_Pack0X02_D1_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0X02_D1.CtrlFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.CtrlFlag;
	PackData->Pack_0X02_D1.Dev_Type=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Dev_Type;
	PackData->Pack_0X02_D1.Dev_ID=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Dev_ID;
	PackData->Pack_0X02_D1.BackFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.BackFlag;


	
	PackData->Pack_0X02_D1.Input_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Input_Temp;
	PackData->Pack_0X02_D1.Output_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Output_Temp;
	
	PackData->Pack_0X02_D1.Instant_Current=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Instant_Current;
	PackData->Pack_0X02_D1.Instant_Current_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Instant_Current_Unit;
	
	PackData->Pack_0X02_D1.Instant_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Instant_Energy;
	PackData->Pack_0X02_D1.Instant_Energy_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Instant_Energy_Unit;
	
	PackData->Pack_0X02_D1.Total_Current=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Total_Current;
	PackData->Pack_0X02_D1.Total_Current_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Total_Current_Unit;
	
	PackData->Pack_0X02_D1.Total_Code=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Total_Code;
	PackData->Pack_0X02_D1.Total_Code_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Total_Code_Unit;
	
	PackData->Pack_0X02_D1.Total_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Total_Energy;
	PackData->Pack_0X02_D1.Total_Energy_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Total_Energy_Unit;
	
	PackData->Pack_0X02_D1.Work_Time=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Work_Time;
	
	PackData->Pack_0X02_D1.STATE1=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.STATE1;
	PackData->Pack_0X02_D1.STATE2=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.STATE2;


	PackSize =sizeof(FY1000_Pack0X02_D1_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X02_D1.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X02_D1.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 
}




void FY1000_Pack_0X02_A2(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X02_D2.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X02_D2.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X02_D2.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X02_D2.Head.ConType =0X02;

	PackData->Pack_0X02_D2.Head.Lenth =sizeof(FY1000_Pack0X02_D2_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0X02_D2.CtrlFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.CtrlFlag;
	PackData->Pack_0X02_D2.Dev_Type=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Dev_Type;
	PackData->Pack_0X02_D2.Dev_ID=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Dev_ID;
	PackData->Pack_0X02_D2.BackFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.BackFlag;

	
	PackData->Pack_0X02_D2.Input_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Input_Temp;
	PackData->Pack_0X02_D2.Output_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Output_Temp;
	
	PackData->Pack_0X02_D2.Instant_Current=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Instant_Current;
	PackData->Pack_0X02_D2.Instant_Current_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Instant_Current_Unit;
	
	PackData->Pack_0X02_D2.Instant_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Instant_Energy;
	PackData->Pack_0X02_D2.Instant_Energy_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Instant_Energy_Unit;
	
	PackData->Pack_0X02_D2.Total_Current=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Total_Current;
	PackData->Pack_0X02_D2.Total_Current_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Total_Current_Unit;
	
	PackData->Pack_0X02_D2.Total_Code=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Total_Code;
	PackData->Pack_0X02_D2.Total_Code_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Total_Code_Unit;
	
	PackData->Pack_0X02_D2.Total_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Total_Energy;
	PackData->Pack_0X02_D2.Total_Energy_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Total_Energy_Unit;
	
	PackData->Pack_0X02_D2.Work_Time=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.Work_Time;
	
	PackData->Pack_0X02_D2.STATE1=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.STATE1;
	PackData->Pack_0X02_D2.STATE2=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D2.STATE2;


	PackSize =sizeof(FY1000_Pack0X02_D2_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X02_D2.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X02_D2.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}





void FY1000_Pack_0X02_A3(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X02_D3.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X02_D3.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X02_D3.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X02_D3.Head.ConType =0X02;

	PackData->Pack_0X02_D3.Head.Lenth =sizeof(FY1000_Pack0X02_D3_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0X02_D3.CtrlFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.CtrlFlag;
	PackData->Pack_0X02_D3.Dev_Type=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Dev_Type;
	PackData->Pack_0X02_D3.Dev_ID=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Dev_ID;
	PackData->Pack_0X02_D3.BackFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.BackFlag;

	
	PackData->Pack_0X02_D3.Set_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Set_Temp;
	PackData->Pack_0X02_D3.Cur_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Cur_Temp;
	PackData->Pack_0X02_D3.Ave_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Ave_Temp;
	PackData->Pack_0X02_D3.Input_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Input_Temp;
	PackData->Pack_0X02_D3.Output_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Output_Temp;
	PackData->Pack_0X02_D3.ValvePosition=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.ValvePosition;
	PackData->Pack_0X02_D3.Cycle_OpTim=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Cycle_OpTim;
	PackData->Pack_0X02_D3.Cycle_OpRat=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Cycle_OpRat;
	PackData->Pack_0X02_D3.Apportion_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Apportion_Energy;
	PackData->Pack_0X02_D3.Face_State=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Face_State;
	PackData->Pack_0X02_D3.Valve_State=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D3.Valve_State;

	PackSize =sizeof(FY1000_Pack0X02_D3_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X02_D3.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X02_D3.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}






void FY1000_Pack_0X02_A4(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X02_D4.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X02_D4.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X02_D4.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X02_D4.Head.ConType =0X02;

	PackData->Pack_0X02_D4.Head.Lenth =sizeof(FY1000_Pack0X02_D4_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0X02_D4.CtrlFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.CtrlFlag;
	PackData->Pack_0X02_D4.Dev_Type=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.Dev_Type;
	PackData->Pack_0X02_D4.Dev_ID=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.Dev_ID;
	PackData->Pack_0X02_D4.BackFlag=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.BackFlag;

	
	PackData->Pack_0X02_D4.ValvePosition=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.ValvePosition;
	PackData->Pack_0X02_D4.Cycle_OpTim=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.Cycle_OpTim;
	PackData->Pack_0X02_D4.Cycle_OpRat=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.Cycle_OpRat;
	PackData->Pack_0X02_D4.Apportion_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.Apportion_Energy;
	PackData->Pack_0X02_D4.Valve_State=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.Valve_State;



	PackSize =sizeof(FY1000_Pack0X02_D4_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X02_D4.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X02_D4.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}

#ifdef Valve_NWK_ENABLE
void FY1000_Pack_0X02_A5(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

    //Э��ͷ Head
	PackData->Pack_0XB0_D5.Head.Start           = FY1000Pro_StartCode;
	PackData->Pack_0XB0_D5.Head.Version         = FY1000Pro_ProtocolCode;
	PackData->Pack_0XB0_D5.Head.SN              = SysPara.Device_SN;			
	PackData->Pack_0XB0_D5.Head.ConType         = 0X02;
	PackData->Pack_0XB0_D5.Head.Lenth           = sizeof(FY1000_Pack0XB0_D5_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0XB0_D5.CtrlFlag             = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.CtrlFlag;
	PackData->Pack_0XB0_D5.Dev_Type             = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Dev_Type;
	PackData->Pack_0XB0_D5.Dev_ID               = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Dev_ID;
	PackData->Pack_0XB0_D5.BackFlag             = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.BackFlag;

	//����������
	PackData->Pack_0XB0_D5.Input_Temp           = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Input_Temp;
	PackData->Pack_0XB0_D5.Output_Temp          = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Output_Temp;
	PackData->Pack_0XB0_D5.EnterWater_Pressure  = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.EnterWater_Pressure;
	PackData->Pack_0XB0_D5.ReturnWater_Pressure = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.ReturnWater_Pressure;
	PackData->Pack_0XB0_D5.Room_Temp            = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Room_Temp;
	PackData->Pack_0XB0_D5.Current_Valve_Open   = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Current_Valve_Open;
	PackData->Pack_0XB0_D5.SetValue_Open        = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.SetValue_Open;
	PackData->Pack_0XB0_D5.Temp_Diff            = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Temp_Diff;
	PackData->Pack_0XB0_D5.ReturnTemp_Set       = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.ReturnTemp_Set;
	PackData->Pack_0XB0_D5.PressureDiff_Set     = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.PressureDiff_Set;
    PackData->Pack_0XB0_D5.Error                = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Error;
	PackData->Pack_0XB0_D5.Software_Version     = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Software_Version;
	PackData->Pack_0XB0_D5.Run_Mode             = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Run_Mode;
	PackData->Pack_0XB0_D5.Address              = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Address;
	PackData->Pack_0XB0_D5.Motor_Steering       = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Motor_Steering;
    PackData->Pack_0XB0_D5.Adjust_Switch        = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Adjust_Switch;
	PackData->Pack_0XB0_D5.Adjust_Tigger        = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Adjust_Tigger;
	PackData->Pack_0XB0_D5.Dc_Motor_Speed       = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Dc_Motor_Speed;

    
    //У���
	PackSize = sizeof(FY1000_Pack0XB0_D5_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0XB0_D5.Check = SUMCheck_Input((INT8U*)PackData,PackSize);
    
    //END
	PackData->Pack_0XB0_D5.End = FY1000Pro_EndCode;

	PackSize += 2;
	PORT->OutputPackSize = PackSize;
	PORT->PackSendFlag   = ENABLE; 


}
#endif

INT8U  FY1000_Pack_0X03(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if ( PackData->Pack_0X03.Head.SN ==SysPara.Device_SN)
	{
		BackVal =0X00;
		
	}
	return BackVal;
}


void FY1000_Pack_0X04(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X04.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X04.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X04.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X04.Head.ConType =0X04;

	PackData->Pack_0X04.Head.Lenth =sizeof(FY1000_Pack0X04_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0X04.State=FY1000_Q_RX_Buffer.SendData.Pack_0X04.State;

	PackSize =sizeof(FY1000_Pack0X04_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X04.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X04.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE;


}






INT8U  FY1000_Pack_0X05(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;
	if ( PackData->Pack_0X05.Head.SN ==SysPara.Device_SN)
	{
		if((PackData->Pack_0X05.CtrlFlag ==0X00)||(PackData->Pack_0X05.CtrlFlag ==0XAA))		//ȫ�ֿ��Ʊ�־��Ч���ж�
		{
			if( PackData->Pack_0X05.Dev_Type ==Valve_U)
			{
				if((PackData->Pack_0X05.Set_TCtrlFg ==0X00)||(PackData->Pack_0X05.Set_TCtrlFg ==0XAA))	//�¶��趨���Ʊ�־��Ч���ж�
				{
					if((PackData->Pack_0X05.LimtTE_Flag ==0X00)||(PackData->Pack_0X05.LimtTE_Flag ==0XAA))	//�����¶��趨��־��Ч���ж�
					{

						/*�¶��趨��־��Ч������¶�������ֵ�����ж�*/
						if(PackData->Pack_0X05.Set_TCtrlFg ==0X00)
						{
							BackVal =0X00;
						}
						else if(PackData->Pack_0X05.Set_TCtrlFg ==0XAA)						
						{
							if(( PackData->Pack_0X05.Set_Temp >=1000)&&(PackData->Pack_0X05.Set_Temp <=3000))
							{
								BackVal =0X00;
							}
							else
							{
								BackVal =0X02;
								return BackVal;
							}
						}

						/*�����¶��趨��־��Ч������¶�������ֵ�����ж�*/
						if(PackData->Pack_0X05.LimtTE_Flag ==0X00)	
						{
							BackVal =0X00;
						}
						else if(PackData->Pack_0X05.LimtTE_Flag ==0XAA)						
						{
							if(( PackData->Pack_0X05.LimtTE_Value >=2500))		//�����¶�����ֵ
							{
								BackVal =0X00;
							}
							else
							{
								BackVal =0X02;
								return BackVal;
							}
						}
					}
				}
			}
		}
	}
	return BackVal;
}



void FY1000_Pack_0X06(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X06.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X06.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X06.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X06.Head.ConType =0X06;

	PackData->Pack_0X06.Head.Lenth =sizeof(FY1000_Pack0X06_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	

	PackData->Pack_0X06.State=FY1000_Q_RX_Buffer.SendData.Pack_0X06.State;

	PackSize =sizeof(FY1000_Pack0X06_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X06.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X06.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}







INT8U  FY1000_Pack_0X07(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;
	if ( PackData->Pack_0X07.Head.SN ==SysPara.Device_SN)
	{
		if((PackData->Pack_0X07.CycBot_Energy_Unit ==kW_h)||(PackData->Pack_0X07.CycBot_Energy_Unit ==MW_h))		//ȫ�ֿ��Ʊ�־��Ч���ж�
		{
			if(
                (PackData->Pack_0X07.Dev_Type ==Meter_B)
#ifdef Meter_H_ENABLE
            || (PackData->Pack_0X07.Dev_Type ==Meter_H)
#endif
            )
			{
				BackVal =0X00;
			}
		}
	}
	return BackVal;
}













void FY1000_Pack_0X08(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X08.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X08.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X08.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X08.Head.ConType =0X08;

	PackData->Pack_0X08.Head.Lenth =sizeof(FY1000_Pack0X08_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	

	PackData->Pack_0X08.State=FY1000_Q_RX_Buffer.SendData.Pack_0X08.State;

	PackSize =sizeof(FY1000_Pack0X08_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X08.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X08.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}






INT8U  FY1000_Pack_0X09(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if (PackData->Pack_0X09.Head.SN ==SysPara.Device_SN)
	{
		if(( PackData->Pack_0X09.CtrlDemand==0X0A)||( PackData->Pack_0X09.CtrlDemand==0XA0))
		{
			BackVal =0X00;
		}
	}
	return BackVal;
}





void FY1000_Pack_0X0A(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X0A.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X0A.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X0A.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X0A.Head.ConType =0X0A;

	PackData->Pack_0X0A.Head.Lenth =sizeof(FY1000_Pack0X0A_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	

	PackData->Pack_0X0A.State=FY1000_Q_RX_Buffer.SendData.Pack_0X0A.State;

	PackSize =sizeof(FY1000_Pack0X0A_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X0A.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X0A.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}




INT8U  FY1000_Pack_0X0B(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;
	if (PackData->Pack_0X0B.Head.SN ==SysPara.Device_SN)
	{
		if(( PackData->Pack_0X0B.CtrlDemand==0X55)||(PackData->Pack_0X0B.CtrlDemand==0XAA)||(PackData->Pack_0X0B.CtrlDemand==0XFF))
		{
			BackVal =0X00;
		}
	}
	
	return BackVal;
}



void FY1000_Pack_0X0C(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X0C.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X0C.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X0C.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X0C.Head.ConType =0X0C;

	PackData->Pack_0X0C.Head.Lenth =sizeof(FY1000_Pack0X0C_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	

	PackData->Pack_0X0C.State=FY1000_Q_RX_Buffer.SendData.Pack_0X0C.State;

	PackSize =sizeof(FY1000_Pack0X0C_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X0C.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X0C.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}









INT8U  FY1000_Pack_0X0D(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if (PackData->Pack_0X0D.Head.SN ==SysPara.Device_SN)
	{
		if(( PackData->Pack_0X0D.CtrlDemand==0XAA)||(PackData->Pack_0X0D.CtrlDemand==0X00))//���������ж� 
		{
			if((PackData->Pack_0X0D.ForceFlag==0XAA)||(PackData->Pack_0X0D.ForceFlag==0X00)) //ǿ��״̬�ж�
			{
				if(
				(PackData->Pack_0X0D.DevType==Valve_U)
				||(PackData->Pack_0X0D.DevType==Valve_UH)
				
#ifdef 		Meter_DDF2_ENABLE		
				||(PackData->Pack_0X0D.DevType==Meter_DDF2)
#endif 				
				)	//�豸�����ж�
				{
					BackVal =0X00;
				}
			}
		}
	}
	return BackVal;
}





void FY1000_Pack_0X0E(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X0E.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X0E.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X0E.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X0E.Head.ConType =0X0E;

	PackData->Pack_0X0E.Head.Lenth =sizeof(FY1000_Pack0X0E_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0X0E.DevType=FY1000_Q_RX_Buffer.SendData.Pack_0X0E.DevType;
	PackData->Pack_0X0E.DevID=FY1000_Q_RX_Buffer.SendData.Pack_0X0E.DevID;
	PackData->Pack_0X0E.State=FY1000_Q_RX_Buffer.SendData.Pack_0X0E.State;

	PackSize =sizeof(FY1000_Pack0X0E_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X0E.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X0E.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}


INT8U Heartbeatnum =0;

void FY1000_Pack_0X11(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X11.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X11.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X11.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X11.Head.ConType =0X11;

	PackData->Pack_0X11.Head.Lenth =sizeof(FY1000_Pack0X11_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������

	Heartbeatnum +=1;

	PackData->Pack_0X11.Num =Heartbeatnum;
	
	PackSize =sizeof(FY1000_Pack0X11_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X11.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X11.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}




INT8U  FY1000_Pack_0X12(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if ( PackData->Pack_0X12.Head.SN ==SysPara.Device_SN)
	{
		BackVal =0X00;
	}
	return BackVal;
}


/*
��վ��ʱ
*/
INT8U  FY1000_Pack_0X13(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if ( PackData->Pack_0X13.Head.SN ==SysPara.Device_SN)
	{
		if(( PackData->Pack_0X13.Year !=0)&&( PackData->Pack_0X13.Month !=0)&&(PackData->Pack_0X13.Day !=0))
		{
			BackVal =0X00;
		}
		else
		{
			BackVal =0X02;
		}
	}
	return BackVal;
}




void FY1000_Pack_0X14(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X14.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X14.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X14.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X14.Head.ConType =0X14;

	PackData->Pack_0X14.Head.Lenth =sizeof(FY1000_Pack0X14_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	

	PackData->Pack_0X14.State=FY1000_Q_RX_Buffer.SendData.Pack_0X14.State;

	PackSize =sizeof(FY1000_Pack0X14_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X14.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X14.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}


/*
��վ���ͼ̵�����������
*/
INT8U  FY1000_Pack_0X15(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if ( PackData->Pack_0X15.Head.SN ==SysPara.Device_SN)
	{
		if(( PackData->Pack_0X15.CMD ==0XAA)||( PackData->Pack_0X15.CMD ==0X00))
		{
			BackVal =0X00;
		}
		else
		{
			BackVal =0X02;
		}
	}
	return BackVal;
}


void FY1000_Pack_0X16(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X16.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X16.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X16.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X16.Head.ConType =0X16;

	PackData->Pack_0X16.Head.Lenth =sizeof(FY1000_Pack0X16_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	

	PackData->Pack_0X16.State=FY1000_Q_RX_Buffer.SendData.Pack_0X16.State;


	PackSize =sizeof(FY1000_Pack0X16_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X16.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X16.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}












INT8U  FY1000_Pack_0X17(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if (PackData->Pack_0X17.Head.SN ==SysPara.Device_SN)
	{
		if(( PackData->Pack_0X17.CtrlDemand==0XAA)||(PackData->Pack_0X17.CtrlDemand==0X00))//���Ʊ�־
		{
			if( Valve_U==PackData->Pack_0X17.DevType)
			{
				BackVal =0X00;
			}
		}
	}
	return BackVal;
}




void FY1000_Pack_0X18(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X18.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X18.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X18.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X18.Head.ConType =0X18;

	PackData->Pack_0X18.Head.Lenth =sizeof(FY1000_Pack0X18_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0X18.DevType=FY1000_Q_RX_Buffer.SendData.Pack_0X18.DevType;
	PackData->Pack_0X18.DevID=FY1000_Q_RX_Buffer.SendData.Pack_0X18.DevID;
	PackData->Pack_0X18.State=FY1000_Q_RX_Buffer.SendData.Pack_0X18.State;

	PackSize =sizeof(FY1000_Pack0X18_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X18.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X18.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}



INT8U  FY1000_Pack_0X19(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if (PackData->Pack_0X19.Head.SN ==SysPara.Device_SN)
	{

		if( Valve_U==PackData->Pack_0X19.DevType)
		{
			BackVal =0X00;
		}
	}
	return BackVal;
}





void FY1000_Pack_0X1A(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X1A.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X1A.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X1A.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X1A.Head.ConType =0X1A;

	PackData->Pack_0X1A.Head.Lenth =sizeof(FY1000_Pack0X1A_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0X1A.DevType=FY1000_Q_RX_Buffer.SendData.Pack_0X1A.DevType;
	PackData->Pack_0X1A.DevID=FY1000_Q_RX_Buffer.SendData.Pack_0X1A.DevID;
	PackData->Pack_0X1A.State=FY1000_Q_RX_Buffer.SendData.Pack_0X1A.State;

	PackSize =sizeof(FY1000_Pack0X1A_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X1A.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X1A.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 
	
}



#ifdef Valve_NWK_ENABLE
void FY1000_Pack_0X1C(UART_RBC_Stru* PORT)
{

	FY1000_Send_Uni* PackData           = (FY1000_Send_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X1C.Head.Start      = FY1000Pro_StartCode;
	PackData->Pack_0X1C.Head.Version    = FY1000Pro_ProtocolCode;
	PackData->Pack_0X1C.Head.SN         = SysPara.Device_SN;			
	PackData->Pack_0X1C.Head.Lenth      = sizeof(FY1000_Pack0X1B_NWK_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
    PackData->Pack_0X1A.Head.ConType    = 0X1C;
    
	PackData->Pack_0X1C.DevType         = FY1000_Q_RX_Buffer.SendData.Pack_0X1C.DevType;
	PackData->Pack_0X1C.DevID           = FY1000_Q_RX_Buffer.SendData.Pack_0X1C.DevID;
    
	PackData->Pack_0X1C.Register_Addr   = FY1000_Q_RX_Buffer.SendData.Pack_0X1C.Register_Addr;
    PackData->Pack_0X1C.data            = FY1000_Q_RX_Buffer.SendData.Pack_0X1C.data;

	PackSize = sizeof(FY1000_Pack0X1B_NWK_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X1C.Check           = SUMCheck_Input((INT8U*)PackData, PackSize);
	PackData->Pack_0X1C.End             = FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize = PackSize;
	PORT->PackSendFlag   = ENABLE; 
	
}
#endif



INT8U  FY1000_Pack_0X41(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if( PackData->Pack_0X41.Port !=0)
	{
		BackVal =0X00;
	}
	return BackVal;
}


INT8U  FY1000_Pack_0X43(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if ( PackData->Pack_0X43.Port !=0)
	{
		BackVal =0X00;
		
	}
	return BackVal;
}












/*
	��0X40���ɼ�������GPRSģ�����վIP��ַ��������
	
*/
void FY1000_Pack_0X40(UART_RBC_Stru* PORT)
{

	
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0X40.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0X40.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0X40.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0X40.Head.ConType =0X40;

	PackData->Pack_0X40.Head.Lenth =sizeof(FY1000_Pack0X40_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������

	PackData->Pack_0X40.COMFlag =FY1000_Q_RX_Buffer.SendData.Pack_0X40.COMFlag;
	PackData->Pack_0X40.IP1=FY1000_Q_RX_Buffer.SendData.Pack_0X40.IP1;
	PackData->Pack_0X40.IP2=FY1000_Q_RX_Buffer.SendData.Pack_0X40.IP2;
	PackData->Pack_0X40.IP3=FY1000_Q_RX_Buffer.SendData.Pack_0X40.IP3;
	PackData->Pack_0X40.IP4=FY1000_Q_RX_Buffer.SendData.Pack_0X40.IP4;
	PackData->Pack_0X40.PortNum=FY1000_Q_RX_Buffer.SendData.Pack_0X40.PortNum;

	
	PackSize =sizeof(FY1000_Pack0X40_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0X40.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0X40.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}






void FY1000_Pack_0XB0_F(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0XB0_F.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0XB0_F.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0XB0_F.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0XB0_F.Head.ConType =0XB0;

	PackData->Pack_0XB0_F.Head.Lenth =sizeof(FY1000_Pack0XB0_F_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������

	PackData->Pack_0XB0_F.CtrlFlag=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_F.CtrlFlag;
	PackData->Pack_0XB0_F.Dev_Type=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_F.Dev_Type;
	PackData->Pack_0XB0_F.Dev_ID=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_F.Dev_ID;
	PackData->Pack_0XB0_F.BackFlag=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_F.BackFlag;

	PackData->Pack_0XB0_F.ComTolNum=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_F.ComTolNum;
	PackData->Pack_0XB0_F.ComSucNum=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_F.ComSucNum;
	PackData->Pack_0XB0_F.ComFauNum=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_F.ComFauNum;

	PackSize =sizeof(FY1000_Pack0XB0_F_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0XB0_F.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0XB0_F.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 

}



void FY1000_Pack_0XB0_A1(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0XB0_D1.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0XB0_D1.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0XB0_D1.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0XB0_D1.Head.ConType =0XB0;

	PackData->Pack_0XB0_D1.Head.Lenth =sizeof(FY1000_Pack0XB0_D1_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0XB0_D1.CtrlFlag=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.CtrlFlag;
	PackData->Pack_0XB0_D1.Dev_Type=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Dev_Type;
	PackData->Pack_0XB0_D1.Dev_ID=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Dev_ID;
	PackData->Pack_0XB0_D1.BackFlag=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.BackFlag;


	
	PackData->Pack_0XB0_D1.Input_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Input_Temp;
	PackData->Pack_0XB0_D1.Output_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Output_Temp;
	
	PackData->Pack_0XB0_D1.Instant_Current=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Instant_Current;
	PackData->Pack_0XB0_D1.Instant_Current_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Instant_Current_Unit;
	
	PackData->Pack_0XB0_D1.Instant_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy;
	PackData->Pack_0XB0_D1.Instant_Energy_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy_Unit;
	
	PackData->Pack_0XB0_D1.Total_Current=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Total_Current;
	PackData->Pack_0XB0_D1.Total_Current_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Total_Current_Unit;
	
	PackData->Pack_0XB0_D1.Total_Code=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Total_Code;
	PackData->Pack_0XB0_D1.Total_Code_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Total_Code_Unit;
	
	PackData->Pack_0XB0_D1.Total_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Total_Energy;
	PackData->Pack_0XB0_D1.Total_Energy_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Total_Energy_Unit;
	
	PackData->Pack_0XB0_D1.Work_Time=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Work_Time;
	
	PackData->Pack_0XB0_D1.STATE1=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.STATE1;
	PackData->Pack_0XB0_D1.STATE2=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.STATE2;


	PackSize =sizeof(FY1000_Pack0XB0_D1_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0XB0_D1.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0XB0_D1.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 
}




void FY1000_Pack_0XB0_A2(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0XB0_D2.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0XB0_D2.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0XB0_D2.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0XB0_D2.Head.ConType =0XB0;

	PackData->Pack_0XB0_D2.Head.Lenth =sizeof(FY1000_Pack0XB0_D2_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0XB0_D2.CtrlFlag=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.CtrlFlag;
	PackData->Pack_0XB0_D2.Dev_Type=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Dev_Type;
	PackData->Pack_0XB0_D2.Dev_ID=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Dev_ID;
	PackData->Pack_0XB0_D2.BackFlag=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.BackFlag;

	
	PackData->Pack_0XB0_D2.Input_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Input_Temp;
	PackData->Pack_0XB0_D2.Output_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Output_Temp;
	
	PackData->Pack_0XB0_D2.Instant_Current=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Instant_Current;
	PackData->Pack_0XB0_D2.Instant_Current_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Instant_Current_Unit;
	
	PackData->Pack_0XB0_D2.Instant_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy;
	PackData->Pack_0XB0_D2.Instant_Energy_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Instant_Energy_Unit;
	
	PackData->Pack_0XB0_D2.Total_Current=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Total_Current;
	PackData->Pack_0XB0_D2.Total_Current_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Total_Current_Unit;
	
	PackData->Pack_0XB0_D2.Total_Code=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Total_Code;
	PackData->Pack_0XB0_D2.Total_Code_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Total_Code_Unit;
	
	PackData->Pack_0XB0_D2.Total_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Total_Energy;
	PackData->Pack_0XB0_D2.Total_Energy_Unit=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Total_Energy_Unit;
	
	PackData->Pack_0XB0_D2.Work_Time=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.Work_Time;
	
	PackData->Pack_0XB0_D2.STATE1=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.STATE1;
	PackData->Pack_0XB0_D2.STATE2=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D2.STATE2;


	PackSize =sizeof(FY1000_Pack0XB0_D2_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0XB0_D2.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0XB0_D2.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}





void FY1000_Pack_0XB0_A3(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0XB0_D3.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0XB0_D3.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0XB0_D3.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0XB0_D3.Head.ConType =0XB0;

	PackData->Pack_0XB0_D3.Head.Lenth =sizeof(FY1000_Pack0XB0_D3_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0XB0_D3.CtrlFlag=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.CtrlFlag;
	PackData->Pack_0XB0_D3.Dev_Type=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Dev_Type;
	PackData->Pack_0XB0_D3.Dev_ID=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Dev_ID;
	PackData->Pack_0XB0_D3.BackFlag=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.BackFlag;

	
	PackData->Pack_0XB0_D3.Set_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Set_Temp;
	PackData->Pack_0XB0_D3.Cur_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Cur_Temp;
	PackData->Pack_0XB0_D3.Ave_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Ave_Temp;
	PackData->Pack_0XB0_D3.Input_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Input_Temp;
	PackData->Pack_0XB0_D3.Output_Temp=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Output_Temp;
	PackData->Pack_0XB0_D3.ValvePosition=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.ValvePosition;
	PackData->Pack_0XB0_D3.Cycle_OpTim=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Cycle_OpTim;
	PackData->Pack_0XB0_D3.Cycle_OpRat=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Cycle_OpRat;
	PackData->Pack_0XB0_D3.Apportion_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Apportion_Energy;
	PackData->Pack_0XB0_D3.Face_State=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Face_State;
	PackData->Pack_0XB0_D3.Valve_State=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D3.Valve_State;


	PackSize =sizeof(FY1000_Pack0XB0_D3_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0XB0_D3.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0XB0_D3.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}




void FY1000_Pack_0XB0_A4(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0XB0_D4.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0XB0_D4.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0XB0_D4.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0XB0_D4.Head.ConType =0XB0;

	PackData->Pack_0XB0_D4.Head.Lenth =sizeof(FY1000_Pack0XB0_D4_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0XB0_D4.CtrlFlag=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D4.CtrlFlag;
	PackData->Pack_0XB0_D4.Dev_Type=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D4.Dev_Type;
	PackData->Pack_0XB0_D4.Dev_ID=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D4.Dev_ID;
	PackData->Pack_0XB0_D4.BackFlag=FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D4.BackFlag;

	
	PackData->Pack_0XB0_D4.ValvePosition=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.ValvePosition;
	PackData->Pack_0XB0_D4.Cycle_OpTim=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.Cycle_OpTim;
	PackData->Pack_0XB0_D4.Cycle_OpRat=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.Cycle_OpRat;
	PackData->Pack_0XB0_D4.Apportion_Energy=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.Apportion_Energy;
	PackData->Pack_0XB0_D4.Valve_State=FY1000_Q_RX_Buffer.SendData.Pack_0X02_D4.Valve_State;


	PackSize =sizeof(FY1000_Pack0XB0_D4_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0XB0_D4.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0XB0_D4.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}

#ifdef Valve_NWK_ENABLE

void FY1000_Pack_0XB0_A5(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

    //Э��ͷ Head
	PackData->Pack_0XB0_D5.Head.Start           = FY1000Pro_StartCode;
	PackData->Pack_0XB0_D5.Head.Version         = FY1000Pro_ProtocolCode;
	PackData->Pack_0XB0_D5.Head.SN              = SysPara.Device_SN;			
	PackData->Pack_0XB0_D5.Head.ConType         = 0XB0;
	PackData->Pack_0XB0_D5.Head.Lenth           = sizeof(FY1000_Pack0XB0_D5_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0XB0_D5.CtrlFlag             = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.CtrlFlag;
	PackData->Pack_0XB0_D5.Dev_Type             = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Dev_Type;
	PackData->Pack_0XB0_D5.Dev_ID               = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Dev_ID;
	PackData->Pack_0XB0_D5.BackFlag             = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.BackFlag;

	//����������
	PackData->Pack_0XB0_D5.Input_Temp           = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Input_Temp;
	PackData->Pack_0XB0_D5.Output_Temp          = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Output_Temp;
	PackData->Pack_0XB0_D5.EnterWater_Pressure  = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.EnterWater_Pressure;
	PackData->Pack_0XB0_D5.ReturnWater_Pressure = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.ReturnWater_Pressure;
	PackData->Pack_0XB0_D5.Room_Temp            = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Room_Temp;
	PackData->Pack_0XB0_D5.Current_Valve_Open   = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Current_Valve_Open;
	PackData->Pack_0XB0_D5.SetValue_Open        = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.SetValue_Open;
	PackData->Pack_0XB0_D5.Temp_Diff            = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Temp_Diff;
	PackData->Pack_0XB0_D5.ReturnTemp_Set       = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.ReturnTemp_Set;
	PackData->Pack_0XB0_D5.PressureDiff_Set     = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.PressureDiff_Set;
    PackData->Pack_0XB0_D5.Error                = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Error;
	PackData->Pack_0XB0_D5.Software_Version     = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Software_Version;
	PackData->Pack_0XB0_D5.Run_Mode             = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Run_Mode;
	PackData->Pack_0XB0_D5.Address              = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Address;
	PackData->Pack_0XB0_D5.Motor_Steering       = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Motor_Steering;
    PackData->Pack_0XB0_D5.Adjust_Switch        = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Adjust_Switch;
	PackData->Pack_0XB0_D5.Adjust_Tigger        = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Adjust_Tigger;
	PackData->Pack_0XB0_D5.Dc_Motor_Speed       = FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D5.Dc_Motor_Speed;

    
    //У���
	PackSize = sizeof(FY1000_Pack0XB0_D5_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0XB0_D5.Check = SUMCheck_Input((INT8U*)PackData,PackSize);
    
    //END
	PackData->Pack_0XB0_D5.End = FY1000Pro_EndCode;

	PackSize += 2;
	PORT->OutputPackSize = PackSize;
	PORT->PackSendFlag   = ENABLE; 


}

#endif



/*
 ��0XBA������������ɼ������������ļ�
*/
INT8U  FY1000_Pack_0XBA(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if ( PackData->Pack_0XBA.Head.SN ==SysPara.Device_SN)
	{

		if((1==PackData->Pack_0XBA.EOH )||(2 ==PackData->Pack_0XBA.EOH ))
		{
			BackVal =0X00;
		}
	}
	return BackVal;
}



/*
 ��0XBB������������ɼ������������ļ�
*/
INT8U  FY1000_Pack_0XBB(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if ( PackData->Pack_0XBB.Head.SN ==SysPara.Device_SN)
	{
		BackVal =0X00;
	}
	return BackVal;
}


/*
 ��0XBD��
*/
INT8U  FY1000_Pack_0XBD(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if ( PackData->Pack_0XBD.Head.SN ==SysPara.Device_SN)
	{
		BackVal =0X00;
	}
	return BackVal;
}






/*
	(0XBF���ɼ����Զ��ϴ��豸����ʧ��/ͨ�Ŵ��� ��Ϣ

*/
void FY1000_Pack_0XBF(UART_RBC_Stru* PORT)
{

	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_0XBF.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0XBF.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0XBF.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0XBF.Head.ConType =0XBF;

	PackData->Pack_0XBF.Head.Lenth =sizeof(FY1000_Pack0XBF_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������

	
	PackData->Pack_0XBF.NUM =FY1000_Q_RX_Buffer.SendData.Pack_0XBF.NUM;
	PackData->Pack_0XBF.Ack=FY1000_Q_RX_Buffer.SendData.Pack_0XBF.Ack;
	
	PackSize =sizeof(FY1000_Pack0XBF_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0XBF.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0XBF.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}


/*
	(0XBC���ɼ�������汾��Ӧ��

*/
void FY1000_Pack_0XBC(UART_RBC_Stru* PORT)
{

	FY1000_Send_Uni* PackData =(FY1000_Send_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize = 0;

	PackData->Pack_0XBC.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0XBC.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0XBC.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0XBC.Head.ConType =0XBC;

	PackData->Pack_0XBC.Head.Lenth =sizeof(FY1000_Pack0XBC_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0XBC.Version = SYSTEM_VERSION;
	
	PackSize =sizeof(FY1000_Pack0XBC_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0XBC.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0XBC.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}



/*
	(0XBF���ɼ����ļ�����Ӧ��

*/
void FY1000_Pack_0XBE(UART_RBC_Stru* PORT)
{

	FY1000_Send_Uni* PackData =(FY1000_Send_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize = 0;

	PackData->Pack_0XBE.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0XBE.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0XBE.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0XBE.Head.ConType =0XBE;

	PackData->Pack_0XBE.Head.Lenth =sizeof(FY1000_Pack0XBE_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	
	PackData->Pack_0XBE.RESULT = FY1000_Q_RX_Buffer.SendData.Pack_0XBE.RESULT;

	PackSize =sizeof(FY1000_Pack0XBE_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0XBE.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0XBE.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}






/*
49.	��0XFE���ɼ�������ע����Ϣ����

*/
void FY1000_Pack_0XFE(UART_RBC_Stru* PORT)
{

	FY1000_Send_Uni* PackData =(FY1000_Send_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize = 0;

	PackData->Pack_0XFE.Head.Start =FY1000Pro_StartCode;
	PackData->Pack_0XFE.Head.Version =FY1000Pro_ProtocolCode;
	PackData->Pack_0XFE.Head.SN =SysPara.Device_SN;			

	PackData->Pack_0XFE.Head.ConType =0XFE;

	PackData->Pack_0XFE.Head.Lenth =sizeof(FY1000_Pack0XFE_Stru)-FY1000Pro_HeadSize-2;//ʵ����Ч����������
	

	PackSize =sizeof(FY1000_Pack0XFE_Stru)-2; //У�����ݳ��ȼ���
	PackData->Pack_0XFE.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_0XFE.End =FY1000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


}




/*
 ��0XFF������������ע��ɹ����ݰ�
*/
INT8U  FY1000_Pack_0XFF(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;
	
	if ( PackData->Pack_0XFF.Head.SN ==SysPara.Device_SN)
	{
		BackVal =0X00;
	}
	return BackVal;
}


#ifdef Valve_NWK_ENABLE
INT8U  FY1000_UnPack_0X1B(UART_RBC_Stru* PORT)
{
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X01;

	if (PackData->Pack_0X1B.Head.SN ==SysPara.Device_SN)
	{
		if( ( PackData->Pack_0X1B.Register_Addr==12)||( PackData->Pack_0X1B.Register_Addr==14)||\
            ( PackData->Pack_0X1B.Register_Addr==16)||( PackData->Pack_0X1B.Register_Addr==18)||\
            ( PackData->Pack_0X1B.Register_Addr==22)||( PackData->Pack_0X1B.Register_Addr==23)||\
            ( PackData->Pack_0X1B.Register_Addr==24)||( PackData->Pack_0X1B.Register_Addr==25)||\
            ( PackData->Pack_0X1B.Register_Addr==26)||( PackData->Pack_0X1B.Register_Addr==27) )
		{
			BackVal =0X00;
		}
	}
	return BackVal;
}
#endif

//INT8U FY1000_UnPack_0X1B(UART_RBC_Stru* Ctrl_Point)
//{
//    unsigned short CRC16 = 0xFF;	//�����־
//    UINT8 CRC_H = 0;
//    UINT8 CRC_L = 0;

//    //NWK_Pack_Uni* Packin =(NWK_Pack_Uni*)Ctrl_Point->InputPack;	//ָ��任


//    CRC16 = crc_16_modbus((const unsigned char*)Ctrl_Point->InputPack, (unsigned short) 6);

//    CRC_L = CRC16 >> 8;
//    CRC_H = CRC16 & 0x00FF;

//    //CheckFlg =SUMCheck_Check(((INT8U*)Ctrl_Point->InputPack), DataSize);

//    if(CRC_H != Ctrl_Point->InputPack[6] || CRC_L != Ctrl_Point->InputPack[7])//У������˳�����
//    {
//        CRC16 = 0;
//    }
//    
//    return	CRC16;
//}














/*
�����������ɼ������ͺ�����
��������: INT8U FY1000_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
��������:��Դ�ǿ�Э����շ�����
Ctrl_Point:���տ�����
Protocol: Э����
����ֵ: 0X00 Э������ 0X01 Э�鴦��������� 0XFF Э�鲻����
*/
INT8U FY1000_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
{

	INT8U ErrorFlg =0;
	FY1000_Pack_Uni* PackData =(FY1000_Pack_Uni*)(Ctrl_Point->InputPack);		   	//����ָ�뽻��
//	FY1000_Pack_Uni* PackOUTData =(FY1000_Pack_Uni*)(Ctrl_Point->OutputPack);	    //���ָ�뽻��
	INT8U Proto_RX =Protocol;
	

	switch (Proto_RX)
	{
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
		case 0X01:
		{
			INT8U DevType =DEFUNULL;
			INT32U DevID =0;
			INT16U DevNum =0;
			INT16U UserNum =0;
			ErrorFlg =FY1000_Pack_0X01(Ctrl_Point);
			if(ErrorFlg ==0X00)	//Э����֤�ɹ�
			{
				
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X01...");				
				DevType =PackData->Pack_0X01.Dev_Type;
				DevID =PackData->Pack_0X01.Dev_ID;
				if( PackData->Pack_0X01.CtrlFlag ==0X00)//�������ݽ����ϴ�
				{
					
					if(GetMeters_Num(DevID,(SysDEV_Type)DevType ,&DevNum) ==HAL_OK)	//�豸��ѯ�ɹ�
					{
						
						
						dbg_printf(DEBUG_INFO,"�豸�����ɹ�...");
						dbg_printf(DEBUG_INFO,"�豸�����ύ ����:%d,���:%08lX",DevType,DevID);
					
						UART_TO_FY1000_QueueSend_Stru SendBuffer;
						switch (DevType)
						{

							case Meter_B:	//��Դ188ͨ��Э��
							{

								SendBuffer.SendData.Pack_0X02_D1.CtrlFlag=PackData->Pack_0X01.CtrlFlag;
								SendBuffer.SendData.Pack_0X02_D1.Dev_Type =DevType;
								SendBuffer.SendData.Pack_0X02_D1.Dev_ID =DevID;
								SendBuffer.SendData.Pack_0X02_D1.BackFlag=COMBack_OK;
								
								SendBuffer.SendData.Pack_0X02_D1.Input_Temp =SysDevData[DevNum].Device1.Input_Temp;
								SendBuffer.SendData.Pack_0X02_D1.Output_Temp =SysDevData[DevNum].Device1.Output_Temp;
								
								SendBuffer.SendData.Pack_0X02_D1.Instant_Current =SysDevData[DevNum].Device1.Instant_Current;
								SendBuffer.SendData.Pack_0X02_D1.Instant_Current_Unit =SysDevData[DevNum].Device1.Instant_Current_Unit;
								
								SendBuffer.SendData.Pack_0X02_D1.Instant_Energy =SysDevData[DevNum].Device1.Instant_Energy;
								SendBuffer.SendData.Pack_0X02_D1.Instant_Energy_Unit =SysDevData[DevNum].Device1.Instant_Energy_Unit;
								
								SendBuffer.SendData.Pack_0X02_D1.Total_Current =SysDevData[DevNum].Device1.Total_Current;
								SendBuffer.SendData.Pack_0X02_D1.Total_Current_Unit =SysDevData[DevNum].Device1.Total_Current_Unit;
								
								SendBuffer.SendData.Pack_0X02_D1.Total_Code =SysDevData[DevNum].Device1.Total_Code;
								SendBuffer.SendData.Pack_0X02_D1.Total_Code_Unit =SysDevData[DevNum].Device1.Total_Code_Unit;

								SendBuffer.SendData.Pack_0X02_D1.Total_Energy =SysDevData[DevNum].Device1.Total_Energy;
								SendBuffer.SendData.Pack_0X02_D1.Total_Energy_Unit =SysDevData[DevNum].Device1.Total_Energy_Unit;
								
								SendBuffer.SendData.Pack_0X02_D1.Work_Time =SysDevData[DevNum].Device1.Work_Time;
								
								SendBuffer.SendData.Pack_0X02_D1.STATE1=SysDevData[DevNum].Device1.STATE1;
								SendBuffer.SendData.Pack_0X02_D1.STATE2=SysDevData[DevNum].Device1.STATE2;
								
								FY_1000Send_Code_QInput(&SendBuffer,0X02);
								
							}break;

							
							case Meter_U:	//���������� FY-188
							{
							
								SendBuffer.SendData.Pack_0X02_D1.CtrlFlag=PackData->Pack_0X01.CtrlFlag;
								SendBuffer.SendData.Pack_0X02_D2.Dev_Type =DevType;
								SendBuffer.SendData.Pack_0X02_D2.Dev_ID =DevID;
								SendBuffer.SendData.Pack_0X02_D2.BackFlag=COMBack_OK;
								
								SendBuffer.SendData.Pack_0X02_D2.Input_Temp =SysDevData[DevNum].Device2.Input_Temp;
								SendBuffer.SendData.Pack_0X02_D2.Output_Temp =SysDevData[DevNum].Device2.Output_Temp;
								
								SendBuffer.SendData.Pack_0X02_D2.Instant_Current =SysDevData[DevNum].Device2.Instant_Current;
								SendBuffer.SendData.Pack_0X02_D2.Instant_Current_Unit =SysDevData[DevNum].Device2.Instant_Current_Unit;
								
								SendBuffer.SendData.Pack_0X02_D2.Instant_Energy =SysDevData[DevNum].Device2.Instant_Energy;
								SendBuffer.SendData.Pack_0X02_D2.Instant_Energy_Unit =SysDevData[DevNum].Device2.Instant_Energy_Unit;
								
								SendBuffer.SendData.Pack_0X02_D2.Total_Current =SysDevData[DevNum].Device2.Total_Current;
								SendBuffer.SendData.Pack_0X02_D2.Total_Current_Unit =SysDevData[DevNum].Device2.Total_Current_Unit;
								
								SendBuffer.SendData.Pack_0X02_D2.Total_Code =SysDevData[DevNum].Device2.Total_Code;
								SendBuffer.SendData.Pack_0X02_D2.Total_Code_Unit =SysDevData[DevNum].Device2.Total_Code_Unit;

								SendBuffer.SendData.Pack_0X02_D2.Total_Energy =SysDevData[DevNum].Device2.Total_Energy;
								SendBuffer.SendData.Pack_0X02_D2.Total_Energy_Unit =SysDevData[DevNum].Device2.Total_Energy_Unit;
								
								SendBuffer.SendData.Pack_0X02_D2.Work_Time =SysDevData[DevNum].Device2.Work_Time;
								
								SendBuffer.SendData.Pack_0X02_D2.STATE1=SysDevData[DevNum].Device2.STATE1;
								SendBuffer.SendData.Pack_0X02_D2.STATE2=SysDevData[DevNum].Device2.STATE2;
								FY_1000Send_Code_QInput(&SendBuffer,0X02);
							}break;

							
							
							case Valve_U:	//�û�ͨ�Ϸ�
							{
								SendBuffer.SendData.Pack_0X02_D1.CtrlFlag=PackData->Pack_0X01.CtrlFlag;
								SendBuffer.SendData.Pack_0X02_D3.Dev_Type =DevType;
								SendBuffer.SendData.Pack_0X02_D3.Dev_ID =DevID;
								SendBuffer.SendData.Pack_0X02_D3.BackFlag=COMBack_OK;
								
								SendBuffer.SendData.Pack_0X02_D3.Set_Temp=SysDevData[DevNum].Device3.Set_Temp;
								SendBuffer.SendData.Pack_0X02_D3.Cur_Temp=SysDevData[DevNum].Device3.Cur_Temp;
								SendBuffer.SendData.Pack_0X02_D3.Ave_Temp=SysDevData[DevNum].Device3.Ave_Temp;
								
								SendBuffer.SendData.Pack_0X02_D3.Input_Temp =SysDevData[DevNum].Device3.Input_Temp;
								SendBuffer.SendData.Pack_0X02_D3.Output_Temp =SysDevData[DevNum].Device3.Output_Temp;
								SendBuffer.SendData.Pack_0X02_D3.ValvePosition=SysDevData[DevNum].Device3.ValvePosition;
								SendBuffer.SendData.Pack_0X02_D3.Cycle_OpTim=SysDevData[DevNum].Device3.Cycle_OpTim;
								SendBuffer.SendData.Pack_0X02_D3.Cycle_OpRat=SysDevData[DevNum].Device3.Cycle_OpRat;
								SendBuffer.SendData.Pack_0X02_D3.Apportion_Energy=SysDevData[DevNum].Device3.Apportion_Energy;
								SendBuffer.SendData.Pack_0X02_D3.Face_State=SysDevData[DevNum].Device3.Face_State;
								SendBuffer.SendData.Pack_0X02_D3.Valve_State=SysDevData[DevNum].Device3.Valve_State;

								FY_1000Send_Code_QInput(&SendBuffer,0X02);

							}break;		
							
							case Valve_UH://�û�ͨ�ϻ�ˮ��
							{
								SendBuffer.SendData.Pack_0X02_D1.CtrlFlag=PackData->Pack_0X01.CtrlFlag;
								SendBuffer.SendData.Pack_0X02_D4.Dev_Type =DevType;
								SendBuffer.SendData.Pack_0X02_D4.Dev_ID =DevID;
								SendBuffer.SendData.Pack_0X02_D4.BackFlag=COMBack_OK;

								SendBuffer.SendData.Pack_0X02_D4.ValvePosition=SysDevData[DevNum].Device4.ValvePosition;
								SendBuffer.SendData.Pack_0X02_D4.Cycle_OpTim=SysDevData[DevNum].Device4.Cycle_OpTim;
								SendBuffer.SendData.Pack_0X02_D4.Cycle_OpRat=SysDevData[DevNum].Device4.Cycle_OpRat;
								SendBuffer.SendData.Pack_0X02_D4.Apportion_Energy=SysDevData[DevNum].Device4.Apportion_Energy;
								SendBuffer.SendData.Pack_0X02_D4.Valve_State=SysDevData[DevNum].Device4.Valve_State;

								FY_1000Send_Code_QInput(&SendBuffer,0X02);							

							}break;
			
#ifdef Meter_H_ENABLE
							case Meter_H:	//����188ͨ��Э��
							{
								SendBuffer.SendData.Pack_0X02_D1.CtrlFlag=PackData->Pack_0X01.CtrlFlag;
								SendBuffer.SendData.Pack_0X02_D1.Dev_Type =DevType;
								SendBuffer.SendData.Pack_0X02_D1.Dev_ID =DevID;
								SendBuffer.SendData.Pack_0X02_D1.BackFlag=COMBack_OK;        
								
								SendBuffer.SendData.Pack_0X02_D1.Input_Temp =SysDevData[DevNum].Device5.Input_Temp;
								SendBuffer.SendData.Pack_0X02_D1.Output_Temp =SysDevData[DevNum].Device5.Output_Temp;
								
								SendBuffer.SendData.Pack_0X02_D1.Instant_Current =SysDevData[DevNum].Device5.Instant_Current;
								SendBuffer.SendData.Pack_0X02_D1.Instant_Current_Unit =SysDevData[DevNum].Device5.Instant_Current_Unit;
								
								SendBuffer.SendData.Pack_0X02_D1.Instant_Energy =SysDevData[DevNum].Device5.Instant_Energy;
								SendBuffer.SendData.Pack_0X02_D1.Instant_Energy_Unit =SysDevData[DevNum].Device5.Instant_Energy_Unit;
								
								SendBuffer.SendData.Pack_0X02_D1.Total_Current =SysDevData[DevNum].Device5.Total_Current;
								SendBuffer.SendData.Pack_0X02_D1.Total_Current_Unit =SysDevData[DevNum].Device5.Total_Current_Unit;
								
								SendBuffer.SendData.Pack_0X02_D1.Total_Code =SysDevData[DevNum].Device5.Total_Code;
								SendBuffer.SendData.Pack_0X02_D1.Total_Code_Unit =SysDevData[DevNum].Device5.Total_Code_Unit;

								SendBuffer.SendData.Pack_0X02_D1.Total_Energy =SysDevData[DevNum].Device5.Total_Energy;
								SendBuffer.SendData.Pack_0X02_D1.Total_Energy_Unit =SysDevData[DevNum].Device5.Total_Energy_Unit;
								
								SendBuffer.SendData.Pack_0X02_D1.Work_Time =SysDevData[DevNum].Device5.Work_Time;
								
								SendBuffer.SendData.Pack_0X02_D1.STATE1=SysDevData[DevNum].Device5.STATE1;
								SendBuffer.SendData.Pack_0X02_D1.STATE2=SysDevData[DevNum].Device5.STATE2;
			
								FY_1000Send_Code_QInput(&SendBuffer,0X02);
								
							}break;			
#endif							

                            
#ifdef  Meter_XY_ENABLE								
							case Meter_XY:	//���������� FY-188
							{
								SendBuffer.SendData.Pack_0X02_D1.CtrlFlag=PackData->Pack_0X01.CtrlFlag;
								SendBuffer.SendData.Pack_0X02_D2.Dev_Type =DevType;
								SendBuffer.SendData.Pack_0X02_D2.Dev_ID =DevID;
								SendBuffer.SendData.Pack_0X02_D2.BackFlag=COMBack_OK;
								
								SendBuffer.SendData.Pack_0X02_D2.Input_Temp =SysDevData[DevNum].Device6.Input_Temp;
								SendBuffer.SendData.Pack_0X02_D2.Output_Temp =SysDevData[DevNum].Device6.Output_Temp;
								
								SendBuffer.SendData.Pack_0X02_D2.Instant_Current =SysDevData[DevNum].Device6.Instant_Current;
								SendBuffer.SendData.Pack_0X02_D2.Instant_Current_Unit =SysDevData[DevNum].Device6.Instant_Current_Unit;
								
								SendBuffer.SendData.Pack_0X02_D2.Instant_Energy =SysDevData[DevNum].Device6.Instant_Energy;
								SendBuffer.SendData.Pack_0X02_D2.Instant_Energy_Unit =SysDevData[DevNum].Device6.Instant_Energy_Unit;
								
								SendBuffer.SendData.Pack_0X02_D2.Total_Current =SysDevData[DevNum].Device6.Total_Current;
								SendBuffer.SendData.Pack_0X02_D2.Total_Current_Unit =SysDevData[DevNum].Device6.Total_Current_Unit;
								
								SendBuffer.SendData.Pack_0X02_D2.Total_Code =0;
								SendBuffer.SendData.Pack_0X02_D2.Total_Code_Unit =0X05;

								SendBuffer.SendData.Pack_0X02_D2.Total_Energy =SysDevData[DevNum].Device6.Total_Energy;
								SendBuffer.SendData.Pack_0X02_D2.Total_Energy_Unit =SysDevData[DevNum].Device6.Total_Energy_Unit;
								
								SendBuffer.SendData.Pack_0X02_D2.Work_Time =SysDevData[DevNum].Device6.Work_Time;
								
								SendBuffer.SendData.Pack_0X02_D2.STATE1=SysDevData[DevNum].Device6.STATE1;
								SendBuffer.SendData.Pack_0X02_D2.STATE2=SysDevData[DevNum].Device6.STATE2;
			
								FY_1000Send_Code_QInput(&SendBuffer,0X02);
								
							}break;	
#endif 

                                                        
#ifdef  Meter_HT2X_ENABLE								
                            case Meter_HT2X:  //���������� HT2X
                            case Meter_HT3X:  //���������� HT3X
                            {
                                SendBuffer.SendData.Pack_0X02_D1.CtrlFlag=PackData->Pack_0X01.CtrlFlag;
                                SendBuffer.SendData.Pack_0X02_D2.Dev_Type =DevType;
                                SendBuffer.SendData.Pack_0X02_D2.Dev_ID =DevID;
                                SendBuffer.SendData.Pack_0X02_D2.BackFlag=COMBack_OK;
                                
                                SendBuffer.SendData.Pack_0X02_D2.Input_Temp =SysDevData[DevNum].Device7.Input_Temp;
                                SendBuffer.SendData.Pack_0X02_D2.Output_Temp =SysDevData[DevNum].Device7.Output_Temp;
                                
                                SendBuffer.SendData.Pack_0X02_D2.Instant_Current =SysDevData[DevNum].Device7.Instant_Current;
                                SendBuffer.SendData.Pack_0X02_D2.Instant_Current_Unit =SysDevData[DevNum].Device7.Instant_Current_Unit;
                                
                                SendBuffer.SendData.Pack_0X02_D2.Instant_Energy =SysDevData[DevNum].Device7.Instant_Energy;
                                SendBuffer.SendData.Pack_0X02_D2.Instant_Energy_Unit =SysDevData[DevNum].Device7.Instant_Energy_Unit;
                                
                                SendBuffer.SendData.Pack_0X02_D2.Total_Current =SysDevData[DevNum].Device7.Total_Current;
                                SendBuffer.SendData.Pack_0X02_D2.Total_Current_Unit =SysDevData[DevNum].Device7.Total_Current_Unit;
                                
								SendBuffer.SendData.Pack_0X02_D2.Total_Code =SysDevData[DevNum].Device7.Total_Code;
								SendBuffer.SendData.Pack_0X02_D2.Total_Code_Unit =SysDevData[DevNum].Device7.Total_Code_Unit;


                                SendBuffer.SendData.Pack_0X02_D2.Total_Energy =SysDevData[DevNum].Device7.Total_Energy;
                                SendBuffer.SendData.Pack_0X02_D2.Total_Energy_Unit =SysDevData[DevNum].Device7.Total_Energy_Unit;
                                
                                SendBuffer.SendData.Pack_0X02_D2.Work_Time =SysDevData[DevNum].Device7.Work_Time;
                                
                                SendBuffer.SendData.Pack_0X02_D2.STATE1=SysDevData[DevNum].Device7.STATE1;
                                SendBuffer.SendData.Pack_0X02_D2.STATE2=SysDevData[DevNum].Device7.STATE2;
            
                                FY_1000Send_Code_QInput(&SendBuffer,0X02);
                                
                            }break; 
#endif 
                                                                                    
#ifdef  Meter_BRC_ENABLE								
                            case Meter_BRC:  //���������� BRC
                            {
                                SendBuffer.SendData.Pack_0X02_D1.CtrlFlag=PackData->Pack_0X01.CtrlFlag;
                                SendBuffer.SendData.Pack_0X02_D2.Dev_Type =DevType;
                                SendBuffer.SendData.Pack_0X02_D2.Dev_ID =DevID;
                                SendBuffer.SendData.Pack_0X02_D2.BackFlag=COMBack_OK;
                                
                                SendBuffer.SendData.Pack_0X02_D2.Input_Temp =SysDevData[DevNum].Device8.Input_Temp;
                                SendBuffer.SendData.Pack_0X02_D2.Output_Temp =SysDevData[DevNum].Device8.Output_Temp;
                                
                                SendBuffer.SendData.Pack_0X02_D2.Instant_Current =SysDevData[DevNum].Device8.Instant_Current;
                                SendBuffer.SendData.Pack_0X02_D2.Instant_Current_Unit =SysDevData[DevNum].Device8.Instant_Current_Unit;
                                
                                SendBuffer.SendData.Pack_0X02_D2.Instant_Energy =SysDevData[DevNum].Device8.Instant_Energy;
                                SendBuffer.SendData.Pack_0X02_D2.Instant_Energy_Unit =SysDevData[DevNum].Device8.Instant_Energy_Unit;
                                
                                SendBuffer.SendData.Pack_0X02_D2.Total_Current =SysDevData[DevNum].Device8.Total_Current;
                                SendBuffer.SendData.Pack_0X02_D2.Total_Current_Unit =SysDevData[DevNum].Device8.Total_Current_Unit;
                                
                                SendBuffer.SendData.Pack_0X02_D2.Total_Code =SysDevData[DevNum].Device8.Total_Code;
                                SendBuffer.SendData.Pack_0X02_D2.Total_Code_Unit =SysDevData[DevNum].Device8.Total_Code_Unit;


                                SendBuffer.SendData.Pack_0X02_D2.Total_Energy =SysDevData[DevNum].Device8.Total_Energy;
                                SendBuffer.SendData.Pack_0X02_D2.Total_Energy_Unit =SysDevData[DevNum].Device8.Total_Energy_Unit;
                                
                                SendBuffer.SendData.Pack_0X02_D2.Work_Time =SysDevData[DevNum].Device8.Work_Time;
                                
                                SendBuffer.SendData.Pack_0X02_D2.STATE1=SysDevData[DevNum].Device8.STATE1;
                                SendBuffer.SendData.Pack_0X02_D2.STATE2=SysDevData[DevNum].Device8.STATE2;
            
                                FY_1000Send_Code_QInput(&SendBuffer,0X02);
                                
                            }break; 
#endif 

#ifdef  Meter_DDF2_ENABLE	

							case Meter_DDF2://�û�ͨ�ϻ�ˮ��   ��ͨ  DDF2
							{
								SendBuffer.SendData.Pack_0X02_D4.CtrlFlag=PackData->Pack_0X01.CtrlFlag;
								SendBuffer.SendData.Pack_0X02_D4.Dev_Type =DevType;
								SendBuffer.SendData.Pack_0X02_D4.Dev_ID =DevID;
								SendBuffer.SendData.Pack_0X02_D4.BackFlag=COMBack_OK;

								SendBuffer.SendData.Pack_0X02_D4.ValvePosition=SysDevData[DevNum].Device9.ValvePosition;
								SendBuffer.SendData.Pack_0X02_D4.Cycle_OpTim=0;
								SendBuffer.SendData.Pack_0X02_D4.Cycle_OpRat=0;
								SendBuffer.SendData.Pack_0X02_D4.Apportion_Energy=0;
								SendBuffer.SendData.Pack_0X02_D4.Valve_State=0;

								FY_1000Send_Code_QInput(&SendBuffer,0X02);							

							}break;


#endif

#ifdef  Valve_NWK_ENABLE
							case Valve_NWK://NWK������¥����Ԫ���ڷ�modbusЭ��
							{
                                
                                SendBuffer.SendData.Pack_0XB0_D5.CtrlFlag               = PackData->Pack_0X01.CtrlFlag;
                                SendBuffer.SendData.Pack_0XB0_D5.Dev_Type               = DevType;
                                SendBuffer.SendData.Pack_0XB0_D5.Dev_ID                 = DevID;
                                SendBuffer.SendData.Pack_0XB0_D5.BackFlag               = COMBack_OK;

                                //������  //����С��ģʽ �ֽڵ���
                                
                                SendBuffer.SendData.Pack_0XB0_D5.Input_Temp             = (UINT16)(SysDevData[DevNum].Device11.Input_Temp*100);
                                //dbg_printf(DEBUG_INFO,"Input_Temp  0X%02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.Input_Temp);
                                SendBuffer.SendData.Pack_0XB0_D5.Output_Temp            = (UINT16)(SysDevData[DevNum].Device11.Output_Temp*100);
                                //dbg_printf(DEBUG_INFO,"Output_Temp 0X%02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.Output_Temp);
                                SendBuffer.SendData.Pack_0XB0_D5.EnterWater_Pressure    = (UINT16)(SysDevData[DevNum].Device11.EnterWater_Pressure*100);
                                //dbg_printf(DEBUG_INFO,"EnterWater_Pressure  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.EnterWater_Pressure);
                                SendBuffer.SendData.Pack_0XB0_D5.ReturnWater_Pressure   = (UINT16)(SysDevData[DevNum].Device11.ReturnWater_Pressure*100);
                                //dbg_printf(DEBUG_INFO,"ReturnWater_Pressure  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.ReturnWater_Pressure);
                                SendBuffer.SendData.Pack_0XB0_D5.Room_Temp              = (UINT16)(SysDevData[DevNum].Device11.Room_Temp*100);
                                //dbg_printf(DEBUG_INFO,"Room_Temp  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.Room_Temp);
                                SendBuffer.SendData.Pack_0XB0_D5.Current_Valve_Open     = (UINT16)(SysDevData[DevNum].Device11.Current_Valve_Open*100);
                                //dbg_printf(DEBUG_INFO,"Current_Valve_Open  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.Current_Valve_Open);
                                SendBuffer.SendData.Pack_0XB0_D5.SetValue_Open          = (UINT16)(SysDevData[DevNum].Device11.SetValue_Open*100);
                                //dbg_printf(DEBUG_INFO,"SetValue_Open  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.SetValue_Open);
                                SendBuffer.SendData.Pack_0XB0_D5.Temp_Diff              = (UINT16)(SysDevData[DevNum].Device11.Temp_Diff*100);
                                //dbg_printf(DEBUG_INFO,"Temp_Diff  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.Temp_Diff);
                                SendBuffer.SendData.Pack_0XB0_D5.ReturnTemp_Set         = (UINT16)(SysDevData[DevNum].Device11.ReturnTemp_Set*100);
                                //dbg_printf(DEBUG_INFO,"ReturnTemp_Set  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.ReturnTemp_Set);
                                SendBuffer.SendData.Pack_0XB0_D5.PressureDiff_Set       = (UINT16)(SysDevData[DevNum].Device11.PressureDiff_Set*100);
                                //dbg_printf(DEBUG_INFO,"PressureDiff_Set  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.PressureDiff_Set);
                                
                                
                                SendBuffer.SendData.Pack_0XB0_D5.Error                  = SysDevData[DevNum].Device11.Error;    
                                //dbg_printf(DEBUG_INFO,"Error=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Error);
                                SendBuffer.SendData.Pack_0XB0_D5.Software_Version       = SysDevData[DevNum].Device11.Software_Version; 
                                //dbg_printf(DEBUG_INFO,"Software_Version=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Software_Version);
                                SendBuffer.SendData.Pack_0XB0_D5.Run_Mode               = SysDevData[DevNum].Device11.Run_Mode; 
                                //dbg_printf(DEBUG_INFO,"Run_Mode=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Run_Mode);
                                SendBuffer.SendData.Pack_0XB0_D5.Address                = SysDevData[DevNum].Device11.Address;  
                                //dbg_printf(DEBUG_INFO,"Address=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Address);
                                SendBuffer.SendData.Pack_0XB0_D5.Motor_Steering         = SysDevData[DevNum].Device11.Motor_Steering;   
                                //dbg_printf(DEBUG_INFO,"Motor_Steering=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Motor_Steering);
                                SendBuffer.SendData.Pack_0XB0_D5.Adjust_Switch          = SysDevData[DevNum].Device11.Adjust_Switch;    
                                //dbg_printf(DEBUG_INFO,"Adjust_Switch=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Adjust_Switch);
                                SendBuffer.SendData.Pack_0XB0_D5.Adjust_Tigger          = SysDevData[DevNum].Device11.Adjust_Tigger;    
                                //dbg_printf(DEBUG_INFO,"Adjust_Tigger=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Adjust_Tigger);
                                SendBuffer.SendData.Pack_0XB0_D5.Dc_Motor_Speed         = SysDevData[DevNum].Device11.Dc_Motor_Speed;   
                                //dbg_printf(DEBUG_INFO,"Dc_Motor_Speed=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Dc_Motor_Speed);
                                
                                
								FY_1000Send_Code_QInput(&SendBuffer,0X02);

							}break;
#endif


							default:break;
						}
					}
					else	//�豸��ѯʧ��
					{
					
						UART_TO_FY1000_QueueSend_Stru SendBuffer;
						SendBuffer.SendData.Pack_0X02_D1.CtrlFlag=PackData->Pack_0X01.CtrlFlag;
						SendBuffer.SendData.Pack_0X02_N.Dev_Type =DevType;
						SendBuffer.SendData.Pack_0X02_N.Dev_ID =DevID;
						SendBuffer.SendData.Pack_0X02_N.BackFlag =COMBack_NF;
						FY_1000Send_Code_QInput(&SendBuffer,0X02);
						dbg_printf(DEBUG_INFO,"�豸����ʧ��...");
					}
				}
				
				else if( PackData->Pack_0X01.CtrlFlag ==0XAA)//���²����ն�����
				{
                    //UART_TO_FY1000_QueueSend_Stru SendBuffer;
                    
					if(GetMeters_Num(DevID,(SysDEV_Type)DevType ,&DevNum) ==HAL_OK)	//�ɹ��ҵ��û��豸
					{
						dbg_printf(DEBUG_INFO,"�豸�����ɹ�...");
						dbg_printf(DEBUG_INFO,"�豸�������³��� ����:%d,���:%08lX",DevType,DevID);
						
						switch (DevType)
						{
							
							case Meter_B:	//��Դ188ͨ��Э��
							{
								ClientCH1_Queue_Stru Buffer;
								Buffer.UaComFlg=0XAAAA;							//�첽����ʶ����
								Buffer.Uapack=0X01;
								Buffer.Device =SysDeviceList.Device[DevNum];			//�豸����
								Buffer.SignleCom =SET;							//�ظ�����
								FY_188Send_Code_QInput(&Buffer, 0X01); 				//�������
								
							}break; 	
							
							case Meter_U:	//���������� FY-188
							{
								ClientCH1_Queue_Stru Buffer;
								Buffer.UaComFlg=0XAAAA;							//�첽����ʶ����
								Buffer.Uapack=0X01;
								Buffer.Device =SysDeviceList.Device[DevNum];			//�豸����
								Buffer.SignleCom =SET;							//�ظ�����
								FY_188Send_Code_QInput(&Buffer, 0X01); 				//�������	

							}break;
							
							case Valve_U:	//�û�ͨ�Ϸ�
							{

								ClientCH1_Queue_Stru Buffer;
								
								Buffer.Device =SysDeviceList.Device[DevNum];									//�����豸����
								UserNum =Buffer.Device.UserNum;												//��ȡ�û����
								Buffer.UaComFlg=0XAAAA;													//�첽����ʶ����
								Buffer.Uapack=0X01;
								Buffer.SendData.FY2000Data.Pack_59.Head.DESN=Buffer.Device.Num;						//����DESN
								Buffer.SendData.FY2000Data.Pack_59.LoopTime=CalculateProvideTimeCtrler.ProvideTime;		//���ڹ�ůʱ��
								
								Buffer.SendData.FY2000Data.Pack_59.Apportion_Energy=UserData[UserNum].Apportion_Energy;		//������������/��������
								Buffer.SendData.FY2000Data.Pack_59.Remain_Heat=UserData[UserNum].Remain_Heat;			//����ʣ������
								Buffer.SendData.FY2000Data.Pack_59.Total_Heat=UserData[UserNum].Total_Heat;				//�����û�����������
								
								Buffer.SendData.FY2000Data.Pack_59.ControlType=SysDevData[DevNum].Device3.ControlType;		//�����������
								Buffer.SendData.FY2000Data.Pack_59.ForceCtrlFlg=SysDevData[DevNum].Device3.ForceCtrlFlg; 	//����ǿ�ƿ��Ʊ�־
								
								Buffer.SendData.FY2000Data.Pack_59.Set_TCtrlFg=SysDevData[DevNum].Device3.Set_TCtrlFg;		//ϵͳ�趨�¶ȱ�־
								Buffer.SendData.FY2000Data.Pack_59.Set_Temp=SysDevData[DevNum].Device3.Set_Temp; 		//ϵͳ�趨�¶�
								
								Buffer.SendData.FY2000Data.Pack_59.LimtTE_Flag=SysDevData[DevNum].Device3.LimtTE_Flag;		//ϵͳ�����¶ȱ�־
								Buffer.SendData.FY2000Data.Pack_59.LimtTE_Value=SysDevData[DevNum].Device3.LimtTE_Value; 	//ϵͳ���������¶�
								Buffer.SignleCom =SET;
								FY_2000Send_Code_QInput(&Buffer,59);											//�������	
							}break;		
							
							case Valve_UH://�û�ͨ�ϻ�ˮ��
							{						

								ClientCH1_Queue_Stru Buffer;								
								
								Buffer.Device =SysDeviceList.Device[DevNum];									//�����豸����
								UserNum =Buffer.Device.UserNum;												//��ȡ�û����
								Buffer.UaComFlg=0XAAAA;													//�첽����ʶ����
								Buffer.Uapack=0X01;
								Buffer.SendData.FY2000Data.Pack_59.Head.DESN=Buffer.Device.Num;						//����DESN
								Buffer.SendData.FY2000Data.Pack_59.LoopTime=CalculateProvideTimeCtrler.ProvideTime;		//���ڹ�ůʱ��
								
								Buffer.SendData.FY2000Data.Pack_59.Apportion_Energy=UserData[UserNum].Apportion_Energy;		//������������/��������
								Buffer.SendData.FY2000Data.Pack_59.Remain_Heat=UserData[UserNum].Remain_Heat;			//����ʣ������
								Buffer.SendData.FY2000Data.Pack_59.Total_Heat=UserData[UserNum].Total_Heat;				//����������
								
								Buffer.SendData.FY2000Data.Pack_59.ControlType=SysDevData[DevNum].Device4.ControlType;		//�����������
								Buffer.SendData.FY2000Data.Pack_59.ForceCtrlFlg=SysDevData[DevNum].Device4.ForceCtrlFlg; 	//����ǿ�ƿ��Ʊ�־
								
								Buffer.SendData.FY2000Data.Pack_59.Set_TCtrlFg=0;									//ϵͳ�趨�¶ȱ�־
								Buffer.SendData.FY2000Data.Pack_59.Set_Temp=0; 									//ϵͳ�趨�¶�
								
								Buffer.SendData.FY2000Data.Pack_59.LimtTE_Flag=0;									//ϵͳ�����¶ȱ�־
								Buffer.SendData.FY2000Data.Pack_59.LimtTE_Value=0; 								//ϵͳ���������¶�
								Buffer.SignleCom =SET;
								FY_2000Send_Code_QInput(&Buffer,59);											//�������	

							}break;

#ifdef Meter_H_ENABLE
                            case Meter_H:   //����188ͨ��Э��
                            {
                                ClientCH1_Queue_Stru Buffer;
                                Buffer.UaComFlg=0XAAAA;                             //�첽����ʶ����
                                Buffer.Uapack=0X01;
                                Buffer.Device =SysDeviceList.Device[DevNum];        //�豸����
                                ClientCH1_QueueIN.SignleCom =SET;                   //�ظ�����
                                HZCRL_188Send_Code_QInput(&Buffer, 0X01);           //�������  

                            }break; 
#endif



#ifdef  Meter_XY_ENABLE								
							case Meter_XY:	//���������� XY-188
							{
								ClientCH1_Queue_Stru Buffer;
								Buffer.UaComFlg=0XAAAA;													//�첽����ʶ����
								Buffer.Uapack=0X01;
								Buffer.Device =SysDeviceList.Device[DevNum];                            //�豸����
								Buffer.SignleCom =SET;													//�ظ�����
								XY_188Send_Code_QInput(&Buffer, 0X01);                                  //�������	

							}break;
#endif



#ifdef  Meter_HT2X_ENABLE								
                            case Meter_HT2X:  //���������� HT2X
                            case Meter_HT3X:  //���������� HT3X
                            {
                                ClientCH1_Queue_Stru Buffer;
                                Buffer.UaComFlg=0XAAAA;                                                 //�첽����ʶ����
                                Buffer.Uapack=0X01;
                                Buffer.Device =SysDeviceList.Device[DevNum];                            //�豸����
                                Buffer.SignleCom =SET;                                                  //�ظ�����
                                HT2X_188Send_Code_QInput(&Buffer, 0X01);                                //�������  

                            }break;
#endif



#ifdef  Meter_BRC_ENABLE								
                            case Meter_BRC:  //���������� BRC
                            {
                                ClientCH1_Queue_Stru Buffer;
                                Buffer.UaComFlg=0XAAAA;                                                 //�첽����ʶ����
                                Buffer.Uapack=0X01;
                                Buffer.Device =SysDeviceList.Device[DevNum];                            //�豸����
                                Buffer.SignleCom =SET;                                                  //�ظ�����
                                BRC_188Send_Code_QInput(&Buffer, 0X01);                                 //�������  

                            }break;
#endif


#ifdef  Meter_DDF2_ENABLE
                            case Meter_DDF2:  //���������� BRC
                            {
                                ClientCH1_Queue_Stru Buffer;
                                Buffer.UaComFlg=0XAAAA;                                                 //�첽����ʶ����
                                Buffer.Uapack=0X01;
                                Buffer.Device =SysDeviceList.Device[DevNum];                            //�豸����
                                Buffer.SignleCom =SET;                                                  //�ظ�����
                                DDF2_Send_Code_QInput(&Buffer, 0X01);                                   //�������  

                            }break;

#endif

#ifdef  Valve_NWK_ENABLE
                            case Valve_NWK:  //NWK������¥����Ԫ���ڷ�modbusЭ��
                            {
                                ClientCH1_Queue_Stru Buffer;
                                Buffer.UaComFlg=0XAAAA;                                                 //�첽����ʶ����
                                Buffer.Uapack=0X01;
                                Buffer.Device =SysDeviceList.Device[DevNum];                            //�豸����
                                Buffer.SignleCom =SET;                                                  //�ظ�����
                                NWK_Send_Code_QInput(&Buffer, 0X03);                                    //�������  
                                
                                
//                                //��������������������
//                                SendBuffer.SendData.Pack_0XB0_D5.CtrlFlag               = PackData->Pack_0X01.CtrlFlag;
//                                SendBuffer.SendData.Pack_0XB0_D5.Dev_Type               = DevType;
//                                SendBuffer.SendData.Pack_0XB0_D5.Dev_ID                 = DevID;
//                                SendBuffer.SendData.Pack_0XB0_D5.BackFlag               = COMBack_OK;

//                                //������  //����С��ģʽ �ֽڵ���
//                                
//                                SendBuffer.SendData.Pack_0XB0_D5.Input_Temp             = (UINT16)(SysDevData[DevNum].Device11.Input_Temp*100);
//                                //dbg_printf(DEBUG_INFO,"Input_Temp  0X%02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.Input_Temp);
//                                SendBuffer.SendData.Pack_0XB0_D5.Output_Temp            = (UINT16)(SysDevData[DevNum].Device11.Output_Temp*100);
//                                //dbg_printf(DEBUG_INFO,"Output_Temp 0X%02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.Output_Temp);
//                                SendBuffer.SendData.Pack_0XB0_D5.EnterWater_Pressure    = (UINT16)(SysDevData[DevNum].Device11.EnterWater_Pressure*100);
//                                //dbg_printf(DEBUG_INFO,"EnterWater_Pressure  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.EnterWater_Pressure);
//                                SendBuffer.SendData.Pack_0XB0_D5.ReturnWater_Pressure   = (UINT16)(SysDevData[DevNum].Device11.ReturnWater_Pressure*100);
//                                //dbg_printf(DEBUG_INFO,"ReturnWater_Pressure  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.ReturnWater_Pressure);
//                                SendBuffer.SendData.Pack_0XB0_D5.Room_Temp              = (UINT16)(SysDevData[DevNum].Device11.Room_Temp*100);
//                                //dbg_printf(DEBUG_INFO,"Room_Temp  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.Room_Temp);
//                                SendBuffer.SendData.Pack_0XB0_D5.Current_Valve_Open     = (UINT16)(SysDevData[DevNum].Device11.Current_Valve_Open*100);
//                                //dbg_printf(DEBUG_INFO,"Current_Valve_Open  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.Current_Valve_Open);
//                                SendBuffer.SendData.Pack_0XB0_D5.SetValue_Open          = (UINT16)(SysDevData[DevNum].Device11.SetValue_Open*100);
//                                //dbg_printf(DEBUG_INFO,"SetValue_Open  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.SetValue_Open);
//                                SendBuffer.SendData.Pack_0XB0_D5.Temp_Diff              = (UINT16)(SysDevData[DevNum].Device11.Temp_Diff*100);
//                                //dbg_printf(DEBUG_INFO,"Temp_Diff  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.Temp_Diff);
//                                SendBuffer.SendData.Pack_0XB0_D5.ReturnTemp_Set         = (UINT16)(SysDevData[DevNum].Device11.ReturnTemp_Set*100);
//                                //dbg_printf(DEBUG_INFO,"ReturnTemp_Set  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.ReturnTemp_Set);
//                                SendBuffer.SendData.Pack_0XB0_D5.PressureDiff_Set       = (UINT16)(SysDevData[DevNum].Device11.PressureDiff_Set*100);
//                                //dbg_printf(DEBUG_INFO,"PressureDiff_Set  %02x\r\n\r\n", SendBuffer.SendData.Pack_0XB0_D5.PressureDiff_Set);
//                                
//                                
//                                SendBuffer.SendData.Pack_0XB0_D5.Error                  = SysDevData[DevNum].Device11.Error;    
//                                //dbg_printf(DEBUG_INFO,"Error=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Error);
//                                SendBuffer.SendData.Pack_0XB0_D5.Software_Version       = SysDevData[DevNum].Device11.Software_Version; 
//                                //dbg_printf(DEBUG_INFO,"Software_Version=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Software_Version);
//                                SendBuffer.SendData.Pack_0XB0_D5.Run_Mode               = SysDevData[DevNum].Device11.Run_Mode; 
//                                //dbg_printf(DEBUG_INFO,"Run_Mode=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Run_Mode);
//                                SendBuffer.SendData.Pack_0XB0_D5.Address                = SysDevData[DevNum].Device11.Address;  
//                                //dbg_printf(DEBUG_INFO,"Address=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Address);
//                                SendBuffer.SendData.Pack_0XB0_D5.Motor_Steering         = SysDevData[DevNum].Device11.Motor_Steering;   
//                                //dbg_printf(DEBUG_INFO,"Motor_Steering=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Motor_Steering);
//                                SendBuffer.SendData.Pack_0XB0_D5.Adjust_Switch          = SysDevData[DevNum].Device11.Adjust_Switch;    
//                                //dbg_printf(DEBUG_INFO,"Adjust_Switch=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Adjust_Switch);
//                                SendBuffer.SendData.Pack_0XB0_D5.Adjust_Tigger          = SysDevData[DevNum].Device11.Adjust_Tigger;    
//                                //dbg_printf(DEBUG_INFO,"Adjust_Tigger=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Adjust_Tigger);
//                                SendBuffer.SendData.Pack_0XB0_D5.Dc_Motor_Speed         = SysDevData[DevNum].Device11.Dc_Motor_Speed;   
//                                //dbg_printf(DEBUG_INFO,"Dc_Motor_Speed=%d\r\n",SendBuffer.SendData.Pack_0XB0_D5.Dc_Motor_Speed);
//                                
//                                
//								FY_1000Send_Code_QInput(&SendBuffer,0X02);
                            }break;

#endif


							
							default:break;
						}
					}
					else	//�豸��ѯʧ��
					{
					
						UART_TO_FY1000_QueueSend_Stru SendBuffer;
						
						SendBuffer.SendData.Pack_0X02_D1.CtrlFlag=PackData->Pack_0X01.CtrlFlag;
						SendBuffer.SendData.Pack_0X02_N.Dev_Type =DevType;
						SendBuffer.SendData.Pack_0X02_N.Dev_ID =DevID;
						SendBuffer.SendData.Pack_0X02_N.BackFlag =COMBack_NF;
						FY_1000Send_Code_QInput(&SendBuffer,0X02);
						dbg_printf(DEBUG_INFO,"�豸����ʧ��...");
					}

				}
			}

		}break;
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/

		case 0X03:
		{
			UART_TO_FY1000_QueueSend_Stru SendBuffer;
			ErrorFlg =FY1000_Pack_0X03(Ctrl_Point);
			if(ErrorFlg ==0X00) //Э����֤�ɹ�
			{
				
				SendBuffer.SendData.Pack_0X04.State=COMBack_OK;
				FY_1000Send_Code_QInput(&SendBuffer,0X04);		
				PulseLeaguer_SET(Beep_Ctrler, 1, 10, 10, 20, 0, 0); 			//����ָ�� ��������  ɨ����(tick*X) ���ؿ��   ����	  ���ڼ�����  ��ǰ״̬
				
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X03...");	
				dbg_printf(DEBUG_INFO,"�豸������ʱ����...");	
				
			}
		}break;
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/




		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
	case 0X05:
		{
			INT8U DevType =0;
			INT32U DevID =0;
			
			INT16U DevNum =0;
			INT16U Record =0;
			ErrorFlg =FY1000_Pack_0X05(Ctrl_Point);
			if(ErrorFlg ==0X00)	//Э����֤�ɹ�
			{
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X05...");	
				DevType =PackData->Pack_0X05.Dev_Type;
				DevID =PackData->Pack_0X05.Dev_ID;
				if( PackData->Pack_0X05.CtrlFlag ==0X00)			//��һͨ�Ͽ���������
				{
					UART_TO_FY1000_QueueSend_Stru SendBuffer;
					dbg_printf(DEBUG_INFO,"���豸�¶�����...");
					if(GetMeters_Num(DevID,(SysDEV_Type)DevType ,&DevNum) ==HAL_OK)	//�ɹ��ҵ��û��豸(ͨ�Ͽ�����)
					{
						
						if(PackData->Pack_0X05.Set_TCtrlFg ==0XAA)
						{
							SysDevData[DevNum].Device3.Set_TCtrlFg =0XAA;
							SysDevData[DevNum].Device3.Set_Temp =PackData->Pack_0X05.Set_Temp;
							dbg_printf(DEBUG_INFO,"�豸���:%08lX",DevID);
							dbg_printf(DEBUG_INFO,"�¶�ֵ:%d",SysDevData[DevNum].Device3.Set_Temp);
						}
						else if( PackData->Pack_0X05.Set_TCtrlFg ==0X00)
						{
							SysDevData[DevNum].Device3.Set_TCtrlFg =0XFF;
							dbg_printf(DEBUG_INFO,"ϵͳ�¶�����ȡ��...");
							dbg_printf(DEBUG_INFO,"�豸���:%08lX",DevID);
						}

						if(PackData->Pack_0X05.LimtTE_Flag ==0XAA)
						{
							SysDevData[DevNum].Device3.LimtTE_Flag =0XAA;
							SysDevData[DevNum].Device3.LimtTE_Value =PackData->Pack_0X05.LimtTE_Value;
							dbg_printf(DEBUG_INFO,"�豸���:%08lX",DevID);
							dbg_printf(DEBUG_INFO,"�����¶�ֵ:%d",SysDevData[DevNum].Device3.LimtTE_Value);
						}
						else if( PackData->Pack_0X05.LimtTE_Flag ==0X00)
						{
							SysDevData[DevNum].Device3.LimtTE_Flag =0XFF;
							dbg_printf(DEBUG_INFO,"�����¶�����ȡ��...");
							dbg_printf(DEBUG_INFO,"�豸���:%08lX",DevID);
						}

						
						if(SysDevData_Save(DevNum)==HAL_OK)
						{
							SendBuffer.SendData.Pack_0X06.State =COMBack_OK;
						}
						else
						{
							SendBuffer.SendData.Pack_0X06.State =COMBack_FT;
						}
						FY_1000Send_Code_QInput(&SendBuffer,0X06);
						

					}
					else	//�豸��ѯʧ��
					{
					
						UART_TO_FY1000_QueueSend_Stru SendBuffer;
						SendBuffer.SendData.Pack_0X06.State=COMBack_NF;
						FY_1000Send_Code_QInput(&SendBuffer,0X06);
						dbg_printf(DEBUG_INFO,"�豸��ѯʧ�ܣ������������...");
					}
				}
				else if( PackData->Pack_0X05.CtrlFlag ==0XAA)//����ͨ�Ͽ�����ͳһ�����¶�
				{
				
					UART_TO_FY1000_QueueSend_Stru SendBuffer;
					dbg_printf(DEBUG_INFO,"ȫ���豸�¶�����...");

					if(PackData->Pack_0X05.Set_TCtrlFg ==0XAA)
					{
						dbg_printf(DEBUG_INFO,"�¶�ֵ:%d",PackData->Pack_0X05.Set_Temp);
					}
					else if( PackData->Pack_0X05.Set_TCtrlFg ==0X00)
					{
						dbg_printf(DEBUG_INFO,"ϵͳ�¶�����ȡ��...");
					}

					if(PackData->Pack_0X05.LimtTE_Flag ==0XAA)
					{
						dbg_printf(DEBUG_INFO,"�����¶�ֵ:%d",PackData->Pack_0X05.LimtTE_Value);
					}
					else if( PackData->Pack_0X05.LimtTE_Flag ==0X00)
					{
						dbg_printf(DEBUG_INFO,"�����¶�����ȡ��...");
					}
					
					for( INT16U A=0;A<MAXDevice_Num;A++)
					{
						if( SysDeviceList.Device[A].Type ==Valve_U)
						{
							DevNum=A;
							Record +=1;
							if(PackData->Pack_0X05.Set_TCtrlFg ==0XAA)
							{
								SysDevData[DevNum].Device3.Set_TCtrlFg =0XAA;
								SysDevData[DevNum].Device3.Set_Temp =PackData->Pack_0X05.Set_Temp;
							}
							else if( PackData->Pack_0X05.Set_TCtrlFg ==0X00)
							{
								SysDevData[DevNum].Device3.Set_TCtrlFg =0XFF;
							}

							if(PackData->Pack_0X05.LimtTE_Flag ==0XAA)
							{
								SysDevData[DevNum].Device3.LimtTE_Flag =0XAA;
								SysDevData[DevNum].Device3.LimtTE_Value =PackData->Pack_0X05.LimtTE_Value;
							}
							else if( PackData->Pack_0X05.LimtTE_Flag ==0X00)
							{
								SysDevData[DevNum].Device3.LimtTE_Flag =0XFF;
							}
							SysDevData_Save(DevNum);
						}
					}
					if( Record ==0)	//û�з���ͨ�Ͽ�����
					{

						SendBuffer.SendData.Pack_0X06.State=COMBack_NF;
						FY_1000Send_Code_QInput(&SendBuffer,0X06);
						
					}
					else
					{
						SendBuffer.SendData.Pack_0X06.State =COMBack_OK;
						FY_1000Send_Code_QInput(&SendBuffer,0X06);
					}
					
				}
			}
			else if (ErrorFlg ==0X02)
			{
				UART_TO_FY1000_QueueSend_Stru SendBuffer;
				SendBuffer.SendData.Pack_0X06.State =COMBack_FT;
				FY_1000Send_Code_QInput(&SendBuffer,0X06);
				dbg_printf(DEBUG_INFO,"Э��������󣬷���0X03...");
			}

			
		}break;



/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
		case 0X07:
		{
			INT8U DevType =0;
			INT32U DevID =0;
			UART_TO_FY1000_QueueSend_Stru SendBuffer;
			INT16U DevNum =0;
			ErrorFlg =FY1000_Pack_0X07(Ctrl_Point);
			if(ErrorFlg ==0X00) //Э����֤�ɹ�
			{
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X07...");	
				DevType =PackData->Pack_0X07.Dev_Type;
				DevID =PackData->Pack_0X07.Dev_ID;
 
				if(GetMeters_Num_Build(DevID,(SysDEV_Type)DevType ,&DevNum) ==HAL_OK)	//�ɹ��ҵ�����
				{
					switch(DevType)
					{
						case Meter_B:
						{
							SysDevData[DevNum].Device1.CycBot_Energy =PackData->Pack_0X07.CycBot_Energy;
						}break;
#ifdef Meter_H_ENABLE
						case Meter_H:
						{
							SysDevData[DevNum].Device5.CycBot_Energy =PackData->Pack_0X07.CycBot_Energy;

						}break;
#endif
						default : break;
					}
					SysDevData[DevNum].Device1.CycBot_Energy =PackData->Pack_0X07.CycBot_Energy;

					SendBuffer.SendData.Pack_0X08.State =COMBack_FT; 
					if(SysDevData_Save(DevNum) ==HAL_OK)
					{
						SendBuffer.SendData.Pack_0X08.State =COMBack_OK; 
					}
					FY_1000Send_Code_QInput(&SendBuffer,0X08);

				}
				else		//�豸��ѯʧ��
				{
					SendBuffer.SendData.Pack_0X08.State=COMBack_NF;
					FY_1000Send_Code_QInput(&SendBuffer,0X08);
					dbg_printf(DEBUG_INFO,"�豸����ʧ��...");
				}

			}
		}break;

/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/

		case 0X09:
		{
			
			ClientCH1_Queue_Stru SendBuffer_2000;
			UART_TO_FY1000_QueueSend_Stru SendBuffer_1000;
			ErrorFlg =FY1000_Pack_0X09(Ctrl_Point);		
			if( ErrorFlg==0X00 )
			{
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X09...");	
				SendBuffer_1000.SendData.Pack_0X0A.State =COMBack_OK;
				FY_1000Send_Code_QInput(&SendBuffer_1000,0X0A);
				
			 	//MBUS�˿��������ݷ���
			 	if( PackData->Pack_0X09.CtrlDemand ==0X0A) //ȫ����������
			 	{
			 		SendBuffer_2000.Device.Type =Valve_U;
			 		SendBuffer_2000.SignleCom =RESET;
			 		SendBuffer_2000.SendData.FY2000Data.Pack_51.Delay =10;
					FY_2000Send_Code_QInput(&SendBuffer_2000,51);
					dbg_printf(DEBUG_INFO,"��վ�㲥 ���ſ���...");
					
			 	}
			 	if( PackData->Pack_0X09.CtrlDemand ==0XA0) //ȫ���ط�����
			 	{

			 		SendBuffer_2000.Device.Type =Valve_U;
			 		SendBuffer_2000.SignleCom =RESET;
			 		SendBuffer_2000.SendData.FY2000Data.Pack_52.Delay =10;
					FY_2000Send_Code_QInput(&SendBuffer_2000,52);
					dbg_printf(DEBUG_INFO,"��վ�㲥 ���Źر�...");

			 	}
			}
		}break;



/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
		case 0X0B:
		{
			UART_TO_FY1000_QueueSend_Stru SendBuffer_1000;
			ClientCH1_Queue_Stru SendBuffer_2000;
			ErrorFlg =FY1000_Pack_0X0B(Ctrl_Point);

			INT8U	 ValveCtrlDemandFlg;				//���������־
			INT8U	CtrlFlg;						//ǿ�ƿ��Ʊ�־
			
			if( ErrorFlg==0X00 )
			{

				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X0B...");	
				SendBuffer_1000.SendData.Pack_0X0C.State =COMBack_OK;
				FY_1000Send_Code_QInput(&SendBuffer_1000,0X0C);


				//�û�ǿ��״̬���ݱ���
			 	if(PackData->Pack_0X0B.CtrlDemand==Force_Open)		//ǿ�ƶ������� �û�ǿ�ƿ���
		 		{
					dbg_printf(DEBUG_INFO,"��վ�㲥 ����ǿ�ƿ���...");
		 			for(  INT16U Loop=0;Loop <MAXDevice_Num;Loop++)
		 			{
		 				if(SysDeviceList.Device[Loop].Type==Valve_U)
		 				{
		 					SysDevData[Loop].Device3.ForceCtrlFlg =Force_Open;
		 					
		 				}
		 				else if(SysDeviceList.Device[Loop].Type==Valve_UH)
		 				{
							SysDevData[Loop].Device4.ForceCtrlFlg =Force_Open;
		 				}	
		 			}	
		 			ValveCtrlDemandFlg =0X0A;
		 			CtrlFlg =0XAA;
		 		}
		 		else if(PackData->Pack_0X0B.CtrlDemand==Force_Close)	//ǿ�ƶ������� �û�ǿ�ƹر�
		 		{
					dbg_printf(DEBUG_INFO,"��վ�㲥 ����ǿ�ƹر�...");
		 			for(  INT16U Loop=0;Loop <MAXDevice_Num;Loop++)
		 			{
		 				if(SysDeviceList.Device[Loop].Type==Valve_U)
		 				{
		 					SysDevData[Loop].Device3.ForceCtrlFlg =Force_Close;
		 				}
		 				else if(SysDeviceList.Device[Loop].Type==Valve_UH)
		 				{
							SysDevData[Loop].Device4.ForceCtrlFlg =Force_Close;
		 				}		 				
		 				
		 			}
		 			ValveCtrlDemandFlg =0XA0;
		 			CtrlFlg =0XAA;
		 		}
		 		else if(PackData->Pack_0X0B.CtrlDemand==0XFF)		//ǿ�ƶ������� ǿ��ȡ��
		 		{
					dbg_printf(DEBUG_INFO,"��վ�㲥 ����ǿ��ȡ��...");
		 			for(  INT16U Loop=0;Loop <MAXDevice_Num;Loop++)
		 			{
		 				if(SysDeviceList.Device[Loop].Type==Valve_U)
		 				{
		 					SysDevData[Loop].Device3.ForceCtrlFlg =Force_Nor;
		 				}
		 				else if(SysDeviceList.Device[Loop].Type==Valve_UH)
		 				{
							SysDevData[Loop].Device4.ForceCtrlFlg =Force_Nor;
		 				}			 				
		 			}
		 			ValveCtrlDemandFlg =0X0A;
		 			CtrlFlg =0XFF;
		 		}	
		 		
			 	//MBUS�˿����ݷ���
				SendBuffer_2000.Device.Type =Valve_U;
				SendBuffer_2000.SignleCom =RESET;
				SendBuffer_2000.SendData.FY2000Data.Pack_53.ValveCtrlDemandFlg =ValveCtrlDemandFlg;
		 		SendBuffer_2000.SendData.FY2000Data.Pack_53.CtrlFlg =CtrlFlg;
				FY_2000Send_Code_QInput(&SendBuffer_2000,53);
			}
		}break;	
		
		

/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
		case 0X0D:
		{
			INT8U DevType =DEFUNULL;
			INT32U DevID =0;
			INT16U DevNum =0;
			INT8U CtrlDemand =0;
			INT8U CtrlFlg =0;
			
			
			ClientCH1_Queue_Stru SendBuffer_2000;

			
			ErrorFlg =FY1000_Pack_0X0D(Ctrl_Point);
			if( ErrorFlg==0X00 )
			{
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X0D...");	
				DevType =PackData->Pack_0X0D.DevType;		//�����û����
				DevID =PackData->Pack_0X0D.DevID;			//�����û����
				CtrlDemand =PackData->Pack_0X0D.CtrlDemand;	//������������
				CtrlFlg =PackData->Pack_0X0D.ForceFlag;		//����ǿ�ƿ��Ʊ�־
				if(GetMeters_Num(DevID,(SysDEV_Type)DevType ,&DevNum) ==HAL_OK) //�ɹ��ҵ��û��豸
				{

                    switch (DevType)
                    {
                        case Valve_U:
                        case Valve_UH:
                        {
                            //�û�ǿ��״̬����
                            if(CtrlFlg==0XAA)   //ǿ�ƶ����������� 
                            {
                            
                                if( CtrlDemand ==0XAA)
                                {   
                                    dbg_printf(DEBUG_INFO,"��վ���� ǿ�ƿ��� %08lX",DevID);
                                    if(DevType ==Valve_U)
                                    {
                                        SysDevData[DevNum].Device3.ForceCtrlFlg=Force_Open;
                                    }
                                    else
                                    {
                                        SysDevData[DevNum].Device4.ForceCtrlFlg=Force_Open;
                                    }
                                    SysDevData_Save(DevNum);
                                    CtrlDemand =Valve_Open;
                            
                                }
                                else if( CtrlDemand ==0X00)
                                {
                                    dbg_printf(DEBUG_INFO,"��վ���� ǿ�ƹر� %08lX",DevID);
                                    if(DevType ==Valve_U)
                                    {
                                        SysDevData[DevNum].Device3.ForceCtrlFlg=Force_Close;
                                    }
                                    else
                                    {
                                        SysDevData[DevNum].Device4.ForceCtrlFlg=Force_Close;
                                    }
                                    SysDevData_Save(DevNum);
                                    CtrlDemand =Valve_Close;
                                }
                                
                                //MBUS�˿����ݷ���
                                SendBuffer_2000.Device.Num=SysDeviceList.Device[DevNum].Num;
                                SendBuffer_2000.Device.Type=SysDeviceList.Device[DevNum].Type;
                                SendBuffer_2000.Device.ID=SysDeviceList.Device[DevNum].ID;
                                SendBuffer_2000.SignleCom =SET;
                                SendBuffer_2000.UaComFlg =0XAAAA;                               //�������ظ���¼
                                SendBuffer_2000.Uapack=0X0D;
                                SendBuffer_2000.SendData.FY2000Data.Pack_54.ValveCtrlDemandFlg =CtrlDemand;
                                SendBuffer_2000.SendData.FY2000Data.Pack_54.CtrlFlg =0XAA;
                                FY_2000Send_Code_QInput(&SendBuffer_2000,54);
                                
                                if(PackData->Pack_0X0D.CtrlDemand ==0XAA)
                                {
                                    dbg_printf(DEBUG_INFO,"�豸����...");
                                }
                                else if(PackData->Pack_0X0D.CtrlDemand ==0X00)
                                {
                                    dbg_printf(DEBUG_INFO,"�豸�ر�...");
                                }
                                
                            }
                            else if( CtrlFlg==0X00 )//��ǿ�ƶ������� ǿ��ȡ��
                            {
                                dbg_printf(DEBUG_INFO,"��վ���� ǿ��ȡ�� %08lX",DevID);
                                if(DevType ==Valve_U)
                                {
                                    SysDevData[DevNum].Device3.ForceCtrlFlg=Force_Nor;
                                }
                                else
                                {
                                    SysDevData[DevNum].Device4.ForceCtrlFlg=Force_Nor;
                                }                       
                                SysDevData_Save(DevNum);        
                            
                                //MBUS�˿����ݷ���
                                SendBuffer_2000.Device.Num=SysDeviceList.Device[DevNum].Num;
                                SendBuffer_2000.Device.Type=SysDeviceList.Device[DevNum].Type;
                                SendBuffer_2000.Device.ID=SysDeviceList.Device[DevNum].ID;
                                SendBuffer_2000.SignleCom =SET;
                                SendBuffer_2000.UaComFlg =0XAAAA;                               //�������ظ���¼
                                SendBuffer_2000.Uapack=0X0D;
                                SendBuffer_2000.SendData.FY2000Data.Pack_54.ValveCtrlDemandFlg =0X0A;
                                SendBuffer_2000.SendData.FY2000Data.Pack_54.CtrlFlg =0XFF;
                                FY_2000Send_Code_QInput(&SendBuffer_2000,54);
                                dbg_printf(DEBUG_INFO,"�豸����...");
                                
                            }
                        }

#ifdef Meter_DDF2_ENABLE	

                        case Meter_DDF2:
                        {
                            ClientCH1_Queue_Stru SendBuffer_DDF2;
                            if(CtrlDemand==0XAA)   //������������ 
                            {
                                dbg_printf(DEBUG_INFO,"��վ���� ���� %08lX",DevID);
                                                                //MBUS�˿����ݷ���
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
                                dbg_printf(DEBUG_INFO,"��վ���� �ر� %08lX",DevID);
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
#endif
                    }
    				



			 		
				}
				else		//�û��豸��ѯʧ��
				{
				
					UART_TO_FY1000_QueueSend_Stru SendBuffer_1000;
					SendBuffer_1000.SendData.Pack_0X0E.State =COMBack_NF;
					FY_1000Send_Code_QInput(&SendBuffer_1000,0X0E);
					dbg_printf(DEBUG_INFO,"��վ���� �豸��ѯʧ��...");

					
				}
			 	
			}
		}break;

/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/

		case 0X12:
		{

			ErrorFlg =FY1000_Pack_0X12(Ctrl_Point);
			if( ErrorFlg==0X00 )
			{	//dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X12...");
				//dbg_printf(DEBUG_INFO,"Heart Beat Ack...");
                
                dbg_printf(DEBUG_INFO,"����������Ӧ�� Pack_R 0X12...");

				
				/* ����������� */
				tcpRevEvent();
			}
		}break;


/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/

		case 0X13:
		{

			UART_TO_FY1000_QueueSend_Stru SendBuffer;
			ErrorFlg =FY1000_Pack_0X13(Ctrl_Point);
			if( ErrorFlg==0X00 )
			{	
				
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X13...");	
				RealClock_Str RTC_T;
				time_t Time;
				RTC_T.Year =PackData->Pack_0X13.Year;
				RTC_T.Month=PackData->Pack_0X13.Month;
				RTC_T.Day=PackData->Pack_0X13.Day;
				RTC_T.Hour=PackData->Pack_0X13.Hour;
				RTC_T.Minute=PackData->Pack_0X13.Minute;
				RTC_T.Second=PackData->Pack_0X13.Second;
				RTC_T.Week=0;
				
				if(getTimeTick(&Time, &RTC_T) ==0)
				{
					getRealTime(&Time, &RTC_T);									
					if( PCF8563_Set(&RTC_T) ==HAL_OK)
					{
						SendBuffer.SendData.Pack_0X14.State =COMBack_OK;
						dbg_printf(DEBUG_INFO,"Զ�̶�ʱ�ɹ�  %d:%d:%d  %d:%d:%d  %d",RTC_T.Year,RTC_T.Month,RTC_T.Day,RTC_T.Hour,RTC_T.Minute,RTC_T.Second,RTC_T.Week);
					}
					else
					{
						SendBuffer.SendData.Pack_0X14.State =COMBack_FT;
						dbg_printf(DEBUG_WARNING,"Զ�̶�ʱʧ��...");
					}
					FY_1000Send_Code_QInput(&SendBuffer,0X14);
					
				}
			}
			else if( ErrorFlg==0X02)
			{
				SendBuffer.SendData.Pack_0X14.State =COMBack_FT;
				FY_1000Send_Code_QInput(&SendBuffer,0X14);
			}

			
		}break;		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/

		case 0X15:
		{

			UART_TO_FY1000_QueueSend_Stru SendBuffer;
			ErrorFlg =FY1000_Pack_0X15(Ctrl_Point);
			INT16U CMD =0X00;
			if( ErrorFlg==0X00 )
			{	
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X15...");	
				CMD =0XA0A0;
				if(PackData->Pack_0X15.CMD ==0XAA)
				{
					CMD =0X0A0A;
				}
				
				if(SysPara.RelayRecord !=CMD)
				{
					SysPara.RelayRecord =CMD;
					PowerRelay_SET(CMD);			//����·�̵�����������
					
					SendBuffer.SendData.Pack_0X16.State =COMBack_FT;
					if( SysPara_Update()==HAL_OK)
					{
						SendBuffer.SendData.Pack_0X16.State =COMBack_OK;					

					}
				}
				else
				{
					SendBuffer.SendData.Pack_0X16.State =COMBack_OK;	
				}
				FY_1000Send_Code_QInput(&SendBuffer,0X16);

			}
			else if( ErrorFlg==0X02)
			{
				SendBuffer.SendData.Pack_0X16.State =COMBack_FT;
				FY_1000Send_Code_QInput(&SendBuffer,0X16);
			}

			
		}break; 	
		/*------------------------------------------------------------------------------------------*/
		/*------------------------------------------------------------------------------------------*/
		/*------------------------------------------------------------------------------------------*/		
		/*------------------------------------------------------------------------------------------*/
		/*------------------------------------------------------------------------------------------*/
		/*------------------------------------------------------------------------------------------*/
		/*------------------------------------------------------------------------------------------*/
		/*------------------------------------------------------------------------------------------*/		
		/*------------------------------------------------------------------------------------------*/
		/*------------------------------------------------------------------------------------------*/
		case 0X17:
		{
			INT8U DevType =DEFUNULL;
			INT32U DevID =0;
			INT16U DevNum =0;
			INT8U CtrlDemand =0;
			UART_TO_FY1000_QueueSend_Stru SendBuffer_1000;
			
			SendBuffer_1000.SendData.Pack_0X18.DevType =PackData->Pack_0X17.DevType;
			SendBuffer_1000.SendData.Pack_0X18.DevID =PackData->Pack_0X17.DevID;
			
			ErrorFlg =FY1000_Pack_0X17(Ctrl_Point);
			if( 0X00 ==ErrorFlg)
			{
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X17...");	
				DevType =PackData->Pack_0X17.DevType;		//�����豸����
				DevID =PackData->Pack_0X17.DevID;			//�����豸���
				CtrlDemand =PackData->Pack_0X17.CtrlDemand; 	//���ݿ��Ʊ�־
				if(HAL_OK ==GetMeters_Num(DevID,(SysDEV_Type)DevType ,&DevNum)) //�ɹ��ҵ��û��豸
				{
					INT16U userNum =SysDeviceList.Device[DevNum].UserNum;
					if(CtrlDemand ==0XAA)
					{
						UserData[userNum].Total_Heat =0XAAAA;
					}
					else
					{
						UserData[userNum].Total_Heat =0X00;
					}
					
					
					if(HAL_OK ==UserData_Save(userNum))
					{
						SendBuffer_1000.SendData.Pack_0X18.State =COMBack_OK;
						dbg_printf(DEBUG_INFO,"��վ���� �û����ݱ���ɹ�...");
						dbg_printf(DEBUG_INFO,"�豸����:%d  �豸���:%d  �豸���:%08lX  �û����:%d ",DevType,DevNum,DevID,userNum);
						
					}
					else
					{
						SendBuffer_1000.SendData.Pack_0X18.State =COMBack_FT;
						dbg_printf(DEBUG_INFO,"��վ���� �û����ݱ���ʧ��...");
					}
					FY_1000Send_Code_QInput(&SendBuffer_1000,0X18);					
					
				}
				else		//�û��豸��ѯʧ��
				{

					SendBuffer_1000.SendData.Pack_0X18.State =COMBack_NF;
					FY_1000Send_Code_QInput(&SendBuffer_1000,0X18);
					dbg_printf(DEBUG_INFO,"��վ���� �豸��ѯʧ��...");
				}
				
			}
			else if(0X01 ==ErrorFlg)
			{
				SendBuffer_1000.SendData.Pack_0X18.State =COMBack_FT;
				FY_1000Send_Code_QInput(&SendBuffer_1000,0X18);
				dbg_printf(DEBUG_INFO,"��վ���� �豸��������...");

			}
		}break;

/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
		case 0X19:
		{
			INT8U DevType =DEFUNULL;
			INT32U DevID =0;
			INT16U DevNum =0;
			UART_TO_FY1000_QueueSend_Stru SendBuffer_1000;
			
			SendBuffer_1000.SendData.Pack_0X1A.DevType =PackData->Pack_0X19.DevType;
			SendBuffer_1000.SendData.Pack_0X1A.DevID =PackData->Pack_0X19.DevID;
			SendBuffer_1000.SendData.Pack_0X1A.State =0X00;
			
			ErrorFlg =FY1000_Pack_0X19(Ctrl_Point);
			if( 0X00 ==ErrorFlg)
			{
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X19...");	
				DevType =PackData->Pack_0X19.DevType;		//�����豸����
				DevID =PackData->Pack_0X19.DevID;			//�����豸���
				
				if(HAL_OK ==GetMeters_Num(DevID,(SysDEV_Type)DevType ,&DevNum)) //�ɹ��ҵ��û��豸
				{
					INT16U userNum =SysDeviceList.Device[DevNum].UserNum;
					if(0XAAAA ==UserData[userNum].Total_Heat)
					{
						SendBuffer_1000.SendData.Pack_0X1A.State =0XAA;
					}
					FY_1000Send_Code_QInput(&SendBuffer_1000,0X1A); 
					dbg_printf(DEBUG_INFO,"��վ���� �豸��ѯ�ɹ�...");
					
				}
				else		//�û��豸��ѯʧ��
				{

					SendBuffer_1000.SendData.Pack_0X1A.State =COMBack_NF;
					FY_1000Send_Code_QInput(&SendBuffer_1000,0X1A);
					dbg_printf(DEBUG_INFO,"��վ���� �豸��ѯʧ��...");
				}
				
			}
			else if(0X01 ==ErrorFlg)
			{
				SendBuffer_1000.SendData.Pack_0X1A.State =COMBack_FT;
				FY_1000Send_Code_QInput(&SendBuffer_1000,0X1A);
				dbg_printf(DEBUG_INFO,"��վ���� �豸��������...");
			}
		}break;
        
        
/********************************************************************************************/
/********************************************************************************************/
/***********************************���������************************************************/
/********************************************************************************************/
/********************************************************************************************/
#ifdef  Valve_NWK_ENABLE
        
		case 0X1B:
		{
            INT8U  DevType =DEFUNULL;
			INT32U DevID =0;
			INT16U DevNum =0;
            
            float f_temp = 0;
            
			//ʵ�ֽ��շ������·� 06/10 ����֮�� ����������ɼ���  �������з��� 06/10 ��������
			ClientCH1_Queue_Stru            SendBuffer_NWK;
			//UART_TO_FY1000_QueueSend_Stru   SendBuffer_1000;

			ErrorFlg =FY1000_UnPack_0X1B(Ctrl_Point);		
			if( ErrorFlg==0X00 )
			{
                DevType = PackData->Pack_0X1B.DevType;
                DevID   = PackData->Pack_0X1B.DevID;
                if(HAL_OK ==GetMeters_Num(DevID,(SysDEV_Type)DevType ,&DevNum)) //�ɹ��ҵ��û��豸
				{
                    dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X1B...");	//Ctrl_Point->Pack_0X1B.Register_Addr;
                    
                    //������������
//                    SendBuffer_1000.SendData.Pack_0X1C.DevType          = PackData->Pack_0X1B.DevType;//�豸����
//                    SendBuffer_1000.SendData.Pack_0X1C.DevID            = PackData->Pack_0X1B.DevID;//�豸ID
//                    SendBuffer_1000.SendData.Pack_0X1C.Register_Addr    = PackData->Pack_0X1B.Register_Addr;//��ַ
//                    SendBuffer_1000.SendData.Pack_0X1C.data             = PackData->Pack_0X1B.data;//����
//                    FY_1000Send_Code_QInput(&SendBuffer_1000, 0X1C);
                    NWK_0X1B_Register_Addr = PackData->Pack_0X1B.Register_Addr;//��ַ
                    NWK_0X1B_Data          = PackData->Pack_0X1B.data;//����
                    //MBUS�˿��������ݷ���
                    //SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Head.Addr = PackData->Pack_0X1B.DevID;
                    
                    //0x10���12/14/16/18/  0x06���22/23/24/25/26/27
                    switch(PackData->Pack_0X1B.Register_Addr)
                    {
                        case 12://�����趨��ַ
                        {
                            SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Head.Addr       = PackData->Pack_0X1B.DevID;
                            SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr   = (INT16U)PackData->Pack_0X1B.Register_Addr;
                            bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr, 2);//�ѼĴ�����ַ�ֽڵ���

                            if(PackData->Pack_0X1B.data==0 || (PackData->Pack_0X1B.data>0 && PackData->Pack_0X1B.data<=100 ))
                            {
                                
                                f_temp = (float)(PackData->Pack_0X1B.data);
                                SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue   = f_temp;
                                //���������ֽڵ���
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue, 2);
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue+2, 2);
                                
                                
                                //SendBuffer_2000.Device.Num  =SysDeviceList.Device[DevNum].Num;
                                //SendBuffer_2000.Device.Type =SysDeviceList.Device[DevNum].Type;
                                //SendBuffer_2000.Device.ID   =SysDeviceList.Device[DevNum].ID;
                                //SendBuffer_2000.SignleCom   =SET;
                                //SendBuffer_2000.UaComFlg    =0XAAAA;                               //�������ظ���¼
                                //SendBuffer_2000.Uapack      =0X0D;
                                //SendBuffer_2000.SendData.FY2000Data.Pack_54.ValveCtrlDemandFlg =CtrlDemand;
                                //SendBuffer_2000.SendData.FY2000Data.Pack_54.CtrlFlg =0XAA;
                                
                                
                                SendBuffer_NWK.SignleCom    = SET;     //���մ������ۼ�
                                SendBuffer_NWK.Uapack       = 0X0D;     //����Զ�̿���
                                SendBuffer_NWK.UaComFlg     = 0XAAAA;   //����Զ�� ����
                                SendBuffer_NWK.Device       = SysDeviceList.Device[DevNum];
                                //SendBuffer_NWK.Device.Num = SysDeviceList.Device[DevNum].Num;
                                //SendBuffer_NWK.Device.Type =SysDeviceList.Device[DevNum].Type;
                                //SendBuffer_NWK.Device.ID=SysDeviceList.Device[DevNum].ID;
                                //SendBuffer_NWK.Device.COM_Type=SysDeviceList.Device[DevNum].COM_Type;
                                
                                NWK_Send_Code_QInput(&SendBuffer_NWK, 0x10);//10����
                                
                                dbg_printf(DEBUG_INFO,"���óɹ� Pack_R 0X1B...");
                            }
                            else
                            {
                                ErrorFlg = 0x01;//����
                            }
                        }break;
                        case 14://�²��趨��ַ
                        {
                            SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Head.Addr       = PackData->Pack_0X1B.DevID;
                            SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr   = (INT16U)PackData->Pack_0X1B.Register_Addr;
                            bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr, 2);//�ѼĴ�����ַ�ֽڵ���
                            
                            if(PackData->Pack_0X1B.data==0 || (PackData->Pack_0X1B.data>0 && PackData->Pack_0X1B.data<=10000 ))
                            {
                                
                                f_temp = (float)((float)PackData->Pack_0X1B.data/(float)100);
                                SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue   = f_temp;
                                //���������ֽڵ���
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue, 2);
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue+2, 2);
                                
                                SendBuffer_NWK.SignleCom    = SET;     //���մ������ۼ�
                                SendBuffer_NWK.Uapack       = 0X0D;     //����Զ�̿���
                                SendBuffer_NWK.UaComFlg     = 0XAAAA;   //����Զ�� ����
                                SendBuffer_NWK.Device       = SysDeviceList.Device[DevNum];
                                NWK_Send_Code_QInput(&SendBuffer_NWK, 0x10);//10����
                            }
                            else
                            {
                                ErrorFlg = 0x01;//����
                            }
                        }break;
                        case 16://��ˮ�¶��趨��ַ
                        {
                            SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Head.Addr       = PackData->Pack_0X1B.DevID;
                            SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr   = (INT16U)PackData->Pack_0X1B.Register_Addr;
                            bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr, 2);//�ѼĴ�����ַ�ֽڵ���
                            
                            if(PackData->Pack_0X1B.data==0 || (PackData->Pack_0X1B.data>0 && PackData->Pack_0X1B.data<=10000 ))
                            {

                                f_temp = (float)((float)PackData->Pack_0X1B.data/(float)100);
                                SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue   = f_temp;
                                //���������ֽڵ���
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue, 2);
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue+2, 2);
                                
                                
                                SendBuffer_NWK.SignleCom    = SET;     //���մ������ۼ�
                                SendBuffer_NWK.Uapack       = 0X0D;     //����Զ�̿���
                                SendBuffer_NWK.UaComFlg     = 0XAAAA;   //����Զ�� ����
                                SendBuffer_NWK.Device       = SysDeviceList.Device[DevNum];
                                NWK_Send_Code_QInput(&SendBuffer_NWK, 0x10);//10����
                            }
                            else
                            {
                                ErrorFlg = 0x01;//����
                            }
                        }break;
                        case 18://ѹ���趨��ַ
                        {
                            SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Head.Addr       = PackData->Pack_0X1B.DevID;
                            SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr   = (INT16U)PackData->Pack_0X1B.Register_Addr;
                            bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr, 2);//�ѼĴ�����ַ�ֽڵ���
                            
                            if(PackData->Pack_0X1B.data==0 || (PackData->Pack_0X1B.data>0 && PackData->Pack_0X1B.data<=10000 ))
                            {

                                f_temp = (float)((float)PackData->Pack_0X1B.data/(float)100);
                                SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue   = f_temp;
                                //���������ֽڵ���
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue, 2);
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.DataValue+2, 2);
                                
                                
                                SendBuffer_NWK.SignleCom    = SET;     //���մ������ۼ�
                                SendBuffer_NWK.Uapack       = 0X0D;     //����Զ�̿���
                                SendBuffer_NWK.UaComFlg     = 0XAAAA;   //����Զ�� ����
                                SendBuffer_NWK.Device       = SysDeviceList.Device[DevNum];
                                NWK_Send_Code_QInput(&SendBuffer_NWK, 0x10);//10����
                            }
                            else
                            {
                                ErrorFlg = 0x01;//����
                            }
                        }break;
                        case 22://����ģʽ�趨��ַ
                        {
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Head.Addr       = PackData->Pack_0X1B.DevID;
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Addr   = (INT16U)PackData->Pack_0X1B.Register_Addr;
                            bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr, 2);//�ѼĴ�����ַ�ֽڵ���
                            
                            if( PackData->Pack_0X1B.data < 7 )
                            {
                                
                                SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data= PackData->Pack_0X1B.data;
                                //���������ֽڵ���
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data, 2);
                                
                                
                                SendBuffer_NWK.SignleCom    = SET;     //���մ������ۼ�
                                SendBuffer_NWK.Uapack       = 0X0D;     //����Զ�̿���
                                SendBuffer_NWK.UaComFlg     = 0XAAAA;   //����Զ�� ����
                                SendBuffer_NWK.Device       = SysDeviceList.Device[DevNum];
                                NWK_Send_Code_QInput(&SendBuffer_NWK, 0x06);//06����
                            }
                            else
                            {
                                ErrorFlg = 0x01;//����
                            }
                        }break;
                        case 23://����趨
                        {
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Head.Addr       = PackData->Pack_0X1B.DevID;
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Addr   = (INT16U)PackData->Pack_0X1B.Register_Addr;
                            bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr, 2);//�ѼĴ�����ַ�ֽڵ���
                            
                            if( PackData->Pack_0X1B.data < 247 )
                            {
                                
                                SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data= PackData->Pack_0X1B.data;
                                //���������ֽڵ���
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data, 2);
                                
                                
                                SendBuffer_NWK.SignleCom    = SET;     //���մ������ۼ�
                                SendBuffer_NWK.Uapack       = 0X0D;     //����Զ�̿���
                                SendBuffer_NWK.UaComFlg     = 0XAAAA;   //����Զ�� ����
                                SendBuffer_NWK.Device       = SysDeviceList.Device[DevNum];
                                NWK_Send_Code_QInput(&SendBuffer_NWK, 0x06);//06����
                            }
                            else
                            {
                                ErrorFlg = 0x01;//����
                            }
                        }break;
                        case 24:// ���ת���趨
                        {
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Head.Addr       = PackData->Pack_0X1B.DevID;
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Addr   = (INT16U)PackData->Pack_0X1B.Register_Addr;
                            bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr, 2);//�ѼĴ�����ַ�ֽڵ���
                            
                            if( PackData->Pack_0X1B.data==0 || PackData->Pack_0X1B.data==1 )
                            {
                                
                                SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data= PackData->Pack_0X1B.data;
                                //���������ֽڵ���
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data, 2);
                                
                                
                                SendBuffer_NWK.SignleCom    = SET;     //���մ������ۼ�
                                SendBuffer_NWK.Uapack       = 0X0D;     //����Զ�̿���
                                SendBuffer_NWK.UaComFlg     = 0XAAAA;   //����Զ�� ����
                                SendBuffer_NWK.Device       = SysDeviceList.Device[DevNum];
                                NWK_Send_Code_QInput(&SendBuffer_NWK, 0x06);//06����
                            }
                            else
                            {
                                ErrorFlg = 0x01;//����
                            }
                        }break;
                        case 25://�Զ��г�У�鴥��
                        {
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Head.Addr       = PackData->Pack_0X1B.DevID;
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Addr   = (INT16U)PackData->Pack_0X1B.Register_Addr;
                            bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr, 2);//�ѼĴ�����ַ�ֽڵ���
                            
                            if( PackData->Pack_0X1B.data==0 || PackData->Pack_0X1B.data==1 )
                            {
                                
                                SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data= PackData->Pack_0X1B.data;
                                //���������ֽڵ���
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data, 2);
                                
                                
                                SendBuffer_NWK.SignleCom    = SET;     //���մ������ۼ�
                                SendBuffer_NWK.Uapack       = 0X0D;     //����Զ�̿���
                                SendBuffer_NWK.UaComFlg     = 0XAAAA;   //����Զ�� ����
                                SendBuffer_NWK.Device       = SysDeviceList.Device[DevNum];
                                NWK_Send_Code_QInput(&SendBuffer_NWK, 0x06);//06����
                            }
                            else
                            {
                                ErrorFlg = 0x01;//����
                            }
                        }break;
                        case 26://Զ���г�У�鴥��
                        {
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Head.Addr       = PackData->Pack_0X1B.DevID;
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Addr   = (INT16U)PackData->Pack_0X1B.Register_Addr;
                            bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr, 2);//�ѼĴ�����ַ�ֽڵ���
                            
                            if( PackData->Pack_0X1B.data==0x5555 )
                            {
                                
                                SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data= PackData->Pack_0X1B.data;
                                //���������ֽڵ���
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data, 2);
                                
                                
                                SendBuffer_NWK.SignleCom    = SET;     //���մ������ۼ�
                                SendBuffer_NWK.Uapack       = 0X0D;     //����Զ�̿���
                                SendBuffer_NWK.UaComFlg     = 0XAAAA;   //����Զ�� ����
                                SendBuffer_NWK.Device       = SysDeviceList.Device[DevNum];
                                NWK_Send_Code_QInput(&SendBuffer_NWK, 0x06);//06����
                            }
                            else
                            {
                                ErrorFlg = 0x01;//����
                            }
                        }break;
                        case 27://ֱ������ٶ�
                        {
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Head.Addr       = PackData->Pack_0X1B.DevID;
                            SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Addr   = (INT16U)PackData->Pack_0X1B.Register_Addr;
                            bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_10_cmd.Register_Addr, 2);//�ѼĴ�����ַ�ֽڵ���
                            
                            if( PackData->Pack_0X1B.data>=10 &&  PackData->Pack_0X1B.data<=100 )
                            {
                                
                                SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data= PackData->Pack_0X1B.data;
                                //���������ֽڵ���
                                bytes_reverse( (unsigned char *)&SendBuffer_NWK.SendData.NWKData.pack_06_cmd.Register_Data, 2);
                                
                                
                                SendBuffer_NWK.SignleCom    = SET;     //���մ������ۼ�
                                SendBuffer_NWK.Uapack       = 0X0D;     //����Զ�̿���
                                SendBuffer_NWK.UaComFlg     = 0XAAAA;   //����Զ�� ����
                                SendBuffer_NWK.Device       = SysDeviceList.Device[DevNum];
                                NWK_Send_Code_QInput(&SendBuffer_NWK, 0x06);//06����
                            }
                            else
                            {
                                ErrorFlg = 0x01;//����
                            }
                        }break;
                        default:
                            ErrorFlg = 0x01;//����
                            break;
                    }
                }                
			}
		}break;
        
        
        
/********************************************************************************************/
/********************************************************************************************/
/***********************************��������� END********************************************/
/********************************************************************************************/
/********************************************************************************************/
#endif        //#ifdef  Valve_NWK_ENABLE
        
		case 0X41:
		{
			ErrorFlg =FY1000_Pack_0X41(Ctrl_Point);
			if(ErrorFlg ==0X00) //Э����֤�ɹ�
			{
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X41...");	
				if(
				   (SysPara.IP1 ==PackData->Pack_0X41.IP1) && \
				   (SysPara.IP2 ==PackData->Pack_0X41.IP2) && \
				   (SysPara.IP3 ==PackData->Pack_0X41.IP3) && \
				   (SysPara.IP4 ==PackData->Pack_0X41.IP4) && \
				   (SysPara.PortNum ==PackData->Pack_0X41.Port)
				  )
				  
				  {
						SerReg_Flg = 0;		//ע���Ǹ�λ
						PulseLeaguer_SET(Beep_Ctrler, 2, 10, 10, 20, 0, 0);			  //����ָ��  ��������	ɨ����(tick*X) ���ؿ��	����	���ڼ�����	��ǰ״̬

				  }
			}
		}break;



/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
		case 0X43:
		{
			ErrorFlg =FY1000_Pack_0X43(Ctrl_Point);
			if(ErrorFlg ==0X00) //Э����֤�ɹ�
			{
				dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0X43...");	
				GPRS_State.IPA1 =PackData->Pack_0X43.IPA1;	   //IP��ַ1��
				GPRS_State.IPA2 =PackData->Pack_0X43.IPA2;	   //IP��ַ2��
				GPRS_State.IPA3 =PackData->Pack_0X43.IPA3;	   //IP��ַ3��
				GPRS_State.IPA4 =PackData->Pack_0X43.IPA4;	   //IP��ַ4��
				GPRS_State.Port =PackData->Pack_0X43.Port;	   	   //IP�˿ں�

				GPRS_State.IPB1 =PackData->Pack_0X43.IPB1;	   //IP��ַ1��
				GPRS_State.IPB2 =PackData->Pack_0X43.IPB2;	   //IP��ַ2��
				GPRS_State.IPB3 =PackData->Pack_0X43.IPB3;	   //IP��ַ3��
				GPRS_State.IPB4 =PackData->Pack_0X43.IPB4;	   //IP��ַ4��
				
				for(INT8U Reflag =0;Reflag<20;Reflag++)
				{
					GPRS_State.CCID[Reflag] =PackData->Pack_0X43.CCID[Reflag];
				}

				GPRS_State.GPRS_Power_Flg =PackData->Pack_0X43.GPRS_Power_Flg;	   	//��Դ��־
				GPRS_State.GPRS_ONOFF_Flg =PackData->Pack_0X43.GPRS_ONOFF_Flg;	   	//���ػ���־
				GPRS_State.SIMCard_State =PackData->Pack_0X43.SIMCard_State;		   	//SIM������״̬

				GPRS_State.CSQ1 =PackData->Pack_0X43.CSQ1;	   					//�ź�ǿ��1
				GPRS_State.CSQ2 =PackData->Pack_0X43.CSQ2;	   					//�ź�ǿ��2

				PulseLeaguer_SET(Beep_Ctrler, 2, 10, 10, 20, 0, 0);			   		//����ָ��  ��������  ɨ����(tick*X) ���ؿ��	 ����	 ���ڼ�����  ��ǰ״̬

				/*
						���ͷ�������ע������
						DTU���ӷ������ɹ� �������� ���ͷ�������ע������
						DTU ���ӷ�������     Ҫ��ɼ�������ע��!!!
				*/
				SerReg_Flg = 0;									   			//ע���Ǹ�λ
				UART_TO_FY1000_QueueSend_Stru SendBuffer;
				if(FY_1000Send_Code_QInput(&SendBuffer,0XFE)==pdTRUE)
				{			
					dbg_printf(DEBUG_INFO,"��վ����ע������....");
				}
				
			}
		}break;

/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/		
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------*/

		
		case 0XBA:
		{
			ErrorFlg =FY1000_Pack_0XBA(Ctrl_Point);
			INT16U* CRC16P;
			INT16U CRCCAL =0;
			if( ErrorFlg==0X00 )
			{	UART_TO_FY1000_QueueSend_Stru SendBuffer;

				INT16U datalenth =PackData->Pack_0XBA.Head.Lenth;
				INT16U CRC16VAL =0;
				
				switch(FileTransCrtl.State)
				{
					case 0:	//�ȴ��ļ���ʼ����
					{
						if(datalenth ==8)//�ļ���ʼ����
						{
							/*У��CRC*/
							CRC16P =(INT16U*)(PackData->Pack_0XBA.ByteF+4);
							CRCCAL =*CRC16P;
							CRC16VAL =CRC16Cal(PackData->Pack_0XBA.ByteF,4);
						//	if(( CRC16VAL ==CRCCAL)&&( PackData->Pack_0XBA.NUM ==0) )//У����� �����ݰ������ȷ
							if(( CRC16VAL ==CRCCAL))//У����� �����ݰ������ȷ
							{
								INT32U *DataLenth =0;
								
								FileTransCrtl.EOH =PackData->Pack_0XBA.EOH;
								FileTransCrtl.ErrorNum=0;		//�������������
								FileTransCrtl.PackAddr =0;
								FileTransCrtl.NUM =PackData->Pack_0XBA.NUM;
								DataLenth =(INT32U*)(PackData->Pack_0XBA.ByteF);

								if( *DataLenth >SysDownload_Temp_Size)
								{
									SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
									SendBuffer.SendData.Pack_0XBF.Ack=0X04;
									FY_1000Send_Code_QInput(&SendBuffer,0XBF);
									dbg_printf(DEBUG_ERR,"�ļ�����Χ���˳�...");
								}
								else
								{
									/*  Flash ����*/
									if(spiFlashErase(SysDownload_Temp_Addr, *DataLenth) != HAL_OK)//ʧ��
									{
										SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
										SendBuffer.SendData.Pack_0XBF.Ack=0X04;
										FY_1000Send_Code_QInput(&SendBuffer,0XBF);
										dbg_printf(DEBUG_ERR,"�洢������ʧ�ܣ��˳�...");
									}
									else
									{
										SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
										FileTransCrtl.NUM =PackData->Pack_0XBA.NUM;
										SendBuffer.SendData.Pack_0XBF.Ack=0X01;
										FY_1000Send_Code_QInput(&SendBuffer,0XBF);
										FileTransCrtl.State =1;
										FileTransCrtl.TickCount =SystemTick_ms;
										dbg_printf(DEBUG_ALERT,"�洢��������ɵȴ������ļ�������С��%lu...",*DataLenth);
									}
								}
							}
							else										//У��ʧ��
							{
								FileTransCrtl.ErrorNum +=1;					//�������������
								SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
								SendBuffer.SendData.Pack_0XBF.Ack=0X02;
								if(FileTransCrtl.ErrorNum>3)
								{
									SendBuffer.SendData.Pack_0XBF.Ack=0X05;
								}
								FY_1000Send_Code_QInput(&SendBuffer,0XBF);
								FileTransCrtl.State =0;
								dbg_printf(DEBUG_ERR,"�ļ�У�����...");
							}
						}
					}break;
					
					case 1:	//�ļ����������
					{
						if(datalenth !=5)//�����������ݰ�
						{
							INT16U BufNum =128;
							if( PackData->Pack_0XBA.EOH ==2)
							{
								BufNum =512;
							}
							/*У��CRC*/
							CRC16P =(INT16U*)(PackData->Pack_0XBA.ByteF+BufNum);
							CRCCAL =*CRC16P;
							CRC16VAL =CRC16Cal(PackData->Pack_0XBA.ByteF,BufNum);
							if( CRC16VAL == CRCCAL)	//CRCУ����� �������֤���  ������
							{

								INT8U BUF3 = PackData->Pack_0XBA.NUM -FileTransCrtl.NUM;
								if((INT8U)1==BUF3)
								{
									
									dbg_printf(DEBUG_DEBUG,"�ļ����� %d",PackData->Pack_0XBA.NUM);
									INT32U FlashAddr =0;
									FileTransCrtl.ErrorNum =0;							//�������������			
									/*Flsah д��*/								
									FlashAddr =FileTransCrtl.PackAddr +SysDownload_Temp_Addr;	//��ȡʵ��д���ַ
									if( spiFlashWrite(FlashAddr , PackData->Pack_0XBA.ByteF,BufNum) ==HAL_OK)	//дFlash
									{
										INT8U* SPIReadBuf = pvPortMalloc( BufNum);
										INT16U Err=0;
										if(spiFlashRead(FlashAddr, SPIReadBuf,BufNum) ==HAL_OK)
										{
											for(INT16U i =0;i<BufNum;i++)
											{
												if(*(SPIReadBuf+i) !=*(PackData->Pack_0XBA.ByteF+i))
												{
													Err +=1;
													break;
												}
											}
											if(Err ==0)		//�ļ�д�벢��ȡ��֤�ɹ�   ��������
											{
												SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
												FileTransCrtl.NUM =PackData->Pack_0XBA.NUM;
												SendBuffer.SendData.Pack_0XBF.Ack=0X01;
												FY_1000Send_Code_QInput(&SendBuffer,0XBF);
												
												FileTransCrtl.State =1;
												FileTransCrtl.TickCount =SystemTick_ms;
												dbg_printf(DEBUG_DEBUG,"�ļ�����д��ɹ��ȴ�����...��ǰPACK:%d ADD:%lu",PackData->Pack_0XBA.NUM,FileTransCrtl.PackAddr);
												FileTransCrtl.PackAddr +=BufNum;
											}
											else	//��ȡʧ�� �������¿�ʼ
											{
												SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
												SendBuffer.SendData.Pack_0XBF.Ack=0X04;
												FY_1000Send_Code_QInput(&SendBuffer,0XBF);
												FileTransCrtl.State =0;
												dbg_printf(DEBUG_ERR,"�ļ�����д�����...");
											}
										}
										else		//��ȡʧ��
										{
											SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
											SendBuffer.SendData.Pack_0XBF.Ack=0X04;
											FY_1000Send_Code_QInput(&SendBuffer,0XBF);
											FileTransCrtl.State =0;
											dbg_printf(DEBUG_ERR,"�ļ�������ȡʧ��...");
										}
										vPortFree(SPIReadBuf);

									}
									else	//Flashд��ʧ��  �������¿�ʼ
									{
										SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
										SendBuffer.SendData.Pack_0XBF.Ack=0X04;
										FY_1000Send_Code_QInput(&SendBuffer,0XBF);
										FileTransCrtl.State =0;
										dbg_printf(DEBUG_ERR,"�ļ�����д��ʧ�ܣ��������¿�ʼ...");
									}
								}
								else if((INT8U)0==BUF3)
								{
									dbg_printf(DEBUG_DEBUG,"�ļ��ش� %d",PackData->Pack_0XBA.NUM);
									INT32U FlashAddr =0;
									FileTransCrtl.ErrorNum =0;								//�������������			
									/*Flsah д��*/								
									FlashAddr =FileTransCrtl.PackAddr +SysDownload_Temp_Addr-BufNum;	//��ȡʵ��д���ַ
									if( spiFlashWrite(FlashAddr , PackData->Pack_0XBA.ByteF,BufNum) ==HAL_OK)	//дFlash
									{
										INT8U* SPIReadBuf = pvPortMalloc( BufNum);
										INT16U Err=0;
										if(spiFlashRead(FlashAddr, SPIReadBuf,BufNum) ==HAL_OK)
										{
											for(INT16U i =0;i<BufNum;i++)
											{
												if(*(SPIReadBuf+i) !=*(PackData->Pack_0XBA.ByteF+i))
												{
													Err +=1;
													break;
												}
											}
											if(Err ==0)		//�ļ�д�벢��ȡ��֤�ɹ�   ��������
											{
												SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
												FileTransCrtl.NUM =PackData->Pack_0XBA.NUM;
												SendBuffer.SendData.Pack_0XBF.Ack=0X01;
												FY_1000Send_Code_QInput(&SendBuffer,0XBF);
												
												FileTransCrtl.State =1;
												FileTransCrtl.TickCount =SystemTick_ms;
												dbg_printf(DEBUG_DEBUG,"�ļ��ش�д��ɹ��ȴ�����...��ǰPACK:%d ADD:%lu",PackData->Pack_0XBA.NUM,FileTransCrtl.PackAddr);
												FileTransCrtl.PackAddr +=BufNum;
											}
											else	//��ȡʧ�� �������¿�ʼ
											{
												SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
												SendBuffer.SendData.Pack_0XBF.Ack=0X04;
												FY_1000Send_Code_QInput(&SendBuffer,0XBF);
												FileTransCrtl.State =0;
												dbg_printf(DEBUG_ERR,"�ļ��ش�д�����...");
											}
										}
										else	 //��ȡʧ��
										{
											SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
											SendBuffer.SendData.Pack_0XBF.Ack=0X04;
											FY_1000Send_Code_QInput(&SendBuffer,0XBF);
											FileTransCrtl.State =0;
											dbg_printf(DEBUG_ERR,"�ļ��ش���ȡʧ��...");
										}
										vPortFree(SPIReadBuf);

									}
									else	//Flashд��ʧ��  �������¿�ʼ
									{
										SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
										SendBuffer.SendData.Pack_0XBF.Ack=0X04;
										FY_1000Send_Code_QInput(&SendBuffer,0XBF);
										FileTransCrtl.State =0;
										dbg_printf(DEBUG_ERR,"�ļ��ش�д��ʧ�ܣ��������¿�ʼ...");
									}
								}
								else
								{
									dbg_printf(DEBUG_ERR,"�ļ���Ŵ���%d,%d",PackData->Pack_0XBA.NUM,FileTransCrtl.NUM );
								}
								
							}							
							else	//CRCУ��ʧ��
							{
								FileTransCrtl.ErrorNum +=1;				  //�������������
								SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
								SendBuffer.SendData.Pack_0XBF.Ack=0X02;
								FileTransCrtl.State =1;
								FileTransCrtl.TickCount =SystemTick_ms;
								if(FileTransCrtl.ErrorNum>3)
								{
									SendBuffer.SendData.Pack_0XBF.Ack=0X04;
									FileTransCrtl.State =0;
								}
								FY_1000Send_Code_QInput(&SendBuffer,0XBF);
								dbg_printf(DEBUG_ERR,"�ļ�У��ʧ��...");
							}
						}
						else									//�����ļ�����������ݰ�
						{
							/*У��CRC*/
							CRC16P =(INT16U*)(PackData->Pack_0XBA.ByteF+1);
							CRCCAL =*CRC16P;
							CRC16VAL =CRC16Cal(PackData->Pack_0XBA.ByteF,1);
							if( CRC16VAL ==CRCCAL)		//CRCУ����� 
							{
								FileTransCrtl.ErrorNum =0;			//�������������
								
								/*
									�ļ��������  �����Ӧ
								*/
								SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;	//�����
								SendBuffer.SendData.Pack_0XBF.Ack=PackData->Pack_0XBA.ByteF[0];
								FY_1000Send_Code_QInput(&SendBuffer,0XBF);
								FileTransCrtl.State =0;
								FileTransCrtl.TickCount =SystemTick_ms;
								if(0X03 == SendBuffer.SendData.Pack_0XBF.Ack)
								{
									dbg_printf(DEBUG_ALERT,"�ļ��������...");
								}
								else if(0X05 == SendBuffer.SendData.Pack_0XBF.Ack )
								{
									dbg_printf(DEBUG_ERR,"�ļ�������ֹ...");
								}
							}
							else	//CRCУ��ʧ��
							{
								FileTransCrtl.ErrorNum +=1;					//�������������
								SendBuffer.SendData.Pack_0XBF.NUM=PackData->Pack_0XBA.NUM;
								SendBuffer.SendData.Pack_0XBF.Ack=0X02;
								FileTransCrtl.State =1;
								FileTransCrtl.TickCount =SystemTick_ms;
								
								if(FileTransCrtl.ErrorNum>3)
								{
									SendBuffer.SendData.Pack_0XBF.Ack=0X04;
									FileTransCrtl.State =0;
								}
								FY_1000Send_Code_QInput(&SendBuffer,0XBF);
								dbg_printf(DEBUG_ERR,"�ļ�У��ʧ��...");
							}
						}
					}break;
				}
			}
		}break;


		case 0XBB:
		{
			/* ��ȡ����汾�� */
			UART_TO_FY1000_QueueSend_Stru version_buf;
			ErrorFlg =FY1000_Pack_0XBB(Ctrl_Point);
			if(0X00 ==ErrorFlg)
			{
				dbg_printf(DEBUG_DEBUG,"��ѯ����汾�ţ�%u",SYSTEM_VERSION);
				FY_1000Send_Code_QInput(&version_buf,0XBC);
			}
		}
		break;

		case 0XBD:
		{
			/*�����ļ� */
			UART_TO_FY1000_QueueSend_Stru flash_buf;
			int result;
			ErrorFlg =FY1000_Pack_0XBD(Ctrl_Point);
			if( 0x00 ==ErrorFlg)
			{
				uint8_t cmd = PackData->Pack_0XBD.CMD;
				switch(cmd)
				{
					case 0x01:
					{
						dbg_printf(DEBUG_DEBUG,"Update BootLoader");
						result = flash_file_type(O_BOOT);
						break;
					}
					case 0x02:
					{
						dbg_printf(DEBUG_DEBUG,"Update Application");
						result = flash_file_type(O_APP);
						break;
					}
					case 0x03:
					{
						dbg_printf(DEBUG_DEBUG,"Update Parameter");
						result = verifyProcessFile();
						break;
					}
					default:
					{
						dbg_printf(DEBUG_WARNING,"Unknown update type");
						result = -1;
						break;
					}
				}
				
				flash_buf.SendData.Pack_0XBE.RESULT = COMBack_OK;
				if(-1 == result)
				{
					flash_buf.SendData.Pack_0XBE.RESULT = COMBack_FT;
				}
				FY_1000Send_Code_QInput(&flash_buf,0XBE);
				
				if(-1 != result)
				{
					/* �ȴ����ذ�������ɺ������豸 */
					osDelay(pdMS_TO_TICKS(5000));
					NVIC_SystemReset();
				}
			}
		}break;


		case 0XFF:
		{			
			ErrorFlg =FY1000_Pack_0XFF(Ctrl_Point);
			
			if( ErrorFlg==0X00 )
			{	
				//dbg_printf(DEBUG_INFO,"ϵͳͨ����Ӧ Pack_R 0XFF...");	
                //dbg_printf(DEBUG_INFO,"������ע��ɹ�");
                
				dbg_printf(DEBUG_INFO,"������ע��ɹ�-ϵͳͨ����Ӧ Pack_R 0XFF...");	
                
				SerReg_Flg =0XAAAA;
				PulseLeaguer_SET(Beep_Ctrler, 3, 10, 8, 15, 0, 0);			   		//����ָ��  ��������  ɨ����(tick*X) ���ؿ��	 ����	 ���ڼ�����  ��ǰ״̬
			}
			
		}break;



		default : break;
	}
	return ErrorFlg;
}






 


/*
FY1000_��������� ���ɼ����������� �������� ������

*/
INT8U FY1000_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point)
{

	BaseType_t Err = HAL_ERROR;

	/* ���ն������� */
	Err = xQueueReceive(UART_TO_FY1000_Msg,&FY1000_Q_RX_BufferP,2);
	if( Err != pdTRUE)
	{
		return Err;
	}

	/* ���ƴ��������ݲ���� */
	FY1000_Q_RX_Buffer =*FY1000_Q_RX_BufferP;
	Ctrl_Point->PackCreatFlag =FY1000_Q_RX_Buffer.PackCreatFlag;
	Ctrl_Point->PackINPort =FY1000_Q_RX_Buffer.PackINPort;

	/* ����������־��� ���߿���״̬��� */
	if(Ctrl_Point->PackCreatFlag != ENABLE)
	{
		return HAL_ERROR;
	}

	Ctrl_Point->PackCreatFlag = DISABLE;

	if((SerReg_Flg !=0XAAAA)&&(Ctrl_Point->PackINPort !=0X40))
	{
		Ctrl_Point->PackINPort =0XFE;

	}
	/* ���Э����ʶ�� */
	switch(Ctrl_Point->PackINPort)
	{

		case 0X02:
		{
			switch(FY1000_Q_RX_Buffer.SendData.Pack_0X02_F.BackFlag)
			{
				case COMBack_NF://��ѯʧ��
				{
					FY1000_Pack_0X02_N(Ctrl_Point);
					
				}break;

				case COMBack_CE://ͨ���쳣
				{
					FY1000_Pack_0X02_F(Ctrl_Point);
				}break;
				
				case COMBack_OK://��������
				{
					switch(FY1000_Q_RX_Buffer.SendData.Pack_0X02_D1.Dev_Type)
					{
						case Meter_B:
#ifdef Meter_H_ENABLE
						case Meter_H:
#endif
						{
							FY1000_Pack_0X02_A1(Ctrl_Point);
						}break;
						
						case Meter_U:
#ifdef  Meter_XY_ENABLE	                            
						case Meter_XY:
#endif
						
#ifdef  Meter_HT2X_ENABLE	                            
						case Meter_HT2X:
                        case Meter_HT3X:
#endif
						
#ifdef  Meter_BRC_ENABLE	                            
						case Meter_BRC:
#endif
						{
							FY1000_Pack_0X02_A2(Ctrl_Point);
						}break;

						case Valve_U:
						{
							FY1000_Pack_0X02_A3(Ctrl_Point);
						}break;

						case Valve_UH:
#ifdef  Meter_DDF2_ENABLE	
                        case Meter_DDF2:
#endif							
						{
							FY1000_Pack_0X02_A4(Ctrl_Point);
						}break;
                        
#ifdef  Valve_NWK_ENABLE	
                        case Valve_NWK:
						{
							FY1000_Pack_0X02_A5(Ctrl_Point);
						}break;
#endif
						default:break;

					}
			
				}break;
				default:break;
			}
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X02...");	
		}break;


		
		case 0X04:
		{
			FY1000_Pack_0X04(Ctrl_Point);
			
			SysOnbootFlag =1;
			SysOnbootdelay=SystemTick_ms;
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X04...");	
		}break;

		case 0X06:
		{
			FY1000_Pack_0X06(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X06...");	

		}break;

		case 0X08:
		{
			FY1000_Pack_0X08(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X08...");	

		}break;
		
		case 0X0A:
		{
			FY1000_Pack_0X0A(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X0A...");	

		}break;


		case 0X0C:
		{
			FY1000_Pack_0X0C(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X0C...");	

		}break;

		case 0X0E:
		{
			FY1000_Pack_0X0E(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X0E...");	

		}break;

		case 0X11:
		{
			FY1000_Pack_0X11(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳ��������...");	
		}break;		

		case 0X14:
		{
			FY1000_Pack_0X14(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X14...");	
		}break;	
		
		case 0X16:
		{
			FY1000_Pack_0X16(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X16...");	
		}break;	
		
		case 0X18:
		{
			FY1000_Pack_0X18(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X18...");	
		}break;	
		

		case 0X1A:
		{
			FY1000_Pack_0X1A(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X1A...");	
		}break;	
        
#ifdef Valve_NWK_ENABLE
		case 0X1C:
		{
			FY1000_Pack_0X1C(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X1C...");	
		}break;	
#endif
        
		case 0X40:
		{
			FY1000_Pack_0X40(Ctrl_Point);
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0X40...");	

		}break;	
		

		case 0XB0:
		{
			dbg_printf(DEBUG_INFO,"ϵͳͨ��Ӧ�� Pack_T 0XB0...");
			switch(FY1000_Q_RX_Buffer.SendData.Pack_0XB0_F.BackFlag)
			{
				
				case COMBack_CE://ͨ���쳣
				{
					FY1000_Pack_0XB0_F(Ctrl_Point);
				}break;
				
				case COMBack_OK://��������
				{
					switch(FY1000_Q_RX_Buffer.SendData.Pack_0XB0_D1.Dev_Type)
					{
						case Meter_B:
#ifdef Meter_H_ENABLE
						case Meter_H:
#endif
						{
							FY1000_Pack_0XB0_A1(Ctrl_Point);
						}break;
						
						case Meter_U:
#ifdef  Meter_XY_ENABLE	
						case Meter_XY:
#endif

#ifdef  Meter_HT2X_ENABLE	
                        case Meter_HT2X:
                        case Meter_HT3X:
#endif

#ifdef  Meter_BRC_ENABLE	
                        case Meter_BRC:
#endif

						{
							FY1000_Pack_0XB0_A2(Ctrl_Point);
						}break;

						case Valve_U:
						{
							FY1000_Pack_0XB0_A3(Ctrl_Point);
						}break;

						case Valve_UH:
#ifdef  Meter_DDF2_ENABLE	
                        case Meter_DDF2:
#endif						
						{
							FY1000_Pack_0XB0_A4(Ctrl_Point);
						}break;

#ifdef  Valve_NWK_ENABLE	
                        case Valve_NWK:
						{
							FY1000_Pack_0XB0_A5(Ctrl_Point);
						}break;
#endif
						default:break;

					}
			
				}break;
				
				
				default:break;
				
			}
			
		}break;

		
		case 0XBF:
		{
			FY1000_Pack_0XBF(Ctrl_Point);

		}break;

		case 0XBC:
		{
			FY1000_Pack_0XBC(Ctrl_Point);

		}break;

		case 0XBE:
		{
			FY1000_Pack_0XBE(Ctrl_Point);

		}break;

		case 0XFE:
		{
			FY1000_Pack_0XFE(Ctrl_Point);
			
			dbg_printf(DEBUG_INFO,"ϵͳע�����뷢��...");	

		}break;


		default:
		{
			Ctrl_Point->PackINPort =0;
		}
		break;
	}
/*

�ô������ļ�����״̬���ĸ�λ����
*/
	if(FileTransCrtl.State )		//�ļ�����״̬��λ����
	{
		if( SystemTick_ms -FileTransCrtl.TickCount >=FileTransOUT)
		{
			FileTransCrtl.State =0;
			dbg_printf(DEBUG_DEBUG,"�ļ����䳬ʱ�˳�...");
		}
	}			
	return HAL_OK;
}




BaseType_t UART_TO_FY1000_CCB_QueueSend(UART_TO_FY1000_QueueSend_Stru *InPut)
{

	BaseType_t err;
	err =err;

	UART_TO_FY1000_OutArray[UART_TO_FY1000_OutRecord] =*InPut;		//���ݴ���
	UART_TO_FY1000_OutArrayP[UART_TO_FY1000_OutRecord] = &UART_TO_FY1000_OutArray[UART_TO_FY1000_OutRecord];//����ָ�봫��

    //������Ϣ
    err = xQueueSend(UART_TO_FY1000_Msg, &UART_TO_FY1000_OutArrayP[UART_TO_FY1000_OutRecord], 20);
    
	UART_TO_FY1000_OutRecord +=1;
	if(UART_TO_FY1000_OutRecord >=UART_TO_FY1000_Q_NUM)
	{
		UART_TO_FY1000_OutRecord =0;
	}
	return err;

}





/*
�ɼ���FY1000���ݷ��� ����װ�뺯��
��������
*/
BaseType_t FY_1000Send_Code_QInput(UART_TO_FY1000_QueueSend_Stru*DataBuffer_P,INT8U PackPort )
{
	BaseType_t err;
	
	osMutexWait(fy1000SendMutexHandle, osWaitForever);

	DataBuffer_P->PackCreatFlag =ENABLE;
	DataBuffer_P->PackINPort =PackPort;
	err =UART_TO_FY1000_CCB_QueueSend(DataBuffer_P);//��Ϣ����
	osMutexRelease(fy1000SendMutexHandle);
	if(err ==pdTRUE)
	{
		dbg_printf(DEBUG_DEBUG,"UART_TO_FY1000_CCB_QueueSend    OK ");
	}
	else
	{
		dbg_printf(DEBUG_DEBUG,"UART_TO_FY1000_CCB_QueueSend    ERR ");
	}
	
	return err;
}




/* ����Э�鴦��������ʼ�� */
int fy1000SendMetexInit(void)
{
	osMutexDef(fy1000SendMutex);
	fy1000SendMutexHandle = osMutexCreate(osMutex(fy1000SendMutex));
	
	if(fy1000SendMutexHandle == NULL)
	{
		return -1;
	}
	return 0;
}


 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
