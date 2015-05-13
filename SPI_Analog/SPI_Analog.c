/*//////////////////////////GPL��Դ���֤////////////////////////////////////////////////
    Copyright (C) <2015>  <Xianglong He>
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

    �ļ�����SPI_Analog.c
	���ߣ�������
	���䣺qwgg9654@gmail.com
		  admin@hxlxz.com
	����������SPIͨ�ŵ�IO��ģ��ʵ��
	��ע����ʹ�õĵ�Ƭ���Դ�SPIͨ�����Ӳ�����ܣ���STC15Wϵ�У����Ƽ�ֱ��ʹ����Ӳ��ģ�顣
          ʹ�ø�ģ�飬����config.h�ж���SPI_CS_SET����ΪSPI���ߵ�CSʹ�ܽӿڡ�
          �� #define SPI_CS_SET P0^0
          ʹ�ø�ģ�飬����config.h�ж���SPI_SCLK_SET����ΪSPI���ߵ�SCLKʱ���źŽӿڡ�
          �� #define SPI_SCLK_SET P0^1
          ʹ�ø�ģ�飬����config.h�ж���SPI_MOSI_SET����ΪSPI���ߵ�MOSI�źŽӿڡ�
          �� #define SPI_MOSI_SET P0^2
          ʹ�ø�ģ�飬����config.h�ж���SPI_MISO_SET����ΪSPI���ߵ�MISO�źŽӿڡ�
          �� #define SPI_MISO_SET P0^3
*////////////////////////////////////////////////////////////////////////////////////////\

/*//////////////////�ⲿ����//////////////////////////////////
extern void SPI_Init();		//SPI��ʼ��������ģʽʹ�ã�
extern void SPI_Write(uint8 dat);	//SPI��ģʽ�������ݣ�dat��Ҫ���͵����ݣ�
extern uint8 SPI_Read();	//SPI��ģʽ��ȡ���ݣ����ض�ȡ��������
extern void SPI_Slave_Send(uint8 dat);	//SPI��ģʽ��Ӧ���ݣ�dat��Ҫ��Ӧ�����ݣ�
extern uint8 SPI_Slave_Resive();	//SPI��ģʽ�������ݣ����ؽ��յ�������
////////////////////////////////////////////////////////////*/
//2015��1��8��
#include<reg52.h>
#include<intrins.h>
typedef unsigned char uint8;
typedef unsigned int uint16;

#define CPOL 1	  //����SPIͨ��ģʽ�����飺���Ҫ��SPI�����ͨ�ţ����������Ļ�������CPHA=1��
#define CPHA 1
#define Dealy(); {_nop_();_nop_();_nop_();_nop_();_nop_();}	//����ʵ����ʱҪ���޸�
sbit CS=P1^3;	//SPIͨ�ŵ��ĸ�IO��
sbit SCLK=P1^1;
sbit MOSI=P1^0;
sbit MISO=P1^2;

void SPI_Init()
{
	SCLK=CPOL;
	CS=1;
}
void SPI_Write(uint8 dat)
{
	uint8 mask;
	CS=0;
	if(CPHA)
		{
			for(mask=0x80;mask!=0;mask>>=1)
				{
					SCLK=~SCLK;
					MOSI=dat&mask;
					Dealy();
					SCLK=~SCLK;
					Dealy();
				}
		}
	else
		{
			for(mask=0x80;mask!=0;)
				{
					MOSI=dat&mask;
					SCLK=~SCLK;
					Dealy();
					mask>>=1;
					SCLK=~SCLK;
					Dealy();
				}
		}
	CS=1;
}
uint8 SPI_Read()
{
	uint8 dat=0,mask=0x80;
	CS=0;
		if(CPHA)
		{
			for(;mask!=0;mask>>=1)
				{
					SCLK=~SCLK;
					Dealy();
					if(MISO)dat|=mask;
					SCLK=~SCLK;
					Dealy();
				}
		}
	else
		{
	        for(;mask!=0;mask>>=1)
		        {
					Dealy();
					if(MISO)dat|=mask;
					SCLK=~SCLK;
					Dealy();
		            SCLK=~SCLK;
					Dealy();
		        }
	    }
	CS=1;
	return dat;
}
void SPI_Slave_Send(uint8 dat)
{
	uint8 mask=0x80;
	if(CPHA)
		{
			while(CS);
			for(;mask!=0;mask>>=1)
				{
					while(SCLK==CPOL);
					MISO=dat&mask;
					while(SCLK!=CPOL);
				}
		}
	else
		{
			for(;mask!=0;mask>>=1)
				{
					MISO=dat&mask;
					while(CS);
					while(SCLK==CPOL);
					while(SCLK!=CPOL);
				}
		}

}
uint8 SPI_Slave_Resive()
{
	uint8 mask=0x80,dat=0;
	while(CS);
	if(CPHA)
		{
			for(;mask!=0;mask>>=1)
				{
					while(SCLK==CPOL);
					while(SCLK!=CPOL);
					if(MOSI)dat|=mask;
				}
		}
	else
		{
			for(;mask!=0;mask>>=1)
				{
					while(SCLK==CPOL);
					if(MOSI)dat|=mask;
					while(SCLK!=CPOL);
				}
		}
   return dat;
}
