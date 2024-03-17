/******************** (C) COPYRIGHT 米客科技 ********************/

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __I2C_H
#define __I2C_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "prohead.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C_Speed              100000
#define I2C1_SLAVE_ADDRESS7    0xA0


void IIC_Initial(void);
void IIC_OFF(void);
void IIC_Write8(u8 Dev_addr,u8 WriteAddr,u8 *DataBuff,u16 DataLen);//设备地址，写寄存器地址，写数据数组，写个数
void IIC_Recv8(u8 Dev_addr,u8 Read_addr,u8 *DataBuff,u16 DataLen);//设备地址，读寄存器，读数据缓存，读个数

#endif /* __I2C_EE_H */

/******************* (C) COPYRIGHT 米客科技 *****END OF FILE****/
