//Dados relativos ao display de 7 segmentos
//BCD
#define bitA P1_0
#define bitB P1_1
#define bitC P1_2
#define bitD P1_3
//Multiplexa??o
#define unidade P1_7
#define dezena P1_6
#define centena P1_5
#define milhar P1_4

void decodificaAlgorismo(int numero);
void atualizaDisplays(int numero);



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