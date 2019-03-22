#include "Time_Manager.h"

u8 Time_temp[8]={0,0,0,0,0,0,0,0};  //空年月日时分秒周
/**----------------------------------------------------------------***/
void Show_Time(u16 x,u16 y,u8 En)
{
    static u8 a,flag_1=1,flag_2=1;
    u8 i,Set=0;
     char *day[]={"Zero","Monday   ","Tuesday  ","Wednesday","Thursday ","Friday   ","Saturday ","Sunday   "};
    Time_changer(Time_temp);    
    if(En)  flag_1=1;       
    else    flag_2=1; 
          
    if(flag_1==1&&flag_2==1)   //标志一次来确定是否刷新
    {       
        if(En==1) flag_2=0;
        if(En!=1) flag_1=0;    
        a=Time_temp[6];flag_1=0;
    /*============时钟框架=========================================*/    
        POINT_COLOR=LIGHTBLUE;	//前后背景颜色    
        for(i=0;i<9;i++)
            Draw_Circle(120,160,90-i);
        Draw_PointCircle(120,160, 70,4);
    /*=====================================================*/      
    }
    if(Time_temp[6]==a||En!=1)
    {
        a++;if(a>=60) a=0;
        BACK_COLOR=BLACK;   //前后背景颜色
    //////////////////数字时钟///////////////////////////////////////    
        POINT_COLOR=BLUE;	//前后背景颜色
        LCD_Show2Num(x-40,y+90,Time_temp[4],2); //时
        LCD_ShowWords(x-20,y+90,":");
        POINT_COLOR=RED;	//前后背景颜色
        LCD_Show2Num(x-10,y+90,Time_temp[5],2); //分
        LCD_ShowWords(x+10,y+90,":");
        POINT_COLOR=GREEN;	//前后背景颜色
        LCD_Show2Num(x+20,y+90,Time_temp[6],2); //秒

        LCD_ShowWords(x-80,y+110,"20");
        LCD_Show2Num(x-60,y+110,Time_temp[1],2); //年
        LCD_ShowWords(x-40,y+110,"-");    
        LCD_Show2Num(x-30,y+110,Time_temp[2],2); //月
        LCD_ShowWords(x-10,y+110,"-"); 
        LCD_Show2Num(x,y+110,Time_temp[3],2); //日
        POINT_COLOR=MAGENTA;	//前后背景颜色     
        LCD_ShowString(x+30,y+110,day[Time_temp[7]]); //周        
    //////////////////指针时钟////////////////////////////////////    
        LCD_TimeHour(x,y,70,Time_temp[4],Time_temp[5]);
        LCD_TimeMinute(x,y,70,Time_temp[5]);   
        LCD_TimeSecond(x,y,70,Time_temp[6]);
    }
}
/**----------------------------------------------------------------***/


/* --------------画秒指针------------------------------- */
void LCD_TimeSecond(u16 x0,u16 y0,u8 r,u8 i)
{
	POINT_COLOR=BACK_COLOR;	//前后背景颜色
    LCD_DrawLine(x0,y0,(x0+(r-14)*cos((2*Pi/60)*(i-1)-Pi/2)),(y0+(r-14)*sin(S_uni*(i-1)-Pi/2)));
    POINT_COLOR=GREEN;	//前背景颜色
    LCD_DrawLine(x0,y0,(x0+(r-14)*cos(S_uni*i-Pi/2)),(y0+(r-14)*sin(S_uni*i-Pi/2)));
}
/*---------------画分指针---------------------------------*/

/****此处要注意一些数学换算 sin cos
*****同时也要为了减少数学运算，以增加效率****/
void LCD_TimeMinute(u16 x0,u16 y0,u8 r,u8 i)
{
    u16 a0,b0,a1,b1;
    u8 j;
    for(j=0;j<3;j++)
    {
        POINT_COLOR=BACK_COLOR;	//前后背景颜色
        a1=(u16)(x0-j*cos(S_uni*(i-1)));//换算同理得
        b1=(u16)(y0-j*sin(S_uni*(i-1)));       
        LCD_DrawLine(a1,b1,(u16)(a1+(r-25)*cos(S_uni*(i-1)-Pi/2)) ,(u16)(b1+(r-25)*sin(S_uni*(i-1)-Pi/2)) );
        
        POINT_COLOR=RED;	//前后背景颜色
        a0=(u16)(x0-j*cos(S_uni*i)); //换算前 a0=(u16)(x0+j*cos((2*Pi/60)*i-Pi));
        b0=(u16)(y0-j*sin(S_uni*i));//换算前 b0=(u16)(y0+j*sin((2*Pi/60)*i-Pi));    
//        a1=a0+(r-25)*cos((2*Pi/60)*i-Pi/2);
//        b1=b0+(r-25)*sin((2*Pi/60)*i-Pi/2);
        LCD_DrawLine(a0,b0, (u16)(a0+(r-25)*cos(S_uni*i-Pi/2)) , (u16)(b0+(r-25)*sin(S_uni*i-Pi/2)) );
    }
}
/*---------------画 时 指针---------------------------------*/

