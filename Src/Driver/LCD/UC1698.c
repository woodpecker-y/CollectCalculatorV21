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
* @date :2016-11-24 18:15
***************************************************************
*/ 
#define _UC1698_C_
#include "UC1698.h"
#include "math.h"





const uint8_t BitTable[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

const uint8_t BitTab[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};


/*�в�����ʱ����*/
void delay(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--);
}


/*
�ú�����ֲ���׼�� ���ڶ�ȡ ĳ���ܽżĴ����������

*/
INT16U GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
	/* Check the parameters */
	return ((INT16U)GPIOx->ODR);
}



/*
�ú�����ֲ���׼�� �������� ĳ���ܽżĴ����������

*/
void GPIO_Write(GPIO_TypeDef* GPIOx, INT16U PortVal)
{

	GPIOx->ODR = PortVal;
}







/*
��������:LCD_REST
��������:��Һ������Ӳ����λ 


*/
void LCD_REST(void)
{
	osDelay(50);
	LCD_RST_0;
	osDelay(5);
	LCD_RST_1;
	osDelay(5);
}


/*
��������:LCD_IOInit
��������:��LCD����ģ��ĹܽŽ������� ģʽ��ʼ��

*/
void LCD_IOInit(void)
{
	GPIO_InitTypeDef  LCD_IOInitStructure;

    /* ʹ��LCD��ӦGPIO��Clockʱ�� */

   	__HAL_RCC_GPIOA_CLK_ENABLE();
   	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();



	/* ��ʼ��LCD��A0�ܽţ�����Ϊ������� */
	LCD_IOInitStructure.Pin = LCD_A0_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_A0_Group, &LCD_IOInitStructure);	


	/* ��ʼ��LCD��WR�ܽţ�����Ϊ������� */
	LCD_IOInitStructure.Pin = LCD_WR_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_WR_Group, &LCD_IOInitStructure);	



	/* ��ʼ��LCD��RD�ܽţ�����Ϊ������� */
	LCD_IOInitStructure.Pin = LCD_RD_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_RD_Group, &LCD_IOInitStructure);	


	/* ��ʼ��LCD��CS�ܽţ�����Ϊ������� */
	LCD_IOInitStructure.Pin = LCD_CS_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_CS_Group, &LCD_IOInitStructure);	



	
	
	/* ��ʼ��LCD��RST�ܽţ�����Ϊ������� */
	LCD_IOInitStructure.Pin = LCD_RST_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_RST_Group, &LCD_IOInitStructure);	
	LCD_RST_1;


	
	/* ��ʼ��LCD��BL�ܽţ�����Ϊ������� */
	LCD_IOInitStructure.Pin = LCD_BL_Bit;
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_BL_Group, &LCD_IOInitStructure);	
	LCD_BL_ON;

    /* ��ʼ��LCD��DATA�ܽţ�����Ϊ������� */				  //���ö˿�
    LCD_IOInitStructure.Pin = LCD_DATA0_Bit | LCD_DATA1_Bit | LCD_DATA2_Bit |LCD_DATA3_Bit | LCD_DATA4_Bit | LCD_DATA5_Bit | LCD_DATA6_Bit| LCD_DATA7_Bit;   
	LCD_IOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	LCD_IOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD_DATA_PORT, &LCD_IOInitStructure);		
}





/*
 ��������:	��GPIO�˿ڼĴ�������ָ������8λ����(����)����Ӱ������λ
 LowBit:	���λ
 data	��	�����ֽ�

*/
void PutData8(GPIO_TypeDef * PORT,uint8_t LowBit,uint8_t data)
{
	uint16_t DataBuf =0;
	uint16_t value =data;
	DataBuf=GPIO_ReadOutputData(PORT);
	value =(value<<LowBit);
	DataBuf &=~(0XFF<<LowBit);
	value =value|DataBuf;
	GPIO_Write(PORT,value);
}



/*
�������ƣ�void LCD_WriteCmd(uint8_t cmd)
�������ܣ���LCD����ICд��һ���ֽڵĿ���ָ��


*/
void LCD_WriteCmd(uint8_t Cmd)
	
{
//	LCD_XCS=0;
//	GPIO_ResetBits(LCD_CS_Group,LCD_CS_Bit);
	LCD_CS_0;
	
//	LCD_A0=0;
//	GPIO_ResetBits(LCD_A0_Group,LCD_A0_Bit);
	LCD_A0_0;
	
//	LCD_RD=1;
//	GPIO_SetBits(LCD_RD_Group,LCD_RD_Bit);
	LCD_RD_1;
	
//	LCD_WR=0;
//	GPIO_ResetBits(LCD_WR_Group,LCD_WR_Bit);
	LCD_WR_0;
	
//	port=cmd;
	PutData8(LCD_DATA_PORT,LCD_DATA_LowBit,Cmd);
	
//	LCD_WR=1;
//	GPIO_SetBits(LCD_WR_Group,LCD_WR_Bit);
	LCD_WR_1;
	
//	LCD_XCS=1;
//	GPIO_SetBits(LCD_CS_Group,LCD_CS_Bit);
	LCD_CS_1;
	
	
}

/*
��������:void LCD_WriteOneByte(uint8_t Data)
��������:��Һ������ICд��һ���ֽڵ�����/ָ��
Data����������
*/

void LCD_WriteOneByte(uint8_t Data)
{
//	LCD_XCS=0;
//	GPIO_ResetBits(LCD_CS_Group,LCD_CS_Bit);
	LCD_CS_0;
	
//	LCD_A0=1;
//	GPIO_SetBits(LCD_A0_Group,LCD_A0_Bit);
	LCD_A0_1;
	
//	LCD_RD=1;
//	GPIO_SetBits(LCD_RD_Group,LCD_RD_Bit);
	LCD_RD_1;
	
//	LCD_WR=0;
//	GPIO_ResetBits(LCD_WR_Group,LCD_WR_Bit);
	LCD_WR_0;
	
//	port=dat;
	PutData8(LCD_DATA_PORT,LCD_DATA_LowBit,Data);
	
//	LCD_WR=1;
//	GPIO_SetBits(LCD_WR_Group,LCD_WR_Bit);
	LCD_WR_1;
	
//	LCD_XCS=1;
//	GPIO_SetBits(LCD_CS_Group,LCD_CS_Bit);
	LCD_CS_1;
}


