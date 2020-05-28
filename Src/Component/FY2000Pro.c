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
* @brief :���ļ�����FY-2000ϵ�в�Ʒ��������ͨ��Э��
* 
* 
* 
*
* @author :��ΰ
* @date :2017/9/5 16:30
***************************************************************
*/ 
#define _FY2000PRO_C_
#include "FY2000Pro.h"
#include "main.h"


UART_TO_FY2000_QueueSend_Stru FY2000_Q_RX_Buffer;		//ͨ�ŷ��Ͷ��� ���ջ�����
UART_TO_FY2000_QueueSend_Stru* FY2000_Q_RX_BufferP;	//ͨ�ŷ��Ͷ��� ���ջ�����



/*
��������:FY2000_Pack_RxServer_S
��������:Э��Ԥ�����������  �����ն��л����������ݽ��н��������������
*/

void FY2000_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
{
	INT8U Bufer;
	INT32U DataBdry =0;	//��Ч�������߽�
	FY2000_Pack_Uni* FY2000_RXPack =(FY2000_Pack_Uni*)(Ctrl_Point->InputPack);
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
			case 0: //������ʼ��
			{
				if (Bufer == FY2000Pro_StartCode) 
				{ 
					Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
					Ctrl_Point->RecPackPoint +=1;
					Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
					Ctrl_Point->RecPackState=1; 					//��ʼ�������ݰ�
					DataBdry =0;
					
				}
			}break;
			
			case 1: //����Э������
			{		
				if ( Bufer == FY2000Pro_ProtocolCode)
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
	
			case 4: //����SN ��3�ֽ�
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=5;//��ʼ�������ݰ� 

			}break;
			case 5: //����SN ��4�ֽ�
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=6;//��ʼ�������ݰ� 

			}break; 		

			case 6: //����DESN��1�ֽ�
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=7;//��ʼ�������ݰ� 

					
			}break; 
			
			case 7://����DESN��2�ֽ�
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=8;//��ʼ�������ݰ� 			
			}break;
			
			case 8://����GN��1�ֽ�
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=9;//��ʼ�������ݰ� 	


			}break;

			case 9://����GN��2�ֽ�
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=10;//��ʼ�������ݰ� 	


			}break;			

			case 10://����ConType
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=11;//��ʼ�������ݰ�	
				
			}break;

			case 11:	//���ݳ���
			{

				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������

				if(FY2000_RXPack->DefaultPack.Lenth )	//�ж����������Ƿ����
				{
					Ctrl_Point->RecPackState=12;			//��ʼ�������ݰ�
				}
				else
				{
					Ctrl_Point->RecPackState=13;			//��ʼ�������ݰ�
				}
				DataBdry =FY2000_RXPack->DefaultPack.Lenth;
			}break;
		
			case 12:	//��Ч������
			{		


				
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint] =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=12;					//��ʼ�������ݰ�

				DataBdry -=1;
				if(DataBdry ==0)
			//	if ( (FY2000_RXPack->DefaultPack.Lenth + FY2000Pro_HeadSize)==Ctrl_Point->RecPackPoint)
				{
					Ctrl_Point->RecPackState=13;
				}


				
			}break;

			case 13:	//У���
			{
				
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint] =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=14;					//��ʼ�������ݰ�
				
			}break;
			
			case 14:	//������־
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackState=0; 
				
				if (Bufer ==FY2000Pro_EndCode)
				{
					FY2000_Pack_RxAnalyze_S(Ctrl_Point,FY2000_RXPack->DefaultPack.Lenth+FY2000Pro_HeadSize);
				}
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);
			}break; 
			
			default:	//����״̬,�ָ�״̬Ϊ0
			{
				Ctrl_Point->RecPackState=0;

			}break;
		}
		
		if (++Ctrl_Point->Rx_Rear >= UART_TO_FY2000BufferSize_S)
		{
			Ctrl_Point->Rx_Rear=0;
		}	

	}
/* �޲���ϵͳ������ʹ��   ������ϵͳ�����½��� ������������ 		*/
//	FY2000_Pack_TxServer_S(Ctrl_Point);		//���������
}



 
/*

��������:void  RXPack_AnalyzeForyonV10(INT8U PortNum,INT16U DataNum)
��������:ͨ�Ž����������Ӻ���
*/
INT8U FY2000_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize)
{
	INT8U CheckFlg =0;	//�����־
	INT16U ProtoNO =0;	//Э����
	FY2000_Pack_Uni* Packin =(FY2000_Pack_Uni*)Ctrl_Point->InputPack;	//ָ��任
	
	CheckFlg =SUMCheck_Check(((INT8U*)Ctrl_Point->InputPack),DataSize);
	if(CheckFlg !=0)//У������˳�����
	{
		return	CheckFlg;
	}
	else
	{
		ProtoNO =Packin->DefaultPack.ConType;//����Э�����
		CheckFlg =FY2000_Pack_Rx_S(Ctrl_Point,ProtoNO);
	}
	return CheckFlg;
}




