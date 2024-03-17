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
//����BEEP,��Fredָ����Ƶ������ 
void Beep_Control_ON(u8 Fred)
{
		switch(Fred)
		{
				case 1:  BEEP_Init(BEEP_FREQUENCY_1KHZ);
                                         BEEP_Cmd(ENABLE); 
                                         break;   //1K���
				case 2:  BEEP_Init(BEEP_FREQUENCY_2KHZ);
                                         BEEP_Cmd(ENABLE); 
                                         break;   //2K���
				case 4:  BEEP_Init(BEEP_FREQUENCY_4KHZ);
                                         BEEP_Cmd(ENABLE); 
                                         break;   //4K���
		}
}

//�ر�BEEP
void Beep_OFF(void)
{
	BEEP_Cmd(DISABLE);

}

void LED_GPIO_Init(void)
{
          GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_OUT_PP_HIGH_FAST);//PD1���������
          GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_OUT_PP_HIGH_FAST);//PA1���������
          GPIO_Init(GPIOA,GPIO_PIN_2,GPIO_MODE_OUT_PP_HIGH_FAST);
          GPIO_Init(GPIOD,GPIO_PIN_5,GPIO_MODE_OUT_PP_HIGH_FAST);
          GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_OUT_PP_HIGH_FAST);

}

//LED���� 
//����Num:��x��LED;  ����Flag: 1-Led����; 0-LedϨ��
void LEDCont(u8 Num, bool Flag)
{
     
      if(Flag)
      {
                      switch(Num)
                      {
                        case 1: GPIO_WriteLow(GPIOD,GPIO_PIN_1);  break;//PD1����͵�ƽ������LED
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
                        case 1: GPIO_WriteHigh(GPIOD,GPIO_PIN_1);  break;//PD1����ߵ�ƽ�� �ر�LED
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
		//BEEP�˿��� STM8���������֮һ 
		//����BEEP�����
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//ע�� 
		//���Ǳ���ͨ��STLINK��STM8 OPTION BYTE���� �е�PD4�ܽ�����ΪBEEP����
		//��ʹ��STVP��������
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//����BEEP ѭ�����1K 2K 4K ����Ƶ��,���ҵ���1,2,3LED��
		while(1)
		{
				//����1K
				LEDCont(1, (bool)1);
				LEDCont(2, (bool)0);
				LEDCont(3, (bool)0);
				Beep_Control_ON(1);
				DIS_Delayms(100);
				Beep_OFF();
				DIS_Delayms(100);
				//����2K
				LEDCont(1, (bool)0);
				LEDCont(2, (bool)1);
				LEDCont(3, (bool)0);
				Beep_Control_ON(2);
				DIS_Delayms(100);
				Beep_OFF();
				DIS_Delayms(100);	
				//����4K
				LEDCont(1, (bool)0);
				LEDCont(2, (bool)0);
				LEDCont(3, (bool)1);
				Beep_Control_ON(4);
				DIS_Delayms(100);
				Beep_OFF();
				DIS_Delayms(100);
		}
}

//��ʱ����
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