/****此处要注意一些数学换算 sin cos
*****同时也要为了减少数学运算，以增加效率****/
void LCD_TimeHour(u16 x0,u16 y0,u8 r,u8 i,u8 m)
{
    u16 a0,b0,a1,b1;
    u8 j;
    for(j=0;j<5;j++)
    {
        POINT_COLOR=BACK_COLOR;	//前后背景颜色
        a1=(u16)(x0-j*cos(H_uni(i-1,m)));//换算同理得
        b1=(u16)(y0-j*sin(H_uni(i-1,m)));       
        LCD_DrawLine(a1,b1,(u16)(a1+(r-35)*cos(H_uni(i-1,m)-Pi/2)) ,(u16)(b1+(r-35)*sin(H_uni(i-1,m)-Pi/2)) );
        //LCD_DrawLine((u16)(x0+j*cos(*(i-1))),(u16)(y0+j*sin(H_uni*(i-1))),(u16)(a1-(r-35)*cos(H_uni*(i-1)+Pi/2)) ,(u16)(b1-(r-35)*sin(S_uni*(i-1)+Pi/2)) );

        POINT_COLOR=BLUE;	//前后背景颜色
        a0=(u16)(x0-j*cos(H_uni(i,m))); //换算前 a0=(u16)(x0+j*cos((2*Pi/60)*i-Pi));
        b0=(u16)(y0-j*sin(H_uni(i,m)));//换算前 b0=(u16)(y0+j*sin((2*Pi/60)*i-Pi));    
//        a1=a0+(r-25)*cos((2*Pi/60)*i-Pi/2);
//        b1=b0+(r-25)*sin((2*Pi/60)*i-Pi/2);
        LCD_DrawLine(a0,b0, (u16)(a0+(r-35)*cos(H_uni(i,m)-Pi/2)) , (u16)(b0+(r-35)*sin(H_uni(i,m)-Pi/2)) );        
        //LCD_DrawLine((u16)(x0+j*cos(H_uni*i)),(u16)(y0+j*sin(H_uni*i)), (u16)(a0-(r-30)*cos(H_uni*i+Pi/2)) , (u16)(b0-(r-30)*sin(H_uni*i+Pi/2)) );
    }
}
/**----------------------------------------------------------------***/

void My_TimeSet(void)
{
    u8 i,kval,Sflag=1,Settime=0;
    
    LCD_Fill(4,4,236,290,BLACK);
    Show_Time(120,160,1);
    
    Ds1302_Write_Byte(ds1302_control_add,0x00);			//关闭写保护 
    Ds1302_Write_Byte(ds1302_sec_add,0x80);				//暂停秒钟
    
    while(1)
    {
        kval=Key_Scan();
        
        if(kval==1) 
        {
            Sflag++;if(Sflag>=7) Sflag=1;
        }
        switch(Sflag)
        {
            case 1:     if(kval==3)
                            {i=1;Settime=1;} 
                        else if(kval==4)
                            {i=2;Settime=1;}   
                        break;
            case 2:     if(kval==3)
                            {i=3;Settime=1;} 
                        else if(kval==4)
                            {i=4;Settime=1;}   
                        break;  
            case 3:     if(kval==3)
                            {i=5;Settime=1;}
                        else if(kval==4)
                            {i=6;Settime=1;}   
                        break; 
            case 4:     if(kval==3)
                            {i=7;Settime=1;}
                        else if(kval==4)
                            {i=8;Settime=1;}   
                        break;   
            case 5:     if(kval==3)
                            {i=9;Settime=1;} 
                        else if(kval==4)
                            {i=10;Settime=1;}   
                        break;   
            case 6:     if(kval==3)
                            {i=11;Settime=1;} 
                        else if(kval==4)
                            {i=12;Settime=1;}   
                        break;                             
        }
        
       if(Settime==1)
       { 
           Settime=0; Set_time(i);
            Show_Time(120,160,0);
       }
        
        if(kval==2) 
         {
            Ds1302_Write_Byte(ds1302_control_add,0x00);			//关闭写保护 
            Ds1302_Write_Byte(ds1302_sec_add,0x00);				//打开 秒钟
            LCD_Fill(4,4,236,290,BLACK); 
            return;//检测到键盘2后，清屏直接退出
         }  
        kval=0;
    }
    
}
/**----------------------------------------------------------------***/

