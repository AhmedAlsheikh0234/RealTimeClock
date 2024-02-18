/*
 * sevenseg_driver.c
 *
 * Created: 2/4/2024 4:33:13 PM
 *  Author: HaNdSyA---
 */ 
#include <avr/io.h>              //This code is usable for !!BCD decoder with comm Anode 7seg!!
#include "DIO_driver.h"
#include "sevenseg_driver.h"
#ifdef cc
unsigned char arr[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
#else
unsigned char arr[]={~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F};
#endif
		                                     
void sevensegBCD_init(unsigned char port)             
{
	DIO_setpindir(port,PIN,1);
	DIO_setpindir(port,PIN+1,1);
	DIO_setpindir(port,PIN+2,1);
	DIO_setpindir(port,PIN+3,1);
} 
void sevensegBCD_write(unsigned char port,unsigned char number)
{
	DIO_writelownipple(port,number);                   //when connected on low nipple pins change to high nipple if pins are 4+
}
void sevenseg_init(unsigned char port)
{
	DIO_setportdir(port,0xff);
}
void sevenseg_write(unsigned char port,unsigned char number)
{
	DIO_portwrite(port,arr[number]);
}	