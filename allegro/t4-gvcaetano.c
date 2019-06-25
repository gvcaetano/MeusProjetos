//Aluno: Gabriel Vinicius Schmitt caetano
//Programa: Calculadora de polinômios
//
// para compilar este programa, use este comando:
// gcc -Wall -o t4-gvcaetano t4-gvcaetano.c tela.c -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro -lm




// o tamanho da tela, em pixels
#define L_TELA 1500
#define A_TELA  900

// tamanho do vetor de inimigos
#define QNT_MAX 3
// aceleracao da gravidade
#define XLR8 1.5
// posicao inicial
#define H_MAX 152

#include "tela.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



// estado das bolas
enum { INAT, ATIVO, CAIU };

// declaracao da struct bola para desenhar circulos
typedef struct {
  float x, y, vx, vy, r;
  int cor, borda, esta;
  double timer;
} bola;

// declaracao da struct caixa para desenhar retangulos
typedef struct {
  float xc, yc, l, h;
  int cor, borda;
} caixa;

typedef struct {
} fase;

// declaracao de funcoes em ordem alfabetica
void ativa_bola(int *ini_atv, bola inimigo[]);
bool click_dentro(caixa caixa);
void controla_barra(caixa *cursor);
void desenha_caveira(float x, float y);
void desenha_estrela(float x, float y);
void desenha_jogo(double inicio, caixa *caixa, bola inimigo[], int *vidas,
    int inimigos, int *pontos);
void desenha_menu_final(caixa msg, caixa bt_play, caixa bt_end, int pontos);
void desenha_menu_inicial(caixa msg, caixa bt_play);
void desenha_mouse(double x, double y);
void gerador_de_inimigos(bola inimigo[]);
void jogo(int *vidas, int *pontos, int *ini_atv);
void mecanica_principal( bola *inimigo, caixa *cursor, int *pontos,
    int *ini_atv, int *vidas);
bool menu_final(caixa msg, int *pts);
void menu_inicial(caixa msg);
void movimenta_bolas(bola *inimigo, caixa *cursor, int *pontos, int *ini_atv,
    int *vidas);
void pisca(bola *bola);
void rebate_na_borda(bola *obj);
void rebate_ou_morre(bola *bola, caixa *caixa, int *pontos, int *ini_atv,
    int *vidas);
void reset(int *pts, int *vidas, int *ini_atv, double *timer, bola inimigo[]);



int main(void)
{
  // inicio da estrutura que compoe todo o estado do jogo
  /*struct jogo {
    caixa raquete = {0, 0, 600, 30, azul, branco};
    bola inimigo[];
    double v_inicial;


  }*/
  // variaveis necessarias
  int vidas, pontos, ini_atv;
  bool play = true;
  
  //funcao leitura de arquivo
  int pontos_ranquing[10];
  char nomes_ranquing[31];
  FILE *ranquing;
  FILE *nomes;/*
  for (int i=0;i<10;i++) {
    fscanf(ranquing, "%d", &pontos_ranquing[i]);
  }
  for ()
*/
  caixa msg = {L_TELA/2, A_TELA/2, 700, 200, amarelo, branco};

  tela_inicio(L_TELA, A_TELA, "Trabalho 3 do Gabriel Caetano");
  menu_inicial(msg);
  while (play) {
    jogo(&vidas, &pontos, &ini_atv);
    play = menu_final(msg, &pontos);
  }
  tela_fim();
  return 0;
}

// ativa bolas que estiverem inativas e com o tempo certo
void ativa_bola(int *ini_atv, bola inimigo[])
{
  if (*ini_atv<QNT_MAX) {
    for (int i=0;i<QNT_MAX;i++) {
      bool esta_inativo = inimigo[i].esta == INAT;
      bool hora_de_ativar = inimigo[i].timer + 3 <= tela_relogio();
      if (esta_inativo && hora_de_ativar) {
        inimigo[i].esta  = ATIVO;
        inimigo[i].cor   = vermelho;
        inimigo[i].borda = branco;
        *ini_atv+=1;
        for (int j=0;j<QNT_MAX;j++) {
          if (inimigo[j].esta == INAT && j != i) {
            inimigo[j].timer = tela_relogio();
          }
        }
      }
    }
  }
}

