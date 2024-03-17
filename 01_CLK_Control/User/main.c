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
void LED_GPIO_Init(void);
void DIS_Delayms(u16 Num);
/* Private functions ---------------------------------------------------------*/

#define LED_ON    GPIO_WriteLow(GPIOD,GPIO_PIN_1)//PD1����͵�ƽ������LED
#define LED_OFF   GPIO_WriteHigh(GPIOD,GPIO_PIN_1)//PD1����ߵ�ƽ��Ϩ��LED

void main(void)
{
  
		u8 i;
		//STM8S Ĭ����������Ϊ�ڲ�16MHZ 8��Ƶ CPUDIVȫ��ִ��
		//2M  CPUDIVȫ��ִ��     ---- �ֱ���˸3��LED -----
                LED_GPIO_Init();// GPIO Initial
		for(i = 0; i < 3; i++)
		{
				LED_ON;
				DIS_Delayms(500);
				LED_OFF;
				DIS_Delayms(500);
		}
                
		//����-> 4M CPUDIVȫ��ִ��
                CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV4);// ʱ�ӿ���
       
		for(i = 0; i < 3; i++)
		{
				LED_ON;
				DIS_Delayms(500);
				LED_OFF;
				DIS_Delayms(500);
		}		
		//����-> 8M CPUDIVȫ��ִ��
		CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV2);

           
		for(i = 0; i < 3; i++)
		{
				LED_ON;
				DIS_Delayms(500);
				LED_OFF;
				DIS_Delayms(500);
		}		
		//����-> 16M CPUDIVȫ��ִ��
		CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
          
		for(i = 0; i < 3; i++)
		{
				LED_ON;
				DIS_Delayms(500);
				LED_OFF;
				DIS_Delayms(500);
		}		
		
		//����-> 16M CPUDIV 2��Ƶִ��
		CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV2);

            
		for(i = 0; i < 3; i++)
		{
				LED_ON;
				DIS_Delayms(500);
				LED_OFF;
				DIS_Delayms(500);
		}	
		//����-> 16M CPUDIV 4��Ƶִ��
		CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV4);

            
		for(i = 0; i < 3; i++)
		{
				LED_ON;
				DIS_Delayms(500);
				LED_OFF;
				DIS_Delayms(500);
		}	
		//����-> 16M CPUDIV 8��Ƶִ��
		CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV8);

            
		for(i = 0; i < 3; i++)
		{
				LED_ON;
				DIS_Delayms(500);
				LED_OFF;
				DIS_Delayms(500);
		}	
		//����-> 16M CPUDIV 16��Ƶִ��
		CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV16);
          
		for(i = 0; i < 3; i++)
		{
				LED_ON;
				DIS_Delayms(500);
				LED_OFF;
				DIS_Delayms(500);
		}	
		
  while (1)//
  {
  }
  
}

// LED GPIO Initial
void LED_GPIO_Init(void)
{

   GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_OUT_PP_LOW_SLOW);//PD1���������

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
