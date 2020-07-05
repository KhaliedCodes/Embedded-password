#include <reg51.h>

sbit r1 = P1^0;
sbit r2 = P1^1;
sbit r3 = P1^2;
sbit r4 = P1^3;

sbit c1 = P1^4;
sbit c2 = P1^5;
sbit c3 = P1^6;

sbit rs = P3^5;
sbit rw = P3^6;
sbit en = P3^7;

sfr lcd = 0xA0;



void delay(unsigned int time){
	unsigned i, j;
	for(i=0;i<time;i++){
		for(j=0;j<1275;j++);
	}
}

void lcdcmd(unsigned char val){
	lcd = val;
	rs = 0;
	rw = 0;
	en = 1;
	delay(1);
	en = 0;
}

void lcddat(unsigned char dat){
	lcd = dat;
	rs = 1;
	rw = 0;
	en = 1;
	delay(1);
	en = 0;
}

unsigned int t = 0;

void UART_Init()
{ 
    SCON = 0x50;
    TMOD = 0x20; 
    TH1 = 0xFD;
    TR1 = 1;
}

void UART_TxChar(char ch)
{
    SBUF = ch;
    while(TI==0);
    TI = 0;
}


void main(){
	unsigned char a[]={"Access Granted"};
	unsigned char b[]={"Access Denied"};
	unsigned char pass[4];
	unsigned int i = 0;
	
	
	
	while(1){
	lcd = 0x00;
	lcdcmd(0x38);
	lcdcmd(0x01);
	lcdcmd(0x84);
	lcdcmd(0x0F);
	
	
	i = 0;
	while(i<4){
		r1 = 0; r2 = 1; r3 = 1; r4 = 1;
		if(c1 == 0){
			lcddat('1');
			delay(30);
			pass[i]='1';
			i++;
		}
		if(c2 == 0){
			lcddat('2');
			delay(30);
			pass[i]='2';
			i++;
		}
		if(c3 == 0){
			lcddat('3');
			delay(30);
			pass[i]='3';
			i++;
		}
		r1 = 1; r2 = 0;
		if(c1 == 0){
			lcddat('4');
			delay(30);
			pass[i]='4';
			i++;
		}
		if(c2 == 0){
			lcddat('5');
			delay(30);
			pass[i]='5';
			i++;
		}
		if(c3 == 0){
			lcddat('6');
			delay(30);
			pass[i]='6';
			i++;
		}
		r2 = 1; r3 = 0;
		if(c1 == 0){
			lcddat('7');
			delay(30);
			pass[i]='7';
			i++;
		}
		if(c2 == 0){
			lcddat('8');
			delay(30);
			pass[i]='8';
			i++;
		}
		if(c3 == 0){
			lcddat('9');
			delay(30);
			pass[i]='9';
			i++;
		}
		r3 = 1; r4 = 0;
		if(c1 == 0){
			lcddat('*');
			delay(30);
			pass[i]='*';
			i++;
		}
		if(c2 == 0){
			lcddat('0');
			delay(30);
			pass[i]='0';
			i++;
		}
		if(c3 == 0){
			lcddat('#');
			delay(30);
			pass[i]='#';
			i++;
		}
		r4 = 1;
	}
	lcdcmd(0x01);
	if(pass[0] == '0' && pass[1] == '0' && pass[2] == '0' && pass[3] == '0'){
		UART_Init();
		for(t=0;a[t]!=0;t++){
			lcddat(a[t]);
			UART_TxChar(a[t]);
    }
	}
	else{
		UART_Init();
		for(t=0;b[t]!=0;t++){
			lcddat(b[t]);
      UART_TxChar(b[t]);
    }
	}

    
	delay(300);
}
}