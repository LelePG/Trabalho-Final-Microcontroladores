#define LCD			P2
#define EN			P3_1
#define RS			P3_0

void configLCD(void);
void line1(void);
void line2(void);
void writeMSG(char msg[]);
void wrCMD(void);
void wrCHAR(void);

void clearLCD();
void mensagemInicial();


void configLCD(void)
{
	LCD = 0x38;
	wrCMD();
	LCD = 0x06;
	wrCMD();
	LCD = 0x0E;
	wrCMD();
	LCD = 0x01;
	wrCMD();
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
	for(i = 0; i < 16 && msg[i] != '\0'; i++)
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

void clearLCD(){
	configLCD();
	return;
}

void mensagemInicial(){
	clearLCD();
	line1();
	writeMSG("Qual o intervalo");
	line2();
	writeMSG("para tomar agua?");
	return;
}

void mensagemAguaInicial(){
	clearLCD();
	line1();
	writeMSG("Hora da agua!!!");
}

void mensagemAguaFinal(){
	clearLCD();
	line1();
	writeMSG("Tome sua agua!!!");
	delayT0(2000);
	clearLCD();
}