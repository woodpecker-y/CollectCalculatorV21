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
* @brief :
* 
* 
* 
*
* @author :
* @date :2017/6/20 12:47
***************************************************************
*/ 
#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_
 



 
#ifdef _TYPEDEF_C_
#define TYPEDEF_EXT
#else
#define TYPEDEF_EXT extern
#endif
 




//  ������������޹ص���������
//********************************************************************************************************
typedef	unsigned char		INT8U;		//  �޷���8λ���ͱ���
typedef	unsigned char		UINT8;		//  �޷���8λ���ͱ���
typedef	unsigned char		U8;			//  �޷���8λ���ͱ���
typedef	unsigned char		u8;			//  �޷���8λ���ͱ���

typedef	signed char			INT8S;		//  �з���8λ���ͱ���
typedef	signed char			SINT8;		 //  �з���8λ���ͱ���
typedef	signed char			S8;			//  �з���8λ���ͱ���
typedef	signed char			s8;			//  �з���8λ���ͱ���


typedef	unsigned short		INT16U;		//  �޷���16λ���ͱ���
typedef	unsigned short		UINT16;	 	//  �޷���16λ���ͱ���
//typedef	unsigned short		U16;             	//  �޷���16λ���ͱ���
typedef	unsigned short		u16;             	//  �޷���16λ���ͱ���


typedef	signed short		SINT16;		//  �з���16λ���ͱ���
typedef	signed short		INT16S;		//  �з���16λ���ͱ���
typedef	signed short		S16;		//  �з���16λ���ͱ���
typedef	signed short		s16;		//  �з���16λ���ͱ���

typedef	unsigned long		INT32U;	//  �޷���32λ���ͱ���
typedef	unsigned long		UINT32;	//  �޷���32λ���ͱ���
//typedef	unsigned long		U32;		//  �޷���32λ���ͱ���

typedef	signed long			INT32S;		 //  �з���32λ���ͱ���
typedef	signed long			SINT32;		//  �з���32λ���ͱ���
//typedef	signed long			S32;		//  �з���32λ���ͱ���

typedef	unsigned long long	INT64U;	//  �޷���64λ���ͱ���      
typedef	unsigned long long	U64;		//  �޷���64λ���ͱ���      
typedef	unsigned long long	u64;		//  �޷���64λ���ͱ���      

typedef	long long			INT64S;		//  �з���64λ���ͱ���		
typedef	long long			S64;		//  �з���64λ���ͱ���		
typedef	long long			s64;		//  �з���64λ���ͱ���		

typedef	float				FL32;		//  �����ȸ�������32λ���ȣ�
typedef	double				FL64;		//  ˫���ȸ�������64λ���ȣ�


///*********************************************************************************************************************





 
#ifdef _TYPEDEF_C_
//*************************�Զ���BCD TO HEX ת�����ݷ�������
#pragma pack(1)
typedef union
{
	INT16U Data;
	struct 
	{
		INT8U Gr0 :4;	//ʮ���Ƶ�1λ
		INT8U Gr1 :4;	//ʮ���Ƶ�2λ
		INT8U Gr2 :4;	//ʮ���Ƶ�3λ
		INT8U Gr3 :4;	//ʮ���Ƶ�4λ
	}Data_Bytes;
}BCD_HEX_2;

typedef union
{
	INT32U Data;
	struct 
	{
		INT8U Gr0 :4;	//ʮ���Ƶ�1λ
		INT8U Gr1 :4;	//ʮ���Ƶ�2λ
		INT8U Gr2 :4;	//ʮ���Ƶ�3λ
		INT8U Gr3 :4;	//ʮ���Ƶ�4λ
		INT8U Gr4 :4;	//ʮ���Ƶ�5λ
		INT8U Gr5 :4;	//ʮ���Ƶ�6λ
		INT8U Gr6 :4;	//ʮ���Ƶ�7λ
		INT8U Gr7 :4;	//ʮ���Ƶ�8λ
	}Data_Bytes;
}BCD_HEX_4;
#pragma pack()





#endif
 




 
 

TYPEDEF_EXT INT8U HexToBcd(INT8U Byte);
TYPEDEF_EXT INT8U BcdToHex(INT8U Byte);
TYPEDEF_EXT INT16U BcdToHex2(INT16U *DATA);
TYPEDEF_EXT INT16U HexToBcd2(INT16U *DATA);
TYPEDEF_EXT INT32U BcdToHex4(INT32U *DATA);
TYPEDEF_EXT INT32U HexToBcd4(INT32U *DATA);


 
#endif
/* END */
/*  
 @copy COPYRIGHT 2016 Foryon     
*/  
 




 
