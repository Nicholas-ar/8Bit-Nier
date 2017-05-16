#include "teclado.h"

void keyboard_input()
{
   int i;

   for(i = 0; i < KEY_MAX; i++)
     teclas_anteriores[i] = key[i];

   poll_keyboard();
}

int apertou(int TECLA)
{
    return(teclas_anteriores[TECLA] == 0 && key[TECLA] != 1);
}

int segurou(int TECLA)
{
    return(teclas_anteriores[TECLA] == 1 && key[TECLA] == 1);
}

int soltou(int TECLA)
{
    return(teclas_anteriores[TECLA] == 1 && key[TECLA] == 0);
}
