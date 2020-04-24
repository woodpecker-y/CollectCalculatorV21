/*  
***************************************************************
*****************Tools Version 20161020************************
* @copy  COPYRIGHT 2016 Foryon  
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
* @brief :���ļ����ڹ���ɼ�����Ͻ�û��Ĳ���/״̬/����

* 
* 
* 
*
* @author :��ΰ
* @date :2017/8/29 14:51
***************************************************************
*/ 
#ifndef _USERPARA_H_
#define _USERPARA_H_
 


#include "TypeDef.h"
#include "PubDef.h"
#include "W25QXX.H"
#include "FRAM.H"




 
#ifdef _USERPARA_C_
#define USERPARA_EXT
#else
#define USERPARA_EXT extern
#endif






/*�û������ṹ
�洢��Flash
*/
#pragma pack(1)				//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
	INT32U	User_ID;			//�û�ID������λ���·�����������
	INT32U	Reserved;			//�ɼ���ʶ����û�����(һ�����û���ַ)
	
	INT8U	Buld;				//¥����					1
	INT8U	Unit;				//��Ԫ��					1
	INT8U	Floor;				//¥���					1
	INT8U	Cell;				//�����					1

	INT16U	CellArea;			//�������
	INT32U	BuildMeter_ID;		//����¥����ID
}SysUserPara_Stru;


typedef struct
{
	SysUserPara_Stru User[MAXUser_Num];
	INT16U	CRC16;		//У��ֵ
	
}SysUserList_Stru;
#pragma pack()		//�ֽڶ������


USERPARA_EXT SysUserList_Stru SysUserList;		//ϵͳ�û��б�





/* �û�����@״̬ �ṹ
�洢��FRAM
*/
#pragma pack(1)		//�ֽڶ���ģʽ ��ʡ�洢�ռ�
typedef struct
{
						
	INT32S	Remain_Heat; 		//ʣ������
	INT32U	Total_Heat; 		//�û���������	   Ŀǰ�����û���̯�Ŀ��Ʊ�־2017��12��22��
	INT32U	Apportion_Energy;	//��ǰ(��̯)����	//��������
	INT32U	Total_Time; 		//��̯ʱ����ڽ��������ķ�̯����
	INT16U	CRC16;			    //����У��
	
}UserData_Stru;
#pragma pack()		            //�ֽڶ������
USERPARA_EXT UserData_Stru UserData[MAXUser_Num];	//�û������б�








 
 


#ifdef _USERPARA_C_



#endif





HAL_StatusTypeDef SysUserList_Init(void);
HAL_StatusTypeDef SysUserList_Update(void);
HAL_StatusTypeDef SysUserList_Reset(void);




HAL_StatusTypeDef UserData_Read(INT16U ListNum,UserData_Stru* Value);
HAL_StatusTypeDef UserData_Update(INT16U ListNum,UserData_Stru* Value);
HAL_StatusTypeDef UserData_Save(INT16U ListNum);
HAL_StatusTypeDef UserData_InitALL(INT16U UserNum);
HAL_StatusTypeDef UserData_ResetALL(INT16U UserNum);

HAL_StatusTypeDef GetUser_Num(INT32U ID,INT16U* Num);






 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
