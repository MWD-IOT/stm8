/***************************************************************
* �����׿ͿƼ�
* http://etrh.taobao.com
* ʵ��ƽ̨��STM8S������
* ��汾  ��V2.1.0
***************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "prohead.h"
#include "uart.h"

/* Private defines -----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Global parameter ---------------------------------------------------------*/


//��ʱ����ʼ��
void Driver_Timer_Init()
{		
        //2Mʱ�� 2000��Ƶ,��������Ϊ1ms ,�趨�Զ����ؼĴ���ֵ1000,�ظ���������Ϊ0������ʱ1s            
        TIM1_TimeBaseInit(0x07D0, TIM1_COUNTERMODE_UP, 0x3E8, 0x0000);
        TIM1_SetCounter(0x0000);//���������ĳ�ʼֵ����Ϊ0
        TIM1_ClearFlag(TIM1_FLAG_UPDATE);
        TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
        TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);//�����������ж�
        TIM1_Cmd(ENABLE);//ʹ��TMI1
        
        //���벶��ģʽ
        //TIM2_TimeBaseInit( 0x07D0,0x03E8);
        TIM2_ICInit(TIM2_CHANNEL_1, TIM2_ICPOLARITY_RISING, TIM2_ICSELECTION_DIRECTTI, TIM2_ICPSC_DIV1, 0);
        TIM2_SetCounter(0x0000);//���������ĳ�ʼֵ����Ϊ0
        TIM2_ClearFlag(TIM2_FLAG_CC1);
        TIM2_ClearITPendingBit(TIM2_IT_CC1);
        TIM2_ITConfig(TIM2_IT_CC1, ENABLE);//����ͨ��1����/�Ƚ��ж�      
        TIM2_Cmd(ENABLE);//ʹ��TMI2

}

uint8_t main_flag;
uint32_t ICValue1 = 0;
uint32_t ICValue2 = 0;

void main(void)
{      
        Uart_Init();
        GPIO_Init(GPIOG,GPIO_PIN_2,GPIO_MODE_OUT_PP_LOW_SLOW);//PG2���������
        GPIO_Init(GPIOG,GPIO_PIN_3,GPIO_MODE_OUT_PP_LOW_SLOW);//PG3���������
        GPIO_Init(GPIOG,GPIO_PIN_4,GPIO_MODE_OUT_PP_LOW_SLOW);//PG4���������
        
        GPIO_WriteLow(GPIOG,GPIO_PIN_2);//PG2����͵�ƽ
//        GPIO_WriteLow(GPIOG,GPIO_PIN_3);//PG3����͵�ƽ
//        GPIO_WriteLow(GPIOG,GPIO_PIN_4);//PG4����͵�ƽ
		//��ʼ����ʱ��
		Driver_Timer_Init();
		//�����ж�
        enableInterrupts(); 	
        printf("Start up\r\n");
        
		while(1)
		{   
//            printf("ICValue1��%d\r\n");
//            printf("ICValue2��%d\r\n");
//          if(main_flag)
//          {
//            printf("main_falg:%d\n", main_flag);
//            GPIO_WriteReverse(GPIOG, GPIO_PIN_2);
//            main_flag = 0;
//          }
//          GPIO_WriteReverse(GPIOG,GPIO_PIN_3);//PG3����ߵ�ƽ
//          printf("Delayus();\r\n");
//          GPIO_WriteReverse(GPIOG,GPIO_PIN_3);//PG3����͵�ƽ         
		}
}
		



#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
