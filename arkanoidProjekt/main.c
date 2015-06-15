#include <eZ8.h>
#include <sio.h>
#include "ansi.h"

long millis = 0;
long ball_timer = 0;

#pragma interrupt
int timer0int(){
	millis++;
	ball_timer++;
}
<
void timersetup(){

	DI();
	T0CTL = 0x09;
	T0H = 0x00;
	T0L = 0x01;
	T0RH = 0x24;
	T0RL = 0x00;
	SET_VECTOR(TIMER0,timer0int);
	
	IRQ0ENH |= 0x20;
	IRQ0ENL &= 0xDF;

	//start count
	T0CTL |= 0x80;
	EI();	
}
void keysetup(){
	PFDD = 0xC0;
	PDDD = 0x08; 
}
char key_press(){
  char r=0;

  if(((PDIN >> 3) & 1) == 0) r+=1;
  if(((PFIN >> 6) & 1) == 0) r+=2;
  //if(((PFIN >> 7) & 1) == 0) r+=4;

  return r;
}
void slidersetup(int sx, int sy){
	char si;
	gotoxy(sy,sx-2);
	for(si = 0; si < 5; si++){

	printf("%c",219);
	}
}
sliderupdate(char *x, char *y){
	if(key_press() == 2 & *x != 68){
		gotoxy(*y,*x-2);
		printf("%c",32);
		(*x)++;
		gotoxy(*y,*x+2);
		printf("%c",219);
	
	}
	else if(key_press() == 1 & *x != 4){
		gotoxy(*y,*x+2);
		printf("%c",32);
		(*x)--;
		gotoxy(*y,*x-2);
		printf("%c",219);
	
	}
}

void  main (){
	char sx = 35;
	char sy = 20;
	init_uart(_UART0,_DEFFREQ,_DEFBAUD);
	gotoxy(0,0);
	timersetup();
	keysetup();
	gamesetup(0,0,70,20);
	slidersetup(sx,sy);
	for(;;){
	if(ball_timer > 50){
		ball_timer = 0;
		sliderupdate(&sx, &sy);
		
		}
	}
	for(;;){
	}
}


