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
	2014��12��11��
	����������PCF8591 AD/DAоƬ�򵥿���
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////�ⲿ����//////////////////////////////////
extern uint8 PCF8591_Read(uint8 chanl);	//��ȡADת���õ���ֵ����ͨת�����ǲ�֣���chanl��ͨ���ţ����أ�ADֵ
extern void PCF8591_DA(uint8 dat);	//����DA�����dat��Ҫ�����ADֵ����
////////////////////////////////////////////////////////////*/
#include<reg51.h>
typedef unsigned char uint8;
typedef unsigned int uint16;

extern void IIC_Start();    //����IICͨ����ʼ�ź�
extern void IIC_Stop();     //����IICͨ����ֹ�ź�
extern bit IIC_Write(uint8 dat);    //IICͨ��д��һ��uint8�͵����ݣ�dat��Ҫд������ݣ����أ�1���ɹ���0��ʧ��
extern uint8 IIC_Read(bit ACK);     //IICͨ�Ŷ���һ��uint8�͵����ݣ�ACK��0����ĩλ���ݣ�1��ĩλ���ݣ������ض���������

uint8 PCF8591_Read(uint8 chanl)
{
	uint8 dat;
	IIC_Start();
	IIC_Write(0x90);
	IIC_Write(chanl<<4);
	IIC_Start();
	IIC_Write(0x91);
	IIC_Read(0);
	dat=IIC_Read(1);
	IIC_Stop();
	return dat;
}
void PCF8591_DA(uint8 dat)
{
	IIC_Start();
	IIC_Write(0x90);
	IIC_Write(0x40);
	IIC_Write(dat);
	IIC_Stop();
}
