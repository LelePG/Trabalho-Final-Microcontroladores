#include <at89x52.h>
#include <lib_timers.h>
#include <definesIO.h>


void ativaAgua(void);
void atualizaDisplays(int numero);
void verificaSegundo(); //Verifica se um segundo se passou
int identificaCaractere(void);
void decodificaAlgorismo(int numero);
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
		//if(segundosDisplay == 0){
		//	ativaAgua();
		//}
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
	int tempoFinal;
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

int leColunas(int a, int b, int c){
	
	if (bitColuna1 )
		{
			return a;
		}
		else if (bitColuna2)
		{
			return b;
		}
		else if (bitColuna3)
		{
			return c;
		}
		
		return 99;
	
}

int identificaCaractere()
{
int valorLido;
	while (1)
	{
		int delayTempo = 30;
		delayT0(delayTempo);

		bitLinhaA = 0;
		bitLinhaB = 0;
	
		valorLido = leColunas(1,2,3);
		if(valorLido!=99){
			return valorLido;
		}
		
		
		delayT0(delayTempo);
		bitLinhaA = 1;
		bitLinhaB = 0;

		
		valorLido = leColunas(4,5,6);
		if(valorLido!=99){
			return valorLido;
		}

		delayT0(delayTempo);
		bitLinhaA = 0;
		bitLinhaB = 1;

		
		valorLido = leColunas(7,8,9);
		if(valorLido!=99){
			return valorLido;
		}
		
		delayT0(delayTempo);

		bitLinhaA = 1;
		bitLinhaB = 1;

		
		valorLido = leColunas(-5,0,-10); // -5 = * e -10 = #
		if(valorLido!=99){
			return valorLido;
		}
		
		delayT0(delayTempo);
	}
}

void ativaAgua(void) interrupt 2
{ // foi apertardo o bot�o p3.2
	//reseta o contador principal
	EA = 0;
	//desativaT1();
	contadorDeMiliSeg = 0;
	segundosDisplay = valorResetaTimer;

	//Ativa luz, buzzer e bomba
	ligaLED(500);

	EA = 1;
	iniciaCont50msT1();
	return;
}

void atualizaDisplays(int numero)
{
	//atualiza display da unidade
	decodificaAlgorismo(numero % 10);
	unidade = 0;
	delayT0(10);
	unidade = 1;

	//atualiza display da dezena
	decodificaAlgorismo(((int)(numero / 10) % 10));
	dezena = 0;
	delayT0(10);
	dezena = 1;

	//atualiza display da centena
	decodificaAlgorismo(((int)(numero / 100) % 10));
	centena = 0;
	delayT0(10);
	centena = 1;

	//atualiza display do milhar
	decodificaAlgorismo(((int)(numero / 1000) % 10));
	milhar = 0;
	delayT0(10);
	milhar = 1;

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

void decodificaAlgorismo(int numero)
{
	switch (numero)
	{
	case 0:
		bitA = 0;
		bitB = 0;
		bitC = 0;
		bitD = 0;
		break;
	case 1:
		bitA = 1;
		bitB = 0;
		bitC = 0;
		bitD = 0;
		break;
	case 2:
		bitA = 0;
		bitB = 1;
		bitC = 0;
		bitD = 0;
		break;
	case 3:
		bitA = 1;
		bitB = 1;
		bitC = 0;
		bitD = 0;
		break;
	case 4:
		bitA = 0;
		bitB = 0;
		bitC = 1;
		bitD = 0;
		break;
	case 5:
		bitA = 1;
		bitB = 0;
		bitC = 1;
		bitD = 0;
		break;
	case 6:
		bitA = 0;
		bitB = 1;
		bitC = 1;
		bitD = 0;
		break;
	case 7:
		bitA = 1;
		bitB = 1;
		bitC = 1;
		bitD = 0;
		break;
	case 8:
		bitA = 0;
		bitB = 0;
		bitC = 0;
		bitD = 1;
		break;
	case 9:
		bitA = 1;
		bitB = 0;
		bitC = 0;
		bitD = 1;
		break;
	}

	return;
}
