void write_int16_eeprom(int16 address, int16 dados);
int16 read_int16_eeprom(int16 address);
int8 msb(int16 dados);
int8 lsb(int16 dados);

void write_int16_eeprom(int16 address, int16 dados) {
	write_eeprom(address,msb(dados));
	write_eeprom(++address,lsb(dados));
}

int16 read_int16_eeprom(int16 address){
	int8 hi, lo;

	hi=read_eeprom(address);
	lo=read_eeprom(++address);
	return (make16(hi,lo));
}

int8 msb(int16 dados){
	return (make8(dados,1));
}

int8 lsb(int16 dados){
	return (make8(dados,0));
}