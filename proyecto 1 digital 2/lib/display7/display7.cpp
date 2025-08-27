#include "display7.h"

// leds internas del display
#define seg_a 32
#define seg_b 13
#define seg_c 4
#define seg_d 22
#define seg_e 21
#define seg_f 33
#define seg_g 5
#define punto 23
int segmentos[8] = {seg_a, seg_b, seg_c, seg_d, seg_e, seg_f, seg_g, punto};

//displays
#define D1 18
#define D2 17
#define D3 16
#define D4 19
int displays[4] = {D1, D2, D3, D4};

void configurarDisplay(){
    for(int i = 0; i<8; i++){
    pinMode(segmentos[i], OUTPUT);
    digitalWrite(segmentos[i], LOW);
    }

    for(int i = 0; i<4; i++){
    pinMode(displays[i], OUTPUT);
    digitalWrite(displays[i], LOW);
    }
 }

 void desplegarPunto(bool hayPunto){
    digitalWrite(punto, hayPunto);
 }

 void desplegarNumero(int numero, int display){
    for(int i = 0; i<4; i++){
        if(i==display){
            digitalWrite(displays[display], HIGH);
        }
        else{
            digitalWrite(displays[i], LOW);
        }
    }

    desplegarPunto(display==1);
    
switch(numero){
    case 0:  // 0
      digitalWrite(seg_a, HIGH);
      digitalWrite(seg_b, HIGH);
      digitalWrite(seg_c, HIGH);
      digitalWrite(seg_d, HIGH);
      digitalWrite(seg_e, HIGH);
      digitalWrite(seg_f, HIGH);
      digitalWrite(seg_g, LOW);
      break;
    case 1:  // 1
      digitalWrite(seg_a, LOW);
      digitalWrite(seg_b, HIGH);
      digitalWrite(seg_c, HIGH);
      digitalWrite(seg_d, LOW);
      digitalWrite(seg_e, LOW);
      digitalWrite(seg_f, LOW);
      digitalWrite(seg_g, LOW);
      break;
    case 2:  // 2
      digitalWrite(seg_a, HIGH);
      digitalWrite(seg_b, HIGH);
      digitalWrite(seg_c, LOW);
      digitalWrite(seg_d, HIGH);
      digitalWrite(seg_e, HIGH);
      digitalWrite(seg_f, LOW);
      digitalWrite(seg_g, HIGH);
      break;
    case 3:  // 3
      digitalWrite(seg_a, HIGH);
      digitalWrite(seg_b, HIGH);
      digitalWrite(seg_c, HIGH);
      digitalWrite(seg_d, HIGH);
      digitalWrite(seg_e, LOW);
      digitalWrite(seg_f, LOW);
      digitalWrite(seg_g, HIGH);
      break;
    case 4:  // 4
      digitalWrite(seg_a, LOW);
      digitalWrite(seg_b, HIGH);
      digitalWrite(seg_c, HIGH);
      digitalWrite(seg_d, LOW);
      digitalWrite(seg_e, LOW);
      digitalWrite(seg_f, HIGH);
      digitalWrite(seg_g, HIGH);
      break;
    case 5:  // 5
      digitalWrite(seg_a, HIGH);
      digitalWrite(seg_b, LOW);
      digitalWrite(seg_c, HIGH);
      digitalWrite(seg_d, HIGH);
      digitalWrite(seg_e, LOW);
      digitalWrite(seg_f, HIGH);
      digitalWrite(seg_g, HIGH);
      break;
    case 6:  // 6
      digitalWrite(seg_a, HIGH);
      digitalWrite(seg_b, LOW);
      digitalWrite(seg_c, HIGH);
      digitalWrite(seg_d, HIGH);
      digitalWrite(seg_e, HIGH);
      digitalWrite(seg_f, HIGH);
      digitalWrite(seg_g, HIGH);
      break;
    case 7:  // 7
      digitalWrite(seg_a, HIGH);
      digitalWrite(seg_b, HIGH);
      digitalWrite(seg_c, HIGH);
      digitalWrite(seg_d, LOW);
      digitalWrite(seg_e, LOW);
      digitalWrite(seg_f, LOW);
      digitalWrite(seg_g, LOW);
      break;
    case 8:  // 8
      digitalWrite(seg_a, HIGH);
      digitalWrite(seg_b, HIGH);
      digitalWrite(seg_c, HIGH);
      digitalWrite(seg_d, HIGH);
      digitalWrite(seg_e, HIGH);
      digitalWrite(seg_f, HIGH);
      digitalWrite(seg_g, HIGH);
      break;
    case 9:  // 9
      digitalWrite(seg_a, HIGH);
      digitalWrite(seg_b, HIGH);
      digitalWrite(seg_c, HIGH);
      digitalWrite(seg_d, LOW);
      digitalWrite(seg_e, LOW);
      digitalWrite(seg_f, HIGH);
      digitalWrite(seg_g, HIGH);
      break;
    default: // Apagar todos si el dígito no es válido
      digitalWrite(seg_a, LOW);
      digitalWrite(seg_b, LOW);
      digitalWrite(seg_c, LOW);
      digitalWrite(seg_d, LOW);
      digitalWrite(seg_e, LOW);
      digitalWrite(seg_f, LOW);
      digitalWrite(seg_g, LOW);
      break;
    }
 }
 
 void apagarDisplays() {
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}
