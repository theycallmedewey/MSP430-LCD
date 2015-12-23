#ifndef LCD_H
#define LCD_H

#include <msp430.h>

// Define the USCI to use for sending bytes to the shift register
#define LCD_USCI 			UCA0
#define LCD_USCI_PORT 		P1
#define LCD_USCI_CLK_MASK 	BIT2
#define LCD_USCI_SIMO_MASK	BIT4

#define LCD_CTL_PORT		P1
#define LCD_SR_LATCH_MASK	BIT1
#define LCD_EN_MASK			BIT0
#define LCD_RS_MASK			BIT5

//Generate buffer names from the configured values
#define PORT_CAT(port,buf)  port ## buf
#define GET_PORTDIR(port)	PORT_CAT(port,DIR)
#define GET_PORTOUT(port)	PORT_CAT(port,OUT)
#define GET_PORTSEL(port)	PORT_CAT(port,SEL)
#define GET_PORTSEL2(port)	PORT_CAT(port,SEL2)
#define GET_USCITXBUF(usci)	PORT_CAT(usci,TXBUF)
#define GET_USCICTL0(usci)	PORT_CAT(usci,CTL0)
#define GET_USCICTL1(usci)	PORT_CAT(usci,CTL1)
#define GET_USCISTAT(usci)	PORT_CAT(usci,STAT)

#define LCD_USCI_TXBUF 	GET_USCITXBUF(LCD_USCI)
#define LCD_USCI_STAT	GET_USCISTAT(LCD_USCI)
#define LCD_USCI_CTL0  	GET_USCICTL0(LCD_USCI)
#define LCD_USCI_CTL1  	GET_USCICTL1(LCD_USCI)
#define LCD_USCI_PSEL 	GET_PORTSEL(LCD_USCI_PORT)
#define LCD_USCI_PSEL2	GET_PORTSEL2(LCD_USCI_PORT)

#define LCD_CTL_PDIR	GET_PORTDIR(LCD_CTL_PORT)
#define LCD_CTL_POUT	GET_PORTOUT(LCD_CTL_PORT)

// User interface
void lcd_init();
void lcd_set_row( char row );
void lcd_write( const char* str );

// Helpers
void lcd_send_data( char data );
void lcd_send_cmd( char cmd );
void lcd_send( char cmd );
void lcd_pulse_enable();
void lcd_delay_micros();

// Important commands, etc
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_2LINE 0x08
#define LCD_5x8DOTS 0x00

#endif
