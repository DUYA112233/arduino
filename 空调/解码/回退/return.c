#include <stdio.h>
#include <math.h>

#define high 1650
#define low 550

int i;
char input[12];  //输入12个16进制数
int hex12[12];//16进制转换为10进制处理
int hex24[24];  //转换为hex24
int binary[96];//二进制数
int time[197]; //红外高电平持续时间

void hex_extend();
void hexTObinary();
void binaryTOtime();

int main()
{
	scanf("%s", input);
  printf("hex12:\n");
  for(i = 0 ; i < 12 ; i++)
  {
    if(input[i] < 58)
		{
			hex12[i] = input[i]-48;
		}
		else
		{
			hex12[i] = input[i]-55;
		}
		printf("%d ", hex12[i]);
  }
  printf("\n");
	hex_extend();
  hexTObinary();
  binaryTOtime();
}

void hex_extend()
{
	int i;
	for(i = 0 ; i < 12 ; i++)
	{
		if(i%2 == 0)
		{
			hex24[2*i] = hex12[i];
			hex24[2*i+2] = 15-hex12[i];
		}
		else
		{
			hex24[2*i-1] = hex12[i];
			hex24[2*i+1] = 15-hex12[i];
		}
	}
  printf("hex24:\n");
	for(i = 0 ; i < 24 ; i++)
	{
		printf("%d ", hex24[i]);
	}
}

void hexTObinary()
{
  int j;
  printf("binary:\n");
  for(i = 0 ; i < 24 ; i++)
  {
    for(j = 0 ; j < 4 ; j++)
    {
      binary[4*i+j] = 0;  //初始化binary数组
      if(hex24[i] - pow(2, 3-j) >= 0)
      {
        hex24[i] -= pow(2, 3-j);
        binary[4*i+j] = 1;
      }
      printf("%d ", binary[4*i+j]);
    }
  }
}

void binaryTOtime()
{
  time[0] = 6050;
  time[1] = 7350;
  time[194] = low;
  time[195] = 7350;
  time[196] = low;
  printf("\ntime:\n");
  for(i = 2 ; i < 194 ; i += 2)
  {
    if(binary[i/2-1] == 0)
    {
      time[i] = time[i+1] = low;
    }
    else
    {
      time[i] = low;
      time[i+1] = high;
    }
  }
  for(i = 0 ; i < 197 ; i++)
  {
    printf("%d ", time[i]);
  }
}
