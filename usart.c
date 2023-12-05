#include <xc.h>
#include "LCD.h"


//CONFIG bits for PIC18F87J11
#pragma config FOSC=HSPLL
#pragma config WDTEN=OFF
#pragma config XINST=OFF

void InitPins(void);
void ConfigInterrupts(void);
void ConfigPeriph(void);

char rx;
char rxBuffer[20];
volatile int txCount;
volatile int rxCount;

char txStr[] = "Hello World\n";

void main(void) {
    txCount = rxCount = 0;
    OSCTUNEbits.PLLEN = 1;
    LCDInit();
    LCDClear();
    InitPins();
    ConfigPeriph();
    ConfigInterrupts();
    TXSTA1bits.TXEN = 1; //Turn on TX

    //Main loop
    while (1) {
        //Check the button
        if (PORTBbits.RB0 == 0) {
            //Put code here that executes when the button is pressed
        }
                
        //Check for a received byte
        if (PIR1bits.RC1IF == 1) { //A byte is available from USART
            rx = RCREG1; //Read the received byte
            rxBuffer[rxCount] = rx; //save the byte into the string buffer
            if (rxBuffer[rxCount] == '\r') { //check for CR
                rxBuffer[rxCount] = '\0'; //Terminate the string
                lprintf(0, rxBuffer);
                rxCount = 0;
                LATDbits.LATD1 ^= 1; //Toggle LED D2
            } else if (rxCount < 16) {
                ++rxCount;
                LATDbits.LATD0 ^= 1; //Toggle LED D1
            }
        }
    }
}

void InitPins(void) {
    LATD = 0; //Turn off all LED's
    TRISD = 0; //LED's are outputs
    TRISB = 0b00000001; //Set RB0 as input (this is the button)
    
    //Set the TX and RX pins to the correct direction
    TRISC = 0b10000000; //RC7 is RX, RC6 is TX

}

void ConfigInterrupts(void) {

    //Enable interrupt when USART transmit buffer is empty
    PIE1bits.TX1IE = 1; //enable tx interrupt

    //Turn on all enabled interrupts
    INTCONbits.PEIE = 1; //turn on peripheral interrupts
    INTCONbits.GIE = 1; //Turn on interrupts
}

void ConfigPeriph(void) {

    //Configure peripherals here

    //Configure the USART for 9600 baud asynchronous transmission
    SPBRG1 = 832; //9600 baud
    SPBRGH1 = 832 >> 8;
    TXSTA1bits.BRGH = 1;
    BAUDCON1bits.BRG16 = 1;
    TXSTA1bits.SYNC = 0; //asynchronous mode
    RCSTA1bits.SPEN = 1; //Enable the serial port
    RCSTA1bits.CREN = 1; //Enable reception

}

void __interrupt(high_priority) HighIsr(void) {
    //Check the source of the interrupt
    if (PIR1bits.TX1IF == 1) {
        //Transmit register is empty
        TXREG1 = txStr[txCount]; //Send the next character from the string
        ++txCount;
        if (txStr[txCount] == '\0') { //Check for the end of the string
            txCount = 0;
        }
    }
}



