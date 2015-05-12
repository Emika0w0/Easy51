/*//////////////////////////GPL��Դ����֤////////////////////////////////////////////////
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

	�ļ�����DS18B20.c
	���ߣ�������
	���䣺qwgg9654@gmail.com
		  admin@hxlxz.com
	����������DS18B20�¶ȴ������ļ򵥲�������ģ��
	��ע������ʹ�÷�װ�õĺ������в���������Ҫʹ��ֱ�Ӷ�DS18B20��д�ĺ�����
          ʹ�ø�ģ�飬���ڳ����ж���DS18B20_IO_SET����ΪDS18B20�����ݽӿڡ�
          �� #define DS18B20_IO_SET P0^0
          ʹ�ø�ģ�飬���ڳ����ж���STC_YX����ΪSTC��Ƭ��ָ����ơ�
          �� #define STC_YX "STC_Y5"
          ʹ�ø�ģ�飬���ڳ����ж���XTAL����Ϊ����Ƶ��
          �� #define XTAL 11.059200
*////////////////////////////////////////////////////////////////////////////////////////
#include<DS18B20.h>
#define _6nop(); {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}
//����������STC_Y3,STC_Y5��nop��ʱ
#define STC_Y1 1
#define STC_Y3 3
#define STC_Y5 5

sbit DS18B20_IO = DS18B20_IO_SET;

#ifndef STC_YX
#define STC_YX STC_Y5
#endif //���û�ж���STC��Ƭ����ָ�����Ĭ��ΪSTC_Y5ָ�

#ifndef XTAL
#define XTAL 11.059200
#endif //���û�ж��徧��Ƶ�ʣ���Ĭ��Ϊ11.0592M����

