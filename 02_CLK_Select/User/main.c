/***************************************************************
* �����׿ͿƼ�
* http://etrh.taobao.com
* ʵ��ƽ̨��STM8S������
* ��汾  ��V2.1.0
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

#define LED_ON    GPIO_WriteLow(GPIOD,GPIO_PIN_1)//PD1����͵�ƽ������LED
#define LED_OFF   GPIO_WriteHigh(GPIOD,GPIO_PIN_1)//PD1����ߵ�ƽ��Ϩ��LED

void main(void)
{
  
		//STM8S Ĭ����������Ϊ�ڲ�16MHZ ����HSI 
		//���������л����ⲿʱ��
		//����ʱ���л��ж�_SWIEN����
                ErrorStatus clk_return_status;
                clk_return_status = CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
                if (clk_return_status == SUCCESS)  //SUCCESS or ERROR
                {};
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//ע�� ���ⲿʱ�Ӵ���16Mʱ
		//���Ǳ���ͨ��STLINK��STM8 OPTION BYTE���� �е�WAITESTATE ����������Ϊ��1 wait state��
		//��ʹ��STVP��������
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//OK ��˸LED
                
                
                LED_GPIO_Init();
		while (1)
		{
				LED_ON;
				DIS_Delayms(500);
				LED_OFF;
				DIS_Delayms(500);
		}
}

//����ʱ����
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

   GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_OUT_PP_LOW_SLOW);//PD1���������

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