/*
50����Ӻ���
*/
void FY2000_Pack_50(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT8U PackSize =0;
	
	PackData->Pack_50.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_50.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_50.Head.SN =FY2000Pro_BroadcastAddr;
	PackData->Pack_50.Head.DESN =0;
	PackData->Pack_50.Head.GN =0;
	PackData->Pack_50.Head.ConType =50;

	PackData->Pack_50.Head.Lenth =sizeof(FY2000_Pack50_Stru)-FY2000Pro_HeadSize-2;//ʵ����Ч����������
	PackSize =sizeof(FY2000_Pack50_Stru)-2;	//У�����ݳ��ȼ���

	if(PCF8563_Read(&RTC_Time) ==HAL_OK)
	{
		PackData->Pack_50.Year =RTC_Time.Year;
		PackData->Pack_50.Month =RTC_Time.Month;
		PackData->Pack_50.Day =RTC_Time.Day;
		PackData->Pack_50.Hour =RTC_Time.Hour;
		PackData->Pack_50.Minute =RTC_Time.Minute;
		PackData->Pack_50.Second =RTC_Time.Second;
		PackData->Pack_50.Week =RTC_Time.Week;
		
		PackData->Pack_50.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
		PackData->Pack_50.End =FY2000Pro_EndCode;
		
		PackSize+=2;
		PORT->OutputPackSize =PackSize;
		PORT->PackSendFlag =ENABLE;
	}
}



/*
51����Ӻ���
*/
void FY2000_Pack_51(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_51.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_51.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_51.Head.SN =FY2000Pro_BroadcastAddr;
	PackData->Pack_51.Head.DESN =0;
	PackData->Pack_51.Head.GN =0;
	PackData->Pack_51.Head.ConType =51;
	
	PackData->Pack_51.Head.Lenth =sizeof(FY2000_Pack51_Stru)-FY2000Pro_HeadSize-2;//ʵ����Ч����������
	PackSize =sizeof(FY2000_Pack51_Stru)-2; //У�����ݳ��ȼ���


	PackData->Pack_51.Delay =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_51.Delay;	

	PackData->Pack_51.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_51.End =FY2000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE;

}




/*
	52����Ӻ���
	��������ȫ���ط�����
*/
void FY2000_Pack_52(UART_RBC_Stru* PORT)
{
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;
	{

		PackData->Pack_52.Head.Start =FY2000Pro_StartCode;
		PackData->Pack_52.Head.Version =FY2000Pro_ProtocolCode;
		PackData->Pack_52.Head.SN =FY2000Pro_BroadcastAddr;
		PackData->Pack_52.Head.DESN =0;
		PackData->Pack_52.Head.GN =0;
		PackData->Pack_52.Head.ConType =52;
		PackData->Pack_52.Head.Lenth =2;
		
		PackData->Pack_52.Head.Lenth =sizeof(FY2000_Pack52_Stru)-FY2000Pro_HeadSize-2;//ʵ����Ч����������
		PackSize =sizeof(FY2000_Pack52_Stru)-2; //У�����ݳ��ȼ���

		PackData->Pack_52.Delay =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_52.Delay;

		PackData->Pack_52.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
		PackData->Pack_52.End =FY2000Pro_EndCode;

		PackSize+=2;
		PORT->OutputPackSize =PackSize;
		PORT->PackSendFlag =ENABLE;	
	}
	
}






/*
53����Ӻ���
�������͹㲥���ط�����

*/
void FY2000_Pack_53(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;



	PackData->Pack_53.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_53.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_53.Head.SN =FY2000Pro_BroadcastAddr;
	PackData->Pack_53.Head.DESN =0X0000;
	PackData->Pack_53.Head.GN =0X0000;
	PackData->Pack_53.Head.ConType =53;

	PackData->Pack_53.Head.Lenth =sizeof(FY2000_Pack53_Stru)-FY2000Pro_HeadSize-2;//ʵ����Ч����������
	PackSize =sizeof(FY2000_Pack53_Stru)-2; //У�����ݳ��ȼ���

	PackData->Pack_53.ValveCtrlDemandFlg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_53.ValveCtrlDemandFlg;
	PackData->Pack_53.CtrlFlg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_53.CtrlFlg;
	
	PackData->Pack_53.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_53.End =FY2000Pro_EndCode;
	
	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 


	
}







