#include "PCD8544.h"
#include "font5x7.c"

PCD8544 pcd8544;

// a 5x7 font table
extern unsigned char font[];

// the memory buffer for the LCD
unsigned char pcd8544_buffer[PCD8544_LCDWIDTH * PCD8544_LCDHEIGHT / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFF, 0xFC, 0xE0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0xC0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC7, 0xC7, 0x87, 0x8F, 0x9F, 0x9F, 0xFF, 0xFF, 0xFF,
0xC1, 0xC0, 0xE0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE,
0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0xC0, 0xE0, 0xF1, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x0F, 0x0F, 0x87,
0xE7, 0xFF, 0xFF, 0xFF, 0x1F, 0x1F, 0x3F, 0xF9, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xFD, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xF0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
0x7E, 0x3F, 0x3F, 0x0F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0xE0, 0xF1, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFC, 0xF0, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01,
0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x1F, 0x3F, 0x7F, 0x7F,
0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};


#ifdef enablePartialUpdate
PCD8544_PARTIAL pcd8544_partial;
#endif



void pcd8544_updateBoundingBox(int xmin, int ymin, int xmax, int ymax) {
#ifdef enablePartialUpdate
	if (xmin < pcd8544_partial.xUpdateMin) pcd8544_partial.xUpdateMin = xmin;
	if (xmax > pcd8544_partial.xUpdateMax) pcd8544_partial.xUpdateMax = xmax;
	if (ymin < pcd8544_partial.yUpdateMin) pcd8544_partial.yUpdateMin = ymin;
	if (ymax > pcd8544_partial.yUpdateMax) pcd8544_partial.yUpdateMax = ymax;
#endif
}

void pcd8544_init(int dc, int rst, int cs) {
	int contrast = 50;
	pcd8544.dc = dc;
	pcd8544.rst = rst;
	pcd8544.cs = cs;
	
	pcd8544.cursor_x = pcd8544.cursor_y = 0;
	pcd8544.textsize = 1;
	pcd8544.textcolor = PCD8544_BLACK;
	
	/*gpio_pud(pcd8544.dc, GPIO_PUD_CLEAR);
	gpio_pud(pcd8544.rst, GPIO_PUD_CLEAR);*/
	
	gpio_set_output(pcd8544.dc);
	gpio_set_output(pcd8544.rst);
	
	// toggle RST low to reset
	gpio_clear_pin(pcd8544.rst);
	systim_waitms(100);
	gpio_set_pin(pcd8544.rst);
	
	// get into the EXTENDED mode!
	pcd8544_spiwrite(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION, PCD8544_COMMAND);

	// set VOP
	if (contrast > 0x7f)
		contrast = 0x7f;

	pcd8544_spiwrite(PCD8544_SETVOP | contrast, PCD8544_COMMAND); // Experimentally determined
	
	//set temp coefficient
	pcd8544_spiwrite(PCD8544_SETTEMP, PCD8544_COMMAND);
	
	// LCD bias select (4 is optimal?)
	pcd8544_spiwrite(PCD8544_SETBIAS | 0x4, PCD8544_COMMAND);

	// normal mode
	pcd8544_spiwrite(PCD8544_FUNCTIONSET, PCD8544_COMMAND);

	// Set display to Normal
	pcd8544_spiwrite(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL, PCD8544_COMMAND);

	// initial display line
	// set page address
	// set column address
	// write display data

	// set up a bounding box for screen updates

	pcd8544_updateBoundingBox(0, 0, PCD8544_LCDWIDTH-1, PCD8544_LCDHEIGHT-1);
	// Push out pcd8544_buffer to the Display (will show the AFI logo)
	pcd8544_display();
}

void pcd8544_drawbitmap(int x, int y, const unsigned char *bitmap, int w, int h, int color) {
	int i, j;
	for (j=0; j<h; j++) {
		for (i=0; i<w; i++ ) {
			if (bitmap[i + (j/8)*w] & (1 << (j%8))) {
				pcd8544_my_setpixel(x+i, y+j, color);
			}
		}
	}

	pcd8544_updateBoundingBox(x, y, x+w, y+h);
}


void pcd8544_drawstring(int x, int y, char *c) {
	pcd8544.cursor_x = x;
	pcd8544.cursor_y = y;
	while(*c) {
		pcd8544_write(*c);
		c++;
	}
}

