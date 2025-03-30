#include <reg51.h>

unsigned int a = 0; // ????
unsigned int b = 0; // ????
sbit ge = P2^2;
sbit shi = P2^1;
unsigned int code seg_code[] = {0x18, 0xDD, 0x2C, 0x8C, 0xC9, 0x8A, 0x0A, 0xDC, 0x08, 0x88};

void delay(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 123; j++);
}

void display() {
    P1 = seg_code[a];
    shi = 1;
    delay(3);
    shi=0;       

    P1 = seg_code[b];
    ge=1;
    delay(3);
    ge=0;
}

// ?????
void init_serial() {
    TMOD = 0x20;   // ???1?????2(8?????)
    TH1 = 0xFD;    // ?????9600(11.0592MHz??)
    TL1 = 0xFD;
    SCON = 0x50;   // ????1,????
    TR1 = 1;       // ?????1
    ES = 1;        // ??????
    EA = 1;        // ?????
}

void main() {
    init_serial(); // ?????

    while (1) {
        display();
    }
}

// ????????
void serial_isr() interrupt 4 {
    if (RI) {          // ????
        RI = 0;        // ????????
        a = b;
        b = SBUF-'0';
    }
    if (TI) {          // ????
        TI = 0;        // ????????
    }
}