/*
54����Ӻ���
�������Ϳ������ط���ǿ�������ȶ�������


*/
void FY2000_Pack_54(UART_RBC_Stru* PORT)
{

	
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_54.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_54.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_54.Head.SN =FY2000_Q_RX_Buffer.ID;	
	PackData->Pack_54.Head.DESN =0;	
	PackData->Pack_54.Head.GN =0;
	PackData->Pack_54.Head.ConType =54;
	PackData->Pack_54.Head.Lenth =2;

	PackData->Pack_54.Head.Lenth =sizeof(FY2000_Pack54_Stru)-FY2000Pro_HeadSize-2;//ʵ����Ч����������
	PackSize =sizeof(FY2000_Pack54_Stru)-2; //У�����ݳ��ȼ���

	PackData->Pack_54.ValveCtrlDemandFlg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_54.ValveCtrlDemandFlg;	
	PackData->Pack_54.CtrlFlg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_54.CtrlFlg;	

	PackData->Pack_54.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_54.End =FY2000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 



}

 
 
 /*
 55����Ӻ���
 ���������ն�ʱ��У׼����
 */
 void FY2000_Pack_55(UART_RBC_Stru* PORT)
 {
	 FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	 //ָ��任
	 INT16U PackSize =0;


	 PackData->Pack_55.Head.Start =FY2000Pro_StartCode;
	 PackData->Pack_55.Head.Version =FY2000Pro_ProtocolCode;
	 PackData->Pack_55.Head.SN =FY2000_Q_RX_Buffer.ID;	
	 PackData->Pack_55.Head.DESN =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_55.Head.DESN;	
	 PackData->Pack_55.Head.GN =0;
	 PackData->Pack_55.Head.ConType =55;

	 PackData->Pack_55.Head.Lenth =sizeof(FY2000_Pack55_Stru)-FY2000Pro_HeadSize-2;//ʵ����Ч����������
	 PackSize =sizeof(FY2000_Pack55_Stru)-2; //У�����ݳ��ȼ���


	 if(PCF8563_Read(&RTC_Time) ==HAL_OK)
	 {
		 PackData->Pack_55.Year =RTC_Time.Year;
		 PackData->Pack_55.Month =RTC_Time.Month;
		 PackData->Pack_55.Day =RTC_Time.Day;
		 PackData->Pack_55.Hour =RTC_Time.Hour;
		 PackData->Pack_55.Minute =RTC_Time.Minute;
		 PackData->Pack_55.Second =RTC_Time.Second;
		 PackData->Pack_55.Week =RTC_Time.Week;
		 
		 PackData->Pack_55.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
		 PackData->Pack_55.End =FY2000Pro_EndCode;
		 
		 PackSize+=2;
		 PORT->OutputPackSize =PackSize;
		 PORT->PackSendFlag =ENABLE; 

	 }

 }






/*
59����Ӻ���
�����������ݲɼ�����

*/
void FY2000_Pack_59(UART_RBC_Stru* PORT )
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;
	{
		
		PackData->Pack_59.Head.Start =FY2000Pro_StartCode;
		PackData->Pack_59.Head.Version =FY2000Pro_ProtocolCode;
		PackData->Pack_59.Head.SN =FY2000_Q_RX_Buffer.ID;	
		PackData->Pack_59.Head.DESN =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Head.DESN;
		PackData->Pack_59.Head.GN =0;
		PackData->Pack_59.Head.ConType =59;

		PackData->Pack_59.Head.Lenth =sizeof(FY2000_Pack59_Stru)-FY2000Pro_HeadSize-2;//ʵ����Ч����������
		PackSize =sizeof(FY2000_Pack59_Stru)-2; //У�����ݳ��ȼ���

		
		PackData->Pack_59.DATA =0XAAAA;
		PackData->Pack_59.LoopTime =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.LoopTime;
		
		PackData->Pack_59.Apportion_Energy =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Apportion_Energy;
		PackData->Pack_59.Remain_Heat =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Remain_Heat;
		PackData->Pack_59.Total_Heat =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Total_Heat;
		
		PackData->Pack_59.ControlType =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.ControlType;

		if((FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.ForceCtrlFlg ==0X55)||(FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.ForceCtrlFlg ==0XAA))
		{
			PackData->Pack_59.ForceCtrlFlg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.ForceCtrlFlg;
		}
		else
		{
			PackData->Pack_59.ForceCtrlFlg =0XFF;
		}

		if( FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Set_TCtrlFg ==0XAA)
		{
			PackData->Pack_59.Set_TCtrlFg =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Set_TCtrlFg;
		}
		else
		{
			PackData->Pack_59.Set_TCtrlFg =0X00;
		}
		
		PackData->Pack_59.Set_Temp =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.Set_Temp;


		if( FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.LimtTE_Flag ==0XAA)
		{
			PackData->Pack_59.LimtTE_Flag =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.LimtTE_Flag;
		}
		else
		{
			PackData->Pack_59.LimtTE_Flag =0XFF;
		}		
		PackData->Pack_59.LimtTE_Value =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_59.LimtTE_Value;
		
		PackData->Pack_59.Year_S =SysPara.StartTime.Year;
		PackData->Pack_59.Month_S =SysPara.StartTime.Month;
		PackData->Pack_59.Day_S =SysPara.StartTime.Day;
		PackData->Pack_59.Hour_S =SysPara.StartTime.Hour;
		PackData->Pack_59.Minute_S =SysPara.StartTime.Minute;
		PackData->Pack_59.Second_S =SysPara.StartTime.Second;

		PackData->Pack_59.Year_F =SysPara.FinalTime.Year;
		PackData->Pack_59.Month_F =SysPara.FinalTime.Month;
		PackData->Pack_59.Day_F =SysPara.FinalTime.Day;
		PackData->Pack_59.Hour_F =SysPara.FinalTime.Hour;
		PackData->Pack_59.Minute_F =SysPara.FinalTime.Minute;
		PackData->Pack_59.Second_F =SysPara.FinalTime.Second;

		PackData->Pack_59.Buld =1;
		PackData->Pack_59.Unit=1;
		PackData->Pack_59.Floor=1;
		PackData->Pack_59.Cell=1;

		PackData->Pack_59.CellArea=10000;
		PackData->Pack_59.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
		PackData->Pack_59.End =FY2000Pro_EndCode;
		
		PackSize+=2;
		PORT->OutputPackSize =PackSize;
		PORT->PackSendFlag =ENABLE; 
		
	}
	
}