/*
	��������:��Һ�����г�ʼ��
	����˵��:��Һ��ֻ���������ͬ��ʵҵ�ṩ��TG160160B-18ϵ��Һ�����ú���Ҳ�ɹٷ��ṩ ���õ�����оƬΪUC1698
	ע������:��ʹ�øú���֮ǰӦ����Һ�����ϵ縴λ����  ��RST�ܽ�����  Ȼ����̧��
*/
void Lcd_Init(void)
{
	
	//дָ���     // (ָ����еĶ�����ָ��)   ָ��Ӣ�����Ͳ���   ָ�����Ľ���
	LCD_WriteCmd(0xE2); // (23) SYSTEM RESET    ϵͳ��λ

	LCD_WriteCmd(0xC8);// (19)SET N-LINE INVERSION
 	LCD_WriteCmd(0x13);
 	
 	LCD_WriteCmd(0xA0);//(14)SET LINE rate
 	
	LCD_WriteCmd(0XEB); // (26) SET LCD BIAS RATIO   0xE8:5  0xE9:10  0xEA:11  0xEB:12     ����LCD��ƫѹ��

	LCD_WriteCmd(0x81); // (10) SET VBIAS POTENTIOMETER     ����VOPָ��
	LCD_WriteCmd(120); //  set  vop  0~255  d8:17.0v               ���������VOPֵ  ֵԽ����ʾԽ��	//b8:16.2v

	LCD_WriteCmd(0xaf); // (17) SET DISPLAY ENABLE

	LCD_WriteCmd(0xf4); //  (30) SET WINDOW PROGRAM STARTING COLUMN ADDRESS  ������ʾ���ڣ�����ʾRAM��������ߵ�һ�����߶�ӦIC��SEGλ��
	LCD_WriteCmd(0x25); //     ����  3x27��0x25��=111  LCD  �ڲ��߼�������ߵĵ�һ�����߶�ӦUC1698��SEG112��
				 //     �����3x27�е�3������  UC1698�ǲ���IC  һ����ɫ������������ɫ��R G B ����ɣ�
				 //     �������ǽ�������ɫ��R G B ��ֱ�������ʾ������ɫ�ĺڰ׵�

	LCD_WriteCmd(0xf5); //  (31) SET WINDOW PROGRAM STARTING ROW ADDRESS    ������ʾ���ڣ�����ʾRAM�������ϱߵ�һ�����߶�ӦIC��COMλ��
	LCD_WriteCmd(0x00); //      ����  0(0x00)           LCD  �ڲ��߼������ϱߵĵ�һ�����߶�ӦUC1698��COM1��

	LCD_WriteCmd(0xf6); //  (32) SET WINDOW PROGRAM ENDING COLUMN ADDRESS    ������ʾ���ڣ�����ʾRAM�������ұ����һ�����߶�ӦIC��SEGλ��
	LCD_WriteCmd(0x5A); //      ����  3x90��0x5A��=270  LCD  �ڲ��߼������ұߵ����һ�����߶�ӦUC1698��SEG271��   270 - 111 = 160���պ�160�����ߣ�

	LCD_WriteCmd(0xf7); //  (33) SET WINDOW PROGRAM ENDING ROW ADDRESS      ������ʾ���ڣ�����ʾRAM�������±����±�һ�����߶�ӦIC��COMλ��
	LCD_WriteCmd(0xa0); //      ����  160(0xa0)         LCD  �ڲ��߼������±�һ�����߶�ӦUC1698��COM160
                 //   ����ͼ    �Դ��С�������Ϊ'-'��'+'���� ������û��TG160160 ��ʾ���ڽ��������Ϊ'+'����,���Ϊ'-'����������д���ݣ������ǵ����Ͽ�����
                 //        seg1 seg2  seg3 ... seg111 seg112 seg113 ... seg269 seg270 seg271 ... seg384
                 //  com160  -   -     -    -    -      +      +     +     +     +       -    -     -
                 //  com159  -   -     -    -    -      +      +     +     +     +       -    -     -
                 //  com158  -   -     -    -    -      +      +     +     +     +       -    -     -
                 //  ...     -   -     -    -    -      +      +     +     +     +       -    -     -
                 //  com2    -   -     -    -    -      +      +     +     +     +       -    -     -
                 //  com1    -   -     -    -    -      +      +     +     +     +       -    -     -


	LCD_WriteCmd(0xf8); //  (34) SET WINDOW PROGRAM MODE  ������ʾ���ڵı��ģʽ ���ó��ڲ�ģʽ��ac3=0����
                 //      ʹд��ʾ����ʱ���Դ�ĵ�ַָ���������������õĴ������0xf4  0xf5 0xf6 0xf7��Ϊ�߽��Զ�����
	LCD_WriteCmd(0xd1); //  (20) SET COLOR PATTERN ����ɫ����ʽ ����RGB��SEG�Ķ�Ӧ��ϵ
                 //       ����(0xd1) RGB��SEG�Ķ�Ӧ��ϵΪ  SEG1->R SEG2->G SEG3->B SEG4->R ......  SEG111->R ѭ��
	LCD_WriteCmd(0xd5); //  (21) SET COLOR MODE   ����ɫ��ģʽ
                 //       ���� (0xd5)  LC[7:6] = 01b  ( RRRR-GGGG-BBBB, 4K-color��4Kɫ��)
                 //       8λ�ӿ�д�����ֽ�˳��      DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0 ÿ���ֽڶ�Ӧλ����ɫ��ϵ�����ǵ���Ϊ��ɫ����ҲҪע��˳��
                 //         д��һ���ֽ�����         R3  R2  R1  R0  G3  G2  G1  G0
                 //         д�ڶ����ֽ�����         B3  B2  B1  B0  R3  R2  R1  R0
                 //         д�������ֽ�����         G3  G2  G1  G0  B3  B2  B1  B0
                 //         д���ĸ��ֽ�����         R3  R2  R1  R0  G3  G2  G1  G0   ѭ�� ͬ��һ���ֽ�����
                 //         R3R2R1R0  G3G2G1G0  B3B2B1B0  �ֱ���������R G B ����ɫ�㣬ÿ������4λ��ʾ����ÿ���������16���Ҷȣ�
                 //         ���ǲ�ɫ����16��R��x 16��G��X 16��B��= 4096 (4Kɫ)
                 //   �ر�ע��   �˴���������д�����ֽڲŶ�Ӧ��ʾ���ϵ�6���㣬��ƽ��д2���ֶ�Ӧ1����
                 //   �ر�ע��   д�Դ�һ�е��ֽ���һ����3�ı�������Ȼд��ȥ�����ݻ���ʾ��ȫ����һ������
                 //              ���ǵ���һ��1-160��160����3�ı�������Ҫд��һ����Ҫ������д162���պ�3�ı��������㼴81���ֽ�����
                 //              ͼƬȡĤʱһ��Ҫ��ͼƬ��С���ó�162��seg��X 160��com�� �мǲ�������160��seg��X 160��com�����������Ҳ���ʾ��ȫ������
	LCD_WriteCmd(0xC4); //  (18) SET LCD MAPPING CONTROL   ����LCD����IC RAM �Ķ�Ӧ��ϵ
                 //       ͨ���޸Ĵ�ָ�����ʵ����ʾ������������¾��� �����ı��Դ����ݣ���ʵ�������ǵ�SEG���Ҳ��Գơ�
}
 

