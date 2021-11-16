# 👩‍💻 Trabalho-Final-Microcontroladores
<!-- adicionar um gif do proejto -->
## O que é este projeto?

Este é o trabalho final da disciplina de Microcontroladores ofertada em 2021/1 (semestre remoto) no curso de Engenharia de computação da Universidade Federal de Pelotas.
A proposta a ser desenvolvida neste projeto é um sistema que dispensa água em intervalos definidos pelo usuário, ou de acordo com o aperto de um botão utilizando o microcontrolador 8051.

## Como este projeto funciona?

## Instruções de utilização
Para utilizar este projeto, é preciso ter o simulador Proteus instalado na sua máquina. O software keil 

## Recursos de Software utilizados no projeto

* [Keil uVision](https://www.keil.com/c51/demo/eval/c51.htm)
* Simulador ISIS Proteus

## Recursos de Hardware utilizados no projeto

* [Microcontrolador 8051](https://pdf1.alldatasheet.com/datasheet-pdf/view/82390/ATMEL/AT89S52.html) (utilizado a disciplina);
* [Decodificador / Multiplexador CMOS 4555 1-4](https://www.ti.com/lit/ds/symlink/cd4555b.pdf?HQS=dis-mous-null-mousermode-dsf-pf-null-wwe&ts=1636865612936&ref_url=https%253A%252F%252Fbr.mouser.com%252F);
* [Display LCD 16X2 LM016L](https://www.datasheetarchive.com/pdf/download.php?id=cea14fe6a1c8d82c706c3cf01e69100cf1b7fe&type=O&term=LCD%2520LM016L%2520SPECIFICATIONS); 
* [Decodificador BCD para 4 segmentos](https://www.ti.com/lit/ds/symlink/cd74hc4511.pdf?ts=1636866635548&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FCD74HC4511%253Futm_source%253Dsupplyframe%2526utm_medium%253DSEP%2526utm_campaign%253Dnot_alldatasheet%2526DCM%253Dyes%2526dclid%253DCMLsyquLl_QCFZaRlQIdyeUC0Q);
* Componentes genéricos
    * Display de 7 segmentos de quatro dígitos;
    * Bar Graph com 10 LEDs;
    * Keypad 4X3;
    * Motor para simular a bomba d'água já que o simulador não tinha esse recurso;
    * Botões;
    * Capacitor eletrolítico;
    * Diodo;
    * Resistores;
    * Transistor PNP;
    * Decoder BCD 4 para 10;

## Pinos utilizados no 8051

 pino |P0 | P1 | P2 | P3
:------:|:---:|:----:|:----:|:---:
0| Coluna 1 - Keypad | A - display 7 segmentos | display LCD| en - LCD
1| Coluna 2 - Keypad | B - display 7 segmentos |display LCD| rs - LCD
2| Coluna 3 - Keypad | C - display 7 segmentos |display LCD| Interrupção de configuração
3| | D - display 7 segmentos |display LCD| Interrupção de dispenser imediato
4| buzzer | milhar - display 7 segmentos |display LCD|
5| bomba | centena - display 7 segmentos |display LCD|
6| enable all LEDs| dezena - display 7 segmentos |display LCD| Bit A do decodificador - keypad
7| enable dos LEDs| unidade - display 7 segmentos |display LCD| Bit B do decodificador -keypad

## Links úteis





