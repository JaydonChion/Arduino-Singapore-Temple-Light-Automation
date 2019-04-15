#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define BRIGHTNESS 100
#define interrupt 2
#define relay1 3
#define relay2 4
#define relay3 8
#define relay4 9
#define relay5 11

#define motion 11\
#define PIN 6
#define NUM_PIXELS 290
int currentChoice =1;
int previousChoice = -1;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

static int motionSensor =0;

//functions
void readChoice();

void displayColor(int x, int y, int z);
void blueGreen(uint8_t wait);


void turnOff();


unsigned long previousMillis = 0;

void setup() {


  Serial.begin(9600);

  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  pinMode(relay5,OUTPUT);

  pinMode(motion,INPUT);
  pinMode(interrupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt), readChoice, FALLING);
  pixels.setBrightness(BRIGHTNESS);
  pixels.begin(); 
  turnOff();

  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  digitalWrite(relay4,HIGH);
  digitalWrite(relay5,HIGH);

}

void loop() {

  
  while(motionSensor == 0){

motionSensor = digitalRead(motion);
    
  }

  if( motionSensor == HIGH){
    previousMillis = millis();
    motionSensor = 0;
    unsigned long currentMillis = millis();
    while(((unsigned long)(currentMillis - previousMillis) )<(30000 - 8000))
    {      
      
        if(digitalRead(motion)==1){        //added this
             previousMillis = millis();

      
    }
      Serial.println((millis() - previousMillis));

      
      
      

          digitalWrite(relay1,LOW);
          digitalWrite(relay2,LOW);
          digitalWrite(relay3,LOW);
          digitalWrite(relay4,LOW);
          digitalWrite(relay5,LOW);
      

           blueGreen(30);

         
           // previousChoice = currentChoice;
      

  

          
        
          
        
         
      currentMillis = millis();
      
    


    
 }



  }

  
motionSensor = 0;


  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  digitalWrite(relay4,HIGH);
  digitalWrite(relay5,HIGH);
      
  turnOff();
 

  //}



  
}





void displayColor(int x, int y, int z){


for(int i=0;i<NUM_PIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(x,y,z)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(20);





}
}









void readChoice()
{

 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis();
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if ((unsigned long)(interrupt_time - last_interrupt_time) > 200)
 {
   currentChoice++;
       int userChoice= currentChoice%4;
        currentChoice = userChoice;
    
 }
 last_interrupt_time = interrupt_time;

 
  }





void turnOff()
{


for(int i=0;i<NUM_PIXELS;i++){

    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.




}


}


void blueGreen(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(0, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return pixels.Color(0, 255 - WheelPos * 3, 0,0);
}

uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}
