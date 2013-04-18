#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdlib.h>
#include "DHT.h"

// uint8_t DHT_Read_Data(uint8_t select);
void USARTInit(uint16_t ubrr_value);
char USARTReadChar();
void USARTWriteChar(char data);
void USART_putstring(char* StringPtr);

void main()
{
	char charData[8];
	uint8_t data;
	char String[]="Hello world!\n\r";
	USARTInit(51);
   
	DDRC |= _BV(PC4);    //Set pin Output
	PORTC |= _BV(PC4);

	while(1)
	{
		//data=USARTReadChar();
		data = DHT_Read_Data(0);
		//data = 5;
		itoa(data, charData, 10);
		USART_putstring(charData); //Pass the string to the USART_putstring function and sends it over the serial
		//USARTWriteChar('\n');
		//USARTWriteChar('\r');
		//USART_putstring(String);
		//PORTC &= _BV(PC4);    //Pin High		
		_delay_ms(1000);
	}
   
	return;
}

//This function is used to initialize the USART at a given UBRR value
void USARTInit(uint16_t ubrr_value)
{
   //Set Baud rate
   UBRRL = ubrr_value;
   UBRRH = (ubrr_value>>8);

   /*Set Frame Format
   >> Asynchronous mode
   >> No Parity
   >> 1 StopBit
   >> char size 8   */
   UCSRC=(1<<URSEL)|(3<<UCSZ0);
   
   //Enable The receiver and transmitter
   UCSRB=(1<<RXEN)|(1<<TXEN);
}

char USARTReadChar()
{
   //Wait until data is available
   while(!(UCSRA & (1<<RXC))){}
   return UDR;
}

void USARTWriteChar(char data)
{
   //Wait until the transmitter is ready
   while(!(UCSRA & (1<<UDRE))){}
   UDR=data;
}

void USART_putstring(char* StringPtr){

	while(*StringPtr != 0x00){
		USARTWriteChar(*StringPtr);
		StringPtr++;}
}