#define _NWKmodbus_C_

#include "PubDef.h"
#ifdef Valve_NWK_ENABLE


#include "main.h"
#include "check.h"
#include "NWKmodbus.h"

UART_TO_NWK_QueueSend_Stru      NWK_Q_RX_Buffer;		//ͨ�ŷ��Ͷ��� ���ջ�����
UART_TO_NWK_QueueSend_Stru*     NWK_Q_RX_BuffeP;	    //ͨ�ŷ��Ͷ��� ���ջ�����P

UINT16 NWK_Rcv_Lenth = 0;
UINT8 recv_cmd = 0;

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
                        recv_cmd = Bufer;//03
                    }
                    else if( Bufer == NWKPro_ACKProtocolCode06 || Bufer == NWKPro_ACKProtocolCode10)
                    {
                        Ctrl_Point->InputPack[Ctrl_Point->RecPackPoint]  =Bufer;
                        Ctrl_Point->RecPackPoint +=1;
                        Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);	 //�յ����ݼ��ʱ������ 
                        Ctrl_Point->RecPackState=5; //��ʼ�������ݰ�	
                        
                        NWK_Rcv_Lenth = 4;       //06 �� 10 �������������������Ϊ4���ֽ�
                        DataBdry = NWK_Rcv_Lenth;
                        recv_cmd = Bufer;//06 �� 10
                    }
                        
			}break;
			
			case 2://06 �����������
			{

                if(DataBdry>0)
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
            
			case 5://06 �����������
			{
                DataBdry--;
                if(DataBdry>0)
                {
                    Ctrl_Point->RecPackState=5;			            //��ʼ�������ݰ�
                }
                else
                {
                    Ctrl_Point->RecPackState=3;			            //��ʼ�������ݰ�
                }
                
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
        if(recv_cmd == NWKPro_ACKProtocolCode03)
        {
            CRC16 =NWK_Pack_Rx_S(Ctrl_Point, 0x03);
        }
        else if(recv_cmd == NWKPro_ACKProtocolCode06)
        {
            CRC16 =NWK_Pack_Rx_S(Ctrl_Point, 0x06);
        }
        else if(recv_cmd == NWKPro_ACKProtocolCode10)
        {
            CRC16 =NWK_Pack_Rx_S(Ctrl_Point, 0x10);
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
    
    UART_TO_FY1000_QueueSend_Stru   SendBuffer_1000;
    
	switch (Proto_RX)
	{
        case 0x03:
        {
            if( DevType == Valve_NWK )           
            {
                if(PackData->Pack_03_ack.lenth == 0x38)
                {
                    //if(PackData->Pack.Head.Addr == SysDevData[DevNum].Device11.Address)
                    //{
                    
                    //�����͵�16���Ʊ�ʾ�� ���������ֽ�С��ģʽ�洢��
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Input_Temp, 2);
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Input_Temp+2, 2);
                
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Output_Temp, 2);
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Output_Temp+2, 2);
                
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.EnterWater_Pressure, 2);
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.EnterWater_Pressure+2, 2);
                    
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.ReturnWater_Pressure, 2);
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.ReturnWater_Pressure+2, 2);
                    
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Room_Temp, 2);
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Room_Temp+2, 2);
                    
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Current_Valve_Open, 2);
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Current_Valve_Open+2, 2);
                    
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.SetValue_Open, 2);
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.SetValue_Open+2, 2);
                    
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Temp_Diff, 2);
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Temp_Diff+2, 2);
                    
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.ReturnTemp_Set, 2);
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.ReturnTemp_Set+2, 2);
                    
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.PressureDiff_Set, 2);
                    bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.PressureDiff_Set+2, 2);
                        
                    SysDevData[DevNum].Device11.Input_Temp              = (float)PackData->Pack_03_ack.data.Input_Temp;
                    SysDevData[DevNum].Device11.Output_Temp             = (float)PackData->Pack_03_ack.data.Output_Temp;
                    SysDevData[DevNum].Device11.EnterWater_Pressure     = (float)PackData->Pack_03_ack.data.EnterWater_Pressure;
                    SysDevData[DevNum].Device11.ReturnWater_Pressure    = (float)PackData->Pack_03_ack.data.ReturnWater_Pressure;
                    SysDevData[DevNum].Device11.Room_Temp               = (float)PackData->Pack_03_ack.data.Room_Temp;
                    SysDevData[DevNum].Device11.Current_Valve_Open      = (float)PackData->Pack_03_ack.data.Current_Valve_Open;
                    SysDevData[DevNum].Device11.SetValue_Open           = (float)PackData->Pack_03_ack.data.SetValue_Open;
                    SysDevData[DevNum].Device11.Temp_Diff               = (float)PackData->Pack_03_ack.data.Temp_Diff;
                    SysDevData[DevNum].Device11.ReturnTemp_Set          = (float)PackData->Pack_03_ack.data.ReturnTemp_Set;
                    SysDevData[DevNum].Device11.PressureDiff_Set        = (float)PackData->Pack_03_ack.data.PressureDiff_Set;
                    SysDevData[DevNum].Device11.Error                   = (UINT16)*bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Error, 2);
                    SysDevData[DevNum].Device11.Software_Version        = (UINT16)*bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Software_Version, 2);
                    SysDevData[DevNum].Device11.Run_Mode                = (UINT16)*bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Run_Mode, 2);
                    SysDevData[DevNum].Device11.Address                 = (UINT16)*bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Address, 2);
                    SysDevData[DevNum].Device11.Motor_Steering          = (UINT16)*bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Motor_Steering, 2);
                    SysDevData[DevNum].Device11.Adjust_Switch           = (UINT16)*bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Adjust_Switch, 2);
                    SysDevData[DevNum].Device11.Adjust_Tigger           = (UINT16)*bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Adjust_Tigger, 2);
                    SysDevData[DevNum].Device11.Dc_Motor_Speed          = (UINT16)*bytes_reverse( (unsigned char *)&PackData->Pack_03_ack.data.Dc_Motor_Speed, 2);
                    
                    if( SysDevData_Save(DevNum) ==HAL_OK)
                    {
                        dbg_printf(DEBUG_DEBUG,"�û����ݱ���......���: %d \r\n ",DevNum);
                    }
                    SysDevStatus[DevNum].Device11.ComSucNum +=1;
                    SysDevStatus[DevNum].Device11.ComFauNum =0;
                    
                    
                    //��������������������
                    SendBuffer_1000.SendData.Pack_0XB0_D5.CtrlFlag               = 0xAA;
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Dev_Type               = ClientCH1Ctrler.Device.Type;
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Dev_ID                 = ClientCH1Ctrler.Device.ID;
                    SendBuffer_1000.SendData.Pack_0XB0_D5.BackFlag               = COMBack_OK;

                    //������  //����С��ģʽ �ֽڵ���
                    
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Input_Temp             = (UINT16)(SysDevData[DevNum].Device11.Input_Temp*100);
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Output_Temp            = (UINT16)(SysDevData[DevNum].Device11.Output_Temp*100);
                    SendBuffer_1000.SendData.Pack_0XB0_D5.EnterWater_Pressure    = (UINT16)(SysDevData[DevNum].Device11.EnterWater_Pressure*100);
                    SendBuffer_1000.SendData.Pack_0XB0_D5.ReturnWater_Pressure   = (UINT16)(SysDevData[DevNum].Device11.ReturnWater_Pressure*100);
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Room_Temp              = (UINT16)(SysDevData[DevNum].Device11.Room_Temp*100);
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Current_Valve_Open     = (UINT16)(SysDevData[DevNum].Device11.Current_Valve_Open*100);
                    SendBuffer_1000.SendData.Pack_0XB0_D5.SetValue_Open          = (UINT16)(SysDevData[DevNum].Device11.SetValue_Open*100);
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Temp_Diff              = (UINT16)(SysDevData[DevNum].Device11.Temp_Diff*100);
                    SendBuffer_1000.SendData.Pack_0XB0_D5.ReturnTemp_Set         = (UINT16)(SysDevData[DevNum].Device11.ReturnTemp_Set*100);
                    SendBuffer_1000.SendData.Pack_0XB0_D5.PressureDiff_Set       = (UINT16)(SysDevData[DevNum].Device11.PressureDiff_Set*100);
                    
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Error                  = SysDevData[DevNum].Device11.Error;    
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Software_Version       = SysDevData[DevNum].Device11.Software_Version; 
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Run_Mode               = SysDevData[DevNum].Device11.Run_Mode; 
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Address                = SysDevData[DevNum].Device11.Address;  
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Motor_Steering         = SysDevData[DevNum].Device11.Motor_Steering;   
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Adjust_Switch          = SysDevData[DevNum].Device11.Adjust_Switch;    
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Adjust_Tigger          = SysDevData[DevNum].Device11.Adjust_Tigger;    
                    SendBuffer_1000.SendData.Pack_0XB0_D5.Dc_Motor_Speed         = SysDevData[DevNum].Device11.Dc_Motor_Speed;   
                    
                    
                    FY_1000Send_Code_QInput(&SendBuffer_1000, 0X02);
                    
                    ClientCH1Ctrler.SignleCom = RESET;
                    //}
                }
            }
        }break;
        
        case 0x06:
        {
            //if(PackData->Pack_06_ack.Head.Addr == SysDevData[DevNum].Device11.Address)
            //{
                if(PackData->Pack_06_ack.Head.CMD==0x06)
                {
                    SysDevStatus[DevNum].Device11.ComSucNum +=1;
                    SysDevStatus[DevNum].Device11.ComFauNum =0;
                    
                    SendBuffer_1000.SendData.Pack_0X1C.DevType          = ClientCH1Ctrler.Device.Type;//�豸����
                    SendBuffer_1000.SendData.Pack_0X1C.DevID            = ClientCH1Ctrler.Device.ID;//�豸ID  
                    //SendBuffer_1000.SendData.Pack_0X1C.Register_Addr    = PackData->Pack_06_ack.Register_Addr;//��ַ
                    //SendBuffer_1000.SendData.Pack_0X1C.data             = PackData->Pack_06_ack.Register_Data;//����
                    
                    SendBuffer_1000.SendData.Pack_0X1C.Register_Addr    = NWK_0X1B_Register_Addr;//��ַ
                    SendBuffer_1000.SendData.Pack_0X1C.data             = NWK_0X1B_Data;//����
                    
                    FY_1000Send_Code_QInput(&SendBuffer_1000, 0X1C);
                    
                    
                    ClientCH1Ctrler.SignleCom = RESET;
                }
            //}
            
        }break;
        
        case 0x10:
        {
            //if(PackData->Pack_10_ack.Head.Addr == SysDevData[DevNum].Device11.Address)
            //{
                if(PackData->Pack_10_ack.Head.CMD==0x10)
                {
                    SysDevStatus[DevNum].Device11.ComSucNum +=1;
                    SysDevStatus[DevNum].Device11.ComFauNum =0;
                    
                    SendBuffer_1000.SendData.Pack_0X1C.DevType          = ClientCH1Ctrler.Device.Type;//�豸����
                    SendBuffer_1000.SendData.Pack_0X1C.DevID            = ClientCH1Ctrler.Device.ID;//�豸ID
//                    SendBuffer_1000.SendData.Pack_0X1C.Register_Addr    = PackData->Pack_10_ack.Register_Addr;//��ַ
//                    SendBuffer_1000.SendData.Pack_0X1C.data             = PackData->Pack_10_ack.Register_Data;//����
                    
                    SendBuffer_1000.SendData.Pack_0X1C.Register_Addr    = NWK_0X1B_Register_Addr;//��ַ
                    SendBuffer_1000.SendData.Pack_0X1C.data             = NWK_0X1B_Data;//����
                    
                    FY_1000Send_Code_QInput(&SendBuffer_1000, 0X1C);
                    
                    ClientCH1Ctrler.SignleCom = RESET;
                }
            //}
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
void NWK_Pack_03_S(UART_RBC_Stru* PORT)
{

	NWK_Send_Uni* PackData =(NWK_Send_Uni*)(PORT->OutputPack);	//ָ��任
	//INT8U PackSize =0;
    //INT8U TYPE =0;

		
	PackData->Pack_03_cmd.Head.Addr 				= (INT8U)NWK_Q_RX_Buffer.ID;			//NWK_Q_RX_Buffer.ID;
	PackData->Pack_03_cmd.Head.CMD  				= NWKPro_ACKProtocolCode03;
	
	PackData->Pack_03_cmd.Register_Addr_H 	        = 0X00;
	PackData->Pack_03_cmd.Register_Addr_L           = 0X00;
	
	PackData->Pack_03_cmd.Register_Num_H 	        = 0X00;
	PackData->Pack_03_cmd.Register_Num_L  	        = 0X1C;
	
	PackData->Pack_03_cmd.CRC16_H 					= 0x44;
	PackData->Pack_03_cmd.CRC16_L 					= 0x03;

	PORT->OutputPackSize = 8; //sizeof(NWK_Pack_Stru);
	//PORT->OutputPackSize = PackSize;
	PORT->PackSendFlag =ENABLE;
}


/*
NWK�����Ʋɼ������͸�¥����Ԫ���ڷ�modbusЭ�� 
*/
void NWK_Pack_06_S(UART_RBC_Stru* PORT)
{

	NWK_Send_Uni* PackData =(NWK_Send_Uni*)(PORT->OutputPack);	//ָ��任
    UINT16 CRC16 = 0;
    UINT8 CRC_H = 0;
    UINT8 CRC_L = 0;

	PackData->pack_06_cmd.Head.Addr 	    = (INT8U)NWK_Q_RX_Buffer.ID;
	PackData->pack_06_cmd.Head.CMD  		= NWKPro_ACKProtocolCode06;
	
	PackData->pack_06_cmd.Register_Addr 	= NWK_Q_RX_Buffer.SendData.NWKData.pack_06_cmd.Register_Addr;
    PackData->pack_06_cmd.Register_Data     = NWK_Q_RX_Buffer.SendData.NWKData.pack_06_cmd.Register_Data;
	
    CRC16 = crc_16_modbus((const unsigned char *)PackData, 6);
    CRC_L = CRC16 >> 8;
    CRC_H = CRC16 & 0x00FF;
    
	PackData->pack_06_cmd.CRC16_H 					= CRC_H;
	PackData->pack_06_cmd.CRC16_L 					= CRC_L;
    
    
	PORT->OutputPackSize = 8; 
	//PORT->OutputPackSize = PackSize;
	PORT->PackSendFlag =ENABLE;
}


/*
NWK�����Ʋɼ������͸�¥����Ԫ���ڷ�modbusЭ�� 
*/
void NWK_Pack_10_S(UART_RBC_Stru* PORT)
{

	NWK_Send_Uni* PackData =(NWK_Send_Uni*)(PORT->OutputPack);	//ָ��任
    UINT16 CRC16 = 0;
    UINT8 CRC_H = 0;
    UINT8 CRC_L = 0;

		
	PackData->pack_10_cmd.Head.Addr 	    = (INT8U)NWK_Q_RX_Buffer.ID;			//NWK_Q_RX_Buffer.ID;
	PackData->pack_10_cmd.Head.CMD  		= NWKPro_ACKProtocolCode10;
    
    //�Ĵ����׵�ַ
	PackData->pack_10_cmd.Register_Addr 	= NWK_Q_RX_Buffer.SendData.NWKData.pack_10_cmd.Register_Addr;
    
    //�Ĵ�������
    PackData->pack_10_cmd.Register_lenth    = 0x0200;       //����
    //�Ĵ����ֽ���
    PackData->pack_10_cmd.Register_size     = 0x04;
    
    //�Ĵ������� 4���ֽ�
	PackData->pack_10_cmd.DataValue 	    = NWK_Q_RX_Buffer.SendData.NWKData.pack_10_cmd.DataValue;
	
    
    CRC16 = crc_16_modbus((const unsigned char *)PackData, 11);
    CRC_L = CRC16 >> 8;
    CRC_H = CRC16 & 0x00FF;
    
	PackData->pack_10_cmd.CRC16_H 					= CRC_H;
	PackData->pack_10_cmd.CRC16_L 					= CRC_L;
    
    
	PORT->OutputPackSize = sizeof(NWK_10_Pack_Stru); 
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
		case 0X03:
		{
			NWK_Pack_03_S(Ctrl_Point);

		}break;
        case 0x06:
        {
            NWK_Pack_06_S(Ctrl_Point);
        }break;
        
        case 0x10:
        {
            NWK_Pack_10_S(Ctrl_Point);
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



