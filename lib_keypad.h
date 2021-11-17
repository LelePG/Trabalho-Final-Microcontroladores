//Dados relativos ao Keypad
// Pinos utilizados para ativar o decodificador (ativa as linhas)
#define linhaA P3_6
#define linhaB P3_7
//Pinos utilizados para fazer a leitura das colunas
#define coluna1 P0_0
#define coluna2 P0_1
#define coluna3 P0_2

int leColunas(int a, int b, int c); //Lê as colunas do keypad e retorna um valor correspondente
int identificaCaractere();			//identifica o caractere que foi pressionado no keypad

int leColunas(int a, int b, int c)
{
	if (coluna1)
	{
		return a;
	}
	else if (coluna2)
	{
		return b;
	}
	else if (coluna3)
	{
		return c;
	}
	return 99; //retorno que indica que nenhuma tecla foi pressionada
}

int identificaCaractere()
{
	int valorLido;
	while (1)
	{
		int delayTempo = 40; //tempo encontrado com base em testes

		linhaA = 0;
		linhaB = 0;

		valorLido = leColunas(1, 2, 3);
		if (valorLido != 99)
		{
			return valorLido;
		}

		delayT0(delayTempo);
		linhaA = 1;
		linhaB = 0;

		valorLido = leColunas(4, 5, 6);
		if (valorLido != 99)
		{
			return valorLido;
		}

		delayT0(delayTempo);
		linhaA = 0;
		linhaB = 1;

		valorLido = leColunas(7, 8, 9);
		if (valorLido != 99)
		{
			return valorLido;
		}

		delayT0(delayTempo);

		linhaA = 1;
		linhaB = 1;

		valorLido = leColunas(-5, 0, -10); // -5 = * e -10 = #
		if (valorLido != 99)
		{
			return valorLido;
		}

		delayT0(delayTempo);
	}
}