#include <global.h>
#include <string.h>
#include "flex_lcd.c"
#include "1wire.c"
#include "ds1820.c"
#include "ds1307.c"
#include "eeprom.c"
//#include "serial_cmd.c"

//prototipos de funcao
void serialCmd();


//definicao dos pontos de eeprom onde serao
//gravadas os h0orarios dos eventos
#define evt1_on  0x00 //lampada 1
#define evt1_off 0x02 //lampada 1
#define evt2_on  0x04 //lampada 2
#define evt2_off  0x06 //lampada 1
#define evt3_on  0x08 //lampada 3
#define evt3_off  0x0A //lampada 1
#define evt4_on  0x0C //lampada 4
#define evt4_off  0x0E //lampada 1
#define evt5_on  0x10 //moon light
#define evt5_off  0x12 //lampada 1
#define temp_hi  0x14 //temperatura máxima
#define temp_lo  0x15 //temperatura mínima

//definicao dos comandos
#define HELP "HELP"
#define EVT1 "EVT1"
#define EVT2 "EVT2"

char fullcmd[20];

void main(){
    float temperature;
	byte sec, min, hrs; 
	int32 dataini, datafim;
	char cmd;
	int myLoop;
	myLoop=0;
    dataini=859;
	datafim=1432;
	write_int16_eeprom(Evt1_on,dataini);
	write_int16_eeprom(Evt1_off, datafim);
    //byte day, month,yr; 
    //byte dow; 
    //lcd_init();
    //lcd_putc("\f"); //limpa o lcd
    //lcd_putc("Inicializando"); //o buffer do lcd é de 40 chars
    //lcd_gotoxy(1,2);
    //lcd_putc("LCD...");
    //delay_ms(500);
    //lcd_gotoxy(1,2);
    //lcd_putc("DS18x20...");
    //delay_ms(500);
    //lcd_gotoxy(1,2);
    //lcd_putc("DS1307....");
    //ds1307_start();
    //delay_ms(500);
    //lcd_putc("\f"); //limpa o lcd	
    //
	printf("%s","Ready>");
	while(TRUE){
		output_high(PIN_A0);
		delay_ms(50);    
        //temperature = ds1820_read();
        //lcd_gotoxy(10,1);
        //printf(lcd_putc,"%03.1f", temperature);
	    //ds1307_get_time(hrs, min, sec);
	    //lcd_gotoxy(1,1);
	    //printf(lcd_putc,"\%02d:\%02d:\%02d", hrs,min,sec);
		if ( kbhit() ) {
		    cmd = getc();
			if (cmd == 13)
				serialCmd();
		    putc(cmd);
			fullcmd[myLoop]=cmd;
			++myLoop;}
		output_low(PIN_A0);
		delay_ms(50);
	}
}

void serialCmd() {
	char Command[20] = "Mauro";
if (strcmp(fullCmd,Command)==0)
	printf("OK\n\r");
else
    printf("ERR\n\r");
}
