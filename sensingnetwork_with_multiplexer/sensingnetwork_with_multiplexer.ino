/*
  First Configuration
  This sketch demonstrates the usage of MKR WAN 1300/1310 LoRa module.
  This example code is in the public domain.
*/

#include <MKRWAN.h>
#include <Wire.h>
#include <AHT20.h>
AHT20 aht20;

LoRaModem modem;

// Uncomment if using the Murata chip as a module
// LoRaModem modem(Serial1);

String appEui= "3574817514217441";
String appKey= "ABCDC2475232327162444532217441FF";
String devAddr= "a8610a30323e8411";
String nwkSKey;
String appSKey;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Welcome to MKR WAN 1300/1310 first configuration sketch");
  Serial.println("Register to your favourite LoRa network and we are ready to go!");
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(AS923)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  if (modem.version() != ARDUINO_FW_VERSION) {
    Serial.println("Please make sure that the latest modem firmware is installed.");
    Serial.println("To update the firmware upload the 'MKRWANFWUpdate_standalone.ino' sketch.");
  }
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  int mode = 0;
  while (mode != 1 && mode != 2) {
    Serial.println("Are you connecting via OTAA (1) or ABP (2)?");
    mode = 1;
  }

  int connected;
  if (mode == 1) {
    Serial.println("Enter your APP EUI");
    appEui = "3574817514217441";

    Serial.println("Enter your APP KEY");
    appKey = "ABCDC2475232327162444532217441FF";

    appKey.trim();
    appEui.trim();

    connected = modem.joinOTAA(appEui, appKey);
  } else if (mode == 2) {

    Serial.println("Enter your Device Address");
    while (!Serial.available());
    devAddr = Serial.readStringUntil('\n');

    Serial.println("Enter your NWS KEY");
    while (!Serial.available());
    nwkSKey = Serial.readStringUntil('\n');

    Serial.println("Enter your APP SKEY");
    while (!Serial.available());
    appSKey = Serial.readStringUntil('\n');

    devAddr.trim();
    nwkSKey.trim();
    appSKey.trim();

    connected = modem.joinABP(devAddr, nwkSKey, appSKey);
  }

  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }

  delay(5000);

//センサの初期化
  Wire.begin(); //Join I2C bus
  //Check if the AHT20 will acknowledge
  if (aht20.begin() == false)
  {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    while (1);
  }

}

void loop() {

  if (aht20.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20.getTemperature();
    float humidity = aht20.getHumidity();

  int err;
  modem.setPort(3);
  modem.beginPacket();
  modem.print(String(temperature)+","+String(humidity));
  err = modem.endPacket(true);
  if (err > 0) {
  //  Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
  }

  //Print the results
  //Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.print(",");
  //Serial.print(" ℃\t");
  //Serial.print("Humidity: ");
  Serial.print(humidity, 2);
  //Serial.print("% RH");

  Serial.println();
  }

  delay(3000);
}