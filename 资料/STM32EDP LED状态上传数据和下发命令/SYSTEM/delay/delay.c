#include "delay.h" 

// Header:
// File Name: 
// Author:
// Date:

void delay_us( int i)
 {     
    while( i--)
       {	

        }
 }		  

// Header:
// File Name: 
// Author:
// Date:

void delay_ms(unsigned int time)
	 {
	  while(time--)
	  	  {	
		   delay_us(1000);
		   
		  }
	 }




























