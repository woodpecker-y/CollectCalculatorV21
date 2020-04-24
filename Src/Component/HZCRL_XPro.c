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
* @brief :���ļ����ڻ����Ǳ��CRL-G �Լ�CRL-Hϵ�г�����������ͨ��Э��
* 
* 
* 
*
* @author :
* @date :2017/10/9 14:01
***************************************************************
*/ 
#define _HZCRL_XPRO_C_

#include "HZCRL_XPro.h"
#include "main.h"


#ifdef Meter_H_ENABLE
UART_TO_HZCRL_QueueSend_Stru HZCRL_Q_RX_Buffer;		//ͨ�ŷ��Ͷ��� ���ջ�����
UART_TO_HZCRL_QueueSend_Stru* HZCRL_Q_RX_BufferP;		//ͨ�ŷ��Ͷ��� ���ջ�����

static INT16U _htons(INT16U n);
static INT32U _htonl(INT32U n);



static INT16U _htons(INT16U n)
{
  return ((n & 0xff) << 8) | ((n & 0xff00) >> 8);
}

/* ��С��ģʽ��ת */
static INT32U _htonl(INT32U n)
{
  return ((n & 0xff) << 24) |
    ((n & 0xff00) << 8) |
    ((n & 0xff0000UL) >> 8) |
    ((n & 0xff000000UL) >> 24);
}

/* ����У��� */
INT8U CalSum(INT8U *buf, INT32U len)
{
    u8 sum = 0;
    for(int i=0; i<len; i++)
    {
        sum += buf[i];
    }
    return sum;
}


INT32U fifo_len( UART_RBC_Stru* Ctrl_Point)
{
    if(Ctrl_Point->Rx_Rear <= Ctrl_Point->Rx_Front)
    {
        return Ctrl_Point->Rx_Front - Ctrl_Point->Rx_Rear;
    }
    else
    {
        return Ctrl_Point->BufferSize - Ctrl_Point->Rx_Rear + Ctrl_Point->Rx_Front;
    }
}

/** �Ӷ��л�������ȡһ�ֽ����ݣ��ɹ������ֽ����ݣ�û���ݿɶ�����0����ʱ����-1 **/
INT32S fifo_get( UART_RBC_Stru* Ctrl_Point, INT8U *buf, INT32U len)
{
    INT32S result = 0;
    /** �����ݿɶ� **/
    if(fifo_len(Ctrl_Point) >= len)
    {
        /* ��ȡ���� */
        for(int i=0; i<len; i++)
        {
            buf[i] = Ctrl_Point->InputBuffer[Ctrl_Point->Rx_Rear];
            if(++Ctrl_Point->Rx_Rear >= Ctrl_Point->BufferSize)
            {
                Ctrl_Point->Rx_Rear=0;
            }
        }
        /* ���ó�ʱ���� */
        Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);
        result = len;
    }
    /** �����ݿɶ� **/
    else
    {
        if (*(Ctrl_Point->Ticks)- Ctrl_Point->RecPackTimeOut > Ctrl_Point->TimeOut)
        {
            /* ���ó�ʱ���� */
            Ctrl_Point->RecPackTimeOut=*(Ctrl_Point->Ticks);
            result = -1;
        }
    }
    return result;
}

 
 /*
��������:HZCRL_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
��������:Э��Ԥ�����������  �����ն��л����������ݽ��н��������������
*/
void HZCRL_Pack_RxServer_S( UART_RBC_Stru* Ctrl_Point )
{
    static recState_S reState = S_Start;
    INT8U *buf = Ctrl_Point->InputPack;
    static int offset = 0;
    int len = 0;
    static int datalen = 0;
    switch(reState)
    {
        case S_Start:
        {
            len = fifo_get(Ctrl_Point, buf + offset, 1);
            if(len > 0)
            {
                if(buf[offset] == Start_Mark)
                {
                    reState = S_Type;
                    offset++;
                }
            }
        }
        break;
        case S_Type:
        {
            len = fifo_get(Ctrl_Point, buf + offset, 1);
            if(len > 0)
            {
                reState = S_Address;
                offset++;
            }
            else if(-1 == len)
            {
                reState = S_Start;
                offset = 0;
            }
        }
        break;
        case S_Address:
        {
            len = fifo_get(Ctrl_Point, buf + offset, 7);
            if(len > 0)
            {
                reState = S_Ctr;
                offset += 7;
            }
            else if(-1 == len)
            {
                reState = S_Start;
                offset = 0;
            }
        }
        break;
        case S_Ctr:
        {
            len = fifo_get(Ctrl_Point, buf + offset, 1);
            if(len > 0)
            {
                reState = S_Len;
                offset++;
            }
            else if(-1 == len)
            {
                reState = S_Start;
                offset = 0;
            }
        }
        break;
        case S_Len:
        {
            len = fifo_get(Ctrl_Point, buf + offset, 1);
            if(len > 0)
            {
                datalen = buf[offset];
                if( datalen != 0)
                {
                    reState = S_Data;
                }
                else
                {
                    reState = S_Sum;
                }
                offset++;
            }
            else if(-1 == len)
            {
                reState = S_Start;
                offset = 0;
            }
        }
        break;
        case S_Data:
        {
            len = fifo_get(Ctrl_Point, buf + offset, datalen);
            if(len > 0)
            {
                reState = S_Sum;
                offset += datalen;
            }
            else if(-1 == len)
            {
                reState = S_Start;
                offset = 0;
            }
        }
        break;
        case S_Sum:
        {
            len = fifo_get(Ctrl_Point, buf + offset, 1);
            if(len > 0)
            {
                if(buf[offset] == CalSum(buf, offset))
                {
                    reState = S_End;
                    offset++;
                }
                else
                {
                    reState = S_Start;
                    offset = 0;
                }
            }
            else if(-1 == len)
            {
                reState = S_Start;
                offset = 0;
            }
        }
        break;
        case S_End:
        {
            len = fifo_get(Ctrl_Point, buf + offset, 1);
            if(len > 0)
            {
                if(buf[offset] == End_Mark)
                {
                    /* ����״̬����׼����һ֡���� */
                    reState = S_Start;
                    offset = 0;
                    /** һ֡���ݽ������ **/
                    HZCRL_Pack_Rx_S(Ctrl_Point, 0x01);
                }
                else
                {
                    reState = S_Start;
                    offset = 0;
                }
            }
            else if(-1 == len)
            {
                reState = S_Start;
                offset = 0;
            }
        }
        break;
        default: break;
    }
}

