
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
* @date :2016-11-24 18:15
***************************************************************
*/ 
#ifndef _UC1698_H_
#define _UC1698_H_
 


#include "stm32f4xx_hal.h"
#include "TypeDef.h"
#include "String.h"
#include "ZM.h" 
#include "cmsis_os.h"

 
#ifdef _UC1698_C_
#define UC1698_EXT
#else
#define UC1698_EXT extern
#endif




//LCD���ݶ˿ں궨��
#define LCD_DATA_PORT	GPIOE		//�˿ں�
#define LCD_DATA_LowBit	8			//���λ���ź�

#define LCD_DATA0_Bit	GPIO_PIN_8
#define LCD_DATA1_Bit	GPIO_PIN_9
#define LCD_DATA2_Bit	GPIO_PIN_10
#define LCD_DATA3_Bit	GPIO_PIN_11
#define LCD_DATA4_Bit	GPIO_PIN_12
#define LCD_DATA5_Bit	GPIO_PIN_13
#define LCD_DATA6_Bit	GPIO_PIN_14
#define LCD_DATA7_Bit	GPIO_PIN_15




//LCD���ƶ˿ں궨��
#define LCD_A0_Group	GPIOB
#define LCD_A0_Bit		GPIO_PIN_13
#define LCD_A0_1		(HAL_GPIO_WritePin(LCD_A0_Group, LCD_A0_Bit, GPIO_PIN_SET))
#define LCD_A0_0		(HAL_GPIO_WritePin(LCD_A0_Group, LCD_A0_Bit, GPIO_PIN_RESET))

#define LCD_WR_Group	GPIOB
#define LCD_WR_Bit		GPIO_PIN_12
#define LCD_WR_1		(HAL_GPIO_WritePin(LCD_WR_Group, LCD_WR_Bit, GPIO_PIN_SET))
#define LCD_WR_0		(HAL_GPIO_WritePin(LCD_WR_Group, LCD_WR_Bit, GPIO_PIN_RESET))

#define LCD_RD_Group	GPIOE
#define LCD_RD_Bit		GPIO_PIN_7
#define LCD_RD_1		(HAL_GPIO_WritePin(LCD_RD_Group,LCD_RD_Bit,GPIO_PIN_SET))
#define LCD_RD_0		(HAL_GPIO_WritePin(LCD_RD_Group,LCD_RD_Bit,GPIO_PIN_RESET))


#define LCD_CS_Group	GPIOB
#define LCD_CS_Bit		GPIO_PIN_1
#define LCD_CS_1		(HAL_GPIO_WritePin(LCD_CS_Group,LCD_CS_Bit,GPIO_PIN_SET))
#define LCD_CS_0		(HAL_GPIO_WritePin(LCD_CS_Group,LCD_CS_Bit,GPIO_PIN_RESET))


#define LCD_RST_Group	GPIOB
#define LCD_RST_Bit		GPIO_PIN_0
#define LCD_RST_1		(HAL_GPIO_WritePin(LCD_RST_Group,LCD_RST_Bit,GPIO_PIN_SET))
#define LCD_RST_0		(HAL_GPIO_WritePin(LCD_RST_Group,LCD_RST_Bit,GPIO_PIN_RESET))

#define LCD_BL_Group	GPIOC
#define LCD_BL_Bit		GPIO_PIN_5
#define LCD_BL_ON		(HAL_GPIO_WritePin(LCD_BL_Group,LCD_BL_Bit,GPIO_PIN_SET))
#define LCD_BL_OFF		(HAL_GPIO_WritePin(LCD_BL_Group,LCD_BL_Bit,GPIO_PIN_RESET))






/*
��ʾ�������궨�壬���ֶ������ ����ͬ��ʵҵҺ�� TG160160B-18ϵ��

Һ���ص㣺����ɨ�� ÿ������Ϊ4bit ���Խ��лҶȵ��� ÿ��ɨ����������Ϊ162�� =81�ֽ�

Ӧ�ü��� ͨ��ʵ�ʵ���λͼ���е���ת�� 1���Ӧ4λȻ�������ʾ������� ���ͨ�����ɨ�跽ʽʵ��ˢ������
*/
#define LCD_Column_NUM	160			//Һ��ʵ����Ч������
#define LCD_Row_NUM		160			//Һ��ʵ����Ч������
#define LCD_Column_Word	20			//Һ���Ӿ�����������д�������������ַ�ʽ�������һ���ֽڵı����֣�������3���ֽ����� 20*4+1 =81
#define LCD_Column_Byte	81			//Һ��RAM ����������д���ֽ������������� 3�ı���





#pragma pack(1)		//�ֽڶ���
typedef union _LCDRAM
{
	INT8U data_S[LCD_Column_Byte*LCD_Row_NUM];		//ȫ��ɨ��
	INT8U Scan_Value[LCD_Row_NUM][LCD_Column_Byte];	//����ɨ��
	struct 
	{
		uint32_t	Word[LCD_Column_Word];				//ÿ�а���20��˫��   ע��С��ģʽ
		INT8U 	reserved;
		
	}group[LCD_Row_NUM];

}LCD_dis_Stru;
#pragma pack()

UC1698_EXT LCD_dis_Stru LCD_RAM;		//����Һ��RAM��������������Ϊʵ��Һ����ʾ����������




//******************************************************************************************
#define LCD_Width	LCD_Column_NUM
#define LCD_Hight	LCD_Row_NUM

typedef struct
{
	INT8U	ColBuf[((LCD_Width%8)>0)?((LCD_Width/8)+1):(LCD_Width/8)];//���ֽ���
}Vision_Stru;

UC1698_EXT Vision_Stru	VisionBuf[LCD_Hight];	//�����Ӿ����ݻ�����

//*****************************************************************


UC1698_EXT void LCD_REST(void);
UC1698_EXT void LCD_IOInit(void);	//LCD�˿�����
UC1698_EXT void Lcd_Init(void);//LCD��ʼ��

UC1698_EXT void PutData8(GPIO_TypeDef * PORT,INT8U LowBit,INT8U data);//�˿ڼĴ�������
UC1698_EXT void LCD_WriteCmd(INT8U Cmd);//дָ��
UC1698_EXT void LCD_WriteOneByte(INT8U Data);//д����


UC1698_EXT INT8U Fill_LcdRAM_1DOT(INT8U Row,INT8U Column,INT8U DOT);	//���һ������
UC1698_EXT INT8U Fill_LcdRAM_Row(INT8U Row,INT8U DOT);					//���һ��
UC1698_EXT INT8U Fill_LcdRAM_Column(INT8U Column,INT8U DOT); 			//���һ��
UC1698_EXT INT8U Fill_LcdRAM_Region_ALL(INT8U DOT); 						//ȫ����ڻ�������


UC1698_EXT INT8U Fill_LcdRAM_Region(INT8U Row1,INT8U Column1,INT8U Row2,INT8U Column2,INT8U DOT);//�����������������
UC1698_EXT INT8U Fill_LcdRAM_Region_Opposite(INT8U Row1,INT8U Column1,INT8U opposite_X,INT8U opposite_Y,INT8U DOT);//�����������������

UC1698_EXT void Update_LcdRAM_ALL(void);//����LCDRAM
UC1698_EXT INT8U  GUI_Point(INT8U X, INT8U Y, INT8U Color);
UC1698_EXT INT8U  GUI_Line( int16_t x, int16_t y, int16_t x1, int16_t y1, INT8U color) ;//��һ��ֱ��UC1698_EXT
UC1698_EXT void  GUI_Circle(uint32_t x0, uint32_t y0, uint32_t r, INT8U color);
UC1698_EXT INT8U GUI_Rectangle(INT16U Xs, INT16U Ys,INT16U Xf, INT16U Yf,INT8U Color);
UC1698_EXT INT8U GUI_Rectangle_Dev(INT16U Xs, INT16U Ys,INT16U Xf, INT16U Yf, INT16U DevNum,INT8U Color);
UC1698_EXT INT8U Fill_VisionBUF(INT8U X1,INT8U Y1,INT8U X2,INT8U Y2,INT8U Data);



UC1698_EXT INT16U FindZMStation(uint16_t Code);

UC1698_EXT void DispArray(uint16_t XAdd,uint16_t YAdd,uint16_t Width,uint16_t Hight,INT8U DispMode,const unsigned char *Array);

UC1698_EXT void DispStringM(uint16_t Xadd,uint16_t Yadd,   const  char *Letters,INT8U Mode,INT8U FontType);



UC1698_EXT void Update_VisionBuf_TO_LcdRAM(void) ;	 
UC1698_EXT void Clear_VisionBUF(void); //����Ӿ�������
UC1698_EXT void Refresh_Screen(void);


UC1698_EXT void Update_LcdRAM_Row(INT8U StartRow,INT8U Rows);
UC1698_EXT void Refresh_Screen_Row(INT8U StartRow,INT8U Rows);

UC1698_EXT char* Disp_Integer(int Data);
UC1698_EXT char* Disp_Float(float Data,int B);
UC1698_EXT char* Disp_Float_Point(INT32U Data,int B,float C);

UC1698_EXT char* Disp_BCD_32(INT32U input);
UC1698_EXT char* Disp_BCD_16(INT16U input);
UC1698_EXT char* Disp_BCD_8(INT8U input);

UC1698_EXT char* Disp_32_Binary(INT32U Data,int B,int C,int D);
UC1698_EXT char* Disp_16_Binary(INT16U Data,int B,int C,int D);
UC1698_EXT char* Disp_8_Binary(INT8U Data,int B,int C,int D);

#endif