/*
60����Ӻ���
���������ն�ͨ�Ų�������
*/
void FY2000_Pack_60(UART_RBC_Stru* PORT)
{
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;



	PackData->Pack_60.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_60.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_60.Head.SN =FY2000_Q_RX_Buffer.ID;
	PackData->Pack_60.Head.DESN =FY2000_Q_RX_Buffer.SendData.FY2000Data.Pack_60.Head.DESN;
	PackData->Pack_60.Head.GN =0;
	PackData->Pack_60.Head.ConType =60;

	PackData->Pack_60.Head.Lenth =sizeof(FY2000_Pack60_Stru)-FY2000Pro_HeadSize-2;//ʵ����Ч����������
	PackSize =sizeof(FY2000_Pack60_Stru)-2; //У�����ݳ��ȼ���


	if(PCF8563_Read(&RTC_Time) ==HAL_OK)
	{
		PackData->Pack_60.Year =RTC_Time.Year;
		PackData->Pack_60.Month =RTC_Time.Month;
		PackData->Pack_60.Day =RTC_Time.Day;
		PackData->Pack_60.Hour =RTC_Time.Hour;
		PackData->Pack_60.Minute =RTC_Time.Minute;
		PackData->Pack_60.Second =RTC_Time.Second;
		PackData->Pack_60.Week =RTC_Time.Week;

		PackData->Pack_60.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
		PackData->Pack_60.End =FY2000Pro_EndCode;

		PackSize+=2;
		PORT->OutputPackSize =PackSize;
		PORT->PackSendFlag =ENABLE; 
	}
}


/*
61����Ӻ���
�����㲥���͹�ů��ʼ����

*/
void FY2000_Pack_61(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_61.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_61.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_61.Head.SN =FY2000Pro_BroadcastAddr;
	PackData->Pack_61.Head.DESN =0;
	PackData->Pack_61.Head.GN =0;
	PackData->Pack_61.Head.ConType =61;

	PackData->Pack_61.Head.Lenth =sizeof(FY2000_Pack61_Stru)-FY2000Pro_HeadSize-2;//ʵ����Ч����������
	PackSize =sizeof(FY2000_Pack61_Stru)-2; //У�����ݳ��ȼ���



		
	PackData->Pack_61.Year_S =SysPara.StartTime.Year;
	PackData->Pack_61.Month_S =SysPara.StartTime.Month;
	PackData->Pack_61.Day_S =SysPara.StartTime.Day;
	PackData->Pack_61.Hour_S =SysPara.StartTime.Hour;
	PackData->Pack_61.Minute_S =SysPara.StartTime.Minute;
	PackData->Pack_61.Second_S =SysPara.StartTime.Second;

	PackData->Pack_61.Year_F =SysPara.FinalTime.Year;
	PackData->Pack_61.Month_F =SysPara.FinalTime.Month;
	PackData->Pack_61.Day_F =SysPara.FinalTime.Day;
	PackData->Pack_61.Hour_F =SysPara.FinalTime.Hour;
	PackData->Pack_61.Minute_F =SysPara.FinalTime.Minute;
	PackData->Pack_61.Second_F =SysPara.FinalTime.Second;
	
	PackData->Pack_61.TimeSetFlag =0XAA;
	
	PackData->Pack_61.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_61.End =FY2000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 

	
}




