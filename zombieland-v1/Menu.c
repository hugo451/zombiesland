#include "Menu.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include<stdio.h>

int esta_sobre_iniciar(ALLEGRO_EVENT evento){
    puts("Esta sobre iniciar...");
    if(evento.mouse.y > 230 && evento.mouse.y <= 290){
        return 1;
    }
    return 0;
}
int esta_sobre_opcoes(ALLEGRO_EVENT evento){
    puts("Esta sobre opcoes...");
    if(evento.mouse.y > 285 && evento.mouse.y <= 430){
        return 1;
    }
    return 0;
}

int esta_sobre_sair(ALLEGRO_EVENT evento){
    puts("Esta sobre sair...");
    if(evento.mouse.y > 540 && evento.mouse.y <= 585){
        return 1;
    }
    return 0;
}

void criar_menu(ALLEGRO_DISPLAY *janela,ALLEGRO_FONT *fonte,int altura, int largura){
    char *opcoes[] = {"Iniciar","Creditos","Sair"};
    int altura_ = altura/3;
    int i;
    for(i = 0; i  < 3 ; i++){
        al_draw_text(fonte,al_map_rgb(255,0,0),largura/2, altura_,ALLEGRO_ALIGN_CENTRE,opcoes[i]);
        altura_+=150;
    }

}

void criar_barra_de_selecao(ALLEGRO_DISPLAY *janela,ALLEGRO_BITMAP **seletor,int altura,int largura){
    *seletor = al_create_bitmap(200,50);
    al_set_target_bitmap(*seletor);
    al_clear_to_color(al_map_rgb(0,0,255));
    al_set_target_bitmap(al_get_backbuffer(janela));
}

