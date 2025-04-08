#include <REG52.h>
#include "intrins.h"
#include "04032117.h"

// ����OLED��I2C��ַ
#define OLED_ADDRESS 0x78  // ͨ��Ϊ0x78��0x7A

// ÿ���ַ�ռ16�ֽڣ���A - Z��a - z��0 - 9������������˳������



sbit led=P2^0;
sbit a=P1^7;
sbit SDA = P1^1;  // I2C������
sbit SCL = P1^0;

// ��ʱ����

//void DelayMs(unsigned int);

void DelayMs(unsigned int ms) {
    unsigned int i, j;
      for(i=0;i<ms; i++)
        for(j=0; j<110; j++);
}


// I2C��ʼ�ź�
void I2C_Start() {
    SDA = 1;
    SCL = 1;
    _nop_(); _nop_(); // ������ʱ
    SDA = 0;          // �½��ش�����ʼ����
    _nop_(); _nop_();
    SCL = 0;          // ����SCL׼����������
}



// I2Cֹͣ�ź�
void I2C_Stop() {
    SDA = 0;
    SCL = 1;
    _nop_(); _nop_();
    SDA = 1;          // �����ش���ֹͣ����
    _nop_(); _nop_();
}

// ����һ���ֽ�
void I2C_SendByte(unsigned char dat) {
    unsigned char i;
    for(i=0; i<8; i++) {
        SDA = dat >> 7;  // ȡ���λ
        dat <<= 1;
        SCL = 1;
        _nop_(); _nop_(); // ���ָߵ�ƽ
        SCL = 0;          // �½�����������
    }
    // �ȴ�ACK���˴��򻯴���
    SDA = 1;
    SCL = 1;
    _nop_(); _nop_();
    SCL = 0;
}

// ��OLED��������
void OLED_WriteCmd(unsigned char cmd) {
    I2C_Start();
    I2C_SendByte(OLED_ADDRESS); // �����豸��ַ
    I2C_SendByte(0x00);         // �����ֽڣ�����ģʽ��
    I2C_SendByte(cmd);          // ��������
    I2C_Stop();
}

// ��OLED��������
void OLED_WriteData(unsigned char dat) {
    I2C_Start();
    I2C_SendByte(OLED_ADDRESS); // �����豸��ַ
    I2C_SendByte(0x40);         // �����ֽڣ�����ģʽ��
    I2C_SendByte(dat);          // ��������
    I2C_Stop();
}

// OLED��ʼ��
void OLED_Init() {
    DelayMs(100); // �ȴ�OLED�ϵ��ȶ�
    
     OLED_WriteCmd(0xAE); // �ر���ʾ
    
    OLED_WriteCmd(0xD5); // ������ʾʱ�ӷ�Ƶ
    OLED_WriteCmd(0x80);
    
    OLED_WriteCmd(0xA8); // ���ö�·������
    OLED_WriteCmd(0x3F);
    
    OLED_WriteCmd(0xD3); // ������ʾƫ��
    OLED_WriteCmd(0x00);
    
    OLED_WriteCmd(0x40); // ������ʾ��ʼ��
    
    OLED_WriteCmd(0x8D); // ��ɱ�����
    OLED_WriteCmd(0x14); // ������ɱ�
    
    OLED_WriteCmd(0x20); // �ڴ�ģʽ
    OLED_WriteCmd(0x00); // ˮƽѰַģʽ
    
    OLED_WriteCmd(0xA1); // ����ӳ�䣨���ҷ�ת��
    OLED_WriteCmd(0xC8); // ��ɨ�跽�����·�ת��
    
    OLED_WriteCmd(0xDA); // COM��������
    OLED_WriteCmd(0x12);
    
    OLED_WriteCmd(0x81); // �Աȶ�����
    OLED_WriteCmd(0xCF);
    
    OLED_WriteCmd(0xD9); // Ԥ�������
    OLED_WriteCmd(0xF1);
    
    OLED_WriteCmd(0xDB); // VCOMH��ѹ
    OLED_WriteCmd(0x40);
    
    OLED_WriteCmd(0xA4); // ��ʾȫ�������ر�
    OLED_WriteCmd(0xA6); // ������ʾ���Ƿ�ɫ��
    
    OLED_WriteCmd(0xAF); // ������ʾ
}

// ����
void OLED_Clear() {
    unsigned char i, j;
    for(j=0; j<8; j++) {
        OLED_WriteCmd(0xB0 + j); // ����ҳ��ַ
        OLED_WriteCmd(0x00);     // �е͵�ַ
        OLED_WriteCmd(0x10);     // �иߵ�ַ
        for(i=0; i<128; i++) {
            OLED_WriteData(0x00); // ���0x00���
        }
    }
}
// ��ָ��λ����ʾ�ַ�
void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch) {
    unsigned char c=ch-65;
    unsigned char i;
    OLED_WriteCmd(0xB0 + y);               // ����ҳ��ַ
    OLED_WriteCmd(((x & 0xF0) >> 4) | 0x10); // �иߵ�ַ
    OLED_WriteCmd(x & 0x0F);               // �е͵�ַ
    for(i=0; i<16; i++) {
        OLED_WriteData(Font8x16[c][i]); // �����ֿ�����
    }
}



// ������
int i;

void main() {
	a=1;
    OLED_Init();    // ��ʼ��OLED
    OLED_Clear();   // ����
    
    while(1)
    {
	if(a==0)
	{
		OLED_ShowChar(0, 1, 'A');
		OLED_ShowChar(0, 2, 'B');
		
		DelayMs(100);
		
		OLED_ShowChar(18, 1, 'C');
		OLED_ShowChar(18, 2, 'D');
		
		DelayMs(100);
		
		OLED_ShowChar(36, 1, 'E');
		OLED_ShowChar(36, 2, 'F');
		
		DelayMs(100);
		
		OLED_ShowChar(0, 4, 'G');
		OLED_ShowChar(0, 5, 'H');
		
		DelayMs(100);
		
		OLED_ShowChar(18, 4, 'I');
		OLED_ShowChar(18, 5, 'J');
		
		DelayMs(100);
		
		OLED_ShowChar(36, 4, 'K');
		OLED_ShowChar(36, 5, 'L');
		
		DelayMs(100);
		OLED_Clear();   // ����
		
		OLED_ShowChar(0, 1, 'A');
		OLED_ShowChar(0, 2, 'B');
		OLED_ShowChar(18, 1, 'C');
		OLED_ShowChar(18, 2, 'D');
		OLED_ShowChar(36, 1, 'E');
		OLED_ShowChar(36, 2, 'F');
		OLED_ShowChar(0, 4, 'G');
		OLED_ShowChar(0, 5, 'H');
		OLED_ShowChar(18, 4, 'I');
		OLED_ShowChar(18, 5, 'J');
		OLED_ShowChar(36, 4, 'K');
		OLED_ShowChar(36, 5, 'L');
	}	
	}
}