void pcd8544_drawchar(int x, int y, unsigned char c) {
	if (y >= PCD8544_LCDHEIGHT) return;
	if ((x+5) >= PCD8544_LCDWIDTH) return;
	
	int i, j;
	for (i = 0; i<5; i++ ) {
		int d = font[(c*5)+i];
		for (j = 0; j<8; j++) {
			if (d & (1 << j)) {
				pcd8544_my_setpixel(x+i, y+j, pcd8544.textcolor);
			}
			else {
				pcd8544_my_setpixel(x+i, y+j, !pcd8544.textcolor);
			}
		}
	}
	for (j = 0; j<8; j++) {
		pcd8544_my_setpixel(x+5, y+j, !pcd8544.textcolor);
	}
	pcd8544_updateBoundingBox(x, y, x+5, y + 8);
}

void pcd8544_write(char c) {
	if (c == '\n') {
		pcd8544.cursor_y += pcd8544.textsize*8;
	} else if (c == '\r') {
		pcd8544.cursor_x = 0;
	} else {
		pcd8544_drawchar(pcd8544.cursor_x, pcd8544.cursor_y, c);
		pcd8544.cursor_x += pcd8544.textsize*6;
		if (pcd8544.cursor_x >= (PCD8544_LCDWIDTH-5)) {
			pcd8544.cursor_x = 0;
			pcd8544.cursor_y+=8;
		}
		if (pcd8544.cursor_y >= PCD8544_LCDHEIGHT) 
			pcd8544.cursor_y = 0;
	}
}

void pcd8544_setCursor(int x, int y){
	pcd8544.cursor_x = x; 
	pcd8544.cursor_y = y;
}


// bresenham's algorithm - thx wikpedia
void pcd8544_drawline(int x0, int y0, int x1, int y1, int color) {
	int steep = pcd8544_abs(y1 - y0) > pcd8544_abs(x1 - x0);
	if (steep) {
		pcd8544_swap(x0, y0);
		pcd8544_swap(x1, y1);
	}

	if (x0 > x1) {
		pcd8544_swap(x0, x1);
		pcd8544_swap(y0, y1);
	}

	// much faster to put the test here, since we've already sorted the points
	pcd8544_updateBoundingBox(x0, y0, x1, y1);

	int dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int err = dx / 2;
	int ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			pcd8544_my_setpixel(y0, x0, color);
		} else {
			pcd8544_my_setpixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}


// filled rectangle
void pcd8544_fillrect(int x, int y, int w, int h, int color) {

	// stupidest version - just pixels - but fast with internal buffer!
	int i, j;
	for (i=x; i<x+w; i++) {
		for (j=y; j<y+h; j++) {
			pcd8544_my_setpixel(i, j, color);
		}
	}

	pcd8544_updateBoundingBox(x, y, x+w, y+h);
}

// draw a rectangle
void pcd8544_drawrect(int x, int y, int w, int h, int color) {
	// stupidest version - just pixels - but fast with internal buffer!
	int i, j;
	for (i=x; i<x+w; i++) {
		pcd8544_my_setpixel(i, y, color);
		pcd8544_my_setpixel(i, y+h-1, color);
	}
	for (i=y; i<y+h; i++) {
		pcd8544_my_setpixel(x, i, color);
		pcd8544_my_setpixel(x+w-1, i, color);
	} 

	pcd8544_updateBoundingBox(x, y, x+w, y+h);
}

// draw a circle outline
void pcd8544_drawcircle(int x0, int y0, int r, int color) {
	pcd8544_updateBoundingBox(x0-r, y0-r, x0+r, y0+r);

	int f = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x = 0;
	int y = r;
	
	pcd8544_my_setpixel(x0, y0+r, color);
	pcd8544_my_setpixel(x0, y0-r, color);
	pcd8544_my_setpixel(x0+r, y0, color);
	pcd8544_my_setpixel(x0-r, y0, color);

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
  
		pcd8544_my_setpixel(x0 + x, y0 + y, color);
		pcd8544_my_setpixel(x0 - x, y0 + y, color);
		pcd8544_my_setpixel(x0 + x, y0 - y, color);
		pcd8544_my_setpixel(x0 - x, y0 - y, color);

		pcd8544_my_setpixel(x0 + y, y0 + x, color);
		pcd8544_my_setpixel(x0 - y, y0 + x, color);
		pcd8544_my_setpixel(x0 + y, y0 - x, color);
		pcd8544_my_setpixel(x0 - y, y0 - x, color);
    
	}
}

void pcd8544_fillcircle(int x0, int y0, int r, int color) {
	pcd8544_updateBoundingBox(x0-r, y0-r, x0+r, y0+r);

	int f = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x = 0;
	int y = r;
	
	int i;
	for (i=y0-r; i<=y0+r; i++) {
		pcd8544_my_setpixel(x0, i, color);
	}

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		
		int i;
		for (i=y0-y; i<=y0+y; i++) {
			pcd8544_my_setpixel(x0+x, i, color);
			pcd8544_my_setpixel(x0-x, i, color);
		} 
		for (i=y0-x; i<=y0+x; i++) {
			pcd8544_my_setpixel(x0+y, i, color);
			pcd8544_my_setpixel(x0-y, i, color);
		}    
	}
}


