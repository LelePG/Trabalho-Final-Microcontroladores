#include <at89x52.h>
#include <lib_timers.h>
#include <lib_7seg.h>
#include <lib_keypad.h>
#include <lib_lcd.h>
#include <lib_ativaAgua.h>

#define TEMPO_DE_FUNCIONAMENTO 2000 //tempo que a bomba ficará ativada

//Configurações inicias
void configuraAplicacao();
void configInterrupcoes();
void defineIntervalo(); //define o intervalo em segundos entre as hidratações
//Funções relacionadas à interrupções
void ativaAguaInterrupt();		 //liga a flag, disparada por interrupção externa
void defineIntervaloInterrupt(); //liga a flag, disparada por interrupção externa
void verificaSegundo();			 //Verifica se um segundo se passou (disparada por interrupção no timer1)
// Outras funções
void ativaAgua();

//Variáveis globais necessárias para a contagem regressiva
int valorResetaTimer = 200;
int qtdeDeMiliSeg;
int tempoRestante;

//Flags ativadas pelas interrupções
volatile bit flagAtivaAgua = 0;
volatile bit flagDefineIntervalo = 0;

void main()
{
	configuraAplicacao(); //configurações iniciais
	while (1)
	{
		atualizaDisplays(tempoRestante);
		if (flagAtivaAgua == 1 || tempoRestante == 0)
		{ //condição para ativar agua
			flagAtivaAgua = 0;
			ativaAgua();
			EX1 = 1; //ativa novamente a interrupcao que liga a flag
		}
		else if (flagDefineIntervalo == 1)
		{ //confição para mudar o intervalo entre hidratações
			flagDefineIntervalo = 0;
			defineIntervalo();
			EX0 = 1; //ativa novamente a interrupcao que liga a flag
		}
	}
}

void configuraAplicacao()
{
	desligaAtuadores();
	configLCD();
	configInterrupcoes();
	defineIntervalo();
}

void configInterrupcoes()
{
	EA = 1;
	ET1 = 1;
	EX0 = 1;
	EX1 = 1;
}

void defineIntervalo()
{
	int inputUsuario = 0;
	desativaT1(); //Para o contador caso ele esteja ligado

	valorResetaTimer = 0;
	mensagemInicial();

	do
	{
		valorResetaTimer *= 10;
		valorResetaTimer += inputUsuario;
		inputUsuario = identificaCaractere();
		delayT0(200); //delay para que um aperto não seja considerado como vários
	} while (inputUsuario >= 0);

	if (valorResetaTimer < 5) //verificação de seguranca caso o usuário tenha digitado um número baixo demais
	{ 
		valorResetaTimer = 5;
	} else if (valorResetaTimer > 9999){
		valorResetaTimer = 9999;
	}

	clearLCD();
	tempoRestante = valorResetaTimer; //reinicia a contagem regressiva
	inicia50msT1();					  //liga o contador de segundos novamente
}

void ativaAgua(void)
{
	EA = 0; //desativa interrupções globais

	//Um bipe acontece junto com a mensagem
	ligaBuzzer();
	mensagemAguaInicial();
	desligaBuzzer();
	
	//desativa displays 7seg
	unidade = 1;
	dezena = 1;
	centena = 1;
	milhar = 1;
	desativaT1(); //desliga timer

	//reseta variáveis globais
	qtdeDeMiliSeg = 0;
	tempoRestante = valorResetaTimer;

	//Ativa componentes
	ligaBomba();
	ligaLED(TEMPO_DE_FUNCIONAMENTO);
	desligaBomba();
	
	
	//som na mensagem final
	ligaBuzzer();
	mensagemAguaFinal();
	desligaBuzzer();
	
	
	inicia50msT1();
	EA = 1; //ativa interrupcoes globais
}

void defineIntervaloInterrupt() interrupt 0 //Interrupção externa 0
{
	flagDefineIntervalo = 1;
	EX0 = 0;
}

void ativaAguaInterrupt() interrupt 2 //Interrupção externa 1
{
	flagAtivaAgua = 1;
	EX1 = 0;
}

void verificaSegundo() interrupt 3 //Interrupção de estouro do timer 1
{
	//Verifica se um segundo passou, levando em considera��o que para que isso aconte�a
	//a fun��o espera 50ms precisa ser executada 200 vezes.
	desativaT1();			  //desliga o timer
	qtdeDeMiliSeg++;		  //mais milissegundos se passaram
	if (qtdeDeMiliSeg == 200) // um segundo passou
	{
		tempoRestante--;   //diminui o valor de segundos exibido no display
		qtdeDeMiliSeg = 0; //reseta a quantidade de milissegundos
	}
	inicia50msT1(); // inicia o timer novamente
}
