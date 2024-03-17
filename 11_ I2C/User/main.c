/***************************************************************
* http://etrh.taobao.com
* 实验平台：米客STM8开发板
* 库版本  ：V2.1.0
***************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "prohead.h"
#include "i2c.h"

/* Global parameter ---------------------------------------------------------*/
#define MMA7660ADRW         0x98  
#define LM75ARR         0x90    

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
//温度值变量
u8 Temp_Vaule;

  
void main(void)
{      
		//初始化I2C接口
		IIC_Initial();
		u8 Data1[]= {0x00};
		IIC_Write8(LM75ARR,0x01,Data1,1);
		while (1)
                {
         	u8 Buff[3]; 
		IIC_Recv8(LM75ARR, 0x00,Buff,3);
		Temp_Vaule  =Buff[0];	
		Temp_Vaule  =Buff[1];	
                Temp_Vaule  =Buff[2];	
             //   Temp_Vaule  =Buff[3];	
		//保存结果
		//Temp_Vaule = ;
                };
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
