/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/*******************************************************************************************************
*  Function: IIC_Initial						                                                           
*  Object: ��I2Cģ�飬��ִ�г�ʼ��	
*  ���룺 ��
*  ����� ��	   	                                     
*  ��ע�� ��ģʽ �������� Ӳ��I2C  7λ��ַģʽ I2C����Ѱַ��ʽͨ�� ʱ��ϸ��� Ҳ�����ڶ��豸ͨ��  
*         10Kbps ͨ������
********************************************************************************************************/
void IIC_Initial(void)
{ 
                CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, ENABLE);//��������ʱ��
                //��׼ģʽ��100kbits��  , ��Ӧ��7λ�ӵ�ַ���ȡ�2M����ʱ��Ƶ��
                I2C_Init(I2C_Speed, I2C1_SLAVE_ADDRESS7, I2C_DUTYCYCLE_2, I2C_ACK_NONE, I2C_ADDMODE_7BIT, CLK_GetClockFreq()/1000000);
                I2C_Cmd(ENABLE);//����I2C
}


/********************************************************************************************************
*  Function: IIC_OFF						                                                           
*  Object: �ر�I2Cģ��	
*  ���룺 ��
*  ����� ��	   	                                     
*  ��ע:  ��
********************************************************************************************************/
void IIC_OFF(void)
{ 
		u16 time;
		//�ȴ����߿��� ��ʱ���ٵȴ�
		time = 500;
		while(I2C_GetFlagStatus(I2C_FLAG_BUSBUSY) || --time);
		//�ر�I2Cģ��
                I2C_Cmd(DISABLE);
		//��I2Cʱ��
                CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE);
}

/********************************************************************************************************
*  Function: IIC_Write8						                                                           
*  Object: Ӳ��I2C����
*  ���룺 ���豸��ַ��д�Ĵ�����ʼ��ַ�����������ݵ�ͷָ�룻�������ݵĳ��� 
*  ����� ��  	                                     
*  ��ע:  ͨ����������ֳ�ʱ���� ��ֱ�ӷ��� ���ⳤ�ȴ�
********************************************************************************************************/
void IIC_Write8(u8 Dev_addr,u8 WriteAddr,u8 *DataBuff,u16 DataLen)
{  	
		u16 time;
		//�ȴ����߿���
		time = 500;
		while(I2C_GetFlagStatus(I2C_FLAG_BUSBUSY))
			if(!--time) 
				return;
				
		//����ʼ����
                I2C_GenerateSTART(ENABLE);               
                // ����EV5 ��
                while(!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));		
		//���ӵ�ַ
                I2C_Send7bitAddress(Dev_addr, I2C_DIRECTION_TX);//���豸��ַ����

		//�ȴ�ACKӦ��
		time = 500;
                //* ����EV6�������־λ��������������һ��Ӧ���ź� */
                while(!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
			if(!--time) 
				return;
                //����д�Ĵ�����ַ
                I2C_SendData(WriteAddr);
                /* Test on EV8 and clear it */
                while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));

		//��������
		for(;DataLen>0;DataLen--,DataBuff++)
		{
                                while( !I2C_GetFlagStatus(I2C_FLAG_TXEMPTY));//�ȴ��Ĵ���Ϊ��

                                I2C_SendData(*DataBuff);//��������
                                //�ȴ��������
                                while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		}
	
		//��ֹͣ����,�ر�ͨ��
                I2C_GenerateSTOP(ENABLE);
}

/********************************************************************************************************
*  Function: IIC_Recv8						                                                           
*  Object: Ӳ��I2C���� 
*  ���룺 ���豸��ַ�����������ݵ�ͷָ�룻�������ݵĳ���
*  ����� �� 	                                     
*  ��ע:  ͨ����������ֳ�ʱ���� ��ֱ�ӷ��� ���ⳤ�ȴ�
********************************************************************************************************/
void IIC_Recv8(u8 Dev_addr,u8 Read_addr,u8 *DataBuff,u16 DataLen)
{  	

	u16 time;
		//�ȴ����߿���
		time = 500;
		while(I2C_GetFlagStatus(I2C_FLAG_BUSBUSY))
			if(!--time) 
				return;
				
		//����ʼ����
                I2C_GenerateSTART(ENABLE);               
                // ����EV5 ��
                while(!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));		
		//���ӵ�ַ
                I2C_Send7bitAddress(Dev_addr, I2C_DIRECTION_TX);//���豸��ַ����

		//�ȴ�ACKӦ��
		time = 500;
                //* ����EV6�������־λ��������������һ��Ӧ���ź� */
                while(!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
			if(!--time) 
				return;
                //����д�Ĵ�����ַ
                I2C_SendData(Read_addr);
                /* Test on EV8 and clear it */
                while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));
                
                time = 500;
		while(I2C_GetFlagStatus(I2C_FLAG_BUSBUSY))
			if(!--time)
				return;
                   //�ٷ���ʼλ��
                I2C_GenerateSTART(ENABLE);
                while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));
                asm("nop");
		asm("nop");
		asm("nop");

                //���ʹӵ�ַ����ģʽ�������ģʽ
                I2C_Send7bitAddress(Dev_addr+1, I2C_DIRECTION_RX);
                time = 500;
                while (!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
                  
		//��������,��DataLen-1����
		//��ȡ���������ǣ�����ʹ��ACKӦ��
                I2C_AcknowledgeConfig(I2C_ACK_CURR);
		for(;DataLen>1;DataLen--,DataBuff++)
		{
			//�ȴ��Ĵ���Ϊ��
                        time = 500;
                        while(!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_RECEIVED))
                          if(!--time)
				return;
			*DataBuff = I2C_ReceiveData();
		}
                //�ر�ACKӦ��
               I2C_AcknowledgeConfig(I2C_ACK_NONE);
	
		//��ֹͣ����,�ر�ͨ��
                I2C_GenerateSTOP(ENABLE);
                asm("nop");
		asm("nop");
		asm("nop");
	
		//�����һ����
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
