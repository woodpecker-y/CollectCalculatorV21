/*
***********************************************************************************
*			
*���ܣ�
*
*
*
*˵����1.
*      2.
*      3.
*
*
*By			:��ΰ
*Contact	:511328030@qq.com
*History	:2016-1-28 14:37:47
***********************************************************************************
*/
#ifndef _MALLOC_H_
#define _MALLOC_H_

#include "TypeDef.h"
#include "stm32f10x.h"
#ifdef _MALLOC_C_
#define MALLOC_EXT
#else 
#define MALLOC_EXT extern
#endif 


 
#ifndef NULL
#define NULL 0
#endif

//���������ڴ��
#define SRAMIN		0		//�ڲ��ڴ��
#define SRAMEX		1		//�ⲿ�ڴ��
#define SRAMCCM	2		//CCM�ڴ��(�˲���SRAM����CPU���Է���!!!)


#define SRAMBANK	1		//����֧�ֵ�SRAM����.	


//mem1�ڴ�����趨.mem1��ȫ�����ڲ�SRAM����.
#define MEM1_BLOCK_SIZE			32  	  					//�ڴ���СΪ32�ֽ�
#define MEM1_MAX_SIZE				32*128  						//�������ڴ� 100K
#define MEM1_ALLOC_TABLE_SIZE		MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 	//�ڴ���С

//mem2�ڴ�����趨.mem2���ڴ�ش����ⲿSRAM����
//#define MEM2_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
//#define MEM2_MAX_SIZE			1 *32  						//�������ڴ�960K
//#define MEM2_ALLOC_TABLE_SIZE	MEM2_MAX_SIZE/MEM2_BLOCK_SIZE 	//�ڴ���С
		 
//mem3�ڴ�����趨.mem3����CCM,���ڹ���CCM(�ر�ע��,�ⲿ��SRAM,��CPU���Է���!!)
//#define MEM3_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
//#define MEM3_MAX_SIZE			1 *32  						//�������ڴ�60K
//#define MEM3_ALLOC_TABLE_SIZE	MEM3_MAX_SIZE/MEM3_BLOCK_SIZE 	//�ڴ���С
		 

//�ڴ���������
typedef struct 
{
	void (*init)(u8);					//��ʼ��
	u8 (*perused)(u8);				//�ڴ�ʹ����
	u8 	*membase[SRAMBANK];		//�ڴ�� ����SRAMBANK��������ڴ�
	u16 *memmap[SRAMBANK];			//�ڴ����״̬��
	u8  memrdy[SRAMBANK];			//�ڴ�����Ƿ����
}_m_mallco_dev;

//MALLOC_EXT	_m_mallco_dev mallco_dev;	 //��mallco.c���涨��

#ifdef _MALLOC_C_
void mymemset(void *s,u8 c,u32 count);			//�����ڴ�
void mymemcpy(void *des,void *src,u32 n);		//�����ڴ�     

u32 my_mem_malloc(u8 memx,u32 size);			//�ڴ����(�ڲ�����)
u8 my_mem_free(u8 memx,u32 offset);			//�ڴ��ͷ�(�ڲ�����)
#endif 




MALLOC_EXT	void mymemcpy(void *des,void *src,u32 n);
////////////////////////////////////////////////////////////////////////////////
MALLOC_EXT	void my_mem_init(u8 memx);					//�ڴ�����ʼ������(��/�ڲ�����)

MALLOC_EXT	u8 my_mem_perused(u8 memx);				//����ڴ�ʹ����(��/�ڲ�����)
MALLOC_EXT	void myfree(u8 memx,void *ptr);  			//�ڴ��ͷ�(�ⲿ����)
MALLOC_EXT	void *mymalloc(u8 memx,u32 size);			//�ڴ����(�ⲿ����)
MALLOC_EXT	void *myrealloc(u8 memx,void *ptr,u32 size);	//���·����ڴ�(�ⲿ����)
#endif
