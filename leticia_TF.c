#include <at89x52.h>
#include <lib_timers.h>
#include <lib_7seg.h>
#include <lib_keypad.h>
#include <definesIO.h>


void ativaAgua(void);
void verificaSegundo(); //Verifica se um segundo se passou
int defineIntervalo();
void configuraAplicacao();
void ligaLED(int tempoDelay);

int valorResetaTimer = 200;
int contadorDeMiliSeg;
int segundosDisplay;

void main()
{
	configuraAplicacao();
	while (1)
	{

		atualizaDisplays(segundosDisplay);
		if(segundosDisplay == 0){
			ativaAgua();
		}
		//delayT0(1000);
	}
}

int c = 0;

void ligaLED(int tempoDelay)
{ //Prot�tipo tem coisa pra melhorar aqui
	enableAllLEDs = 0;
	enableLEDs = 1;
	tempoDelay = tempoDelay / 7;
	for (c = 0; c <= 10; c++)
	{
		decodificaAlgorismo(c);
		delayT0(tempoDelay * 0.5);
	}
	enableAllLEDs = 1;
	delayT0(tempoDelay * 2);
	enableAllLEDs = 0;
	enableLEDs = 0;
	return;
}

void configuraAplicacao()
{
	enableAllLEDs = 0;
	enableLEDs = 0;
	defineIntervalo();

	EA = 1;
	ET1 = 1;
	EX0 = 1;
	EX1 = 1;
	segundosDisplay = valorResetaTimer;
	iniciaCont50msT1();
}

int defineIntervalo()
{
	int inputUsuario;
	int tempoFinal = 0;
	do
	{
		tempoFinal *= 10;
		tempoFinal += inputUsuario;
		inputUsuario = identificaCaractere();
		//atualizaDisplays(inputUsuario);
		delayT0(300);
	} while (inputUsuario >= 0);
	valorResetaTimer = tempoFinal;
	return tempoFinal;
}



void ativaAgua(void) interrupt 2
{ // foi apertardo o bot�o p3.2
	//reseta o contador principal
	EA = 0;
	unidade = 1;
	dezena = 1;
	centena = 1;
	milhar = 1;
	desativaT1();
	contadorDeMiliSeg = 0;
	segundosDisplay = valorResetaTimer;

	//Ativa luz, buzzer e bomba
	ligaLED(500);

	EA = 1;
	iniciaCont50msT1();
	return;
}



void verificaSegundo() interrupt 3
{
	//Verifica se um segundo passou, levando em considera��o que para que isso aconte�a
	//a fun��o espera 50ms precisa ser executada 200 vezes.
	desativaT1();
	contadorDeMiliSeg++; //anota mais uma execu��o da fun��o espera 50ms
	if (contadorDeMiliSeg == 200)
	{
		segundosDisplay--; //diminui o valor de segundos exibido no display
		contadorDeMiliSeg = 0;
	}
	iniciaCont50msT1(); // inicia o contador novamente
	return;
}

