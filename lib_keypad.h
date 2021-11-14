//Dados relativos ao Keypad
#define bitLinhaA P3_6
#define bitLinhaB P3_7

#define bitColuna1 P0_0
#define bitColuna2 P0_1
#define bitColuna3 P0_2


int leColunas(int a, int b, int c){
	
	if (bitColuna1 )
		{
			return a;
		}
		else if (bitColuna2)
		{
			return b;
		}
		else if (bitColuna3)
		{
			return c;
		}
		
		return 99;
	
}

int identificaCaractere()
{
int valorLido;
	while (1)
	{
		int delayTempo = 30;

		bitLinhaA = 0;
		bitLinhaB = 0;
	
		valorLido = leColunas(1,2,3);
		if(valorLido!=99){
			return valorLido;
		}
		
		
		delayT0(delayTempo);
		bitLinhaA = 1;
		bitLinhaB = 0;

		
		valorLido = leColunas(4,5,6);
		if(valorLido!=99){
			return valorLido;
		}

		delayT0(delayTempo);
		bitLinhaA = 0;
		bitLinhaB = 1;

		
		valorLido = leColunas(7,8,9);
		if(valorLido!=99){
			return valorLido;
		}
		
		delayT0(delayTempo);

		bitLinhaA = 1;
		bitLinhaB = 1;

		
		valorLido = leColunas(-5,0,-10); // -5 = * e -10 = #
		if(valorLido!=99){
			return valorLido;
		}
		
		delayT0(delayTempo);
	}
}