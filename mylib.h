// Hexiang Li
typedef unsigned short u16;
typedef unsigned int u32;


extern unsigned short *videoBuffer;
extern const unsigned char fontdata_6x8[12288];


#define REG_DISPCTL *(u16 *)0x4000000
#define MODE3 3
#define MODE4 4

#define BUFFER0 (u16 *)0x6000000
#define BUFFER1 (u16 *)0x600A000
#define BUFFER1FLAG (1<<4)
#define PALETTE ((u16 *)0x5000000)

#define BG2_ENABLE (1<<10)
#define RGB(r,g,b) ((r) | ((g) << 5) | ((b) << 10))
#define RED RGB(31,0,0)
#define WHITE RGB(31,31,31)
#define BLACK 0
#define GREEN RGB(0,31,0)
#define BLUE RGB(0,0,31)
#define CYAN RGB(0,31,31)
#define MAGENTA RGB(31,0,31)
#define YELLOW RGB(31, 31, 0)
#define GRAY RGB(25, 25, 25)
#define LTGRAY RGB(20, 20, 20)
#define OFFSET(r,c,len) ((r)*(len)+(c))

#define BEGIN 0
#define GAME 1
#define WIN 2
#define LOSE 3

#define BIRD_W 14
#define BIRD_H 10
#define BIRD_C 70
#define HOLE_L 50
#define PIPE_W 20

typedef struct
{
	int r;
	int c;
}BIRD;

typedef struct
{
	int r;
	int c;
	int hole;
	int on;
}PIPE;


/* Buttons */

#define BUTTON_A      (1<<0)
#define BUTTON_B      (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START  (1<<3)
#define BUTTON_RIGHT  (1<<4)
#define BUTTON_LEFT   (1<<5)
#define BUTTON_UP     (1<<6)
#define BUTTON_DOWN   (1<<7)
#define BUTTON_R      (1<<8)
#define BUTTON_L      (1<<9)

#define BUTTONS (*( volatile unsigned int *)0x04000130)
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)
#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)

/* DMA */

#define REG_DMA0SAD         *(const volatile u32*)0x40000B0 // source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(const volatile u32*)0x40000BC // source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(const volatile u32*)0x40000C8 // source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(const volatile u32*)0x40000D4 // source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register

typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)


// Prototypes
void setPixel(int row, int col, u16 color);
void waitForVblank();
void setPixel4(int row, int col, char index);
void FlipPage();
// void fillScreen4(char index);
void drawImage4(int r, int c, int width, int height, const u16* image);
void drawPipe(int r, int c, int hole, const u16* image);
void drawChar(int row, int col, char ch, u16 color);
void drawString(int row, int col, char *str, u16 color);
void drawChar4(int row, int col, char ch, char index);
void drawString4(int row, int col, char *str, char index);
int play();
void loadPalette(const unsigned short * toLoad, int size, int offset);
void delay(int someInt);