// funcao para reconhecer click no botao
bool click_dentro(caixa caixa)
{
  float cursor_x, cursor_y;
  tela_cade_o_rato(&cursor_x, &cursor_y);
  if (cursor_x > caixa.xc - caixa.l / 2 &&
      cursor_x < caixa.xc + caixa.l / 2 &&
      cursor_y > caixa.yc - caixa.h / 2 &&
      cursor_y < caixa.yc + caixa.h / 2) {
    return true;
  } else {
    return false;
  }
}

// funcao que movimenta a plataforma controlada pelo mouse
void controla_barra(caixa *cursor)
{
  float mx, my;
  tela_cade_o_rato(&mx, &my);
  if (mx > cursor->l / 2 && mx < L_TELA - cursor->l / 2) {
    if (mx - cursor->xc)
    cursor->xc = mx;
  } else if(mx < cursor->l / 2) {
    cursor->xc = cursor->l / 2;
  } else {
    cursor->xc = L_TELA - cursor->l / 2;
  }
}

// desenha uma caveira na posicao x y
void desenha_caveira(float x, float y)
{
  tela_retangulo(x - 10, y, x + 10, y + 30, 0, preto, branco);
  tela_linha(x, y, x, y + 30, 0, preto);
  tela_linha(x - 5, y, x - 5, y + 30, 0, preto);
  tela_linha(x + 5, y, x + 5, y + 30, 0, preto);
  tela_circulo(x, y, 20, 0, branco, branco);
  tela_circulo(x-8.5, y, 6, 0, preto, preto);
  tela_circulo(x+8.5, y, 6, 0, preto, preto);
}

// desenha uma estrela na posicao x y
void desenha_estrela(float x, float y)
{
  tela_linha(x-20, y-10, x-5, y-10, 3, amarelo);
  tela_linha(x-5, y-10, x, y-25, 3, amarelo);
  tela_linha(x, y-25, x+5, y-10, 3, amarelo);
  tela_linha(x+5, y-10, x+20, y-10, 3, amarelo);
  tela_linha(x+20, y-10, x+10, y, 3, amarelo);
  tela_linha(x+10, y, x+15, y+15, 3, amarelo);
  tela_linha(x+15, y+15, x, y+5, 3, amarelo);
  tela_linha(x, y+5, x-15, y+15, 3, amarelo);
  tela_linha(x-15, y+15, x-10, y, 3, amarelo);
  tela_linha(x-10, y, x-20, y-10, 3, amarelo);
}

// funcao que desenha tela durante o jogo com todos os objetos
void desenha_jogo(double inicio, caixa *caixa, bola inimigo[], int *vidas,
    int inimigos, int *pontos)
{
  tela_inicia_desenho();
  tela_retangulo(caixa->xc - caixa->l / 2, caixa->yc - caixa->h / 2,
      caixa->xc + caixa->l / 2, caixa->yc + caixa->h / 2, 2, caixa->cor, 
      caixa->borda);
  char v[20], p[20], m[100];
  sprintf(v, "Vidas: %d", *vidas);
  tela_texto(60, 30, 26, branco, v);
  sprintf(p, "Pontos: %d", *pontos);
  tela_texto(L_TELA-80, 30, 26, branco, p);
  if (inicio + 4 > tela_relogio()) {
    sprintf(m, "Rebata as bolas para marcar pontos, se cair perde uma vida.");
    tela_texto(L_TELA/2, A_TELA/2, 36, branco, m);
  }
  for (int i=0;i<inimigos;i++) {
    tela_circulo(inimigo[i].x, inimigo[i].y, inimigo[i].r, 3, inimigo[i].borda,
        inimigo[i].cor);  
  }
  tela_termina_desenho();
}

