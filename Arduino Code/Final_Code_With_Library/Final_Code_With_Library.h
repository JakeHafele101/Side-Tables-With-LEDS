//led strip library
#include <FastLED.h>

//transciever library
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Pushbutton pin constants
#define BUTTON_NUM 7
#define BRIGHT_UP 8
#define BRIGHT_DOWN 2
#define HUE_UP 7
#define HUE_DOWN 3
#define SPEED_UP 6
#define SPEED_DOWN 4
#define PRESET 5

#define BRIGHTNESS_CHANGE 10
#define HUE_CHANGE 10
#define RATE_CHANGE 500 //ms

#define BRIGHTNESS_MAX 255
#define HUE_MAX 255
#define RATE_MAX 2000 //ms
#define PRESET_MAX 3 //Different settings for lights

//Defines transciever pins
#define CE 9
#define CSN 10

//Define led strip info
#define NUM_STRIP 3
#define NUM_LEDS = 30; //amount of LEDS per strip, read top to bottom of table, PLACEHOLDER NUMBERS
#define LED_STRIP = {A0, A1, A2} //Top to bottom strips, SW1 is A0, SW2 is A1, SW3 is A2
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
