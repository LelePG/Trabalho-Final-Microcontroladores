# Trabalho-Final-Microcontroladores

## O que é este projeto?

Este é o trabalho final da disciplina de Microcontroladores ofertada em 2021/1 (semestre remoto) no curso de Engenharia de computação da Universidade Federal de Pelotas.
A proposta a ser desenvolvida neste projeto é um sistema que dispensa água em intervalos definidos pelo usuário, ou de acordo com o aperto de um botão utilizando o microcontrolador 8051.

## Recursos de Hardware utilizados no projeto

* [Microcontrolador 8051](https://pdf1.alldatasheet.com/datasheet-pdf/view/82390/ATMEL/AT89S52.html) (utilizado a disciplina);
* Display LCD 16X2;
* Barra de LEDs;
* Keypad 4X3;
* 

## Recursos de Software utilizados no projeto

* [Keil uVision](https://www.keil.com/c51/demo/eval/c51.htm)
* Simulador ISIS Proteus

## Instruções de utilização


## Pinos utilizados no 8051

 pino |P0 | P1 | P2 | P3
:------:|:---:|:----:|:----:|:---:
0| Coluna 1 - Keypad | A - display 7 segmentos | display LCD| en - LCD
1| Coluna 2 - Keypad | B - display 7 segmentos |display LCD| rs - LCD
2| Coluna 3 - Keypad | C - display 7 segmentos |display LCD| Interrupção de configuração
3| | D - display 7 segmentos |display LCD| Interrupção de dispenser imediato
4| | milhar - display 7 segmentos |display LCD|
5| | centena - display 7 segmentos |display LCD|
6| enable all LEDs| dezena - display 7 segmentos |display LCD| Bit A do decodificador - keypad
7| enable dos LEDs (também utilizado para ativar o motor)| unidade - display 7 segmentos |display LCD| Bit B do decodificador -keypad

## Links úteis





