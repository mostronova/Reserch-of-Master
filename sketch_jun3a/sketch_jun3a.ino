#include <Wire.h>
#include <AHT20.h>
AHT20 aht20;

int j = 0;

String SensorName[6] = {"あ", "い", "う", "え", "お", "か"};

void setup() {
  Serial.begin(115200);
  Serial.println("Humidity AHT20 examples");

  Wire.begin();  //Join I2C bus
  //Check if the AHT20 will acknowledge
  if (aht20.begin() == false) {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    while (1)
      ;
  }
  Serial.println("AHT20 acknowledged.");

  for (int i = 3; i >= 8; i = i + 1) {
    pinMode(i, OUTPUT);  // sets the digital pin i as output
  }
}



void loop() {

  digitalWrite(j + 3 , HIGH); // sets the digital pin i on

  Serial.println(millis());

  aht20.begin();

  // if (aht20.begin() == false)
  // {
  //   Serial.println("AHT20 not detected. Please check wiring. Freezing.");
  //   while (1);
  // }

  Serial.print("pin");
    Serial.print(SensorName[j]); 
     // Serial.print(j);
    Serial.print("\t");

    //Get the new temperature and humidity value
    float temperature = aht20.getTemperature();
    float humidity = aht20.getHumidity();

    //Print the results
    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.print(" ℃\t");
    Serial.print("Humidity: ");
    Serial.print(humidity, 2);
    Serial.print("% RH");
    Serial.println();

  // if (aht20.available() == true)
  // {
  //   Serial.print("pin");
  //   Serial.print(SensorName[j + 1]);
  //   // Serial.print(j);
  //   Serial.print("\t");

  //   //Get the new temperature and humidity value
  //   float temperature = aht20.getTemperature();
  //   float humidity = aht20.getHumidity();

  //   //Print the results
  //   Serial.print("Temperature: ");
  //   Serial.print(temperature, 2);
  //   Serial.print(" ℃\t");
  //   Serial.print("Humidity: ");
  //   Serial.print(humidity, 2);
  //   Serial.print("% RH");

  //   Serial.println();
  // }

  digitalWrite(j + 3 , LOW);  // sets the digital pin i off
  delay(1000);            // waits for a second

  if (j == 5)
  {
    j = 0;
  }
  else
  {
    j = j + 1;
  }
}