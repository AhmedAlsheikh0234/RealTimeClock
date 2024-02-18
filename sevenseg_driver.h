/*
 * sevenseg_driver.h
 *
 * Created: 2/4/2024 4:34:32 PM
 *  Author: HaNdSyA---
 */ 


#ifndef SEVENSEG_DRIVER_H_
#define SEVENSEG_DRIVER_H_

#define PIN 0

#define cc

void sevensegBCD_init(unsigned char port);
void sevensegBCD_write(unsigned char port,unsigned char number);
void sevenseg_init(unsigned char port);
void sevenseg_write(unsigned char port,unsigned char number);


#endif /* SEVENSEG_DRIVER_H_ */