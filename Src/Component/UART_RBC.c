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
* @brief :  1.�����ģ�����ڵ���ͨ�ŵĻ�����ƴ�������Ӳ�������ͨ��Э����м����㣨���崦��
	          2.����ʵ�ֵ��ٻ����ڴ濽�����ݵ�˫�����Э�鴦��
		  3.�Ƽ�����Ӳ���ʹ���Э��Ĺ�ϵ����������Ա(��ϵ)��
		  4.Ӧ�ò� ��Ӳ������ ��Ҫ�ҽ� Ӳ�����ͷ�����
		  5.Ӳ���㵽Ӧ�ò���Ҫ���б�дЭ�鴦����
		  

		  ���л��ƣ�	���裨���У�ͨ���жϣ�DMA,�ڴ濽���ķ�ʽ���������뻺����
		  			Ӧ�ò�ͨ���жϻ�������־λ�ж��Ƿ���������Ҫ����
					Ӧ�ò� Э���������������Ժ�ͨ���м������н����Э�飩���з���
					ʵ������ӿڵ���ͬӦ�ýӿڵ������л�

					��Ӳ�������￴���������ݲ��ϵĵ����뵽���ȶ���õĻ�����
					��Ӧ�ò����⿴�������Ų�ͬͨ��Э������ݽ��뻺�建�����У�ֻ��Ҫʹ�ò�ͬ��Э����д�����
* 
* 
* 
*
* @author :��ΰ
* @date :2016/11/8 22:30
***************************************************************
*/ 
#define _UART_RBC_C_
#include "UART_RBC.h"


/*

UART_RBC ������ܳ�ʼ��

*/
void UART_RBC_ControlerInit(void)
{

	INT16U Loop =0;
	for(Loop =0;Loop<Max_UART_RBC_NUM;Loop++)
	{
	    UART_RBC_Manager[Loop].Enable = DISABLE;

	    UART_RBC_Manager[Loop].Rx_Front = 0;
	    UART_RBC_Manager[Loop].Rx_Rear = 0;
//	    UART_RBC_Manager[Loop].Rx_Full = 0;
//	    UART_RBC_Manager[Loop].Rx_Null = 1;

	    UART_RBC_Manager[Loop].RecPackTimeOut = 0;
	    UART_RBC_Manager[Loop].InputPack = 0;
//	    UART_RBC_Manager[Loop].InputPackSize = 0;

	    UART_RBC_Manager[Loop].RxPack_Mutex = 1;

	    UART_RBC_Manager[Loop].RecPackState = 0;
	    UART_RBC_Manager[Loop].RecPackPoint = 0;
	}

}
 

 
 /*
 ���뻺�����������������
 @ UART_RBCMem: ������ָ��
 @ InputBuffer:���뻺�����׵�ַ
 @ BufferSize :���뻺������С
 @ InputPack: ��������׵�ַ
 @ OutputPack: ��������׵�ַ
 @ PackSize: ������д�С
 @ TICK:	ʱ�� �Ƽ�ʹ��ϵͳʱ��
 @ TimeOut:ʱ�����ֵ
 
 */
 