/*
�������ƣ�uint8_t Fill_LcdRAM_1DOT(uint8_t Row,uint8_t Column,DOT)
�������ܣ�����RAMĳһ��������

Row:�к�0--X
Column:�к�0--Y
����ֵ:0 ���³ɹ� 1:�е�ַ���� 2:�е�ַ����
*/

uint8_t Fill_LcdRAM_1DOT(uint8_t Row,uint8_t Column,uint8_t DOT)
{
	uint8_t X_add =Row;		//�е�ַ
	uint8_t Y_add =Column;	//�е�ַ
	uint8_t ColumnNum =Column/2;//�ֽ�λ
	uint8_t ColumnCh =Column%2;	//�ߵ�λ
	uint8_t Databuf =0;
	
	if (X_add >=LCD_Row_NUM)		//�ж��е�ַ�Ƿ񳬱�
	{
		return 1;
	}
	if ( Y_add >=LCD_Column_NUM)	//�ж��е�ַ�Ƿ񳬱�
	{
		return 2;
	}
	Databuf =LCD_RAM.Scan_Value[Row][ColumnNum];
	if ( DOT ==0)
	{
		if ( ColumnCh ==0)//���ֽ�
		{
			Databuf &=0X0F;
		}
		else			  //���ֽ�
		{
			Databuf &=0XF0;
		}
	}
	else
	{
		if ( ColumnCh ==0)//���ֽ�
		{
			Databuf |=0XF0;
		}
		else			  //���ֽ�
		{
			Databuf |=0X0F;
		}		
	}
	LCD_RAM.Scan_Value[Row][ColumnNum] =Databuf;
	return 0;
}

/*
 �������ƣ�uint8_t Update_LcdRAM_Row(uint8_t Row,uint8_t DOT)
 �������ܣ���RAMĳһ����ڻ�������
*/

uint8_t Fill_LcdRAM_Row(uint8_t Row,uint8_t DOT)
{
	uint8_t ErrState =0;
	uint8_t YNum =0;
	
	for ( YNum =0;YNum<LCD_Column_NUM;YNum++)
	{
		ErrState =Fill_LcdRAM_1DOT(Row,YNum,DOT);
		if ( ErrState !=0)
		{
			return 1;
		}
	}
	return 0;
}

/*
 �������ƣ�uint8_t Update_LcdRAM_Column(uint8_t Column,uint8_t DOT)
 �������ܣ���RAMĳһ����ڻ�������
*/
uint8_t Fill_LcdRAM_Column(uint8_t Column,uint8_t DOT)
{
	uint8_t ErrState =0;
	uint8_t XNum =0;
	
	for ( XNum =0;XNum<LCD_Row_NUM;XNum++)
	{
		ErrState =Fill_LcdRAM_1DOT(XNum,Column,DOT);
		if ( ErrState !=0)
		{
			return 1;
		}
	}
	return 0;
}

/*
 �������ƣ�uint8_t Fill_LcdRAM_Region(uint8_t Row1,uint8_t Column1,uint8_t Row2,uint8_t Column2,uint8_t DOT)
 �������ܣ���RAMĳһ������ڻ�������
 Row1:��ʼX���� 
 Row2:��ֹX����
 Column1:��ʼY����
 Column2:��ֹY����
*/
uint8_t Fill_LcdRAM_Region(uint8_t Row1,uint8_t Column1,uint8_t Row2,uint8_t Column2,uint8_t DOT)
{
	uint8_t ErrState =0;
	uint8_t XNum =Row1;
	uint8_t YNum =Column1;
	
	if (( Row1>=LCD_Row_NUM)||(Row2>=LCD_Row_NUM)||( Column1>=LCD_Column_NUM)||( Column2>=LCD_Column_NUM))
	{
		return 1;
	}
	
	for ( XNum =Row1;XNum<=Row2;XNum++)
	{
		for ( YNum =Column1;YNum<=Column2;YNum++)
		{
			ErrState =Fill_LcdRAM_1DOT(XNum,YNum,DOT);
			if ( ErrState !=0)
			{
				return 1;
			}
		}
		
	}
	return 0;
}

/*
 �������ƣ�uint8_t Fill_LcdRAM_Region(uint8_t Row1,uint8_t Column1,uint8_t Row2,uint8_t Column2,uint8_t DOT)
 �������ܣ���RAMĳһ������ڻ�������
 Row1:��ʼX���� 
 Column1:��ʼY����
 opposite_X:ƫ��X����
 opposite_Y:ƫ��Y����
 DOT: 1���  0����
*/
uint8_t Fill_LcdRAM_Region_Opposite(uint8_t Row1,uint8_t Column1,uint8_t opposite_X,uint8_t opposite_Y,uint8_t DOT)
{
	uint8_t ErrState =0;
	uint8_t RowEnd =Row1+opposite_X;
	uint8_t ColumnEnd =Column1+opposite_Y;
	ErrState =Fill_LcdRAM_Region(Row1,Column1,RowEnd,ColumnEnd,DOT);
	return ErrState;
}

/*
 �������ƣ�uint8_t Fill_LcdRAM_Region_ALL(uint8_t DOT)
 �������ܣ���RAMȫ��������ڻ�������
 DOT: 1���  0����
*/

uint8_t Fill_LcdRAM_Region_ALL(uint8_t DOT)
{
	uint8_t ErrState =0;
	uint8_t RowEnd =LCD_Row_NUM -1;
	uint8_t ColumnEnd =LCD_Column_NUM -1;
	ErrState =Fill_LcdRAM_Region(0,0,RowEnd,ColumnEnd,DOT);
	return ErrState;
}


/*
 �������ƣ�Update_LcdRAM_ALL(void)
 �������ܣ�ˢ�� LCDRAM��ʾ��
*/
void Update_LcdRAM_ALL(void)
{

	uint32_t i=0;

		            // ����(0x25)�Դ����ߵ�ַָ�뿪ʼλ�ã��Դ����ߵ�ַ����ʾ�������ߵ�ַ��Ӧ������д���Ϊ'-'����ֱ��д���Ϊ'+'����
	LCD_WriteCmd(0x05);	//  set column adress LSB CA3 CA2 CA1 CA0  =05  //05
	LCD_WriteCmd(0x12); //  set column adress MSB CA6 CA5 =02          // 12
						// ����(0x00)�Դ���ߵ�ַָ�뿪ʼλ�ã��Դ���ߵ�ַ����ʾ���ĺ��ߵ�ַ��Ӧ������д���Ϊ'-'����ֱ��д���Ϊ'+'����
	LCD_WriteCmd(0X60); //  set ROW adress LSB RA3 RA2 RA1 RA0  =00//60
	LCD_WriteCmd(0x70); //  set ROW adress MSB RA7 RA6 RA5 RA4  =00//70


	for ( i =0;i<LCD_Row_NUM*LCD_Column_Byte;i++)
	{
	
		LCD_WriteOneByte(LCD_RAM.data_S[i]);   //a byte per a pixel   дһ���ֽ�����
		
	}

}


