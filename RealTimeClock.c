/*
 * RealTimeClock.c
 *
 * Created: 2/4/2024 9:39:13 PM
 *  Author: Ahmed Al-Sheikh
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "sevenseg_driver.h"
#include "LCD_driver.h"
#include "keybad_driver.h"
#include "timer.h"
#include "macros.h"

volatile unsigned char sec_c=0;

int main(void)
{
	unsigned char min_c=0,h_c=0,val,first_digit,sec_digit;
	LCD_init();
	keybad_init();
	sevenseg_init('A');
	set_bit(DDRC,0);
	set_bit(DDRC,1);
	set_bit(DDRC,2);
	set_bit(DDRC,3);
	set_bit(DDRC,4);
	set_bit(DDRC,5);
	LCD_sendstring("Created by Ahmed");
	_delay_ms(1000);
	LCD_clearscr();
	LCD_sendstring("Press 5 to");
	LCD_movecursor(2,1);
	LCD_sendstring("Adjust Clock");
	timer2_overflow_init();
    while(1)
    {
		val=keybad_checkpress();
		if (val!=NOTPRESSED)    //button is pressed
		{
			if (val=='5')  //right button pressed
			{
				hours:
				LCD_clearscr();
				LCD_sendstring("Hours=");
				LCD_movecursor(1,7);
				_delay_ms(200);
				do 
				{
					sec_digit=keybad_checkpress();
				} while (sec_digit==NOTPRESSED);
				LCD_sendchar(sec_digit);
				_delay_ms(200);
				do 
				{
					first_digit=keybad_checkpress();
				} while (first_digit==NOTPRESSED);
				LCD_sendchar(first_digit);
				_delay_ms(200);
				h_c=(sec_digit-48)*10+(first_digit-48);
				LCD_clearscr();
				if (h_c>24)
				{
					LCD_sendstring("Hours cant be");
					LCD_movecursor(2,1);
					LCD_sendstring("more than 24");
					_delay_ms(1000);
					LCD_clearscr();
					LCD_sendstring("Enter Again");
					_delay_ms(1000);
					LCD_clearscr();
					goto hours;
				}
				minutes:                                       //end of hours counter entry code
				LCD_sendstring("Minutes=");
				LCD_movecursor(1,9);
				_delay_ms(200);
				do
				{
					sec_digit=keybad_checkpress();
				} while (sec_digit==NOTPRESSED);
				LCD_sendchar(sec_digit);
				_delay_ms(200);
				do
				{
					first_digit=keybad_checkpress();
				} while (first_digit==NOTPRESSED);
				LCD_sendchar(first_digit);
				_delay_ms(200);
				min_c=(sec_digit-48)*10+(first_digit-48);
				LCD_clearscr();
				if (min_c>=60)
				{
					LCD_sendstring("Minutes cant be");
					LCD_movecursor(2,1);
					LCD_sendstring("More than 60");
					_delay_ms(1000);
					LCD_clearscr();
					LCD_sendstring("Enter Again");
					_delay_ms(1000);
					LCD_clearscr();
					goto minutes;
				}                                      //end of minutes counter entry code
				seconds:
				LCD_sendstring("Seconds=");
				LCD_movecursor(1,9);
				_delay_ms(200);
				do
				{
					sec_digit=keybad_checkpress();
				} while (sec_digit==NOTPRESSED);
				LCD_sendchar(sec_digit);
				_delay_ms(200);
				do
				{
					first_digit=keybad_checkpress();
				} while (first_digit==NOTPRESSED);
				LCD_sendchar(first_digit);
				_delay_ms(200);
				sec_c=(sec_digit-48)*10+(first_digit-48);
				LCD_clearscr();
				if (sec_c>=60)
				{
					LCD_sendstring("Seconds cant be");
					LCD_movecursor(2,1);
					LCD_sendstring("More than 60");
					_delay_ms(1000);
					LCD_clearscr();
					LCD_sendstring("Enter Again");
					_delay_ms(1000);
					LCD_clearscr();
					goto seconds;
				}
				else
				{
					LCD_sendstring("Press 5 to");
					LCD_movecursor(2,1);
					LCD_sendstring("Adjust Clock");
				}
				                       //end of seconds counter entry code			   
			}	  	    	
			else
			{
				LCD_clearscr();
				LCD_sendstring("Please Press 5");
				_delay_ms(1000);
				LCD_clearscr();
				LCD_sendstring("Press 5 to");
				LCD_movecursor(2,1);
				LCD_sendstring("Adjust Clock");
			}
		}
		clr_bit(PORTC,5);
		set_bit(PORTC,0);
		set_bit(PORTC,1);
		set_bit(PORTC,2);
		set_bit(PORTC,3);
		set_bit(PORTC,4);         
		sevenseg_write('A',sec_c%10);
		_delay_ms(3);                    // activating first digit of seconds counter
		
		clr_bit(PORTC,4);
		set_bit(PORTC,0);
		set_bit(PORTC,1);
		set_bit(PORTC,2);
		set_bit(PORTC,3);
		set_bit(PORTC,5);
		sevenseg_write('A',sec_c/10);
		_delay_ms(3);                    //activating second digit of seconds counter
		
		clr_bit(PORTC,3);
		set_bit(PORTC,0);
		set_bit(PORTC,1);
		set_bit(PORTC,2);
		set_bit(PORTC,4);
		set_bit(PORTC,5);
		sevenseg_write('A',min_c%10);
		_delay_ms(3);                  //activating first digit of minutes counter
        
		clr_bit(PORTC,2);
		set_bit(PORTC,0);
		set_bit(PORTC,1);
		set_bit(PORTC,4);
		set_bit(PORTC,3);
		set_bit(PORTC,5);
		sevenseg_write('A',min_c/10);   //activating second digit of minutes counter
		_delay_ms(3);
		
		clr_bit(PORTC,1);
		set_bit(PORTC,0);
		set_bit(PORTC,4);
		set_bit(PORTC,2);
		set_bit(PORTC,3);
		set_bit(PORTC,5);
		sevenseg_write('A',h_c%10);
		_delay_ms(3);                   //activating first digit of hours counter
		
		clr_bit(PORTC,0);
		set_bit(PORTC,4);
		set_bit(PORTC,1);
		set_bit(PORTC,2);
		set_bit(PORTC,3);
		set_bit(PORTC,5);
		sevenseg_write('A',h_c/10);    //activating second digit of hours counter
		_delay_ms(3);
		
		if (sec_c>=60)
		{
			sec_c=0;
			min_c++;
		}
		if (min_c>=60)
		{
			min_c=0;
			h_c++;
		}
		if (h_c>=24)
		{
			
			h_c=0;
		}
    }
	
}
ISR(TIMER2_OVF_vect)
{
	sec_c++;
}