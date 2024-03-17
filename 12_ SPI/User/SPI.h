/**
  ******************************************************************************
  * @file    stm8s_spi.h
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   This file contains all functions prototype and macros for the SPI peripheral.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H
#define __SPI_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"


#define IO_Rst_H    GPIO_WriteHigh(GPIOB,GPIO_PIN_5)
#define IO_Rst_L    GPIO_WriteLow(GPIOB,GPIO_PIN_5)

//#define AD9910_F1_H

// SPI CS
#define SPI_CS_H     GPIO_WriteHigh(GPIOA,GPIO_PIN_3)
#define SPI_CS_L     GPIO_WriteLow(GPIOA,GPIO_PIN_3)


void SPI_Initial(void);
void SPI_Send(u8 *DataBuff,u16 DataLen);
void SPI_Receive(u8 *DataBuff,u16 DataLen);
void SPI_Write(u8 addr,u8 *dat,u8 num);
void SPI_Read(u8 addr,u8 num,u8 *Rec_dat);

/**
  * @}
  */

#endif /* __STM8S_SPI_H */

/**
  * @}
  */
  
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/