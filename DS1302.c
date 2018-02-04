/*
 * DS1302.c
 *
 *  Created on: Jan 27, 2018
 *      Author: Stanciu
 */
#include "DS1302.h"

void DS1302_readAll(){
	readTime();
	readDate();
}

void writeTime(){
	uint8_t data;
	//Write seconds:
	data = 0;//CH flag 0 (clock halt)
	data = ((seconds/10)<<4) + (seconds%10);
	DS1302_writeReg(SEC, data);
	//Write minutes:
	data = 0;
	data = ((minutes/10)<<4) + (minutes%10);
	DS1302_writeReg(MINS, data);
	//Write hour:
	data = 0; //24 hour mode
	data = ((hour/10)<<4) + (hour%10);
	DS1302_writeReg(HOUR, data);
}

void writeDate(){
	uint8_t data;
	//Write date:
	data = 0;
	data = ((date/10)<<4) + (date%10);
	DS1302_writeReg(DATE, data);
	//Write month:
	data = 0;
	data = ((month/10)<<4) + (month%10);
	DS1302_writeReg(MTH, data);
	//Write year:
	data = 0;
	data = ((year/10)<<4) + (year%10);
	DS1302_writeReg(YEAR, data);
}

uint8_t DS1302_readReg(uint8_t reg){
	uint8_t cmd_data = 0;
	uint8_t data = 0;
	reg += RD_OFF; //READ OFFSET BY 0x1;
	int i;
	
	cmd_data = reg;
	C_CLK_ClrVal(); //CLK low, data sent on rising edge
	C_RST_SetVal(); //CE high
	C_DATA_SetDir(1); //output
	for(i=0;i<8;i++){
		C_CLK_ClrVal();
		WAIT1_Waitms(DLY);
		C_DATA_PutVal(cmd_data & (1<<i));
		C_CLK_SetVal(); //rising edge for data input
		WAIT1_Waitms(DLY);
	}
	//data input:
	C_DATA_SetDir(0);//input
	for(i = 0;i<8;i++){
		C_CLK_ClrVal();//read after falling edge
		WAIT1_Waitms(DLY);
		data += (C_DATA_GetVal()<<i);
		C_CLK_SetVal();
		WAIT1_Waitms(DLY);
	}
	C_RST_ClrVal();//CE low
	int processed = 0;
	processed = (((data & 0b11110000)>>4)*10) + (data & 0b1111);
	return processed;
}

void DS1302_writeReg(uint8_t reg, uint8_t data){
	uint8_t cmd_data = 0; 
	
	int i;
	cmd_data = reg;
	C_CLK_ClrVal(); //CLK low, data sent on rising edge
	C_RST_SetVal(); //CE high
	C_DATA_SetDir(1); //output
	for(i=0;i<8;i++){
		C_CLK_ClrVal();
		WAIT1_Waitms(DLY);
		C_DATA_PutVal(cmd_data & (1<<i));
		C_CLK_SetVal(); //rising edge for data input
		WAIT1_Waitms(DLY);
	}
	for(i=0;i<8;i++){
		C_CLK_ClrVal();
		WAIT1_Waitms(DLY);
		C_DATA_PutVal(data & (1<<i));
		C_CLK_SetVal(); //rising edge for data input
		WAIT1_Waitms(DLY);
	}
	C_RST_ClrVal();//CE low
}

void readTime(){
	seconds = DS1302_readReg(SEC);
	minutes = DS1302_readReg(MINS);
	hour = DS1302_readReg(HOUR);
}

void readDate(){
	date = DS1302_readReg(DATE);
	month = DS1302_readReg(MTH);
	year = DS1302_readReg(YEAR);
}
