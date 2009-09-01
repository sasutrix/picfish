#include <16F887.h>
#include <stdlib.h>
#use delay(clock=8000000)
#include "flex_lcd.c"
#include "1wire.c"
#include "ds1820.c"

//#define ONE_WIRE_PIN PIN_E2
#use rs232(baud=9600, UART1)


#fuses MCLR,NOPROTECT,NOWDT, HS


void main()
{
    float temperature; 
    char text[20];


	lcd_init();
    lcd_putc("\f"); //limpa o lcd
	lcd_putc("Inicializando"); //o buffer do lcd é de 40 chars
	lcd_gotoxy(1,2);
	lcd_putc("LCD...");
	delay_ms(500);
	lcd_gotoxy(1,2);
	lcd_putc("DS18x20...");
	delay_ms(500);
	lcd_gotoxy(1,2);	
	lcd_putc("          ");	
		

	while(TRUE){
		output_high(PIN_A0);
		delay_ms(500);    
		temperature = ds1820_read();
		printf("%6.4f\n\r", temperature);
		//lcd_gotoxy(1,2);
		//lcd_putc(text);
        output_low(PIN_A0);
		delay_ms(500);
       
	}
}
