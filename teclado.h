#ifndef TECLADO_H_INCLUDED
#define TECLADO_H_INCLUDED

#include <allegro.h>

int teclas_anteriores[KEY_MAX];

void keyboard_input();
int apertou(int TECLA);
int segurou(int TECLA);
int soltou(int TECLA);

#endif // TECLADO_H_INCLUDED
