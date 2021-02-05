#include <sdl.h>
#include <sdl_ttf.h>
#include <iostream>
#include <sstream>

#include "c:\z\_MI\Window.h"
#include "c:\z\_MI\defines.h"
#include "c:\z\_MI\drawshapes.h"
#include "c:\z\_MI\drawfontsolid.h"
#include "c:\z\_MI\colors.h"

#undef main

#define DARKBLUE     0,  0, 25,255
#define DARKGREEN    0, 25,  0,255
#define DDARKGREEN   0, 15,  0,255
#define LDARKGREEN   0, 45,  0,255

#pragma warning(disable:4505)

static void drawFont();
static void rectAccordian();

static void drawCenterBounds();
static void rectCenter();

static void drawCornersBounds();
static void rectCorners();

static void drawSidesBounds();
static void rectSides();
//static bool counter(int &incre, int value);
static void rectRandom();
static void leftrightRandom();
static int countdown(int incre, int time);
	
SDL_Window*   window;
SDL_Renderer* renderer;
SDL_Event     e;

SDL_Texture*  solidTexture;
SDL_Texture*  text;
SDL_Rect		  solidRect;
TTF_Font*	  gFont;

const int FPS = 30;

static int val = 100;
static int val1 = 0;
int s = 10;
int changer = 5;

int lrcheck = 0;
static bool keywaspressed = false;
static bool keystateup = true;

enum { OPAQ,TRAN };

