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
* @date :2018/8/19 11:10
***************************************************************
*/ 
#define _DDF2PRO_C_
#include "DDF2Pro.h"
#include "main.h"

#ifdef  Meter_DDF2_ENABLE	

UART_TO_DDF2_QueueSend_Stru DDF2_Q_RX_Buffer;		//ͨ�ŷ��Ͷ��� ���ջ�����
UART_TO_DDF2_QueueSend_Stru* DDF2_Q_RX_BuffeP;	//ͨ�ŷ��Ͷ��� ���ջ�����P






/*
void DDF2_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
��������:Э��Ԥ�����������  �����ն��л����������ݽ��н��������������

*/
void DDF2_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
{
	INT8U Bufer;
	INT32U DataBdry =0;	//��Ч�������߽�
	DDF2_Pack_Uni* DDF2_RXPack =(DDF2_Pack_Uni*)(Ctrl_Point->InputPack);
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
				if (Bufer == DDF2Pro_StartCode) 
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
				if ( Bufer == DDF2Pro_ProtocolCode)
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

			case 6:	//����SNRE ��1�ֽ�
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=7;//��ʼ�������ݰ� 

					
			}break;	
			
			case 7://����SNRE ��2�ֽ�
			{
					
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
				Ctrl_Point->RecPackState=8;//��ʼ�������ݰ� 			
			}break;
			
			case 8://���ս���FAdd2
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

				if(DDF2_RXPack->DefaultPack.Head.Lenth)	                //�ж����������Ƿ����
				{
					Ctrl_Point->RecPackState=11;			            //��ʼ�������ݰ�
				}
				else
				{
					Ctrl_Point->RecPackState=12;			            //��ʼ�������ݰ�
				}
				DataBdry =DDF2_RXPack->DefaultPack.Head.Lenth;
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
				
				if (Bufer ==DDF2Pro_EndCode)
				{
					DDF2_Pack_RxAnalyze_S(Ctrl_Point,DDF2_RXPack->DefaultPack.Head.Lenth+DDF2Pro_HeadSize);
				}
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);
			}break;	
			
			default:	//����״̬,�ָ�״̬Ϊ0
			{
				Ctrl_Point->RecPackState=0;

			}break;
		}
		
		if (++Ctrl_Point->Rx_Rear >= UART_TO_DDF2BufferSize_S)
		{
			Ctrl_Point->Rx_Rear=0;
		}	

	}

}




/*
INT8U DDF2_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize)
��������:ͨ�Ž����������Ӻ���
*/
INT8U DDF2_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize)
{
	INT8U CheckFlg =0;	//�����־
	INT8U ProtoNO =0;	//Э����
	DDF2_Pack_Uni* Packin =(DDF2_Pack_Uni*)Ctrl_Point->InputPack;	//ָ��任
	
	CheckFlg =SUMCheck_Check(((INT8U*)Ctrl_Point->InputPack),DataSize);
	if(CheckFlg !=0)//У������˳�����
	{
		return	CheckFlg;
	}
	else
	{

		ProtoNO =Packin->DefaultPack.Head.Lenth;
		if(0x05 ==ProtoNO)
		{
            ProtoNO =0x04;
		}
		else if (0x24 ==ProtoNO)
		{
            ProtoNO =0x02;

		}
		CheckFlg =DDF2_Pack_Rx_S(Ctrl_Point,ProtoNO);
	}
	return CheckFlg;
}







