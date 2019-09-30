#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
//Biblioteca criada
#include "Menu.h"

//Definições
#define LARGURA 800
#define ALTURA 600


void mensagem_erro(char *texto_erro){//Funçao que exibe mensagens de erro
    al_show_native_message_box(NULL,"ERRO FATAL",texto_erro,NULL,NULL,ALLEGRO_MESSAGEBOX_ERROR);
}



typedef struct{//Estrutura que guarda informações do jogador (posteriormente, podemos substituir por alguma estrutura da biblioteca dos personagens)
    ALLEGRO_BITMAP *sprite;
    int x;
    int y;
    int widthheroi;
    int heightheroi;
    int pontuacao;
}tPosicaoJogador;

typedef struct{
    float x;
    float y;

    int width;
    int height;

    ALLEGRO_BITMAP *image;

}Background;//Estrutura do background (devemos mudar esse nome, já que ela também é usada para os inimigos)

int colisao(Background *i, tPosicaoJogador *h, Background * bg,ALLEGRO_FONT *fonte)
{
    if((h->x + h->widthheroi) > i->x && h->x < (i->x + i->width) && (h->y + h->heightheroi) > i->y && h->y < (i->y + i->height))
    {
        printf("COLIDIUUUUUUUUUUUUUU!!!!!!!!\n");

        al_destroy_bitmap(i->image);


        ALLEGRO_BITMAP *ini = NULL;
        i->image = al_load_bitmap("zombie_cheer2.png");
        al_draw_bitmap(i->image, i->x, i->y, 0);
        al_draw_text(fonte,al_map_rgb(255,0,0),LARGURA/2-70,ALTURA/2,NULL,"FIM DE JOGO");

        al_flip_display();
        al_clear_to_color(al_map_rgb(255,255,255));
        //al_rest(3);

        return 0;
    }

    return 1;
}


