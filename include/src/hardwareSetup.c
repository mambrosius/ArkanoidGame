
long ms = 0;
long ball_timer = 0;

#pragma interrupt
int timer0int() {

	ms++:
	ball_timer++; 
}

void timerSetup(){

	DI();
	T0CTL = 0x09;	// Timer control
	T0H   = 0x00;	// Timer high
	T0L   = 0x01;	// Timer low
	T0RH  = 0x24;	// Timer reload high
	T0RL  = 0x00;	// Timer reload low

	SET_VECTOR(TIMER0,timer0int);

	IRQ0ENH |= 0x20; // Enable high
	IRQ0ENL &= 0xDF; // Enable low 

	// Starting count
	T0CTL |= 0x80;

	EI();	
}

void keySetup(){

	PFDD = 0xC0;
	PDDD = 0x08;

}

char keyPress(){
 	
 	char r=0;
 	
	if(((PDIN >> 3) & 1) == 0) r+=1;
  	if(((PFIN >> 6) & 1) == 0) r+=2;

  return r;
}