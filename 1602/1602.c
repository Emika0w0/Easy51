/*//////////////////////////GPL��Դ���֤////////////////////////////////////////////////
    Copyright (C) <2014>  <Xianglong He>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	��Ȩ���У�C�� <2014>   <������>
	��һ����������������������������������������GNUͨ�ù������֤
	�������޸ĺ����·�����һ���������ʹ�����֤�ĵ����棬���ߣ�������
	��ѡ�����κθ��µİ汾��

	������һ�����Ŀ����ϣ�������ã���û���κε���������û���ʺ��ض�Ŀ��
	�������ĵ���������ϸ����������GNUͨ�ù������֤��

	��Ӧ���Ѿ��ͳ���һ���յ�һ��GNUͨ�ù������֤�ĸ����������û�У����
	��<http://www.gnu.org/licenses/>��
	���ߣ�������
	���䣺qwgg9654@gmail.com
		  568629794@qq.com
	2014��12��9��
	����������1602Һ������ʾ������
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////�ⲿ����//////////////////////////////////
extern void LCD1602_Clear();    //LCD1602����
extern void LCD1602_AreaClear(uint8 x,uint8 y,uint8 len);   //LCD1602��Χ������x�������꣬y�������꣬len���������ַ�����
extern void LCD1602_Show(uint8 x,uint8 y,uint8 *dat,uint8 len); //LCD1602��ʾ�ַ�����x�������꣬y�������꣬dat��Ҫ��ʾ���ַ����飬len��Ҫ��ʾ�ĳ��ȣ�
extern void LCD1602_Init(); //LCD1602��ʼ������������������ͷ���á�
extern void LCD1602_CloseCursor();	//�ر�LCD1602���
extern void LCD1602_ShowCursor();	//��LCD1602���
extern void LCD1602_SetLocation(uint8 x,uint8 y);	//����LCD1602���λ��
////////////////////////////////////////////////////////////*/
#include<reg51.h>
#include<intrins.h>
#define LCD1602_DB P0
sbit LCD1602_RS=P1^0;   //�����ʵ������޸�
sbit LCD1602_RW=P1^1;
sbit LCD1602_E=P1^5;
typedef unsigned char uint8;
typedef unsigned int uint16;
void Delay5ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 54;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}
void LCD1602_Wait()
{
	uint8 a;
	LCD1602_RS=0;
	LCD1602_RW=1;
	LCD1602_DB=0xFF;
	do
	{
		LCD1602_E=1;
		a=LCD1602_DB;
		LCD1602_E=0;
	}while(a&0x80);
}
void LCD1602_WriteData(uint8 dat)
{
	LCD1602_Wait();
	LCD1602_RW=0;
	LCD1602_RS=1;
	LCD1602_DB=dat;
	LCD1602_E=1;
	LCD1602_E=0;
}
void LCD1602_WriteCMD(uint8 cmd)
{
	LCD1602_Wait();
	LCD1602_RW=0;
	LCD1602_RS=0;
	LCD1602_DB=cmd;
	LCD1602_E=1;
	LCD1602_E=0;
}
void LCD1602_Clear()
{
	LCD1602_WriteCMD(0x01);
}
void LCD1602_SetLocation(uint8 x,uint8 y)
{
	uint8 temp;
	if(y==1)temp=0x40;
	else temp=0x00;
	temp+=x;
	LCD1602_WriteCMD(temp|0x80);
}
void LCD1602_AreaClear(uint8 x,uint8 y,uint8 len)
{
	LCD1602_SetLocation(x,y);
	while(len--)
	{
		LCD1602_WriteData(' ');
	}
}
void LCD1602_Show(uint8 x,uint8 y,uint8 *dat,uint8 len)
{
	LCD1602_SetLocation(x,y);
	while(len--)
	{
		LCD1602_WriteData(*dat++);
	}
}
void LCD1602_ShowCursor()
{
    LCD1602_WriteCMD(0x0F);
}
void LCD1602_CloseCursor()
{
    LCD1602_WriteCMD(0x0C);
}
void LCD1602_Init()
{
	LCD1602_WriteCMD(0x38);
	Delay5ms();
	LCD1602_WriteCMD(0x38);
	Delay5ms();
	LCD1602_WriteCMD(0x38);
	Delay5ms();
	LCD1602_WriteCMD(0x38);
	LCD1602_WriteCMD(0x0C);
	LCD1602_WriteCMD(0x06);
	LCD1602_WriteCMD(0x01);
}
