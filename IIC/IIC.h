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

	�ļ�����IIC.h
	���ߣ�������
	���䣺qwgg9654@gmail.com
		  admin@hxlxz.com
	�����������õ�Ƭ��IO��ģ��ʵ��IICͨ��-ͷ�ļ�
	��ע��
*////////////////////////////////////////////////////////////////////////////////////////

	//2014��12��9��

void IIC_Start();    //����IICͨ����ʼ�ź�
void IIC_Stop();     //����IICͨ����ֹ�ź�
bit IIC_Write(unsigned char dat);    //IICͨ��д��һ��uint8�͵����ݣ�dat��Ҫд������ݣ����أ�1���ɹ���0��ʧ��
unsigned char IIC_Read(bit ACK);     //IICͨ�Ŷ���һ��uint8�͵����ݣ�ACK��0����ĩλ���ݣ�1��ĩλ���ݣ������ض���������

