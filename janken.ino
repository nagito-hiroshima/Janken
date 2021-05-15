int g = 13; //グースイッチの宣言
int c = 12; //チョキスイッチの宣言
int p = 11;  //パースイッチの宣言
int gl =A2;  //グーLEDの宣言
int cl =A1;  //チョキEDの宣言
int pl =A0;  //パーLEDの宣言
#include "SoftwareSerial.h"
#include "DFPlayer_Mini_Mp3.h"


int cgl=A5;
int ccl=A4;
int cpl=A3;
int one=1,loopp,chages,mp3=1;
int kati=9;
int make=10;

void setup() {
  // put your setup code here, to run once:
 pinMode(g,INPUT_PULLUP);
 pinMode(c,INPUT_PULLUP);
 pinMode(p,INPUT_PULLUP);
 pinMode(gl,OUTPUT);
 pinMode(cl,OUTPUT);
 pinMode(pl,OUTPUT);
 pinMode(cgl,OUTPUT);
 pinMode(ccl,OUTPUT);
 pinMode(cpl,OUTPUT);
 pinMode(2,INPUT_PULLUP);
 pinMode(3,INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(3),reset,FALLING);
 attachInterrupt(digitalPinToInterrupt(2),chage,FALLING);
 pinMode(kati,OUTPUT);
 pinMode(make,OUTPUT);
 pinMode(4,INPUT_PULLUP);
 if (digitalRead(4) == LOW)
  { chages = 1;
   }else{
    one = 999;
   }

  Serial.begin (9600);
  mp3_set_serial (Serial);  //set Serial for DFPlayer-mini mp3 module 
  mp3_set_volume (20); //0-30　音量


}

void loop() {
  if (loopp == 0){
    lloop(); 
    }
    
  if(mp3 == 1 &&one >=1)
  {
    mp3_play(1);
    mp3 =2;
  }


  
  if (one >= 1){
    if (digitalRead(g) == LOW) {
      
      loopp =1;
      one = one-1;
      Gu();
      
      
      

    }
    if (digitalRead(c) == LOW ) {
      
      loopp =1;
      one = one-1;
      Choki();
      
    }
    if (digitalRead(p) == LOW) {
      
      loopp =1;
      one = one-1;
      Pa();
      
    }
    
   }
   else{
    loopp =1;
    mp3=1;
   }
   
  }
void reset(){
  loopp = 0;
  one =1;
  digitalWrite(gl,LOW);
  digitalWrite(cl,LOW);
  digitalWrite(pl,LOW);
  digitalWrite(kati,LOW);
  digitalWrite(make,LOW);
  }
void chage(){
  one = one+chages;
  loopp = 0;
  digitalWrite(gl,LOW);
  digitalWrite(cl,LOW);
  digitalWrite(pl,LOW);
  digitalWrite(kati,LOW);
  digitalWrite(make,LOW);
  
}
void lloop(){
  digitalWrite(cgl,HIGH);
  delay(40);
  digitalWrite(cgl,LOW);
  digitalWrite(ccl,HIGH);
  delay(40);
  digitalWrite(ccl,LOW);
  digitalWrite(cpl,HIGH);
  delay(40);
  digitalWrite(cpl,LOW);
  }

void Gu(){
  mp3_play(2);
  int CPU=random(3); //ランダム生成器
  digitalWrite(gl,HIGH);//自分の出した手のライトを点灯
  
  if ( CPU == 0){//グーあいこ
    digitalWrite(cgl,HIGH);//CPUの手のライトを点灯
    delay(1000);
    mp3_play(3);
    digitalWrite(gl,LOW);//あいこのため再試合
    digitalWrite(cgl,LOW);
    one = one+1;
    loopp =0;
  } 
  if (CPU ==1){//チョキ　勝ち
    digitalWrite(ccl,HIGH);
    win();
  }
  if (CPU ==2){//パー　負け
    digitalWrite(cpl,HIGH);
    lose();
  }
}

void Choki(){
  mp3_play(2);
  int CPU=random(3); //ランダム生成器
  digitalWrite(cl,HIGH);//自分の出した手のライトを点灯
  
  if ( CPU == 0){//グー　負け
    digitalWrite(cgl,HIGH);//CPUの手のライトを点灯
    lose();
  } 
  if (CPU ==1){//チョキ　あいこ
    digitalWrite(ccl,HIGH);
    delay(1000);
    mp3_play(3);
    digitalWrite(cl,LOW);//あいこのため再試合
    digitalWrite(ccl,LOW);
    one = one+1;
    loopp =0;
  }
  if (CPU ==2){//パー　勝ち
    digitalWrite(cpl,HIGH);
    win();
  }
}

void Pa(){
  mp3_play(2);
  int CPU=random(3); //ランダム生成器
  digitalWrite(pl,HIGH);//自分の出した手のライトを点灯
  
  if ( CPU == 0){//グー　勝ち
    digitalWrite(cgl,HIGH);//CPUの手のライトを点灯
    win();
  } 
  if (CPU ==1){//チョキ　負け
    digitalWrite(ccl,HIGH);
    lose();
  }
  if (CPU ==2){//パー　あいこ
    digitalWrite(cpl,HIGH);
    delay(1000);
    mp3_play(3);
    digitalWrite(pl,LOW);//あいこのため再試合
    digitalWrite(cpl,LOW);
    one = one+1;
    loopp =0;
  }
}

void win(){
  
  delay(1000);
  mp3_play(5);
  digitalWrite(kati,HIGH);
  delay(4000);
  loopp = 0;
  digitalWrite(gl,LOW);
  digitalWrite(cl,LOW);
  digitalWrite(pl,LOW);
  digitalWrite(kati,LOW);
  if(one >=1){
    mp3=1;
  }
  
  
  
  
}
void lose(){
  
  delay(1000);
  mp3_play(4);
  digitalWrite(make,HIGH);
  delay(4500);
  loopp = 0;
  digitalWrite(gl,LOW);
  digitalWrite(cl,LOW);
  digitalWrite(pl,LOW);
  digitalWrite(make,LOW);
  if(one >=1){
    mp3=1;
  }
  
  
  }
