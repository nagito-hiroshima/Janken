//ユーザー側宣言
int g = 13; //グースイッチピン宣言
int c = 12; //チョキスイッチピン宣言
int p = 11; //パースイッチピン宣言
int gLED =A2; //グーLEDピン宣言
int cLED =A1; //チョキEDピン宣言
int pLED =A0; //パーLEDピン宣言

//CPU側宣言
int cgLED=A5; //コンピューターグーLEDピン宣言
int ccLED=A4; //コンピューターチョキLEDピン宣言
int cpLED=A3; //コンピューターパーLEDピン宣言

//システム宣言
#include "SoftwareSerial.h" //シリアル通信
#include "DFPlayer_Mini_Mp3.h" //DFPlayer用ライブラリ
int credit=1,wait,chages,playmusic=1;
int WinLED=9; //勝利判定LEDピン宣言
int LoseLED=10; //敗北判定LEDピン宣言

void setup() {
 pinMode(g,INPUT_PULLUP);
 pinMode(c,INPUT_PULLUP);
 pinMode(p,INPUT_PULLUP);
 pinMode(gLED,OUTPUT);
 pinMode(cLED,OUTPUT);
 pinMode(pLED,OUTPUT);
 pinMode(cgLED,OUTPUT);
 pinMode(ccLED,OUTPUT);
 pinMode(cpLED,OUTPUT);
 pinMode(WinLED,OUTPUT);
 pinMode(LoseLED,OUTPUT);
 pinMode(2,INPUT_PULLUP);
 pinMode(3,INPUT_PULLUP);
 pinMode(4,INPUT_PULLUP);//ゲームモード切り替えスイッチ（毎回チャージ必須・無限）

 attachInterrupt(digitalPinToInterrupt(3),reset,FALLING); //リセットボタン（クレジットクリア）
 attachInterrupt(digitalPinToInterrupt(2),chage,FALLING); //クレジットボタン
 
 Serial.begin (9600);
  mp3_set_serial (Serial);  //set Serial for DFPlayer-mini mp3 module 
  mp3_set_volume (20); //0-30　音量
 
 if (digitalRead(4) == LOW)//ゲームモード判定
  { chages = 1; //１チャージで遊べる回数
   }else{
    credit = 9999; //無限回数
   }
}


void loop() {
  if (wait == 0){
    COMLED(); //CPUのLEDを高速点灯させる waitが１になるまで　
    }    
  
  if(playmusic == 1 &&credit >=1)//「じゃんけん」を言ってない＆creditが１以上
  {
    mp3_play(1); //ファイル１を再生
    playmusic =2; //再生を一回だけ
  }

  if (credit >= 1){ //creditがある時
    if (digitalRead(g) == LOW) { //グーが押された時
      wait =1; //COMLEDを高速点灯させない
      credit = credit-1; //creditを一回使用
      Gu(); //グー処理
      }
    
    if (digitalRead(c) == LOW ) { //チョキが押された時
      wait =1;
      credit = credit-1;
      Choki();
      }
    
    if (digitalRead(p) == LOW) { //パーが押された時
      wait =1;
      credit = credit-1;
      Pa();
      }

    }else{ //creditが無くなったら
      wait =1; //高速点灯はしない
      playmusic=1; //「じゃんけん」を言わない
    }
}

void reset(){ //リセットボタン
  wait = 0; //高速点灯処理初期化
  credit =1; //credit初期化
  digitalWrite(gLED,LOW);
  digitalWrite(cLED,LOW);
  digitalWrite(pLED,LOW);
  digitalWrite(WinLED,LOW);
  digitalWrite(LoseLED,LOW);
}

void chage(){ //チャージ処理
  credit = credit+chages; //既存のcreditにChage回加算
  wait = 0; //高速点灯処理初期化
  digitalWrite(gLED,LOW);
  digitalWrite(cLED,LOW);
  digitalWrite(pLED,LOW);
  digitalWrite(WinLED,LOW);
  digitalWrite(LoseLED,LOW); 
}

void COMLED(){//高速点灯処理
  digitalWrite(cgLED,HIGH);
  delay(40);
  digitalWrite(cgLED,LOW);
  digitalWrite(ccLED,HIGH);
  delay(40);
  digitalWrite(ccLED,LOW);
  digitalWrite(cpLED,HIGH);
  delay(40);
  digitalWrite(cpLED,LOW);
}

void Gu(){
  mp3_play(2);
  int CPU=random(3); //ランダム生成器
  digitalWrite(gLED,HIGH);//自分の出した手のライトを点灯
  
  if ( CPU == 0){//グーあいこ
    digitalWrite(cgLED,HIGH);//CPUの手のライトを点灯
    delay(1000);
    mp3_play(3);
    digitalWrite(gLED,LOW);//あいこのため再試合
    digitalWrite(cgLED,LOW);
    credit = credit+1;
    wait =0;
  } 
  if (CPU ==1){//チョキ　勝ち
    digitalWrite(ccLED,HIGH);
    win();
  }
  if (CPU ==2){//パー　負け
    digitalWrite(cpLED,HIGH);
    lose();
  }
}

void Choki(){
  mp3_play(2);
  int CPU=random(3); //ランダム生成器
  digitalWrite(cLED,HIGH);//自分の出した手のライトを点灯
  
  if ( CPU == 0){//グー　負け
    digitalWrite(cgLED,HIGH);//CPUの手のライトを点灯
    lose();
  } 
  if (CPU ==1){//チョキ　あいこ
    digitalWrite(ccLED,HIGH);
    delay(1000);
    mp3_play(3);
    digitalWrite(cLED,LOW);//あいこのため再試合
    digitalWrite(ccLED,LOW);
    credit = credit+1;
    wait =0;
  }
  if (CPU ==2){//パー　勝ち
    digitalWrite(cpLED,HIGH);
    win();
  }
}

void Pa(){
  mp3_play(2);
  int CPU=random(3); //ランダム生成器
  digitalWrite(pLED,HIGH);//自分の出した手のライトを点灯
  
  if ( CPU == 0){//グー　勝ち
    digitalWrite(cgLED,HIGH);//CPUの手のライトを点灯
    win();
  } 
  if (CPU ==1){//チョキ　負け
    digitalWrite(ccLED,HIGH);
    lose();
  }
  if (CPU ==2){//パー　あいこ
    digitalWrite(cpLED,HIGH);
    delay(1000);
    mp3_play(3);
    digitalWrite(pLED,LOW);//あいこのため再試合
    digitalWrite(cpLED,LOW);
    credit = credit+1;
    wait =0;
  }
}

void win(){//勝利処理  
  delay(1000);
  mp3_play(5);
  digitalWrite(WinLED,HIGH);
  delay(4000);
  wait = 0;
  digitalWrite(gLED,LOW);
  digitalWrite(cLED,LOW);
  digitalWrite(pLED,LOW);
  digitalWrite(WinLED,LOW);
  if(credit >=1){
    playmusic=1;
  }
}

void lose(){
  delay(1000);
  mp3_play(4);
  digitalWrite(LoseLED,HIGH);
  delay(4500);
  wait = 0;
  digitalWrite(gLED,LOW);
  digitalWrite(cLED,LOW);
  digitalWrite(pLED,LOW);
  digitalWrite(LoseLED,LOW);
  if(credit >=1){
    playmusic=1;
  }
}
