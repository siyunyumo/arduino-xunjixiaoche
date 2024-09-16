#include <LiquidCrystal_I2C.h>




int starttime;
int buzzerPin=3;
int ledPin=4;
int ENA = 5;
int ENB = 6;
int IN1 = 7;
int IN2 = 8;
int IN3 = 12;
int IN4 = 13;
int IR_LEFT = A3 ;   //D3,绿线5V ，红线GND
int IR_RIGHT = A2;   //D4


int IR_L;

int IR_R;


LiquidCrystal_I2C lcd(0x27,16,2);

/*宏定义小车转向方向*/
#define Forward {digitalWrite(IN1,HIGH);digitalWrite(IN2,LOW);digitalWrite(IN3,LOW);digitalWrite(IN4,HIGH);}    //前进
#define Back {digitalWrite(IN1,LOW);digitalWrite(IN2,HIGH);digitalWrite(IN3,HIGH);digitalWrite(IN4,LOW);}       //后退
#define Right{digitalWrite(IN1,LOW);digitalWrite(IN2,HIGH);digitalWrite(IN3,LOW);digitalWrite(IN4,HIGH);}       //左转
#define Left {digitalWrite(IN1,HIGH);digitalWrite(IN2,LOW);digitalWrite(IN3,HIGH);digitalWrite(IN4,LOW);}      //右转
#define Stop {digitalWrite(IN1,LOW);digitalWrite(IN2,LOW);digitalWrite(IN3,LOW);digitalWrite(IN4,LOW);}         //停止




void setup() {
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  analogWrite(ENA,180);
  analogWrite(ENB,180);
  pinMode(IR_LEFT,INPUT);
  pinMode(IR_RIGHT,INPUT);
  pinMode(buzzerPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
     lcd.backlight();
    
    
   
   lcd.init();
}
void Trackline()  //巡线
{
  IR_L = digitalRead(IR_LEFT);
  IR_R=digitalRead(IR_RIGHT);
 
  if ((IR_L == LOW)&&(IR_R ==LOW)) //直行
  {
    Forward;
    starttime = millis();
    return;
  }
 if ((IR_L == LOW)&&(IR_R == HIGH))  //右转1
  {
    Right;
    return;
  }
 
 if((IR_L== HIGH)&&(IR_R == LOW))  //左转1
   {
    Left;
    return;
   }
 if((IR_L== HIGH)&&(IR_R == HIGH))
   {
    Stop;
    float S = starttime/1000;
    lcd.setCursor(0,0);
    lcd.print(S);
    digitalWrite(buzzerPin,HIGH);
    digitalWrite(ledPin,HIGH);
    delay(5000);
    digitalWrite(buzzerPin,LOW);
    digitalWrite(ledPin,LOW);
    for(;;){}
    }
 
 
 
}
void loop() 
{
    while(1)
    {
      Trackline();
      }    
}
