//////////////////////////////////////////////////////////////////////////////// 
///                               DS1307.C                                   /// 
///                     Driver for Real Time Clock                           /// 
///                                                                          /// 
/// ds1307_init() - Enable oscillator without clearing the seconds register -/// 
///                 used when PIC loses power and DS1307 run from 3V BAT     /// 
///               - Disable squarewave output                                /// 
///                                                                          /// 
/// ds1307_set_date_time(day,mth,year,dow,hour,min,sec)  Set the date/time   /// 
///                                                                          /// 
/// ds1307_get_date(day,mth,year,dow)               Get the date             /// 
///                                                                          /// 
/// ds1307_get_time(hr,min,sec)                     Get the time             /// 
///                                                                          /// 
//////////////////////////////////////////////////////////////////////////////// 

//As definições abaixo estão no global.h
//#define RTC_SDA  PIN_C4 
//#define RTC_SCL  PIN_C3 


#define DS1307_I2C_WRITE_ADDR 0xD0 
#define DS1307_I2C_READ_ADDR  0xD1

// DS1307 register offsets 
#define DS1307_SECONDS_REG		0x00 
#define DS1307_MINUTES_REG      0x01 
#define DS1307_HOURS_REG    	0x02 
#define DS1307_DAY_OF_WEEK_REG 	0x03 
#define DS1307_DATE_REG     	0x04 
#define DS1307_MONTH_REG    	0x05 
#define DS1307_YEAR_REG     	0x06 
#define DS1307_CONTROL_REG  	0x07 

/*
 DS1307 SquareWave Control Register
+----+-----+-----+-----+-----+-----+-----+-----+-----+
| BIT|  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
|----+-----+-----+-----+-----------+-----+-----+-----|
|    | OUT |  0  |  0  |SQWE |  0  |  0  | RS1 | RS0 |
+----+-----+-----+-----------------------+-----------+

OUT:		Nível lógico do pino SQW/OUT quando o oscilador está desligado.
			1: Nível lógico = 1
			0: Nivel lógico = 0 
			Tipicamente é setado para 0 na inicialização

SQWE: 		Controla o pino SQW/OUT
			1: Ativa Oscilador
			0: Desativa Oscilador
			Tipicamente é setado para 0 na inicialização

RS1:RS0		Controla a frequência do pino SQW/OUT
			0 0 1Kz
			0 1	4.096Khz
			1 0 8.192Khz
			1 1 32.768Khz

*/
#define DS1307_SQW_OFF_OUTHI 0b10000000 //0x80 0d128
#define DS1307_SQW_OFF_OUTLO 0b00000000 //0x00 0d0
#define DS1307_SQW_1K		 0b00010000	//0x10 0d16
#define DS1307_SQW_4K		 0b00010001 //0x11 0d17
#define DS1307_SQW_8K		 0b00010010 //0x12 0d18
#define DS1307_SQW_32K		 0b00010011 //0x13 0d19




#use i2c(master, sda=RTC_SDA, scl=RTC_SCL) 

BYTE bin2bcd(BYTE binary_value); 
BYTE bcd2bin(BYTE bcd_value); 

//apenas para a primeira vez que for utilizar o ds1307
//depois use o ds1307_start()
void ds1307_init(void) 
{ 
   BYTE seconds = 0; 

   i2c_start(); 
   i2c_write(DS1307_I2C_WRITE_ADDR);    // WR to RTC 
   i2c_write(DS1307_SECONDS_REG);       // REG 0 
   i2c_start(); 
   i2c_write(DS1307_I2C_READ_ADDR);    // RD from RTC 
   seconds = bcd2bin(i2c_read(0));     // Read current "seconds" in DS1307 
   i2c_stop(); 
   seconds &= 0x7F;					   
 /* 
 A linha acima pega o valor do segundos e faz um AND lógico no setimo bit
 ex: 30 segundos = 0x1E = 0b00011110 
	   127d = 0x7F = 0b01111111

     0b00011110
   & 0b01111111
     ----------
     0b00011110

 o sétimo bit do registro de segundos = 0 inicializa o RTC 
 o AND (&) lógico, acima só faz alterar o sétimo bit, mantendo os demais como estão. */

   delay_us(3); 

   i2c_start(); 
   i2c_write(DS1307_I2C_WRITE_ADDR);   // WR to RTC 
   i2c_write(DS1307_SECONDS_REG);      // REG 0 
   i2c_write(bin2bcd(seconds));        // Start oscillator with current "seconds value 
   i2c_start(); 
   i2c_write(DS1307_I2C_WRITE_ADDR);   // WR to RTC 
   i2c_write(DS1307_CONTROL_REG);      // Control Register 
   i2c_write(DS1307_SQW_OFF_OUTHI);    // Disable squarewave output pin 
   i2c_stop(); 

} 

