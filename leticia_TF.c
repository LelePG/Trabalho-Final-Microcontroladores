#include<at89x52.h>
#include <libTF.h>

#define bombaAgua P0_6
#define buzzer P0_7

//Dados relativos ao display de 7 segmentos
//BCD
#define bitA P1_0
#define bitB P1_1
#define bitC P1_2
#define bitD P1_3
//Multiplexação
#define unidade P1_7
#define dezena P1_6
#define centena P1_5
#define milhar P1_4

//Dados relativos ao Keypad
#define bitLinhaA P0_0
#define bitLinhaB P0_1
#define bitColuna1 P0_2
#define bitColuna2 P0_3
#define bitColuna3 P0_4


#define ledTeste P0_5

void ativaAgua(void);
void atualizaDisplays(int numero);
void verificaSegundo(); //Verifica se um segundo se passou
int identificaCaractere(void);
void decodificaAlgorismo(int numero);
int defineIntervalo();
void configuraAplicacao();

int valorResetaTimer = 200;

int contadorDeMiliSeg;
int segundosDisplay;

void main(){
		configuraAplicacao();
while(1){
	
	atualizaDisplays(segundosDisplay);
}
	//while(1){	
			//ativaAgua();
//delayT0(100);
	//	atualizaDisplays(k);
	
		//delayT0(100);
		
//}
	}
	
void configuraAplicacao(){
defineIntervalo();
EA = 1;
ET1 = 1;
EX0 = 1;
segundosDisplay = valorResetaTimer;
iniciaCont50msT1();
}	
	
int defineIntervalo(){
		int inputUsuario;
	int tempoFinal;
		do{
			tempoFinal +=inputUsuario;
			tempoFinal *= 10;
			inputUsuario = identificaCaractere();
		}while(inputUsuario >= 0);
		valorResetaTimer = tempoFinal;
		return tempoFinal;
}	
	
	
int identificaCaractere(){
	
	
while(1){
	
	bitLinhaA=0;
	bitLinhaB=0;
	if(bitColuna1 == 0 ){
		return 1;
	} else if (bitColuna2 ==0){
		return 2;
	} else if(bitColuna3 ==0){
		return 3;
	}
	delayT0(65);
	
	bitLinhaA=1;
	bitLinhaB=0;
	if(bitColuna1 == 0 ){
		return 4;
	} else if (bitColuna2 ==0){
		return 5;
	} else if(bitColuna3 ==0){
		return 6;
	}
	
	delayT0(65);
	
	bitLinhaA=0;
	bitLinhaB=1;
	if(bitColuna1 == 0 ){
		return 7;
	} else if (bitColuna2 ==0){
		return 8;
	} else if(bitColuna3 ==0){
		return 9;
	}
	
	delayT0(65);
	
	bitLinhaA=1;
	bitLinhaB=1;
	if(bitColuna1 == 0 ){
		return -1;//*
	} else if (bitColuna2 ==0){
		return 0;
	} else if(bitColuna3 ==0){
		return -2;//#
	}
	delayT0(65);
}
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
			decodificaAlgorismo(numero%10);
			unidade = 0;
			delayT0(10);
			unidade = 1;
	
			//atualiza display da dezena
			decodificaAlgorismo(((int)(numero/10)%10));
			dezena = 0;
			delayT0(10);
			dezena = 1;
	
			//atualiza display da centena
			decodificaAlgorismo(((int)(numero/100)%10));
			centena = 0;
			delayT0(10);
			centena = 1;
	
			//atualiza display do milhar
			decodificaAlgorismo(((int)(numero/1000)%10));
			milhar = 0;
			delayT0(10);
			milhar = 1;
	
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

void decodificaAlgorismo(int numero){
	switch(numero){
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


