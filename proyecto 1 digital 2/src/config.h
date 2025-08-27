/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME  "fatimaescobarc"
#define IO_KEY       "aio_TAtu57ixXpjvyMlyV2WCGLLMOKLo"

/******************************* WIFI **************************************/


#define WIFI_SSID "Nosoyese"
#define WIFI_PASS "soyese123"


// comment out the following lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"


AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