struct RectBounds
{
	int x;
	int y;
	int w;
	int h;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

int main()
{

	// init_Window(1600/4,0,
	// 				1600,900,
	// 				0,0);

	init_Window(0,0,
					1600,900,
					2,1);
	
	bool running = true;

	while(running)
	{

		//input
		while(POLLEVENT)
		{
			if(UPPRESS)
			{
				if(LEFT)     { lrcheck = 0;keywaspressed = false; }
				if(RIGHT)    { lrcheck = 0;keywaspressed = false; }
			}
			if(DOWNPRESS)
			{
				if(ESCAPE)   { running = false; }
				if(I_KEY)    { s++;       }
				if(K_KEY)    { s--;       }
				if(HOME)     { changer--; }
				if(END)      { changer++; }
				
				if(PAGEUP)   { val+=10;   }
				if(PAGEDOWN) { val-=10;   }
				
				if(E_KEY)    { val1++;    }
				if(D_KEY)    { val1--;    }

				if(UP)       { val++;     }
				if(DOWN)     { val--;     }
				if(LEFT)     { lrcheck = 1;keywaspressed = true; }
				if(RIGHT)    { lrcheck = 2;keywaspressed = true; }
			}
		}

		if(changer<0) changer=0;
		if(changer>5) changer=5;

		//draw
		SDL_SetRenderDrawColor(renderer, DARKBLUE);
		
		SDL_RenderClear(renderer);
		drawFillRect(0,0,1600,900,LDARKGREEN,0); //screen dimensions
		
		drawFont();
		
		switch(changer)
		{
			case 0:
			{
				drawCenterBounds();
				rectCenter();
			}break;
			case 1:
			{
				
				drawCornersBounds();
				rectCorners();
			}break;
			case 2:
			{
				drawSidesBounds();
				rectSides();
			}break;
			case 3:
			{
				rectAccordian();
			}break;
			case 4:
			{
				rectRandom();
			}break;
			case 5:
			{
				leftrightRandom();
			}break;
		}
		
		SDL_RenderPresent(renderer);
		
		//properties
		//SDL_Delay(1000/FPS);
		SDL_ShowCursor(SDL_DISABLE); //hide cursor
	}
	
	return(0);
}

static void drawCenterBounds()
{

	int cx = 1600/2;
	int cy =  900/2;
	
	drawFillRect(cx-25,cy-25,
					 25+25,25+25,
					 0,18,0,255,
					 OPAQ);
	
	drawFillRect(cx-2,cy-2,
					 4,4,
					 0,0,0,255,
					 OPAQ);
	
}

static void drawCornersBounds()
{

	int cx = 10;//1600/2;
	int cy = 10;// 900/2;
	
	drawFillRect(cx,cy,
					 25+25,25+25,
					 0,18,0,255,
					 OPAQ);

	cx = 1600-25-10-25;
	cy = 10;
	
	drawFillRect(cx,cy,
					 25+25,25+25,
					 0,18,0,255,
					 OPAQ);

	cx = 10;
	cy = 900-25-10-25;
	
	drawFillRect(cx,cy,
					 25+25,25+25,
					 0,18,0,255,
					 OPAQ);

	cx = 1600-25-10-25;
	cy = 900-25-10-25;
	
	drawFillRect(cx,cy,
					 25+25,25+25,
					 0,18,0,255,
					 OPAQ);
	
	
}

static void drawSidesBounds()
{

	int regionbounds = 50;
	int recthalf = 25;
	int screenhalf = 1600/2;
	
	int rectcenter = screenhalf-recthalf;
	
	int cx = rectcenter;
	int cy = 10;
	
	drawFillRect(cx,cy,
					 regionbounds,regionbounds,
					 DARKGREEN,
					 OPAQ);

	cx = 1600/2-25;
	cy = 900-25-10-25;
	
	drawFillRect(cx,cy,
					 25+25,25+25,
					 DARKGREEN,
					 OPAQ);

	cx = 10;
	cy = 900/2-25;
	
	drawFillRect(cx,cy,
					 25+25,25+25,
					 DARKGREEN,
					 OPAQ);

	cx = 1600-25-10-25;
	cy = 900/2-25;
	
	drawFillRect(cx,cy,
					 25+25,25+25,
					 DARKGREEN,
					 OPAQ);

	// center pixel
	drawFillRect(1600/2-1,  10+25,     2,2, BLACK, OPAQ);
	drawFillRect(1600/2-1,  900-25-10, 2,2, BLACK, OPAQ);
	drawFillRect(10+25,     900/2-1,   2,2, BLACK, OPAQ);
	drawFillRect(1600-25-10,900/2-1,   2,2, BLACK, OPAQ);
	
}

static void drawFont()
{
	
	//CONVERSION INT TO CONST CHAR*
	std::stringstream convert1;
	convert1 << val;
	std::string one  = convert1.str();
	const char* cone = one.c_str();

	drawFontSolid(0,0,0,
					  100,0,
					  cone,
					  CYAN,
					  "c:/z/_MI/data/font/arial.ttf",32);
	
}

static void rectCorners()
{

	RectBounds rb = { 100,100,s,s, 255,0,0,255 };
	
	static unsigned int udlf = 1;
	
	static unsigned int rx = 1;//rand() % 25;
	static unsigned int ry = 1;//rand() % 25;
	
	static int incre = 0;

	if(incre >= val)
	{
		udlf = rand() % 4;
		
		rx = rand() % 45;
		ry = rand() % 45;

		incre = 0;
	}
	else
	{
		switch(udlf)
		{
			case 0:{ drawFillRect(             10+rx,            10+ry, rb.w,rb.h, rb.r,rb.g,rb.b,rb.a, OPAQ); }break;
			case 1:{ drawFillRect((1600-25-10-25)+rx,            10+ry, rb.w,rb.h, rb.r,rb.g,rb.b,rb.a, OPAQ); }break;
			case 2:{ drawFillRect(             10+rx,(900-25-10-25)+ry, rb.w,rb.h, rb.r,rb.g,rb.b,rb.a, OPAQ); }break;
			case 3:{ drawFillRect((1600-25-10-25)+rx,(900-25-10-25)+ry, rb.w,rb.h, rb.r,rb.g,rb.b,rb.a, OPAQ); }break;
		}
	}
	
	incre++;

}

static void rectSides()
{

	RectBounds rb = { 100,100,s,s, 255,0,0,255 };
	
	static unsigned int udlf = 1;
	
	static unsigned int rx = 1;//rand() % 25;
	static unsigned int ry = 1;//rand() % 25;
	
	static int incre = 0;

	if(incre >= val)
	{
		udlf = rand() % 4;
		
		rx = rand() % 45;
		ry = rand() % 45;

		incre = 0;
	}
	else
	{
		switch(udlf)
		{
			case 0:
			{
				drawFillRect(10+rx,(450-25-5)+ry,
								 rb.w,rb.h,
								 rb.r,rb.g,rb.b,rb.a,
								 OPAQ);
			}break;
			case 1:
			{
				drawFillRect((1600-25-10-25)+rx,(450-25-5)+ry,
								 rb.w,rb.h,
								 rb.r,rb.g,rb.b,rb.a,
								 OPAQ);
			}break;
			case 2:
			{
				drawFillRect((750+25)+rx,10+ry,
								 rb.w,rb.h,
								 rb.r,rb.g,rb.b,rb.a,
								 OPAQ);
			}break;
			case 3:
			{
				drawFillRect((750+25)+rx,(900-25-10-25)+ry,
								 rb.w,rb.h,
								 rb.r,rb.g,rb.b,rb.a,
								 OPAQ);
			}break;
		}
	}
	
	incre++;

}

static void rectAccordian()
{
	
	for(int i = 0; i < 100/2; i++)
	{
		drawFillRect(100+(i*val1),100+(i*val1),50,50,
						 0+(Uint8)(i), 122+(Uint8)(i), 200+(Uint8)(i), 255,
						 1);
	}
	
}

static void rectCenter()
{
	
	RectBounds rb = { 100,100, 5,5, RED };
		
	unsigned int rvx = rand() % 45;
	unsigned int rvy = rand() % 45;

	static int tempx = 0;
	static int tempy = 0;
		
	static int incre = 0;
	
	if(incre >= val)
	{
		tempx = rvx;
		tempy = rvy;
			
		incre = 0;
	}
	else
	{
		drawFillRect(((1600/2)-25)+tempx,((900/2)-25)+tempy, rb.w,rb.h, rb.r,rb.g,rb.b,rb.a, OPAQ);
	}
	
	incre++;
}

// static bool counter(int &incre, int value)
// {
// 	if(incre >= value)
// 	{
// 		incre = 0;
// 		return true;
// 	}
// 	incre++;
// 	return false;
// }

static void rectRandom()
{
	
	unsigned int rx = rand() % 1600;
	unsigned int ry = rand() % 900;

	static int tempx = 0;
	static int tempy = 0;
	static int incre = 0;
	if(incre >= val)
	{
		
		tempx = rx;
		tempy = ry;
		incre = 0;
	}
	else
	{
		
		drawFillRect(tempx-25,tempy-25, 25,25, RED, OPAQ);
	}
	
	incre++;
}

static void leftrightRandom()
{

	int cx = 1600/2;
	int cy = 900/2;
	
	unsigned int lr = rand() % 2;
	
	static int templr = lr;

	static int score = 0;
	static int fail = 0;

	static int incre1 = 0;
	static int incre2 = 0;
	
	//CONVERSION INT TO CONST CHAR*
	std::stringstream convert1;
	convert1 << score;
	std::string one  = convert1.str();
	const char* cscore = one.c_str();

	std::stringstream convert2;
	convert2 << fail;
	std::string two  = convert2.str();
	const char* cfail = two.c_str();

	std::stringstream convert3;
	convert3 << val1;
	std::string three  = convert3.str();
	const char* cval1 = three.c_str();

	std::stringstream convert4;
	convert4 << val1/6;
	std::string four  = convert4.str();
	const char* cval2 = four.c_str();

	if(incre1 >= val1)
	{
		keystateup = true;
		templr = lr;
		incre1 = 0;
	}
	else
	{
		if(incre1 > (val1/6))
		{
			if(incre2 >= val)
			{
				incre2 = 0;
			}
			else
			{
				
				if(keywaspressed == true && keystateup == true)
				{
					if(keystateup)
					{
						if(lrcheck == 1 && templr == 0){ score++;  } // left, left
						if(lrcheck == 2 && templr == 1){ score++;  } // right, right
						
						if(lrcheck == 1 && templr == 1){ fail-- ;  } // left, right
						if(lrcheck == 2 && templr == 0){ fail-- ;  } // right, left
						
						keystateup = !keystateup;
					}
				}
				
				// left, right
				if(templr == 0)
				{
					//drawFontSolid( 2,0,0, cx-3,cy, "LEFT",  CYAN, "c:/z/_MI/data/font/arial.ttf",32 );
					drawFontSolid( 1,0,0, cx,cy, "LEFT",  GREEN, "c:/z/_MI/data/font/arial.ttf",32 );
				}
				else
				{
					//drawFontSolid( 0,0,0, cx+3,cy, "RIGHT", CYAN, "c:/z/_MI/data/font/arial.ttf",32 );
					drawFontSolid( 1,0,0, cx,cy, "RIGHT", GREEN, "c:/z/_MI/data/font/arial.ttf",32 );
				}
				
			}
			incre2++;
		}
	}

	// points
	drawFontSolid( 0,0,0, cx-50,cy-50, cscore, CYAN, "c:/z/_MI/data/font/arial.ttf",32 ); // score
	drawFontSolid( 0,0,0, cx+50,cy-50,  cfail,  RED, "c:/z/_MI/data/font/arial.ttf",32 ); // fails

	drawFontSolid( 0,0,0, 200,0,  cval1, WHITE, "c:/z/_MI/data/font/arial.ttf",32 );//val1
	drawFontSolid( 0,0,0, 300,0,  cval2, WHITE, "c:/z/_MI/data/font/arial.ttf",32 );//val1/6
	

	incre1++;
}

/*

////////////////

int main()
{

 int (*func)(param_list);
 (*func)(params);
 func(params);
}

////////////////

void f();
void (*p_fun)() =   f;
void (*p_fun)() = & f;

////////////////

char ** fun()
{
 static char * z = (char*)"Merry Christmas :)";
 retunr &z;
}
int main()
{
 char ** ptr = NULL;
 char ** (*fun_ptr)();
 fun_ptr = &fun;
 printf("%s %p",*ptr,fun);
}

////////////////

 */
