/*
 * Exported with nin10kit v1.0
 * Invocation command was nin10kit -mode=4 pics screen.jpg background.png win.jpg die.png 
 * Time-stamp: Sunday 11/08/2015, 22:28:04
 * 
 * Image Information
 * -----------------
 * screen.jpg 240@160
 * background.png 240@160
 * win.jpg 240@160
 * die.png 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef PICS_H
#define PICS_H

extern const unsigned short pics_palette[200];
#define PICS_PALETTE_SIZE 200

extern const unsigned short screen[19200];
#define SCREEN_SIZE 19200
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

extern const unsigned short background[19200];
#define BACKGROUND_SIZE 19200
#define BACKGROUND_WIDTH 240
#define BACKGROUND_HEIGHT 160

extern const unsigned short win[19200];
#define WIN_SIZE 19200
#define WIN_WIDTH 240
#define WIN_HEIGHT 160

extern const unsigned short die[19200];
#define DIE_SIZE 19200
#define DIE_WIDTH 240
#define DIE_HEIGHT 160

#endif

