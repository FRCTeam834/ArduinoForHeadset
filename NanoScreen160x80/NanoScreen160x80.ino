//including various libraries needed to run
#include <Adafruit_GFX.h>         // Core graphics library
#include <Adafruit_ST7735.h>      // Hardware-specific library for ST7735
#include <SdFat.h>                // SD card & FAT filesystem library
#include <Adafruit_SPIFlash.h>    // SPI / QSPI flash library
#include <Adafruit_ImageReader.h> // Image-reading functions
#include <SPI.h>

#define SD_CS      5
#define TFT_CS     10
#define TFT_DC     4
#define TFT_RST    9 

Adafruit_ST7735      tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
SdFat                SD;         // SD card filesystem
Adafruit_ImageReader reader(SD); // Image-reader object, pass in SD filesys

//setup the LCD
void setup()
{
    tft.initR(INITR_MINI160x80); // Initialize a ST7735S chip, mini display

    tft.fillScreen(ST77XX_BLUE); // Starting color of the screen is blue

    initializeSDCard();

    Serial.begin(9600);
}

void loop()
{
  int incomingByte = 0;
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    switch (incomingByte)
    {
      // Used as part of auto recognition
      case 0xAA:
        Serial.write(0x55);
        Serial.flush();
        break;

      // Used as part of auto recognition
      case 0xC3:
        Serial.write(0x3C);
        Serial.flush();
        break;

       // '0', Clear the screen
       case 48:
        tft.fillScreen(ST77XX_BLACK);
        break;

      // For anything else, use the value as a character to create a file name
      default:
        char buf[6];
        sprintf(buf, "%c.bmp", incomingByte);
        bmpDraw(buf);
        break;
    }
  }
}

void initializeSDCard()
{
  // The Adafruit_ImageReader constructor call (above, before setup())
  // accepts an uninitialized SdFat or FatFileSystem object. This MUST
  // BE INITIALIZED before using any of the image reader functions!
  if (!SD.begin(SD_CS, SD_SCK_MHZ(10))) // Breakouts require 10 MHz limit due to longer wires
  {
    displayErrorMessage("SD Card missing",
                        ST77XX_WHITE,
                        ST77XX_RED);
  }
}

void bmpDraw(char *file_name)
{
  ImageReturnCode imageReturnCode = reader.drawBMP(file_name, tft, 0, 0);
  if (imageReturnCode != IMAGE_SUCCESS)
  {
    switch (imageReturnCode)
    {
      case IMAGE_ERR_FILE_NOT_FOUND: // Could not open file
        char file_not_found_buf[26];
        sprintf(file_not_found_buf, "File not\r\nfound\r\n(%s)", file_name);
        displayErrorMessage(file_not_found_buf,
                            ST77XX_WHITE,
                            ST77XX_MAGENTA);
        break;

      case IMAGE_ERR_FORMAT:         // Not a supported image format
        char format_err_buf[23];
        sprintf(format_err_buf, "Format\r\nError\r\n(%s)", file_name);
        displayErrorMessage(format_err_buf,
                            ST77XX_BLUE,
                            ST77XX_ORANGE);
        break;

      case IMAGE_ERR_MALLOC:         // Could not allocate image
        displayErrorMessage("Malloc Error",
                            ST77XX_BLUE,
                            ST77XX_YELLOW);
        break;
    }
    tft.setRotation(0);
  }  
}

void displayErrorMessage(char *message,
                         uint16_t textColor,
                         uint16_t screenColor)
{
    tft.setRotation(3);
    tft.setCursor(1, 1);
    tft.setTextSize(3);
    tft.fillScreen(screenColor);
    tft.setTextColor(textColor);
    tft.print(message);
    tft.setRotation(0);    
}
