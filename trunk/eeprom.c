void write_int16_eeprom(long int address, int16 dados) {
	int8 msb_dado, lsb_dado;
   	
	msb_dado = make8(datos);
	dado.low = data << 8;

	write_eeprom(address,data.high);
	write_eeprom(address++,data.low);
return