/*
 �������ƣ�Update_LcdRAM_Row(void)
 �������ܣ�ˢ�� LCDRAM��ʾ��(��ʾĳЩ��)
 ע�����StartRowΪ����ˢ����ʼ����
				 RowsΪҪ����ˢ�µ�����
*/
void Update_LcdRAM_Row(uint8_t StartRow,uint8_t Rows)
{

	 uint32_t i=0;
		            // ����(0x25)�Դ����ߵ�ַָ�뿪ʼλ�ã��Դ����ߵ�ַ����ʾ�������ߵ�ַ��Ӧ������д���Ϊ'-'����ֱ��д���Ϊ'+'����
	LCD_WriteCmd(0x05);	//  set column adress LSB CA3 CA2 CA1 CA0  =05
	LCD_WriteCmd(0x12); //  set column adress MSB CA6 CA5 =02
						// ����(0x00)�Դ���ߵ�ַָ�뿪ʼλ�ã��Դ���ߵ�ַ����ʾ���ĺ��ߵ�ַ��Ӧ������д���Ϊ'-'����ֱ��д���Ϊ'+'����
	LCD_WriteCmd(0x60|(StartRow&0x0f)); //  set ROW adress LSB RA3 RA2 RA1 RA0  =00      ����y��ַ
    LCD_WriteCmd(0x70|(StartRow>>4));   //  set ROW adress MSB RA7 RA6 RA5 RA4  =00
	for ( i =StartRow*LCD_Column_Byte;i<(StartRow+Rows)*LCD_Column_Byte;i++)
	{
		LCD_WriteOneByte(LCD_RAM.data_S[i]);   //a byte per a pixel   дһ���ֽ�����

	}
}


/*
 ��������:FindZMStation(uint16_t Code)
 ��������:�ں��ֿ��������Ӧ���ֵ�λ�ò�ͨ������ֵ�ݽ���ģ��λ
*/

INT16U FindZMStation(uint16_t Code)
{
  uint16_t Counter;
  for(Counter=0;;Counter++)
    {
      uint16_t tmp = ZKIndex[Counter++] << 8;
      tmp += ZKIndex[Counter];
      if( tmp==0xFFFF)
        {
          return 0;
        }
      else
        {
          if( tmp==Code)
            {
              return Counter/2;
            }
        }
    }
};


void DispArray(uint16_t XAdd,uint16_t YAdd,uint16_t Width,uint16_t Hight,uint8_t DispMode,const unsigned char *Array)
{
	uint8_t	DataBuff =0;
	uint8_t DeelData =0;
	uint16_t XCount =0;
	uint16_t YCount =0;
	uint16_t ArrayWidth =0;
	if((XAdd+Width)>LCD_Width)
    {
		return;
    }
	if(YAdd>LCD_Hight)
    {
		return;
    }
	ArrayWidth=((Width%8)>0)?((Width/8)+1):(Width/8);	//����ַ������ռ�ֽ�����

	if(DispMode==0)/*������ʾ  �׵׺���*/
    {
		for(YCount=0;YCount<Hight;YCount++)
        {
			for(XCount=0;XCount<Width;XCount++)
            {
				DeelData=*(Array+(XCount/8)+YCount*ArrayWidth);	//�������������ģ�ĵ��ֽ�λ��
				DataBuff = VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8];	//ȡ������������ʾ��������Ӧ���ֽ�
				
				if ((DeelData&BitTab[XCount%8])==0)
				{
					VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8]= DataBuff&(~(BitTab[((XAdd+XCount)%8)]));
				}
				else
                {
					VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8] = DataBuff|(BitTab[((XAdd+XCount)%8)]);
                }
            }
        }
    }
	
	else	/*������ʾ  �ڵװ���*/
	{
		for(YCount=0;YCount<Hight;YCount++)
        {
			for(XCount=0;XCount<Width;XCount++)
            {
				DeelData=*(Array+(XCount/8)+YCount*ArrayWidth);	//�������������ģ�ĵ��ֽ�λ��
				DataBuff = VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8];	//ȡ������������ʾ��������Ӧ���ֽ�
				
				if ((DeelData&BitTab[XCount%8])==0)
                {
					VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8] = DataBuff|(BitTab[((XAdd+XCount)%8)]);

                }
				else
                {
					VisionBuf[YAdd+YCount].ColBuf[(XAdd+XCount)/8]= DataBuff&(~(BitTab[((XAdd+XCount)%8)]));
                }
            }
        }
    }
};


/*

��������:�ַ������ò���ʾAPI�ӿڣ�ͨ���ýӿڿ�������Ļָ��λ����ʾһ���ַ����ߺ���
�������  Xadd�����꣨��>�ң�;Yadd�����꣨�ϡ�>�£�;Lettersp �ַ����ĵ�ַ ;Mode ��ʾģʽ 0�׵׺��� 1�ڵװ���;  FontType:�����С  �˺���Ŀǰ��֧������ 9 10 11 12����
*/
void DispStringM(uint16_t Xadd,uint16_t Yadd,  const char*   Lettersp,uint8_t Mode,uint8_t FontType)   //�����ѡ�񼰺ڵװ��ֻ�׵׺��ֵ�ѡ��
{
    uint8_t number;	//ASCII�������
    uint16_t CurryX;//��ǰ������
    uint16_t  Temp1;//��ģ��ַ
	uint8_t *Letters;//��ģ��ַ
    CurryX=Xadd;
    Letters = (uint8_t *)Lettersp;
    for(number=0;*(Letters+number)!='\0';)
    {
        if(Letters[number]<128)  //�ַ�
        {
            if (FontType==9) 	 //����9��
            {
                DispArray(CurryX,Yadd,6,12,Mode,ASCII12[Letters[number]-0x20]);
                CurryX=CurryX+6;
            }
            else if(FontType==10) //����10��
            {
                DispArray(CurryX,Yadd,7,13,Mode,ASCII13[Letters[number]-0x20]);
                CurryX=CurryX+7;
            }
            else if(FontType==11) //����11��
            {
                DispArray(CurryX,Yadd,8,15,Mode,ASCII15[Letters[number]-0x20]);
                CurryX=CurryX+8;
            }
            else if(FontType==12) //����12��
            {
                DispArray(CurryX,Yadd,8,16,Mode,ASCII16[Letters[number]-0x20]);
                CurryX=CurryX+8;
            }
            number++;
        }
        else //����
        {
            Temp1=FindZMStation(( Letters[number] << 8 )+ Letters[number+1] );
            if(Temp1!=0xFFFF)
            {
                if (FontType==9) //����9��
                {
                    DispArray(CurryX,Yadd,12,12,Mode,Zkarry12[Temp1]);
                }
                else if (FontType==10)//����10��
                {
                    DispArray(CurryX,Yadd,13,13,Mode,Zkarry13[Temp1]);
                }
                else if (FontType==11)//����11��
                {
                    DispArray(CurryX,Yadd,15,15,Mode,Zkarry15[Temp1]);
                }
                else if (FontType==12)//����12��
                {
                    DispArray(CurryX,Yadd,16,16,Mode,Zkarry16[Temp1]);
                }
            }
            if (FontType==9)//����9��
            {
                CurryX=CurryX+12;
            }
            else if (FontType==10)//����10��
            {
                CurryX=CurryX+13;
            }
            else if (FontType==11)//����11��
            {
                CurryX=CurryX+15;
            }
            else if (FontType==12)//����12��
            {
                CurryX=CurryX+16;
            }			
            number+=2;
        }
    }
};


