void delay(int x);
void delay1ms();


int decodificaAlgorismo(int numero){
	int valoresBinarios[10] = {2,159,37,13,153,73,65,31,0,25};
	return valoresBinarios[numero];
}

void delay(int x){
	int i;
	for(i=0;i<x;i++){
		delay1ms(); // chama o delay de 1 ms x vezes, gerando um delay de xms
	}
	return;
}


void delay1ms(){
	//Frequência do microcontrolador: f = 11.0592M
	//Periodo: 1/f = T =  90.4224n
	//Ciclo de máquina = 12*T = 1.085u
	//Quantidade de contagens = (1ms) / (ciclo de máquina) = 921.6 sendo que 1ms é o tempo que preciso contar
	//Valor inicial do timer = 65535 - 922 = 64613 (arrendodando 921.6)
	//Convertendo 64613 para binário : 11111100 01100101
	//Separando os resultados: 11111100 -> mais significativa ->  252 -> TH0
	//1100101 -> menos significativo -> 101-> TL0 
	TMOD = 1; // coloca o contador no modo 1 (contador de 16 bits)
	TL0 = 101; // inicia parte menos significativa
	TH0 = 252; //inicia parte mais significativa
	TR0=1; // inicia o contador
	do{
		//loop que não faz nada, apenas espera o overflow do contador
	}while(TF0!= 1);
	TR0 = 0; //para o contador
	TF0 = 0; //reseta a flag do overflow, ou na próxima iteração nem vamos entrar no laço.
	return;
}