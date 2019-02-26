//including various libraries needed to run
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    9 
#define TFT_DC     4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

//setup the LCD
void setup() {
    tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display

    tft.setRotation(3);

    tft.fillScreen(ST77XX_BLUE); //Starting color of the screen is blue

    Serial.begin(9600);
}


void loop() {
  int incomingByte = 0;
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    switch ((char)incomingByte) {
      
      //if input is c
      case 'c':
        //print hatch panel is attached animation
        drawCompressorStuck();
        break;

      //if input is u
      case 'u':
        //print elevator is at the top animation
        drawElevatorTop();
        break;

      //if input is d
      case 'd':
        //print elevator is at the bottom animation
        drawElevatorBottom();
        break;

      //if input is b
      case 'b':
        //print ball is secured animation
        drawBall();
        break;

      //if input is a
      case 'a':
        //print arm is full tilt animation
        drawTilt();
        break;

      //if input is n
      case 'n':
        //print nothing is happening animation
        drawNone();
        break;
    }
  }
}


//Used when the compressor is fully stuck to the hatch
void drawCompressorStuck(){
  //fill screen with white, print a green circle, and print a white circle
  tft.fillScreen(ST77XX_WHITE);
  tft.fillCircle(80, 40,
                 42,
                 ST77XX_GREEN);
  tft.fillCircle(80, 40,
                 10,
                 ST77XX_WHITE);     
}



//Used when the elevator is at the top
void drawElevatorTop(){
  //print screen with white, print red triangle, print red rectangle
  tft.fillScreen(ST77XX_WHITE);
  tft.fillTriangle(80,0,
                   50,30,
                   110,30,
                   ST77XX_RED);
  tft.fillRect(60,30,
               40,80,
               ST77XX_RED);                 
}



//used when elevator is at the bottom
void drawElevatorBottom(){
  //fill screen with white, print red triangle, and red rectangle
  tft.fillScreen(ST77XX_WHITE);
  tft.fillTriangle(80,80,
                   50,40,
                   110,40,
                   ST77XX_RED);
  tft.fillRect(60,0,
               40,40,
               ST77XX_RED);
                   
}



//used when the robot has a ball
void drawBall(){
  //fill screen with white, print orange circle
  tft.fillScreen(ST77XX_WHITE);
  tft.fillCircle(80,40,
                 40,
                 ST77XX_ORANGE);
}



//used when the arm is fully tilted up
void drawTilt(){
  //fill the screen with red and make an X using 4 white triangles
  tft.fillScreen(ST77XX_RED);
  tft.fillTriangle(0,60,
                   0,20,
                   60,40,
                   ST77XX_WHITE);
  tft.fillTriangle(160,60,
                   160,20,
                   100,40,
                   ST77XX_WHITE);
  tft.fillTriangle(20,0,
                   140,0,
                   80,20,
                   ST77XX_WHITE);
   tft.fillTriangle(20,80,
                   140,80,
                   80,60,
                   ST77XX_WHITE);
}



//used to restart the screen to black
void drawNone(){
  //fill screen into black
  tft.fillScreen(ST77XX_BLACK);
  
}
  