/*
 �������ƣ�void Update_VisionBuf_TO_LcdRAM(void) 
 �������ܣ��Ӿ���������LCD_RAM�������ľ����Ӻ�
 ����������ͨ���Ӿ�������ÿ�е�ÿ�������ֽڶ�ӦLCD_RAM���������ĸ��ֽ�

 ע�������ΪС��ģʽ!!!!!!!

*/

void Update_VisionBuf_TO_LcdRAM(void) 
{	
	uint8_t VisBuf =0;	//��ʾ��������ǰ�ֽ�
	uint32_t LcdBuf =0;	//LCD��������ǰ�ֽ�
	uint8_t CUX =0;		//�������ֽ�
	uint8_t CUY =0;		//����������

	for ( CUY =0;CUY<LCD_Hight;CUY++)		//��ɨ��
	{
		for (CUX =0;CUX<20;CUX++)			//���ֽ�ɨ��
		{
			VisBuf =VisionBuf[CUY].ColBuf[CUX];	//��ȡ��ǰ���ֽ�
			
			LcdBuf =LCD_RAM.group[CUY].Word[CUX];//ԭ���ݶ�ȡ
			
			if ( (VisBuf&0X80) ==0)	//������һλ,ʵ��Ϊ�͵�1�ֽڸ�><2
			{
				LcdBuf &=0XFFFFFF0F;
			}
			else
			{
				LcdBuf |=0X000000F0;
			}
			
			if ( (VisBuf&0X40) ==0)//�����ڶ�λ,ʵ��Ϊ�͵�1�ֽڵ�><1
			{
				LcdBuf &=0XFFFFFFF0;
			}
			else
			{
				LcdBuf |=0X0000000F;
			}
			
			
			if ( (VisBuf&0X20) ==0)//��������λ,ʵ��Ϊ�͵�2�ֽڸ�><4
			{
				LcdBuf &=0XFFFF0FFF;
			}
			else
			{
				LcdBuf |=0X0000F000;
			}
			
			if ( (VisBuf&0X10) ==0)//��������λ,ʵ��Ϊ�͵�2�ֽڵ�><3
			{
				LcdBuf &=0XFFFFF0FF;
			}
			else
			{
				LcdBuf |=0X0000F00;
			}
	
			if ( (VisBuf&0X08) ==0)//��������λ,ʵ��Ϊ�͵�3�ֽڸ�><6
			{
				LcdBuf &=0XFF0FFFFF;
			}
			else
			{
				LcdBuf |=0X00F00000;
			}
			
			if ( (VisBuf&0X04) ==0)//��������λ,ʵ��Ϊ�͵�3�ֽڵ�><5
			{
				LcdBuf &=0XFFF0FFFF;
			}
			else
			{
				LcdBuf |=0X000F0000;
			}
			
			if ( (VisBuf&0X02) ==0)//��������λ,ʵ��Ϊ�͵�4�ֽڸ�><8
			{
				LcdBuf &=0X0FFFFFFF;
			}
			else
			{
				LcdBuf |=0XF0000000;
			}
			
			if ( (VisBuf&0X01) ==0)//�����ڰ�λ,ʵ��Ϊ�͵�4�ֽڵ�><7
			{
				LcdBuf &=0XF0FFFFFF;
			}
			else
			{
				LcdBuf |=0X0F000000;
			}
			LCD_RAM.group[CUY].Word[CUX] =LcdBuf;	//��������ݻش�
			
		}
	}
	
}


/* �������ƣ�Clear_VisionBUF()
 * �������ܣ������ʾ������
 * �������������ڶ�ʱˢ����ʾ��������ʹ�ô˺�������ʾ����������
 */
void Clear_VisionBUF(void)
{
  	INT16U x =0;
	INT16U y =0;
	for ( y=0;y<LCD_Row_NUM;y++)
	 {
		 for ( x=0;x<LCD_Column_Word;x++)
		 {
			 VisionBuf[y].ColBuf[x]=0X00;
		}
    }
    
}



/* 
//�� �� ��: GUI_Point() 
//�� �ܣ�	��ָ��λ���ϻ���
//��ڲ�����  X		ָ�������ں������λ��
//            Y		ָ���������������λ��
//            color	��ʾ��ɫ(Ϊ0ʱ��Ϊ1ʱ��ʾ)
//���ڲ����� ��
//�� �� ֵ�� ����ֵΪ0ʱ��ʾ�����ɹ�
			  ����ֵΪ1ʱ��ʾ�����곬��
			  ����ֵΪ0ʱ��ʾ�����곬��

*/
INT8U  GUI_Point(INT8U X, INT8U Y, INT8U Color)
{ 
	INT8U ErrFlg =0;
	INT8U X_add =X;		//�е�ַ
	INT8U Y_add =Y;		//�е�ַ
	INT8U Databuf =X_add/8;
	INT8U DatabufDot =X_add%8;
	if (X_add >=LCD_Width)	//�ж��е�ַ�Ƿ񳬱�
	{
		ErrFlg =1;
		return ErrFlg;
	}
	if ( Y_add >=LCD_Hight)	//�ж��е�ַ�Ƿ񳬱�
	{
		ErrFlg =2;
		return ErrFlg;
	}
	
    	// ���û�������Ӧ�ĵ�
	if (Color )    
	{
		VisionBuf[Y_add].ColBuf[Databuf]|=BitTab[DatabufDot];
	}
	else
	{
		VisionBuf[Y_add].ColBuf[Databuf]&=(~BitTab[DatabufDot]);
	}
	return ErrFlg;
    
}


 //============================================================================= 