/*///////////////////////////////////////////////////////////////////////////////////
*��������DelayX10us
*�������ܣ���ʱ
*�����б���
*   t
*       �������ͣ�unsigned char������
*       ����������Ҫ��ʱ��ʱ������λ��10us
*����ֵ���ޡ�
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��11��
*�汾��1.1
*�汾�Ķ�����д������ʹ֮���ڸ���ָ���������Ƶ���¹���
*���ߣ�������
*���ڣ�2015��5��11��
*////////////////////////////////////////////////////////////////////////////////////
void DelayX10us(unsigned char t)
{
	unsigned int i;
	#if STC_YX == STC_Y1
		//�����ǰָ�ΪSTC_Y1�����ڸÿƬ�����ܽϲ�����ú�����Բ�ͬ�ľ���Ƶ��ѡ����ʱ����
        #if XTAL < 8
        #elif XTAL >= 8 && XTAL < 9
            _nop_();
        #elif XTAL >= 9 && XTAL < 12
            i = t;
            while(--i);
        #elif XTAL >= 12 && XTAL < 14
            i = 2 * t;
            while(--i);
        #elif XTAL >= 14 && XTAL < 16
            i = 3 * t;
            while(--i);
        #elif XTAL >= 16 && XTAL < 18
            i = 4 * t;
            while(--i);
        #elif XTAL >= 18 && XTAL < 20
            i = 5 * t;
            while(--i);
        #elif XTAL >= 20
            i = XTAL / 10 * t + 0.5;
            while(--i);
        #endif
    #else                           //�����ǰָ�ΪSTC_Y3��STC_Y5
		i = t * 2;
        while (--i)
		{
			_6nop();_6nop();_6nop();_6nop();_6nop();
			_6nop();_nop_();_nop_();_nop_();
		}
	#endif
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������DS18B20_Init
*�������ܣ���ʼ��DS18B20
*�����б���
*   ��
*����ֵ��һ��bit�ͱ�������ʼ���Ƿ�������1��������0��ʧ�ܣ�
*�汾��1.0
*���ߣ�������
*���ڣ�2015��5��11��
*////////////////////////////////////////////////////////////////////////////////////
bit DS18B20_Init()
{
	bit temp;
	EA=0;               //�����жϣ���ֹʱ�򱻸���
	DS18B20_IO=0;       //����1-wine���ߣ�����Init�ź�
	DelayX10us(60);     //��ʱ600us
	DS18B20_IO=1;       //�ͷ�����
	DelayX10us(8);      //��ʱ80us���ȴ�������Ӧ
	temp=DS18B20_IO;    //��ȡ����
	while(!DS18B20_IO); //�ȴ����߱��ͷ�
	EA=1;               //�ָ��ж�ʹ��
	return ~temp;       //���ػ�ȡ���ĳ�ʼ��״̬��Ϊ����ϰ�ߣ�����ȡ�����ٷ���
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������DS18B20_Write
*�������ܣ���DS18B20дһ��unsigned char�͵����ݻ�����
*�����б���
*   dat
*       �������ͣ�unsigned char������
*       ����������Ҫд������ݻ�����
*����ֵ����
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��11��
*////////////////////////////////////////////////////////////////////////////////////
void DS18B20_Write(unsigned char dat)
{
	unsigned char mask;
	EA=0;                               //�����жϣ���ֹʱ�򱻸���
	for(mask=0x01;mask!=0;mask<<=1)     //��λ��������
	{
		if(dat&mask)                    //��ȡ��ǰλ�Ƿ�Ϊ1
		{
			DS18B20_IO=0;               //λ��ʼ�ź�
			#if STC_YX == STC_Y1
			_nop_();                    //��΢��ʱ����ֹ���󡣶Բ�ͬ�ĵ�Ƭ��ָ����˲�ͬ�Ĵ���
			#else
            _6nop();_6nop();
			#endif
			DS18B20_IO=1;               //�������ߣ���������
			DelayX10us(8);              //��ʱ80us
		}
		else                            //��ǰλΪ0
		{
			DS18B20_IO=0;               //�������ߣ���������
			DelayX10us(8);              //��ʱ80us
			DS18B20_IO=1;               //�ͷ�����
		}
			#if STC_YX == STC_Y1
			_nop_();_nop_();            //��΢��ʱ����ֹ���󡣶Բ�ͬ�ĵ�Ƭ��ָ����˲�ͬ�Ĵ���
			#else
            _6nop();_6nop();
			#endif
	}
	EA=1;                               //�ָ��ж�ʹ��
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������DS18B20_Read
*�������ܣ���DS18B20�ж�ȡһλ����
*�����б���
*   ��
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��11��
*////////////////////////////////////////////////////////////////////////////////////
unsigned char DS18B20_Read()
{
	unsigned char mask,dat=0;
	EA=0;                               //�����жϣ���ֹʱ�򱻸���
	for(mask=0x01;mask!=0;mask<<=1)     //��λ��ȡ����
	{
		DS18B20_IO=0;                   //�������ߣ�������ʼ�ź�
        #if STC_YX == STC_Y1
        _nop_();_nop_();                //��΢��ʱ����ֹ���󡣶Բ�ͬ�ĵ�Ƭ��ָ����˲�ͬ�Ĵ���
        #else
        _6nop();_6nop();
        #endif

		DS18B20_IO=1;                   //�ͷ�����
		DelayX10us(1);                  //��ʱ10us
		if(DS18B20_IO)dat|=mask;        //��ȡ���ߣ���ȡ1λ���ݱ�����
		DelayX10us(5);                  //��ʱ50us��׼����ȡ��һλ����
	}
	EA=1;                               //�ָ��ж�ʹ��
	return dat;
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������DS18B20_Start
*�������ܣ�����DS18B20�¶�ת����
*�����б���
*   *addr
*       �������ͣ�unsigned char��ָ�루����8��unsigned char�����ݣ�
*       ����������64�ֽڵ�������š��ر�ģ�Skip ROMʱaddr[0]�봫��0x00
*����ֵ��һ��bit�ͱ����������Ƿ�������1��������0��ʧ�ܣ�
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��11��
*////////////////////////////////////////////////////////////////////////////////////
bit DS18B20_Start(unsigned char *addr)
{
	if(!DS18B20_Init())return 0;            //���ͳ�ʼ���źţ������ʼ�����󣬷���0
	if(addr[0]==0x00)DS18B20_Write(0xCC);   //���addr[0]Ϊ0x00������Skip ROMָ��
	else                                    //���򣬷���Match ROMָ�����������ROM��
	{
		DS18B20_Write(0x55);
		DS18B20_Write(addr[0]);
		DS18B20_Write(addr[1]);
		DS18B20_Write(addr[2]);
		DS18B20_Write(addr[3]);
		DS18B20_Write(addr[4]);
		DS18B20_Write(addr[5]);
		DS18B20_Write(addr[6]);
		DS18B20_Write(addr[7]);
	}
	DS18B20_Write(0x44);                    //���������¶�ת��ָ��
	return 1;
}
/*///////////////////////////////////////////////////////////////////////////////////
*��������DS18B20_GetTemp
*�������ܣ���ȡDS18B20������¶ȡ�
*�����б���
*   *addr
*       �������ͣ�unsigned char��ָ�루����8��unsigned char�����ݣ�
*       ����������64�ֽڵ�������š��ر�ģ�Skip ROMʱaddr[0]�봫��0x00
*����ֵ��һ��double�ͱ�������ȡ�����¶�ֵ������������ʱ������-999��
*�汾��1.0
*���ߣ�������
*���ڣ�2014��12��11��
*�汾��1.1
*�汾�Ķ����޸ķ���ֵ���ͣ�ֱ�ӷ���double������
*���ߣ�������
*���ڣ�2015��5��11��
*////////////////////////////////////////////////////////////////////////////////////
double DS18B20_GetTemp(unsigned char *addr)
{
	int temp;                                   //�����¶�ֵ�����м�����
	unsigned char temp1,temp2;                  //�����¶�ֵ�����м�����
	unsigned int temp3;                         //�����¶�ֵ�����м�����
	double tempo;                               //�������յõ����¶�ֵ
	bit flag = 0;                               //�������λ
	if(!DS18B20_Init())return -999;             //���ͳ�ʼ���źţ������ʼ�����󣬷���-999
	if(addr[0] == 0x00)DS18B20_Write(0xCC);     //���addr[0]Ϊ0x00������Skip ROMָ��
	else                                        //���򣬷���Match ROMָ�����������ROM��
	{
		DS18B20_Write(0x55);
		DS18B20_Write(addr[0]);
		DS18B20_Write(addr[1]);
		DS18B20_Write(addr[2]);
		DS18B20_Write(addr[3]);
		DS18B20_Write(addr[4]);
		DS18B20_Write(addr[5]);
		DS18B20_Write(addr[6]);
		DS18B20_Write(addr[7]);
	}
	DS18B20_Write(0xBE);                        //���Ͷ�ȡ�¶�ָ��
	temp1=DS18B20_Read();                       //����һ��unsigned char�����ݣ����ݴ�
	temp2=DS18B20_Read();                       //���ڶ���unsigned char�����ݣ����ݴ�
	temp3=(unsigned int)temp2;                  //����λunsigned char�����ݷŵ�һ��unsigned int�ͱ�����
	temp3 <<= 8;
	temp3|=(unsigned int)temp1;
	DelayX10us(15);                             //��ʱ150us
	if(temp3&0x8000)                            //����õ����¶�ֵ�Ǹ�ֵ
	{
		temp3 &= 0x07FF;                        //��ȡ�¶�ֵ�ľ���ֵ
		temp = -temp3;
		flag = 1;                               //���ø�ֵ��־
	}
	else
	{
		temp3 &= 0x07FF;                        //��ȡ�¶�ֵ�ľ���ֵ
		temp = temp3;
	}
	tempo = temp >> 4;                          //�����¶�ֵ���洢��double�ͱ���tempo��
	tempo += (temp & 0x08) * 0.5 + (temp & 0x04) * 0.25 + (temp & 0x02) * 0.125 + (temp & 0x01) * 0.6275;
	return tempo;
}