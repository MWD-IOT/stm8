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
/* Private functions ---------------------------------------------------------*/

/* Global parameter ---------------------------------------------------------*/
volatile bool ExiFlag = False;

//PA4���жϳ�ʼ��
void Driver_ExtIntOn(void)
{		
                //PA4 ��������,�����˿��ж�
                GPIO_Init(GPIOA,GPIO_PIN_4,GPIO_MODE_IN_PU_IT);
		//�½��ش���
                EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA, EXTI_SENSITIVITY_FALL_ONLY);
}

// LED GPIO Initial
void LED_GPIO_Init(void)
{   
      GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_OUT_PP_LOW_SLOW);//PD1���������
      GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_OUT_PP_LOW_SLOW);//PA1���������
      GPIO_Init(GPIOA,GPIO_PIN_2,GPIO_MODE_OUT_PP_LOW_SLOW);
}


//LED���� ����1 ����; 0 Ϩ��;
void Driver_LEDCont(bool flag)
{
		if(flag)
		{
                                GPIO_WriteLow(GPIOD,GPIO_PIN_1);//PD1����͵�ƽ������LED
                                GPIO_WriteLow(GPIOA,GPIO_PIN_1);
                                GPIO_WriteLow(GPIOA,GPIO_PIN_2);
                      
		}
		else
		{
                                GPIO_WriteHigh(GPIOD,GPIO_PIN_1);//PD1����ߵ�ƽ���ر�LED��
                                GPIO_WriteHigh(GPIOA,GPIO_PIN_1);
                                GPIO_WriteHigh(GPIOA,GPIO_PIN_2);

                                
		}
}


void main(void)
{      
		//��������STM8Ĭ����HSI��Ƶ2Mִ�����ʽ���
                LED_GPIO_Init();
		Driver_LEDCont((bool)1);
		//�����ⲿ�ж�
		Driver_ExtIntOn();
		//�����ж�
                enableInterrupts(); 	/* �������ж� */
		//�ȴ��ж�
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
								//ѭ������LED��״̬
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
