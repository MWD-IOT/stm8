/***************************************************************
* �����׿ͿƼ�
* http://etrh.taobao.com
* ʵ��ƽ̨��STM8S������
* ��汾  ��V2.1.0
***************************************************************/
/* Includes ------------------------------------------------------------------*/
/* ����ϵͳͷ�ļ� */
#include <stdarg.h>
#include <stdio.h>
#include "stm8s.h"
#include "prohead.h"
/* Private defines -----------------------------------------------------------*/
//#define __DEBUG__
/* Private function prototypes -----------------------------------------------*/
void DIS_Delayms(u16 Num);
/* Private functions ---------------------------------------------------------*/

#ifdef __DEBUG__
/********************************************************************************************************
*  Function: Driver_UARTON						                                                           
*  Object:  �������ڣ���ִ�г�ʼ��                         
*  ���룺 ��
*  ����� ��								                         	                                     
*  ��ע�� 8λ����λ ��У�� 1λ��ʼλ/1λֹͣλ 	�궨��BAUDRATE�趨������ 
********************************************************************************************************/
void Driver_UARTON(void)
{	
        //�رշ����ж�		
        //�������趨 ��ʱ��ΪHSI-16M //8λ����λ 1λ��ʼλ 1λֹͣλ ��У��//�����շ�
        UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
        UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);//��������ж�
        UART1_Cmd(ENABLE);		        //ʹ��UART
}

/********************************************************************************************************
*  Function: Driver_UARTSendByByte						                                                           
*  Object:  ���������ⷢ                            
*  ���룺 ���͵�����
*  ����� ��								                         	                                     
*  ��ע�� 1Byte							                                         
********************************************************************************************************/
void Driver_UARTSendByByte(u8 Data)
{
        FlagStatus fs;
        
        UART1_SendData8((u8)Data);
        //fs=RESET or SET,�ȴ��������ݼĴ����գ�˵�����ͳɹ�
        do{
            fs = UART1_GetFlagStatus(UART1_FLAG_TXE); // ���ͳɹ�������SET,
        }while(fs == RESET );	/* �ȴ�������� */
 
}

/*******************************************************************************
 *   sFunction: fputc
 *   Object: �ض���c�⺯��printf��UART1
 *  ���룺 ��
 *  ����� ��	
 * ����: Ҫ��ӡ���ַ�
 * ˵��: ��printf���� 
 ******************************************************************************/
int fputc(int ch, FILE *f)
{  
	/* ��Printf���ݷ������� */

	Driver_UARTSendByByte(ch);
	
	return (ch);
}

#endif //__DEBUG__


/********************************************************************************************************
*  Function: Driver_ADCON						                                                           
*  Object: ����ADCģ�� ִ�г�ʼ��      
*  ���룺 ��
*  ����� ��								                         	                                     
*  ��ע�� ��                                  
********************************************************************************************************/
void Driver_ADCON(void)
{                         
                CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, ENABLE);
                //����ת����ͨ��14��ϵͳʱ�ӣ�8 ��Ƶ���ر��ⲿ�����¼�����������룬�ر�ʩ���ش�����
                ADC2_Init(ADC2_CONVERSIONMODE_SINGLE, ADC2_CHANNEL_14, ADC2_PRESSEL_FCPU_D8, ADC2_EXTTRIG_TIM, 
                          DISABLE, ADC2_ALIGN_LEFT, ADC2_SCHMITTTRIG_CHANNEL0, DISABLE);
                ADC2_ITConfig(DISABLE);//ADCת�������жϽ�ֹ 
                ADC2_Cmd(ENABLE);//����ADC2


             
}

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



void main(void)
{      
	        u16 u16_ADC2_value;
                //����ADC����
		Driver_ADCON();
#ifdef __DEBUG__
                Driver_UARTON();
                enableInterrupts();/* �������ж� */    
#endif
		while(1)
		{
				// ��ʼת��
				ADC2_StartConversion();
                                //��ADCֵ
                                u16_ADC2_value = ADC2_GetConversionValue();                                
#ifdef __DEBUG__
                                printf("%d\r\n",u16_ADC2_value);
#endif                                

				if(u16_ADC2_value)
				{
						//����ADCֵ ����LED��
					        LEDCont(1, (bool)0);
						LEDCont(2, (bool)0);
						LEDCont(3, (bool)0);
						LEDCont(4, (bool)0);
						LEDCont(5, (bool)0);
						if(u16_ADC2_value > 200)//��Ϊÿһ�������������ֵ��һ�������ʵ���ֵ��������Ҫ����ʵ������޸ģ���Ȼ���ܵ�һֱ����
							LEDCont(1, (bool)1);
						if(u16_ADC2_value > 350)
							LEDCont(2, (bool)1);
						if(u16_ADC2_value > 500)
							LEDCont(3, (bool)1);
						if(u16_ADC2_value > 650)
							LEDCont(4, (bool)1);
						if(u16_ADC2_value > 800)
							LEDCont(5, (bool)1);
				}
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