//�� �� ��: GUI_Line() 
//�� ��:    �����ӳ���:Ϊ�˻رܸ��ӵĸ�������,��������������΢�ֵķ���
//			��(x��,y��)Ϊ���,��(x1��,y1��)Ϊ�յ㻭һ��ֱ��
//��ڲ���: x,y	��ʼ����	x1,y1�յ�����	color:0-1 0:���� 1:����
//	 ��������������������
//	 �� x,y ------->x1 ��
//	 ��	|�v			   ��
//   �� |  �v		   ��	
//	 ��	|	 �v		   ��
//	 ��	y1	  x1,y1	   ��
//	 ��������������������
//		   zuo
//���ڲ���: �� 
//�� �� ֵ: ��
//============================================================================= 

INT8U GUI_Line( int16_t x, int16_t y, int16_t x1, int16_t y1, uint8_t color) 
{ 
	INT8U ErrFlg =0;
	int16_t dx,dy,err = 0;
	if (x1 >=LCD_Width)	//�ж��е�ַ�Ƿ񳬱�
	{
		ErrFlg =1;
		return ErrFlg;
	}
	if ( y1 >=LCD_Hight)	//�ж��е�ַ�Ƿ񳬱�
	{
		ErrFlg =2;
		return ErrFlg;
	}

	if(y != y1)
	{
		if(y1 < y) /*����ж���䱣֤��y1>=y���ǰ��*/
		{
			dx = y1; dy = x1;
			y1 = y;  x1 = x;
			y = dx;  x = dy;
		}
		dy = y1 - y;
		dx = x1 - x;
		GUI_Point(x ,y,color);
		
		if((x1 >= x)&&((y1 - y) <= (x1 - x)))
		{
			for(;x != x1;)
			{
				if(err < 0)
				{
					GUI_Point(x + 1,y,color);
					x += 1;
					err += dy;
				}
				else
				{
					GUI_Point(x + 1,y + 1,color);
					x += 1;
					y += 1;
					err += (dy - dx);
				}
			}
		}
		else
			if((x1 >= x)&&((y1 - y) > (x1 - x)))
			{
				for(;y != y1;)
				{
					if(err < 0)
					{
						GUI_Point(x + 1,y + 1,color);
						x += 1;
						y += 1;
						err += (dy - dx);
					}
					else
					{
						GUI_Point(x,y + 1,color);
						y += 1;
						err -= dx;
					}
				}
			}
			else
				if((x1 < x)&&((y1 - y) <= (x - x1)))
				{
					for(;x != x1;)
					{
						if(err < 0)
						{
							GUI_Point(x - 1,y,color);
							x -= 1;
							err += dy;
						}
						else
						{
							GUI_Point(x - 1,y + 1,color);
							x -= 1;
							y += 1;
							err += (dy + dx);
						}
					}
				}
				else
					if((x1 < x)&&((y1 - y) > (x1 - x)))
					{
						for(;y != y1;)
						{
							if(err < 0)
							{
								GUI_Point(x - 1,y + 1,color);
								x -= 1;
								y += 1;
								err += (dy + dx);
							}
							else
							{
								GUI_Point(x,y + 1,color);
								y += 1;
								err += dx;
							}
						}
					}
	}	
	else
	{
		dx = x; dy = x1;
		if(x < x1)
		{
			dx = x1;
			dy = x;
		}
		for(;dy < dx;dy++)
			GUI_Point(dy,y,color);

			GUI_Point(x1 ,y1,color);
	}
	return ErrFlg;
}
 //============================================================================= 
//�� �� ��: GUI_Circle() 
//�� ��:    ָ��Բ��λ�ü��뾶����Բ
//��ڲ���: x0		Բ�ĵ�x����ֵ
//          y0		Բ�ĵ�y����ֵ
//          r       Բ�İ뾶
//          color	��ʾ��ɫ
//���ڲ���: �� 
//�� �� ֵ: ��
//============================================================================= 
void  GUI_Circle(uint32_t x0, uint32_t y0, uint32_t r, uint8_t color)
{ 
	int32_t  draw_x0, draw_y0;			// ��ͼ���������
	int32_t  draw_x1, draw_y1;	
	int32_t  draw_x2, draw_y2;	
	int32_t  draw_x3, draw_y3;	
	int32_t  draw_x4, draw_y4;	
	int32_t  draw_x5, draw_y5;	
	int32_t  draw_x6, draw_y6;	
	int32_t  draw_x7, draw_y7;	
	int32_t  xx, yy;					// ��Բ���Ʊ���
 
	int32_t  di;						// ���߱���
   
	/* �������� */
	if(0==r) return;

	/* �����8�������(0��45��90��135��180��225��270��)��������ʾ */
	draw_x0 = draw_x1 = x0;
	draw_y0 = draw_y1 = y0 + r;
	if(draw_y0<LCD_Hight) GUI_Point(draw_x0, draw_y0, color);	// 90��

	draw_x2 = draw_x3 = x0;
	draw_y2 = draw_y3 = y0 - r;
	if(draw_y2>=0) GUI_Point(draw_x2, draw_y2, color);			// 270��
   
	
	draw_x4 = draw_x6 = x0 + r;
	draw_y4 = draw_y6 = y0;
	if(draw_x4<LCD_Width) GUI_Point(draw_x4, draw_y4, color);	// 0��

	draw_x5 = draw_x7 = x0 - r;
	draw_y5 = draw_y7 = y0;
	if(draw_x5>=0) GUI_Point(draw_x5, draw_y5, color);			// 180��   
	if(1==r) return;					// ���뾶Ϊ1������Բ����
   
   
	/* ʹ��Bresenham�����л�Բ */
	di = 3 - 2*r;					// ��ʼ�����߱���

	xx = 0;
	yy = r;	
	while(xx<yy)
	{  
		if(di<0)
		{  
			di += 4*xx + 6;	      
		}
		else
		{ 
			di += 4*(xx - yy) + 10;
			yy--;	  
			draw_y0--;
			draw_y1--;
			draw_y2++;
			draw_y3++;
			draw_x4--;
			draw_x5++;
			draw_x6--;
			draw_x7++;	 	
		}
		xx++;   
		draw_x0++;
		draw_x1--;
		draw_x2++;
		draw_x3--;
		draw_y4++;
		draw_y5++;
		draw_y6--;
		draw_y7--;
		/* Ҫ�жϵ�ǰ���Ƿ�����Ч��Χ�� */
		if( (draw_x0<=LCD_Width)&&(draw_y0>=0) )	
		{  
			GUI_Point(draw_x0, draw_y0, color);
		}	    
		if( (draw_x1>=0)&&(draw_y1>=0) )	
		{ 
			GUI_Point(draw_x1, draw_y1, color);
		}
		if( (draw_x2<=LCD_Width)&&(draw_y2<=LCD_Hight) )	
		{  
			 GUI_Point(draw_x2, draw_y2, color);   
		}
		if( (draw_x3>=0)&&(draw_y3<=LCD_Hight) )	
		{ 
			 GUI_Point(draw_x3, draw_y3, color);
		}
		if( (draw_x4<=LCD_Width)&&(draw_y4>=0) )	
		{ 
			GUI_Point(draw_x4, draw_y4, color);
		}
		if( (draw_x5>=0)&&(draw_y5>=0) )	
		{  
			GUI_Point(draw_x5, draw_y5, color);
		}
		if( (draw_x6<=LCD_Width)&&(draw_y6<=LCD_Hight) )	
		{ 
			GUI_Point(draw_x6, draw_y6, color);
		}
		if( (draw_x7>=0)&&(draw_y7<=LCD_Hight) )	
		{  
			GUI_Point(draw_x7, draw_y7, color);
		}
   }
}


