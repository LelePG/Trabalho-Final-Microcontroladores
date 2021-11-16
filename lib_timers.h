//Dados referentes ao timers 1 e 0
void delay1msT0();	 //delay de 1 ms utilzando o timer 0
void delayT0(int x); //delay de x milissegundos utilizando o Timer 0
void inicia50msT1(); // inicia a contagem de tempo de 50ms no Timer 1
void desativaT1();	 //para o contador T1

void delay1msT0()
{
	//Frequ�ncia do microcontrolador: f = 11.0592M
	//Periodo: 1/f = T =  90.4224n
	//Ciclo de m�quina = 12*T = 1.085u
	//Quantidade de contagens = (1ms) / (ciclo de m�quina) = 921.6 sendo que 1ms � o tempo que preciso contar
	//Valor inicial do timer = 65535 - 922 = 64613 (arrendodando 921.6)
	//Convertendo 64613 para bin�rio : 11111100 01100101
	//Separando os resultados: 11111100 -> mais significativa ->  252 -> TH0
	//1100101 -> menos significativo -> 101-> TL0
	TMOD = 1;  // coloca o contador no modo 1 (contador de 16 bits)
	TL0 = 101; // inicia parte menos significativa
	TH0 = 252; //inicia parte mais significativa
	TR0 = 1;   // inicia o contador
	while (TF0 != 1)
		;
	TR0 = 0; //para o contador
	TF0 = 0; //reseta a flag do overflow, ou na pr�xima itera��o nem vamos entrar no la�o.
	return;
}

void delayT0(int x)
{
	int i;
	for (i = 0; i < x; i++)
	{
		delay1msT0(); // chama o delay de 1 ms x vezes, gerando um delay de xms
	}
	return;
}

void inicia50msT1()
{
	//Frequ�ncia do microcontrolador: f = 11.0592M
	//Periodo: 1/f = T =  90.4224n
	//Ciclo de m�quina = 12*T = 1.085u
	//Quantidade de contagens = (50ms) / (ciclo de m�quina) = 46082.94
	//Valor inicial do timer = 65535 - 46083 = 19452 (arrendodando 46082.94)
	//Convertendo 19452 para bin�rio : 01001011 11111100
	//Separando os resultados: 01001011 -> mais significativa ->  75
	//11111100 -> menos significativo -> 252
	TMOD = 1;  // coloca o contador no modo 1 (contador de 16 bits)
	TL1 = 252; // inicia parte menos significativa
	TH1 = 75;  //inicia parte mais significativa
	TR1 = 1;   // inicia o contador
	//e deixa o contador contando at� estourar.
	return;
}

void desativaT1()
{
	TR1 = 0; //para o contador
	TF1 = 0; //reseta a flag do overflow, ou na pr�xima itera��o nem vamos entrar no la�o.
}