void pcd8544_my_setpixel(int x, int y, int color) {
	if ((x >= PCD8544_LCDWIDTH) || (y >= PCD8544_LCDHEIGHT))
		return;

	// x is which column
	if (color) 
		pcd8544_buffer[x+ (y/8)*PCD8544_LCDWIDTH] |= (1 << (y%8));  
	else
		pcd8544_buffer[x+ (y/8)*PCD8544_LCDWIDTH] &= ~(1 << (y%8)); 
}



// the most basic function, set a single pixel
void pcd8544_setPixel(int x, int y, int color) {
	if ((x >= PCD8544_LCDWIDTH) || (y >= PCD8544_LCDHEIGHT))
		return;

	// x is which column
	if (color) 
		pcd8544_buffer[x+ (y/8)*PCD8544_LCDWIDTH] |= (1 << (y%8));
	else
		pcd8544_buffer[x+ (y/8)*PCD8544_LCDWIDTH] &= ~(1 << (y%8));

	pcd8544_updateBoundingBox(x,y,x,y);
}


// the most basic function, get a single pixel
int pcd8544_getPixel(int x, int y) {
	if ((x >= PCD8544_LCDWIDTH) || (y >= PCD8544_LCDHEIGHT))
		return 0;

	return (pcd8544_buffer[x+ (y/8)*PCD8544_LCDWIDTH] >> (7-(y%8))) & 0x1;  
}

void pcd8544_spiwrite(char c, int dc) {
	spi_set_cpol(0);
	spi_set_cpha(0);
	spi_set_cs(pcd8544.cs);
	spi_set_cspol(pcd8544.cs, 0);
	
	gpio_write_pin(pcd8544.dc, dc);
	spi_transfer(&c, 1);
}

/*void pcd8544_spiwrite(int c) {
	gpio_clear_pin(pcd8544.dc);
	pcd8544_spiwrite((char)c);
}

void pcd8544_spiwrite(int c) {
	gpio_set_pin(pcd8544.dc);
	pcd8544_spiwrite((char)c);
}*/

void pcd8544_setContrast(int val) {
	if (val > 0x7f) {
		val = 0x7f;
	}
	pcd8544_spiwrite(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION, PCD8544_COMMAND);
	pcd8544_spiwrite(PCD8544_SETVOP | val, PCD8544_COMMAND);
	pcd8544_spiwrite(PCD8544_FUNCTIONSET, PCD8544_COMMAND);
  
}



void pcd8544_display(void) {
	int col, maxcol, p;
  
	for(p = 0; p < 6; p++) {
#ifdef enablePartialUpdate
		// check if this page is part of update
		if (pcd8544_partial.yUpdateMin >= ((p+1)*8) ) {
			continue;   // nope, skip it!
		}
		if (pcd8544_partial.yUpdateMax < p*8) {
			break;
		}
#endif

    pcd8544_spiwrite(PCD8544_SETYADDR | p, PCD8544_COMMAND);


#ifdef enablePartialUpdate
    col = pcd8544_partial.xUpdateMin;
    maxcol = pcd8544_partial.xUpdateMax;
#else
    // start at the beginning of the row
    col = 0;
    maxcol = PCD8544_LCDWIDTH-1;
#endif

	pcd8544_spiwrite(PCD8544_SETXADDR | col, PCD8544_COMMAND);

		for(; col <= maxcol; col++) {
			//uprintf("%d ", col);
			pcd8544_spiwrite(pcd8544_buffer[(PCD8544_LCDWIDTH*p)+col], PCD8544_DATA);
		}
	}

	pcd8544_spiwrite(PCD8544_SETYADDR, PCD8544_COMMAND);  // no idea why this is necessary but it is to finish the last byte?
#ifdef enablePartialUpdate
	pcd8544_partial.xUpdateMin = PCD8544_LCDWIDTH - 1;
	pcd8544_partial.xUpdateMax = 0;
	pcd8544_partial.yUpdateMin = PCD8544_LCDHEIGHT-1;
	pcd8544_partial.yUpdateMax = 0;
#endif

}

// clear everything
void pcd8544_clear(void) {
	unsigned int i = 0;
	for (i = 0; i < PCD8544_LCDWIDTH*PCD8544_LCDHEIGHT/8; i++)
		pcd8544_buffer[i] = 0;
	pcd8544_updateBoundingBox(0, 0, PCD8544_LCDWIDTH-1, PCD8544_LCDHEIGHT-1);
	pcd8544.cursor_y = pcd8544.cursor_x = 0;
}