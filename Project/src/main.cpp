#include <Arduino.h>
#include <HTTPUpdate.h>

void update();
void setup()
{
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  WiFi.begin("Galaxy A52s 5G D8E1", "gkyy7430");
}

uint32_t updateCounter = 0;

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(13, 1);
  delay(1000);
  digitalWrite(13, 0);
  delay(1000);

  if (WiFi.status() == WL_CONNECTED)
  {
    updateCounter++;
    if (updateCounter > 30)
    {
      updateCounter = 0;
      update();
    }
  }
}

String getChipId()
{
  String ChipIdHex = String((uint32_t)(ESP.getEfuseMac() >> 32), HEX);
  ChipIdHex += String((uint32_t)ESP.getEfuseMac(), HEX);
  return ChipIdHex;
}

void update()
{
  String url = "http://otadrive.com/deviceapi/update?";
  url += "k=2d71f7fb-c099-46d2-a94a-f0d5a4188ca6";
  url += "&v=1.0.0.1";
  url += "&s=" + getChipId();

  WiFiClient client;
  httpUpdate.update(client, url, "1.0.0.2");
}