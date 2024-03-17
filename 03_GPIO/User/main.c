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
void DIS_Delayms(u16 Num);
/* Private functions ---------------------------------------------------------*/

//LED���� 
//����Num:��x��LED;  ����Flag: 1-Led����; 0-LedϨ��
void LEDCont(u8 Num, bool Flag)
{
      static bool startflag = TRUE;
      if(startflag)
      {
                      
                      GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_OUT_PP_HIGH_FAST);//PD1���������
                      GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_OUT_PP_HIGH_FAST);//PA1���������
                      GPIO_Init(GPIOA,GPIO_PIN_2,GPIO_MODE_OUT_PP_HIGH_FAST);
                      GPIO_Init(GPIOD,GPIO_PIN_5,GPIO_MODE_OUT_PP_HIGH_FAST);
                      GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_OUT_PP_HIGH_FAST);
                
                      startflag = (bool)0;
      }  
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


//������1״̬
BitStatus ReadKey1(void)
{
	  BitStatus bit_status;	  
          //GPIO ��������, ����
          GPIO_Init(GPIOF,GPIO_PIN_5,GPIO_MODE_IN_PU_NO_IT);
	  //��ȡ״̬
          bit_status = GPIO_ReadInputPin(GPIOF, GPIO_PIN_5);
         
          return bit_status;
}

//������2״̬
BitStatus ReadKey2(void)
{
	  BitStatus bit_status;	  
          //GPIO ��������, ����
          GPIO_Init(GPIOF,GPIO_PIN_4,GPIO_MODE_IN_PU_NO_IT);
	  //��ȡ״̬
          bit_status = GPIO_ReadInputPin(GPIOF, GPIO_PIN_4);
         
          return bit_status;
}

//������3״̬
BitStatus ReadKey3(void)
{
	  BitStatus bit_status;	  
          //GPIO ��������, ����
          GPIO_Init(GPIOF,GPIO_PIN_0,GPIO_MODE_IN_PU_NO_IT);
	  //��ȡ״̬
          bit_status = GPIO_ReadInputPin(GPIOF, GPIO_PIN_0);
         
          return bit_status;
}

void main(void)
{      
	while(1)
	{
			static u8 Timer;
			static bool flag;
			//��˸LED4��LED5
			if(!Timer)
			{
					Timer = 5;
					flag = !flag;
					LEDCont(4, flag);
					LEDCont(5, flag);
			}
			else
				Timer--;
			//��������LED1״̬
			if(ReadKey1())
				LEDCont(1, (bool)0);
			else
				LEDCont(1, (bool)1);
			//��������LED2״̬	
			if(ReadKey2())
				LEDCont(2, (bool)0);
			else
				LEDCont(2, (bool)1);
			//��������LED3״̬	
			if(ReadKey3())
				LEDCont(3, (bool)0);
			else
				LEDCont(3, (bool)1);
			DIS_Delayms(10);
	}
}

//����ʱ����
void DIS_Delayms(u16 Num)
{
		u16 Timer;
		while(Num--)
		{
		 	Timer = 1000;
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