int main()
{
    //As duas linhas a seguir declaram e inicializam flags referentes ao estado atual da tela do jogo
    int esta_no_menu = 1;
    int esta_no_gameplay = 0;
    if(!al_init()){//Inicializa o allegro
        mensagem_erro("Erro ao inicializar o allegro.");
        return -1;
    }
    if(!al_init_image_addon()){//Habilita as funcionalidades relacionadas a manipulação de imagens
        mensagem_erro("Erro ao carregar addon de imagens");
        return -1;
    }
    if(!al_install_keyboard()){//Instala o teclado
        mensagem_erro("Erro ao inializar teclado.");
        return -1;
    }
    if(!al_install_mouse()){//Instala o mouse
        mensagem_erro("Erro ao instalar o mouse.");
        return -1;
    }



    al_init_font_addon();//Habilita o uso de funcionalidades relacionadas a fontes de texto

    if(!al_init_ttf_addon()){
        mensagem_erro("Erro ao iniciar fonte(texto)");
        return -1;
    }

    //al_set_new_display_flags(ALLEGRO_FULLSCREEN); //Habilita a tela cheia
    ALLEGRO_DISPLAY *janela = NULL;//Estrutura que representa a tela do jogo
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;//Fila de eventos, que recebe eventos da tela, teclado, mouse, etc...
    //ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_TIMER *timer = al_create_timer(1/60.0);//Cria inicializa um temporizador com frequência de 60 Hz.
    ALLEGRO_FONT *fonte = al_load_font("fontes/darkdominion.ttf",42,0);//Cria uma estrutura de fonte e, nela, carrega uma fonte de texto.
    ALLEGRO_BITMAP *bgImage = NULL;//Bitmap que guardará a imagem de fundo.
    ALLEGRO_BITMAP *sprite, *sprite_2;//Sprites que serão atribuidos ao personagem
    tPosicaoJogador player;//Cria uma variavel do tipo tPosicaoJogador, que irá guardar os dados do jogador.
    sprite = al_load_bitmap("adventurer_walk1.png");
    sprite_2 = al_load_bitmap("adventurer_walk2.png");
    player.sprite = al_load_bitmap("adventurer_stand.png");//Atribui uma imagem ao sprite do jogador.
    //Dimensoes do heroi
    player.widthheroi = al_get_bitmap_width(player.sprite);
    player.heightheroi = al_get_bitmap_height(player.sprite);
    ALLEGRO_BITMAP *fundo_do_menu = al_load_bitmap("fundoDoMenu.bmp");

    Background BG, BG_2;
    //Inimigo
    Background inimigo;
    ALLEGRO_BITMAP *ini = NULL;
    ini = al_load_bitmap("zombie_stand.png");
    inimigo.image = ini;
    inimigo.x = 600;
    inimigo.y = 400;
    inimigo.width = al_get_bitmap_width(inimigo.image);



    bgImage = al_load_bitmap("backnew/back1.png");

    BG.image = bgImage;

    //al_convert_mask_to_alpha(player.sprite,al_map_rgb(255,255,255));//Remove o fundo branco do sprite do personagem

    al_set_target_bitmap(al_get_backbuffer(janela));//Muda o bitmap padrão para o backbuffer do display.


    janela = al_create_display(LARGURA,ALTURA);//Cria uma tela, na variável janela.

    if(!janela){
        mensagem_erro("Erro ao criar a janela.");
        al_destroy_display(janela);
        return -1;
    }

    if(!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){//Muda o tipo do cursor do mouse.
        mensagem_erro("Erro ao definir o cursor do mouse.");
        return -1;
    }

    //fonte = al_load_font("fontes/CAPTKD__.ttf",42,0);

    if(!fonte){
        mensagem_erro("Erro ao carregar fonte(texto).");
        al_destroy_display(janela);
        return -1;
    }


    fila_eventos = al_create_event_queue();//Cria uma fila de eventos e atribui à variável fila_eventos.

    al_register_event_source(fila_eventos, al_get_keyboard_event_source());//Mandando a fonte de eventos do teclado para a fila de eventos.
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));//Mandando a fonte de eventos da tela para a fila de eventos.
    al_register_event_source(fila_eventos, al_get_mouse_event_source());//Mandando a fonte de eventos do mouse para a fila de eventos.
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));//Mandando a fonte de eventos do temporizador para a fila de eventos.

    al_start_timer(timer);//Inicializa a contagem no temporizador.


    al_clear_to_color(al_map_rgb(86,201,50));//Colore a tela

    //al_draw_text(fonte,al_map_rgb(255,0,0),LARGURA/2,ALTURA/2,ALLEGRO_ALIGN_CENTRE,"Ola mundo!");

    ALLEGRO_BITMAP *seletor = NULL;//Cria um bitmap vazio que será o seletor das opções no menu.
    tPosicao_Seletor posicaoSeletor;//Estrutura que guardará a posição do seletor.
    //As próximas duas linhas definem a posição inicial do seletor.
    posicaoSeletor.x = LARGURA/2-130;
    const int posicaoSuperiorSeletor = posicaoSeletor.y = ALTURA/3-100;
    const int posicaoInferiorSeletor = posicaoSuperiorSeletor+300;
    //A função abaixo cria um seletor, e manda-o para a variável seletor.
    seletor = al_load_bitmap("blood.png");
    //criar_barra_de_selecao(janela,&seletor,ALTURA/3,LARGURA);
    //A função abaixo desenha o menu na tela.
    criar_menu(janela,fonte,ALTURA,LARGURA);
    al_flip_display();//Atualiza a tela.

    int contador = 0,cont;//contadores.
    int pulo = 0;//flag de pulo.
    int slide = 0;//flag...
    int tempo = 0;
    int frequencia = 0;

    //As duas linhas abaixo definem a posição inicial do jogador.
    player.x = 300;
    player.y = 400;
    const int gravidade = 1;//Valor da gravidade.
    const int velPulo = 20;//Velocidade do pulo.
    int velHorizontal = 2;
    int vely = 0;
    int velx = 0;
    int velzumbi = 5;

    int zumbi = 0;

    //As duas linhas abaixo determinam a posição inicial do background.
    BG.x = 0;
    BG.y = 0;
    //Pega a largura do background e manda para o campo width, da variável BG.
    BG.width = al_get_bitmap_width(BG.image);
    player.pontuacao = 0;//Inicializa a pontuação do jogador com zero.
    //criar_barra_de_selecao(janela,seletor,posicaoSeletor.y,LARGURA);
    player.pontuacao = 0;//Inicia a pontuação com zero
    int melhor_pontuacao = 0;//Inicia a melhor pontuação com zero (posteriormente, podemos substituir isso pela leitura de um arquivo que guarde a melhor pontuação)
    int esta_nos_creditos = 0;
    int escolha = 1;
    while(1){//Loop princiapal (aqui é onde o jogo como um todo ocorre)
        while(esta_no_menu){//Loop do menu
            al_clear_to_color(al_map_rgb(255,255,255));
            //al_draw_scaled_bitmap(fundo_do_menu,0,0,al_get_bitmap_width(fundo_do_menu),al_get_bitmap_height(fundo_do_menu),0,0,800,600,0);
            al_draw_scaled_bitmap(fundo_do_menu,0,0,al_get_bitmap_width(fundo_do_menu),al_get_bitmap_height(fundo_do_menu),0,0,800,600,0);
            //al_draw_bitmap(seletor,posicaoSeletor.x,posicaoSeletor.y,0);
            al_draw_scaled_bitmap(seletor,0,0,al_get_bitmap_width(seletor),al_get_bitmap_height(seletor),posicaoSeletor.x,posicaoSeletor.y,250,250,0);//Desenha o seletor
            criar_menu(janela,fonte,ALTURA,LARGURA);//Cria e desenha o menu.
            ALLEGRO_EVENT evento;//Variável que receberá os eventos da fila de eventos.

            al_wait_for_event(fila_eventos,&evento);//Esperando pela chegada dos eventos.

            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){//Se o evento for do tipo fechar a janela.
                int resposta = al_show_native_message_box(janela,"Sair do Jogo","Tem certeza?","Deseja sair do jogo?",NULL,ALLEGRO_MESSAGEBOX_YES_NO);

                if(resposta){
                    puts("Encerrando jogo...");
                    goto GAME_OVER;//Vá para o fim do jogo (fora do loop principal)
                }

            }else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){//Se o evento detectou que uma tecla foi pressionada
                if(evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
                    puts("ENTER");
                    if(escolha == 3){//Se estiver sobre o label "sair"
                        //A linha abaixo exibe uma janela com duas opções, sim ou não, que retorna o valor 1->sim ou 0->não. E este valor é guardado na variável resposta.
                        int resposta = al_show_native_message_box(janela,"Sair do Jogo","Tem certeza?","Deseja sair do jogo?",NULL,ALLEGRO_MESSAGEBOX_YES_NO);

                        if(resposta){//Se resposta for diferente de 0.
                            puts("Encerrando jogo...");
                            goto GAME_OVER;//Vá para fora do loop principal.
                        }
                    }else if(escolha == 1){//Se estiver sobre o label "iniciar".
                        esta_no_menu = 0;//Desabilita a flag do menu.
                        esta_no_gameplay = 1;//Habilita a flag do gameplay.


                    }else if(escolha == 2){
                        esta_nos_creditos = 1;
                        //al_clear_to_color(al_map_rgb(255,255,255));
                        esta_no_gameplay = esta_no_menu = 0;
                    }
                }
                else if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN){//Se o código da tecla pressionada for a seta para baixo
                    if(posicaoSeletor.y < posicaoInferiorSeletor){//Se o seletor não estiver na parte mais inferior possível.
                        escolha++;
                        posicaoSeletor.y+=150;//Move o seletor para baixo.
                    }else{//Se ele já estiver na posição mais inferior possível.
                        escolha = 1;
                        posicaoSeletor.y = posicaoSuperiorSeletor;//Volte para a posição mais superior.
                    }
                }else if(evento.keyboard.keycode == ALLEGRO_KEY_UP){//Se a tecla pressionada foi a tecla para cima.
                    if(posicaoSeletor.y > posicaoSuperiorSeletor){//Se ele ainda não estiver na posição mais superior.
                        escolha--;
                        posicaoSeletor.y-=150;//Move o seletor para cima.
                    }else{//Se ele já estiver na posição mais superior.
                        escolha = 3;
                        posicaoSeletor.y = posicaoInferiorSeletor;//Volta para a posição mais inferior.
                    }
                }
            }


        //al_destroy_bitmap(seletor);
        al_flip_display();//Atualiza a tela
        }
    while(esta_no_gameplay){//laço do gameplay.
        if(!colisao(&inimigo, &player, &BG,fonte)){//Se for detectada uma colisão.
            esta_no_gameplay = 0;//Desabilita a flag do gameplay
            esta_no_menu = 1;//Habilita a flag do menu.
            //As duas linhas a seguir reiniciam a posição do inimigo.
            inimigo.x = 600;
            inimigo.y = 400;
            zumbi = 0;//Reseta a flag que serve para mandar ou não zombis.
            player.pontuacao = 0;//Reinicia a pontuação do jogador.
            al_rest(0.5);
            continue;//Volta para o inicio do laço do gameplay.
        }
        //printf("bg.x = %f\n",BG.x);
        al_clear_to_color(al_map_rgb(255,255,255));//Colore a tela para branco.
        //al_draw_bitmap(BG.image,BG.x,BG.y,0);
        al_draw_scaled_bitmap(BG.image,BG.x,BG.y,al_get_bitmap_width(BG.image),al_get_bitmap_height(BG.image),0,0,800,600,1);//Desenha o fundo (que será móvel)

        if(BG.x + BG.width < 800){//Se a posição da borda esquerda do fundo for menor que 800
                //al_draw_bitmap(BG.image,BG.x+BG.width,BG.y,0);
                al_draw_scaled_bitmap(BG.image,BG.x + BG.width,BG.y,al_get_bitmap_width(BG.image),al_get_bitmap_height(BG.image),0,0,800,600,1);//Desenha outro fundo para preencher este vazio.
                cont++;
                if(cont%100==0)
                {
                    inimigo.x = 800;
                    inimigo.y = 400;
                    zumbi = 1;
                }
                if(zumbi == 1)
                {
                    inimigo.x -= velzumbi;
                    al_draw_bitmap(inimigo.image, inimigo.x, inimigo.y, 0);


                }
            }
            if(BG.x + BG.width <= 0){
                if(velHorizontal < 10)
                //velHorizontal += 1;
                BG.x = 0;

            }

        ALLEGRO_EVENT evento;//Variável que irá receber os eventos da fila de eventos.

        al_wait_for_event(fila_eventos,&evento);//Espera pelo eventos
        if(zumbi == 1)
        {
            inimigo.x -= velzumbi;
            al_draw_bitmap(inimigo.image, inimigo.x +15, inimigo.y, 0);

        }
        if(evento.type == ALLEGRO_EVENT_TIMER){//Se o evento for a contagem do timer
            player.pontuacao++;//Incrementa a pontuação
            if(zumbi == 1)
            {
                inimigo.x -= velzumbi;
                al_draw_bitmap(inimigo.image, inimigo.x - 15, inimigo.y, 0);

            }

            BG.x -= velHorizontal;//Move a imagem de fundo.
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

            //printf("pulo = %d\n",pulo);
        else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){//Se o evento detectado foi uma tecla pressionada.
            if(zumbi == 1)
            {
                inimigo.x -= velzumbi;
                al_draw_bitmap(inimigo.image, inimigo.x, inimigo.y, 0);

            }
            if(evento.keyboard.keycode == ALLEGRO_KEY_UP && pulo){//Se pressionou a seta pra cima e a flag de pulo for 1.
                player.sprite = al_load_bitmap("adventurer_jump.png");
                vely = -velPulo;//Muda a velocidade no exo y.
                pulo = 0;//Desabilita a flag de pulo.
            }
            if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN){//Se a tecla pressionada foi a seta para baixo
                player.sprite = al_load_bitmap("adventurer_slide.png");
                slide = 1;
            }
        }
        //al_draw_textf(fonte,al_map_rgb(255,0,200),0,0,NULL,"HIGH SCORE: %d",melhor_pontuacao);//Desenha o label contendo a melhor pontuação feita
        al_draw_bitmap(player.sprite,player.x,player.y,0);//Desenha o jogador na tela
        //As duas linhas a seguir desenham a pontuação atual e a melhor pontuação, em labels na tela.
        al_draw_textf(fonte,al_map_rgb(49,44,148),0,0,NULL,"HIGH SCORE: %d SCORE: %d",melhor_pontuacao,player.pontuacao/100);//Desenha o label contendo a pontuação
        if((player.pontuacao/100) > melhor_pontuacao){//Se a pontuação atual for maior que a melhor pontuação.
            melhor_pontuacao = player.pontuacao/100;//A melhor pontuação é a pontuação atual.
        }
        if(!pulo)//Se a flag de pulo for zero (significa que o jogador está no ar)
            vely += gravidade;//Incremnta-se o valor da velocidade no eixo y com o valor da gravidade (a gravidade puxa o jogador para baixo)
        else//Senão,
        vely = 0;//A velocidade no eixo y é zero.

        player.y += vely;//À posição do jogador no eixo y é acrescentado o valor da velocidade no eixo y.
        player.x += velx;//À posição do jogador no eixo x é acrescentado o valor da velocidade no eixo x.
        velx = 0;//Como decidimos que o personagem não deve se mover no eixo x, a velocidade no eixo x será sempre zero.
        pulo = (player.y >= 400);//A posição 400 do eixo y foi definida como sendo o chão, então se o jogador estiver no chão, a flag pulo é habilitada.
        al_flip_display();//Atualiza a tela.
    }
    while(esta_nos_creditos){
        char nomes[7][30] = {{"Andre Hugo"}, {"Isaac"}, {"Lucas Guedes"}, {"Mayra Amaral"}, {"Phellipe Palitot"}, {"Lincoln David"}};
        int i,foi = 0;

        al_draw_scaled_bitmap(fundo_do_menu, 0, 0, al_get_bitmap_width(fundo_do_menu),al_get_bitmap_height(fundo_do_menu),0,0,800,600,0);

        al_flip_display();

        al_draw_text(fonte, al_map_rgb(255, 0, 0), 400, 150, ALLEGRO_ALIGN_CENTRE, "Criadores:");

        for(i = 0; i <= 6; i++)
        {
            al_flip_display();
            if(i < 5)
            {
                al_draw_text(fonte, al_map_rgb(255, 0, 0), 400, 200 + 50* i, ALLEGRO_ALIGN_CENTRE, &nomes[i][0]);
                al_rest(0.5);
            }else{
                al_draw_text(fonte, al_map_rgb(255, 0, 0), 400, 200 + 50*i, ALLEGRO_ALIGN_CENTRE, "Orientador:");
                al_rest(0.5);
                al_draw_text(fonte, al_map_rgb(255, 0, 0), 400, 200 + 50* i +50, ALLEGRO_ALIGN_CENTRE, &nomes[i][0]);
                al_draw_text(fonte,al_map_rgb(200,0,0),LARGURA/2,0,ALLEGRO_ALIGN_CENTRE,"Pressione ESC para voltar ao menu.");
                al_rest(0.5);
            }

        }
    foi = 1;
    ALLEGRO_EVENT evento;
    BESTIAL:
    al_wait_for_event(fila_eventos,&evento);
    if(evento.type == ALLEGRO_EVENT_TIMER){
        puts("Tempo...");
    }else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
        if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            esta_nos_creditos = esta_no_gameplay = 0;
            esta_no_menu = 1;
            break;
        }
    }
    if(foi == 1)goto BESTIAL;
    }
    }
    GAME_OVER:
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
    al_destroy_bitmap(player.sprite);
    al_destroy_bitmap(sprite);
    al_destroy_bitmap(sprite_2);
    al_destroy_timer(timer);
    return 0;
}
