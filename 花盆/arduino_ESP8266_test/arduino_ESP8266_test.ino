#define SSID        "515znb"            //WIFI 名
#define PASSWORD    "515znbqs"          //WIFI 密码
#define HOST_NAME   "192.168.1.181"     //连接服务器的 IP
#define HOST_PORT    "8989"             //连接服务器的 端口
#define onnet_NAME   "jjfaedp.hedevice.com"  //
#define onenet_PORT  "876"              //
#define wifi_uart    Serial1           //arduino与esp8266通信串口

String comdata="";

void setup(){
  Serial.begin(9600);
  wifi_uart.begin(115200);
  Serial.flush();
  wifi_uart.flush();
  Serial.println("setup begin");
  close_connect();
  Serial.println("setup finished");
}

void loop() {
  if(wifi_uart.available() > 0)
  {
    return_data();
  }
  else if(Serial.available() > 0)
  {
    send_data();
  }
}

/*
 * 将esp8266接入路由器
 */
int join_wifi()
{
  wifi_uart.flush();
  wifi_uart.write("AT+CWMODE=1\r\n");
  if(!return_data());
  wifi_uart.write("AT+CWJAP=\""SSID"\",\""PASSWORD"\"\r\n");
  if(!return_data());
  wifi_uart.write("AT+CIFSR\r\n");
  if(!return_data());
  return 1;
}

/*
 * 与服务器连接并开启透传
 */
int connect_to_server()
{
  wifi_uart.write("AT+CIPMUX=0\r\n");
  if(!return_data());
  wifi_uart.write("AT+CIPMODE=1\r\n");
  if(!return_data());
  wifi_uart.write("AT+CIPSTART=\"TCP\",\""HOST_NAME"\","HOST_PORT"\r\n");
  if(!return_data());
  wifi_uart.write("AT+CIPSEND\r\n");
  if(!return_data());
  return 1;
}

/*
 * 关闭与服务器的连接
 */
void close_connect()
{
  wifi_uart.println("begin close");
  delay(200);
  wifi_uart.print("+++");
  delay(200);
  wifi_uart.println();
  wifi_uart.write("AT+CIPCLOSE\r\n");
  delay(2000);
  if(!return_data());
  wifi_uart.write("AT+CIPMODE=0\r\n");
  if(!return_data());
  wifi_uart.write("AT+SAVETRANSLINK=0\r\n");
  if(!return_data());
 }

/*
 * 打印esp8266从服务器端接收到的信息，若没有信息返回0，打印成功返回1
 */
int return_data()
{
  int flag = 0;
  int return_flag = 0;
  String getdata="";
  delay(200);
  if(wifi_uart.available() > 0)
  {
    delay(100);
    getdata=wifi_uart.readString();
    flag = 1;
  }
  if(flag == 1)
  {
    if(getdata == "OK" || getdata == "ERROR")
    {
      return_flag = 1;
    }
  }
  if(getdata == "close")
  {
    close_connect();
  }
  if(flag)
  {
    Serial.print("readString:");
    Serial.println(getdata);
  }
  return return_flag;
}

/*
 * 读取电脑信息通过esp8266打印到服务器端
 */
void send_data()
{
  if(Serial.available()>0)
  {
    delay(100);
    comdata = Serial.readString();
    Serial.print("sendString:");
    Serial.println(comdata);
  }
  if(comdata=="close")
  {
    close_connect();
  }
  else if(comdata=="open")
  {
    connect_to_server();
  }
  else if(comdata=="init")
  {
    if(join_wifi())
    {
      Serial.println("join wifi successfully!");
    }
    if(connect_to_server())
    {
      Serial.println("connect successfully!");
    }
  }
  if (comdata.length() > 0)
  {
     wifi_uart.println(comdata);
  }
  comdata = "";
}

