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
* @date :2016-12-10 15:23
***************************************************************
*/ 
#define _INDEPKEY_C_
#include "IndepKEY.h"
 
/*
    ��������: void IndepKEYFunction_Init(void)
    ��������:  �����������ܳ�ʼ��
    
*/

void IndepKEYFunction_Init(void)
{
	INT8U i;
	IndepKEYPara_Stru Para;

	#if IndepKEY_ExtInitHOOK==1

	 (*IndepKEY_ExtInitHooks)();

	#endif

	Para.TrigCondition =DEFNULL;
	Para.FallEdge_Num =100;
	Para.LowLevel_Num =1000;
	Para.LowLevel_NumFirst =2000;
	Para.UpEdge_Num =100;

	for(i = 0;i < IndepKEY_Num;i ++)
	{
		IndepKEY_Ctrler[i].Enable =DISABLE;
		IndepKEY_Ctrler[i].TrigPara =Para;
		IndepKEY_Ctrler[i].PreStatus =DEFNULL;
		IndepKEY_Ctrler[i].CurStatus =DEFNULL;
		IndepKEY_Ctrler[i].TrigStatus =DEFNULL;

		IndepKEY_Ctrler[i].FallEdge_Count =0;
		IndepKEY_Ctrler[i].LowLevel_CountFirst =0;
		IndepKEY_Ctrler[i].LowLevel_Count =0;
		IndepKEY_Ctrler[i].UpEdge_Count =0;
		IndepKEY_Ctrler[i].TrigOUT =NULL;
	}
}



/*
    ��������: �������ҽӶ�������
    @para  Enable: ʹ�ܱ�־
    @para    ParaS: ��������
                    InputHooks:��ں��������ذ���ֵ 
                    OutPutHooks :���ں��������������㴥��������ִ��
    @return   : ��������ָ��              
*/
IndepKEY_Stru*  IndepKEY_Create(FunctionalState Enable, IndepKEYPara_Stru ParaS, IndepKEY_State (*InputHooks)(void),void (*OutPutHooks)(void))
{

	
	if(IndepKEY_Limiter >= IndepKEY_Num)
	{
		return 0;
	}
	
	IndepKEY_Ctrler[IndepKEY_Limiter].Enable = Enable;
	IndepKEY_Ctrler[IndepKEY_Limiter].TrigPara= ParaS;
	IndepKEY_Ctrler[IndepKEY_Limiter].GetKeyStatus= InputHooks;
	IndepKEY_Ctrler[IndepKEY_Limiter].TrigOUT= OutPutHooks;
	IndepKEY_Ctrler[IndepKEY_Limiter].PreStatus =(*IndepKEY_Ctrler[IndepKEY_Limiter].GetKeyStatus)();//��ֵ��ȡ
	IndepKEY_Limiter +=1;	
	return &IndepKEY_Ctrler[IndepKEY_Limiter - 1];
	
	
}


/*
     ��������: �޸�/���� ������������
    @para      Member: ����ָ��
                    ParaS     : ��������

*/

void IndepKEY_ParaSet(IndepKEY_Stru* Member,IndepKEYPara_Stru ParaS)
{
    FunctionalState  EnaFlag;

    EnaFlag =Member->Enable;
	Member->Enable = DISABLE;
	Member->TrigPara =ParaS;
	Member->Enable = EnaFlag;
}


/*  
    ʹ�ܶ�������
    @ para  Member   
    @ Enable ʹ�ܱ�־
*/
void IndepKEY_Enable(IndepKEY_Stru *Member,FunctionalState Enable)
{
	Member->Enable = Enable;
}



/*
    ��������ɨ�������
    @para:       null
    @return :   null

    ע������: ���������Է��� Ӧ������ɨ��  �˲� �Ƚ� �Լ���ֵʶ�����ز�����ɨ�������������
   
*/
void IndepKEY_ScanServer(void)  
{
	INT8U i =0;

	IndepKEY_State Status =ReadStateOFF;
	for ( i =0;i<IndepKEY_Num;i++)
	{
		if( IndepKEY_Ctrler[i].Enable ==ENABLE)	//��Աʹ��
		{
			Status =(*IndepKEY_Ctrler[i].GetKeyStatus)();
			if ( IndepKEY_Ctrler[i].PreStatus!=Status)		//��⵽������������
			{
				IndepKEY_Ctrler[i].LowLevel_CountFirst =0;		//��ƽ��������������
				IndepKEY_Ctrler[i].LowLevel_Count =0;		//��ƽ��������������

		        if( Status ==ReadStateON)	//�½��صĴ�����������
				{
					IndepKEY_Ctrler[i].FallEdge_Count +=1;	//�½����˲�����ֵ�ۼ�
					if(IndepKEY_Ctrler[i].FallEdge_Count >=IndepKEY_Ctrler[i].TrigPara.FallEdge_Num)
					{
						if(IndepKEY_Ctrler[i].TrigPara.TrigCondition&FallEdge)//��������
						{
							IndepKEY_Ctrler[i].TrigStatus =FallEdge;
						    (*IndepKEY_Ctrler[i].TrigOUT)();		//���ں�������
						}
						IndepKEY_Ctrler[i].PreStatus=Status;	//״̬��¼
						IndepKEY_Ctrler[i].FallEdge_Count =0;	//�½����˲�����ֵ����
					}
				}

				if(Status ==ReadStateOFF) //�����صĴ�����������
				{
					IndepKEY_Ctrler[i].UpEdge_Count +=1;	//�������˲�����ֵ�ۼ�
					if(IndepKEY_Ctrler[i].UpEdge_Count >=IndepKEY_Ctrler[i].TrigPara.UpEdge_Num)
					{
						if(IndepKEY_Ctrler[i].TrigPara.TrigCondition&UpEdge)//��������
						{
							IndepKEY_Ctrler[i].TrigStatus =UpEdge;
                            (*IndepKEY_Ctrler[i].TrigOUT)();		//���ں�������
						}
						IndepKEY_Ctrler[i].PreStatus=Status;	//״̬��¼
						IndepKEY_Ctrler[i].UpEdge_Count =0;	//�������˲�����ֵ����
					}
				}
			}
			
			else 	//û�м�⵽��ƽ��ת   ˵������Ϊ������ƽ
			{
				IndepKEY_Ctrler[i].UpEdge_Count =0;	//���ش�������������
				IndepKEY_Ctrler[i].FallEdge_Count =0;
				if((Status ==ReadStateON))    //�͵�ƽ�Ĵ����������������
				{

					IndepKEY_Ctrler[i].LowLevel_CountFirst +=1;
					IndepKEY_Ctrler[i].LowLevel_Count +=1;	//�������˲�����ֵ�ۼ�
					if( IndepKEY_Ctrler[i].LowLevel_CountFirst >=IndepKEY_Ctrler[i].TrigPara.LowLevel_NumFirst)//�״��½����˲�����
					{
						if(IndepKEY_Ctrler[i].LowLevel_Count >=IndepKEY_Ctrler[i].TrigPara.LowLevel_Num)
						{
							IndepKEY_Ctrler[i].UpEdge_Count =0;	//�������˲�����ֵ����
							if(IndepKEY_Ctrler[i].TrigPara.TrigCondition&LowLevel)
							{
								IndepKEY_Ctrler[i].TrigStatus =LowLevel;
							    (*IndepKEY_Ctrler[i].TrigOUT)();		//���ں�������
							}
							IndepKEY_Ctrler[i].LowLevel_Count =0;	//�������˲�����ֵ����						
						}
					}
				}
			}
		}
	}

}




















 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
 




 
