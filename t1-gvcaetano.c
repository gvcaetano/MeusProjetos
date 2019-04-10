//Aluno: Gabriel Vinicius Schmitt caetano
//Programa: Informa data e hora.

#include <time.h>
#include <stdio.h>

//Compensação do fuso e um ano antes para valores negativos
#define FUSO 31525200

// Definição dos dias da semana para o switch.
enum { qua, qui, sex, sab, dom, seg, ter };
int main()
{
  //Definição de variáveis.
  int anos, diasMes, diasAnos, dias, horas, minutos, segundos;
  long long int entrada, total;
  int jan=31, feb=jan+28, mar=feb+31, apr=mar+30, mai=apr+31, jun=mai+30;
  int jul=jun+31, aug=jul+31, sep=aug+30, oct=sep+31, nov=oct+30;
  printf("Digite um valor em segundos para ser convertido\n"
      "em uma data e hora ou 0 para data e hora atual:\n");
  scanf("%lld", &entrada);
  if (entrada) {
    total = entrada + FUSO;
  } else {
    total = time(0) + FUSO;
  }

  segundos = total % 60;       //Definição de horas, minutos, segundos, anos
  minutos = (total / 60) % 60; // e variáveis auxiliares.
  horas = (total / 3600) % 24;
  diasAnos = total / 86400;
  anos = diasAnos / 365 + 1969;

  switch (diasAnos % 7) { //Definição do dia da semana.
    case qui:
      printf("Quinta-feira, ");
      break;
    case sex:
      printf("Sexta-Feira, ");
      break;
    case sab:
      printf("Sábado, ");
      break;
    case dom:
      printf("Domingo, ");
      break;
    case seg:
      printf("Segunda-feira, ");
      break;
    case ter:
      printf("Terça-feira, ");
      break;
    case qua:
      printf("Quarta-Feira, ");
      break;
  }  

  //Correções para bissexto.
  diasMes = ((diasAnos % 365) - (anos - 1969) / 4);
  diasMes = diasMes + (((anos - 2001) / 100) - (anos - 2001) / 400);
  if (!(anos % 4) && (anos % 100) || !(anos % 400)) {
    feb++; mar++; apr++; mai++; jun++; jul++; aug++; sep++; oct++; nov++;
  }

  if (diasMes < 0) { //Correção da quantidade de dias e do ano na virada.
    if ((!(anos % 4) && (anos % 100)) || !(anos % 400)) {
      diasMes = diasMes + 366;
    } else {
      diasMes = diasMes + 365;
    }
    anos--;
  }  

  diasMes++; //definição de mês e dia.
  if (diasMes <= jan) {
    dias = diasMes;
    printf("%d de janeiro", dias);
  } else if (diasMes <= feb) {
    dias = diasMes - jan;
    printf("%d de fevereiro", dias);
  } else if (diasMes <= mar) {
    dias = diasMes - feb;
    printf("%d de março", dias);
  } else if (diasMes <= apr) {
    dias = diasMes - mar;
    printf("%d de abril", dias);
  } else if (diasMes <= mai) {
    dias = diasMes - apr;
    printf("%d de maio", dias);
  } else if (diasMes <= jun) {
    dias = diasMes - mai;
    printf("%d de junho", dias);
  } else if (diasMes <= jul) {
    dias = diasMes - jun;
    printf("%d de julho", dias);
  } else if (diasMes <= aug) {
    dias = diasMes - jul;
    printf("%d de agosto", dias);
  } else if (diasMes <= sep) {
    dias = diasMes - aug;
    printf("%d de setembro", dias);
  } else if (diasMes <= oct) {
    dias = diasMes - sep;
    printf("%d de outubro", dias);
  } else if (diasMes <= nov) {
    dias = diasMes - oct;
    printf("%d de novembro", dias);
  } else {
    dias = diasMes - nov;
    printf("%d de dezembro", dias);
  }

  //Printando resto da mensagem.
  printf(" de %d, %dh%dmin%ds\n", anos, horas, minutos, segundos);
  return 0;
}
