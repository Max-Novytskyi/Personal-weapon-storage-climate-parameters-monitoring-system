#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop ()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(humidity);
  delay(2000);
}
