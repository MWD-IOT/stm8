/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/*******************************************************************************************************
*  Function: IIC_Initial						                                                           
*  Object: 打开I2C模块，并执行初始化	
*  输入： 无
*  输出： 无	   	                                     
*  备注： 主模式 两线连接 硬件I2C  7位地址模式 I2C采用寻址方式通信 时序较复杂 也常用于多设备通信  
*         10Kbps 通信速率
********************************************************************************************************/
void IIC_Initial(void)
{ 
                CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, ENABLE);//启用外设时钟
                //标准模式（100kbits）  , 无应答，7位从地址长度。2M输入时钟频率
                I2C_Init(I2C_Speed, I2C1_SLAVE_ADDRESS7, I2C_DUTYCYCLE_2, I2C_ACK_NONE, I2C_ADDMODE_7BIT, CLK_GetClockFreq()/1000000);
                I2C_Cmd(ENABLE);//启用I2C
}


/********************************************************************************************************
*  Function: IIC_OFF						                                                           
*  Object: 关闭I2C模块	
*  输入： 无
*  输出： 无	   	                                     
*  备注:  无
********************************************************************************************************/
void IIC_OFF(void)
{ 
		u16 time;
		//等待总线空闲 超时则不再等待
		time = 500;
		while(I2C_GetFlagStatus(I2C_FLAG_BUSBUSY) || --time);
		//关闭I2C模块
                I2C_Cmd(DISABLE);
		//关I2C时钟
                CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE);
}

/********************************************************************************************************
*  Function: IIC_Write8						                                                           
*  Object: 硬件I2C发送
*  输入： 从设备地址；写寄存器开始地址；待发送数据的头指针；待发数据的长； 
*  输出： 无  	                                     
*  备注:  通信中如果出现超时故障 则直接返回 避免长等待
********************************************************************************************************/
void IIC_Write8(u8 Dev_addr,u8 WriteAddr,u8 *DataBuff,u16 DataLen)
{  	
		u16 time;
		//等待总线空闲
		time = 500;
		while(I2C_GetFlagStatus(I2C_FLAG_BUSBUSY))
			if(!--time) 
				return;
				
		//发起始条件
                I2C_GenerateSTART(ENABLE);               
                // 测试EV5 ，
                while(!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));		
		//发从地址
                I2C_Send7bitAddress(Dev_addr, I2C_DIRECTION_TX);//从设备地址发送

		//等待ACK应答
		time = 500;
                //* 测试EV6并清除标志位，检测从器件返回一个应答信号 */
                while(!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
			if(!--time) 
				return;
                //发送写寄存器地址
                I2C_SendData(WriteAddr);
                /* Test on EV8 and clear it */
                while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));

		//发送数据
		for(;DataLen>0;DataLen--,DataBuff++)
		{
                                while( !I2C_GetFlagStatus(I2C_FLAG_TXEMPTY));//等待寄存器为空

                                I2C_SendData(*DataBuff);//发送数据
                                //等待发送完毕
                                while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		}
	
		//发停止条件,关闭通信
                I2C_GenerateSTOP(ENABLE);
}

/********************************************************************************************************
*  Function: IIC_Recv8						                                                           
*  Object: 硬件I2C接收 
*  输入： 从设备地址；待接收数据的头指针；待发数据的长；
*  输出： 无 	                                     
*  备注:  通信中如果出现超时故障 则直接返回 避免长等待
********************************************************************************************************/
void IIC_Recv8(u8 Dev_addr,u8 Read_addr,u8 *DataBuff,u16 DataLen)
{  	

	u16 time;
		//等待总线空闲
		time = 500;
		while(I2C_GetFlagStatus(I2C_FLAG_BUSBUSY))
			if(!--time) 
				return;
				
		//发起始条件
                I2C_GenerateSTART(ENABLE);               
                // 测试EV5 ，
                while(!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));		
		//发从地址
                I2C_Send7bitAddress(Dev_addr, I2C_DIRECTION_TX);//从设备地址发送

		//等待ACK应答
		time = 500;
                //* 测试EV6并清除标志位，检测从器件返回一个应答信号 */
                while(!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
			if(!--time) 
				return;
                //发送写寄存器地址
                I2C_SendData(Read_addr);
                /* Test on EV8 and clear it */
                while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
                
                time = 500;
		while(I2C_GetFlagStatus(I2C_FLAG_BUSBUSY))
			if(!--time)
				return;
                   //再发起始位，
                I2C_GenerateSTART(ENABLE);
                while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));
                asm("nop");
		asm("nop");
		asm("nop");

                //发送从地址，主模式进入接收模式
                I2C_Send7bitAddress(Dev_addr+1, I2C_DIRECTION_RX);
                time = 500;
                while (!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
                  
		//接收数据,读DataLen-1个数
		//读取多少数据是，必须使能ACK应答
                I2C_AcknowledgeConfig(I2C_ACK_CURR);
		for(;DataLen>1;DataLen--,DataBuff++)
		{
			//等待寄存器为满
                        time = 500;
                        while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_RECEIVED))
                          if(!--time)
				return;
			*DataBuff = I2C_ReceiveData();
		}
                //关闭ACK应答
               I2C_AcknowledgeConfig(I2C_ACK_NONE);
	
		//发停止条件,关闭通信
                I2C_GenerateSTOP(ENABLE);
                asm("nop");
		asm("nop");
		asm("nop");
	
		//读最后一个数
		time = 500;
                while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_RECEIVED))
			if(!--time)
				return;
		*DataBuff = I2C_ReceiveData();		
}

u8 I2C_ReadRegister_SR1()
{
  uint8_t temp;
  temp=I2C->SR1;
  return temp;
}