/* ת�����յ������ݰ��Ĵ�С��ģʽ */
void pack_Hton(HZCRL_Pack01S_ACK_Stru *ack)
{
    ack->Head.address = _htonl(ack->Head.address);
    ack->data.datamark = _htons(ack->data.datamark);
    ack->data.settleEnergy = _htonl(ack->data.settleEnergy);
    ack->data.totalEnergy = _htonl(ack->data.totalEnergy);
    ack->data.instant_Energy = _htonl(ack->data.instant_Energy);
    ack->data.Current = _htonl(ack->data.Current);
    ack->data.totalCurrent = _htonl(ack->data.totalCurrent);
    ack->data.inputTempL = _htons(ack->data.inputTempL);
    ack->data.outputTempL = _htons(ack->data.outputTempL);
    ack->data.totalWorkL = _htons(ack->data.totalWorkL);
    ack->data.Year = _htons(ack->data.Year);
}

/*
��������: HZCRL_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
��������:����������CJ188Э����շ�����
Ctrl_Point:���տ�����
Protocol: Э����
����ֵ: 0X00 Э������ 0X01 Э�鴦��������� 0XFF Э�鲻����
*/
INT8U HZCRL_Pack_Rx_S(UART_RBC_Stru* Ctrl_Point,INT8U Protocol)
{
    INT8U ErrorFlg =0;
	HZCRL_Pack01S_ACK_Stru *PackData = (HZCRL_Pack01S_ACK_Stru *)(Ctrl_Point->InputPack);
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
		case 0x01:
		{

            if(ClientCH1Ctrler.Device.Type == Meter_H)		//����������
            {
                pack_Hton(PackData);
                
				MeterID = PackData->Head.address;		//��ȡ�豸��ID
				DevNum =ClientCH1Ctrler.Device.Num; 	//��ȡ�豸�±�
				
  //               if( GetMeters_Num(MeterID,Meter_H,&DevNum) == HAL_OK)	//�豸���ҳɹ�
                if( SysDeviceList.Device[DevNum].ID ==MeterID)	//�豸IDƥ��ɹ�
                {
                    //��ǰ�����ɼ�
                    DataBuffer4 = PackData->data.totalEnergy;
                    SysDevData[DevNum].Device5.Total_Energy = BcdToHex4(&DataBuffer4);//����ֵ
                    SysDevData[DevNum].Device5.Total_Energy_Unit = PackData->data.totalEnergy_Unit;//������λ

                    //�ȹ��ʲɼ�
                    DataBuffer4 = PackData->data.instant_Energy;
                    SysDevData[DevNum].Device5.Instant_Energy = BcdToHex4(&DataBuffer4);//�ȹ���
                    SysDevData[DevNum].Device5.Instant_Energy_Unit =PackData->data.instant_Energy_Unit;//�ȹ��ʵ�λ

                    //˲ʱ�����ɼ�
                    DataBuffer4 = PackData->data.Current;
                    SysDevData[DevNum].Device5.Instant_Current = BcdToHex4(&DataBuffer4);//����
                    SysDevData[DevNum].Device5.Instant_Current_Unit = PackData->data.Current_Unit;//���ٵ�λ

                    //�ۼ������ɼ�
                    DataBuffer4 = PackData->data.totalCurrent;					
                    SysDevData[DevNum].Device5.Total_Current = BcdToHex4(&DataBuffer4);//�ۼ�����
                    SysDevData[DevNum].Device5.Total_Current_Unit = PackData->data.totalCurrent_Unit;//�ۼ�������λ

                    
                    //��ˮ�¶Ȳɼ�
                    DataBuffer2 = PackData->data.inputTempL;
                    TempL = BcdToHex2(&DataBuffer2);
                    
                    DataBuffer = PackData->data.inputTempH;
                    TempH = BcdToHex(DataBuffer);
                    SysDevData[DevNum].Device5.Input_Temp = TempH*10000+TempL;

                    //��ˮ�¶Ȳɼ�
                    DataBuffer2 = PackData->data.outputTempL;
                    TempL = BcdToHex2(&DataBuffer2);
                    
                    DataBuffer = PackData->data.outputTempH;
                    TempH = BcdToHex(DataBuffer);
                    SysDevData[DevNum].Device5.Output_Temp = TempH*10000+TempL;


                    //����ʱ��
                    DataBuffer2 = PackData->data.totalWorkL;
                    WorkTime_L = BcdToHex2(&DataBuffer2);
                    DataBuffer = PackData->data.totalWorkH;
                    WorkTime_H = BcdToHex(DataBuffer);
                    SysDevData[DevNum].Device5.Work_Time = WorkTime_H*10000UL+WorkTime_L;


                    //�Ǳ�����״̬���
                    //�Ǳ�״̬��һ���ֽ�
                    SysDevData[DevNum].Device5.STATE1 =PackData->data.state1;//�Ǳ�״̬
                    //�Ǳ�״̬�ڶ����ֽ�
                    SysDevData[DevNum].Device5.STATE2 =PackData->data.state2;//�Ǳ�״̬

                    SysDevData[DevNum].Device5.Apportion_Energy =SysDevData[DevNum].Device5.Total_Energy -SysDevData[DevNum].Device5.CycBot_Energy;  //������������

					if( SysDevData_Save(DevNum) ==HAL_OK)
					{
						dbg_printf(DEBUG_DEBUG,"�û����ݱ���......���: %d \r\n ",DevNum);
					}
					SysDevStatus[DevNum].Device5.ComSucNum +=1;
					SysDevStatus[DevNum].Device5.ComFauNum =0;
						/* ��̨ʵʱ����ת��   �Զ�����*/
				//		if( SysPara.SendMode ==DevSendMode_Auto)//�����ϱ�����Ϊ�Զ�����	�����ⲿ�������ݳ��� 						
						if(( SysPara.SendMode ==DevSendMode_Auto)&&( ClientCH1Ctrler.UaComFlg ==0))//�����ϱ�����Ϊ�Զ����� �����ⲿ������Ч
						{
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;

							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.CtrlFlag =0XAA;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_Type =Meter_H;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_ID =MeterID;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.BackFlag=COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Input_Temp =SysDevData[DevNum].Device5.Input_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Output_Temp =SysDevData[DevNum].Device5.Output_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Current =SysDevData[DevNum].Device5.Instant_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Current_Unit =SysDevData[DevNum].Device5.Instant_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy =SysDevData[DevNum].Device5.Instant_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Instant_Energy_Unit =SysDevData[DevNum].Device5.Instant_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Current =SysDevData[DevNum].Device5.Total_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Current_Unit =SysDevData[DevNum].Device5.Total_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Code =SysDevData[DevNum].Device5.Total_Code =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Code_Unit =SysDevData[DevNum].Device5.Total_Code_Unit =MW_h;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Energy =SysDevData[DevNum].Device5.Total_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Total_Energy_Unit =SysDevData[DevNum].Device5.Total_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Work_Time =SysDevData[DevNum].Device5.Work_Time;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.STATE1 =SysDevData[DevNum].Device5.STATE1;
							FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.STATE2 =SysDevData[DevNum].Device5.STATE2;
							

							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0XB0)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸�Զ���������ת��......���: %d SN:%08X\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0XB0_D1.Dev_ID);
							}
						}
						/* ��̨ʵʱ����ת�� �Զ�����END*/


						/* ��̨ʵʱ����ת��   Զ�̳���*/
						if( ClientCH1Ctrler.UaComFlg !=0)//�����ϱ�����Ϊ�Զ�����	�����ⲿ�������ݳ��� 
						{
							UART_TO_FY1000_QueueSend_Stru FY1000_Q_TX_Buffer;


							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.CtrlFlag =0XAA;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Dev_Type =Meter_H;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Dev_ID =MeterID;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.BackFlag=COMBack_OK;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Input_Temp =SysDevData[DevNum].Device5.Input_Temp;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Output_Temp =SysDevData[DevNum].Device5.Output_Temp;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Instant_Current =SysDevData[DevNum].Device5.Instant_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Instant_Current_Unit =SysDevData[DevNum].Device5.Instant_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Instant_Energy =SysDevData[DevNum].Device5.Instant_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Instant_Energy_Unit =SysDevData[DevNum].Device5.Instant_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Total_Current =SysDevData[DevNum].Device5.Total_Current;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Total_Current_Unit =SysDevData[DevNum].Device5.Total_Current_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Total_Code =SysDevData[DevNum].Device5.Total_Code =0;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Total_Code_Unit =SysDevData[DevNum].Device5.Total_Code_Unit =MW_h;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Total_Energy =SysDevData[DevNum].Device5.Total_Energy;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Total_Energy_Unit =SysDevData[DevNum].Device5.Total_Energy_Unit;
							
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Work_Time =SysDevData[DevNum].Device5.Work_Time;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.STATE1 =SysDevData[DevNum].Device5.STATE1;
							FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.STATE2 =SysDevData[DevNum].Device5.STATE2;

							if(FY_1000Send_Code_QInput(&FY1000_Q_TX_Buffer,0X02)==pdTRUE)
							{
								dbg_printf(DEBUG_DEBUG,"�豸Զ�̳�������ת��......���: %d SN:%08X\r\n ",DevNum,FY1000_Q_TX_Buffer.SendData.Pack_0X02_D1.Dev_ID);
							}
						}
						/* ��̨ʵʱ����ת�� Զ�̳���END*/


     
                    ClientCH1Ctrler.SignleCom =RESET;

                }
            }
		}
		break;
		
		default :
		{
		   ErrorFlg =0XFF; 
        }
        break;

	}
	return ErrorFlg;
}


