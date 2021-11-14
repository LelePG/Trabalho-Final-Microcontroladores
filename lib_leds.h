//Pinos relativos aos LEDs
#define ativaComponentes P0_7 //utilizada para os LEDs e para a "bomba"
#define enableAllLEDs P0_6

void ligaLED(int tempoDelay);//Liga os LEDs e dispensa água

int c;
	
void ligaLED(int tempoDelay)
{ 
	enableAllLEDs = 0;
	ativaComponentes = 1;

	tempoDelay = (int) tempoDelay/7; //atualiza o tempo para que o tempo total desejado seja atingido com a função

	for (c = 0; c <= 10; c++)
	{
		decodificaAlgorismo(c);
		delayT0(tempoDelay * 0.5);
	}
	enableAllLEDs = 1;
	delayT0(tempoDelay * 2);
	enableAllLEDs = 0;
	ativaComponentes = 0;
}



