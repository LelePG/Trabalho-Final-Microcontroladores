#include<at89x52.h>
#include <libTF.h>

#define bombaAgua P0_0
#define buzzer P0_1

//Dados relativos ao display de 7 segmentos
#define dados7seg P2
#define unidade P1_7
#define dezena P1_6
#define centena P1_5
#define milhar P1_4



void ativaAgua(void);
void atualizaDisplays(int numero);
void verificaSegundo(); //Verifica se um segundo se passou


int valorResetaContador = 251;

int contadorDeMiliSeg;
int segundosDisplay = 300;

void main(){
	EA = 1;
	ET1 = 1;
	EX0 = 1;
	iniciaCont50msT1();

	while(1){	
			//ativaAgua();
		//atualizaDisplays(segundosDisplay);
		//delayT0(100);
}

 //Rotina de ativar a água
void ativaAgua(void){
  bombaAgua = 0;
  //luz.setCode(1);
  buzzer = 1845;
  delayT0(1000);
  bombaAgua= 1;
	buzzer = 0;
	delayT0(10);
	
	
  //luz.setCode(6);
}




void atualizaDisplays(int numero){
			//atualiza display da unidade
			dados7seg = decodificaAlgorismo(numero%10);
			unidade = 1;
			delayT0(10);
			unidade = 0;
	
			//atualiza display da dezena
			dados7seg = decodificaAlgorismo(((int)(numero/10)%10));
			dezena = 1;
			delayT0(10);
			dezena = 0;
	
			//atualiza display da centena
			dados7seg = decodificaAlgorismo(((int)(numero/100)%10));
			centena = 1;
			delayT0(10);
			centena = 0;
	
			//atualiza display do milhar
			dados7seg = decodificaAlgorismo(((int)(numero/1000)%10));
			milhar = 1;
			delayT0(10);
			milhar = 0;
	
			return;
}


void verificaSegundo() interrupt 3{
	//Verifica se um segundo passou, levando em consideração que para que isso aconteça
	//a função espera 50ms precisa ser executada 200 vezes.
	desativaT1();
	contadorDeMiliSeg++; //anota mais uma execução da função espera 50ms
	if (contadorDeMiliSeg == 200){
		segundosDisplay--; //diminui o valor de segundos exibido no display
		contadorDeMiliSeg = 0;
	}
	iniciaCont50msT1(); // inicia o contador novamente
	return;
}


