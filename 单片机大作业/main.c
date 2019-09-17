#include<reg51.h>
#include<intrins.h>
#include"XPT2046.h"

sbit IRIN=P3^2;
sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;

#define COMMONPORTS		P0


unsigned char IrValue[6];
unsigned char Time;
void IrInit();
void DelayMs(unsigned int );
/*******************************************************************************
* 函数名         : main
* 函数功能		   : 主函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

//--列选通控制--//
unsigned char code TAB[8]  = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

//--点阵字码--//
unsigned char code CHARCODE1[18][8]=
{

{0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00}, //0

{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00}, //1

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00}, //2

{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, //3

};
unsigned char code CHARCODE2[18][8]=
{
{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, 

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00},

{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00}, 

{0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00}, //0

};
unsigned char code CHARCODE3[65][8]=
{

{0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00}, //0

{0x00,0x00,0x00,0x08,0x08,0x00,0x00,0x00}, //1

{0x00,0x00,0x00,0x18,0x08,0x00,0x00,0x00}, //2

{0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00}, //3

{0x00,0x00,0x00,0x18,0x18,0x10,0x00,0x00}, //3

{0x00,0x00,0x00,0x18,0x18,0x18,0x00,0x00}, //3

{0x00,0x00,0x00,0x18,0x18,0x1C,0x00,0x00}, //3

{0x00,0x00,0x00,0x18,0x1C,0x1C,0x00,0x00}, //3

{0x00,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x00}, //3

{0x00,0x00,0x04,0x1C,0x1C,0x1C,0x00,0x00}, //3

{0x00,0x00,0x0C,0x1C,0x1C,0x1C,0x00,0x00}, //3

{0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x00,0x00}, //3

{0x00,0x00,0x3C,0x1C,0x1C,0x1C,0x00,0x00}, //3

{0x00,0x00,0x3C,0x3C,0x1C,0x1C,0x00,0x00}, //3

{0x00,0x00,0x3C,0x3C,0x3C,0x1C,0x00,0x00}, //3

{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00}, //3

{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x20,0x00}, //3

{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x30,0x00}, //3

{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x38,0x00}, //3

{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x3C,0x00}, //3

{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x3E,0x00}, //3

{0x00,0x00,0x3C,0x3C,0x3C,0x3E,0x3E,0x00}, //3

{0x00,0x00,0x3C,0x3C,0x3E,0x3E,0x3E,0x00}, //3

{0x00,0x00,0x3C,0x3E,0x3E,0x3E,0x3E,0x00}, //3

{0x00,0x00,0x3E,0x3E,0x3E,0x3E,0x3E,0x00}, //3

{0x00,0x02,0x3E,0x3E,0x3E,0x3E,0x3E,0x00}, //3

{0x00,0x06,0x3E,0x3E,0x3E,0x3E,0x3E,0x00}, //3

{0x00,0x06,0x3E,0x3E,0x3E,0x3E,0x3E,0x00}, //0

{0x00,0x0E,0x3E,0x3E,0x3E,0x3E,0x3E,0x00}, //1

{0x00,0x1E,0x3E,0x3E,0x3E,0x3E,0x3E,0x00}, //2

{0x00,0x3E,0x3E,0x3E,0x3E,0x3E,0x3E,0x00}, //3

{0x00,0x7E,0x3E,0x3E,0x3E,0x3E,0x3E,0x00}, //3

{0x00,0x7E,0x7E,0x3E,0x3E,0x3E,0x3E,0x00}, //3

{0x00,0x7E,0x7E,0x7E,0x3E,0x3E,0x3E,0x00}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x3E,0x3E,0x00}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x3E,0x00}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x00}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x40}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x60}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x70}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x78}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7C}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7E,0x7F}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x7E,0x7F,0x7F}, //3

{0x00,0x7E,0x7E,0x7E,0x7E,0x7F,0x7F,0x7F}, //3

{0x00,0x7E,0x7E,0x7E,0x7F,0x7F,0x7F,0x7F}, //3

{0x00,0x7E,0x7E,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0x00,0x7E,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0x00,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0x01,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0x03,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0x07,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0x0F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0x1F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0x3F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0xFF,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0x7F}, //3

{0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F}, //3

{0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F}, //3

{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F}, //3

{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F}, //3

{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF} //3

};

unsigned char code CHARCODE4[18][8]=
{
{0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00}, //0

{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00},


};

unsigned char code CHARCODE5[18][8]=
{
{0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00}, 

{0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00},


};

void delay(unsigned int time)
{
  unsigned int i,j;
  for(i=0;i<time;i++)
    for(j=0;j<121;j++);
}

/*******************************************************************************
* 函数名         : Hc595SendByte(unsigned char dat)
* 函数功能		   : 想74H595发送一个字节的数据
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Hc595SendByte(unsigned char dat)
{
	unsigned char a;
	SRCLK=0;
	RCLK=0;
	for(a=0;a<8;a++)
	{
		SER=dat>>7;
		dat<<=1;

		SRCLK=1;
		_nop_();
		_nop_();
		SRCLK=0;	
	}

	RCLK=1;
	_nop_();
	_nop_();
	RCLK=0;
}

void main()
{
	unsigned char i;
	unsigned char tab, j;
	uint temp;
	IrInit();	
	while(1)
	{
		temp = Read_AD_Data(0xA4);		//   AIN2 光敏电阻

	  	if(temp > 70){
			IrValue[5]=IrValue[2]&0x0f;		//低位	
			if(IrValue[5] == 6) {
				for(j = 0;j < 4; j++){
					for(i=0;i<30;i++){
						for(tab=0;tab<8;tab++)
							{	
							Hc595SendByte(0x00);			     //消隐																
							COMMONPORTS	= TAB[tab];				 //输出字码	
							Hc595SendByte(CHARCODE1[j][tab]);	
							delay(2);		
							}
						}	
				}	
			}
			if(IrValue[5] == 12) {
				for(j = 0;j < 4; j++){
					for(i=0;i<30;i++){
						for(tab=0;tab<8;tab++)
							{	
							Hc595SendByte(0x00);			     //消隐																
							COMMONPORTS	= TAB[tab];				 //输出字码	
							Hc595SendByte(CHARCODE2[j][tab]);	
							delay(2);		
							}
						}	
				}	
			}
			if(IrValue[5] == 8) {
				for(j = 0;j < 65; j++){
					for(i=0;i<5;i++){
						for(tab=0;tab<8;tab++)
							{	
							Hc595SendByte(0x00);			     //消隐																
							COMMONPORTS	= TAB[tab];				 //输出字码	
							Hc595SendByte(CHARCODE3[j][tab]);	
							delay(2);		
							}
						}	
				}	
			}
			if(IrValue[5] == 14) {
				for(j = 65;j > 0; j--){
					for(i=0;i<5;i++){
						for(tab=0;tab<8;tab++)
							{	
							Hc595SendByte(0x00);			     //消隐																
							COMMONPORTS	= TAB[tab];				 //输出字码	
							Hc595SendByte(CHARCODE3[j-1][tab]);	
							delay(2);		
							}
						}	
				}	
			}			
		
		}
		else{
			IrValue[5]=IrValue[2]&0x0f;		//低位	
			if(IrValue[5] == 6) {
				for(j = 0;j < 2; j++){
					for(i=0;i<30;i++){
						for(tab=0;tab<8;tab++)
							{	
							Hc595SendByte(0x00);			     //消隐																
							COMMONPORTS	= TAB[tab];				 //输出字码	
							Hc595SendByte(CHARCODE4[j][tab]);	
							delay(2);		
							}
						}	
				}	
			}
			if(IrValue[5] == 12) {
				for(j = 0;j < 2; j++){
					for(i=0;i<30;i++){
						for(tab=0;tab<8;tab++)
							{	
							Hc595SendByte(0x00);			     //消隐																
							COMMONPORTS	= TAB[tab];				 //输出字码	
							Hc595SendByte(CHARCODE5[j][tab]);	
							delay(2);		
							}
						}	
				}	
			}
			if(IrValue[5] == 8) {
				for(j = 0;j < 16; j++){
					for(i=0;i<5;i++){
						for(tab=0;tab<8;tab++)
							{	
							Hc595SendByte(0x00);			     //消隐																
							COMMONPORTS	= TAB[tab];				 //输出字码	
							Hc595SendByte(CHARCODE3[j][tab]);	
							delay(2);		
							}
						}	
				}	
			}
			if(IrValue[5] == 14) {
				for(j = 16;j > 0; j--){
					for(i=0;i<5;i++){
						for(tab=0;tab<8;tab++)
							{	
							Hc595SendByte(0x00);			     //消隐																
							COMMONPORTS	= TAB[tab];				 //输出字码	
							Hc595SendByte(CHARCODE3[j-1][tab]);	
							delay(2);		
							}
						}	
				}	
			}			
		
		}


	}
}									 
/*******************************************************************************
* 函数名         : DelayMs()
* 函数功能		   : 延时
* 输入           : x
* 输出         	 : 无
*******************************************************************************/

