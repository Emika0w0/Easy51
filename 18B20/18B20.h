#ifndef _HEAD_18B20_
#define _HEAD_18B20_

extern int DS18B20_GetTemp(uint8 *addr);    //��ȡ18B20������¶ȡ���addr��64�ֽڵ�������ţ�skip ROM��addr[0]=0x00�������¶�ֵ��
extern void DS18B20_Start(uint8 *addr);     //����18B20�¶�ת������addr��64�ֽڵ�������ţ�skip ROM��addr[0]=0x00����ÿ�ζ����¶Ⱥ�������������¶�ת����
extern bit DS18B20_Init();  //��ʼ��18B20��Ҳ�����ڼ�������Ƿ���ڡ�����ֵ1��������2���쳣��

#endif // _HEAD_18B20_
