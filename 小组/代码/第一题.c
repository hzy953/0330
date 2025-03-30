#include <reg51.h>

unsigned char led_status = 0xFE;

void timer0_init() {
    TMOD &= 0xF0;    
    TMOD |= 0x01;     
    TH0 = 0x4C;       
    TL0 = 0x00;       
    ET0 = 1;          
    EA = 1;  
    TR0 = 1;  
}

void main() {
    P1 = led_status;  
    timer0_init();
    while(1);  
}

void timer0_isr() interrupt 1 {
    static unsigned int count = 0;
    
    TH0 = 0x4C;  
    TL0 = 0x00;
    
    if(++count >= 20) { 
        count = 0;
        
        led_status = (led_status << 1) | ((led_status >> 7) & 0x01);
        P1 = led_status;
    }
}