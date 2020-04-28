#define _NWKmodbus_C_

#include "PubDef.h"
#ifdef Valve_NWK_ENABLE


#include "main.h"
#include "check.h"
#include "NWKmodbus.h"

UART_TO_NWK_QueueSend_Stru      NWK_Q_RX_Buffer;		//ͨ�ŷ��Ͷ��� ���ջ�����
UART_TO_NWK_QueueSend_Stru*     NWK_Q_RX_BuffeP;	    //ͨ�ŷ��Ͷ��� ���ջ�����P

UINT16 NWK_Rcv_Lenth = 0;

/*
void NWK_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
��������:Э��Ԥ�����������  �����ն��л����������ݽ��н��������������
*/
void NWK_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
{
	INT8U  Bufer;
    //INT8U  CMD;
	INT32U DataBdry =0;	//��Ч�������߽�
	//NWK_Pack_Uni* NWK_RXPack =(NWK_Pack_Uni*)(Ctrl_Point->InputPack);
    
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
                        Ctrl_Point->RecPackState=2; //��ʼ�������ݰ�
                        
                        NWK_Rcv_Lenth = NWKPro_ACKProtocolSize+0x01;       //06�����������������Ϊ4���ֽ�
                        DataBdry = NWKPro_ACKProtocolSize;
                    }
                    else if( Bufer == NWKPro_ACKProtocolCode06 )
                    {
                        Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
                        Ctrl_Point->RecPackPoint +=1;
                        Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������ 
                        Ctrl_Point->RecPackState=2; //��ʼ�������ݰ�	
                        
                        NWK_Rcv_Lenth = 4;       //06�����������������Ϊ4���ֽ�
                        DataBdry = NWK_Rcv_Lenth;
                    }
			}break;
			
			case 2://06 �����������
			{
                if(DataBdry)
                {
                    Ctrl_Point->RecPackState=2;			            //��ʼ�������ݰ�
                }
                else
                {
                    Ctrl_Point->RecPackState=3;			            //��ʼ�������ݰ�
                }
                DataBdry--;
                Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
                Ctrl_Point->RecPackPoint +=1;
                Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������

			}break;
            
			case 3://CRC16_H
			{

				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������
                Ctrl_Point->RecPackState=4;			            //��ʼ�������ݰ�

			}break;
            
			case 4:	//CRC16_L
			{
				Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
				Ctrl_Point->RecPackPoint +=1;
				Ctrl_Point->RecPackTimeOut =*(Ctrl_Point->Ticks);		//�յ����ݼ��ʱ������
                Ctrl_Point->RecPackState = 0;	
                
                NWK_Pack_RxAnalyze_S(Ctrl_Point, NWK_Rcv_Lenth + NWKPro_HeadSize);
				
			}break;

			default:	//����״̬,�ָ�״̬Ϊ0
			{
				Ctrl_Point->RecPackState=0;

			}break;
		}
		
		if (++Ctrl_Point->Rx_Rear >= UART_TO_NWKBufferSize_S)
		{
			Ctrl_Point->Rx_Rear=0;
		}	

	}

}




/*
INT8U DDF2_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point,INT8U DataSize)
��������:ͨ�Ž����������Ӻ���
*/
INT8U NWK_Pack_RxAnalyze_S(UART_RBC_Stru* Ctrl_Point, INT8U DataSize)
{
	unsigned short CRC16 =0;	//�����־
    UINT8 CRC_H = 0;
    UINT8 CRC_L = 0;
    
	//NWK_Pack_Uni* Packin =(NWK_Pack_Uni*)Ctrl_Point->InputPack;	//ָ��任
	
    
    CRC16 = crc_16_modbus((const unsigned char*)Ctrl_Point->InputPack, (unsigned short) DataSize);
    
    CRC_L = CRC16 >> 8;
    CRC_H = CRC16 & 0x00FF;
    
	//CheckFlg =SUMCheck_Check(((INT8U*)Ctrl_Point->InputPack), DataSize);
    
	if(CRC_H != Ctrl_Point->InputPack[DataSize] || CRC_L != Ctrl_Point->InputPack[DataSize+1])//У������˳�����
	{
        CRC16 = 0;
		return	CRC16;
	}
	else
	{
        if(NWK_Rcv_Lenth == NWKPro_ACKProtocolSize+0x01)
        {
            CRC16 =NWK_Pack_Rx_S(Ctrl_Point, 0x03);
        }
        else if(NWK_Rcv_Lenth == 4)
        {
            CRC16 =NWK_Pack_Rx_S(Ctrl_Point, 0x06);
        }
		
	}
	return CRC16;
}










