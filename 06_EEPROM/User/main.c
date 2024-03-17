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
/* Private functions ---------------------------------------------------------*/

/* Global parameter ---------------------------------------------------------*/

/********************************************************************************************************
*  Function: Driver_FlashUNLock				                                                           
*  Object: 解锁EEPROM
*  输入： 无
*  输出： 无 	                                     
*  备注:  无
********************************************************************************************************/
void Driver_FlashUNLock(void)
{
                FLASH_Unlock(FLASH_MEMTYPE_DATA);   //解锁EEPROM            
}


/********************************************************************************************************
*  Function: Driver_FlashLock				                                                           
*  Object: 锁定EEPROM
*  输入： 无
*  输出： 无 	                                     
*  备注:  无
********************************************************************************************************/
void Driver_FlashLock(void)
{
                FLASH_Lock(FLASH_MEMTYPE_DATA);//锁定EEPROM
       
}
/********************************************************************************************************
*  Function: Driver_EPWrite				                                                           
*  Object: 写EEPROM
*  输入： 头地址(0~1535)  数据指针  数据长
*  输出： 无 	                                     
*  备注: 1.5K EEPROM  不能超过
********************************************************************************************************/
void Driver_EPWrite(uint32_t Adr, u8 *pData, u16 Len)
{
		uint32_t *p;
		//p指针指向EEPROM 对应的单元
		p = (uint32_t*)0x4000 + Adr;   
		//解锁
		Driver_FlashUNLock();
		//写数据
		for( ; Len > ZERO; Len--)
		{                                
                                FLASH_ProgramByte((uint32_t)p, *pData);
                                p++;
                                pData++;
		} 
		//加锁
		Driver_FlashLock();
}

/********************************************************************************************************
*  Function: Driver_EPRead				                                                           
*  Object: 读EEPROM
*  输入： 头地址(0~1535) 数据存放指针 数据长
*  输出： 无 	                                     
*  备注: 1.5K EEPROM
********************************************************************************************************/
void Driver_EPRead(uint32_t Adr, u8 *pData, u16 Len)
{
		uint32_t *p;
		//p指针指向EEPROM 对应的单元
		p = (uint32_t*)0x4000 + Adr; 
		//解锁
		Driver_FlashUNLock();
		//读数据
		for( ; Len > ZERO; Len--)
                {
			*pData++ = FLASH_ReadByte((uint32_t)p);
                        p++;
                }
		//加锁
		Driver_FlashLock();
}



//LED控制 输入1 点亮; 0 熄灭;
void Driver_LEDCont(bool flag)
{
		static bool startflag = TRUE;
		if(startflag)
		{
                                
                                GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_OUT_PP_LOW_SLOW);//PD3，推挽输出            
				startflag = (bool)0;
		}
		if(flag)
		{
                                GPIO_WriteLow(GPIOD,GPIO_PIN_3);//PD3输出低电平，点亮LED                       
		}
		else
		{
                                GPIO_WriteHigh(GPIOD,GPIO_PIN_3);//PD3输出高电平，关闭LED灯                                
		}
}


void main(void)
{      
		//STM8S 207R8 共有1.5K字节EEPROM
		u8 num[]={1,2,3};
		//从EERPOM首地址开始 写入1,2,3
		Driver_EPWrite(0, num, sizeof(num));
		//从EERPOM首地址开始 读入3个数进num数组
		memset(num, 0, sizeof(num));
		Driver_EPRead(0, num, sizeof(num));
		//判断EEPROM读出的数据是否等于写入的数据,是的话点亮LED1, 说明EEPROM读写正确
		if(num[0] == 1 && num[1] == 2 && num[2] == 3)
			Driver_LEDCont((bool)1);
		else
			Driver_LEDCont((bool)0);
		//OK
		while (1);
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
