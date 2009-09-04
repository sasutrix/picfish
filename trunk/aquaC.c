#include <global.h>
#include <string.h>
#include "flex_lcd.c"
#include "1wire.c"
#include "ds1820.c"
#include "ds1307.c"
#include "eeprom.c"


#define Evt1_on  0x00 //lampada 1
#define Evt1_off 0x02
#define Evt2_on  0x04 //lampada 2
#define Evt2_off 0x06
#define Evt3_on  0x08 //lampada 3
#define Evt3_off 0x0A
#define Evt4_on  0x0C //lampada 4
#define Evt4_off 0x0E
#define Evt5_on  0x10 //moon light
#define Evt5_off 0x12
#define temp_hi  0x14 //temperatura máxima
#define temp_lo  0x15 //temperatura mínima



void main()
{
    float temperature;
	byte sec, min, hrs; 
	int32 dataini, datafim;
	char fullcmd[20], cmd;
	int myLoop;

	myLoop=0;

	dataini=859;
	datafim=1432;

	write_int16_eeprom(Evt1_on,dataini);
	write_int16_eeprom(Evt1_off, datafim);

    //byte day, month,yr; 
    //byte dow; 

//	lcd_init();
//    lcd_putc("\f"); //limpa o lcd
//
//
//	lcd_putc("Inicializando"); //o buffer do lcd é de 40 chars
//	lcd_gotoxy(1,2);
//	lcd_putc("LCD...");
//	delay_ms(500);
//
//	lcd_gotoxy(1,2);
//	lcd_putc("DS18x20...");
//	delay_ms(500);
//
//    lcd_gotoxy(1,2);
//	lcd_putc("DS1307....");
//	ds1307_start();
//	delay_ms(500);
//
//	lcd_putc("\f"); //limpa o lcd	
//
	printf("%s","Ready>");

		

	while(TRUE){
		output_high(PIN_A0);
		delay_ms(50);    
//	  
//    	temperature = ds1820_read();
//		lcd_gotoxy(10,1);
//		printf(lcd_putc,"%03.1f", temperature);
//       
//    	ds1307_get_time(hrs, min, sec);
//        lcd_gotoxy(1,1);
//        printf(lcd_putc,"\%02d:\%02d:\%02d", hrs,min,sec);
//
//		strcpy(cmd,"EVT1");
		
	
			if (kbhit()){
			    cmd = getc();
				putc(cmd);
				fullcmd[myLoop]=cmd;
				++myLoop;}
				
		
		//if (strcmp(getcmd, cmd)=0){
		//	printf("OK\n\r");}
		//else{
		//	printf("ERR\n\r");}
	
        output_low(PIN_A0);
		delay_ms(50);
//       
	}
}
