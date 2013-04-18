/*
 DHT-11 Library
 Adapted from Charalampos Andrianakis's code.
 */

#include "DHT.h"

uint8_t DHT_Read_Data(uint8_t select){

    //data[5] is 8byte table where data come from DHT are stored
    //laststate holds laststate value
    //counter is used to count microSeconds
    uint8_t data[5], laststate = 0, counter = 0, j = 0, i = 0;
    
    //Clear array
    data[0] = data[1] = data[2] = data[3] = data[4] = 0;
    
    cli();                              //Disable interrupts
    
    //Prepare the bus
    DDRC   |= (1<<PC0);    //Set pin Output
    PORTC        |= (1<<PC0);    //Pin High
    _delay_ms(250);                     //Wait for 250mS
    
    //Send Request Signal
    PORTC        &=~(1<<PC0);    //Pin Low
    _delay_ms(20);                      //20ms Low 
    
    PORTC        |= (1<<PC0);    //Pin High
    _delay_us(40);                      //40us High
	
    //Set pin Input to read Bus
    DDRC   &=~(1<<PC0);    //Set pin Input

    laststate=DHT_Read_Pin;             //Read Pin value
    
    //Repeat for each Transistions
    for (i=0; i<MAXTIMINGS; i++) {

        //While state is the same count microseconds
        while (laststate==DHT_Read_Pin) {
            _delay_us(1);			
            counter++;
        }
        //USARTWriteChar('p');
        //laststate==(1<<PC0) checks if laststate was High
        //ignore the first 2 transitions which are the DHT Response
        if (laststate==(1<<PC0) && (i > 2)) {
            //Save bits in segments of bytes
            //Shift data[] value 1 position left
            //Example. 01010100 if we shift it left one time it will be
            //10101000
            data[j/8]<<=1;
            if (counter >= 40) {    //If it was high for more than 40uS
                data[j/8]|=1;       //it means it is bit '1' so make a logic
            }                       //OR with the value (save it)
            j++;                    //making an OR by 1 to this value 10101000
        }                           //we will have the resault 10101001
                                    //1 in 8-bit binary is 00000001
        //j/8 changes table record every 8 bits which means a byte has been saved
        //so change to next record. 0/8=0 1/8=0 ... 7/8=0 8/8=1 ... 15/8=1 16/8=2
        laststate=DHT_Read_Pin;     //save current state
        counter=0;                  //reset counter
        
    }
    sei();                          //Enable interrupts
    
    //Check if DHT-11 is connected
    if (data[0]==0 && data[1]==0 && data[2]==0 && data[3]==0) {
        //uart_puts("\r\nDHT not pluged!");
        return(4);
    }
    //Check if data received are correct by checking the CheckSum
    if (data[0] + data[1] + data[2] + data[3] == data[4]) {
        if (select==DHT_Temp) {     //Return the value has been choosen
            return(data[2]);
        }else if(select==DHT_RH){
            return(data[0]);
        }
    }else{
		return(8);
        //uart_puts("\r\nCheck Sum Error");
    }
}
