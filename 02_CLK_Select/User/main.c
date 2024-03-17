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

/* Private function prototypes -----------------------------------------------*/
void LED_GPIO_Init(void);
void DIS_Delayms(u16 Num);
/* Private functions ---------------------------------------------------------*/

#define LED_ON    GPIO_WriteLow(GPIOD,GPIO_PIN_1)//PD1输出低电平，点亮LED
#define LED_OFF   GPIO_WriteHigh(GPIOD,GPIO_PIN_1)//PD1输出高电平，熄灭LED

void main(void)
{
  
		//STM8S 默认启动晶振为内部16MHZ 晶振HSI 
		//这里我们切换到外部时钟
		//禁用时钟切换中断_SWIEN清零
                ErrorStatus clk_return_status;
                clk_return_status = CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
                if (clk_return_status == SUCCESS)  //SUCCESS or ERROR
                {};
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//注意 当外部时钟大于16M时
		//我们必须通过STLINK将STM8 OPTION BYTE配置 中的WAITESTATE 配置字设置为“1 wait state”
		//请使用STVP进行配置
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//OK 闪烁LED
                
                
                LED_GPIO_Init();
		while (1)
		{
				LED_ON;
				DIS_Delayms(500);
				LED_OFF;
				DIS_Delayms(500);
		}
}

//软延时函数
void DIS_Delayms(u16 Num)
{
		u16 Timer;
		while(Num--)
		{
		 	Timer = 500;
			while(Timer--); 
		}
}			


// LED GPIO Initial
void LED_GPIO_Init(void)
{

   GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_OUT_PP_LOW_SLOW);//PD1，推挽输出

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