INT8U UART_RBC_Creat( UART_RBC_Stru** UART_RBCMem,INT8U* InputBuffer,INT16U BufferSize,INT8U* InputPack,INT8U* OutputPack,INT16U PackSize,INT32U* TICK,INT8U TimeOut)
{
    if(UART_RBC_Record >= Max_UART_RBC_NUM)
    {
            return 0X0F;
    }
    UART_RBC_Manager[UART_RBC_Record].InputBuffer = InputBuffer;
    UART_RBC_Manager[UART_RBC_Record].BufferSize =BufferSize;
    UART_RBC_Manager[UART_RBC_Record].Rx_Front = 0;
    UART_RBC_Manager[UART_RBC_Record].Rx_Rear = 0;
//    UART_RBC_Manager[UART_RBC_Record].Rx_Full =0;
//    UART_RBC_Manager[UART_RBC_Record].Rx_Null =1;
    UART_RBC_Manager[UART_RBC_Record].TimeOut=TimeOut;
    UART_RBC_Manager[UART_RBC_Record].RecPackTimeOut=*TICK;
	UART_RBC_Manager[UART_RBC_Record].Ticks=TICK;

    UART_RBC_Manager[UART_RBC_Record].InputPack=InputPack;
	UART_RBC_Manager[UART_RBC_Record].OutputPack=OutputPack;
    UART_RBC_Manager[UART_RBC_Record].PackSize=PackSize;
//    UART_RBC_Manager[UART_RBC_Record].InputPackSize =0;
    UART_RBC_Manager[UART_RBC_Record].RxPack_Mutex =1;
    UART_RBC_Manager[UART_RBC_Record].RecPackState =0;
    UART_RBC_Manager[UART_RBC_Record].RecPackPoint =0;	 
    UART_RBC_Manager[UART_RBC_Record].Enable = DISABLE;

    UART_RBC_Record ++;
    *UART_RBCMem =(UART_RBC_Stru*)&(UART_RBC_Manager[UART_RBC_Record - 1]);
    return 0X00;
    }


/*
	���ģ�������ʼ��
	
	member �������Ա
	Output��APP�����Ӳ���������ӿ�
	BUSY:
�������æ��־ָ��
	
	����ֵ����
	

*/
void UART_RBC_OutputHandle_Init(UART_RBC_Stru* member, void(*Output)(UART_RBC_Stru *),HAL_StatusTypeDef *BUSY)
{
	member->API_TxFunCal = Output;	//���������ַ����
	member->SendBusy = BUSY;		//���������ַ����
	


}

/*
	���ģ�������ʼ��
	
	member �������Ա
	IN�����赽Ӧ�ò㺯���ӿ�
	����ֵ����
	

*/
void UART_RBC_InputHandle_Init(UART_RBC_Stru* member, void (*IN)(UART_RBC_Stru *))
{
	member->API_RxFunCal = IN;	//���������ַ����


}


/*
	���ģ��ʹ�ܷ�����
	Falg:ʹ�ܱ�־ Enable/DISABLE
	����ֵ����

*/
void UART_RBC_Enable(UART_RBC_Stru* member,FunctionalState Falg)
{
    member->Enable = Falg;
  
}







/*
�������������������:
@ InputNum �������ݴ�С
@ InputBuffer_P ���������׵�ַ
*/
void UART_RBC_BufferInput(UART_RBC_Stru* member,INT16U InputNum,INT8U* InputBuffer_P)
{
	INT16U loop =0;
	for(loop =0;loop<InputNum;loop++)
	{
		member->InputBuffer[member->Rx_Front] =*(InputBuffer_P+loop);
		member->Rx_Front +=1;
		if( member->Rx_Front >=member->BufferSize)
		{
			member->Rx_Front =0;
		}
/*		if( member->Rx_Front ==member->Rx_Rear)
		{
			member->Rx_Full =1;
		}
		else
		{
			member->Rx_Full =0;
		}
*/
	}
}





/*
	���ģ���Է�����
	�Զ����Ӧ�ò㵽Ӳ�������ݷ��Ϳ���
*/
void UART_RBC_TXServer(void)
{
	INT16U Loop =0;
	for ( Loop = 0; Loop < UART_RBC_Record; Loop++)
	{
		if ( UART_RBC_Manager[Loop].Enable == ENABLE)
		{
			(*UART_RBC_Manager[Loop].API_TxFunCal)(UART_RBC_Manager+Loop);
		}		
	}
}
/* end   */



/*
	���ģ���Է�����
	��ɸ�����Աģ������ݻ���ͽ���

*/
void UART_RBC_RXServer(void)
{
	INT16U Loop =0;
	for ( Loop = 0; Loop < UART_RBC_Record; Loop++)
	{
		if ( UART_RBC_Manager[Loop].Enable == ENABLE)
		{
			(*UART_RBC_Manager[Loop].API_RxFunCal)(UART_RBC_Manager+Loop);
		}		
	}
}




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
