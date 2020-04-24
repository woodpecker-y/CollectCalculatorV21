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
* @brief :���ļ����ڹ���ɼ�����Ͻ�û��Ĳ���/״̬����
* 
* 
* 
*
* @author :��ΰ
* @date :2017/8/29 14:51
***************************************************************
*/ 
#define _USERPARA_C_
#include "UserPara.h"







/*
	ϵͳ�û��б��ʼ��
	����ϵͳ�ϵ���Flash���µ��ڴ�����
*/
HAL_StatusTypeDef SysUserList_Init(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	Errstate = ReadData_SPIFlash(SysUserList_Addr,(INT8U*)&SysUserList,sizeof(SysUserList_Stru));
	return Errstate;
}
 



 /*
	ϵͳ�û��б����
	���ڵ�ϵͳ���������仯�� ���ڴ����ݸ������洢��
*/
HAL_StatusTypeDef SysUserList_Update(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	Errstate = WriteData_SPIFlash(SysUserList_Addr,(INT8U*)&SysUserList,sizeof(SysUserList_Stru));
	return Errstate;
}



 /*
	ϵͳ�û��б�Ĭ������
	��ϵͳ�����ظ�Ĭ�����ã����Ҹ������洢��
*/
HAL_StatusTypeDef SysUserList_Reset(void)
{
	HAL_StatusTypeDef Errstate =HAL_OK;

	for( INT16U i=0;i<MAXUser_Num;i++)
	{
		SysUserList.User[i].User_ID=0;
		SysUserList.User[i].Reserved=0;
		SysUserList.User[i].Buld =0;
		SysUserList.User[i].Unit=0;
		SysUserList.User[i].Floor=0;
		SysUserList.User[i].Cell=0;
		SysUserList.User[i].CellArea=0;
		SysUserList.User[i].BuildMeter_ID=0;
	}
	Errstate = SysUserList_Update();
	return Errstate;
	
}






/*

��������:�Ӵ洢����ȡ��һ�û�����
*/
HAL_StatusTypeDef UserData_Read(INT16U ListNum,UserData_Stru* Value)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	INT16U Mem_Addr =ListNum*(sizeof(UserData_Stru))+UserData_Addr;   //�洢����ַ����
	INT16U Data_Size =sizeof(UserData_Stru);//�û��������ݴ���
	UserData_Stru Data;
	
	if(ListNum>MAXUser_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	if(ReadData_FRAM(Mem_Addr,(INT8U*)&Data,Data_Size) ==0)
	{
		memcpy((INT8U*)Value,  (INT8U*)&Data,Data_Size);//���������ݴ��ݸ�����ָ��
		ErrFlg =HAL_OK;
	}
	else
	{
		ErrFlg =HAL_ERROR;
	}
	return ErrFlg;

}



/*
��������:��洢��д�뵥һ�û�������

*/

HAL_StatusTypeDef UserData_Update(INT16U ListNum,UserData_Stru* Value)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;		//�����־����
	INT16U Mem_Addr =ListNum*(sizeof(UserData_Stru))+UserData_Addr;   //�洢����ַ����
	INT16U Data_Size =sizeof(UserData_Stru);//�û��������ݴ���

	if(ListNum>MAXUser_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	if(WriteData_FRAM(Mem_Addr, (INT8U*)Value, Data_Size)==0)//д���������
	{
		ErrFlg =HAL_OK;
	}
	else
	{
		ErrFlg =HAL_ERROR;
	}
	return ErrFlg;
}


/*

	�������ܽ��ڴ����ݸ��µ��洢�� 
	�ڸ���֮ǰ�뱣֤�ڴ����ݵ���ȷ
*/
HAL_StatusTypeDef UserData_Save(INT16U ListNum)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;		//�����־����

	UserData_Stru UserPara_WriteBuf;
	if (ListNum>MAXUser_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	UserPara_WriteBuf =UserData[ListNum];
	ErrFlg =UserData_Update( ListNum,&UserPara_WriteBuf);
	return ErrFlg;
}






/*
��������:UserDara_InitALL(INT16U UserNum)
��������:��ϵͳ���������ϵ��ʼ�� (�Ӵ洢����ָ��λ�ö�ȡ����,��������������û�����)
����:��
����ֵ:  ����0X00;����ֵ  �쳣
*/
HAL_StatusTypeDef UserData_InitALL(INT16U UserNum)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	UserData_Stru UserDataB;

	if (UserNum>MAXUser_Num)
	{
		ErrFlg =HAL_ERROR;
		return ErrFlg;
	}
	for (INT16U i =0; i<UserNum;i++)
	{
		ErrFlg=UserData_Read(i,&UserDataB);
		if (ErrFlg ==HAL_OK )
		{
			UserData[i] =UserDataB;
		}
		else
		{
			ErrFlg =HAL_ERROR;
			break;
		}
	}
	return ErrFlg;
	
}





/*
��������:���û����ݻظ���������
*/
HAL_StatusTypeDef UserData_ResetALL(INT16U UserNum)
{
	HAL_StatusTypeDef ErrFlg =HAL_OK;
	UserData_Stru DataBuffer;
	
	
	DataBuffer.Remain_Heat =0;		//ʣ������
	DataBuffer.Total_Heat =0;		//�û���������
	DataBuffer.Apportion_Energy =0;	//��̯���� /��ǰ���
	DataBuffer.Total_Time =0;		//����ʱ��
	
	for(INT16U i =0; i<UserNum;i++)
	{
		DataBuffer =UserData[i] =DataBuffer;
		ErrFlg=UserData_Update(i,&DataBuffer);
		
		if ( ErrFlg==HAL_OK)
		{
			continue;
		}
		else
		{
			ErrFlg =HAL_ERROR;
		}
	}
	
	return ErrFlg;
	
}




/*
	�����û���ID ��ȡ�û��б��±�
*/
HAL_StatusTypeDef GetUser_Num(INT32U ID,INT16U* Num)
{
	for( INT16U A=0;A<MAXUser_Num;A++)
	{

		if(SysUserList.User[A].User_ID ==ID)
		{
			*Num =A;
			return HAL_OK;
		}
	}
	
	return HAL_ERROR;
	
}








/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
