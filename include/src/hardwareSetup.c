

#pragma interrupt
void (){

void timersetup(){

	DI();
	T0CTL = 0x39;
	T0H = 0x00;
	T0L = 0x01;
	T0RH = 0x00;
	T0RL = 0x48;
	SET_VECTOR(TIMER0,timer0int);
	
	IRQ0ENH |= 0x00;
	IRQ0ENL |= 0x20;
	
	

	//start count
	T0CTL |= 0x80;

    
	EI();	
}
