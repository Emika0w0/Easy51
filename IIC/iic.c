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

	�ļ�����IIC.c
	���ߣ�������
	���䣺qwgg9654@gmail.com
		  admin@hxlxz.com
	�����������õ�Ƭ��IO��ģ��ʵ��IICͨ��
	��ע��ʹ�ø�ģ�飬���ڳ����ж���IIC_SDA����ΪIIC���ߵ�SDA���ݽӿڡ�
          �� #define IIC_SDA_SET P0^0
          ʹ�ø�ģ�飬���ڳ����ж���IIC_SCL����ΪIIC���ߵ�SCL���ݽӿڡ�
          �� #define IIC_SCL_SET P0^1
*////////////////////////////////////////////////////////////////////////////////////////
#include<reg51.h>
#include<IIC.h>

#define IICDelay() {nop_();nop_();nop_();nop_();}
//IICͨ���еļ���ʱ

sbit IIC_SDA = IIC_SDA_SET;
sbit IIC_SCL = IIC_SCL_SET;

/*///////////////////////////////////////////////////////////////////////////////////
*��������IIC_Start
*�������ܣ�����IIC������ʼ�ź�
*�����б�
*   ��
*����ֵ����
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��9��
*��ע�����ں�����Լ��׶��������ṩ��ϸע��
*////////////////////////////////////////////////////////////////////////////////////
void IIC_Start()
{
	IIC_SCL = 0;
	IICDelay();
	IIC_SDA = 1;
	IICDelay();
	IIC_SCL = 1;
	IICDelay();
	IIC_SDA = 0;
	IICDelay();
	IIC_SCL = 0;
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������IIC_Stop
*�������ܣ�����IIC����ֹͣ�ź�
*�����б�
*   ��
*����ֵ����
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��9��
*��ע�����ں�����Լ��׶��������ṩ��ϸע��
*////////////////////////////////////////////////////////////////////////////////////
void IIC_Stop()
{
	IIC_SCL = 0;
	IICDelay();
	IIC_SDA = 0;
	IICDelay();
	IIC_SCL = 1;
	IICDelay();
	IIC_SDA = 1;
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������IIC_Write
*�������ܣ���IIC���߷���һ��unsigned char������
*�����б�
*   dat
*       �������ͣ�unsigned char������
*       ����������Ҫ���͵�����
*����ֵ��һ��bit�������Ƿ�������ɲ�����1��������0���쳣��
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��9��
*////////////////////////////////////////////////////////////////////////////////////
bit IIC_Write(unsigned char dat)
{
	unsigned char i, mask = 0x80;
	bit a;                              //���ڴ洢���յ���ACK
	for(i = 0;i < 8;i ++)               //��λ��������
		{
			if(dat&mask)IIC_SDA = 1;    //�жϵ�ǰλ��1����0����Ӧ���߻�����SDA
			else IIC_SDA = 0;
			IICDelay();                 //��ʱ
			IIC_SCL = 1;                //����SCL
			mask >>= 1;                 //׼��������һλ����
			IIC_SCL = 0;                //����SCL
		}
	IICDelay();                         //��ʱ
	IIC_SDA = 1;                        //����IIC����
	IICDelay();
	IIC_SCL = 1;
	IICDelay();
	a=IIC_SDA;                          //��ȡACK�ź�
	IIC_SCL = 0;
	return (~ a);                       //����ACK�źţ�1��������
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������IIC_Read
*�������ܣ���IIC���߶�ȡһ��unsigned char������
*�����б�
*   ACK
*       �������ͣ�bit������
*       �������������ݶ�ȡ�������͵�Ӧ��λ���Ӧ��λ
*����ֵ��һ��unsigned char�ͱ�������ȡ��������
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��9��
*////////////////////////////////////////////////////////////////////////////////////
unsigned char IIC_Read(bit ACK)
{
	unsigned char i,mask = 0x80,dat = 0;
	IIC_SCL = 0;                            //׼��IIC����
	IIC_SDA = 1;
	for(i=0;i<8;i++)                        //��λ��ȡ����
		{
			IICDelay();                     //��ʱ
			IIC_SCL = 1;                    //����SCL
			IICDelay();                     //��ʱ
			if(IIC_SDA)dat |= mask;         //��ȡ1bit���ݣ�������dat����Ӧ����
			mask >>= 1;
			IIC_SCL = 0;                    //����SCL��׼����ȡ��һλ����
		}
	IICDelay();                             //��ʱ
	IIC_SDA = ACK;                          //����ACK��NAK�ź�
	IICDelay();                             //��ʱ
	IIC_SCL = 1;                            //����IIC����
	IICDelay();
	IIC_SCL = 0;
	return dat;
}
