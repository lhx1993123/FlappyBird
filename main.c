// Hexiang Li

#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"
#include "pics.h"
#include "pics.c"


int main()
{
	REG_DISPCTL = MODE4 | BG2_ENABLE | BUFFER1FLAG;
	loadPalette(pics_palette, PICS_PALETTE_SIZE, 0);

	int state = BEGIN;
	while(1)
	{
		switch(state)
		{
			case BEGIN:
				// loadPalette(pics_palette, PICS_PALETTE_SIZE, 0);
				drawImage4(0, 0, 240, 160, (u16*)screen);
				waitForVblank();
				FlipPage();
				while(!KEY_DOWN_NOW(BUTTON_START));
				state = GAME;
				break;
			case GAME:
				state = play();
				break;
			case WIN:
				loadPalette(pics_palette, PICS_PALETTE_SIZE, 0);
				drawImage4(0, 0, 240, 160, (u16*)win);
				drawString4(5, 8, "Press Select", PALETTE[0]);
				waitForVblank();
				FlipPage();
					while(!KEY_DOWN_NOW(BUTTON_SELECT));
				state = BEGIN;
				break;
			case LOSE:
				// loadPalette(pics_palette, PICS_PALETTE_SIZE, 0);
				drawImage4(0, 0, 240, 160, (u16*)die);
				waitForVblank();
				FlipPage();
				while(!KEY_DOWN_NOW(BUTTON_SELECT));
				state = BEGIN;
				break;
			default:
				break;
		}
	}
	return 0;
}

int play()
{
	int score = 0;
	int speed = 1;
	int life = 1;
	int timer = 10;
	int pT = 0;
	char lifes[15];
	char scores[15];

	BIRD bird;
	bird.r = 70;
	bird.c = BIRD_C;

	// loadPalette(pics_palette, PICS_PALETTE_SIZE, 0);
	drawImage4(0, 0, 240, 160, (u16*)background);
	FlipPage();
	drawImage4(0, 0, 240, 160, (u16*)background);

	PIPE pp[4];
	for(int i = 0; i < 4; i++)
	{
		pp[i].r = 10;
		pp[i].c = 219 - i*60;
		pp[i].hole = 25 + rand() / (RAND_MAX / (145 - HOLE_L - 25 + 1) + 1);
		pp[i].on = 0;

		if(i == 0)
		{
			pp[i].on = 1;
		}
	}

	int frame = 0;
	while(1)
	{
		if(KEY_DOWN_NOW(BUTTON_SELECT))
		{
			return 0;
		}

		if(KEY_DOWN_NOW(BUTTON_A))
		{
			speed = -5;
		}

		if(timer == 0)
		{
			bird.r += speed;
			speed++;
			timer = 3;
		}
		timer--;
		if(pT == 0)
		{
			pp[0].on = 1;
		}
		else
		{
			pT--;
		}
		if(bird.r < 10)
		{
			bird.r = 10;
		}
		if(bird.r > 149)
		{			
			life--;
			if (life < 0) 
			{
				return LOSE;
			}
			bird.r = 70;
			speed = 1;
			timer = 2;
		}

		for(int i = 1; i < 4; i++)
		{
			if(pp[0].c < 220 - i*60 && !pp[i].on)
			{
				pp[i].c = 219;
				pp[i].on = 1;
			}
		}

		for(int i = 0; i < 4; i++)
		{
			if(pp[i].on)
			{
				pp[i].c -= 1;
				if(bird.c == (pp[i].c + PIPE_W / 2) && pp[i].on)
				{
					score++;
					if(score == 5)
					{
						return WIN;
					}
				}
				if(pp[i].c < 0)
				{
					pp[i].c = 219;
					pp[i].hole = 25 + rand() / (RAND_MAX / (145 - HOLE_L - 25 + 1) + 1);
					pT = 20;
					pp[i].on = 0;
				}
				//collision
				if(bird.c + 14 > pp[i].c && bird.c < pp[i].c + 20 && ((bird.r < pp[i].hole) | (bird.r + 10 > pp[i].hole + HOLE_L)) && pp[i].on)
				{
					life--;
					if (life < 0)
					{
						return LOSE;		
					}
					bird.r = pp[i].hole + 2;
					speed = 1;
					timer = 2;
				}
			}
		}

		drawImage4(0, 0, 240, 160, (u16*)background);
		delay(3);


		//draw pipe
		for(int i = 0; i < 4; i++)
		{
			if(pp[i].on)
			{
				drawPipe(pp[i].r, pp[i].c, pp[i].hole, (u16*)pipes);
			}
		}

		//draw bird
		if(frame % 9 == 0)
		{
			drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy0);
		}
		else if(frame % 9 == 1)
		{
			drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy1);
		}
		else if(frame % 9 == 2)
		{
			drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy2);
		}
		else if(frame % 9 == 3)
		{
			drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy3);
		}
		else if(frame % 9 == 4)
		{
			drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy4);
		}
		else if(frame % 9 == 5)
		{
			drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy5);
		}
		else if(frame % 9 == 6)
		{
			drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy6);
		}
		else if(frame % 9 == 7)
		{
			drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy7);
		}
		else
		{
			drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy8);
		}
			// drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy0);
			// drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy1);
			// drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy2);
			// drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy3);
			// drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy4);
			// drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy5);
			// drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy6);
			// drawImage4(bird.r, bird.c, BIRD_W, BIRD_H, (u16*)flappy7);
		sprintf(lifes, "Life: %d", life);
		drawString4(0, 10, lifes, PALETTE[0]);
		sprintf(scores, "Score: %d", score);
		drawString4(0, 170, scores, PALETTE[0]);
		waitForVblank();
		frame++;
		FlipPage();
	}
	return 1;
}

