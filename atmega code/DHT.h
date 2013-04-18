/*
 DHT-11 Library
 Adapted from Charalampos Andrianakis's code.
 */
 
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
 
//DHT Pin and Port
#define DHT_PORT    PORTC
#define DHT_PIN     0

//The packet size is 40bit but each bit consists of low and high state
//so 40 x 2 = 80 transitions. Also we have 2 transistions DHT response
//and 2 transitions which indicates End Of Frame. In total 84
#define MAXTIMINGS  84

//Select between Temp and Humidity Read
#define DHT_Temp    0
#define DHT_RH      1

#define DHT_Read_Pin    (PINC & _BV(PC0))

#define F_CPU 16000000

//This is the main function which requests and reads the packet
uint8_t DHT_Read_Data(uint8_t select);