void DelayMs(unsigned int x)   //0.14ms误差 0us
{
 unsigned char i;
  while(x--)
 {
  for (i = 0; i<13; i++)
 {}
 }
}
/*******************************************************************************
* 函数名         : IrInit()
* 函数功能		   : 初始化红外线接收
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void IrInit()
{
	IT0=1;//下降沿触发
	EX0=1;//打开中断0允许
	EA=1;	//打开总中断

	IRIN=1;//初始化端口
}
/*******************************************************************************
* 函数名         : ReadIr()
* 函数功能		   : 读取红外数值的中断函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void ReadIr() interrupt 0
{
	unsigned char j,k;
	unsigned int err;
	Time=0;					 
	DelayMs(70);

	if(IRIN==0)		//确认是否真的接收到正确的信号
	{	 
		
		err=1000;				//1000*10us=10ms,超过说明接收到错误的信号
		/*当两个条件都为真是循环，如果有一个条件为假的时候跳出循环，免得程序出错的时
		侯，程序死在这里*/	
		while((IRIN==0)&&(err>0))	//等待前面9ms的低电平过去  		
		{			
			DelayMs(1);
			err--;
		} 
		if(IRIN==1)			//如果正确等到9ms低电平
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //等待4.5ms的起始高电平过去
			{
				DelayMs(1);
				err--;
			}
			for(k=0;k<4;k++)		//共有4组数据
			{				
				for(j=0;j<8;j++)	//接收一组数据
				{

					err=60;		
					while((IRIN==0)&&(err>0))//等待信号前面的560us低电平过去
//					while (!IRIN)
					{
						DelayMs(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //计算高电平的时间长度。
					{
						DelayMs(1);//0.14ms
						Time++;
						err--;
						if(Time>30)
						{
							EX0=1;
							return;
						}
					}
					IrValue[k]>>=1;	 //k表示第几组数据
					if(Time>=8)			//如果高电平出现大于565us，那么是1
					{
						IrValue[k]|=0x80;
					}
					Time=0;		//用完时间要重新赋值							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			return;
		}
	}			
}