// funcao que desenha a tela final
void desenha_menu_final(caixa msg, caixa bt_replay, caixa bt_end, int pontos)
{
  float x, y;
  tela_cade_o_rato(&x,&y);
  char msg_texto[50];
  sprintf(msg_texto, "Parabéns, você fez %d pontos!", pontos);
  char bt_play_fim[] = "Clique aqui para fechar!";
  char bt_play_de_novo[] = "Clique aqui para tentar novamente";
  tela_inicia_desenho();
  tela_retangulo(msg.xc - msg.l / 2, msg.yc - msg.h / 2,msg.xc + msg.l / 2,
      msg.yc + msg.h / 2 + 60, 0, msg.borda, msg.cor);
  tela_texto(msg.xc, msg.yc - 50, 30, preto, msg_texto);
  tela_retangulo(bt_replay.xc - bt_replay.l / 2, bt_replay.yc - bt_replay.h / 2,
      bt_replay.xc + bt_replay.l / 2, bt_replay.yc + bt_replay.h / 2, 2,
      bt_replay.borda, bt_replay.cor);
  tela_texto(bt_replay.xc, bt_replay.yc, 30, preto, bt_play_de_novo);
  tela_retangulo(bt_end.xc - bt_end.l / 2, bt_end.yc - bt_end.h / 2,
      bt_end.xc + bt_end.l / 2, bt_end.yc + bt_end.h / 2, 2, bt_end.borda,
      bt_end.cor);
  tela_texto(bt_end.xc, bt_end.yc, 30, preto, bt_play_fim);
  desenha_mouse(x, y);
  tela_termina_desenho();
}

// funcao que desenha a tela inicial
void desenha_menu_inicial(caixa msg, caixa bt_play)
{
  float x, y;
  tela_cade_o_rato(&x, &y);
  char msg_texto[] = "Bem vindo ao trabalho 3 do Gabriel Caetano";
  char bt_play_texto[] = "Clique aqui para começar!";
  tela_inicia_desenho();
  tela_retangulo(msg.xc - msg.l / 2, msg.yc - msg.h / 2, msg.xc + msg.l / 2,
      msg.yc + msg.h / 2, 2, msg.borda, msg.cor);
  tela_texto(msg.xc, msg.yc - 40, 28, preto, msg_texto);
  tela_retangulo(bt_play.xc - bt_play.l / 2, bt_play.yc - bt_play.h / 2,
      bt_play.xc + bt_play.l / 2, bt_play.yc + bt_play.h / 2, 2, bt_play.borda,
      bt_play.cor);
  tela_texto(bt_play.xc, bt_play.yc, 30, preto, bt_play_texto);
  desenha_mouse(x, y);
  desenha_caveira(x+50, y);
  desenha_estrela(x-50, y);
  tela_termina_desenho();
}

// funcao que desenha o mouse do jogo
void desenha_mouse(double x, double y)
{
  tela_linha(x, y, x + 30, y + 15, 4, azul);
  tela_linha(x, y, x + 15, y + 30, 4, azul);
  tela_linha(x + 30, y + 15, x + 15, y + 15, 4, azul);
  tela_linha(x + 15, y + 15, x + 15, y + 30, 4, azul);
}

// declaração dos valores iniciais das bolas
void gerador_de_inimigos(bola inimigo[])
{
  for (int i=0;i<QNT_MAX;i++) {
    inimigo[i].vx = rand() % 21 - 10;
    inimigo[i].vy = 0;
    inimigo[i].r = 20;
    inimigo[i].x = (rand() % (L_TELA - 40)) + 20;
    inimigo[i].y = A_TELA + 150;
    inimigo[i].cor = vermelho;
    inimigo[i].borda = branco;
    inimigo[i].esta = CAIU;
    inimigo[i].timer = tela_relogio();
  }
}

// funcao que executa a mecanica principal do jogo
void jogo(int *vidas, int *pontos, int *ini_atv)
{
  double timer = 0;
  bola inimigo[QNT_MAX];
  reset(pontos, vidas, ini_atv, &timer, inimigo);
  double inicio = tela_relogio();
  caixa cursor = {0, A_TELA - 30, 500, 30, azul, branco};
  while (*vidas) {
    controla_barra(&cursor);
    ativa_bola(ini_atv, inimigo);
    for (int i=0;i<QNT_MAX;i++) {
      mecanica_principal(&inimigo[i], &cursor, pontos, ini_atv, vidas);
    }
    desenha_jogo(inicio, &cursor, inimigo, vidas, QNT_MAX, pontos);
  }
}

