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

//PWM��ʼ��
void Driver_PWMON(void)
{ 
                CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER3, ENABLE);
                //����PWMƵ�ʣ�Fpwm=Fmaster/TIM3_ARR 
		//����Fpwm = 2000000/100 = 20K
                TIM3_TimeBaseInit(TIM3_PRESCALER_1, 0x0064);
                //����TIM3_CH1 ΪPWMģʽ2 ,����TIM3_CH1 ͨ�����,��������Ƚϣ�50%ռ�ձ�
                TIM3_OC1Init(TIM3_OCMODE_PWM2, TIM3_OUTPUTSTATE_ENABLE, 0x0050, TIM3_OCPOLARITY_HIGH);
                //��������,��ʼPWM���
                TIM3_Cmd(ENABLE);


}

//PWMռ�ձȵ��� 0-100, ��ֵԽ��LIGHT��Խ��
void Driver_PWMSet(u16 Num)
{
		if(Num > 100)
			return;
                TIM3_SetCompare1((u16)Num);

}

//��ʱ����
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
		//����PWM�����PD2 TIM3_CH1���
		Driver_PWMON();
		//����PWMռ�ձ� ʵ�ֽ���Ч��
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
