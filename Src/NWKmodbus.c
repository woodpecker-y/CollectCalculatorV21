#define _NWKmodbus_C_

#include "PubDef.h"
#ifdef Valve_NWK_ENABLE

#include "NWKmodbus.h"
#include "main.h"


UART_TO_NWK_QueueSend_Stru      NWK_Q_RX_Buffer;		//ͨ�ŷ��Ͷ��� ���ջ�����
UART_TO_NWK_QueueSend_Stru*     NWK_Q_RX_BuffeP;	    //ͨ�ŷ��Ͷ��� ���ջ�����P



/*
void NWK_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
��������:Э��Ԥ�����������  �����ն��л����������ݽ��н��������������
*/
void NWK_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
{
	INT8U  Bufer;
    INT8U  CMD;
	INT32U DataBdry =0;	//��Ч�������߽�
	NWK_Pack_Uni* NWK_RXPack =(NWK_Pack_Uni*)(Ctrl_Point->InputPack);
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
			case 0:	//����modbus�ӻ���ַ
			{
				if (Bufer != 0)
				{
					Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
					Ctrl_Point->RecPackPoint +=1;
					Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
					Ctrl_Point->RecPackState=1;						//��ʼ�������ݰ�
					DataBdry =0;
					
				}
			}break;
			
			case 1:	//����modbus ������
			{	    
                    if ( Bufer == NWKPro_ACKProtocolCode03 )
                    {
                        Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
                        Ctrl_Point->RecPackPoint +=1;
                        Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������ 
                        Ctrl_Point->RecPackState=2;//��ʼ�������ݰ�	
                    }
                    else if( Bufer == NWKPro_ACKProtocolCode06 )
                    {
                        Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
                        Ctrl_Point->RecPackPoint +=1;
                        Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������ 
                        Ctrl_Point->RecPackState=3;//��ʼ�������ݰ�	
                        
                        NWK_RXPack.Lenth = 4;
                    }
			}break;
			
			case 2://���չ����� 03
			{

                    if ( Bufer == NWKPro_ACKProtocolSize)//��ȡ���ݳ���Ϊ 0x38 = (2*0x1C)
                    {
                        NWK_RXPack.Lenth = Bufer;//�������ݳ���
                        
                        Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
                        Ctrl_Point->RecPackPoint +=1;
                        Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
                        Ctrl_Point->RecPackState=3;//��ʼ�������ݰ�	
                    }
		
			}break;
			
			case 3://06 �����������
			{
                if(NWK_RXPack.Lenth)
                {
                    Ctrl_Point->RecPackState=3;			            //��ʼ�������ݰ�
                }
                else
                {
                    Ctrl_Point->RecPackState=4;			            //��ʼ�������ݰ�
                }
                Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
                Ctrl_Point->RecPackPoint +=1;
                Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������

			}break;
            
			case 4://CRC16_H
			{

				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
                Ctrl_Point->RecPackState=5;			            //��ʼ�������ݰ�

			}break;
            
			case 5:	//CRC16_L
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
INT8U NWK_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize)
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

INT8U NWK_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
��������:��Դ�ǿ�Э����շ�����
Ctrl_Point:���տ�����
Protocol: Э����
����ֵ: 0X00 Э������ 0X01 Э�鴦��������� 0XFF Э�鲻����
*/
INT8U NWK_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
{

	INT8U ErrorFlg =0;
	NWK_Pack_Uni* PackData =(NWK_Pack_Uni*)(Ctrl_Point->InputPack);		   	//����ָ�뽻��
	INT8U Proto_RX =Protocol;

	
	switch (Proto_RX)
	{
		case 0X02:
        {
            ErrorFlg =NWK_Pack_0X02_S(Ctrl_Point);
            if(  ErrorFlg ==0X00)
            {
                
                INT8U DevType =ClientCH1Ctrler.Device.Type;
                INT16U DESN =ClientCH1Ctrler.Device.Num;
                
                
                if(DevType ==Meter_NWK )           
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
			
			ErrorFlg =NWK_Pack_0X04_S(Ctrl_Point);
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
NWK�����Ʋɼ������͸�¥����Ԫ���ڷ�modbusЭ�� 01 03 00 00 00 1C 44 03
*/
void NWK_Pack_S(UART_RBC_Stru* PORT)
{

	NWK_Pack_Uni* PackData =(NWK_Pack_Uni*)(PORT->OutputPack);	//ָ��任
	//INT8U PackSize =0;
    //INT8U TYPE =0;

		
	PackData->Pack.Head.Addr 				= NWK_Q_RX_Buffer.ID;			//NWK_Q_RX_Buffer.ID;
	PackData->Pack.Head.CMD  				= 0X03;
	
	PackData->Pack.Register_Addr_H 	        = 0X00;
	PackData->Pack.Register_Addr_L          = 0X00;
	
	PackData->Pack.Register_Num_H 	        = 0X00;
	PackData->Pack.Register_Num_L  	        = 0X1C;
	
	PackData->Pack.CRC16_H 					= 0x44;
	PackData->Pack.CRC16_L 					= 0x03;
	
	//TYPE = 0x0B;                            //NWK_Q_RX_Buffer.COM_Type;
	
    //if(0==TYPE)
    //{
    //    TYPE =0X15;
    //}

	PORT->OutputPackSize = sizeof(NWK_Pack_Stru);
	//PORT->OutputPackSize = PackSize;
	PORT->PackSendFlag =ENABLE;
}




/*
NWK_���������
*/
INT8U NWK_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point)
{

	BaseType_t Err = HAL_ERROR;

	/* ���߿���״̬��� */

	/* ���ն������� */
	Err =xQueueReceive(UART_TO_NWK_Msg, &NWK_Q_RX_BuffeP,5);
	if( Err != pdTRUE)
	{
		return HAL_ERROR;
	}

	/* ���ƴ��������ݲ���� */
	NWK_Q_RX_Buffer =*NWK_Q_RX_BuffeP;
	Ctrl_Point->PackCreatFlag =NWK_Q_RX_Buffer.PackCreatFlag;
	Ctrl_Point->PackINPort =NWK_Q_RX_Buffer.PackINPort;

	
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
			NWK_Pack_S(Ctrl_Point);

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



