#include<at89x52.h>
#include <funcoes.h>

#define bombaAgua P0_0
#define buzzer P0_1
#define dados7seg P2
#define unidade P1_7
#define dezena P1_6
#define centena P1_5
#define milhar P1_4


void ativaAgua(void);
int decodificaAlgorismo(int numero);
void atualizaDisplays(int numero);
void ativaContagemRegressiva(int numero);
void verificaSegundo();
void espera50ms();
void desativaContador();
void ativaPorInterrup(); 

int valorResetaContador = 251;

int segundoParcial;
int contador = 300;

void main(){
	EA = 1;
	ET1 = 1;
	EX0 = 1;
	espera50ms();
	//ativaContagemRegressiva(60); //segundos
	while(1){	
			//ativaAgua();
		atualizaDisplays(contador);
		delay(100);
	}
}

 //Rotina de ativar a água
void ativaAgua(void){
  bombaAgua = 0;
  //luz.setCode(1);
  buzzer = 1845;
  delay(1000);
  bombaAgua= 1;
	buzzer = 0;
	delay(10);
	
	
  //luz.setCode(6);
}




void atualizaDisplays(int numero){
			//atualiza display da unidade
			dados7seg = decodificaAlgorismo(numero%10);
			unidade = 1;
			delay(10);
			unidade = 0;
	
			//atualiza display da dezena
			dados7seg = decodificaAlgorismo(((int)(numero/10)%10));
			dezena = 1;
			delay(10);
			dezena = 0;
	
			//atualiza display da centena
			dados7seg = decodificaAlgorismo(((int)(numero/100)%10));
			centena = 1;
			delay(10);
			centena = 0;
	
			//atualiza display do milhar
			dados7seg = decodificaAlgorismo(((int)(numero/1000)%10));
			milhar = 1;
			delay(10);
			milhar = 0;
	
			return;
}



void espera50ms(){
	//Frequência do microcontrolador: f = 11.0592M
	//Periodo: 1/f = T =  90.4224n
	//Ciclo de máquina = 12*T = 1.085u
	//Quantidade de contagens = (50ms) / (ciclo de máquina) = 46082.94 
	//Valor inicial do timer = 65535 - 46083 = 19452 (arrendodando 46082.94)
	//Convertendo 19452 para binário : 01001011 11111100
	//Separando os resultados: 01001011 -> mais significativa ->  75
	//11111100 -> menos significativo -> 252
	TMOD = 1; // coloca o contador no modo 1 (contador de 16 bits)
	TL1 = 252; // inicia parte menos significativa
	TH1 = 75; //inicia parte mais significativa
	TR1=1; // inicia o contador
	//e deixa o contador livre.
	return;
}

void verificaSegundo() interrupt 3{
	void desativaContador();

	segundoParcial++;
	if (segundoParcial == 200){
		contador--;
		segundoParcial = 0;
	}
	espera50ms();
	
}

void desativaContador(){
	
	TR1 = 0; //para o contador
	TF1 = 0; //reseta a flag do overflow, ou na próxima iteração nem vamos entrar no laço.
	
}

