#include<stdio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

enum{triangle, circle, cross, square, L1, R1, L2, R2, start};
enum{MENU,jogando_1, jogando_2, Gameover, pause, comandos};


typedef struct{
    ALLEGRO_BITMAP *sprite;
    int x;
    int y;
    int widthheroi;
    int heightheroi;

}tPosicaoJogador;

typedef struct{
    float x;
    float y;
    float velX;
    float velY;
    int dirX;
    int dirY;

    int width;
    int height;

    ALLEGRO_BITMAP *image;

}Background;

int colisao(Background *i, tPosicaoJogador *h, Background * bg)
{
    if((h->x + h->widthheroi - 12) > i->x + 12 && h->x + 12 < (i->x + i->width - 12) && (h->y + h->heightheroi - 20) > i->y + 20 && h->y - 20 < (i->y + i->height + 20))
    {
        printf("COLIDIUUUUUUUUUUUUUU!!!!!!!!\n");

        al_destroy_bitmap(i->image);

        al_flip_display();
        i->image = al_load_bitmap("zombie_cheer2.png");
        ALLEGRO_BITMAP *ini = NULL;
        al_draw_bitmap(i->image, i->x, i->y, 0);
        al_flip_display();

        return 0;
    }

    return 1;
}


int main(){

    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_FONT *fonte_16 = NULL;
    ALLEGRO_FONT *fonte_22 = NULL;
    //INICIALIZANDO FUNÇÕES DO ALLEGRO
    al_init();
    al_install_keyboard();
    al_install_joystick();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_TIMER *timer = al_create_timer(1/60.0);
    ALLEGRO_DISPLAY *janela = al_create_display(800,600);
    ALLEGRO_JOYSTICK *Controle_1;
    ALLEGRO_JOYSTICK_STATE jst;
    ALLEGRO_EVENT_QUEUE *fila_eventos = al_create_event_queue();
    fonte = al_load_font("arial.ttf", 48, 0);
    fonte_16 = al_load_font("arial.ttf", 16, 0);
    fonte_22 = al_load_font("arial.ttf", 22, 0);
    //INICIANDO CONFIGURAÇÕES DO PLAYER
    tPosicaoJogador player;

    ALLEGRO_BITMAP *sprite, *sprite_2;
    sprite = al_load_bitmap("adventurer_walk1.png");
    sprite_2 = al_load_bitmap("adventurer_walk2.png");
    player.sprite = al_load_bitmap("adventurer_stand.png");
    player.widthheroi = al_get_bitmap_width(player.sprite);
    player.heightheroi = al_get_bitmap_height(player.sprite);

    //INICIANDO O BACGROUND
    ALLEGRO_BITMAP *bgImage = NULL;
    Background BG, BG_Menu;
    bgImage = al_load_bitmap("trees.png");
    BG.image = bgImage;
    BG_Menu.image = al_load_bitmap("fundoDoMenu.jpg");

    //INICIANDO INIMIGO
    Background inimigo;
    ALLEGRO_BITMAP *ini = NULL;
    ini = al_load_bitmap("zombie_stand.png");
    inimigo.image = ini;
    inimigo.x = 600;
    inimigo.y = 400;
    inimigo.width = al_get_bitmap_width(inimigo.image);

    //CONTORNO DOS PERSONAGENS
    al_convert_mask_to_alpha(player.sprite,al_map_rgb(255,255,255));
    al_convert_mask_to_alpha(inimigo.image,al_map_rgb(255,255,255));

    al_set_target_bitmap(al_get_backbuffer(janela));


    al_clear_to_color(al_map_rgb(255,0,0));

    al_flip_display();

    //EVENTOS E TEMPO NO JOGO
    al_register_event_source(fila_eventos,al_get_display_event_source(janela));
    al_register_event_source(fila_eventos,al_get_keyboard_event_source());
    al_register_event_source(fila_eventos,al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos,al_get_joystick_event_source());

    al_start_timer(timer);


    //VARIÁVEIS NECESSÁRIAS
    int contador = 0, cont = 0;
    int pulo = 0;
    int slide = 0;
    int cooldown = 200;
    int tempo = 0;
    int frequencia = 0;
    int STATE = MENU;
    int estado = 0;

    player.x = 200;
    player.y = 400;
    const int gravidade = 1;
    const int velPulo = 20;
    int velHorizontal = 4;
    int vely = 0;
    int velx = 0;
    int velzumbi = velHorizontal;

    int zumbi = 0;

    BG.x = 0;
    BG.y = 300;
    BG.width = al_get_bitmap_width(BG.image);

    //LOOP DO JOGO
    while(1){
        while(STATE == jogando_2){
            if(!(colisao(&inimigo, &player, &BG)) && !slide){
                al_rest(1);
                STATE = MENU;
                inimigo.x = -100;
                pulo = 1;
                slide = 0;
                tempo = 0;
                frequencia = 0;
                cooldown = 200;
                velHorizontal = 4;
                al_clear_to_color(al_map_rgb(0,0,0));
                al_flip_display();
                break;
            }
            if(!(colisao(&inimigo, &player, &BG)) && slide){
                inimigo.x = -100;
            }
            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(BG.image,BG.x,BG.y,0);

            if(BG.x + BG.width < 800){
                    puts("Coisou...");
                    al_draw_bitmap(BG.image,BG.x + BG.width,BG.y,0);

                    if(zumbi == 1)
                    {
                        inimigo.x -= velzumbi;
                        al_draw_bitmap(inimigo.image, inimigo.x, inimigo.y, 0);
                        al_convert_mask_to_alpha(inimigo.image,al_map_rgb(255,255,255));
                    }
                }
                if(BG.x + BG.width <= 0){
                    puts("Zerou...");
                    if(velHorizontal < 10)
                    velHorizontal += 1;
                    BG.x = 0;

                }

            ALLEGRO_EVENT evento;

            al_wait_for_event(fila_eventos,&evento);
            if(zumbi == 1)
            {
                inimigo.x -= velzumbi;
                al_draw_bitmap(inimigo.image, inimigo.x +15, inimigo.y, 0);
                al_convert_mask_to_alpha(inimigo.image,al_map_rgb(255,255,255));
            }
            if(evento.type == ALLEGRO_EVENT_TIMER){
                cont++;
                cooldown++;
                if(zumbi == 1)
                {
                    inimigo.x -= velzumbi;
                    al_draw_bitmap(inimigo.image, inimigo.x - 15, inimigo.y, 0);
                    al_convert_mask_to_alpha(inimigo.image,al_map_rgb(255,255,255));
                }

                BG.x -= velHorizontal;
                tempo++;
                if(slide){
                  frequencia++;
                  if(frequencia == 30){
                    frequencia = 0;
                    slide = 0;
                  }
                }
                if(!(slide) && contador == 0 && pulo && tempo % (60 / velHorizontal) == 0){
                    player.sprite = sprite;
                    contador = 2;
                }
                if(!(slide) && contador == 1 && pulo && tempo % (60 / velHorizontal) == 0){
                    player.sprite = sprite_2;
                    contador = 0;
                }
                if(contador == 2){
                    contador = 1;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(zumbi == 1)
                {
                    inimigo.x -= velzumbi;
                    al_draw_bitmap(inimigo.image, inimigo.x, inimigo.y, 0);
                    al_convert_mask_to_alpha(inimigo.image,al_map_rgb(255,255,255));
                }
                if(evento.keyboard.keycode == ALLEGRO_KEY_UP && pulo){
                    player.sprite = al_load_bitmap("adventurer_jump.png");
                    puts("Pressionou!");
                    vely = -velPulo;
                    pulo = 0;
                }
                if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN && cooldown >= 200){
                    player.sprite = al_load_bitmap("adventurer_slide.png");
                    slide = 1;
                    cooldown = 0;
                }
                if(evento.keyboard.keycode == ALLEGRO_KEY_1 && cont >= 100){
                    al_destroy_bitmap(inimigo.image);
                    inimigo.image = al_load_bitmap("zombie_stand.png");
                    inimigo.x = 800;
                    inimigo.y = 400;
                    zumbi = 1;
                    cont = 0;
                }
                if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    STATE = pause;
                    estado = 2;
                    continue;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN){
                    switch(evento.joystick.button){
                        case circle:
                        if(cooldown >= 200){
                        player.sprite = al_load_bitmap("adventurer_slide.png");
                        slide = 1;
                        cooldown = 0;
                        }
                        break;
                        case cross:
                            player.sprite = al_load_bitmap("adventurer_jump.png");
                            puts("Pressionou!");
                            vely = -velPulo;
                            pulo = 0;
                            break;
                        case start:
                            STATE = pause;
                            estado = 2;
                            break;
                    }
            }else if(evento.type == ALLEGRO_EVENT_JOYSTICK_AXIS){
                al_destroy_bitmap(inimigo.image);
                inimigo.image = al_load_bitmap("zombie_stand.png");
                inimigo.x = 800;
                inimigo.y = 400;
                zumbi = 1;
                cont = 0;
            }

            al_draw_bitmap(player.sprite,player.x,player.y,0);
            if(!pulo)
                vely += gravidade;
            else
            vely = 0;

            player.y += vely;
            player.x += velx;
            velx = 0;
            pulo = (player.y >= 400);
            al_flip_display();
        }
        while(STATE == jogando_1){
            if(!(colisao(&inimigo, &player, &BG)) && !slide){
                al_rest(1);
                STATE = MENU;
                inimigo.x = -100;
                pulo = 1;
                slide = 0;
                tempo = 0;
                frequencia = 0;
                cooldown = 200;
                velHorizontal = 4;
                al_clear_to_color(al_map_rgb(0,0,0));
                al_flip_display();
                break;
            }
            if(!(colisao(&inimigo, &player, &BG)) && slide){
                inimigo.x = -100;
            }
            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(BG.image,BG.x,BG.y,0);

            if(BG.x + BG.width < 800){
                    puts("Coisou...");
                    al_draw_bitmap(BG.image,BG.x + BG.width,BG.y,0);

                    if(zumbi == 1)
                    {
                        inimigo.x -= velzumbi;
                        al_draw_bitmap(inimigo.image, inimigo.x, inimigo.y, 0);
                        al_convert_mask_to_alpha(inimigo.image,al_map_rgb(255,255,255));

                    }
                }
                if(BG.x + BG.width <= 0){
                    puts("Zerou...");
                    if(velHorizontal < 10)
                    velHorizontal += 1;
                    BG.x = 0;

                }

            ALLEGRO_EVENT evento;

            al_wait_for_event(fila_eventos,&evento);
            if(zumbi == 1)
            {
                inimigo.x -= velzumbi;
                al_draw_bitmap(inimigo.image, inimigo.x +15, inimigo.y, 0);
                al_convert_mask_to_alpha(inimigo.image,al_map_rgb(255,255,255));
            }
            if(evento.type == ALLEGRO_EVENT_TIMER){
                cont++;
                if(cont%100 == 0){
                    al_destroy_bitmap(inimigo.image);
                    inimigo.image = al_load_bitmap("zombie_stand.png");
                    inimigo.x = 800;
                    inimigo.y = 400;
                    zumbi = 1;
                    cont = 0;
                }
                cooldown++;
                if(zumbi == 1)
                {
                    inimigo.x -= velzumbi;
                    al_draw_bitmap(inimigo.image, inimigo.x - 15, inimigo.y, 0);
                    al_convert_mask_to_alpha(inimigo.image,al_map_rgb(255,255,255));
                }

                BG.x -= velHorizontal;
                tempo++;
                if(slide){
                  frequencia++;
                  if(frequencia == 30){
                    frequencia = 0;
                    slide = 0;
                  }
                }
                if(!(slide) && contador == 0 && pulo && tempo % (60 / velHorizontal) == 0){
                    player.sprite = sprite;
                    contador = 2;
                }
                if(!(slide) && contador == 1 && pulo && tempo % (60 / velHorizontal) == 0){
                    player.sprite = sprite_2;
                    contador = 0;
                }
                if(contador == 2){
                    contador = 1;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(zumbi == 1)
                {
                    inimigo.x -= velzumbi;
                    al_draw_bitmap(inimigo.image, inimigo.x, inimigo.y, 0);
                    al_convert_mask_to_alpha(inimigo.image,al_map_rgb(255,255,255));
                }
                if(evento.keyboard.keycode == ALLEGRO_KEY_UP && pulo){
                    player.sprite = al_load_bitmap("adventurer_jump.png");
                    puts("Pressionou!");
                    vely = -velPulo;
                    pulo = 0;
                }
                if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN && cooldown >= 200){
                    player.sprite = al_load_bitmap("adventurer_slide.png");
                    slide = 1;
                    cooldown = 0;
                }
                if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    STATE = pause;
                    estado = 1;
                    continue;
                }
            }
            else if(evento.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN){
                    switch(evento.joystick.button){
                        case circle:
                        if(cooldown >= 200){
                        player.sprite = al_load_bitmap("adventurer_slide.png");
                        slide = 1;
                        cooldown = 0;
                        }
                        break;
                        case cross:
                            player.sprite = al_load_bitmap("adventurer_jump.png");
                            puts("Pressionou!");
                            vely = -velPulo;
                            pulo = 0;
                            break;
                        case start:
                            STATE = pause;
                            estado = 1;
                            break;
                    }
            }else if(evento.type == ALLEGRO_EVENT_JOYSTICK_AXIS){
                player.sprite = al_load_bitmap("adventurer_jump.png");
                puts("Pressionou!");
                vely = -velPulo;
                pulo = 0;
                break;
            }

            al_draw_bitmap(player.sprite,player.x,player.y,0);
            if(!pulo)
                vely += gravidade;
            else
            vely = 0;

            player.y += vely;
            player.x += velx;
            velx = 0;
            pulo = (player.y >= 400);
            al_flip_display();
        }

        while(STATE == MENU){
            al_draw_bitmap(BG_Menu.image, 0, 0, 0);
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 150, ALLEGRO_ALIGN_CENTER, "Comandos do menu:");
            al_draw_text(fonte_16, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTER,"Pressione [esc] para encerrar o jogo");
            al_draw_text(fonte_16, al_map_rgb(255, 255, 255), 400, 232, ALLEGRO_ALIGN_CENTER,"Pressione [Space] para jogar o no modo Single player");
            al_draw_text(fonte_16, al_map_rgb(255, 255, 255), 400, 264, ALLEGRO_ALIGN_CENTER,"Pressione [Enter] para jogar no modo Multiplayer");
            al_draw_text(fonte_16, al_map_rgb(255, 255, 255), 400, 296, ALLEGRO_ALIGN_CENTER,"Pressione [4] para ver a lsita de comandos");
            al_flip_display();
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos,&evento);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    STATE = Gameover;
                    break;
                }else if(evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
                    STATE = jogando_2;
                    break;
                }else if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){
                    STATE = jogando_1;
                    break;
                }else if(evento.keyboard.keycode == ALLEGRO_KEY_4){
                    STATE = comandos;
                    break;
                }
            }
        }
        while(STATE == comandos){
            al_draw_bitmap(BG_Menu.image, 0, 0, 0);
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 150, ALLEGRO_ALIGN_CENTER,"Controle:");
            al_draw_text(fonte_22, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTER,"JUMP: [X] SLIDE: [O] PAUSE: [SELECT] 2nd PLAYER: DPAD");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 400, 250, ALLEGRO_ALIGN_CENTER,"Teclado:");
            al_draw_text(fonte_22, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER,"JUMP: [UP] SLIDE: [DOWN] PAUSE: [ESC] 2nd PLAYER: [1]");
            al_draw_text(fonte_22, al_map_rgb(255, 255, 255), 400, 332, ALLEGRO_ALIGN_CENTER,"Pressione [esc] para voltar para o menu");
            al_flip_display();
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos,&evento);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    STATE = MENU;
                    break;
                }
            }
        }
        while(STATE == pause){
            al_draw_text(fonte, al_map_rgb(255, 0, 0), 400, 225, ALLEGRO_ALIGN_CENTER,"PRESSIONE [ESC]");
            al_draw_text(fonte, al_map_rgb(255, 0, 0), 400, 275, ALLEGRO_ALIGN_CENTER,"ou");
            al_draw_text(fonte, al_map_rgb(255, 0, 0), 400, 325, ALLEGRO_ALIGN_CENTER,"[SELECT] PARA RETOMAR O JOGO");
            al_flip_display();
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos,&evento);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    if(estado = 1){
                        STATE = jogando_1;
                    }else if(estado = 2){
                        STATE = jogando_2;
                    }
                }
            }
            if(evento.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN){
                if(evento.joystick.button == start){
                    if(estado = 1){
                        STATE = jogando_1;
                    }else if(estado = 2){
                        STATE = jogando_2;
                    }
                }
            }
        }

        if(STATE == Gameover){
        al_destroy_bitmap(bgImage);
        al_destroy_bitmap(inimigo.image);
        al_destroy_event_queue(fila_eventos);
        al_destroy_bitmap(player.sprite);
        al_destroy_display(janela);
        al_destroy_bitmap(BG_Menu.image);
        return 0;
        }
    }
}
