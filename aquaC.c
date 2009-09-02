#include <16F887.h>
#include <stdlib.h>
#include <global.h>
#use delay(clock=8000000)
#include "flex_lcd.c"
#include "1wire.c"
#include "ds1820.c"
#include "ds1307.c"

#use rs232(baud=9600, UART1)


#fuses MCLR,NOPROTECT,NOWDT, HS


void main()
{
    float temperature;
	byte sec, min, hrs; 
    //byte day, month,yr; 
    //byte dow; 

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
	lcd_putc("DS1307....");
	ds1307_init();
	delay_ms(500);

	lcd_putc("\f"); //limpa o lcd	
		

	while(TRUE){
		output_high(PIN_A0);
		delay_ms(50);    
	  
    	temperature = ds1820_read();
		lcd_gotoxy(10,1);
		printf(lcd_putc,"%03.1f", temperature);
        //printf(lcd_putc,"%03.1f\n\r", temperature);
	
    	ds1307_get_time(hrs, min, sec);
        lcd_gotoxy(1,1);
        printf(lcd_putc,"\%02d:\%02d:\%02d", hrs,min,sec);
	
        output_low(PIN_A0);
		delay_ms(50);
       
	}
}
