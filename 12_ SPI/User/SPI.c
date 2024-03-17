#include "SPI.h"
/***************************************************************************
*  Function: SPI_Initial			  								                        
*  Object:  执行初始化						  					             
*  输入： 无        		           																				
*  输出： 无				                                 			                
*  备注： 主模式 四线连接 硬件SPI sck	mosi misi 								                       
***************************************************************************/
void SPI_Initial(void)
{ 
                SPI_DeInit();
                CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, ENABLE); // CLK_PERIPHERAL_SPI
                
                GPIO_Init(GPIOC,GPIO_PIN_5|GPIO_PIN_6,GPIO_MODE_OUT_PP_HIGH_FAST);
                GPIO_Init(GPIOC,GPIO_PIN_7,GPIO_MODE_IN_PU_NO_IT);
                //配置通信波特率1Mbps,空闲状态时，SCK保持低电平,数据采样从第一个时钟边沿开始,通信时，
                //串行移位，高位在前，低位在后,NSS引脚软件管理 
                SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_32, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_LOW, 
                         SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x07);
                SPI_Cmd(ENABLE);//使能SPI   
                                //端口配置为快速摆率,
            //    GPIO_Init(GPIOC,GPIO_PIN_5|GPIO_PIN_6,GPIO_MODE_OUT_PP_HIGH_FAST);
            //    GPIO_Init(GPIOC,GPIO_PIN_7,GPIO_MODE_IN_PU_NO_IT);

}

/***************************************************************************
*  Function: SPI_Send			  								                       
*  Object:  SPI发送数据													  					             
*  输入： &DataBuff 发送数据缓存的头指针；DataLen 发送数据的个数；       
*  输出： 无				                                 			                 
*  备注： 主模式 四线连接 硬件SPI sck	mosi misi 							                      
***************************************************************************/
void SPI_Send(u8 *DataBuff,u16 DataLen)
{
		//执行发送
		for(;DataLen>0;DataBuff++,DataLen--)
		{                                             
                        while(SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
                        SPI_SendData(*DataBuff);
		}
                while(SPI_GetFlagStatus(SPI_FLAG_BSY)== SET);
}

/***************************************************************************
*  Function: Driver_SPIReceive			  								                   
*  Object:  SPI接收数据													  					             
*  输入： &DataBuff 接收数据缓存的头指针；DataLen 接收数据的个数；        
*  输出： 无				                                 			                 
*  备注： 主模式 四线连接 硬件SPI sck	mosi misi                     
***************************************************************************/
void SPI_Receive(u8 *DataBuff,u16 DataLen)
{
		//执行接收
		for(;DataLen>0;DataBuff++,DataLen--)
		{
			//等待接收,等待接收缓冲区非空
                        while(!SPI_GetFlagStatus(SPI_FLAG_RXNE));
			//接收数据
			*DataBuff = SPI_ReceiveData();
                        
		}
		//等待总线空闲 
                while(SPI_GetFlagStatus(SPI_FLAG_BSY)== SET);
}




void SPI_Write(u8 addr,u8 *dat,u8 num)//
{
SPI_CS_L;
IO_Rst_L;
SPI_Send(&addr,1);



SPI_Send(dat,num);

SPI_CS_H;
IO_Rst_H;

}


void SPI_Read(u8 addr,u8 num,u8 *Rec_dat)//
{

SPI_CS_L;
IO_Rst_L;
SPI_Send(&addr,1);


SPI_Receive(Rec_dat,num);

SPI_CS_H;
IO_Rst_H;

}