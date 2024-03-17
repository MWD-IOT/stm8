#include "SPI.h"
/***************************************************************************
*  Function: SPI_Initial			  								                        
*  Object:  ִ�г�ʼ��						  					             
*  ���룺 ��        		           																				
*  ����� ��				                                 			                
*  ��ע�� ��ģʽ �������� Ӳ��SPI sck	mosi misi 								                       
***************************************************************************/
void SPI_Initial(void)
{ 
                SPI_DeInit();
                CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, ENABLE); // CLK_PERIPHERAL_SPI
                
                GPIO_Init(GPIOC,GPIO_PIN_5|GPIO_PIN_6,GPIO_MODE_OUT_PP_HIGH_FAST);
                GPIO_Init(GPIOC,GPIO_PIN_7,GPIO_MODE_IN_PU_NO_IT);
                //����ͨ�Ų�����1Mbps,����״̬ʱ��SCK���ֵ͵�ƽ,���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ,ͨ��ʱ��
                //������λ����λ��ǰ����λ�ں�,NSS����������� 
                SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_32, SPI_MODE_MASTER, SPI_CLOCKPOLARITY_LOW, 
                         SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x07);
                SPI_Cmd(ENABLE);//ʹ��SPI   
                                //�˿�����Ϊ���ٰ���,
            //    GPIO_Init(GPIOC,GPIO_PIN_5|GPIO_PIN_6,GPIO_MODE_OUT_PP_HIGH_FAST);
            //    GPIO_Init(GPIOC,GPIO_PIN_7,GPIO_MODE_IN_PU_NO_IT);

}

/***************************************************************************
*  Function: SPI_Send			  								                       
*  Object:  SPI��������													  					             
*  ���룺 &DataBuff �������ݻ����ͷָ�룻DataLen �������ݵĸ�����       
*  ����� ��				                                 			                 
*  ��ע�� ��ģʽ �������� Ӳ��SPI sck	mosi misi 							                      
***************************************************************************/
void SPI_Send(u8 *DataBuff,u16 DataLen)
{
		//ִ�з���
		for(;DataLen>0;DataBuff++,DataLen--)
		{                                             
                        while(SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
                        SPI_SendData(*DataBuff);
		}
                while(SPI_GetFlagStatus(SPI_FLAG_BSY)== SET);
}

/***************************************************************************
*  Function: Driver_SPIReceive			  								                   
*  Object:  SPI��������													  					             
*  ���룺 &DataBuff �������ݻ����ͷָ�룻DataLen �������ݵĸ�����        
*  ����� ��				                                 			                 
*  ��ע�� ��ģʽ �������� Ӳ��SPI sck	mosi misi                     
***************************************************************************/
void SPI_Receive(u8 *DataBuff,u16 DataLen)
{
		//ִ�н���
		for(;DataLen>0;DataBuff++,DataLen--)
		{
			//�ȴ�����,�ȴ����ջ������ǿ�
                        while(!SPI_GetFlagStatus(SPI_FLAG_RXNE));
			//��������
			*DataBuff = SPI_ReceiveData();
                        
		}
		//�ȴ����߿��� 
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