/* ��С��ģʽ��ת */
unsigned char *bytes_reverse(unsigned char *dat, unsigned char len)
{
    unsigned char i = 0, j = 0;
    unsigned char tmp = 0;

    for (i=0,j=len-1; i<=j; ++i,--j)
    {
        tmp     = dat[i];
        dat[i]  = dat[j];
        dat[j]  = tmp;
    }

    return dat;
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

	INT8U ErrorFlg = 0;
	NWK_Pack_Uni* PackData = (NWK_Pack_Uni*)(Ctrl_Point->InputPack);		   	//����ָ�뽻��
	INT8U Proto_RX = Protocol;

	INT16U DevNum = ClientCH1Ctrler.Device.Num;
    INT8U DevType = ClientCH1Ctrler.Device.Type;
    
	switch (Proto_RX)
	{
        case 0x03:
        {
            if( DevType == Valve_NWK )           
            {
                if(PackData->Pack.lenth == 0x38)
                {
                    //if(PackData->Pack.Head.Addr == SysDevData[DevNum].Device11.Address)
                    //{
                        SysDevData[DevNum].Device11.Input_Temp              = (float)*bytes_reverse((unsigned char *)&PackData->Pack.data.Input_Temp, 4);
                        SysDevData[DevNum].Device11.Output_Temp             = (float)*bytes_reverse((unsigned char *)&PackData->Pack.data.Output_Temp, 4);
                        SysDevData[DevNum].Device11.EnterWater_Pressure     = (float)*bytes_reverse((unsigned char *)&PackData->Pack.data.EnterWater_Pressure, 4);
                        SysDevData[DevNum].Device11.ReturnWater_Pressure    = (float)*bytes_reverse((unsigned char *)&PackData->Pack.data.ReturnWater_Pressure, 4);
                        SysDevData[DevNum].Device11.Room_Temp               = (float)*bytes_reverse((unsigned char *)&PackData->Pack.data.Room_Temp, 4);
                        SysDevData[DevNum].Device11.Current_Valve_Open      = (float)*bytes_reverse((unsigned char *)&PackData->Pack.data.Current_Valve_Open, 4);
                        SysDevData[DevNum].Device11.SetValue_Open           = (float)*bytes_reverse((unsigned char *)&PackData->Pack.data.SetValue_Open, 4);
                        SysDevData[DevNum].Device11.Temp_Diff               = (float)*bytes_reverse((unsigned char *)&PackData->Pack.data.Temp_Diff, 4);
                        SysDevData[DevNum].Device11.ReturnTemp_Set          = (float)*bytes_reverse((unsigned char *)&PackData->Pack.data.ReturnTemp_Set, 4);
                        SysDevData[DevNum].Device11.PressureDiff_Set        = (float)*bytes_reverse((unsigned char *)&PackData->Pack.data.PressureDiff_Set, 4);
                        SysDevData[DevNum].Device11.Error                   = PackData->Pack.data.Error;
                        SysDevData[DevNum].Device11.Software_Version        = PackData->Pack.data.Software_Version;
                        SysDevData[DevNum].Device11.Run_Mode                = PackData->Pack.data.Run_Mode;
                        SysDevData[DevNum].Device11.Address                 = PackData->Pack.data.Address;
                        SysDevData[DevNum].Device11.Motor_Steering          = PackData->Pack.data.Motor_Steering;
                        SysDevData[DevNum].Device11.Adjust_Switch           = PackData->Pack.data.Adjust_Switch;
                        SysDevData[DevNum].Device11.Adjust_Tigger           = PackData->Pack.data.Adjust_Tigger;
                        SysDevData[DevNum].Device11.Dc_Motor_Speed          = PackData->Pack.data.Dc_Motor_Speed;
                        
                        if( SysDevData_Save(DevNum) ==HAL_OK)
                        {
                            dbg_printf(DEBUG_DEBUG,"�û����ݱ���......���: %d \r\n ",DevNum);
                        }
                        SysDevStatus[DevNum].Device11.ComSucNum +=1;
                        SysDevStatus[DevNum].Device11.ComFauNum =0;
                        
                        
                        ClientCH1Ctrler.SignleCom = RESET;
                    //}
                }
            }
        }break;
        
        case 0x06:
        {
            if(PackData->Pack.Head.Addr == SysDevData[DevNum].Device11.Address)
            {
                if(PackData->Pack.Head.CMD == 0x06)
                {
                    
                    
                    
                    ClientCH1Ctrler.SignleCom = RESET;
                }
            }
            
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

	NWK_Send_Uni* PackData =(NWK_Send_Uni*)(PORT->OutputPack);	//ָ��任
	//INT8U PackSize =0;
    //INT8U TYPE =0;

		
	PackData->Pack.Head.Addr 				= (INT8U)NWK_Q_RX_Buffer.ID;			//NWK_Q_RX_Buffer.ID;
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

	PORT->OutputPackSize = 8; //sizeof(NWK_Pack_Stru);
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



