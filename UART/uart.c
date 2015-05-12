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

	�ļ�����UART.c
	���ߣ�������
	���䣺qwgg9654@gmail.com
		  admin@hxlxz.com
	���������������ַ���ͨ��ģ��
	��ע������ʹ�÷�װ�õĺ������в���������Ҫʹ��ֱ�ӶԴ��ڽ��в�����
*////////////////////////////////////////////////////////////////////////////////////////

	//2014��12��9��

#include<reg51.h>
#include<UART.h>

#ifndef BUFFMAX
#define BUFFMAX 64
#endif // ���û�ж���BUFFMAX����Ĭ��Ϊ64

extern void UART_Action(unsigned char *dat, unsigned char len);
//�˺��������б�д�����������һ���ַ�����������Զ�����
unsigned char pdata UART_Buff[BUFFMAX];     //���ڽ��ջ�����
unsigned char UART_BuffIndex = 0;           //���ڽ��ջ�������ǰλ��
bit UART_SendFlag;                          //���ڷ�����ɱ�־
bit UART_ResiveFlag;                        //���ڽ�����ɱ�־
bit UART_ResiveStringEndFlag;               //�����ַ�������ȫ����ɱ�־
bit UART_ResiveStringFlag;                  //�����ַ������ڽ��ձ�־

/*///////////////////////////////////////////////////////////////////////////////////
*��������UART_Conf
*�������ܣ����ô���
*�����б�
*   baud
*       �������ͣ�unsigned char������
*       ����������Ҫ���õĲ�����
*����ֵ����
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��9��
*////////////////////////////////////////////////////////////////////////////////////
void UART_Conf(unsigned int baud) //UART���ú�����buad�������õĲ����ʣ�
{
	TL1 = TH1 = 256 - 11059200 / 12 / 32 / baud;
	EA = 1;
	ES = 1;
	TMOD &= 0X0F;
	TMOD |= 0X20;
	SCON = 0X50;
	TR1 = 1;
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������UART_SendString
*�������ܣ��򴮿ڷ���һ���ַ���
*�����б�
*   *dat
*       �������ͣ�unsigned char��ָ��
*       ����������Ҫ���͵��ַ������׵�ַ
*   len
*       �������ͣ�unsigned char������
*       ����������Ҫ���͵��ַ����ĳ���
*����ֵ����
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��9��
*////////////////////////////////////////////////////////////////////////////////////
void UART_SendString(unsigned char *dat, unsigned char len)
{
	while(len)
	{
		len --;
		SBUF = *dat;
		dat ++;
		while(! UART_SendFlag);
		UART_SendFlag = 0;
	}
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������UART_Driver
*�������ܣ�����ͨ�ż�غ���������ѭ���е��á�
*           ������յ��ַ��������Զ��������б�д��UART_Action(unsigned char *dat,unsigned char len)
*�����б�
*   ��
*����ֵ����
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��9��
*////////////////////////////////////////////////////////////////////////////////////
void UART_Driver()//
{
	unsigned char pdata dat[BUFFMAX];
	unsigned char len;
	if(UART_ResiveStringEndFlag)
		{
			UART_ResiveStringEndFlag = 0;
			len = UART_Read(dat, BUFFMAX);
			UART_Action(dat, len);
		}
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������UART_RxMonitor
*�������ܣ������ַ������ս����жϣ��ڶ�ʱ���е���
*�����б�
*   ms
*       �������ͣ�unsigned char������
*       ������������ʱ����ʱʱ������λ��ms��
*����ֵ����
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��9��
*////////////////////////////////////////////////////////////////////////////////////
void UART_RxMonitor(unsigned char ms)
{
	static unsigned char ms30 = 0, UART_BuffIndex_Backup;
	ms30 += ms;
	if(! UART_ResiveStringFlag)return ;
	if(UART_BuffIndex_Backup != UART_BuffIndex)
	{
		UART_BuffIndex_Backup = UART_BuffIndex;
		ms30 = 0;
	}
	if(ms30 > 30)
		{
			ms30 = 0;
			UART_ResiveStringEndFlag = 1;
			UART_ResiveStringFlag = 0;
		}
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������UART_Read
*�������ܣ����ݴ������е����ݶ�ȡ������
*�����б�
*   *to
*       �������ͣ�unsigned char��ָ��
*       �����������洢���յ����ַ���λ��
*   len
*       �������ͣ�unsigned char������
*       ����������Ҫ��ȡ���ַ����ĳ���
*����ֵ��unsigned char�����ݣ��ַ�����ʵ�ʳ���
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��9��
*////////////////////////////////////////////////////////////////////////////////////
unsigned char UART_Read(unsigned char *to, unsigned char len)
{
	unsigned char i;
	if(UART_BuffIndex < len)len = UART_BuffIndex;
	for(i = 0;i < len;i ++)
		{
			*to = UART_Buff[i];
			to ++;
		}
	UART_BuffIndex = 0;
	return len;
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������interrupt_UART
*�������ܣ������жϺ���
*�����б�
*   ��
*����ֵ����
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��9��
*////////////////////////////////////////////////////////////////////////////////////
void interrupt_UART() interrupt 4
{
	if(TI)
	{
		TI = 0;
		UART_SendFlag = 1;
	}
	if(RI)
	{
		RI = 0;
		UART_ResiveFlag = 1;
		UART_Buff[UART_BuffIndex] = SBUF;
		UART_ResiveStringFlag = 1;
		UART_BuffIndex ++;
	}
}