//inicia o ds1307 apos ter funcionado na bateria
void ds1307_start(void)
{
   output_float(RTC_SCL);
   output_float(RTC_SDA);
}


void ds1307_set_date_time(BYTE day, BYTE mth, BYTE year, BYTE dow, BYTE hr, BYTE min, BYTE sec) 
{ 
  sec &= 0x7F; 
  hr &= 0x3F; 

  i2c_start(); 
  i2c_write(DS1307_I2C_WRITE_ADDR);          // I2C write address 
  i2c_write(DS1307_I2C_WRITE_ADDR);          // Start at REG 0 - Seconds 
  i2c_write(bin2bcd(sec));      	// REG 0 
  i2c_write(bin2bcd(min));      	// REG 1 
  i2c_write(bin2bcd(hr));      		// REG 2 
  i2c_write(bin2bcd(dow));      	// REG 3 
  i2c_write(bin2bcd(day));      	// REG 4 
  i2c_write(bin2bcd(mth));      	// REG 5 
  i2c_write(bin2bcd(year));      	// REG 6 
  i2c_write(DS1307_SQW_OFF_OUTHI);  // REG 7 - Disable squarewave output pin 
  i2c_stop(); 
} 

void ds1307_get_date(BYTE &day, BYTE &mth, BYTE &year, BYTE &dow) 
{ 
  i2c_start(); 
  i2c_write(DS1307_I2C_WRITE_ADDR); 
  i2c_write(DS1307_DAY_OF_WEEK_REG); // Start at REG 3 - Day of week 
  i2c_start(); 
  i2c_write(DS1307_I2C_READ_ADDR); 
  dow  = bcd2bin(i2c_read() & 0x7f);   // REG 3 
  day  = bcd2bin(i2c_read() & 0x3f);   // REG 4 
  mth  = bcd2bin(i2c_read() & 0x1f);   // REG 5 
  year = bcd2bin(i2c_read(0));         // REG 6 
  i2c_stop(); 
} 

void ds1307_get_time(BYTE &hr, BYTE &min, BYTE &sec) 
{ 
  i2c_start(); 
  i2c_write(DS1307_I2C_WRITE_ADDR); 
  i2c_write(DS1307_SECONDS_REG);		// Start at REG 0 - Seconds 
  i2c_start(); 
  i2c_write(DS1307_I2C_READ_ADDR); 
  sec = bcd2bin(i2c_read() & 0x7f); 
  min = bcd2bin(i2c_read() & 0x7f); 
  hr  = bcd2bin(i2c_read(0) & 0x3f); 
  i2c_stop(); 

} 

BYTE bin2bcd(BYTE binary_value) 
{ 
  BYTE temp; 
  BYTE retval; 

  temp = binary_value; 
  retval = 0; 

  while(TRUE) 
  { 
    // Get the tens digit by doing multiple subtraction 
    // of 10 from the binary value. 
    if(temp >= 10) 
    { 
      temp -= 10; 
      retval += 0x10; 
    } 
    else // Get the ones digit by adding the remainder. 
    { 
      retval += temp; 
      break; 
    } 
  } 

  return(retval); 
} 


// Input range - 00 to 99. 
BYTE bcd2bin(BYTE bcd_value) 
{ 
  BYTE temp; 

  temp = bcd_value; 
  // Shifting upper digit right by 1 is same as multiplying by 8. 
  temp >>= 1; 
  // Isolate the bits for the upper digit. 
  temp &= 0x78; 

  // Now return: (Tens * 8) + (Tens * 2) + Ones 

  return(temp + (temp >> 2) + (bcd_value & 0x0f)); 
} 
