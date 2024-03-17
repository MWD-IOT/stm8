/***************************************************************
* 深圳米客科技
* http://etrh.taobao.com
* 实验平台：STM8S开发板
* 库版本  ：V2.1.0
***************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "prohead.h"
/* Private defines -----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Global parameter ---------------------------------------------------------*/
volatile bool ExiFlag = False;

//PA4口中断初始化
void Driver_ExtIntOn(void)
{		
                //PA4 上拉输入,开启端口中断
                GPIO_Init(GPIOA,GPIO_PIN_4,GPIO_MODE_IN_PU_IT);
		//下降沿触发
                EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA, EXTI_SENSITIVITY_FALL_ONLY);
}

// LED GPIO Initial
void LED_GPIO_Init(void)
{   
      GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_OUT_PP_LOW_SLOW);//PD1，推挽输出
      GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_OUT_PP_LOW_SLOW);//PA1，推挽输出
      GPIO_Init(GPIOA,GPIO_PIN_2,GPIO_MODE_OUT_PP_LOW_SLOW);
}


//LED控制 输入1 点亮; 0 熄灭;
void Driver_LEDCont(bool flag)
{
		if(flag)
		{
                                GPIO_WriteLow(GPIOD,GPIO_PIN_1);//PD1输出低电平，点亮LED
                                GPIO_WriteLow(GPIOA,GPIO_PIN_1);
                                GPIO_WriteLow(GPIOA,GPIO_PIN_2);
                      
		}
		else
		{
                                GPIO_WriteHigh(GPIOD,GPIO_PIN_1);//PD1输出高电平，关闭LED灯
                                GPIO_WriteHigh(GPIOA,GPIO_PIN_1);
                                GPIO_WriteHigh(GPIOA,GPIO_PIN_2);

                                
		}
}


void main(void)
{      
		//程序启动STM8默认以HSI分频2M执行速率进行
                LED_GPIO_Init();
		Driver_LEDCont((bool)1);
		//开启外部中断
		Driver_ExtIntOn();
		//开总中断
                enableInterrupts(); 	/* 开启总中断 */
		//等待中断
		while(1)
		{
				static u16 Timer = 0; 
				if(ExiFlag)
				{
						Timer = 0xfff;
						ExiFlag = False;
				}
                                if(!GPIO_ReadInputPin(GPIOA,GPIO_PIN_4))
                                {
					        Timer = 0xfff;
                                }
				if(Timer)
				{
						if(!--Timer)
						{
								static bool flag = 0;
								//循环控制LED灯状态
								flag = !flag;
								Driver_LEDCont(flag);
						}
				}
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
