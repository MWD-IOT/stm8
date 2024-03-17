/***************************************************************
* 深圳米客科技
* http://etrh.taobao.com
* 实验平台：STM8S开发板
* 库版本  ：V2.1.0
***************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "prohead.h"
#include "uart.h"

/* Private defines -----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Global parameter ---------------------------------------------------------*/


//定时器初始化
void Driver_Timer_Init()
{		
        //2M时钟 2000分频,计数周期为1ms ,设定自动重载寄存器值1000,重复计数器设为0，即定时1s            
        TIM1_TimeBaseInit(0x07D0, TIM1_COUNTERMODE_UP, 0x3E8, 0x0000);
        TIM1_SetCounter(0x0000);//将计数器的初始值设置为0
        TIM1_ClearFlag(TIM1_FLAG_UPDATE);
        TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
        TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);//允许计数溢出中断
        TIM1_Cmd(ENABLE);//使能TMI1
        
        //输入捕获模式
        //TIM2_TimeBaseInit( 0x07D0,0x03E8);
        TIM2_ICInit(TIM2_CHANNEL_1, TIM2_ICPOLARITY_RISING, TIM2_ICSELECTION_DIRECTTI, TIM2_ICPSC_DIV1, 0);
        TIM2_SetCounter(0x0000);//将计数器的初始值设置为0
        TIM2_ClearFlag(TIM2_FLAG_CC1);
        TIM2_ClearITPendingBit(TIM2_IT_CC1);
        TIM2_ITConfig(TIM2_IT_CC1, ENABLE);//允许通道1捕获/比较中断      
        TIM2_Cmd(ENABLE);//使能TMI2

}

uint8_t main_flag;
uint32_t ICValue1 = 0;
uint32_t ICValue2 = 0;

void main(void)
{      
        Uart_Init();
        GPIO_Init(GPIOG,GPIO_PIN_2,GPIO_MODE_OUT_PP_LOW_SLOW);//PG2，推挽输出
        GPIO_Init(GPIOG,GPIO_PIN_3,GPIO_MODE_OUT_PP_LOW_SLOW);//PG3，推挽输出
        GPIO_Init(GPIOG,GPIO_PIN_4,GPIO_MODE_OUT_PP_LOW_SLOW);//PG4，推挽输出
        
        GPIO_WriteLow(GPIOG,GPIO_PIN_2);//PG2输出低电平
//        GPIO_WriteLow(GPIOG,GPIO_PIN_3);//PG3输出低电平
//        GPIO_WriteLow(GPIOG,GPIO_PIN_4);//PG4输出低电平
		//初始化定时器
		Driver_Timer_Init();
		//开总中断
        enableInterrupts(); 	
        printf("Start up\r\n");
        
		while(1)
		{   
//            printf("ICValue1：%d\r\n");
//            printf("ICValue2：%d\r\n");
//          if(main_flag)
//          {
//            printf("main_falg:%d\n", main_flag);
//            GPIO_WriteReverse(GPIOG, GPIO_PIN_2);
//            main_flag = 0;
//          }
//          GPIO_WriteReverse(GPIOG,GPIO_PIN_3);//PG3输出高电平
//          printf("Delayus();\r\n");
//          GPIO_WriteReverse(GPIOG,GPIO_PIN_3);//PG3输出低电平         
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
