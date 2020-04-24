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
* @brief :SPI Flash�����ļ�
* 
* 
* 
*
* @author :��ΰ
* @date :2017-01-13 16:05
***************************************************************
*/ 
#define _W25QXX_C_
#include "W25QXX.h"
 





osMutexId spiFlashMutexHandle;

static int spiFlash_SysInit(void)
{
	osMutexDef(spiFlashMutex);
	spiFlashMutexHandle = osMutexCreate(osMutex(spiFlashMutex));
	if(spiFlashMutexHandle == NULL)
	{
		return -1;
	}
	return 0;
}


/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void W25QXX_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */

	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	//WP
	HAL_GPIO_WritePin(Flash_WP_PORT, Flash_WP_PIN, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = Flash_WP_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(Flash_WP_PORT, &GPIO_InitStruct);


	//HOLD
	HAL_GPIO_WritePin(Flash_HOLD_PORT, Flash_HOLD_PIN, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = Flash_WP_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(Flash_HOLD_PORT, &GPIO_InitStruct);
	
	//CS
	HAL_GPIO_WritePin(Flash_CS_PORT, Flash_CS_PIN, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = Flash_WP_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(Flash_CS_PORT, &GPIO_InitStruct);




}








//4KbytesΪһ��Sector
//16������Ϊ1��Block
//W25Q256
//����Ϊ32M�ֽ�,����512��Block,8192��Sector 
													 
//��ʼ��SPI FLASH��IO��
void W25QXX_Init(void)
{ 
    INT8U temp;
    GPIO_InitTypeDef GPIO_Initure;
    
	GPIO_Initure =GPIO_Initure;
	W25QXX_GPIO_Init();
    
	Flash_CS_H;			            //SPI FLASH��ѡ��
	MX_SPI1_Init();		   			    //��ʼ��SPI
	SPI1_SetSpeed(SPI_BAUDRATEPRESCALER_2); //����Ϊ45Mʱ��,����ģʽ
	W25QXX_TYPE=W25QXX_ReadID();	        //��ȡFLASH ID.
    if(W25QXX_TYPE==W25Q64)                //SPI FLASHΪW25Q256
    {
        temp=W25QXX_ReadSR(3);              //��ȡ״̬�Ĵ���3���жϵ�ַģʽ
        if((temp&0X01)==0)			        //�������4�ֽڵ�ַģʽ,�����4�ֽڵ�ַģʽ
		{
			Flash_CS_L; 			        	//ѡ��
			SPI1_ReadWriteByte(W25X_Enable4ByteAddr);//���ͽ���4�ֽڵ�ַģʽָ��   
			Flash_CS_H;       		        	//ȡ��Ƭѡ   
		}
    }
	spiFlash_SysInit();//��ʼ��spi Flash��д������
}  




//��ȡоƬID
//����ֵ����:				   
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80  
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16    
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32  
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64 
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128 	  
//0XEF18,��ʾоƬ�ͺ�ΪW25Q256
u16 W25QXX_ReadID(void)
{
	u16 Temp = 0;	  
	Flash_CS_L;				    
	SPI1_ReadWriteByte(0x90);//���Ͷ�ȡID����	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	 			   
	Temp|=SPI1_ReadWriteByte(0xFF)<<8;  
	Temp|=SPI1_ReadWriteByte(0xFF);	 
	Flash_CS_H;				    
	return Temp;
}   		    





//��ȡW25QXX��״̬�Ĵ�����W25QXXһ����3��״̬�Ĵ���
//״̬�Ĵ���1��
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
//״̬�Ĵ���2��
//BIT7  6   5   4   3   2   1   0
//SUS   CMP LB3 LB2 LB1 (R) QE  SRP1
//״̬�Ĵ���3��
//BIT7      6    5    4   3   2   1   0
//HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
//regno:״̬�Ĵ����ţ���:1~3
//����ֵ:״̬�Ĵ���ֵ
INT8U W25QXX_ReadSR(INT8U regno)   
{  
	INT8U byte=0,command=0; 
    switch(regno)
    {
        case 1:
            command=W25X_ReadStatusReg1;    //��״̬�Ĵ���1ָ��
            break;
        case 2:
            command=W25X_ReadStatusReg2;    //��״̬�Ĵ���2ָ��
            break;
        case 3:
            command=W25X_ReadStatusReg3;    //��״̬�Ĵ���3ָ��
            break;
        default:
            command=W25X_ReadStatusReg1;    
            break;
    }    
	Flash_CS_L;                            //ʹ������   
	SPI1_ReadWriteByte(command);            //���Ͷ�ȡ״̬�Ĵ�������    
	byte=SPI1_ReadWriteByte(0Xff);          //��ȡһ���ֽ�  
	Flash_CS_H;                            //ȡ��Ƭѡ     
	return byte;   
} 


//дW25QXX״̬�Ĵ���
void W25QXX_WriteSR(INT8U regno,INT8U sr)   
{   
    INT8U command=0;
    switch(regno)
    {
        case 1:
            command=W25X_WriteStatusReg1;    //д״̬�Ĵ���1ָ��
            break;
        case 2:
            command=W25X_WriteStatusReg2;    //д״̬�Ĵ���2ָ��
            break;
        case 3:
            command=W25X_WriteStatusReg3;    //д״̬�Ĵ���3ָ��
            break;
        default:
            command=W25X_WriteStatusReg1;    
            break;
    }   
	Flash_CS_L;                            //ʹ������   
	SPI1_ReadWriteByte(command);           //����дȡ״̬�Ĵ�������    
	SPI1_ReadWriteByte(sr);                 //д��һ���ֽ�  
	Flash_CS_H;                            //ȡ��Ƭѡ     	      
}   


//W25QXXдʹ��	
//��WEL��λ   
void W25QXX_Write_Enable(void)   
{
	Flash_CS_L;                            //ʹ������   
    SPI1_ReadWriteByte(W25X_WriteEnable);   //����дʹ��  
	Flash_CS_H;                            //ȡ��Ƭѡ     	      
} 

//W25QXXд��ֹ	
//��WEL����  
void W25QXX_Write_Disable(void)   
{  
	Flash_CS_L;                            //ʹ������   
    SPI1_ReadWriteByte(W25X_WriteDisable);  //����д��ָֹ��    
	Flash_CS_H;                            //ȡ��Ƭѡ     	      
} 

//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
void W25QXX_Write_Page(INT8U* pBuffer,uint32_t WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
    W25QXX_Write_Enable();                  //SET WEL 
	Flash_CS_L;                            //ʹ������   
    SPI1_ReadWriteByte(W25X_PageProgram);   //����дҳ����   
    if(W25QXX_TYPE==W25Q256)                //�����W25Q256�Ļ���ַΪ4�ֽڵģ�Ҫ�������8λ
    {
        SPI1_ReadWriteByte((INT8U)((WriteAddr)>>24)); 
    }
    SPI1_ReadWriteByte((INT8U)((WriteAddr)>>16)); //����24bit��ַ    
    SPI1_ReadWriteByte((INT8U)((WriteAddr)>>8));   
    SPI1_ReadWriteByte((INT8U)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)SPI1_ReadWriteByte(pBuffer[i]);//ѭ��д��  
	Flash_CS_H;                            		//ȡ��Ƭѡ     	      
	W25QXX_Wait_Busy();					   		//�ȴ�д�����
} 



/*******************************************************************************
* Function Name  : SPI_FLASH_PageWrite
* Description    : Writes more than one byte to the FLASH with a single WRITE
*                  cycle(Page WRITE sequence). The number of byte can't exceed
*                  the FLASH page size.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to. ʵ�������ַ
*                  - NumByteToWrite : number of bytes to write to the FLASH,
*                    must be equal or less than "SPI_FLASH_PageSize" value.
* Output         : None
* Return         : ���ݳ��޷��� �������ݵ�����  ��������0X00
*******************************************************************************/
INT16U W25QXX_PageWrite(INT8U* pBuffer, INT32U WriteAddr, INT16U NumByteToWrite)
{
	INT16U BackValue =0X0000;
	//�����ӱ߽��������� ������ҳд
  	INT16U Pageborder =SPI_FLASH_PageSize-(WriteAddr%SPI_FLASH_PageSize);	//���㵱ǰҳ�¸õ�ַ����д����ֽ�����
	W25QXX_Write_Enable();												/* Enable the write access to the FLASH */
	Flash_CS_L;															/* Select the FLASH: Chip Select low */
	
	SPI1_ReadWriteByte(W25X_PageProgram); 								/* Send "Write to Memory " instruction */
    if(W25QXX_TYPE==W25Q256)                							//�����W25Q256�Ļ���ַΪ4�ֽڵģ�Ҫ�������8λ
    {
        SPI1_ReadWriteByte((INT8U)((WriteAddr)>>24)); 
    }	
	SPI1_ReadWriteByte((WriteAddr & 0xFF0000) >> 16);/* Send WriteAddr high nibble address byte to write to */
	SPI1_ReadWriteByte((WriteAddr & 0xFF00) >> 8); /* Send WriteAddr medium nibble address byte to write to */
	SPI1_ReadWriteByte(WriteAddr & 0xFF); /* Send WriteAddr low nibble address byte to write to */



	//�����ӱ߽��������� ������ҳд
	if(NumByteToWrite > Pageborder) 
	{
		BackValue =NumByteToWrite -Pageborder;
		NumByteToWrite = Pageborder;
	}

	/* while there is data to be written on the FLASH */
	while (NumByteToWrite--)
	{
	/* Send the current byte */
		SPI1_ReadWriteByte(*pBuffer);
	/* Point on the next byte to be written */
	pBuffer++;
	}
	/* Deselect the FLASH: Chip Select high */
	Flash_CS_H;
	/* Wait the end of Flash writing */
	W25QXX_Wait_Busy();
	return BackValue;
}




/*******************************************************************************
* Function Name  : SPI_FLASH_SectorWrite
* Description    : Writes block of data to the FLASH. In this function, the
*                  number of WRITE cycles are reduced, using Page WRITE sequence.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void W25QXX_SectorWrite(INT8U * pBuffer, INT32U WriteAddr, INT16U NumByteToWrite)
{
	INT8U NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
	Addr = WriteAddr % SPI_FLASH_PageSize;			//ҳ�������־
	count = SPI_FLASH_PageSize - Addr;				//��ҳ��ҳβ�߽��ֽ�����
	
	NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;//��ҳ������
	NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;//��ҳ�ֽڼ�����

	
	if (Addr == 0) /* WriteAddr is SPI_FLASH_PageSize aligned  */
	{
		if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
	  	{
	  		W25QXX_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
	  	}
	  	else /* NumByteToWrite > SPI_FLASH_PageSize */
	  	{
	  		while (NumOfPage--)//����д����ҳ
			{
				W25QXX_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
				WriteAddr +=  SPI_FLASH_PageSize;
				pBuffer += SPI_FLASH_PageSize;
			}
			if ( NumOfSingle !=0)//д���ҳ
			{
				W25QXX_PageWrite(pBuffer, WriteAddr, NumOfSingle);
			}
			
		}
	}
	/* WriteAddr is not SPI_FLASH_PageSize aligned  */
	else //��ʼ�ֽ�û��ҳ����
	{
		if (NumOfPage == 0) //û����������ҳ
		{
			if ( NumByteToWrite<=count)//�ֽ�����û�п�ҳ
			{
				W25QXX_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
			}
			else
			{
				temp = NumOfSingle - count;
				W25QXX_PageWrite(pBuffer, WriteAddr, count);
				WriteAddr +=  count;
				pBuffer += count;
				W25QXX_PageWrite(pBuffer, WriteAddr, temp);
			}
		}
		
    	else /* NumByteToWrite > SPI_FLASH_PageSize */
    	{
			NumByteToWrite -= count;
			NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
			NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;
			W25QXX_PageWrite(pBuffer, WriteAddr, count);
			WriteAddr +=  count;
			pBuffer += count;
			while (NumOfPage--)
			{
				W25QXX_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
				WriteAddr +=  SPI_FLASH_PageSize;
				pBuffer += SPI_FLASH_PageSize;
			}
			if (NumOfSingle != 0)
			{
				W25QXX_PageWrite(pBuffer, WriteAddr, NumOfSingle);
			}
    	}
  	}
}








//��������оƬ		  
//�ȴ�ʱ�䳬��...
void W25QXX_Erase_Chip(void)   
{                                   
    W25QXX_Write_Enable();					//SET WEL 
    W25QXX_Wait_Busy();   
	Flash_CS_L;                            //ʹ������   
    SPI1_ReadWriteByte(W25X_ChipErase);			//����Ƭ��������  
	Flash_CS_H;							//ȡ��Ƭѡ     	      
	W25QXX_Wait_Busy();					//�ȴ�оƬ��������
}   


/*******************************************************************************
* Function Name  : SPI_FLASH_SectorErase
* Description    : Erases the specified FLASH sector.
* Input              : SectorAddr: address of the sector to erase.
		�õ�ַΪ�洢���������ַ��ͨ����ָ��洢���������д�����ַ�������������Բ���
* Output           : None
* Return            :0X00  ����   0XA0 ��ַ�����洢����Χ
*******************************************************************************/
HAL_StatusTypeDef W25QXX_Erase_Sector(INT32U Dst_Addr)   
{  
  	HAL_StatusTypeDef BackVal =HAL_OK;
 	if (Dst_Addr >=SPI_FLASH_Size)
	{
		BackVal =HAL_ERROR;
		return BackVal;
	}
    W25QXX_Write_Enable();                	//SET WEL 	 
    W25QXX_Wait_Busy();   
	Flash_CS_L;                            //ʹ������   
    SPI1_ReadWriteByte(W25X_SectorErase);   		//������������ָ�� 
    if(W25QXX_TYPE==W25Q256)            	//�����W25Q256�Ļ���ַΪ4�ֽڵģ�Ҫ�������8λ
    {
        SPI1_ReadWriteByte((INT8U)((Dst_Addr)>>24)); 
    }
    SPI1_ReadWriteByte((INT8U)((Dst_Addr)>>16));	//����24bit��ַ    
    SPI1_ReadWriteByte((INT8U)((Dst_Addr)>>8));   
    SPI1_ReadWriteByte((INT8U)Dst_Addr);  
	Flash_CS_H;							//ȡ��Ƭѡ     	      
    W25QXX_Wait_Busy();   				    //�ȴ��������
    
	BackVal =HAL_OK;
	return BackVal;
    
}  


 
//�ȴ�����
void W25QXX_Wait_Busy(void)   
{   

	while((W25QXX_ReadSR(1)&0x01)==0x01)			// �ȴ�BUSYλ���
	{
		osDelay(1);
		SP706_Toggle;
	}
} 



//�������ģʽ
void W25QXX_PowerDown(void)   
{ 
	Flash_CS_L;									//ʹ������   
    SPI1_ReadWriteByte(W25X_PowerDown);				//���͵�������  
	Flash_CS_H;                            	//ȡ��Ƭѡ     	      

}   
//����
void W25QXX_WAKEUP(void)   
{  
	Flash_CS_L;									//ʹ������   
    SPI1_ReadWriteByte(W25X_ReleasePowerDown);		//send W25X_PowerDown command 0xAB    
	Flash_CS_H;                            	//ȡ��Ƭѡ     	      

}   









/*

 ��������:��Flash�ƶ���ַд���������ݡ���д��֮ǰ������ڵ��������в���

INT8U * pBuffer:����ָ��
uint32_t WriteAddr:�洢���׵�ַ
u16 Lenth:���ݳ���
//0X00  ����   0XA0 ��ַ�����洢����Χ
*/
HAL_StatusTypeDef W25QXX_WriteBuffer(INT8U * pBuffer, INT32U WriteAddr, INT16U Lenth)/* �����ͻ�����������д��flash�� */
{
	HAL_StatusTypeDef BackVal =HAL_OK;
	INT16U Sector_Start =WriteAddr /SPI_FLASH_SectorSize;				//������д������ʼ����
	INT16U Sector_End =(WriteAddr+Lenth-1) /SPI_FLASH_SectorSize;		//������д������ֹ����
	INT16U BU =0;		//����������¼��

	if ((WriteAddr+Lenth)>SPI_FLASH_Size)
	{
		BackVal =HAL_ERROR;
		return BackVal;
	}
	
	for (BU =Sector_Start;BU<=Sector_End;BU++)
	{
	 	BackVal =W25QXX_Erase_Sector(BU*SPI_FLASH_SectorSize);//��������
	 	if( BackVal !=HAL_OK )
	 	{
			return BackVal;
	 	}
	}
	W25QXX_SectorWrite (pBuffer,WriteAddr,Lenth);	//������д������
	return BackVal;

}





//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
HAL_StatusTypeDef W25QXX_ReadBuffer(INT8U* pBuffer,INT32U ReadAddr,INT16U NumByteToRead)   
{ 
 	u16 i;   										    
	Flash_CS_L;                            	//ʹ������   
    SPI1_ReadWriteByte(W25X_ReadData);			//���Ͷ�ȡ����  
    if(W25QXX_TYPE==W25Q256)               	//�����W25Q256�Ļ���ַΪ4�ֽڵģ�Ҫ�������8λ
    {
        SPI1_ReadWriteByte((INT8U)((ReadAddr)>>24));    
    }
    SPI1_ReadWriteByte((INT8U)((ReadAddr)>>16));   //����24bit��ַ    
    SPI1_ReadWriteByte((INT8U)((ReadAddr)>>8));   
    SPI1_ReadWriteByte((INT8U)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
        pBuffer[i]=SPI1_ReadWriteByte(0XFF);    //ѭ������  
    }
	Flash_CS_H;                          //ȡ��Ƭѡ   

	return HAL_OK;
}  






/*
 ��������: ReadData_SPIFash(unsigned int FM_Addr,unsigned char *dstp,unsigned int Byte_num)
*/

static __inline HAL_StatusTypeDef ReadData_SPIFlash_UnSafe(INT32U FM_Addr,INT8U *dstp,INT16U Byte_num)
{
	HAL_StatusTypeDef BackValue =HAL_OK;
	INT8U readcount =0;
	INT8U* SPIReadBuf = pvPortMalloc( SPIFlash_DaBuf_Size);
		
	
	if(SPIReadBuf == NULL)
	{
		BackValue =HAL_ERROR;
		dbg_printf(DEBUG_ERR,"�ڴ治��");
		return BackValue;
	}

	if (Byte_num>SPIFlash_DaBuf_Size)
	{
		BackValue =HAL_ERROR;
		
		vPortFree( SPIReadBuf);
		return BackValue;
	}
	if((FM_Addr+Byte_num) >SPIFlash_Size)
	{
		BackValue =HAL_ERROR;

		vPortFree( SPIReadBuf);
		return BackValue;
	}
	readcount = 0;

	while (1)
	{
		readcount++;
		if (readcount>3)
		{
			BackValue=HAL_ERROR;
			break;
		}

		if(HAL_OK ==W25QXX_ReadBuffer(SPIReadBuf,FM_Addr,Byte_num))
		{
			
			if(CRC16Check(SPIReadBuf,Byte_num-2)==0)
			{
				BackValue=HAL_OK;
				memcpy(dstp,SPIReadBuf,Byte_num);
				break;
			}
		}
	}

	
	vPortFree( SPIReadBuf);
	return BackValue;
}

/* �̰߳�ȫ�汾 */
HAL_StatusTypeDef ReadData_SPIFlash(INT32U FM_Addr,INT8U *dstp,INT16U Byte_num)
{
	HAL_StatusTypeDef result;
	osMutexWait(spiFlashMutexHandle, osWaitForever);
	result = ReadData_SPIFlash_UnSafe(FM_Addr,dstp,Byte_num);
	osMutexRelease(spiFlashMutexHandle);
	return result;
}


/*
�������� :INT8U WriteData_SPIFLASH(unsigned int FM_Addr,unsigned char *srcp,unsigned int Byte_num)
 ��������: ��洢��д��һ������������,ע�����4���ֽ�ΪУ����

   ����ֵ: 0XF0��д������������������
	       0XA0�����ݵ�ַ�����洢����ַ
	       0XFF����У�����
	       0X00����
*/
static __inline HAL_StatusTypeDef WriteData_SPIFlash_UnSafe(INT32U FM_Addr,INT8U *srcp,INT16U Byte_num)
{
	HAL_StatusTypeDef BackValue =HAL_OK;
	INT8U readcount =0;
	if (Byte_num>SPIFlash_DaBuf_Size)
	{
		BackValue =HAL_ERROR;
		return BackValue;
	}

	if ((FM_Addr+Byte_num)>SPIFlash_Size)
	{
		BackValue =HAL_ERROR;
		return BackValue;
	}
	
	while (1)
	{
		readcount++;
		if (readcount>3)
		{
			BackValue =HAL_ERROR;
			break;
		}
		CRC16Put(srcp,Byte_num-2);
		
		if(HAL_OK ==W25QXX_WriteBuffer(srcp,FM_Addr,Byte_num))
		{
			if(HAL_OK == W25QXX_ReadBuffer(srcp,FM_Addr,Byte_num))
			{
				BackValue =HAL_OK;
				break;
			}
		}	
	}
	return BackValue;
}

/* �̰߳�ȫ�汾 */
HAL_StatusTypeDef WriteData_SPIFlash(INT32U FM_Addr,INT8U *srcp,INT16U Byte_num)
{
	HAL_StatusTypeDef result;
	osMutexWait(spiFlashMutexHandle, osWaitForever);
	result = WriteData_SPIFlash_UnSafe(FM_Addr,srcp,Byte_num);
	osMutexRelease(spiFlashMutexHandle);
	return result;
}


/* �̰߳�ȫ�汾��ֻ������д�뺯�� */
HAL_StatusTypeDef spiFlashErase(INT32U address, INT32U size)
{
	HAL_StatusTypeDef result = HAL_OK;
	INT16U Sector_Start = address / SPI_FLASH_SectorSize;				//������д������ʼ����
	INT16U Sector_End = (address + size-1) / SPI_FLASH_SectorSize;	//������д������ֹ����


	
	INT16U BU = 0;		//����������¼��

	if ((address + size) > SPI_FLASH_Size)
	{
		return HAL_ERROR;
	}
	
	/* ִ���̰߳�ȫ���� */
	osMutexWait(spiFlashMutexHandle, osWaitForever);
	for (BU = Sector_Start; BU<=Sector_End; BU++)
	{
		result = W25QXX_Erase_Sector(BU * SPI_FLASH_SectorSize);//��������
	 	if( result != HAL_OK )
	 	{
			osMutexRelease(spiFlashMutexHandle);
			os_printf("\r\n");
			return result;
	 	}
		os_printf("\33[K");
		os_printf("\rerase:%d/%d",BU-Sector_Start+1, Sector_End-Sector_Start+1);
	}
	os_printf("\r\n");
	osMutexRelease(spiFlashMutexHandle);

	return result;
}





/* �̰߳�ȫ�汾��ֻд�벻�������� */
HAL_StatusTypeDef spiFlashWrite(INT32U address, INT8U *buf, INT32U size)
{
	HAL_StatusTypeDef result = HAL_OK;

	if ((address + size) > SPI_FLASH_Size)
	{
		return HAL_ERROR;
	}
	
	/* ִ���̰߳�ȫд�� */
	osMutexWait(spiFlashMutexHandle, osWaitForever);
	W25QXX_SectorWrite (buf, address, size);	//������д������
	osMutexRelease(spiFlashMutexHandle);

	return result;
}

/* �̰߳�ȫ�汾�Ķ����� */
HAL_StatusTypeDef spiFlashRead(INT32U address, INT8U *buf, INT32U size)
{
	HAL_StatusTypeDef result;
	osMutexWait(spiFlashMutexHandle, osWaitForever);
	result = W25QXX_ReadBuffer(buf, address, size);
	osMutexRelease(spiFlashMutexHandle);
	return result;
}


 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
