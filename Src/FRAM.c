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
* @brief :��FRAM ��д���������ļ�
* 
* 
* 
*
* @author :��ΰ
* @date :2017/8/24 18:51
***************************************************************
*/ 
#define _FRAM_C_
#include "FRAM.h"



osMutexId framMutexHandle;

int fram_SysInit(void)
{
	osMutexDef(framMutex);
	framMutexHandle = osMutexCreate(osMutex(framMutex));
	if(framMutexHandle == NULL)
	{
		return -1;
	}
	return 0;
}

 
 
/** Configure pins as 
FRAM ��ʼ��
*/
void FRAM_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(FRAM_WP_GPIO_Port, FRAM_WP_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : FRAM_WP_Pin */
	GPIO_InitStruct.Pin = FRAM_WP_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(FRAM_WP_GPIO_Port, &GPIO_InitStruct);

	FRAM_WP_Enable;		//�洢��д����

	fram_SysInit();//��ʼ�������д������
	
}




/*
 ��FRAM��ָ����ַд������

 */
HAL_StatusTypeDef FRAM_Write(INT16U addr,INT16U Length,INT8U* DATA) //�����ӵ�ַ  ���ݳ���  ����ָ��
{
	HAL_StatusTypeDef BackValue =HAL_OK;
	FRAM_WP_Disable;
	//	INTX_DISABLE();
	//						        ���  �豸��ַ	 �洢��ַ	 �洢��ַ�ߴ�         ����ָ�� ��С	���ʱ��
		BackValue = HAL_I2C_Mem_Write(&hi2c1, FRAM_ID<<1 , addr,   FRAM_MEMADD_SIZE , DATA,   Length , FRAM_RW_Timeout);

	//   INTX_ENABLE();
	FRAM_WP_Enable;
	return BackValue;
}
/*

��FRAM��ָ����ַ��ȡ����
*/
HAL_StatusTypeDef FRAM_Read(INT16U addr,INT16U Length,INT8U* DATA)//�����ӵ�ַ  ���ݳ���  ����ָ��
{
	HAL_StatusTypeDef BackValue =HAL_OK;
	//INTX_DISABLE();
	//						        ���  �豸��ַ	 �洢��ַ	 �洢��ַ�ߴ�         ����ָ�� ��С	���ʱ��
		BackValue = HAL_I2C_Mem_Read(&hi2c1, FRAM_ID<<1 , addr,   FRAM_MEMADD_SIZE , DATA,   Length , FRAM_RW_Timeout);

	//INTX_ENABLE();
	return BackValue;

}




/*
 ��������: ReadDataFromFRAM(unsigned int FM_Addr,unsigned char *dstp,unsigned int Byte_num)
*/

static __inline INT8U ReadData_FRAM_UnSafe(INT16U FM_Addr,INT8U *dstp,INT16U Byte_num)
{
	INT8U BackValue =0;
	INT8U readcount =0;
	
	if (Byte_num>FRAM_DaBuf_Size)
	{
		BackValue =0XF0;
		return BackValue;
	}
	if((FM_Addr+Byte_num) >FRAM_Size)
	{
		BackValue =0XA0;
		return BackValue;
	}
	readcount = 0;

	while (1)
	{
		readcount++;
		if (readcount>3)
		{
			break;
		}

		if(HAL_OK ==FRAM_Read(FM_Addr,Byte_num,tempbuf))
		{
			BackValue = CRC16Check(tempbuf,Byte_num-2);
			if (BackValue==0)
			{
				memcpy(dstp,tempbuf,Byte_num);
				break;
			}
		}
		
	}
	
	return BackValue;
}


INT8U ReadData_FRAM(INT16U FM_Addr,INT8U *dstp,INT16U Byte_num)
{
	INT8U result;
	osMutexWait(framMutexHandle, osWaitForever);
	result = ReadData_FRAM_UnSafe(FM_Addr,dstp,Byte_num);
	osMutexRelease(framMutexHandle);
	return result;
}

/*
�������� :INT8U WriteDataToFRAM(unsigned int FM_Addr,unsigned char *srcp,unsigned int Byte_num)
 ��������: ��洢��д��һ������������,ע����������ֽ�ΪУ����

   ����ֵ: 0XF0��д������������������
	       0XA0�����ݵ�ַ�����洢����ַ
	       0XFF����У�����
	       0X00����
*/
static __inline INT8U WriteData_FRAM_UnSafe(INT16U FM_Addr,INT8U *srcp,INT16U Byte_num)
{
	INT8U BackValue =0;
	INT8U readcount =0;

	if (Byte_num>FRAM_DaBuf_Size)
	{
		BackValue =0XF0;
		return BackValue;
	}

	if ((FM_Addr+Byte_num)>FRAM_Size)
	{
		BackValue =0XA0;
		return BackValue;
	}
	
	while (1)
	{
		readcount++;
		if (readcount>3)
		{
			BackValue =0XFF;
			break;
		}
		CRC16Put(srcp,Byte_num-2);
		
		if(HAL_OK ==FRAM_Write(FM_Addr,Byte_num,srcp))
		{
			if(0X00 == ReadData_FRAM_UnSafe(FM_Addr,srcp,Byte_num))
			{
				BackValue =0X00;
				break;
			}
		}	
	}

	return BackValue;
}

INT8U WriteData_FRAM(INT16U FM_Addr,INT8U *srcp,INT16U Byte_num)
{
	INT8U result;
	osMutexWait(framMutexHandle, osWaitForever);
	result = WriteData_FRAM_UnSafe(FM_Addr,srcp,Byte_num);
	osMutexRelease(framMutexHandle);
	return result;
}

/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
