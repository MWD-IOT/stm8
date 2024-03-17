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

//PWM初始化
void Driver_PWMON(void)
{ 
                CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER3, ENABLE);
                //设置PWM频率，Fpwm=Fmaster/TIM3_ARR 
		//这里Fpwm = 2000000/100 = 20K
                TIM3_TimeBaseInit(TIM3_PRESCALER_1, 0x0064);
                //设置TIM3_CH1 为PWM模式2 ,开启TIM3_CH1 通道输出,启用输出比较，50%占空比
                TIM3_OC1Init(TIM3_OCMODE_PWM2, TIM3_OUTPUTSTATE_ENABLE, 0x0050, TIM3_OCPOLARITY_HIGH);
                //启动计数,开始PWM输出
                TIM3_Cmd(ENABLE);


}

//PWM占空比调节 0-100, 数值越大LIGHT灯越亮
void Driver_PWMSet(u16 Num)
{
		if(Num > 100)
			return;
                TIM3_SetCompare1((u16)Num);

}

//延时函数
void DIS_Delayms(u16 Num)
{
		u16 Timer;
		while(Num--)
		{
		 	Timer = 1000;
			while(Timer--); 
		}
}	

void main(void)
{      
		//开启PWM输出从PD2 TIM3_CH1输出
		Driver_PWMON();
		//调节PWM占空比 实现渐亮效果
		while(1)
		{
				static u16 Num = 0;
				if(Num > 100)
					Num = 1;
				Driver_PWMSet(Num);
				DIS_Delayms(30);
				Num += 1;
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
