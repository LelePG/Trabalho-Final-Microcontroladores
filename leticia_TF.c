#include <at89x52.h>
#include <lib_timers.h>
#include <lib_7seg.h>
#include <lib_keypad.h>
#include <lib_lcd.h>
#include <lib_ativaAgua.h>
#include <definesIO.h>


void ativaAgua(void);
void verificaSegundo(); //Verifica se um segundo se passou
void defineIntervalo();
void configuraAplicacao();
void configInterrupcoes();
void ativaAguaInterrupt();
void defineIntervaloInterrupt();

int valorResetaTimer = 200;
int contadorDeMiliSeg;
int segundosDisplay;


volatile bit flagAtivaAgua = 0;
volatile bit flagDefineIntervalo = 0;


void main()
{
	configLCD();
	configInterrupcoes();
	configuraAplicacao();
	while (1)
	{
		atualizaDisplays(segundosDisplay);
		if(segundosDisplay == 0){ //condição para ativar a ágia
			ativaAgua();
		} else if (flagAtivaAgua ==1){ //condição para ativar a água
			flagAtivaAgua = 0;
			ativaAgua();
			EX1 = 1;
		} else if (flagDefineIntervalo ==1){ //confição para mudar o intervalo entre hidratações
			flagDefineIntervalo = 0;
			defineIntervalo();
			EX0 = 1;
		}
	}
}

void configuraAplicacao() 
{
	enableAllLEDs = 0;
	enableLEDs = 0;
	defineIntervalo();
	
}


void configInterrupcoes(){
	EA = 1;
	ET1 = 1;
	EX0 = 1;
	EX1 = 1;
	return;
}

void defineIntervalo()
{
	int inputUsuario =0;
	desativaT1();

	valorResetaTimer	 = 0;
		mensagemInicial();

	do
	{
			valorResetaTimer *= 10;
			valorResetaTimer += inputUsuario;
		inputUsuario = identificaCaractere();
		//atualizaDisplays(inputUsuario);
		delayT0(300);
	} while (inputUsuario >= 0);
	if(valorResetaTimer < 5){
		valorResetaTimer = 5;
	}

	clearLCD();
	segundosDisplay = valorResetaTimer;

	iniciaCont50msT1();

	return;
}



void ativaAgua(void) //não está retornando pra main
{ 
	mensagemAguaInicial();
	
	EA = 0;
	unidade = 1;
	dezena = 1;
	centena = 1;
	milhar = 1;
	desativaT1();
	contadorDeMiliSeg = 0;
	segundosDisplay = valorResetaTimer;

	//Ativa luz, buzzer e bomba
	ligaLED(90);
	mensagemAguaFinal();
	
	iniciaCont50msT1();
		EA = 1;

	return;
}



void defineIntervaloInterrupt() interrupt 0{
	flagDefineIntervalo = 1;
	EX0 = 0;
}

void ativaAguaInterrupt() interrupt 2{
	flagAtivaAgua = 1;
	EX1 = 0;
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

