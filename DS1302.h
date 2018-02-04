/*
 * DS1302.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Stanciu
 */
#include "Cpu.h"
#include "Events.h"
#include "C_CLK.h"
#include "BitIoLdd1.h"
#include "C_DATA.h"
#include "BitIoLdd2.h"
#include "C_RST.h"
#include "BitIoLdd3.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "WAIT1.h"
#include "MCUC1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#ifndef DS1302_H_
#define DS1302_H_

#define SEC 0x80
#define MINS 0x82
#define HOUR 0x84
#define DATE 0x86
#define MTH 0x88
#define DAY 0x8A
#define YEAR 0x8C
#define DLY 5

#define RD_OFF 0x1

uint8_t seconds,minutes, hour, date, month, year;

void readTime();
void readDate();

void writeTime();
void writeDate();

void DS1302_readAll();
uint8_t DS1302_readReg(uint8_t reg);
void DS1302_writeReg(uint8_t reg, uint8_t data);

#endif /* DS1302_H_ */