/*
62����Ӻ���
�����㲥���͹�ů��ͨ�Ͽ��������������������

*/
void FY2000_Pack_62(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT16U PackSize =0;

	PackData->Pack_62.Head.Start =FY2000Pro_StartCode;
	PackData->Pack_62.Head.Version =FY2000Pro_ProtocolCode;
	PackData->Pack_62.Head.SN =FY2000Pro_BroadcastAddr;
	PackData->Pack_62.Head.DESN =0;
	PackData->Pack_62.Head.GN =0;
	PackData->Pack_62.Head.ConType =62;

	PackData->Pack_62.Head.Lenth =sizeof(FY2000_Pack62_Stru)-FY2000Pro_HeadSize-2;//ʵ����Ч����������
	PackSize =sizeof(FY2000_Pack62_Stru)-2; //У�����ݳ��ȼ���

	
	PackData->Pack_62.DATA =0XAAAA;
	
	PackData->Pack_62.Check =SUMCheck_Input((INT8U*)PackData,PackSize);
	PackData->Pack_62.End =FY2000Pro_EndCode;

	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE; 
}



/*
128����Ӻ���

*/
INT8U  FY2000_Pack_128(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X00;
	
	if ( PackData->Pack_128.CtrlFlg ==0XAA)
	{
		BackVal =0X00;
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}



/*
129����Ӻ���

*/
INT8U  FY2000_Pack_129(UART_RBC_Stru* PORT)
{
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X00;

	if ( PackData->Pack_129.CtrlFlg ==0XAAAA)
	{
		BackVal =0X00;
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}





/*
131����Ӻ���

*/
INT8U  FY2000_Pack_131(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X00;

	if ( PackData->Pack_131.CtrlFlg ==0XAAAA)
	{
		BackVal =0X00;
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}



/*
132�����Ӻ���

*/
INT8U  FY2000_Pack_132(UART_RBC_Stru* PORT)
{

	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT16U DESN =PackData->Pack_132.Head.DESN;
	INT8U BackVal =0X01;
	INT32U MeterID =PackData->Pack_132.Head.SN;
	if ( MeterID !=0)
	{
		if(ClientCH1Ctrler.Device.ID ==MeterID)
		{
			if(SysDeviceList.Device[DESN].ID ==MeterID) //�豸���ͺͲ�ƷID������ƥ����֤
			{
				BackVal =0X00;
			}
		}
	}
	return BackVal;
}



/*
133����Ӻ���

*/

INT8U  FY2000_Pack_133(UART_RBC_Stru* PORT)
{
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X00;
	
	if ( PackData->Pack_133.CtrlFlg ==0XAAAA)
	{
		BackVal =0X00;
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}



/*
134����Ӻ���
*/
INT8U  FY2000_Pack_134(UART_RBC_Stru* PORT)
{
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X00;

	if( PackData->Pack_134.CtrlFlg ==0XAAAA)
	{
		BackVal =0X00;
	}
	else
	{
		BackVal =0X01;
	}
	return BackVal;
}







/*

��������: INT8U FY2000_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
��������:��Դ�ǿ�Э����շ�����
Ctrl_Point:���տ�����
Protocol: Э����
����ֵ: 0X00 Э������ 0X01 Э�鴦��������� 0XFF Э�鲻����
*/
INT8U FY2000_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
{

	INT8U ErrorFlg =0;
	FY2000_Pack_Uni* PackData =(FY2000_Pack_Uni*)(Ctrl_Point->InputPack);		   	//����ָ�뽻��
	FY2000_Pack_Uni* PackOUTData =(FY2000_Pack_Uni*)(Ctrl_Point->OutputPack);	    //���ָ�뽻��
	INT8U Proto_RX =Protocol;
	
	PackData =PackData;
	PackOUTData =PackOUTData;
	switch (Proto_RX)
	{
		case 128:
		{
			UART_TO_FY1000_QueueSend_Stru SendBuffer;
			ClientCH1Ctrler.SignleCom =RESET;
			
			ErrorFlg =FY2000_Pack_128(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				SendBuffer.SendData.Pack_0X0E.DevType =ClientCH1Ctrler.Device.Type;
				SendBuffer.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
				SendBuffer.SendData.Pack_0X0E.State =COMBack_OK;
				dbg_printf(DEBUG_INFO,"���Ŷ���ִ�гɹ�...������:%d  ���%08lX",ClientCH1Ctrler.Device.Type,ClientCH1Ctrler.Device.ID);
			}
			else
			{
				SendBuffer.SendData.Pack_0X0E.DevType =ClientCH1Ctrler.Device.Type;
				SendBuffer.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
				SendBuffer.SendData.Pack_0X0E.State =COMBack_FT;
				dbg_printf(DEBUG_INFO,"���Ŷ���ִ��ʧ��...������:%d  ���%08lX",ClientCH1Ctrler.Device.Type,ClientCH1Ctrler.Device.ID);
			}
			FY_1000Send_Code_QInput(&SendBuffer,0X0E);
			

			
		}break;
		case 129:
		{
			ErrorFlg =FY2000_Pack_129(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				ClientCH1Ctrler.SignleCom =RESET;
			}			 
		}break;
		
		case 131:
		{
			ErrorFlg =FY2000_Pack_131(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				ClientCH1Ctrler.SignleCom =RESET;
			}				 
		}break;

		case 132:
		{
			ErrorFlg =FY2000_Pack_132(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				INT16U DESN =PackData->Pack_132.Head.DESN;
				INT16U UserNum =0;		//�û����
				INT8U DevType =ClientCH1Ctrler.Device.Type;
				if( DevType ==Valve_U)
				{
					
					SysDevData[DESN].Device3.Cur_Temp =PackData->Pack_132.Cur_Temp;		//��ǰ�¶�
					SysDevData[DESN].Device3.Ave_Temp =PackData->Pack_132.Ave_Temp;		//ƽ���¶�
					SysDevData[DESN].Device3.Input_Temp =PackData->Pack_132.Input_Temp;		//����¶�
					SysDevData[DESN].Device3.Output_Temp =PackData->Pack_132.Output_Temp;	//�����¶�
					SysDevData[DESN].Device3.ValvePosition =PackData->Pack_132.Valve_POS;		//����λ��
					SysDevData[DESN].Device3.Cycle_OpTim =PackData->Pack_132.Cycle_OpTim;	//���ڿ���ʱ��/��ů�����ۼƿ���ʱ��
					SysDevData[DESN].Device3.Cycle_OpRat =PackData->Pack_132.Cycle_OpRat;	//���ڿ�������

					SysDevData[DESN].Device3.Face_State =PackData->Pack_132.Face_State;		//���״̬
					SysDevData[DESN].Device3.Valve_State =PackData->Pack_132.Valve_STate; 	//����״̬

					if( SysDevData[DESN].Device3.Set_TCtrlFg !=0XAA)						//�û�����¶Ȳ���ϵͳ����
					{
						SysDevData[DESN].Device3.Set_Temp =PackData->Pack_132.Set_Temp;
					}
					
					SysDevStatus[DESN].Device3.ComSucNum +=1;
					SysDevStatus[DESN].Device3.ComFauNum =0;

					/*ͨ��ʱ����������������豸���ݺ��û�����ƥ��*/
					if( SysPara.DeviceType ==Type_Valve)	//ͨ��ʱ��������ȼ���ϵͳ
					{
						INT32U UserID =ClientCH1Ctrler.Device.UserKEY;
						
						if(GetUser_Num(UserID,&UserNum ) ==HAL_OK) //�û���ѯ�ɹ�
						{
							UserData[UserNum].Total_Time =SysDevData[DESN].Device3.Cycle_OpTim;	//�����ſ������ݴ��ݸ��û�
							SysDevData[DESN].Device3.Apportion_Energy =UserData[UserNum].Apportion_Energy;		//���û��ķ�̯�����ش���ͨ�Ͽ�����
							
							 if(UserData_Save(UserNum) ==HAL_OK)
							 {
								dbg_printf(DEBUG_DEBUG,"�û����ݱ���  ���: %d \r\n ",UserNum);
							 }
						}						
					}


					if( SysDevData_Save(DESN) ==HAL_OK)
					{
						dbg_printf(DEBUG_DEBUG,"�豸���ݱ���  ���: %d \r\n ",DESN);
					}


					
/*
ͨ�Ͽ�����������¶ȵĵ���
Ŀǰֻ��������ɽ�ȼ�����Ŀ	2017 11
**********************************************************************************/
#if (1== Valve_U_TempChange)
					/*�����û���ѯ����ĵ�ʵʱ����*/
					INT16U Temp_IN =SysDevData[DESN].Device3.Input_Temp;
					INT16U Temp_OUT =SysDevData[DESN].Device3.Output_Temp;
					
					INT16U Temp_IN_B =0;
					INT16U Temp_OUT_B =0;

					if((Temp_IN >3500)||(Temp_OUT >3500))
					{
						INT32U BuildMeterID =0;	
						INT16U DevNum =0;
						BuildMeterID =SysUserList.User[UserNum].BuildMeter_ID;
						
						if( GetMeters_Num(BuildMeterID, Meter_H,&DevNum)==HAL_OK)
						{
							Temp_IN_B =SysDevData[DevNum].Device5.Input_Temp;
							Temp_OUT_B =SysDevData[DevNum].Device5.Output_Temp;
							
							if( (Temp_IN_B >1000)&&(Temp_OUT_B>1000)&&(SysDevStatusErr[DevNum]==0x00))	//¥�����¶�������Ч  ͨ������
							{
								time_t seed =RTC_TimeTicks;
								INT32U cal =0;
								INT16S cal0 =0;	
								
								srand(seed);
								cal = rand();
								cal0 =cal%99;
								
								cal0=cal0-50;
								if(cal0 >0)
								{
									Temp_IN =Temp_IN_B+cal0;
									Temp_OUT =Temp_OUT_B+cal0;
								}
								else
								{
									Temp_IN =Temp_IN_B-(0-cal0);
									Temp_OUT =Temp_OUT_B-(0-cal0);
								}
								
							}
						}
					}
					SysDevData[DESN].Device3.Input_Temp =Temp_IN;
					SysDevData[DESN].Device3.Output_Temp =Temp_OUT;
					
#endif

/*END********************************************************************** */


					/* ��̨ʵʱ����ת��   �Զ�����*/
						//if( SysPara.SendMode ==DevSendMode_Auto )//�����ϱ�����Ϊ�Զ�����	�����ⲿ�������ݳ��� 
						if(( SysPara.SendMode ==DevSendMode_Auto)&&( ClientCH1Ctrler.UaComFlg ==0))//�����ϱ�����Ϊ�Զ�����	�����ⲿ�������ݳ��� 
						{
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.CtrlFlag=0XAA;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_Type=Valve_U;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_ID =ClientCH1Ctrler.Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.BackFlag=COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Set_Temp =SysDevData[DESN].Device3.Set_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cur_Temp =SysDevData[DESN].Device3.Cur_Temp;							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Ave_Temp =SysDevData[DESN].Device3.Ave_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Input_Temp =SysDevData[DESN].Device3.Input_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Output_Temp =SysDevData[DESN].Device3.Output_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.ValvePosition =SysDevData[DESN].Device3.ValvePosition;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cycle_OpTim =SysDevData[DESN].Device3.Cycle_OpTim;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Cycle_OpRat =0;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Apportion_Energy =SysDevData[DESN].Device3.Apportion_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Face_State =SysDevData[DESN].Device3.Face_State;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Valve_State =SysDevData[DESN].Device3.Valve_State;

							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸�Զ���������ת����������  ���: %d SN:%08lX\r\n ",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D3.Dev_ID);
							}
						}
					/* ��̨ʵʱ����ת�� �Զ�����END*/

					/* ��̨ʵʱ����ת��   �Զ�����*/
						if( ClientCH1Ctrler.UaComFlg !=0 )//�����ϱ�����Ϊ�Զ�����	�����ⲿ�������ݳ��� 
						{
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.CtrlFlag=0XAA;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Dev_Type=Valve_U;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Dev_ID =ClientCH1Ctrler.Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.BackFlag=COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Set_Temp =SysDevData[DESN].Device3.Set_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Cur_Temp =SysDevData[DESN].Device3.Cur_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Ave_Temp =SysDevData[DESN].Device3.Ave_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Input_Temp =SysDevData[DESN].Device3.Input_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Output_Temp =SysDevData[DESN].Device3.Output_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.ValvePosition =SysDevData[DESN].Device3.ValvePosition;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Cycle_OpTim =SysDevData[DESN].Device3.Cycle_OpTim;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Cycle_OpRat =0;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Apportion_Energy =SysDevData[DESN].Device3.Apportion_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Face_State =SysDevData[DESN].Device3.Face_State;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Valve_State =SysDevData[DESN].Device3.Valve_State;
							


							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0X02)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸Զ�̳�������ת����������  ���: %d SN:%08lX\r\n ",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0X02_D3.Dev_ID);
							}
						}
					/* ��̨ʵʱ����ת�� �Զ�����END*/

					
					ClientCH1Ctrler.SignleCom =RESET;

				}
				
				else if(DevType ==Valve_UH )			//��ˮͨ�Ͽ�����   �豸����4
				{

					SysDevData[DESN].Device4.ValvePosition =PackData->Pack_132.Valve_POS;		//����λ��
					
					SysDevData[DESN].Device4.Cycle_OpTim =PackData->Pack_132.Cycle_OpTim;	//���ڿ���ʱ��/��ů�����ۼƿ���ʱ��
					SysDevData[DESN].Device4.Cycle_OpRat =PackData->Pack_132.Cycle_OpRat;	//���ڿ�������

					SysDevData[DESN].Device4.Valve_State =PackData->Pack_132.Valve_STate; 	//����״̬

				
					SysDevStatus[DESN].Device4.ComSucNum +=1;
					SysDevStatus[DESN].Device4.ComFauNum =0;
					
					if( SysDevData_Save(DESN) ==HAL_OK)
					{
						dbg_printf(DEBUG_DEBUG,"�豸���ݱ���  ���: %d \r\n ",DESN);
					}

					/* ��̨ʵʱ����ת��  �Զ����� */
						//if( SysPara.SendMode ==DevSendMode_Auto )//�����ϱ�����Ϊ�Զ�����	�����ⲿ�������ݳ��� 
						if(( SysPara.SendMode ==DevSendMode_Auto)&&( ClientCH1Ctrler.UaComFlg ==0))//�����ϱ�����Ϊ�Զ�����	�����ⲿ�������ݳ��� 
						{
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.CtrlFlag=0XAA;							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_Type=Valve_UH;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID =ClientCH1Ctrler.Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.BackFlag=COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ValvePosition =SysDevData[DESN].Device4.ValvePosition;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpTim =SysDevData[DESN].Device4.Cycle_OpTim;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpRat =0;							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Apportion_Energy =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Valve_State =SysDevData[DESN].Device4.Valve_State;
							
							
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸�Զ���������ת����������  ���: %d SN:%08lX",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID);
							}
						}
					/* ��̨ʵʱ����ת�� �Զ�����END*/		

					/* ��̨ʵʱ����ת��  Զ�̳��� */
						if( ClientCH1Ctrler.UaComFlg !=0 )//�����ϱ�����Ϊ�Զ�����	�����ⲿ�������ݳ��� 
						{
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.CtrlFlag=0XAA;							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_Type=Valve_UH;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_ID =ClientCH1Ctrler.Device.ID;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.BackFlag=COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.ValvePosition =SysDevData[DESN].Device4.ValvePosition;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Cycle_OpTim =SysDevData[DESN].Device4.Cycle_OpTim;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Cycle_OpRat =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Apportion_Energy =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Valve_State =SysDevData[DESN].Device4.Valve_State;
							
							
							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0X02)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸Զ�̳�������ת����������  ���: %d SN:%08lX",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_ID);
							}
						}
					/* ��̨ʵʱ����ת�� Զ�̳���END*/						
					
					ClientCH1Ctrler.SignleCom =RESET;
				}
			}				 
		}break;
		
		case 133:
		{
			ErrorFlg =FY2000_Pack_133(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				ClientCH1Ctrler.SignleCom =RESET;
			}				 
		}break;
		default :ErrorFlg =0XFF; break;
	}
	return ErrorFlg;
}




 


