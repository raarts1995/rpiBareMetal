#ifndef PCD8544_H
#define PCD8544_H

#include "systimer.h"
#include "spi.h"
#include "gpio.h"
#include "uart.h"

#define PCD8544_BLACK 1
#define PCD8544_WHITE 0

#define PCD8544_COMMAND 0
#define PCD8544_DATA 1

#define PCD8544_LCDWIDTH 84
#define PCD8544_LCDHEIGHT 48

#define PCD8544_POWERDOWN 0x04
#define PCD8544_ENTRYMODE 0x02
#define PCD8544_EXTENDEDINSTRUCTION 0x01

#define PCD8544_DISPLAYBLANK 0x0
#define PCD8544_DISPLAYNORMAL 0x4
#define PCD8544_DISPLAYALLON 0x1
#define PCD8544_DISPLAYINVERTED 0x5

// H = 0
#define PCD8544_FUNCTIONSET 0x20
#define PCD8544_DISPLAYCONTROL 0x08
#define PCD8544_SETYADDR 0x40
#define PCD8544_SETXADDR 0x80

// H = 1
#define PCD8544_SETTEMP 0x04
#define PCD8544_SETBIAS 0x10
#define PCD8544_SETVOP 0x80

#define pcd8544_swap(a, b) { int t = a; a = b; b = t; }
#define pcd8544_abs(x) ((x < 0) ? -x : x)

// reduces how much is refreshed, which speeds it up!
// originally derived from Steve Evans/JCW's mod but cleaned up and
// optimized
//#define enablePartialUpdate

typedef struct pcd8544{
	int cursor_x, cursor_y;
	int textsize, textcolor;
	int cs;
	int dc;
	int rst;
} PCD8544;

#ifdef enablePartialUpdate
typedef struct pcd8544_partial {
	int xUpdateMin, xUpdateMax, yUpdateMin, yUpdateMax;
} PCD8544_PARTIAL;

extern PCD8544_PARTIAL pcd8544_partial;
#endif

extern PCD8544 pcd8544;

void pcd8544_init(int dc, int rst, int cs);

void pcd8544_command(int c);
void pcd8544_data(int c);

void pcd8544_setContrast(int val);
void pcd8544_clear();
void pcd8544_display();

void pcd8544_setPixel(int x, int y, int color);
int pcd8544_getPixel(int x, int y);
void pcd8544_fillcircle(int x0, int y0, int r, int color);
void pcd8544_drawcircle(int x0, int y0, int r, int color);
void pcd8544_drawrect(int x, int y, int w, int h, int color);
void pcd8544_fillrect(int x, int y, int w, int h, int color);
void pcd8544_drawline(int x0, int y0, int x1, int y1, int color);

void pcd8544_setCursor(int x, int y);
void pcd8544_setTextSize(int s);
void pcd8544_setTextColor(int c);
void pcd8544_write(char c);

void pcd8544_drawchar(int x, int line, unsigned char c);
void pcd8544_drawstring(int x, int line, char *c);
void pcd8544_drawbitmap(int x, int y, const unsigned char *bitmap, int w, int h, int color);

  
void pcd8544_spiwrite(char c, int dc);

void pcd8544_my_setpixel(int x, int y, int color);

#endif