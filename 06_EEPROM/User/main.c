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

/********************************************************************************************************
*  Function: Driver_FlashUNLock				                                                           
*  Object: ����EEPROM
*  ���룺 ��
*  ����� �� 	                                     
*  ��ע:  ��
********************************************************************************************************/
void Driver_FlashUNLock(void)
{
                FLASH_Unlock(FLASH_MEMTYPE_DATA);   //����EEPROM            
}


/********************************************************************************************************
*  Function: Driver_FlashLock				                                                           
*  Object: ����EEPROM
*  ���룺 ��
*  ����� �� 	                                     
*  ��ע:  ��
********************************************************************************************************/
void Driver_FlashLock(void)
{
                FLASH_Lock(FLASH_MEMTYPE_DATA);//����EEPROM
       
}
/********************************************************************************************************
*  Function: Driver_EPWrite				                                                           
*  Object: дEEPROM
*  ���룺 ͷ��ַ(0~1535)  ����ָ��  ���ݳ�
*  ����� �� 	                                     
*  ��ע: 1.5K EEPROM  ���ܳ���
********************************************************************************************************/
void Driver_EPWrite(uint32_t Adr, u8 *pData, u16 Len)
{
		uint32_t *p;
		//pָ��ָ��EEPROM ��Ӧ�ĵ�Ԫ
		p = (uint32_t*)0x4000 + Adr;   
		//����
		Driver_FlashUNLock();
		//д����
		for( ; Len > ZERO; Len--)
		{                                
                                FLASH_ProgramByte((uint32_t)p, *pData);
                                p++;
                                pData++;
		} 
		//����
		Driver_FlashLock();
}

/********************************************************************************************************
*  Function: Driver_EPRead				                                                           
*  Object: ��EEPROM
*  ���룺 ͷ��ַ(0~1535) ���ݴ��ָ�� ���ݳ�
*  ����� �� 	                                     
*  ��ע: 1.5K EEPROM
********************************************************************************************************/
void Driver_EPRead(uint32_t Adr, u8 *pData, u16 Len)
{
		uint32_t *p;
		//pָ��ָ��EEPROM ��Ӧ�ĵ�Ԫ
		p = (uint32_t*)0x4000 + Adr; 
		//����
		Driver_FlashUNLock();
		//������
		for( ; Len > ZERO; Len--)
                {
			*pData++ = FLASH_ReadByte((uint32_t)p);
                        p++;
                }
		//����
		Driver_FlashLock();
}



//LED���� ����1 ����; 0 Ϩ��;
void Driver_LEDCont(bool flag)
{
		static bool startflag = TRUE;
		if(startflag)
		{
                                
                                GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_OUT_PP_LOW_SLOW);//PD3���������            
				startflag = (bool)0;
		}
		if(flag)
		{
                                GPIO_WriteLow(GPIOD,GPIO_PIN_3);//PD3����͵�ƽ������LED                       
		}
		else
		{
                                GPIO_WriteHigh(GPIOD,GPIO_PIN_3);//PD3����ߵ�ƽ���ر�LED��                                
		}
}


void main(void)
{      
		//STM8S 207R8 ����1.5K�ֽ�EEPROM
		u8 num[]={1,2,3};
		//��EERPOM�׵�ַ��ʼ д��1,2,3
		Driver_EPWrite(0, num, sizeof(num));
		//��EERPOM�׵�ַ��ʼ ����3������num����
		memset(num, 0, sizeof(num));
		Driver_EPRead(0, num, sizeof(num));
		//�ж�EEPROM�����������Ƿ����д�������,�ǵĻ�����LED1, ˵��EEPROM��д��ȷ
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
