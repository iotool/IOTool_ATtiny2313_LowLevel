// Low level api to program ATtiny2313 at Arduino IDE 1.6.x
// to reduce the binary code (maximum 2048 bytes).
// 
// https://github.com/iotool/IOTool_ATtiny2313_LowLevel
// 
// RST/PA2 (1)         (20) VCC 
// RXD/PD0-(2)[0]  [16](19)-PB7/SCL
// TXD/PD1-(3)[1]  [15](18)-PB6/MISO
// XT2/PA1-(4)[2]  [14](17)-PB5/MOSI/SDA
// XT1/PA0-(5)[3]  [13](16)-PB4/PWM
// CLK/PD2-(6)[4]  [12](15)-PB3/PWM
//     PD3-(7)[5]  [11](14)-PB2/PWM
//     PD4-(8)[6]  [10](13)-PB1/ADC
// PWM/PD5-(9)[7]   [9](12)-PB0/ADC 
//     GND (10)     [8](11)-PD6
// 
// INPUT_PULLUP = PINMODE_INPUT; DIGITALWRITE_HIGH;
// 
// 2020-07-08  RoHa  v1.0 read/write pins


#ifndef IOTOOL_ATTINY2313_LOWLEVEL_H_
#define IOTOOL_ATTINY2313_LOWLEVEL_H_

#ifdef IOTOOL__F_CPU
#define F_CPU IOTOOL__F_CPU  // delay cpu clock overwrite
#else
#define F_CPU 1000000UL      // delay cpu clock 1.0 mhz
#endif

#include <avr/io.h>          // low level pinmode
#include <avr/interrupt.h>   // timer interrupt for sleep
#include <avr/sleep.h>       // sleep to reduce power
#include <util/delay.h>      // low level delay

// delay @ 1.2 MHz
#define DELAY_1MS    _delay_ms(1)
#define DELAY_5MS    _delay_ms(5)
#define DELAY_10MS   _delay_ms(10)
#define DELAY_50MS   _delay_ms(50)
#define DELAY_100MS  _delay_ms(100)
#define DELAY_320MS  _delay_ms(320)
#define DELAY_500MS  _delay_ms(500)
#define DELAY_1S     _delay_ms(1000)

#define PINMODE_PA0_INPUT   DDRA &= ~(1 << PA0)
#define PINMODE_PA1_INPUT   DDRA &= ~(1 << PA1)
#define PINMODE_PA2_INPUT   DDRA &= ~(1 << PA2)
#define PINMODE_PA0_OUTPUT  DDRA |= (1 << PA0)
#define PINMODE_PA1_OUTPUT  DDRA |= (1 << PA1)
#define PINMODE_PA2_OUTPUT  DDRA |= (1 << PA2)

#define PINMODE_PB0_INPUT   DDRB &= ~(1 << PB0)
#define PINMODE_PB1_INPUT   DDRB &= ~(1 << PB1)
#define PINMODE_PB2_INPUT   DDRB &= ~(1 << PB2)
#define PINMODE_PB3_INPUT   DDRB &= ~(1 << PB3)
#define PINMODE_PB4_INPUT   DDRB &= ~(1 << PB4)
#define PINMODE_PB5_INPUT   DDRB &= ~(1 << PB5)
#define PINMODE_PB6_INPUT   DDRB &= ~(1 << PB6)
#define PINMODE_PB7_INPUT   DDRB &= ~(1 << PB7)
#define PINMODE_PB0_OUTPUT  DDRB |= (1 << PB0)
#define PINMODE_PB1_OUTPUT  DDRB |= (1 << PB1)
#define PINMODE_PB2_OUTPUT  DDRB |= (1 << PB2)
#define PINMODE_PB3_OUTPUT  DDRB |= (1 << PB3)
#define PINMODE_PB4_OUTPUT  DDRB |= (1 << PB4)
#define PINMODE_PB5_OUTPUT  DDRB |= (1 << PB5)
#define PINMODE_PB6_OUTPUT  DDRB |= (1 << PB6)
#define PINMODE_PB7_OUTPUT  DDRB |= (1 << PB7)

