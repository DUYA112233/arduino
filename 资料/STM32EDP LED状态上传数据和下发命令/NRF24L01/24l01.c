#include "24l01.h"
#include "lcd.h"
#include "delay.h"
#include "spi.h"
#include "EEPROM.H"
#include "ds1302.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//NRF24L01 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/16 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 
	 

const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
u8 RXdate[6]={0,0,0,0,0,0};            //���յ���5λ���ݴ��������      

u8 CardKeep[6]={0,0,0,0,0,0};                            //����NRF���յ����ŵ�����,����λΪ���ڴ���
u8 Cardjudge[6]={0,0,0,0,0,0};                           //�����жϴ��ȥ�Ŀ����Ƿ�ɹ�	
u8 Cardjudge1[6]={0,0,0,0,0,0};                                     //���ڴ�������Ŀ�������
 u16 Cardnum;  //Ŀǰӵ�еĿ���
//��ʼ��24L01��IO��
void NRF24L01_Init(void)
{
	
	/*RCC->APB2ENR|=1<<2;    //ʹ��PORTA��ʱ�� 
	RCC->APB2ENR|=1<<4;    //ʹ��PORTC��ʱ�� 
	GPIOA->CRL&=0XFFF000FF;//PA4���
	GPIOA->CRL|=0X00033300; 
	GPIOA->ODR|=7<<2;	   //PA2.3.4 ���1		 
	GPIOC->CRL&=0XFF00FFFF;//PC4��� PC5���
	GPIOC->CRL|=0X00830000; 
	GPIOC->ODR|=3<<4;	   //����	*/ 
	SPI2_Init();    //��ʼ��SPI
	NRF24L01_CE=0; 	//ʹ��24L01
	NRF24L01_CSN=1;	//SPIƬѡȡ��	
  
 
}
//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	SPI2_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��   	 
	NRF24L01_Write_Buf(N_WRITE_REG+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//���24L01����	
	return 0;		 //��⵽24L01
}	 	 
//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
u8 NRF24L01_Write_Reg(u8 reg,u8 value)
{
	u8 status;	
   	NRF24L01_CSN=0;                 //ʹ��SPI����
  	status =SPI2_ReadWriteByte(reg);//���ͼĴ����� 
  	SPI2_ReadWriteByte(value);      //д��Ĵ�����ֵ
  	NRF24L01_CSN=1;                 //��ֹSPI����	   
  	return(status);       			//����״ֵ̬
}
//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���
u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val;	    
 	NRF24L01_CSN = 0;          //ʹ��SPI����		
  	SPI2_ReadWriteByte(reg);   //���ͼĴ�����
  	reg_val=SPI2_ReadWriteByte(0XFF);//��ȡ�Ĵ�������
  	NRF24L01_CSN = 1;          //��ֹSPI����		    
  	return(reg_val);           //����״ֵ̬
}	
//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
	u8 status,u8_ctr;	       
  	NRF24L01_CSN = 0;           //ʹ��SPI����
  	status=SPI2_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
 	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI2_ReadWriteByte(0XFF);//��������
  	NRF24L01_CSN=1;       //�ر�SPI����
  	return status;        //���ض�����״ֵ̬
}
//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status,u8_ctr;	    
 	NRF24L01_CSN = 0;          //ʹ��SPI����
  	status = SPI2_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI2_ReadWriteByte(*pBuf++); //д������	 
  	NRF24L01_CSN = 1;       //�ر�SPI����
  	return status;          //���ض�����״ֵ̬
}				   
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
 	SPI2_SetSpeed(SPI_BaudRatePrescaler_8);//spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��   
	NRF24L01_CE=0;
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
 	NRF24L01_CE=1;//��������	   
	while(NRF24L01_IRQ!=0);//�ȴ��������
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_Write_Reg(N_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&MAX_TX)//�ﵽ����ط�����
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}
	if(sta&TX_OK)//�������
	{
		return TX_OK;
	}
	return 0xff;//����ԭ����ʧ��
}
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:0��������ɣ��������������
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							   
	SPI2_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��   
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ    	 
	NRF24L01_Write_Reg(N_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&RX_OK)//���յ�����
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//���RX FIFO�Ĵ��� 
		return 0; 
	}	   
	return 1;//û�յ��κ�����
}					    
//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
void RX_Mode(void)
{
	NRF24L01_CE=0;	  
  	NRF24L01_Write_Buf(N_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	  
  	NRF24L01_Write_Reg(N_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
  	NRF24L01_Write_Reg(N_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  	 
  	NRF24L01_Write_Reg(N_WRITE_REG+RF_CH,40);	     //����RFͨ��Ƶ��		  
  	NRF24L01_Write_Reg(N_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 	    
  	NRF24L01_Write_Reg(N_WRITE_REG+RF_SETUP,0x0f);//����TX�������,0db����,2Mbps,���������濪��   
  	NRF24L01_Write_Reg(N_WRITE_REG+CONFIG, 0x0f);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
  	NRF24L01_CE = 1; //CEΪ��,�������ģʽ 
}						 
//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
//CEΪ�ߴ���10us,����������.	 
void TX_Mode(void)
{														 
	NRF24L01_CE=0;	    
  	NRF24L01_Write_Buf(N_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
  	NRF24L01_Write_Buf(N_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  

  	NRF24L01_Write_Reg(N_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
  	NRF24L01_Write_Reg(N_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
  	NRF24L01_Write_Reg(N_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
  	NRF24L01_Write_Reg(N_WRITE_REG+RF_CH,40);       //����RFͨ��Ϊ40
  	NRF24L01_Write_Reg(N_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
  	NRF24L01_Write_Reg(N_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF24L01_CE=1;//CEΪ��,10us����������
}		  

/*******************************���淢�����Ŀ��ŵ�Flash********************************/
/*** �������Ŀ�����������λ���ݣ�����λ�������ÿ��¼һ�����ݾͰѿ���Cardnum+1************/
u16 KeepCard(u16 Cardnum,u8 *Cardkeep)
{
	 u16 i=0,flag=0;


 Flash_write(USER_ADDR+Cardnum*2,(u32 *)Cardkeep, 5);        //�����͹����Ŀ������浽Flash
 Flash_read(USER_ADDR+Cardnum*2 ,(u32 *)Cardjudge, 5);
 for(i=0;i<5;i++)
  {  
		if(Cardjudge[i]!=Cardkeep[i])                  //�ж϶����������ݺ�д��ȥ�������Ƿ�һ��
		{
		  
			flag=0;
			break;                                      //ֻ��Ҫ�жϵ�һ�����ݲ�һ���Ϳ����ж��ж���
		}
		else flag=1;                                  //���д��Ŀ��źͶ������Ŀ���һģһ�� �򷵻�1 ���򷵻�0
	}

	
	return flag;
}
/******************************NRF��⺯��********************************/
/************************����ʵʱ�������ݲ�����****************************/
void NRFChecking()
{   
  	u16 flag=0,i=0,j=0,sign=0;     //�ж��Ƿ�д��ɹ��ı�־
	  RX_Mode();     //�򿪽���ģʽ��ʹNRF���ڴ��ڽ�������״̬ 
    NRF24L01_RxPacket(RXdate);  //���յ������ݴ浽RXdate��������
	 if(RXdate[4]==KeepCardSign)   //ע��ģʽ�ı�־ ��������������ע��Ŀ���
	 {
	  
		 flag=KeepCard(Cardnum,RXdate);  //д����յ�������  д��ɹ�����1 ʧ�ܷ���0
		 	if(flag==0)
	   {
		   printf("д�뿨��ʧ��");
	   }
	   else printf("���ż�¼�ɹ�") ; 
		 
		 Cleandate();//������黺��
		 Cardnum=Cardnum+1;                  //ע�Ῠ�ųɹ� �������ݼ�1
	  
	 }
	 
	if(RXdate[4]==Normalmode)          //��������ģʽ ��¼���ſ���
	{
		for(i=0;i<Cardnum;i++)           //���ſ����ж� �ж�����һ�ſ�����Ϣ
		{
			Flash_read(USER_ADDR+i*2 ,(u32 *)Cardjudge1, 6);       //���ſ���ȡ Ȼ���ж� �жϵ�i�ſ�
		 for(j=0;j<4;j++)                            
			{
				if(RXdate[j]==Cardjudge1[j])                  //������Ŷ�����һ�� sign���Լ�һ�� ��sign����4�ε�ʱ�� ֤�����ſ�����һģһ����
				{
				   sign++;
				}
				if(sign==4)	                                  //sign����4 ����ֹ����
				{
				  Flash_read(USER_ADDR+i*4 ,(u32 *)Cardjudge1, 6);    //�ٴζ����жϺõĿ���
          Cardjudge1[5]=Cardjudge1[5]+1;               //����ĵ���λ�������ǿ��ڵĴ��� 
          Flash_write(USER_ADDR+i*4,(u32 *)Cardjudge1, 6);  //������������д��Flash ��ʱ���ڴ����Ѿ���1	
					 Recordtime(i);
          Cleandate();					
				}
				
			}
		}
		
		
	}
		 
	  
}

/*********************************��ջ���ĺ���*******************************/
void Cleandate(void)               //�������д�����ݺ������;
{

  u16 i=0;
	for(i=0;i<6;i++)
	{	
  	RXdate[i]=0;   //������������
		CardKeep[i]=0;
		Cardjudge[i]=0;
		Cardjudge1[i]=0;
	}

}

