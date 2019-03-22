#define mySerial Serial1

String readString = ""; //建立一个字符串对象用来接收存放来自客户的数据

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("START");
}

/*
 *  输入字符串，确定从第几位开始解析后面多少位
 *  input:需解析的字符串
 *  Matching:匹配样本
 *  num_start:从第几位开始解析（第一位为字符串开始）
 *  flag:输出1为匹配成功，0为失败
 */
bool AnalysisGetString(String input, String Matching, int num_start)
{
  bool flag = 1;
  int len = Matching.length();
  for(int i = 0; i < len; i++)
  {
    if(input[num_start+i-1] != Matching[i])
    {
      flag = 0;
      break;
    }
    else continue;
  }
  return flag;
}

/*
 * 作为Server端向client端通信
 * 方法：client端发送信息后解析信息并返回所需信息
 * 调用serialEvent函数使串口有数据时才进入此段程序
 */
void serialEvent1()
{
  if (mySerial.available())
  {
    char c = mySerial.read(); //读取一字节数据
    if (c == '$')
    {
      Serial.println(readString);
      if(AnalysisGetString(readString, "time", 1))
      {
        mySerial.println("time is:");
        mySerial.print(millis());
        Serial.println(millis());
      }      
      else
      {
        mySerial.println("no");
      }
      mySerial.print('$');
      readString = "";
    }
    else if(c > 31 && c < 127) //包括所有标点，数字，字母
    {
      readString += c; //拼接数据
    }
  }
}

void loop()
{
  
}
