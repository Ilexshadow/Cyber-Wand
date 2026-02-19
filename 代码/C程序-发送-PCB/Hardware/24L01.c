#include "stm32f10x.h"
#include "24L01.h"
#include "spi.h"
#include "delay.h"
#include "stdio.h"
#include "gpio.h"





u8 TX_ADDRESS[5] = {0x34,0x43,0x10,0x10,0x01};//地址


u8 TX_data[8];//发送的数组




//SPI 发送两个字节，读和写  都用这个函数
u8 SPI_Write_Reg(u8 Reg,u8 data)
{
	u8 states;

	CSN_L;

	states = spi2_send_byte_fun(Reg);

	states = spi2_send_byte_fun(data);

	CSN_H;
	
	return states;
}







//2401初始化为发送模式
void TX_2401_init_send(void)
{
	CE_L;//低电平
	
	SPI_Write_Reg(WRITE_REG_24 + EN_AA,0x00);//关闭自动应答
	delay_us(10);
	
	SPI_Write_Reg(WRITE_REG_24 + SETUP_RETR,0x00);//
	delay_us(10);
	
	SPI_Write_Reg(WRITE_REG_24 + EN_RXADDR,0x01);//
	delay_us(10);
	
	SPI_Write_Reg(WRITE_REG_24 + RF_CH,1);//通讯的频率设置，和接收一样就行
	delay_us(10);
	
	SPI_Write_Reg(WRITE_REG_24 + RX_PW_P0,8);//每次发送8个字节
	delay_us(10);
	
	SPI_Write_Reg(WRITE_REG_24 + RF_SETUP,0x07);//发射功率设置
	delay_us(10);
	
	SPI_Write_Reg(WRITE_REG_24 + CONFIG_24,0x0e);//设置成发送模数
	delay_us(10);
	
	
	//设置发送地址
	CSN_L;
	delay_us(10);
	spi2_send_byte_fun(WRITE_REG_24 + TX_ADDR);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[0]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[1]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[2]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[3]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[4]);
	delay_us(10);
	CSN_H;
	
	
	//设置接收地址
	CSN_L;
	delay_us(10);
	spi2_send_byte_fun(WRITE_REG_24 + RX_ADDR_P0);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[0]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[1]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[2]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[3]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[4]);
	delay_us(10);
	CSN_H;
}



//初始化 发送的数据   默认是按键A的数据
void send_data_init(void)
{
	TX_data[0] = 0x00;
	TX_data[1] = 0x00;
	TX_data[2] = 0x04;
	TX_data[3] = 0x00;
	TX_data[4] = 0x00;
	TX_data[5] = 0x00;
	TX_data[6] = 0x00;
	TX_data[7] = 0x00;
}




//spi 发送数组
u8 SPI_Write_Buf(u8 Reg,u8 *Buf,u8 len)
{
    u8 states;

    CSN_L;

    states=spi2_send_byte_fun(Reg);

    while(len>0)
    {
        spi2_send_byte_fun(*Buf);
        Buf++;
        len--;
    }
		
    CSN_H;

    return states;
}




//2401  发送一组数据
void Send_2401(u8 dat)
{
	
	LED_L;//开灯
	
	//下面8个字节就是通过无线发送的8个字节，也就是USB按键的键值，关于USB按键协议，可以参考下面的网址
	//https://www.cnblogs.com/guyandianzi/p/9882644.html
	
	TX_data[0] = 0;
	TX_data[1] = 0;
	TX_data[2] = dat;
	TX_data[3] = 0;
	TX_data[4] = 0;
	TX_data[5] = 0;
	TX_data[6] = 0;
	TX_data[7] = 0;
	
	CE_L;
	SPI_Write_Buf(WR_TX_PLOAD,TX_data,8);//写发送的数据到2401
	SPI_Write_Reg(WRITE_REG_24 + CONFIG_24,0x0e);	//发送命令
	CE_H;//执行发送
	
	LED_H;//关灯
}




//用于调试2401，读一些状态寄存器，调试好了，就不用了
void  read_fun(void)
{
	u8 test_data1;
	u8 test_data2;
	
	test_data1 = SPI_Write_Reg(READ_REG_24 + STATUS,0x00);
	printf("STATUS = %02x\n",test_data1);
	
	
	test_data2 = SPI_Write_Reg(READ_REG_24 + FIFO_STATUS,0x00);
	printf("FIFO_STATUS = %02x\n",test_data2);
	
	
	if((test_data1==0x2E)&&(test_data2==0x11))
	{
		LED_F;
	}

}




//用于调试2401，读一些状态寄存器，调试好了，就不用了
void read_all_fun(void)
{
	u8 read_dat;
	
	
	read_dat = SPI_Write_Reg(EN_AA,0x00);
	printf("EN_AA = %02x\n",read_dat);
	
	read_dat = SPI_Write_Reg(SETUP_RETR,0x00);
	printf("SETUP_RETR = %02x\n",read_dat);
	
	read_dat = SPI_Write_Reg(EN_RXADDR,0x00);
	printf("EN_RXADDR = %02x\n",read_dat);
	
	read_dat = SPI_Write_Reg(RF_CH,0x00);
	printf("RF_CH = %02x\n",read_dat);
	
	read_dat = SPI_Write_Reg(RX_PW_P0,0x00);
	printf("RX_PW_P0 = %02x\n",read_dat);
	
	read_dat = SPI_Write_Reg(RF_SETUP,0x00);
	printf("RF_SETUP = %02x\n",read_dat);
	
	read_dat = SPI_Write_Reg(CONFIG_24,0x00);
	printf("CONFIG_24 = %02x\n",read_dat);
	
	printf("\n");
	

	CSN_L;
	delay_us(10);
	spi2_send_byte_fun(READ_REG_24 + TX_ADDR);
	delay_us(10);
	read_dat = spi2_send_byte_fun(0x00);
	printf("read_dat1 = %02x\n",read_dat);
	read_dat = spi2_send_byte_fun(0x00);
	printf("read_dat2 = %02x\n",read_dat);
	read_dat = spi2_send_byte_fun(0x00);
	printf("read_dat3 = %02x\n",read_dat);
	read_dat = spi2_send_byte_fun(0x00);
	printf("read_dat4 = %02x\n",read_dat);
	read_dat = spi2_send_byte_fun(0x00);
	printf("read_dat5 = %02x\n",read_dat);
	CSN_H;
	
	
	
	CSN_L;
	delay_us(10);
	spi2_send_byte_fun(READ_REG_24 + RX_ADDR_P0);
	delay_us(10);
	read_dat = spi2_send_byte_fun(0x00);
	printf("read_dat1 = %02x\n",read_dat);
	read_dat = spi2_send_byte_fun(0x00);
	printf("read_dat2 = %02x\n",read_dat);
	read_dat = spi2_send_byte_fun(0x00);
	printf("read_dat3 = %02x\n",read_dat);
	read_dat = spi2_send_byte_fun(0x00);
	printf("read_dat4 = %02x\n",read_dat);
	read_dat = spi2_send_byte_fun(0x00);
	printf("read_dat5 = %02x\n",read_dat);
	CSN_H;
	
	
}









