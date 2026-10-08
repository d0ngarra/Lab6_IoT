#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 9
#define OLED_CS 10
#define OLED_RST 8

Adafruit_SSD1306 display(
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	OLED_MOSI,
	OLED_CLK,
	OLED_DC,
	OLED_RST,
	OLED_CS
);

Adafruit_BMP280 bmp;
float temperature;
float Altitude;
float pressure;

void setup(){
  Wire.begin();
  Serial.println("I2C Started");
  Serial.begin(9600);
  Serial.println("Program Started");
  
  display.begin(
    SSD1306_SWITCHCAPVCC
  );

  display.clearDisplay(); //clear display
  display.setTextSize(1); //set text size
  display.setTextColor(SSD1306_WHITE); //Set Text Color
  display.display(); //Update Display

    if(bmp.begin(0x76)){
      Serial.println("BMP280 Found at 0x76");
    }
    else if(bmp.begin(0x77)){
      Serial.println("BMP280 Found a 0x77");
    }
    else{
      Serial.println("BMP280 Not Found");
    }
}

void loop(){
  temperature = bmp.readTemperature();
  Altitude = bmp.readAltitude(1013.25);
  pressure = bmp.readPressure() / 100;
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Altitude: ");
  Serial.print(Altitude);
  Serial.println(" m");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
  
  //display.clearDisplay(); //Clear the display
  //display.setCursor(0,0); //Move the cursor to the top-left corner
  //display.print("Hello Dawson"); //display "Hello dawson"
  //display.display(); //update the display

  display.clearDisplay();//clear display
  display.setCursor(0,0);//move cursor
  display.print("Temp: ");//display label temp:
  display.print(temperature);//display temp
  display.println(" C");//display temp unit
  display.print("Alt: ");//display alt:
  display.print(Altitude);//diaply alt value
  display.println(" m");//display alt unit
  display.print("Pres: ");//display pres:
  display.print(pressure);//display pres value
  display.println(" hPa");//display pres unit
  display.display();//update display

  delay(1000); // wait a second
}
