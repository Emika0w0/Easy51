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

	�ļ�����UART.h
	���ߣ�������
	���䣺qwgg9654@gmail.com
		  admin@hxlxz.com
	���������������ַ���ͨ��ģ��-ͷ�ļ�
	��ע������ʹ�÷�װ�õĺ������в���������Ҫʹ��ֱ�ӶԴ��ڽ��в�����
*////////////////////////////////////////////////////////////////////////////////////////
#ifndef _HEAD_UART_
#define _HEAD_UART_

#include<intrins.h>
#include<config.h>
void UART_RxMonitor(uint8 ms)//UART�ַ������ս����жϡ��ڶ�ʱ���е��ã�ms����ʱ��ʱ�����ڣ�
void UART_Driver()//UARTͨ�ż�غ���������ѭ���е��á�������յ��ַ��������Զ��������б�д��UART_Action(uint8 *dat,uint8 len)
void UART_SendString(uint8 *dat,uint8 len)  //����ͨ�ţ�����һ���ַ�����dat��Ҫ���͵��ַ�����len���ַ������ȣ�
void UART_Conf(uint16 baud) //UART���ú�����buad�������õĲ����ʣ�
#endif // _HEAD_UART_
