/*
Fátima Fernanda Escobar Castro
Carné: 231967
Electrónica Digital 2 (Biomédica)

    Proyecto #1
    Sensor de temperatura. 

*/
//librerías!
#include <Arduino.h>
#include <stdint.h>
#include <driver/ledc.h>
#include "config.h" // para el ADC read en Adafruit
#include "display7.h" // librería personalizada 


#define delaydisplay 40
//led RGB para semáforo
#define ledR 23
#define ledG 21
#define ledY 22

//sensor y servo
#define pinSensor 34
#define pinServo 15
#define boton 13


//variables útiles
float tempActual;
int32_t dutyServo;
#define freqPWM_servo 50
#define resPWM_servo 16 
#define freqPWM_led 30
#define resPWM_led 12 
hw_timer_t *timer = NULL;

volatile int digitos[4] = {0, 0, 0, 0};  
volatile int indiceDisplay = 0;  


//adafruit IO
#define IO_LOOP_DELAY 5000
unsigned long lastUpdate = 0;

// set up the 'counter' feed
AdafruitIO_Feed *canalTemperatura = io.feed("temperatura-reloj");


// antirrebote
unsigned long ultimaMedicion = 0;
const unsigned long debounceDelay = 50; // ms

// prototipos de función
void initPWMServo();
void initPWMLeds();
float leerTemp();
void relojSemaforo(float temp);
void mostrarTemp(int temp);
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
void separarYEncender(float temp);
void IRAM_ATTR onTimer();



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // wait for serial monitor to open
   while(! Serial); 

  pinMode(pinSensor, INPUT);
  pinMode(boton, INPUT_PULLUP);
  
  initPWMServo();
  initPWMLeds();
  configurarDisplay();

    // Configuración del timer
  // 80 -> prescaler a 1 µs por tick (80 MHz / 80 = 1 MHz)
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);

  // cada 2000 µs -> 2ms por display
  // refresco total ≈ 8 ms = 125 Hz (sin ghosting)
  timerAlarmWrite(timer, 2000, true);
  timerAlarmEnable(timer); 
  

  if(tempActual==0){
    ledcWrite(0, 0);
    ledcWrite(1, 0);
    ledcWrite(2, 0);
  }



  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  // CÓDIGO REPETITIVO de ADAFRUIT

  io.run();



  // lectura por pushbutton
  static bool leyoTemp = HIGH;
  bool lecturaTemp = digitalRead(boton);

  if (leyoTemp == HIGH && lecturaTemp == LOW && (millis() - ultimaMedicion) > debounceDelay) { //antirrebote
    tempActual = leerTemp();
    ultimaMedicion = millis();
   Serial.print("sending -> ");
    Serial.println(tempActual);
    canalTemperatura->save(tempActual);
    
  }
  leyoTemp = lecturaTemp;

  if(tempActual==0){
    for(int i = 0; i<4; i++) desplegarNumero(11,i);
  }
  else{

  relojSemaforo(tempActual);

  ledcWrite(3, dutyServo);    
  
  separarYEncender(tempActual);
  }

  

  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
    // save count to the 'counter' feed on Adafruit IO
    Serial.print("sending -> ");
    Serial.println(tempActual);
    canalTemperatura->save(tempActual);
    //counter->save(count);


    // after publishing, store the current time
    lastUpdate = millis();
  }
 
  

  
}

// definición de funciones

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) { // para mapear floats
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


float leerTemp(){
//estructura tomada de: https://www.electronicwings.com/sensors-modules/lm35-temperature-sensor
  int valor_ADC;
  float temp_val;
  valor_ADC = analogRead(pinSensor);  // Read Temperature
  temp_val = (valor_ADC * 5) / 4095.0; // Convert ADC value to voltage (ESP32: 12-bit, 3.3V)
  temp_val = temp_val * 100.0; // LM35: 10mV/°C, so 1V = 100°C
  Serial.println(temp_val);
  return temp_val;
}

void initPWMServo(void){
  // acá configuramos el PWM del servo
  ledcSetup(3, freqPWM_servo, resPWM_servo);
  ledcAttachPin(pinServo, 3);
  ledcWrite(3, 0);  
}
void initPWMLeds(void){
  // acá configuramos el PWM del servo
  ledcSetup(0, freqPWM_led, resPWM_led);
  ledcAttachPin(ledR, 3);
  ledcWrite(0, 0); 
  
  ledcSetup(1, freqPWM_led, resPWM_led);
  ledcAttachPin(ledG, 3);
  ledcWrite(1, 0); 

  ledcSetup(2, freqPWM_led, resPWM_led);
  ledcAttachPin(ledY, 3);
  ledcWrite(2, 0); 
}

void relojSemaforo(float temp){
  // Limitar la temperatura dentro del rango
  if(temp > 30.0) temp = 30.0;
  if(temp < 20.0) temp = 20.0;

  // LEDs según temperatura
  if(temp <= 22.0){
    // Verde encendido (PWM), otros apagados
    ledcWrite(0, 0);      // Rojo OFF
    ledcWrite(1, 4095);   // Verde ON
    ledcWrite(2, 0);      // Amarillo OFF
  }
  else if(temp <= 25.0){
    // Amarillo encendido (PWM), otros apagados
    ledcWrite(0, 0);      // Rojo OFF
    ledcWrite(1, 0);      // Verde OFF
    ledcWrite(2, 4095);   // Amarillo ON
  }
  else{
    // Rojo encendido (PWM), otros apagados
    ledcWrite(0, 4095);   // Rojo ON
    ledcWrite(1, 0);      // Verde OFF
    ledcWrite(2, 0);      // Amarillo OFF
  }

  // Calcular ciclo de trabajo exacto del servo (0° a 180° = duty de 1638 a 8191)
  dutyServo = mapFloat(temp, 20.0, 30.0, 8191.0, 1638.0); // rota clockwise en vez de ccw
}

void separarYEncender(float temperatura){       

  int temp = (int)(temperatura * 100 + 0.5);

  int decena = temp/1000;
  temp = temp - decena*1000; // mod operator funcionaría tmb
  int unidad = temp/100;
  temp = temp - unidad*100;
  int decima = temp/10;
  temp = temp - decima*10;
  int centesima = temp;

  digitos[0] = decena;
  digitos[1] = unidad;
  digitos[2] = decima;
  digitos[3] = centesima;

}

void IRAM_ATTR onTimer() {
  // apagar todos los displays antes de cambiar
  apagarDisplays();
  // mostrar el dígito actual
  desplegarNumero(digitos[indiceDisplay], indiceDisplay);

  // siguiente display
  indiceDisplay++;
  if (indiceDisplay > 3) {
    indiceDisplay = 0;
}
}
