//Aluno: Gabriel Vinicius Schmitt caetano
//Programa: Calculadora de polinômios

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Definição para o switch do menu.
enum { SAIR, ENTRA_A, ENTRA_B, TROCA, SOMA, SUBT, MULT, DIVI, CALC };

//Declaração de funções em ordem alfabética.
void calcula(double vet[]);
void divide(double vetorA[], double vetorB[], double vetorC[], double vetorD[]);
void escreve(double vet[]);
void iguala(double a[], double b[]);
void menu(double vetorA[], double vetorB[], double vetorC[], double vetorD[]);
void multiplica(double a[], double b[], double c[]);
void mult_parte(double vet[], double coef, int exp, double mult[100]);
void normaliza(double vet[]);
void recebe(double vet[]);
void soma(double a[], double b[], double c[]);
void subtracao(double a[], double b[], double c[]);
void troca(double a[], double b[]);

int main()
{
  double polinomioA[100], polinomioB[100], polinomioC[100], polinomioD[100];
  menu(polinomioA,polinomioB,polinomioC,polinomioD);
  system("reset|cls");
  printf("Obrigado e volte sempre!\n\n");
  return 0;
}

void calcula(double vet[100])
{
  int i, grau = vet[0], partes = grau + 1;
  double x, soma, termo;
  printf("Digite um valor para x: ");
  scanf("%lf", &x);
  for (i=1;i<=partes;i++) {
    termo = vet[i] * pow(x,partes-i);
    soma += termo;
  }
  printf("O resultado do polinômio é %.0lf.\n\n", soma);
}

void divide(double vetorA[], double vetorB[], double vetorC[], double vetorD[])
{
  int prtd, prta, expo, i, grb=vetorB[0], gra=vetorA[0], grd;
  double result[100], resto[100];
  if (vetorB[0] > vetorA[0]) {
    printf("Não é divisível.\nValores não foram alterados.\n");
  } else {
    for (i=0;i<100;i++) {
      vetorD[i] = 0;
      vetorC[i] = 0;
      result[i] = 0;
      resto[i] = 0;
    }
    vetorD[0] = gra - grb;
    i=1;
    while (gra>=grb) {
      expo = gra - grb;
      result[1] = vetorA[1] / vetorB[1];
      vetorD[i] = result[1];
      mult_parte(vetorB, result[1], expo, vetorC);
      subtracao(vetorA, vetorC, resto);
      i++;
      normaliza(vetorA);
      gra = vetorA[0];
    }
    prta = gra+1;
    for(i=0;i<=prta;i++) {
      vetorB[i] = vetorA[i];
    }
    grd = vetorD[0];
    prtd = grd + 1;
    for (i=0;i<=prtd;i++) {
      vetorA[i] = vetorD[i];
    }
    normaliza(vetorB);
    printf("\nO quociente dos polinômios A e B é: ");
    escreve(vetorA);
    printf("E o resto da divisão é:");
    escreve(vetorB);
    printf("\n");
  }
}

void escreve(double vet[100])
{
  int i, grau = vet[0], partes = grau + 1;
  if (vet[0]==0) {
    printf("%.0lf\n", vet[1]);
  } else {
    for (i=grau;i>1;i--) {
     printf("%.4lfx^%d + ", vet[partes - i], i);
    }
    printf("%.4lfx + %.4lf\n",vet[grau], vet[partes]);
  }
}

void iguala(double a[], double b[])
{
  int i, partes;
  while (a[0] != b[0]) {
    if (a[0] > b[0]) {
      b[0]++;
      partes = b[0]+1;
      for (i=partes;i>0;i--) {
        b[i] = b[i-1];
      }
      b[1] = 0;
    } else {
      a[0]++;
      partes = a[0]+1;
      for (i=partes;i>0;i--) {
        a[i] = a[i-1];
      }
      a[1] = 0;
    }
  }
}