/*
��������:GUI_Rectangle(INT16U Xs, INT16U Ys,INT16U Xf, INT16U Yf,INT8U Color)
//��ڲ���: x,y	��ʼ����	x1,y1�յ�����	color:0-1 0:���� 1:����
//	 ��������������������
//	 �� Xs,Ys ------->Xf  ��
//	 ��	|�v			         ��
//    ��  |    �v	                 |	
//	 ��	|	   �v		         ��
//	 ��	Yf	  Xf,Yf	         ��
//	 ��������������������
*/
INT8U GUI_Rectangle(INT16U Xs, INT16U Ys,INT16U Xf, INT16U Yf,INT8U Color)
{
	INT8U ErrFlg =0;
	if (Xf >=LCD_Width)	//�ж��е�ַ�Ƿ񳬱�
	{
		ErrFlg =1;
		return ErrFlg;
	}
	if ( Yf >=LCD_Hight)	//�ж��е�ַ�Ƿ񳬱�
	{
		ErrFlg =2;
		return ErrFlg;
	}
	GUI_Line(Xs,Ys ,Xf, Ys, Color);
	GUI_Line(Xs,Ys ,Xs, Yf, Color);
	GUI_Line(Xs, Yf,Xf,Yf , Color);
	GUI_Line(Xf, Ys,Xf,Yf , Color);

	return ErrFlg;
}

/*
��������:INT8U GUI_Rectangle_Dev(INT16U Xs, INT16U Ys,INT16U Xf, INT16U Yf,INT8U Color)

��������:��һ������ƫ�Ƶľ���   
//��ڲ���: x,y	��ʼ����	x1,y1�յ�����	color:0-1 0:���� 1:����  DevNum ƫ����
//	 ��������������������
//	 �� Xs,Ys ------->Xf  ��
//	 ��	|�v			         ��
//    ��  |    �v	                 |	
//	 ��	|	   �v		         ��
//	 ��	Yf	  Xf,Yf	         ��
//	 ��������������������
*/
INT8U GUI_Rectangle_Dev(INT16U Xs, INT16U Ys,INT16U Xf, INT16U Yf, INT16U DevNum,INT8U Color)
{
	INT8U ErrFlg =0;
	
	if (Xf >=LCD_Width)	//�ж��е�ַ�Ƿ񳬱�
	{
		ErrFlg =1;
		return ErrFlg;
	}
	if ( Yf >=LCD_Hight)	//�ж��е�ַ�Ƿ񳬱�
	{
		ErrFlg =2;
		return ErrFlg;
	}
	if( (Xf-Xs )<=2*DevNum)
	{
		ErrFlg =1;
		return ErrFlg;	
	}
	if( (Yf-Ys )<=2*DevNum)
	{
		ErrFlg =2;
		return ErrFlg;	
	}
	
	GUI_Line(Xs,Ys ,Xf, Ys, Color);
	GUI_Line(Xs+DevNum,Ys+DevNum ,Xf-DevNum, Ys+DevNum, Color);
	
	GUI_Line(Xs,Ys ,Xs, Yf, Color);
	GUI_Line(Xs+DevNum,Ys+DevNum ,Xs+DevNum, Yf-DevNum, Color);

	GUI_Line(Xs, Yf,Xf,Yf , Color);
	GUI_Line(Xs+DevNum, Yf-DevNum,Xf-DevNum,Yf-DevNum , Color);

	GUI_Line(Xf, Ys,Xf,Yf , Color);
	GUI_Line(Xf-DevNum, Ys+DevNum,Xf-DevNum,Yf-DevNum , Color);
	return ErrFlg;
}





/* �������ƣ�INT8U Fill_VisionBUF(INT8U X1,INT8U Y1,INT8U X2,INT8U Y2,INT8U Data)
 * �������ܣ�����Ӿ�������
 */
INT8U Fill_VisionBUF(INT8U X1,INT8U Y1,INT8U X2,INT8U Y2,INT8U Data)
{
  	INT16U x =0;
	INT16U y =0;
	INT8U ErrFlg =0;
	if ((X2>=LCD_Width )||( Y2>=LCD_Hight))
	{
		ErrFlg=0XA0;
		return  ErrFlg;
	}
	for ( y=Y1;y<Y2;y++)
	 {
		 for ( x=X1;x<X2;x++)
		 {
			 GUI_Point(x, y, Data);
		}
	}
	return  ErrFlg;
    
}




/*
��������:Refresh_Screen
��������:������Ļ
��������: �ú���Ӧ������Ϊ����ˢ����Ļ������,��һ���ǰ���ʾ�����������ݵ���LCD�����ݻ����� RAM �ڶ��������ݻ����������ݰ���ʱ��ˢ��Һ����
ע������:�ú���ֻ�Ƕ���ʾ�����ݽ���ת������������������ʾ����������ǰ����

*/
void Refresh_Screen(void)
{
	Update_VisionBuf_TO_LcdRAM();
	Update_LcdRAM_ALL();
}


/*
��������:Refresh_Screen_Row
��������:������Ļ(���и���)
��������: �ú���Ӧ������Ϊ����ˢ����Ļ������,��һ���ǰ���ʾ�����������ݵ���LCD�����ݻ����� RAM �ڶ��������ݻ����������ݰ���ʱ��ˢ��Һ����
ע������:�ú���ֻ�Ƕ���ʾ�����ݽ���ת������������������ʾ����������ǰ����
				StartRowΪ����ˢ����ʼ����
				RowsΪҪ����ˢ�µ�����

*/

void Refresh_Screen_Row(uint8_t StartRow,uint8_t Rows)
{
	Update_VisionBuf_TO_LcdRAM();
	Update_LcdRAM_Row(StartRow,Rows);
}





