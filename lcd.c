#include "lcd.h"

// User interface
void lcd_init()
{
    LCD_USCI_PSEL |= LCD_USCI_CLK_MASK | LCD_USCI_SIMO_MASK;
    LCD_USCI_PSEL2 |= LCD_USCI_CLK_MASK | LCD_USCI_SIMO_MASK;
    LCD_USCI_CTL1 = UCSWRST;
    LCD_USCI_CTL1 |= UCSSEL_2;
    LCD_USCI_CTL0 = UCMSB + UCMST + UCSYNC + UCCKPL;
    LCD_USCI_CTL1 &= ~UCSWRST;

    LCD_CTL_PDIR |= LCD_SR_LATCH_MASK | LCD_EN_MASK | LCD_RS_MASK;

    lcd_delay_micros(50000);

    lcd_send_cmd( LCD_FUNCTIONSET | LCD_8BITMODE | LCD_2LINE );
    lcd_delay_micros(4500);

    lcd_send_cmd( LCD_FUNCTIONSET | LCD_8BITMODE | LCD_2LINE );
    lcd_delay_micros(150);

    lcd_send_cmd( LCD_FUNCTIONSET | LCD_8BITMODE | LCD_2LINE );

    lcd_send_cmd( LCD_FUNCTIONSET | LCD_8BITMODE | LCD_2LINE );

    lcd_send_cmd( LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF );

    lcd_send_cmd( LCD_CLEARDISPLAY );
    lcd_delay_micros(2000);

    lcd_send_cmd( LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT );
}

void lcd_set_row( char row )
{
	if( row == 0 )
	{
		lcd_send_cmd( LCD_SETDDRAMADDR | 0x00 );
	}else{
		lcd_send_cmd( LCD_SETDDRAMADDR | 0x40 );
	}
}

void lcd_write( const char* str )
{
	register int i=0;

	while( str[i] != '\0' )
	{
		lcd_send_data( str[i++] );
	}
}

// Helpers
void lcd_send_data( char data )
{
	LCD_CTL_POUT |= LCD_RS_MASK;
	lcd_send( data );
}

void lcd_send_cmd( char cmd )
{
	LCD_CTL_POUT &= ~LCD_RS_MASK;
	lcd_send( cmd );
}

void lcd_send( char cmd )
{
	LCD_CTL_POUT &= ~LCD_SR_LATCH_MASK;
	LCD_USCI_TXBUF = cmd;
	while( LCD_USCI_STAT & UCBUSY )
	{

	}
	LCD_CTL_POUT |= LCD_SR_LATCH_MASK;
    lcd_pulse_enable();
}

void lcd_pulse_enable()
{
	LCD_CTL_POUT &= ~LCD_EN_MASK;
	lcd_delay_micros(1);
	LCD_CTL_POUT |= LCD_EN_MASK;		// Pulse the enable line
	lcd_delay_micros(1);
	LCD_CTL_POUT &= ~LCD_EN_MASK;
	lcd_delay_micros(100);
}

void lcd_delay_micros( unsigned int delay )
{
	unsigned int i;
	for( i = 0; i < delay; ++i )
	{
		_delay_cycles(16);
	}
}
