// Hexiang Li
#include "mylib.h"
#include "font.c"

u16 *videoBuffer = (u16 *)0x6000000;

void setPixel(int row, int col, u16 color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

// void fillScreen4(char index)
// {	
// 	volatile u16 color = (index<<8) | index;
// 	DMA[3].src = &color;
// 	DMA[3].dst = videoBuffer;
// 	DMA[3].cnt = 19200 | DMA_ON | DMA_SOURCE_FIXED;	
// }	


void setPixel4(int row, int col, char index)
{
	int whichPixel = OFFSET(row, col, 240);
	int whichShort = whichPixel/2;
	unsigned short theShort = videoBuffer[whichShort];

	if(col&1)
	{
		// Col is odd, we insert index to the left byte
		theShort = (theShort & 0x00FF) | (index << 8);
	}
	else
	{
		theShort = (theShort & 0xFF00) | index;
	}
	videoBuffer[whichShort] = theShort;
}

void drawImage4(int r, int c, int width, int height, const u16* image)
{
	for (int y = 0; y < height; y++) {
		DMA[3].src = &image[OFFSET(y, 0, width / 2)];
		DMA[3].dst = videoBuffer + OFFSET(r + y, c, 240)/2;
		DMA[3].cnt = (width/2) | DMA_ON;
	}
}

void FlipPage()
{
	if(REG_DISPCTL & BUFFER1FLAG)
	{
		// We were displaying buffer1 and videobuffer was buffer 0
		REG_DISPCTL = REG_DISPCTL & ~BUFFER1FLAG;
		videoBuffer = BUFFER1;
	}
	else
	{
		REG_DISPCTL = REG_DISPCTL | BUFFER1FLAG;
		videoBuffer = BUFFER0;
	}
}

void drawChar(int row, int col, char ch, u16 color)
{
	int r,c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[(r*6+c)+(48*ch)] == 1)
			{
				setPixel(row+r, col+c, color);
			}
		}
	}
}

void drawString(int row, int col, char *str, u16 color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col += 6;
	}
}

void drawChar4(int row, int col, char ch, char index)
{
	int r,c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[(r*6+c)+(48*ch)] == 1)
			{
				setPixel4(row+r, col+c, index);
			}
		}
	}
}

void drawString4(int row, int col, char *str, char index)
{
	while(*str)
	{
		drawChar4(row, col, *str++, index);
		col += 6;
	}
}

void drawPipe(int r, int c, int hole, const u16* image)
{
	drawImage4(r, c, PIPE_W, hole - r, (u16*)image);
	drawImage4(hole + HOLE_L, c, PIPE_W, 160 - hole - HOLE_L, (u16*)image);
}

void loadPalette(const unsigned short * toLoad, int size, int offset) {
	for (int i = offset; i < (size + offset); i++) {
		PALETTE[i] = toLoad[i];
	}
}

void delay(int i) {
	volatile int n = 0;
	while (n < i) {
		waitForVblank();
		n++;
	}
}