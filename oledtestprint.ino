#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

DHT dht(26, DHT11);

#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(20, 20);
  display.println("Welcome Master");
  display.display();

  delay(2000);
  Serial.begin(115200);
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  display.clearDisplay();

  String tempText = "Temp: " + String(temp) + "°C";
  String humidityText = "Humidity: " + String(humidity) + "%";
  String conditionText;


  //Determine the condition based on the temperature

  if(temp < 25) {
    conditionText = "Condition: Cold";
  } else if (temp >= 25 && temp <= 30) {
    conditionText = "Condition: Normal";
  } else  {
    conditionText = "Condition: Hot";
  }

  int16_t x1, y1;
  uint16_t width, height;

  //calculate the width of the temperature text
  display.getTextBounds(tempText, 0, 0, &x1, &y1, &width, &height);
  int tempX = (display.width() - width) / 2;


  //calculate the width of the humidity text
  display.getTextBounds(humidityText, 0, 0, &x1, &y1, &width, &height);
  int humidityX = (display.width() - width) / 2;


  display.getTextBounds(conditionText, 0, 0, &x1, &y1, &width, &height);
  int conditionX = (display.width() - width) / 2;



  unsigned long startMillis = millis();
  while (millis() - startMillis < 10000) {
    for (int x = 0; x < display.width(); x++ ){
   display.clearDisplay();


   display.setCursor(tempX, 20);
   display.println(tempText);

   display.setCursor(humidityX, 35);
   display.print(humidityText);


    display.drawRect(x, 50, 10, 10, WHITE);

    display.display();
    delay(20);

    if (millis() - startMillis >= 10000) {
      break;
      }
    }
  }

  //display the condition for 10 secods
  display.clearDisplay();
  display.setCursor(conditionX, 30);
  display.println(conditionText);
  display.display();
  delay(10000);
}