#define PINMODE_PD0_INPUT   DDRD &= ~(1 << PD0)
#define PINMODE_PD1_INPUT   DDRD &= ~(1 << PD1)
#define PINMODE_PD2_INPUT   DDRD &= ~(1 << PD2)
#define PINMODE_PD3_INPUT   DDRD &= ~(1 << PD3)
#define PINMODE_PD4_INPUT   DDRD &= ~(1 << PD4)
#define PINMODE_PD5_INPUT   DDRD &= ~(1 << PD5)
#define PINMODE_PD6_INPUT   DDRD &= ~(1 << PD6)
#define PINMODE_PD0_OUTPUT  DDRD |= (1 << PD0)
#define PINMODE_PD1_OUTPUT  DDRD |= (1 << PD1)
#define PINMODE_PD2_OUTPUT  DDRD |= (1 << PD2)
#define PINMODE_PD3_OUTPUT  DDRD |= (1 << PD3)
#define PINMODE_PD4_OUTPUT  DDRD |= (1 << PD4)
#define PINMODE_PD5_OUTPUT  DDRD |= (1 << PD5)
#define PINMODE_PD6_OUTPUT  DDRD |= (1 << PD6)

#define DIGITALWRITE_PA0_LOW     PORTA &= ~(1 << PA0)
#define DIGITALWRITE_PA1_LOW     PORTA &= ~(1 << PA1)
#define DIGITALWRITE_PA2_LOW     PORTA &= ~(1 << PA2)
#define DIGITALWRITE_PA0_HIGH    PORTA |= (1 << PA0)
#define DIGITALWRITE_PA1_HIGH    PORTA |= (1 << PA1)
#define DIGITALWRITE_PA2_HIGH    PORTA |= (1 << PA2)
#define DIGITALWRITE_PA0_TOGGLE  PORTA ^= (1 << PA0)
#define DIGITALWRITE_PA1_TOGGLE  PORTA ^= (1 << PA1)
#define DIGITALWRITE_PA2_TOGGLE  PORTA ^= (1 << PA2)

#define DIGITALWRITE_PB0_LOW     PORTB &= ~(1 << PB0)
#define DIGITALWRITE_PB1_LOW     PORTB &= ~(1 << PB1)
#define DIGITALWRITE_PB2_LOW     PORTB &= ~(1 << PB2)
#define DIGITALWRITE_PB3_LOW     PORTB &= ~(1 << PB3)
#define DIGITALWRITE_PB4_LOW     PORTB &= ~(1 << PB4)
#define DIGITALWRITE_PB5_LOW     PORTB &= ~(1 << PB5)
#define DIGITALWRITE_PB6_LOW     PORTB &= ~(1 << PB6)
#define DIGITALWRITE_PB7_LOW     PORTB &= ~(1 << PB7)
#define DIGITALWRITE_PB0_HIGH    PORTB |= (1 << PB0)
#define DIGITALWRITE_PB1_HIGH    PORTB |= (1 << PB1)
#define DIGITALWRITE_PB2_HIGH    PORTB |= (1 << PB2)
#define DIGITALWRITE_PB3_HIGH    PORTB |= (1 << PB3)
#define DIGITALWRITE_PB4_HIGH    PORTB |= (1 << PB4)
#define DIGITALWRITE_PB5_HIGH    PORTB |= (1 << PB5)
#define DIGITALWRITE_PB6_HIGH    PORTB |= (1 << PB6)
#define DIGITALWRITE_PB7_HIGH    PORTB |= (1 << PB7)
#define DIGITALWRITE_PB0_TOGGLE  PORTB ^= (1 << PB0)
#define DIGITALWRITE_PB1_TOGGLE  PORTB ^= (1 << PB1)
#define DIGITALWRITE_PB2_TOGGLE  PORTB ^= (1 << PB2)
#define DIGITALWRITE_PB3_TOGGLE  PORTB ^= (1 << PB3)
#define DIGITALWRITE_PB4_TOGGLE  PORTB ^= (1 << PB4)
#define DIGITALWRITE_PB5_TOGGLE  PORTB ^= (1 << PB5)
#define DIGITALWRITE_PB6_TOGGLE  PORTB ^= (1 << PB6)
#define DIGITALWRITE_PB7_TOGGLE  PORTB ^= (1 << PB7)

