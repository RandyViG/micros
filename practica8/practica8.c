/*******************************************************
This program was created by the CodeWizardAVR V3.42 
Automatic Program Generator
� Copyright 1998-2020 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : Pr�ctica 7
Version : 
Date    : 16/11/2020
Company : 
Comments: Cron�metro de 59.9 segundos 


Chip type               : ATmega8535
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 128
*******************************************************/

#include<mega8535.h>
#include<delay.h>

#define RESET PIND.0
#define STOP PIND.1
#define START PIND.2
#define SEGUNDOS PORTB
#define UNI_SEG PORTA
#define DECIMA PORTC

const char contador[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,0x6f};
unsigned char seg = 0, uni_seg = 0, decima = 0;
bit stop_actual, stop_pasado, start_actual, start_pasado, reset_actual, reset_pasado, set_start = 0;

void iniPorts( void );
void iniciar( void );
void pausa( void );
void reiniciar( void );
void cronometro( void );

void main(void){
    iniPorts();
    while( 1 ){
        iniciar();
        pausa();
        reiniciar();
        if( set_start )
            cronometro();    
        SEGUNDOS = contador[ seg ];
        UNI_SEG = contador[ uni_seg ];
        DECIMA = contador[ decima ];
    }
}

void iniPorts( void ){
    // Port A initialization
    // Function: Bit7=In Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
    DDRA=(0<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
    // State: Bit7=T Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
    PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

    // Port B initialization
    // Function: Bit7=In Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
    DDRB=(0<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
    // State: Bit7=T Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
    PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

    // Port C initialization
    // Function: Bit7=In Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
    DDRC=(0<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
    // State: Bit7=T Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
    PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

    // Port D initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
    DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=P Bit1=P Bit0=P 
    PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);
}

void iniciar( void ){
    if( !START )
        start_actual = 0;
    else
        start_actual = 1;    
    if( start_pasado && !start_actual ){
        set_start = 1;
        delay_ms( 40 );
    }
    if( !start_pasado &&  start_actual )
        delay_ms( 40 );    
    start_pasado = start_actual;
}

void pausa( void ){
    if( !STOP )
        stop_actual = 0;
    else
        stop_actual = 1;    
    if( stop_pasado && !stop_actual )
        set_start = 0;  
    if( !stop_pasado && stop_actual )
        delay_ms( 40 );    
    stop_pasado = stop_actual;
}

void reiniciar( void ){
    if( !RESET )
        reset_actual = 0;
    else
        reset_actual = 1;    
    if( reset_pasado && !reset_actual ){
        seg = 0;
        uni_seg = 0;
        decima = 0;
    }
    if( !reset_pasado && reset_actual )
        delay_ms( 40 );
    reset_pasado = reset_actual;    
}

void cronometro( void ){
    decima++;
    if( decima == 10 ){
        decima = 0;
        uni_seg++;
        if( uni_seg == 10 ){
            uni_seg = 0;
            seg++;
            if( seg == 6 )
                seg = 0;
        }    
    }
    delay_ms( 40 );    
}