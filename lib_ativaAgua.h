//Pinos relativos aos LEDs
#define enableLEDs P0_7 //utilizada para os LEDs e para a "bomba"
#define enableAllLEDs P0_6

#define bomba P0_5

#define buzzer P0_4

void ligaLED(int tempoDelay);//Liga os LEDs e dispensa água
void ligaBuzzer();
void desligaBuzzer();
void ligaBomba();
void desligaBomba();


int c;

void desligaAtuadores(){
	desligaBuzzer();
	desligaBomba();
	enableAllLEDs = 0;
	enableLEDs = 0;
}
	
void ligaLED(int tempoDelay)
{ 
	enableAllLEDs = 0;
	enableLEDs = 1;

	tempoDelay = (int) tempoDelay/7; //atualiza o tempo para que o tempo total desejado seja atingido com a função

	for (c = 0; c <= 10; c++)
	{
		decodificaAlgorismo(c);
		delayT0(tempoDelay * 0.5);
	}
	enableAllLEDs = 1;
	delayT0(tempoDelay * 2);
	enableAllLEDs = 0;
	enableLEDs = 0;
}

void ligaBuzzer(){
	buzzer = 1;
}

void desligaBuzzer(){
	buzzer = 0;
}


void ligaBomba(){
	bomba = 1;
}

void desligaBomba(){
	bomba = 0;
}