#define DIGITALWRITE_PD0_LOW     PORTD &= ~(1 << PD0)
#define DIGITALWRITE_PD1_LOW     PORTD &= ~(1 << PD1)
#define DIGITALWRITE_PD2_LOW     PORTD &= ~(1 << PD2)
#define DIGITALWRITE_PD3_LOW     PORTD &= ~(1 << PD3)
#define DIGITALWRITE_PD4_LOW     PORTD &= ~(1 << PD4)
#define DIGITALWRITE_PD5_LOW     PORTD &= ~(1 << PD5)
#define DIGITALWRITE_PD6_LOW     PORTD &= ~(1 << PD6)
#define DIGITALWRITE_PD0_HIGH    PORTD |= (1 << PD0)
#define DIGITALWRITE_PD1_HIGH    PORTD |= (1 << PD1)
#define DIGITALWRITE_PD2_HIGH    PORTD |= (1 << PD2)
#define DIGITALWRITE_PD3_HIGH    PORTD |= (1 << PD3)
#define DIGITALWRITE_PD4_HIGH    PORTD |= (1 << PD4)
#define DIGITALWRITE_PD5_HIGH    PORTD |= (1 << PD5)
#define DIGITALWRITE_PD6_HIGH    PORTD |= (1 << PD6)
#define DIGITALWRITE_PD0_TOGGLE  PORTD ^= (1 << PD0)
#define DIGITALWRITE_PD1_TOGGLE  PORTD ^= (1 << PD1)
#define DIGITALWRITE_PD2_TOGGLE  PORTD ^= (1 << PD2)
#define DIGITALWRITE_PD3_TOGGLE  PORTD ^= (1 << PD3)
#define DIGITALWRITE_PD4_TOGGLE  PORTD ^= (1 << PD4)
#define DIGITALWRITE_PD5_TOGGLE  PORTD ^= (1 << PD5)
#define DIGITALWRITE_PD6_TOGGLE  PORTD ^= (1 << PD6)

#define DIGITALREAD_PA0_LOW   (PINA & (1 << PA0))
#define DIGITALREAD_PA1_LOW   (PINA & (1 << PA1))
#define DIGITALREAD_PA2_LOW   (PINA & (1 << PA2))
#define DIGITALREAD_PA0_HIGH  !(PINA & (1 << PA0))
#define DIGITALREAD_PA1_HIGH  !(PINA & (1 << PA1))
#define DIGITALREAD_PA2_HIGH  !(PINA & (1 << PA2))

#define DIGITALREAD_PB0_LOW   (PINB & (1 << PB0))
#define DIGITALREAD_PB1_LOW   (PINB & (1 << PB1))
#define DIGITALREAD_PB2_LOW   (PINB & (1 << PB2))
#define DIGITALREAD_PB3_LOW   (PINB & (1 << PB3))
#define DIGITALREAD_PB4_LOW   (PINB & (1 << PB4))
#define DIGITALREAD_PB5_LOW   (PINB & (1 << PB5))
#define DIGITALREAD_PB6_LOW   (PINB & (1 << PB6))
#define DIGITALREAD_PB7_LOW   (PINB & (1 << PB7))
#define DIGITALREAD_PB0_HIGH  !(PINB & (1 << PB0))
#define DIGITALREAD_PB1_HIGH  !(PINB & (1 << PB1))
#define DIGITALREAD_PB2_HIGH  !(PINB & (1 << PB2))
#define DIGITALREAD_PB3_HIGH  !(PINB & (1 << PB3))
#define DIGITALREAD_PB4_HIGH  !(PINB & (1 << PB4))
#define DIGITALREAD_PB5_HIGH  !(PINB & (1 << PB5))
#define DIGITALREAD_PB6_HIGH  !(PINB & (1 << PB6))
#define DIGITALREAD_PB7_HIGH  !(PINB & (1 << PB7))

#define DIGITALREAD_PD0_LOW   (PIND & (1 << PD0))
#define DIGITALREAD_PD1_LOW   (PIND & (1 << PD1))
#define DIGITALREAD_PD2_LOW   (PIND & (1 << PD2))
#define DIGITALREAD_PD3_LOW   (PIND & (1 << PD3))
#define DIGITALREAD_PD4_LOW   (PIND & (1 << PD4))
#define DIGITALREAD_PD5_LOW   (PIND & (1 << PD5))
#define DIGITALREAD_PD6_LOW   (PIND & (1 << PD6))
#define DIGITALREAD_PD0_HIGH  !(PIND & (1 << PD0))
#define DIGITALREAD_PD1_HIGH  !(PIND & (1 << PD1))
#define DIGITALREAD_PD2_HIGH  !(PIND & (1 << PD2))
#define DIGITALREAD_PD3_HIGH  !(PIND & (1 << PD3))
#define DIGITALREAD_PD4_HIGH  !(PIND & (1 << PD4))
#define DIGITALREAD_PD5_HIGH  !(PIND & (1 << PD5))
#define DIGITALREAD_PD6_HIGH  !(PIND & (1 << PD6))

#endif // IOTOOL_ATTINY2313_LOWLEVEL_H_
