/*

  Udp NTP Client

  Get the time from a Network Time Protocol (NTP) time server
  Demonstrates use of UDP sendPacket and ReceivePacket
  For more on NTP time servers and the messages needed to communicate with them,
  see http://en.wikipedia.org/wiki/Network_Time_Protocol

  created 4 Sep 2010
  by Michael Margolis
  modified 9 Apr 2012
  by Tom Igoe
  updated for the ESP8266 12 Apr 2015
  by Ivan Grokhotkov

  This code is in the public domain.

*/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


unsigned int GetAndDis_time();
void sendNTPpacket(IPAddress& address);

char * ssid = "ESP8266";
char * pass = "990126711008";

unsigned int localPort = 2390;      // local port to listen for UDP packets

/* Don't hardwire the IP address or we won't get the benefits of the pool.
    Lookup the IP address for the host name instead */
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "0.cn.pool.ntp.org";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

int error_i = 0;  //if local_epoch has long time no to be updated,print error
int error_flag = 0;

int conect_i = 0;

unsigned long epoch;

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
}

void loop(){
  if(Serial.read() == 's'){
    unsigned int hmstime = GetAndDis_time();
    Serial.println(hmstime);
    /*
    String HMStime = "";
    if(hmstime != 1)
      HMStime = (String)(CALh(hmstime))+ " : "+ (CALm(hmstime)) +" : "+ (CALs(hmstime));
    else
      HMStime = "ERROR";
    Serial.println(HMStime);
    */
  }
}

unsigned int GetAndDis_time() {
  //get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP);

  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);

  int cb = udp.parsePacket();
  if (!cb) {
    error_i++;
    error_flag = 1;
    } 
   else {
    error_i = 0;
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    epoch = secsSince1900 - seventyYears;
    //peking time
    epoch += 8*3600;
   }
   if(error_flag)
   {
     error_flag = 0;
     if(error_i < 5)
     {
       return epoch;
     }
     else
       return 1;          //抛出-1时说明很久连不上服务器了，该检查下网络了
    }
    else
    {
      return epoch;
    }
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress& address) {
//  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

void readchar(char *zfc){
  int i = 0;
  while(Serial.available() > 0)
  {
    delay(100);
    zfc[i++] = char(Serial.read());
    delay(2);
  }
}

/*
 * 串口读取有问题，以后再搞
 */
void reconect(){
  conect_i++;
    if(conect_i > 15)
    {
      Serial.println("");
      Serial.println("Please Enter ture SSID and PASSWORD:");
      
      Serial.print("SSID:");
      while(Serial.read()>=0){}
      delay(5000);
      readchar(ssid);
      Serial.println("");
      Serial.print("Your new SSID is ");
      Serial.println(ssid);
      
      Serial.print("Password:");
      while(Serial.read()>=0){}
      delay(5000);
      readchar(pass);
      Serial.println("");
      Serial.print("Your new password is ");
      Serial.println(pass);
      conect_i = 0;

      Serial.print("Connecting to ");
      Serial.println(ssid);
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, pass);
    }
  }

unsigned int CALh(unsigned int e)
 {
    unsigned int h = (e  % 86400L) / 3600;
    return h;
 }

 unsigned int CALm(unsigned int e)
 {
    unsigned int m = (e  % 3600) / 60;
    return m;
 }

 unsigned int CALs(unsigned int e)
 {
    unsigned int s =  e  % 60;
    return s;
 }
