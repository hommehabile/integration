ST7920.H
=============================================================
#ifndef ST7920_H
#define ST7920_H

#include "sysdefs.h"

/* Common Aliases */
#ifndef PIN
#define PIN(n) (U32)(1 << (n))
#endif

/* Pin Registers */
#define ST7920_BUSPIN0 16 // Parallel Bus
(P0.16..23)
#define ST7920_DATA ((U32)0xff< #define ST7920_BUSALL 0x00FF0000 // Parallel Bus Mask
(P0.16..23)
#define ST7920_PSB PIN(28) // Parallel Select (0 Serial Mode, 1 = 8/4-Bit Parallel Bus Mode) (P0.28)
#define ST7920_RW PIN(29) // RW (P0.29)
#define ST7920_DI PIN(6) // RS (P0.6)
#define ST7920_E PIN(30) // Enable (P0.30)
#define ST7920_RST PIN(25) // Reset (P0.25)

/* General Definitions */
#define ST7920_BUSIN 0 // Parallel Bus as Input
#define ST7920_BUSOUT 1 // Parallel Bus as Output
#define ST7920_BUSY 0x80 // Busy Flag

/* Basic ST7920 Commands */
#define ST7920_CMD_CLEAR 0x01 // Clear Display
#define ST7920_CMD_HOME 0x02 // Move Cursor Home
#define ST7920_CMD_EM 0x04 // Entry Mode Base
#define ST7920_CMD_EM_INCRR 0x02 // Increment Cursor Right
#define ST7920_CMD_EM_INCRL 0x00 // Increment Cursor Left
#define ST7920_CMD_EM_SHFTR 0x03 // Shift Display Right
#define ST7920_CMD_EM_SHFTL 0x01 // Shift Display Left
#define ST7920_CMD_DC 0x08 // Display Control
#define ST7920_CMD_DC_DISPON 0x04 // Display On
#define ST7920_CMD_DC_CURON 0x02 // Cursor On
#define ST7920_CMD_DC_BLNKON 0x01 // Blink On
#define ST7920_CMD_FNC 0x20 // Function Set
#define ST7920_CMD_FNC_DL8 0x10 // 8-Bit Interface
#define ST7920_CMD_FNC_DL4 0x00 // 4-Bit Interface
#define ST7920_CMD_FNC_EXTINS 0x04 // Extended Instruction Set
#define ST7920_CMD_FNC_BASINS 0x00 // Basic Instruction Set
#define ST7920_CMD_CGRAM_ADDR 0x40 // Set CGRAM Address
#define ST7920_CMD_DDRAM_ADDR 0x80 // Set DDRAM Address

/* Extended ST7920 Commands */
#define ST7920_ECMD_GFXDISPON 0x36 // Ext. Display Control (8-
bit, Extended Instructions, GFX Display On)

// Method Prototypes
void st7920_init(void);
void st7920_clear(void);
void st7920_printf(U8 *text);
void st7920_setPixel(U8 x, U8 y);

#endif

ST7920.C
=============================================================
#include "lpc214x.h"
#include "st7920.h"
#include "delay.h"

void st7920_strobeEnable(void)
{
GPIO0_IOSET = ST7920_E;
DelayMS(15);
GPIO0_IOCLR = ST7920_E;
}

void st7920_setBusDir(U8 dir)
{
if (dir==ST7920_BUSOUT)
{
GPIO0_IODIR |= (ST7920_BUSALL);
}
else
{
GPIO0_IODIR &= ~(ST7920_BUSALL);
}
}

void st7920_waitWhileBusy()
{
U8 rdata;

st7920_setBusDir(ST7920_BUSIN);

// Read busy flag
GPIO0_IOCLR = ST7920_DI; /* Clear RS */
GPIO0_IOSET = ST7920_RW; /* Set Read Mode */

st7920_strobeEnable();

// Loop until no longer busy
while ((rdata & 0x7F) == ST7920_BUSY)
{
rdata = (unsigned char)(GPIO0_IOPIN >> ST7920_BUSPIN0);
}

st7920_setBusDir(ST7920_BUSOUT);
GPIO0_IOCLR = (U32)(ST7920_BUSALL); /* Set all pins low */
GPIO0_IOCLR = ST7920_DI;
GPIO0_IOCLR = ST7920_RW; /* Read mode */
}

