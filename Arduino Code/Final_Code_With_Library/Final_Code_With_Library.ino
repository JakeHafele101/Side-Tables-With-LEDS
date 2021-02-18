#include "Final_Code_With_Library.h"

CRGB leds[NUM_STRIP][NUM_LEDS];

//LED value initialization
int brightness = 100; //Brightness of LEDs
int hue = 100; //Color of LEDs
int rate = 5; //Rate LEDs change
int preset = 0;

//Transceiever initialization
RF24 radio(CE, CSN);
const byte address[6] = "00001"; //Acts as key between receivers

//Button initialization
int buttonState[BUTTON_NUM];
boolean isButtonActive[BUTTON_NUM];
const int buttonDigital[] = {BRIGHT_UP, BRIGHT_DOWN, HUE_UP, HUE_DOWN, SPEED_UP, SPEED_DOWN, PRESET};

void setup() {
  Serial.begin(9600); //Starts terminal at 9600 baud rate

  //Setup functions for LED Strips
  FastLED.addLeds<LED_TYPE, LED_STRIP[0], COLOR_ORDER>(leds[0], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP[1], COLOR_ORDER>(leds[1], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP[2], COLOR_ORDER>(leds[2], NUM_LEDS);

  //Setup functions for transciever and radio object
  radio.begin(); //Wireless receiver setup
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  //Initializes pushbuttons as inputs
  pinMode(BRIGHT_UP, INPUT);
  pinMode(BRIGHT_DOWN, INPUT);
  pinMode(HUE_UP, INPUT);
  pinMode(HUE_DOWN, INPUT);
  pinMode(SPEED_UP, INPUT);
  pinMode(SPEED_DOWN, INPUT);
  pinMode(PRESET, INPUT);

//Sets all button state to default false
  for(int i = 0; i < BUTTON_NUM; i++){ //Button pin setup
    pinMode(buttonDigital[i], INPUT);
    isButtonActive[i] = false; //Sets buttons so they all havent been recognized as pressed yet
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  button_read(); //Scans buttons, updates values to buttons

  //do different led functions


  //talk to different arduinos with transciever

}

void button_read(){
  for(int i = 0; i < BUTTON_NUM; i++){ //Condition checks for buttons being held/pressed
    buttonState[i] = digitalRead(buttonDigital[i]);
    if(buttonState[i] && !isButtonActive[i]){ //Checks if buttonState is 1 and isButtonActive is false
      isButtonActive[i] = true;
//      int buttonSent = i + 1;
//      Serial.println(buttonSent);
//      radio.write(&buttonSent, sizeof(buttonSent));
        check_brightness();
        check_hue();
        check_speed();
        check_preset();
    }
    else if(!buttonState[i] && isButtonActive[i]){ //Checks if buttonState is 0 and isButtonActive is true
      isButtonActive[i] = false;
    }
  }
}

void check_brightness(){
  if(buttonState[0]){
    brightness += BRIGHTNESS_CHANGE;
    if(brightness > BRIGHTNESS_MAX){
      brightness = BRIGHTNESS_MAX;
    }
  }
  else if(buttonState[1]){
    brightness -= BRIGHTNESS_CHANGE;
    if(brightness < 0){
      brightness = 0;
    }
  }
}

void check_hue(){
  if(buttonState[2]){
    hue += HUE_CHANGE;
    if(hue > HUE_MAX){
      hue = HUE_MAX;
    }
  }
  else if(buttonState[3]){
    hue -= HUE_CHANGE;
    if(hue < 0){
      hue = 0;
    }
  }
}

void check_speed(){
  if(buttonState[4]){
    rate += RATE_CHANGE;
    if(rate > RATE_MAX){
      rate = RATE_MAX;
    }
  }
  else if(buttonState[5]){
    rate -= RATE_CHANGE;
    if(rate < 0){
      rate = 0;
    }
  }
}

void check_preset(){
  if(buttonState[6]){
    preset++;
  }
  if(preset > PRESET_MAX){
      preset = 0;
  }
}