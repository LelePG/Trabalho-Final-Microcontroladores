#define buzzer P0_7


//Pinos relativos aos LEDs
#define ativaComponentes P0_7 //utilizada para os LEDs e para a "bomba"
#define enableAllLEDs P0_6

	int c;
	
void ligaLED(int tempoDelay)
{ 
	enableAllLEDs = 0;
	ativaComponentes = 1;

	for (c = 0; c <= 10; c++)
	{
		decodificaAlgorismo(c);
		delayT0(tempoDelay * 0.5);
	}
	enableAllLEDs = 1;
	delayT0(tempoDelay * 2);
	enableAllLEDs = 0;
	ativaComponentes = 0;
	return;
}