void st7920_data(U8 data)
{
st7920_setBusDir(ST7920_BUSOUT);

GPIO0_IOSET = ST7920_DI;
GPIO0_IOCLR = ST7920_RW;

GPIO0_IOSET = ((U32)data< st7920_strobeEnable();

GPIO0_IOSET = ST7920_RW;
GPIO0_IOCLR = (U32)(ST7920_BUSALL);
GPIO0_IOCLR = ST7920_DI;

DelayMS(2);
}

void st7920_command(U8 command)
{
st7920_setBusDir(ST7920_BUSOUT);

st7920_waitWhileBusy();
GPIO0_IOCLR = ST7920_DI;
GPIO0_IOCLR = ST7920_RW;
GPIO0_IOSET = ((U32)command< st7920_strobeEnable();

GPIO0_IOSET = ST7920_RW;
GPIO0_IOCLR = (U32)(ST7920_BUSALL);
GPIO0_IOCLR = ST7920_DI;

DelayMS(2);
}

// 0x80 0x81 0x82 0x83 0x84 0x85 0x86 0x87
// 0x90 0x91 0x92 0x93 0x94 0x95 0x96 0x97
// 0x88 0x89 0x8a 0x8b 0x8c 0x8d 0x8e 0x8f
// 0x98 0x99 0x9a 0x9b 0x9c 0x9d 0x9e 0x9f
void st7920_setGDRamAddress(U8 addr)
{
st7920_command(addr);
}

/* Public Methods
********************************************************** */
void st7920_init(void)
{
// Set pin to default state
U32 mask = (U32)(ST7920_RST | ST7920_PSB | ST7920_RW | ST7920_DI |
ST7920_E);
GPIO0_IOCLR = mask; // Clear all pins
GPIO0_IODIR |= mask; // Set all pins for output
GPIO0_IOSET = ST7920_PSB; // Set PSB High (0 = Serial Mode,
1 = 8/4-Bit Parallel Bus Mode)

// Wait until the LCD is not busy
st7920_waitWhileBusy();

// Toggle Reset
GPIO0_IOSET = ST7920_RST;
DelayMS(21);
GPIO0_IOCLR = ST7920_RST;
DelayMS(20);
GPIO0_IOSET = ST7920_RST;
DelayMS(20);

// Instantiate intialisation commands (Assigned here for debug
purposes. Remove variables in a production environment.)
U8 functionSetBas = (ST7920_CMD_FNC | ST7920_CMD_FNC_DL8 |
ST7920_CMD_FNC_BASINS); // (8-bit, Basic Instruction Set)
U8 functionSetExt = (ST7920_CMD_FNC | ST7920_CMD_FNC_DL8 |
ST7920_CMD_FNC_EXTINS); // (8-bit, Extended Instruction Set)
U8 displayCmd = (ST7920_CMD_DC | ST7920_CMD_DC_DISPON |
ST7920_CMD_DC_BLNKON); // (Display On, Blink On, Cursor OFF)
U8 entryMode = (ST7920_CMD_EM |
ST7920_CMD_EM_INCRR); // (Increment cursor
right, no shift)

// Send initialisation command sequence
st7920_command(functionSetBas); // Basic Function Set
st7920_command(functionSetBas); // Repeat Function Set
st7920_command(displayCmd); // Display
st7920_command(ST7920_CMD_CLEAR); // Clear Display
st7920_command(entryMode); // Set Entry Mode
st7920_command(functionSetExt); // Extended Function Set
st7920_command(ST7920_ECMD_GFXDISPON); // Graphic Display On

st7920_setPixel(1,1);
}

void st7920_clear(void)
{
st7920_command(ST7920_CMD_CLEAR); // Clear Display
}

void st7920_printf(U8 *text)
{
while(*text != 0)
{
st7920_data(*text);
text++;
}
}

void st7920_setPixel(U8 x, U8 y)
{
st7920_setGDRamAddress(0x80);

// ToDo: How to set individual pixels?
}
