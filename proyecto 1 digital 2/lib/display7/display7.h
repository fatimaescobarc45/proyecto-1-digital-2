#ifndef __DISPLAY7_H__
#define __DISPLAY7_H__

#include <Arduino.h>
#include <stdint.h>

void configurarDisplay();
void desplegarNumero(int numero, int display);
void desplegarPunto(bool hayPunto);
void apagarDisplays();

#endif //__DISPLAY7_H__