//Dados referentes ao LCS
#define LCD P2
#define EN P3_1
#define RS P3_0

void configLCD(void);	   //configuração inicial do LCS
void line1(void);		   //coloca o cursor na linha 1
void line2(void);		   // coloca o cursor na linha 2
void writeMSG(char msg[]); //escreve uma mensagem no display
void wrCMD(void);		   //escreve comando
void wrCHAR(void);		   //escreve caractere

void clearLCD();			//limpa o LCD
void mensagemInicial();		//imprime a mensagem inicial da aplicação (utilizada para definir o intervalo)
void mensagemAguaInicial(); //imprime mensagem de início de dispenser da água
void mensagemAguaFinal();	//imprime mensagem de fim de dispenser da água
void turnOnLCD();

void configLCD(void)
{
	LCD = 0x38;
	wrCMD();
	LCD = 0x06;
	wrCMD();
	turnOnLCD();
	clearLCD();
}

void line1(void)
{
	LCD = 0x00;
	wrCMD();
}

void line2(void)
{
	LCD = 0xC0;
	wrCMD();
}

void writeMSG(char msg[])
{
	unsigned char i;
	for (i = 0; i < 16 && msg[i] != '\0'; i++) //modificada para aceitar mensagens que sejam menores que 16
	{
		LCD = msg[i];
		wrCHAR();
	}
}

void wrCMD(void)
{
	RS = 0;
	EN = 1;
	delayT0(1);
	EN = 0;
	delayT0(1);
}

void wrCHAR(void)
{
	RS = 1;
	EN = 1;
	delayT0(5);
	EN = 0;
	delayT0(5);
}

void clearLCD()
{
	LCD = 0x01;
	wrCMD();
	return;
}

void mensagemInicial()
{
	clearLCD();
	line1();
	writeMSG("Qual o intervalo");
	line2();
	writeMSG("para tomar agua?");
	return;
}

void turnOnLCD(){
	LCD = 0x0C;
	wrCMD();
}

void mensagemAguaInicial()
{
	clearLCD();
	line1();
	writeMSG("Hora da agua!!!");
}

void mensagemAguaFinal()
{
	clearLCD();
	line1();
	writeMSG("Tome sua agua!!!");
	delayT0(1500);
	clearLCD();
}