/*
HZCRL_���������

*/
INT8U HZCRL_Pack_TxServer_S(UART_RBC_Stru* Ctrl_Point)
{

	BaseType_t Err;

	/* ���߿���״̬��� */
 //   if(*(Ctrl_Point->SendBusy) != HAL_OK)
//    {
   //     return HAL_ERROR;
//    }

    /* ���ն������� */
    Err =xQueueReceive(UART_TO_HZCRL_Msg,&HZCRL_Q_RX_BufferP,5);
    if( Err != pdTRUE)
    {
        return HAL_ERROR;
    }

    /* ���ƴ��������ݲ���� */
    HZCRL_Q_RX_Buffer = *HZCRL_Q_RX_BufferP;
    Ctrl_Point->PackCreatFlag =HZCRL_Q_RX_Buffer.PackCreatFlag;
    Ctrl_Point->PackINPort =HZCRL_Q_RX_Buffer.PackINPort;
    
    /* ����������־��� ���߿���״̬��� */
    if(Ctrl_Point->PackCreatFlag != ENABLE)	
    {
        return HAL_ERROR;
    }

    Ctrl_Point->PackCreatFlag = DISABLE;
    
    /* ���Э����ʶ�� */
    switch(Ctrl_Point->PackINPort)		
    {
        case 0X01:
        {
            HZCRL_Pack_0X01_S(Ctrl_Point);

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
	����/����˳���ʵʱ��������
*/
void HZCRL_Pack_0X01_S(UART_RBC_Stru* PORT)
{
    HZCRL_Send_Uni* packData =(HZCRL_Send_Uni *)(PORT->OutputPack);

    /* ƴ�ӳ���Э������� */
    packData->Pack0X01S.Head.start = Start_Mark;
    packData->Pack0X01S.Head.type = 0x20;


    /* �����Ǳ��ַ��ת����С�� */
	packData->Pack0X01S.Head.addPlace[0] = 0xFF;
	packData->Pack0X01S.Head.addPlace[1] = 0xFF;
	packData->Pack0X01S.Head.addPlace[2] = 0xFF;
    packData->Pack0X01S.Head.address = HZCRL_Q_RX_Buffer.ID;				//�����Ǳ���
    packData->Pack0X01S.Head.address = _htonl(packData->Pack0X01S.Head.address);

    packData->Pack0X01S.Head.ctr = 0x01;
    packData->Pack0X01S.Head.len = sizeof(HZCRL_Pack01S_Stru) - sizeof(HZCRL_Pack_Head_t) -2;
    packData->Pack0X01S.datamark = 0x1f90;
    packData->Pack0X01S.serialNum = 0x0b;
    packData->Pack0X01S.sum = CalSum((INT8U *)packData, sizeof(HZCRL_Pack01S_Stru) -2);
    packData->Pack0X01S.end = End_Mark;


    PORT->OutputPackSize = sizeof(HZCRL_Pack01S_Stru);
    PORT->PackSendFlag = ENABLE;
}
#endif

/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