/*
	����/������ٲ�ʵʱ��������
*/
void DDF2_Pack_0X01_S(UART_RBC_Stru* PORT)
{

	DDF2_Pack_Uni* PackData =(DDF2_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT8U PackSize =0;
    INT8U TYPE =0;
	

	PackData->Pack_01.Lead1=0XFE;			//ͬ����	
	PackData->Pack_01.Lead2=0XFE;			//ͬ����	
	PackData->Pack_01.Lead3=0XFE;			//ͬ����	
	PackData->Pack_01.Lead4=0XFE;			//ͬ����	
		
	PackData->Pack_01.Head.Start =0X68;
	PackData->Pack_01.Head.Type =0X41;

	PackData->Pack_01.Head.SN =DDF2_Q_RX_Buffer.ID;
	TYPE =DDF2_Q_RX_Buffer.COM_Type;
	if(0==TYPE)
	{
	    TYPE =0X15;
	}

	
	PackData->Pack_01.Head.SNRE =0X2000+TYPE;

	PackData->Pack_01.Head.FAdd2=0X10;
	PackData->Pack_01.Head.ConType =0X01;

	PackData->Pack_01.Head.Lenth =sizeof(DDF2Pro_Pack01_Stru)-DDF2Pro_HeadSize-2-4;//ʵ����Ч����������
	PackSize =sizeof(DDF2Pro_Pack01_Stru)-2;	//У�����ݳ��ȼ���
	


	PackData->Pack_01.Flag =0X902D;
	PackData->Pack_01.SER =0X01;
	
	PackData->Pack_01.Check =SUMCheck_Input((INT8U*)PackData+4,PackSize-4);
	PackData->Pack_01.End =0X16;
	
	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE;
}



/*
	����/����˷��Ϳ�������
*/
void DDF2_Pack_0X03_S(UART_RBC_Stru* PORT)
{

	DDF2_Pack_Uni* PackData =(DDF2_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	INT8U PackSize =0;

	INT8U TYPE =0;
	

	PackData->Pack_03.Lead1=0XFE;			//ͬ����	
	PackData->Pack_03.Lead2=0XFE;			//ͬ����	
	PackData->Pack_03.Lead3=0XFE;			//ͬ����	
	PackData->Pack_03.Lead4=0XFE;			//ͬ����	
		
	PackData->Pack_03.Head.Start =0X68;
	PackData->Pack_03.Head.Type =0X41;

	PackData->Pack_03.Head.SN =DDF2_Q_RX_Buffer.ID;
	TYPE =DDF2_Q_RX_Buffer.COM_Type;
	if(0==TYPE)
	{
	    TYPE =0X15;
	}
	
	PackData->Pack_03.Head.SNRE =0X2000+TYPE;

	PackData->Pack_03.Head.FAdd2=0X10;
	PackData->Pack_03.Head.ConType =0X04;

	PackData->Pack_03.Head.Lenth =sizeof(DDF2Pro_Pack03_Stru)-DDF2Pro_HeadSize-2-4;//ʵ����Ч����������
	PackSize =sizeof(DDF2Pro_Pack03_Stru)-2;	//У�����ݳ��ȼ���
	


	PackData->Pack_03.Flag =0XA017;
	PackData->Pack_03.SER =0X01;
	PackData->Pack_03.OUT =DDF2_Q_RX_Buffer.SendData.DDF2Data.Pack_03.OUT;
	
	PackData->Pack_03.Check =SUMCheck_Input((INT8U*)PackData+4,PackSize-4);
	PackData->Pack_03.End =0X16;
	
	PackSize+=2;
	PORT->OutputPackSize =PackSize;
	PORT->PackSendFlag =ENABLE;
}




/*
	����/����˽����Ǳ���ʵʱ����
*/
INT8U DDF2_Pack_0X02_S(UART_RBC_Stru* PORT)
{

	DDF2_Pack_Uni* PackData =(DDF2_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X00;
	
	if ((PackData->Pack_02.Head.Start==0X68)&&(PackData->Pack_02.Head.Type ==0X41))	//�ڴ��ж�֡ͷ�ĺϷ���
	{
		if ((PackData->Pack_02.Head.SNRE==0x2015))
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
	����/����˽����Ǳ���ʵʱ����
*/
INT8U DDF2_Pack_0X04_S(UART_RBC_Stru* PORT)
{

	DDF2_Pack_Uni* PackData =(DDF2_Pack_Uni*)(PORT->InputPack);	//ָ��任
	INT8U BackVal =0X00;
	
	if ((PackData->Pack_02.Head.Start==0X68)&&(PackData->Pack_02.Head.Type ==0X41))	//�ڴ��ж�֡ͷ�ĺϷ���
	{
		if ((PackData->Pack_02.Head.SNRE==0x2015))
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

INT8U DDF2_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
��������:��Դ�ǿ�Э����շ�����
Ctrl_Point:���տ�����
Protocol: Э����
����ֵ: 0X00 Э������ 0X01 Э�鴦��������� 0XFF Э�鲻����
*/
INT8U DDF2_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
{

	INT8U ErrorFlg =0;
	DDF2_Pack_Uni* PackData =(DDF2_Pack_Uni*)(Ctrl_Point->InputPack);		   	//����ָ�뽻��
	INT8U Proto_RX =Protocol;

	
	switch (Proto_RX)
	{
		case 0X02:
        {
            ErrorFlg =DDF2_Pack_0X02_S(Ctrl_Point);
            if(  ErrorFlg ==0X00)
            {
                
                INT8U DevType =ClientCH1Ctrler.Device.Type;
                INT16U DESN =ClientCH1Ctrler.Device.Num;
                
                
                if(DevType ==Meter_DDF2 )           
                {
                    if(0x01==PackData->Pack_02.IN)
                    {
                        SysDevData[DESN].Device9.ValvePosition =Valve_Close;   //����λ��
                    }
                    else if(0x00==PackData->Pack_02.IN)
                    {
                        SysDevData[DESN].Device9.ValvePosition =Valve_Open;     //����λ��
                    } 
                    else
                    {
                        SysDevData[DESN].Device9.ValvePosition =Valve_Mid;      //����λ��
                    }
                    
                    SysDevData[DESN].Device9.Cycle_OpTim =0;
                    SysDevData[DESN].Device9.Cycle_OpRat =0;

                    SysDevData[DESN].Device9.Valve_State =0;   //����״̬

                
                    SysDevStatus[DESN].Device9.ComSucNum +=1;
                    SysDevStatus[DESN].Device9.ComFauNum =0;
                    
                    if( SysDevData_Save(DESN) ==HAL_OK)
                    {
                        dbg_printf(DEBUG_DEBUG,"�豸���ݱ���  ���: %d \r\n ",DESN);
                    }

                    /* ��̨ʵʱ����ת��  �Զ����� */
                        //if( SysPara.SendMode ==DevSendMode_Auto )//�����ϱ�����Ϊ�Զ�����  �����ⲿ�������ݳ��� 
                        if(( SysPara.SendMode ==DevSendMode_Auto)&&( ClientCH1Ctrler.UaComFlg ==0))//�����ϱ�����Ϊ�Զ�����  �����ⲿ�������ݳ��� 
                        {
                            UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.CtrlFlag=0XAA;                         
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_Type=Meter_DDF2;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID =ClientCH1Ctrler.Device.ID;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.BackFlag=COMBack_OK;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.ValvePosition =SysDevData[DESN].Device9.ValvePosition;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpTim =SysDevData[DESN].Device9.Cycle_OpTim;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Cycle_OpRat =0;                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Apportion_Energy =0;
                            FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Valve_State =SysDevData[DESN].Device9.Valve_State;
                            
                            
                            if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"�豸�Զ���������ת��  ���: %d SN:%08X",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D4.Dev_ID);
                            }
                        }
                    /* ��̨ʵʱ����ת�� �Զ�����END*/       

                    /* ��̨ʵʱ����ת��  Զ�̳��� */
                        if( ClientCH1Ctrler.UaComFlg !=0 )//�����ϱ�����Ϊ�Զ�����   �����ⲿ�������ݳ��� 
                        {
                            UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.CtrlFlag=0XAA;                         
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_Type=Meter_DDF2;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_ID =ClientCH1Ctrler.Device.ID;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.BackFlag=COMBack_OK;
                            
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.ValvePosition =SysDevData[DESN].Device9.ValvePosition;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Cycle_OpTim =SysDevData[DESN].Device9.Cycle_OpTim;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Cycle_OpRat =0;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Apportion_Energy =0;
                            FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Valve_State =SysDevData[DESN].Device9.Valve_State;
                            
                            
                            if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0X02)==pdTRUE)
                            {
                                dbg_printf(DEBUG_DEBUG,"�豸Զ�̳�������ת��  ���: %d SN:%08X",DESN,FY1000_Q_TX_Buffer.SendData.Pack_0X02_D4.Dev_ID);
                            }
                        }
                    /* ��̨ʵʱ����ת�� Զ�̳���END*/                       
                    
                    ClientCH1Ctrler.SignleCom =RESET;
                }
            }


        }break;
		case 0X04:
		{
			UART_TO_FY1000_QueueSend_Stru SendBuffer;
			
			ClientCH1Ctrler.SignleCom =RESET;
			
			ErrorFlg =DDF2_Pack_0X04_S(Ctrl_Point);
			if(  ErrorFlg ==0X00)
			{
				SendBuffer.SendData.Pack_0X0E.DevType =ClientCH1Ctrler.Device.Type;
				SendBuffer.SendData.Pack_0X0E.DevID =ClientCH1Ctrler.Device.ID;
				SendBuffer.SendData.Pack_0X0E.State =COMBack_OK;
				dbg_printf(DEBUG_INFO,"���Ŷ���ִ�гɹ�...������:%d  ���%08X",ClientCH1Ctrler.Device.Type,ClientCH1Ctrler.Device.ID);
			}
			FY_1000Send_Code_QInput(&SendBuffer,0X0E);


		}break;		
		
		default :
		{
		   ErrorFlg =0XFF; 
		}break;

	}
	return ErrorFlg;
}






/*
DDF2_���������

*/
INT8U DDF2_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point)
{

	BaseType_t Err = HAL_ERROR;

	/* ���߿���״̬��� */

	/* ���ն������� */
	Err =xQueueReceive(UART_TO_DDF2_Msg,&DDF2_Q_RX_BuffeP,5);
	if( Err != pdTRUE)
	{
		return HAL_ERROR;
	}

	/* ���ƴ��������ݲ���� */
	DDF2_Q_RX_Buffer =*DDF2_Q_RX_BuffeP;
	Ctrl_Point->PackCreatFlag =DDF2_Q_RX_Buffer.PackCreatFlag;
	Ctrl_Point->PackINPort =DDF2_Q_RX_Buffer.PackINPort;

	
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
			DDF2_Pack_0X01_S(Ctrl_Point);

		}break;

		case 0X03:
		{
			DDF2_Pack_0X03_S(Ctrl_Point);

		}break;

		default:
		{
			Ctrl_Point->PackINPort =0;
		}
		break;
	}
	return HAL_OK;
}











#endif
 
 




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