// executa modificacoes principais no comportamento dos objetos do jogo
// como mudar estado e alterar posicao e velocidade conforme condicoes
void mecanica_principal( bola *inimigo, caixa *cursor, int *pontos,
    int *ini_atv, int *vidas)
{
  movimenta_bolas(inimigo, cursor, pontos, ini_atv, vidas);
  if (inimigo->esta == INAT) {
    pisca(inimigo);
  }
  if (inimigo->esta == CAIU && tela_relogio() - inimigo->timer >= 1.2) {
    inimigo->esta = INAT;
    inimigo->y = H_MAX;
    inimigo->vy = 0;
    inimigo->timer = tela_relogio();
  }
}

// funcao que executa menu final
bool menu_final(caixa msg, int *pts)
{
  caixa bt_replay = {L_TELA/2, A_TELA/2+77.5, 530, 45, branco, preto};
  caixa bt_end = {L_TELA/2, A_TELA/2+22.5, 420, 45, branco, preto};
  while (true) {
    desenha_menu_final(msg, bt_replay, bt_end, *pts);
    if (tela_rato_clicado()) {
      if(click_dentro(bt_end)) {
        return false;
      } else if (click_dentro(bt_replay)) {
        return true;  
      }  
    }
  }
}

// funcao que executa tela inicial do jogo
void menu_inicial(caixa msg)
{
  caixa bt_play={L_TELA / 2, A_TELA / 2 + 22.5, 420, 45, branco, preto};
  while (true) {
    desenha_menu_inicial(msg, bt_play);
    if (tela_rato_clicado() && click_dentro(bt_play)) {
      break;
    }
  }
}

// incrementa posicao, velocidade, e rebate ou mata bolas durante o jogo
void movimenta_bolas(bola *inimigo, caixa *cursor, int *pontos, int *ini_atv,
    int *vidas)
{
  if (inimigo->esta == ATIVO || inimigo->esta == CAIU) {
    rebate_na_borda(inimigo);
    inimigo->x += inimigo->vx;
    inimigo->y += inimigo->vy;
    inimigo->vy += XLR8;
    if (inimigo->esta == ATIVO) {
      rebate_ou_morre(inimigo, cursor, pontos, ini_atv, vidas);
    }
  }
}

// funcao para fazer bolas inativas piscarem
void pisca(bola *bola)
{
  if ((int)(tela_relogio() * 2) % 2 != 0) {
    bola->borda = branco;
    bola->cor = vermelho;
  } else {
    bola->borda = transparente;
    bola->cor = transparente;
  }
}

// funcao para rebater bolas nas laterais
void rebate_na_borda(bola *obj)
{
  if (obj->x < obj->r || obj->x > L_TELA-obj->r) {
    obj->vx *= -1;
  }
  if (obj->y < obj->r) {
    obj->vy *= -1;
  }
}

// funcao para rebater ou eliminar bolas do jogo
void rebate_ou_morre(bola *bola, caixa *caixa, int *pontos, int *ini_atv,
    int *vidas) 
{
  double v_inicial = -45;
  bool limite_inferior = bola->y + bola->r > caixa->yc - caixa->h / 2;
  bool dentro_da_raquete = (bola->x + bola->r > caixa->xc - caixa->l / 2 &&
       bola->x - bola->r < caixa->xc + caixa->l / 2);
  if (limite_inferior && dentro_da_raquete) {
    bola->vy = v_inicial;
    *pontos += 10;
    if (bola->vx < 10 && bola->vx > -10) {
      bola->vx += (bola->vx + (bola->x - caixa->xc)) / (caixa->l / 75);
    }
  } else if (limite_inferior) {
    bola->esta = CAIU;
    bola->timer = tela_relogio();
    *ini_atv -= 1;
    *vidas -= 1;
  }
}

// gera todos os valores iniciais para o inicio e reinicio do jogo
void reset(int *pts, int *vidas, int *ini_atv, double *timer, bola inimigo[])
{
  *pts = 0;
  *vidas = 5;
  *ini_atv = 0;
  *timer = 0;
  gerador_de_inimigos(inimigo);
}