/*
FY188_���������

*/
INT8U FY2000_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point)
{

	BaseType_t Err;

	
	/* ���߿���״̬��� */
//	if(*(Ctrl_Point->SendBusy) != HAL_OK)		//���߿���״̬���
//	{
//		return HAL_ERROR;
//	}

	/* ���ն������� */
	Err =xQueueReceive(UART_TO_FY2000_Msg,&FY2000_Q_RX_BufferP,5);

	if( Err != pdTRUE)
	{
		return HAL_ERROR;
	}

	/* ���ƴ��������ݲ���� */
	FY2000_Q_RX_Buffer =*FY2000_Q_RX_BufferP;
	Ctrl_Point->PackCreatFlag =FY2000_Q_RX_Buffer.PackCreatFlag;
	Ctrl_Point->PackINPort =FY2000_Q_RX_Buffer.PackINPort;

	/* ����������־��� ���߿���״̬��� */
	if(Ctrl_Point->PackCreatFlag != ENABLE)
	{
		return HAL_ERROR;
	}

	Ctrl_Point->PackCreatFlag =DISABLE;

	/* ���Э����ʶ�� */
	switch(Ctrl_Point->PackINPort)
	{
		case 50:
		{
			
			FY2000_Pack_50(Ctrl_Point);
			
		}break;
		
		case 51:
		{
			FY2000_Pack_51(Ctrl_Point);

		}break;

		case 52:
		{
			FY2000_Pack_52(Ctrl_Point);
		}break;		

		case 53:
		{
			FY2000_Pack_53(Ctrl_Point);
		}break;	
		
		case 54:
		{

			FY2000_Pack_54(Ctrl_Point);
			
		}break;
		
		case 55:
		{
			FY2000_Pack_55(Ctrl_Point);
		}break;	

		case 59:
		{
			FY2000_Pack_59(Ctrl_Point);
		}break;	

		case 60:
		{
			FY2000_Pack_60(Ctrl_Point);
			
		}break;	

		case 61:
		{
			FY2000_Pack_61(Ctrl_Point);
			
		}break;
        
        case 62:
		{
			FY2000_Pack_62(Ctrl_Point);
			
		}break;
        
        default:
		{
			Ctrl_Point->PackINPort =0;
		}
		break;
	}

	return HAL_OK;
}






/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
