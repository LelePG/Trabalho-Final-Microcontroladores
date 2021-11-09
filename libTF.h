int decodificaAlgorismo(int numero){
	int valoresBinarios[10] = {2,159,37,13,153,73,65,31,0,25};
	return valoresBinarios[numero];
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


void delayT0(int x){
	int i;
	for(i=0;i<x;i++){
		delay1ms(); // chama o delay de 1 ms x vezes, gerando um delay de xms
	}
	return;
}

void iniciaCont50msT1(){
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
	//e deixa o contador contando até estourar.
	return;
}

void desativaT1(){
	TR1 = 0; //para o contador
	TF1 = 0; //reseta a flag do overflow, ou na próxima iteração nem vamos entrar no laço.
}
