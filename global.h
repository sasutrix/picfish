//configuracao do uc
#include <16F887.h>
#use delay(clock=8000000)
#use rs232(baud=9600, UART1)
#fuses MCLR,NOPROTECT,NOWDT, HS

//configuracoes do ds1307
#define RTC_SDA  PIN_C4 
#define RTC_SCL  PIN_C3 

//configuracoes do ds18b20
#define ONE_WIRE_PIN PIN_E2

