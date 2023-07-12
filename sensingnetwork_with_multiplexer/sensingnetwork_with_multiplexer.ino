/*
  First Configuration
  This sketch demonstrates the usage of MKR WAN 1300/1310 LoRa module.
  This example code is in the public domain.
*/

#include <MKRWAN.h>
#include <Wire.h>
#include <AHT20.h>
#define ADDRESS 0x70  //1110000→16進数に
#include <stdint.h>
AHT20 aht20_0; //あ
AHT20 aht20_1; //い
AHT20 aht20_2; //う

LoRaModem modem;

// Uncomment if using the Murata chip as a module
// LoRaModem modem(Serial1);

String appEui= "";
String appKey= "";
String devAddr= "";
String nwkSKey;
String appSKey;

uint8_t channel_code(uint8_t ch);
void switch_channel(uint8_t ch);

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
    appEui = "";

    Serial.println("Enter your APP KEY");
    appKey = "";

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
  switch_channel(0); //channelを0にした
  if(aht20_0.begin() == false)
  {
    Serial.println("あ not detected. Please check wiring. Freezing.");
  }  

  switch_channel(1); //channelを1にした
  if(aht20_1.begin() == false)
  {
    Serial.println("い not detected. Please check wiring. Freezing.");
  }  

  switch_channel(2); //channelを2にした
  if(aht20_2.begin() == false)
  {
    Serial.println("う not detected. Please check wiring. Freezing.");
  }  

}

void loop() {

  switch_channel(0);
  if (aht20_0.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20_0.getTemperature();
    float humidity = aht20_0.getHumidity();

    int err;
    modem.setPort(3);
    modem.beginPacket();
    modem.print("ch0,"+String(temperature)+","+String(humidity));
    err = modem.endPacket(true);
    if (err > 0) {
    //  Serial.println("Message sent correctly!");
    } else {
      Serial.println("Error sending message :(");
    }

    //Print the results
    Serial.print("あ,");
    //Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.print(",");
    //Serial.print(" ℃\t");
    //Serial.print("Humidity: ");
    Serial.print(humidity, 2);
    //Serial.print("% RH");

    Serial.println();

    delay(1000);
  }

  switch_channel(1);
  if (aht20_1.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20_1.getTemperature();
    float humidity = aht20_1.getHumidity();

    int err;
    modem.setPort(3);
    modem.beginPacket();
    modem.print("ch1,"+String(temperature)+","+String(humidity));
    err = modem.endPacket(true);
    if (err > 0) {
    //  Serial.println("Message sent correctly!");
    } else {
      Serial.println("Error sending message :(");
    }

    //Print the results
    Serial.print("い,");
    //Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.print(",");
    //Serial.print(" ℃\t");
    //Serial.print("Humidity: ");
    Serial.print(humidity, 2);
    //Serial.print("% RH");

    Serial.println();

    delay(1000);
  }

  switch_channel(2);
  if (aht20_2.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20_2.getTemperature();
    float humidity = aht20_2.getHumidity();

    int err;
    modem.setPort(3);
    modem.beginPacket();
    modem.print("ch2,"+String(temperature)+","+String(humidity));
    err = modem.endPacket(true);
    if (err > 0) {
    //  Serial.println("Message sent correctly!");
    } else {
      Serial.println("Error sending message :(");
    }

    //Print the results
    Serial.print("う,");
    //Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.print(",");
    //Serial.print(" ℃\t");
    //Serial.print("Humidity: ");
    Serial.print(humidity, 2);
    //Serial.print("% RH");

    Serial.println();

    delay(1000);
  }

 delay(1000);
}

//channel選択のためにregisterに書き込む内容を作る!! //
uint8_t channel_code(uint8_t ch)
{
  uint8_t nana;
  nana  = ch & 7;  //and➡&

  uint8_t hachi;
  hachi = nana | 8;  //or➡|

  return hachi;
}

//channel変える関数 //アドレスにchannel_codeを送る
void switch_channel(uint8_t ch)
{
  uint8_t nextnana;
  nextnana = channel_code(ch);

  Wire.beginTransmission(ADDRESS);
  Wire.write (nextnana);
  Wire.endTransmission();
}







