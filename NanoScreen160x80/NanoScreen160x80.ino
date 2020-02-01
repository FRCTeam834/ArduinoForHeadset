//including various libraries needed to run
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    9 
#define TFT_DC     4
#define BACKGREEN 0x37E5
#define ARROWBLUE 0x00FC
#define BACKORANGE 0xFD03

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

      // Used as part of auto recognition
      case (char)0xAA:
        Serial.write(0x55);
        Serial.flush();
        break;

      // Used as part of auto recognition
      case (char)0xC3:
        Serial.write(0x3C);
        Serial.flush();
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
/*
      //if input is b
      case 'b':
        //print ball is secured animation
        drawBall();
        break;
*/
      //if input is a
      case 'a':
        //print arm is full tilt animation
        drawTilt();
        break;

      case 's':
        drawScissor();
        break;
        

      //if input is n
      case 'n':
        //print nothing is happening animation
        drawNone();
        break;
    }
  }
}

/*
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
*/


//Used when the elevator is at the top
void drawElevatorTop(){
  //print screen with white, print red triangle, print red rectangle
  tft.fillScreen(BACKGREEN);
  tft.fillTriangle(0,80,
                   160,80,
                   80,0,
                   ARROWBLUE);                
}



//used when elevator is at the bottom
void drawElevatorBottom(){
  //fill screen with white, print red triangle, and red rectangle
  tft.fillScreen(BACKORANGE);
  tft.fillTriangle(0,0,
                   160,0,
                   80,80,
                   ST77XX_BLUE);
}


/*
//used when the robot has a ball
void drawBall(){
  //fill screen with white, print orange circle
  tft.fillScreen(ST77XX_WHITE);
  tft.fillCircle(80,40,
                 40,
                 ST77XX_ORANGE);
}
*/


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

void drawScissor(){
  tft.fillScreen(ST77XX_WHITE);
  tft.fillTriangle(60,20,
                   100,20,
                   80,40,
                   ST77XX_BLUE);
  tft.fillTriangle(60,60,
                   100,60,
                   80,40,
                   ST77XX_BLUE);
                   
}
