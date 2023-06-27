#include<Wire.h>
#define ADDRESS 0x70  //1110000→16進数に
#include <stdint.h>
#include <AHT20.h>
AHT20 aht20_0; //あ
AHT20 aht20_1; //い
AHT20 aht20_2; //う
AHT20 aht20_3; //え
AHT20 aht20_4; //お


//あ～おのモジュールを起動
void setup() {
  // put your setup code here, to run once:  
  Wire.begin();
  Serial.begin(115200);

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

  switch_channel(3); //channelを3にした
  if(aht20_3.begin() == false)
  {
    Serial.println("え not detected. Please check wiring. Freezing.");
  }  

  switch_channel(4); //channelを4にした
  if(aht20_4.begin() == false)
  {
    Serial.println("お not detected. Please check wiring. Freezing.");
  }  


}


void loop() {
  // put your main code here, to run repeatedly:
  switch_channel(0);
  if (aht20_0.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20_0.getTemperature();
    float humidity = aht20_0.getHumidity();

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
  }

  switch_channel(1);
  if (aht20_1.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20_1.getTemperature();
    float humidity = aht20_1.getHumidity();

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
  }

  switch_channel(2);
  if (aht20_2.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20_2.getTemperature();
    float humidity = aht20_2.getHumidity();

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
  }

  switch_channel(3);
  if (aht20_3.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20_3.getTemperature();
    float humidity = aht20_3.getHumidity();

    //Print the results
    Serial.print("え,");
    //Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.print(",");
    //Serial.print(" ℃\t");
    //Serial.print("Humidity: ");
    Serial.print(humidity, 2);
    //Serial.print("% RH");

    Serial.println();
  }

  switch_channel(4);
  if (aht20_4.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = aht20_4.getTemperature();
    float humidity = aht20_4.getHumidity();

    //Print the results
    Serial.print("お,");
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
