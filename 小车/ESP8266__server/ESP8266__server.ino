#include <ESP8266WiFi.h>

const char *ssid     = "515znb";
const char *password = "515znbqs";

WiFiServer server(8266); //建立服务器对象，设置监听端口号为8266

void setup()
{
  Serial.begin(9600);
  Serial.println();

  Serial.printf("Connecting to %s $", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WIFI connected$");

  server.begin();
  Serial.print("IP:");
  Serial.print(WiFi.localIP());
  Serial.print("$");
}

void loop()
{
  WiFiClient client = server.available(); //尝试建立客户对象
  if (client) //如果当前有客户可用
  {
    
    Serial.print("connected");
    Serial.print("$");
    
    while (client.connected()) //如果客户端建立连接
    {
      if (client.available()) //等待有可读数据
      {
        Serial.write(client.read());
      }
      if (Serial.available())//串口读取到的转发到wifi，因为串口是一位一位的发送所以在这里缓存完再发送
      {
        size_t counti = Serial.available();
        uint8_t sbuf[counti];
        Serial.readBytes(sbuf, counti);
        client.write(sbuf, counti);
      }
    }
    delay(1); //等待客户完成接收
    client.stop(); //结束当前连接:
    
    Serial.print("disconnected");
    Serial.print("$");
  }
}
