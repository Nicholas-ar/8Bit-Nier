#include <allegro.h>
#include "teclado.h"
#include "stdlib.h"

volatile int exit_program;
void fecha_programa() { exit_program = TRUE; }
END_OF_FUNCTION(fecha_programa)

volatile int timer;
void maisTimer() {timer++;}
END_OF_FUNCTION(maisTimer)

int bounding_box_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    if( (x1 > x2 + w2) || (y1 > y2 + h2) || (x2 > x1 + w1) || (y2 > y1 + h1) )
     return FALSE;
    else
     return TRUE;
}

int pontosExtras(int m)
{
    if(m <= 1)
        return 1;
    else
        return ( m + pontosExtras(m-1) );
}

typedef struct
{
	long int finalScore;
}jogador;

int main()
{
  allegro_init();
  install_timer();
  install_keyboard();
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 550, 0, 0);
  set_window_title("8 Bit Nier");

  int tiro = 0,i_pod = 430,i_bullet,j_bullet = 70,j_stubby = 750,j_flyer = 750,j_flyer2 = 750;
  int i , rodando = 1, menu=1, abatidos = 0, tempoFlyer = 5000,tempoFlyer2 = 7500;
  jogador n;
  int **inimigos;
  inimigos = calloc(3,sizeof(int));
  for(i=0;i<3;i++)
    inimigos[i] = calloc(3,sizeof(int));
  int *marcadores;
  marcadores = calloc(3 , sizeof (int));

  exit_program = FALSE;
  LOCK_FUNCTION(fecha_programa);
  LOCK_VARIABLE(exit_program);
  set_close_button_callback(fecha_programa);

  timer = 0;
  LOCK_FUNCTION(maisTimer);
  LOCK_VARIABLE(timer);
  install_int_ex(maisTimer, MSEC_TO_TIMER(1));

  ///BITMAPS
  BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
  BITMAP* bullet = load_bitmap("bullet.bmp", NULL);
  BITMAP* BG = load_bitmap("BG.bmp", NULL);
  BITMAP* pod = load_bitmap("pod.bmp", NULL);
  BITMAP* stubby = load_bitmap("stubby.bmp", NULL);
  BITMAP* flyer = load_bitmap("flyer.bmp", NULL);
  BITMAP* logo = load_bitmap("logo.bmp", NULL);

  ///GAME LOOP
  while(!exit_program)
  {
    //INPUT
  	//keyboard_input();

    if(key[KEY_ESC])
    {fecha_programa();}

	if(key[KEY_SPACE] && i_pod>100)
     	{i_pod--;}
 	else if(i_pod<430)
 		{i_pod+=2;}
    if(inimigos[0][0]==1 && j_stubby>20)
        {j_stubby--;}
    if(inimigos[1][0]==1 && j_flyer>20)
        {j_flyer--;}
    if(inimigos[1][1]==1 && j_flyer2>20)
        {j_flyer2--;}
    if(key[KEY_Z] && tiro == 0)
    {
        tiro = 1;
        i_bullet = i_pod+50;
    }
    if(rodando==0 && key[KEY_ENTER])
    {
        tempoFlyer = 5000;
        tempoFlyer2 = 7500;
        timer=0;
        tiro=0;
        j_bullet = 70;
        inimigos[0][0]=0;
        inimigos[1][0]=0;
        inimigos[1][1]=0;
        j_stubby=750;
        j_flyer=750;
        j_flyer2=750;
        marcadores[0]=0;
        marcadores[1]=0;
        marcadores[2]=0;
        abatidos = 0;
        rodando=1;
    }
    if(menu==1 && key[KEY_ENTER])
    {
        tempoFlyer2 = 7500;
        tempoFlyer = 5000;
        timer=0;
        tiro=0;
        j_bullet = 70;
        inimigos[0][0]=0;
        inimigos[1][0]=0;
        inimigos[1][1]=0;
        j_stubby=750;
        j_flyer=750;
        j_flyer2=750;
        marcadores[0]=0;
        marcadores[1]=0;
        marcadores[2]=0;
        abatidos = 0;
        menu=0;
    }

     //UPDATE
    if(rodando == 1 && (j_stubby<60 || j_flyer2<60 || j_flyer<60))
    {
        rodando=0;
        n.finalScore=timer+pontosExtras(abatidos);
        j_stubby=750;
        j_flyer=750;
        j_flyer2=750;
    }
    if(bounding_box_collision(j_bullet,i_bullet,bullet->w,bullet->h,j_stubby,430,stubby->w,stubby->h)==TRUE)
    {
        inimigos[0][0]=0;
        tiro=0;
        j_stubby = 750;
        j_bullet = 70;
        abatidos++;
    }
    if(bounding_box_collision(j_bullet,i_bullet,bullet->w,bullet->h,j_flyer,200,flyer->w,flyer->h)==TRUE)
    {
        inimigos[1][0]=0;
        tiro=0;
        j_flyer = 750;
        j_bullet = 70;
        tempoFlyer -= 50;
        abatidos++;
    }
    if(bounding_box_collision(j_bullet,i_bullet,bullet->w,bullet->h,j_flyer2,300,flyer->w,flyer->h)==TRUE)
    {
        inimigos[1][1]=0;
        tiro=0;
        j_flyer2 = 750;
        j_bullet = 70;
        tempoFlyer2 -= 50;
        abatidos++;
    }
    if(timer-marcadores[0]>=2000)
    {
        marcadores[0]=timer;
        inimigos[0][0]=1;
    }
    if(timer-marcadores[1]>=tempoFlyer)
    {
        marcadores[1]=timer;
        inimigos[1][0]=1;
    }
    if(timer-marcadores[2]>=tempoFlyer2)
    {
        marcadores[2]=timer;
        inimigos[1][1]=1;
    }
    if(tiro)
    {
        j_bullet++;
        j_bullet++;
    }
    if(j_bullet>800)
    {
        tiro = 0;
        j_bullet = 70;
    }
     //DRAW

     if(menu)
    {
  //  draw_sprite(screen, buffer, 0, 0);
  //  clear(buffer);
      draw_sprite(buffer, logo, 50, -30);
      textprintf_centre_ex(buffer,font,400,250,makecol(255,255,255),-1,"PRESS ENTER TO PLAY OR ESC TO QUIT");
      textprintf_centre_ex(buffer,font,160,540,makecol(255,255,255),-1,"Controls: z to shoot and space to fly");

    }
    else if(rodando){
     draw_sprite(buffer, BG, 0, 0);
     textprintf_centre_ex(buffer,font,740,10,makecol(255,255,255),-1,"SCORE:%d",timer);
     draw_sprite_ex(buffer, pod, 0, i_pod, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
     if(inimigos[0][0])
     {
         draw_sprite(buffer, stubby, j_stubby, 430);
     }
     if(inimigos[1][0])
     {
         draw_sprite(buffer, flyer, j_flyer, 200);
     }
     if(inimigos[1][1])
     {
         draw_sprite(buffer, flyer, j_flyer2, 300);
     }
     if(tiro)
     {
         draw_sprite(buffer, bullet, j_bullet, i_bullet);
     }
     draw_sprite(screen, buffer, 0, 0);
     clear(buffer);
    }
    if(rodando==0)
    {
      draw_sprite(screen, buffer, 0, 0);
      clear(buffer);
      draw_sprite(buffer, logo, 50, -30);
      textprintf_centre_ex(buffer,font,400,270,makecol(255,255,255),-1,"FINAL SCORE:%ld",n.finalScore);
      textprintf_centre_ex(buffer,font,400,290,makecol(255,255,255),-1,"PRESS ENTER TO PLAY AGAIN OR ESC TO QUIT");
    }


  }

  ///FINALIZAÇÂO
  destroy_bitmap(buffer);
  destroy_bitmap(pod);
  destroy_bitmap(BG);
  destroy_bitmap(bullet);
  destroy_bitmap(stubby);
  destroy_bitmap(flyer);

  return 0;
}
END_OF_MAIN();
