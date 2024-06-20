#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float lastTemperature = 0.0;
float lastHumidity = 0.0;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);  
}

void loop ()
{ 
  if (Serial.available() > 0) {
    String message = Serial.readString();
    
    char *tempString = strtok(message.c_str(), ",");
    char *humString = strtok(NULL, ",");
    
    float temperature = atof(tempString);
    float humidity = atof(humString);
  
    if (temperature > 30.0 || temperature < 10.0 || humidity > 60 || humidity < 20) {
      digitalWrite(7, HIGH);
       for (int i = 0; i < 7; i++) {
        digitalWrite(6, HIGH);
        delay(2000); 
        digitalWrite(6, LOW);
        delay(2000);
       } 
      } else {
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        } 

    if (temperature != lastTemperature || humidity != lastHumidity) { 
     lcd.setCursor(6, 0);
     lcd.print("    ");
     lcd.setCursor(6, 0);
     lcd.print(temperature);
     lcd.print((char)223);
     lcd.print("C");

     lcd.setCursor(10, 1);
     lcd.print("       ");
     lcd.setCursor(10, 1);
     lcd.print(humidity);
     lcd.print("%");

     lastTemperature = temperature;
     lastHumidity = humidity;
    }
  }
}