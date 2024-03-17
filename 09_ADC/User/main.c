/***************************************************************
* 深圳米客科技
* http://etrh.taobao.com
* 实验平台：STM8S开发板
* 库版本  ：V2.1.0
***************************************************************/
/* Includes ------------------------------------------------------------------*/
/* 包含系统头文件 */
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
*  Object:  开启串口，并执行初始化                         
*  输入： 无
*  输出： 无								                         	                                     
*  备注： 8位数据位 无校验 1位起始位/1位停止位 	宏定义BAUDRATE设定波特率 
********************************************************************************************************/
void Driver_UARTON(void)
{	
        //关闭发送中断		
        //波特率设定 主时钟为HSI-16M //8位数据位 1位起始位 1位停止位 无校验//启动收发
        UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
        UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);//允许接收中断
        UART1_Cmd(ENABLE);		        //使能UART
}

/********************************************************************************************************
*  Function: Driver_UARTSendByByte						                                                           
*  Object:  串口数据外发                            
*  输入： 发送的数据
*  输出： 无								                         	                                     
*  备注： 1Byte							                                         
********************************************************************************************************/
void Driver_UARTSendByByte(u8 Data)
{
        FlagStatus fs;
        
        UART1_SendData8((u8)Data);
        //fs=RESET or SET,等待发送数据寄存器空，说明发送成功
        do{
            fs = UART1_GetFlagStatus(UART1_FLAG_TXE); // 发送成功，返回SET,
        }while(fs == RESET );	/* 等待传输结束 */
 
}

/*******************************************************************************
 *   sFunction: fputc
 *   Object: 重定向c库函数printf到UART1
 *  输入： 无
 *  输出： 无	
 * 返回: 要打印的字符
 * 说明: 由printf调用 
 ******************************************************************************/
int fputc(int ch, FILE *f)
{  
	/* 将Printf内容发往串口 */

	Driver_UARTSendByByte(ch);
	
	return (ch);
}

#endif //__DEBUG__


/********************************************************************************************************
*  Function: Driver_ADCON						                                                           
*  Object: 启动ADC模块 执行初始化      
*  输入： 无
*  输出： 无								                         	                                     
*  备注： 无                                  
********************************************************************************************************/
void Driver_ADCON(void)
{                         
                CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, ENABLE);
                //单次转换，通道14，系统时钟，8 分频，关闭外部触发事件，数据左对齐，关闭施密特触发器
                ADC2_Init(ADC2_CONVERSIONMODE_SINGLE, ADC2_CHANNEL_14, ADC2_PRESSEL_FCPU_D8, ADC2_EXTTRIG_TIM, 
                          DISABLE, ADC2_ALIGN_LEFT, ADC2_SCHMITTTRIG_CHANNEL0, DISABLE);
                ADC2_ITConfig(DISABLE);//ADC转换结束中断禁止 
                ADC2_Cmd(ENABLE);//启用ADC2


             
}

//LED控制 
//输入Num:第x个LED;  输入Flag: 1-Led点亮; 0-Led熄灭；
void LEDCont(u8 Num, bool Flag)
{
      static bool startflag = TRUE;
      if(startflag)
      {
                      
                      GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_OUT_PP_HIGH_FAST);//PD1，推挽输出
                      GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_OUT_PP_HIGH_FAST);//PA1，推挽输出
                      GPIO_Init(GPIOA,GPIO_PIN_2,GPIO_MODE_OUT_PP_HIGH_FAST);
                      GPIO_Init(GPIOD,GPIO_PIN_5,GPIO_MODE_OUT_PP_HIGH_FAST);
                      GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_OUT_PP_HIGH_FAST);
                
                      startflag = (bool)0;
      }  
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
	        u16 u16_ADC2_value;
                //开启ADC外设
		Driver_ADCON();
#ifdef __DEBUG__
                Driver_UARTON();
                enableInterrupts();/* 开启总中断 */    
#endif
		while(1)
		{
				// 开始转换
				ADC2_StartConversion();
                                //读ADC值
                                u16_ADC2_value = ADC2_GetConversionValue();                                
#ifdef __DEBUG__
                                printf("%d\r\n",u16_ADC2_value);
#endif                                

				if(u16_ADC2_value)
				{
						//根据ADC值 控制LED灯
					        LEDCont(1, (bool)0);
						LEDCont(2, (bool)0);
						LEDCont(3, (bool)0);
						LEDCont(4, (bool)0);
						LEDCont(5, (bool)0);
						if(u16_ADC2_value > 200)//因为每一个光敏电阻的阻值不一样，这个实验的值，可能需要根据实际情况修改，不然可能灯一直会亮
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

//软延时函数
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
