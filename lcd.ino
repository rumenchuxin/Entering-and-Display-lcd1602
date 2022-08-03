#include<LiquidCrystal.h>
int JoyStick_X = 0; //定义PS2摇杆的X轴，ANALOG IN的Pin0
int JoyStick_Y = 1; //定义PS2摇杆的Y轴，ANALOG IN的Pin1
int JoyStick_Z = 8; //定义PS2摇杆的Z轴，接在DIGITAL区域的Pin8
int x,y,z,xr,yr,zr,m;//声明全局变量
char keya[27]={' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};//键盘字库:小写字母
char keyd[27]={' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};//键盘字库:大写字母
char keyb[11]={' ','0','1','2','3','4','5','6','7','8','9'};//键盘字库:数字
char keyc[11]={' ',',','.','?','!',':',';','~','_','-','"'};//键盘字库:符号
char key[1]="r";//当前选中字符
char words[]="                ";
int keys=0;//当前选中键盘
int p=1;//当前选中字符的地址
int t=0;//当前光标所在位置
int st=0;//当前场景
int hidden=0;//信息栏状态:0显示，1隐藏
 LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 // 初始化,设置lcd1602的引脚
 // 1602(RS-4)-pin7、1602(R/W-5)接GND、
 // 1602(E-6)pin 6。 
// 1602(D4-11)-pin 5、1602(D5-12)-pin 4。 
// 1602(D6-13)-pin 3、1602(D7-14)-pin 2。
void setup() {
pinMode(JoyStick_Z, INPUT_PULLUP); //定义PS2的Z轴为输入，按下时触发LED灯亮起的条件
lcd.begin(16,2); // 初始化并设置行和列 
lcd.noCursor();
} 
void ps()
{//摇杆坐标读取
      x=analogRead(JoyStick_X);
      y=analogRead(JoyStick_Y);
      z=digitalRead(JoyStick_Z);
//读取摇杆的x,y阻值和z按键状态
}
void pst(){//按键检测
      xr=0;
      yr=0;
      zr=0;//重置变化量xr yr zr
      if(x<=100){
      xr=1;
      }
      if(x>=900){
      xr=2;
      }
      if(y<=100){
      yr=1;
      }
      if(y>=900){
      yr=2;
      }
//xr 0中间,1右边,2左边
//yr 0中间,1上边,2下边
      if(z==0){
      zr=1;
      while(digitalRead(JoyStick_Z)==0){}//等待按键弹起
      int tick=0;//声明时间变量
      while(tick<=300){
      tick++;
      delay(1);
      z=digitalRead(JoyStick_Z);
      if(z==0){
      zr++;
      while(digitalRead(JoyStick_Z)==0){}
      }
      }
      }
}

void in(){//写模块按键
char* zkey;//声明指针
zkey=key;//定位
if(keys==0){
*(zkey)=keya[p];//更改指针内容
m=26;//键盘最大值
}else if(keys==1){
*(zkey)=keyd[p];
m=26;
}else if(keys==2){
*(zkey)=keyb[p];
m=10;
}else if(keys==3){
*(zkey)=keyc[p];
m=10;
}else{
*(zkey)=keya[p];
m=26;
}
if(xr==1){
if(t>=15){
t=0;
}else{
t=t+1;
}
      while(x<=100){ps();}
}
if(xr==2){
if(t<=0){
t=15;
}else{
t=t-1;
}
      while(x>=900){ps();}
}
if(yr==1){
if(p<=0){
p=m;
}else{
p=p-1;
}
      while(y<=100){ps();}
}
if(yr==2){
if(p>=m){
p=0;
}else{
p=p+1;
}
      while(y>=900){ps();}
}
if(zr==1)
{
words[t]=key[0];
}
if(zr==2){
if(keys>=3){
keys=0;
}else{
keys=keys+1;
}
p=1;
lcd.setCursor(0, 1);
if(keys==0){
lcd.print("\"abc\"");
}else if(keys==1){
lcd.print("\"ABC\"");
}else if(keys==2){
lcd.print("\"123\"");
m=10;
}else if(keys==3){
lcd.print("\",.!\"");
}else{
lcd.print("\"abc\"");
}
      while(z==0){ps();}
}
if(zr==3){
if(hidden==0){
hidden=1;
}else{
hidden=0;
write_r();
}
      while(z==0){ps();}
}
}
void write_r(){//写模块初始化
lcd.clear();
lcd.setCursor(0, 1);
lcd.print("\"abc\"");
lcd.setCursor(10,1); 
lcd.print("Key[");
lcd.setCursor(15,1); 
lcd.print("]");
}

void write() {//写模块
in();
lcd.home();
lcd.print(words);
lcd.setCursor(t, 0);
if(hidden==0){
lcd.setCursor(14, 1);
lcd.print(key[0]);
}else
{
lcd.setCursor(0, 1); // 设置光标第二行，第一列位置。
lcd.print("        By.Rummy");
}
}

void set(){

}
void loop(){
ps();
pst();
if (st==0){
lcd.setCursor(0, 0);
lcd.print("Entering&Display");
lcd.setCursor(1, 1);
lcd.print("v0.1b by.Rummy");
if(zr>=1){
lcd.clear();
st=1;
}
}else if(st==1){
write_r();
while(st==1){
ps();
pst();
write();
}
}else{
lcd.home();
lcd.print("This's a bug.to2");
lcd.setCursor(0,1); 
lcd.print("123435371@qq.com");
}
}