void menu(double vetorA[], double vetorB[], double vetorC[], double vetorD[])
{
  int opcao;
  vetorA[0] = 0;
  vetorB[0] = 0;
  vetorC[0] = 0;
  vetorD[0] = 0;
  system("reset||cls");
  printf("Bem vindo.\n\n");
  do {
    printf("Polinômio A: ");
    escreve(vetorA);
    printf("Polinômio B: ");
    escreve(vetorB);
    printf("\nPara prosseguir selecione uma das opções abaixo digitando o nume"
        "ro\ncorrespondente.\n\n1 - Inserir polinômio A;\n2 - Inserir polinômi"
        "o B;\n3 - Trocar polinômios de posição;\n4 - Soma dos polinômios;\n5 "
        "- Subtração dos polinômios (A - B);\n6 - Multiplicação dos polinômios"
        ";\n7 - Divisão dos polinômios (A / B);\n8 - Cálculo do polinômio A (a"
        " partir de um valor de x);\n0 - Encerrar programa.\n\n");
    scanf("%d", &opcao);
    switch(opcao) {
      case SAIR:
        break;
      case ENTRA_A:
        recebe(vetorA);
        break;
      case ENTRA_B:
        recebe(vetorB);
        break;
      case TROCA:
        troca(vetorA,vetorB);
        break;
      case SOMA:
        soma(vetorA,vetorB,vetorC);
        printf("\nA soma dos polinômios A e B é: ");
        escreve(vetorA);
        printf("\n");
        break;
      case SUBT:
        subtracao(vetorA,vetorB,vetorC);
        printf("\nA soma dos polinômios A e B é: ");
        escreve(vetorA);
        printf("\n");
        break;
      case MULT:
        multiplica(vetorA,vetorB,vetorC);
        printf("\nO produto dos polinômios A e B é: ");
        escreve(vetorA);
        printf("\n");
        break;
      case DIVI:
        divide(vetorA,vetorB,vetorC,vetorD);
        break;
      case CALC:
        calcula(vetorA);
        break;
    }
  } while (opcao != SAIR);
}

void multiplica(double vetA[], double vetB[], double vetC[])
{
  int i, grau = vetB[0], partes = grau + 1;
  double mult_aux[100], mult[100];
  for (i=0;i<100;i++) {
    mult[i]=0;
  }
  for (i=1;i<=partes;i++) {
    mult_parte(vetA, vetB[i], partes-i, mult_aux);
    iguala(mult_aux, mult);
    soma(mult, mult_aux, vetC);
  }
  if (mult[0]>98) {
    printf("O produto destes polinômios não coube no vetor e não pode ser "
        "representado.\nValores não foram alterados.\n");
  } else {
    iguala(mult,vetA);
    partes = mult[0]+1;
    for (i=0;i<=partes;i++) {
      vetA[i] = mult[i];
    }
    normaliza(vetA);
  }
}

void mult_parte(double vet[], double coef, int exp, double mult[100])
{
  int i, grau = vet[0], partes = grau + 1;
  for (i=1;i<=partes;i++) {
    mult[i] = vet[i] * coef;
  }
  mult[0] = grau + exp;
}

void normaliza(double vet[100])
{
  int i, termos = vet[0]+1;
  while (vet[1] == 0 && vet[0] != 0) {
    vet[0]--;
    for (i=1;i<=termos;i++) {
      vet[i] = vet[i+1];
    }
  }
}

void recebe(double vet[100])
{  
  int i, partes;
  printf("Digite o grau do polinômio:\n");
  scanf("%lf", &vet[0]);
  while (vet[0] < 0 || vet[0] > 98) {
    printf("Grau do polinômio inválido, tente novamente (0-98).\n");
    scanf("%lf", &vet[0]);
  }
  partes = vet[0] + 1;
  printf("Digite os coeficientes do polinômio começando pelo de maior grau "
      "e decrescendo:\n");
  for (i=1;i<=partes;i++) {
    scanf("%lf", &vet[i]);
  }
  normaliza(vet);
  printf("O polinômio inserido foi: ");
  escreve(vet);
  printf("\n");
}

void soma(double a[], double b[], double c[])
{
  int i, partes;
  iguala(a, b);
  partes = a[0]+1;
  c[0] = a[0];
  for (i=1;i<=partes;i++) {
    c[i] = a[i] + b[i];
  }
  for (i=0;i<=partes;i++) {
    a[i] = c[i];
  }
  normaliza(a);
  normaliza(b);
  normaliza(c);
}

void subtracao(double a[], double b[], double c[])
{
  int i, partes;
  iguala(a, b);
  partes = a[0]+1;
  c[0] = a[0];
  for (i=1;i<=partes;i++) {
    c[i] = a[i] - b[i];
  }
  for (i=0;i<=partes;i++) {
    a[i] = c[i];
  }
  normaliza(a);
  normaliza(b);
  normaliza(c);
}

void troca(double a[100], double b[100])
{
  double aux[100];
  iguala(a,b);
  int i, partes = a[0]+1;
  normaliza(a);
  normaliza(b);
  for (i=0;i<=partes;i++) {
    aux[i] = a[i];
    a[i] = b[i];
    b[i] = aux[i];
  }
  printf("O polinomio A agora é: ");
  escreve(a);
  printf("\nE o polinômio B é: ");
  escreve(b);
  printf("\n");
}