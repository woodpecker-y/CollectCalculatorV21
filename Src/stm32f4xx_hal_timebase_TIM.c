


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
* @date :2017/8/23 18:08
***************************************************************
*/ 

#define _STM32F4XX_HAL_TIMEBASE_TIM_C_
#include "stm32f4xx_hal_timebase_TIM.h"
 




/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function configures the TIM3 as a time base source. 
  *         The time source is configured  to have 1ms time base with a dedicated 
  *         Tick interrupt priority. 
  * @note   This function is called  automatically at the beginning of program after
  *         reset by HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig(). 
  * @param  TickPriority: Tick interrupt priorty.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  RCC_ClkInitTypeDef    		clkconfig;
  uint32_t              uwTimclock = 0;
  uint32_t              uwPrescalerValue = 0;
  uint32_t              pFLatency;
  
  /*Configure the TIM3 IRQ priority */
  HAL_NVIC_SetPriority(TIM3_IRQn, TickPriority ,0); 
  
  /* Enable the TIM3 global Interrupt */
  HAL_NVIC_EnableIRQ(TIM3_IRQn); 
  
  /* Enable TIM3 clock */
  __HAL_RCC_TIM3_CLK_ENABLE();
  
  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  
  /* Compute TIM3 clock */
  uwTimclock = 2*HAL_RCC_GetPCLK1Freq();
   
  /* Compute the prescaler value to have TIM3 counter clock equal to 1MHz */
  uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000) - 1);
  
  /* Initialize TIM3 */
  htim3.Instance = TIM3;
  
  /* Initialize TIMx peripheral as follow:
  + Period = [(TIM3CLK/1000) - 1]. to have a (1/1000) s time base.
  + Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
  + ClockDivision = 0
  + Counter direction = Up
  */
  htim3.Init.Period = (1000000 / 1000) - 1;
  htim3.Init.Prescaler = uwPrescalerValue;
  htim3.Init.ClockDivision = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  if(HAL_TIM_Base_Init(&htim3) == HAL_OK)
  {
    /* Start the TIM time Base generation in interrupt mode */
    return HAL_TIM_Base_Start_IT(&htim3);
  }
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling TIM3 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_SuspendTick(void)
{
  /* Disable TIM3 update Interrupt */
  __HAL_TIM_DISABLE_IT(&htim3, TIM_IT_UPDATE);                                                  
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling TIM3 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_ResumeTick(void)
{
  /* Enable TIM3 Update interrupt */
  __HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);
}




//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!(��ʱ��3����APB1�ϣ�ʱ��ΪHCLK/2)
void TIM3_Init(uint16_t arr,uint16_t psc)
{  
    htim3.Instance=TIM3;                       	//ͨ�ö�ʱ��3
    htim3.Init.Prescaler=psc;                     	//��Ƶϵ��
    htim3.Init.CounterMode=TIM_COUNTERMODE_UP;    	//���ϼ�����
    htim3.Init.Period=arr;                        	//�Զ�װ��ֵ
    htim3.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&htim3);
    
    HAL_TIM_Base_Start_IT(&htim3); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE   
}




//��ʼ��TIM3ʹ��ΪFreeRTOS��ʱ��ͳ���ṩʱ��
void ConfigureTimeForRunTimeStats(void)
{
	//��ʱ��3��ʼ������ʱ��ʱ��Ϊ90M����Ƶϵ��Ϊ90-1�����Զ�ʱ��3��Ƶ��
	//Ϊ90M/90=1M���Զ���װ��Ϊ50-1����ô��ʱ�����ھ���50us
	FreeRTOSRunTimeTicks=0;
	TIM3_Init(50-1,84-1);	//��ʼ��TIM3
}



void FreeRTOSRunTimeTicksUp()
{
	FreeRTOSRunTimeTicks++;
}




 
/* END */
/*
 @copy COPYRIGHT 2016 Foryon     
*/
