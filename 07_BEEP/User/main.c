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
void LED_GPIO_Init(void);
void DIS_Delayms(u16 Num);
/* Private functions ---------------------------------------------------------*/
//开启BEEP,按Fred指定的频率运作 
void Beep_Control_ON(u8 Fred)
{
		switch(Fred)
		{
				case 1:  BEEP_Init(BEEP_FREQUENCY_1KHZ);
                                         BEEP_Cmd(ENABLE); 
                                         break;   //1K输出
				case 2:  BEEP_Init(BEEP_FREQUENCY_2KHZ);
                                         BEEP_Cmd(ENABLE); 
                                         break;   //2K输出
				case 4:  BEEP_Init(BEEP_FREQUENCY_4KHZ);
                                         BEEP_Cmd(ENABLE); 
                                         break;   //4K输出
		}
}

//关闭BEEP
void Beep_OFF(void)
{
	BEEP_Cmd(DISABLE);

}

void LED_GPIO_Init(void)
{
          GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_OUT_PP_HIGH_FAST);//PD1，推挽输出
          GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_OUT_PP_HIGH_FAST);//PA1，推挽输出
          GPIO_Init(GPIOA,GPIO_PIN_2,GPIO_MODE_OUT_PP_HIGH_FAST);
          GPIO_Init(GPIOD,GPIO_PIN_5,GPIO_MODE_OUT_PP_HIGH_FAST);
          GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_OUT_PP_HIGH_FAST);

}

//LED控制 
//输入Num:第x个LED;  输入Flag: 1-Led点亮; 0-Led熄灭；
void LEDCont(u8 Num, bool Flag)
{
     
      if(Flag)
      {
                      switch(Num)
                      {
                        case 1: GPIO_WriteLow(GPIOD,GPIO_PIN_1);  break;//PD1输出低电平，点亮LED
                        case 2:	GPIO_WriteLow(GPIOA,GPIO_PIN_1);  break;
                        case 3:	GPIO_WriteLow(GPIOA,GPIO_PIN_2);  break;
                        case 4:	GPIO_WriteLow(GPIOD,GPIO_PIN_5);  break;
                        case 5:	GPIO_WriteLow(GPIOD,GPIO_PIN_3);  break;
                        default : break;
                      }
      }
      else
      {
                      switch(Num)
                      {
                        case 1: GPIO_WriteHigh(GPIOD,GPIO_PIN_1);  break;//PD1输出高电平， 关闭LED
                        case 2:	GPIO_WriteHigh(GPIOA,GPIO_PIN_1);  break;
                        case 3:	GPIO_WriteHigh(GPIOA,GPIO_PIN_2);  break;
                        case 4:	GPIO_WriteHigh(GPIOD,GPIO_PIN_5);  break;
                        case 5:	GPIO_WriteHigh(GPIOD,GPIO_PIN_3);  break;
                        default:break;
                      }
      }	
}



void main(void)
{      
		//BEEP端口属 STM8优秀的外设之一 
		//开启BEEP端输出
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//注意 
		//我们必须通过STLINK将STM8 OPTION BYTE配置 中的PD4管脚配置为BEEP功能
		//请使用STVP进行配置
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//开启BEEP 循环输出1K 2K 4K 方波频率,并且点亮1,2,3LED灯
		while(1)
		{
				//蜂鸣1K
				LEDCont(1, (bool)1);
				LEDCont(2, (bool)0);
				LEDCont(3, (bool)0);
				Beep_Control_ON(1);
				DIS_Delayms(100);
				Beep_OFF();
				DIS_Delayms(100);
				//蜂鸣2K
				LEDCont(1, (bool)0);
				LEDCont(2, (bool)1);
				LEDCont(3, (bool)0);
				Beep_Control_ON(2);
				DIS_Delayms(100);
				Beep_OFF();
				DIS_Delayms(100);	
				//蜂鸣4K
				LEDCont(1, (bool)0);
				LEDCont(2, (bool)0);
				LEDCont(3, (bool)1);
				Beep_Control_ON(4);
				DIS_Delayms(100);
				Beep_OFF();
				DIS_Delayms(100);
		}
}

//延时函数
void DIS_Delayms(u16 Num)
{
		u16 Timer;
		while(Num--)
		{
		 	Timer = 1000/4;
			while(Timer--); 
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
