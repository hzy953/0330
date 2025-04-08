#include <REG52.h>
#include "intrins.h"
#include "04032117.h"

// 定义OLED的I2C地址
#define OLED_ADDRESS 0x78  // 通常为0x78或0x7A

// 每个字符占16字节，按A - Z、a - z、0 - 9、常见标点符号顺序排列



sbit led=P2^0;
sbit a=P1^7;
sbit SDA = P1^1;  // I2C数据线
sbit SCL = P1^0;

// 延时函数

//void DelayMs(unsigned int);

void DelayMs(unsigned int ms) {
    unsigned int i, j;
      for(i=0;i<ms; i++)
        for(j=0; j<110; j++);
}


// I2C起始信号
void I2C_Start() {
    SDA = 1;
    SCL = 1;
    _nop_(); _nop_(); // 短暂延时
    SDA = 0;          // 下降沿触发起始条件
    _nop_(); _nop_();
    SCL = 0;          // 拉低SCL准备发送数据
}



// I2C停止信号
void I2C_Stop() {
    SDA = 0;
    SCL = 1;
    _nop_(); _nop_();
    SDA = 1;          // 上升沿触发停止条件
    _nop_(); _nop_();
}

// 发送一个字节
void I2C_SendByte(unsigned char dat) {
    unsigned char i;
    for(i=0; i<8; i++) {
        SDA = dat >> 7;  // 取最高位
        dat <<= 1;
        SCL = 1;
        _nop_(); _nop_(); // 保持高电平
        SCL = 0;          // 下降沿锁存数据
    }
    // 等待ACK（此处简化处理）
    SDA = 1;
    SCL = 1;
    _nop_(); _nop_();
    SCL = 0;
}

// 向OLED发送命令
void OLED_WriteCmd(unsigned char cmd) {
    I2C_Start();
    I2C_SendByte(OLED_ADDRESS); // 发送设备地址
    I2C_SendByte(0x00);         // 控制字节（命令模式）
    I2C_SendByte(cmd);          // 命令内容
    I2C_Stop();
}

// 向OLED发送数据
void OLED_WriteData(unsigned char dat) {
    I2C_Start();
    I2C_SendByte(OLED_ADDRESS); // 发送设备地址
    I2C_SendByte(0x40);         // 控制字节（数据模式）
    I2C_SendByte(dat);          // 数据内容
    I2C_Stop();
}

// OLED初始化
void OLED_Init() {
    DelayMs(100); // 等待OLED上电稳定
    
     OLED_WriteCmd(0xAE); // 关闭显示
    
    OLED_WriteCmd(0xD5); // 设置显示时钟分频
    OLED_WriteCmd(0x80);
    
    OLED_WriteCmd(0xA8); // 设置多路复用率
    OLED_WriteCmd(0x3F);
    
    OLED_WriteCmd(0xD3); // 设置显示偏移
    OLED_WriteCmd(0x00);
    
    OLED_WriteCmd(0x40); // 设置显示起始行
    
    OLED_WriteCmd(0x8D); // 电荷泵设置
    OLED_WriteCmd(0x14); // 开启电荷泵
    
    OLED_WriteCmd(0x20); // 内存模式
    OLED_WriteCmd(0x00); // 水平寻址模式
    
    OLED_WriteCmd(0xA1); // 段重映射（左右翻转）
    OLED_WriteCmd(0xC8); // 行扫描方向（上下翻转）
    
    OLED_WriteCmd(0xDA); // COM引脚配置
    OLED_WriteCmd(0x12);
    
    OLED_WriteCmd(0x81); // 对比度设置
    OLED_WriteCmd(0xCF);
    
    OLED_WriteCmd(0xD9); // 预充电周期
    OLED_WriteCmd(0xF1);
    
    OLED_WriteCmd(0xDB); // VCOMH电压
    OLED_WriteCmd(0x40);
    
    OLED_WriteCmd(0xA4); // 显示全部点亮关闭
    OLED_WriteCmd(0xA6); // 正常显示（非反色）
    
    OLED_WriteCmd(0xAF); // 开启显示
}

// 清屏
void OLED_Clear() {
    unsigned char i, j;
    for(j=0; j<8; j++) {
        OLED_WriteCmd(0xB0 + j); // 设置页地址
        OLED_WriteCmd(0x00);     // 列低地址
        OLED_WriteCmd(0x10);     // 列高地址
        for(i=0; i<128; i++) {
            OLED_WriteData(0x00); // 填充0x00清空
        }
    }
}
// 在指定位置显示字符
void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch) {
    unsigned char c=ch-65;
    unsigned char i;
    OLED_WriteCmd(0xB0 + y);               // 设置页地址
    OLED_WriteCmd(((x & 0xF0) >> 4) | 0x10); // 列高地址
    OLED_WriteCmd(x & 0x0F);               // 列低地址
    for(i=0; i<16; i++) {
        OLED_WriteData(Font8x16[c][i]); // 调用字库数据
    }
}



// 主函数
int i;

void main() {
	a=1;
    OLED_Init();    // 初始化OLED
    OLED_Clear();   // 清屏
    
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
		OLED_Clear();   // 清屏
		
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