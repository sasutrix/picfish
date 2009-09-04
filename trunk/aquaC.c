#include <global.h>
#include "flex_lcd.c"
#include "1wire.c"
#include "ds1820.c"
#include "ds1307.c"
#include "eeprom.c"

void main()
{
    float temperature;
	byte sec, min, hrs; 
	int32 dataini, datafim;

	dataini=859;
	datafim=1432;

	write_int16_eeprom(0,dataini);

	//write_eeprom(0,859);
	//write_eeprom(2,1430);
	
    //byte day, month,yr; 
    //byte dow; 

	lcd_init();
    lcd_putc("\f"); //limpa o lcd

	if (datafim > dataini){
		printf("%s","fudeu");
	}

	lcd_putc("Inicializando"); //o buffer do lcd é de 40 chars
	lcd_gotoxy(1,2);
	lcd_putc("LCD...");
	delay_ms(500);

	lcd_gotoxy(1,2);
	lcd_putc("DS18x20...");
	delay_ms(500);

    lcd_gotoxy(1,2);
	lcd_putc("DS1307....");
	ds1307_start();
	delay_ms(500);

	lcd_putc("\f"); //limpa o lcd	
		

	while(TRUE){
		output_high(PIN_A0);
		delay_ms(50);    
	  
    	temperature = ds1820_read();
		lcd_gotoxy(10,1);
		printf(lcd_putc,"%03.1f", temperature);
        printf("%03.1f\n\r", temperature);
	
    	ds1307_get_time(hrs, min, sec);
        lcd_gotoxy(1,1);
        printf(lcd_putc,"\%02d:\%02d:\%02d", hrs,min,sec);
	
        output_low(PIN_A0);
		delay_ms(50);
       
	}
}
