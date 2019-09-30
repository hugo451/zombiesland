#ifndef _Menu_H_
#define _Menu_H_
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*Nos arquivos headers, deixaremos os protótipos de função e
de variáveis globais.

*/
typedef struct{
    float x;
    float y;
}tPosicao_Seletor;



void criar_menu(ALLEGRO_DISPLAY *janela,ALLEGRO_FONT *fonte, int altura, int largura);

void criar_barra_de_selecao(ALLEGRO_DISPLAY *janela,ALLEGRO_BITMAP **seletor,int altura,int largura);

int esta_sobre_iniciar(ALLEGRO_EVENT evento);

int esta_sobre_opcoes(ALLEGRO_EVENT evento);

int esta_sobre_sair(ALLEGRO_EVENT evento);


#endif // _Menu_H_