/*
��������:Disp_Integer
��������:����������ת��Ϊ�ַ���
ע������:DataΪҪת��������
*/
char* Disp_Integer(int Data)
{

	static char CH[32];
	sprintf(CH, "%d", Data); 
	return CH;
}






/*
��������:Disp_Float
��������:����������ת��Ϊ�ַ���
ע������:DataΪҪת��������
			   BΪҪ������С��λ��
*/
char* Disp_Float(float Data,int B)
{

	static char CH[32];
	sprintf(CH, "%.*f",B,Data); 
     
	return CH;
}


/*
��������:Disp_Float_Point
��������:����������ת��Ϊ��������(����С����)���ַ���
ע������:DataΪҪת��������
			   BΪҪ������С��λ��
			   CΪ�������ݵ��ܳ���
*/
char* Disp_Float_Point(INT32U Data,int B,float C)
{
	int i;
	static char TIME[20];
	int D=(int)pow(10,(C-1));
	
	TIME[0] ='0'+(Data/D);
	for(i=1;i<=C;i++)
	{
		if(i<C-B)
		{
			TIME[i] ='0'+(Data%((int)pow(10,(C-i)))/((int)pow(10,(C-i-1))));
		}
		else if(i==C-B)
		{
			TIME[i] ='.';
		}
		else if(i==C)
		{
			TIME[i] ='0'+(Data%10);
		}
		else
		{
			TIME[i] ='0'+(Data%((int)pow(10,(C-i+1)))/((int)pow(10,(C-i-1+1))));
		}
	}
	
	return TIME;
}

/*

//���ļ����б�ϲ�Ϊһ���ַ������磺����[a,bbb,ccc]->�ַ���"a,bbb,cc" author:wangchangshuai jlu  
char* combineFileNames(const char** fileNameList, const int count)  
{  
    if (count <= 0)  
    {  
        return NULL;  
    }  
    int i, length = 0;  
    for (i = 0; i < count; ++i)  
    {  
        length += strlen(fileNameList[i]);  
    }  
//���϶��ŵĸ���  
    length += count - 1;  
  
    char* fileNamesStr = NULL;  
    if ((fileNamesStr = (char*) myMalloc(sizeof(char) * (length + 1))) == NULL)  
    {  
        myLog("Malloc heap failed!\n");  
        return NULL;  
    }  
    memset(fileNamesStr, 0, sizeof(char) * (length + 1));  
    strcpy(fileNamesStr, fileNameList[0]);  
    for (i = 1; i < count; ++i)  
    {  
        strcat(fileNamesStr, ",");  
        strcat(fileNamesStr, fileNameList[i]);  
    }  
    return fileNamesStr;  
} 

*/



 /*
��������:Disp_BCD_32
��������:��INT32U��������ת��ΪBCD����ַ���
ע������:inputΪҪת��������
			   
*/
char* Disp_BCD_32(INT32U input)
{	
	int a=(input/16/16/16/16/16/16/16)*10000000+(input/16/16/16/16/16/16%16)*1000000+(input/16/16/16/16/16%16)*100000+(input/16/16/16/16%16)*10000+(input/16/16/16%16)*1000+((input/16/16)%16)*100+(input/16%16)*10 + input%16;
	static char ch4[20];

	sprintf(ch4, "%d", a);
	
	return ch4;
}
 /*
��������:Disp_BCD_16
��������:��INT16U��������ת��ΪBCD����ַ���
ע������:inputΪҪת��������
			   
*/
char* Disp_BCD_16(INT16U input)
{	
	int a=(input/16/16/16)*1000+((input/16/16)%16)*100+(input/16%16)*10 + input%16;
	static char ch4[20];

	sprintf(ch4, "%d", a);
	
	return ch4;
}
 /*
��������:Disp_BCD_8
��������:��INT8U��������ת��ΪBCD����ַ���
ע������:inputΪҪת��������
			   
*/
char* Disp_BCD_8(INT8U input)
{	
	int a=(input/16)*10 + input%16;
	static char ch4[20];
	sprintf(ch4, "%d", a);
	
	return ch4;
}

/*
��������:Disp_32_Binary
��������:��INT32U��������ת��Ϊ16���Ƶ��ַ���
ע������:DataΪҪת��������
			   BΪҪ������λ��
			   CΪ�Ƿ�0��C=1����0��C=0��0
			   DΪ���뷽ʽ��D=1����룬D=0�Ҷ���
*/
char* Disp_32_Binary(INT32U Data,int B,int C,int D)
{
	static char ch1[20];
	if(C==0)
	{
		if(D==1)
		{
			sprintf(ch1, "%-0*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%0*X",B,Data);
		}
	}
	else
	{
		if(D==1)
		{
			sprintf(ch1, "%-*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%*X",B,Data);
		}
	}
	return ch1;
}


/*
��������:Disp_16_Binary
��������:��INT16U��������ת��Ϊ16���Ƶ��ַ���
ע������:DataΪҪת��������
			   BΪҪ������λ��
			   CΪ�Ƿ�0��C=1����0��C=0��0
			   DΪ���뷽ʽ��D=1����룬D=0�Ҷ���
*/
char* Disp_16_Binary(INT16U Data,int B,int C,int D)
{
	static char ch1[20];
	if(C==0)
	{
		if(D==1)
		{
			sprintf(ch1, "%-0*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%0*X",B,Data);
		}
	}
	else
	{
		if(D==1)
		{
			sprintf(ch1, "%-*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%*X",B,Data);
		}
	}
	return ch1;
}


/*
��������:Disp_8_Binary
��������:��INT8U��������ת��Ϊ16���Ƶ��ַ���
ע������:DataΪҪת��������
			   BΪҪ������λ��
			   CΪ�Ƿ�0��C=1����0��C=0��0
			   DΪ���뷽ʽ��D=1����룬D=0�Ҷ���
*/
char* Disp_8_Binary(INT8U Data,int B,int C,int D)
{
	static char ch1[20];
	if(C==0)
	{
		if(D==1)
		{
			sprintf(ch1, "%-0*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%0*X",B,Data);
		}
	}
	else
	{
		if(D==1)
		{
			sprintf(ch1, "%-*X",B,Data);
		}
		else
		{
			sprintf(ch1, "%*X",B,Data);
		}
	}
	return ch1;
}








/*
��������:strcat(str1,str2)
��������:�������ַ����ϲ�Ϊһ���ַ���
ע������:str1Ϊ��һ���ַ���
			   str2Ϊ�ڶ����ַ���
			   strcat(str1,str2)���Ϊ�ϲ����ַ���(�ַ���str2λ���ַ���str1����)
			   ����:   
			   	char str1[] = {"2222"};
				char str2[] = {" China11111111111"};
				char A[]=strcat(str1,str2)={" 2222China11111111111"};
*/
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/





 

