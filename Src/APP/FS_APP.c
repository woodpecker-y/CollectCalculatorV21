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
* @date :2017/9/15 12:59
***************************************************************
*/ 
#define _FS_APP_C_
#include "FS_APP.h"
 



extern char SD_Path[4];					// SD���߼��豸·��

FATFS fs;							// FatFs�ļ�ϵͳ����
FIL file; 							// �ļ�����
FRESULT f_res;						//�ļ�������� 
UINT fnum;						//�ļ��ɹ���д����
BYTE ReadBuffer[4096]={0};        		//��������
BYTE WriteBuffer[4096]= "��ӭʹ�ã����ļ����ڲ���FATFS�ļ�ϵͳ\r\n";//д������  





 



/*
��������:Get_SDCard_CAP
��������:��ȡSD����������Ϣ

@para *TotalSize ������
@para *FreeSize	ʣ������
@retval Norn
*/

void Get_SDCard_CAP(INT32U *TotalSize ,INT32U*FreeSize)
{
	FATFS fs;
	FATFS *pfs;
	INT32U fre_clust;
	INT32U Total;
	INT32U Free;
	INT32U res;
	pfs=&fs;
	f_mount(&fs,"", 1);  //�����ļ�ϵͳ
	res = f_getfree("", &fre_clust, &pfs);
	if (res) 
	{	
		return; 		//����������в���ȷ�����ش���ֵ
	}
	else 				//���������ȷ
	{
		Total = (pfs->n_fatent - 2) * pfs->csize/2; // ��λKbyte
		Total = Total/1024;	//��λ Mbyte
		
		Free = fre_clust * pfs->csize/2; // ��λkbyte
		Free = Free/1024;		//��λ Mbyte
	}
	*TotalSize =Total;
	*FreeSize =Free;
	f_mount(0, 0, 1);// ж���ļ�ϵͳ
	
}


void Test(void)
{
	
		f_res = f_mount(&fs,(TCHAR const*)SD_Path,1);		//��SD�������ļ�ϵͳ���ļ�ϵͳ����ʱ���SD����ʼ��
		

		WriteBuffer[512] = 'f';
		WriteBuffer[1024] = 'u';
		WriteBuffer[512+1024] = 'c';
		WriteBuffer[2048] = 'k';


		if(f_res == FR_NO_FILESYSTEM)					//���û���ļ�ϵͳ�͸�ʽ�����������ļ�ϵͳ
		{
			printf(">>��SD����û���ļ�ϵͳ���������и�ʽ��...\r\n");
			f_res=f_mkfs((TCHAR const*)SD_Path,0,0);			//��ʽ�� 			
		  
			if(f_res == FR_OK)
			{
				printf("��SD���ѳɹ���ʽ���ļ�ϵͳ��\r\n");
				
				f_res = f_mount(NULL,(TCHAR const*)SD_Path,1);			// ��ʽ������ȡ������SD��
				
				f_res = f_mount(&fs,(TCHAR const*)SD_Path,1);			// ���¹���SD��
			}
			else
			{
				printf(">>>>>��ʽ��ʧ��");
				while(1);
			}
		}
		else if(f_res!=FR_OK)
		{
			printf("����SD�������ļ�ϵͳʧ�ܡ�(%d)\r\n",f_res);
			while(1)
			{
				
			}
		}
		else
		{
			printf(">>>>�ļ�ϵͳ���سɹ��������ʹ��....");
		}

		
		// ********************************�ļ�д�����******************************************
		printf("****** ���������ļ�д�����... ******\r\n");		// ���ļ�������ļ��������򴴽���
		
		f_res = f_open(&file, "02345.txt",FA_CREATE_ALWAYS | FA_WRITE );
		if ( f_res == FR_OK )
		{
			printf("02345.txt�ļ��򿪳ɹ������ļ�д������...");

			f_res=f_write(&file,WriteBuffer,sizeof(WriteBuffer),&fnum); 		//��ָ���洢������д�뵽�ļ���
			if(f_res==FR_OK)
			{
				printf(">>>>>>�ļ�д��ɹ���д���ֽ����ݣ�%d\r\n",fnum);
				printf(">>>>>>���ļ�д�������Ϊ��\r\n%s\r\n",WriteBuffer);
			}
			else
			{
				printf("�����ļ�д��ʧ�ܣ�(%d)\r\n",f_res);
			}    
		  
		  	f_close(&file);		//�ر��ļ�
		}
		else
		{		 
			printf("������/�����ļ�ʧ�ܡ�\r\n");
			while(1);
		}
		
		//------------------- �ļ���ȡ���� ------
		printf("****** ���������ļ���ȡ����... ******\r\n");
		f_res = f_open(&file, "02345.txt", FA_OPEN_EXISTING | FA_READ); 		 
		if(f_res == FR_OK)
		{
			printf(">>>>�ļ��򿪳ɹ�....");
			memset(ReadBuffer,0x00,4096);
			f_res = f_read(&file, ReadBuffer, sizeof(ReadBuffer), &fnum); 
			if(f_res==FR_OK)
			{
				  printf(">>>>>>�ļ���ȡ�ɹ�,�����ֽ����ݣ�%d\r\n",fnum);
				  printf(">>>>>>��ȡ�õ��ļ�����Ϊ��\r\n%s \r\n", ReadBuffer);
					printf("%c",ReadBuffer[512]);	
					printf("%c",ReadBuffer[1024]);
					printf("%c",ReadBuffer[512+1024]);
					printf("%c",ReadBuffer[2048]);  
			}
			else
			{
				printf("�����ļ���ȡʧ�ܣ�(%d)\r\n",f_res);
			} 			   
		}
		else
		{
	   		printf("�������ļ�ʧ��...");
			while(1);
		}
		f_close(&file);							//���ٶ�д���ر��ļ� 
		printf("�ļ��ر�....");
		f_res = f_mount(NULL,(TCHAR const*)SD_Path,1);// ����ʹ�ã�ȡ������
		printf("�ļ�ϵͳж�����....");
		
	


}




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
