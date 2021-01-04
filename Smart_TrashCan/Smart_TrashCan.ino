#include <Servo.h> // 모터 헤더
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);



#include "TrashCan.h"

void printInfo(int value, int cnt){
  lcd.clear();
  lcd.print("STATE  :  ");
  lcd.print(value);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("   ");
  for(int i = 0; i < cnt; i++){
    lcd.print(">");  
  }
  
}


void setup() {  
#if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  

  servo.attach(servoPin);
  lcd.backlight();
  delay(15);  
  servo.write(0); 
  lcd.begin();
  Serial.begin(9600);
  //wifi.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(nightled, OUTPUT);
}

void loop() {

  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);
 
  distance = ((float)(340 * duration) / 10000) / 2;
 
  //시리얼모니터에 Echo가 HIGH인 시간 및 거리를 표시해준다.

  /*Serial.print("DIstance: ");
  Serial.print(distance);
  Serial.println("cm");
  delay(50);*/

  if(distance < 40){
        for(; angle < 85; angle++){ 
            servo.write(angle); 
            delay(10); 
        } 
        delay(1000);
  }
  else{
        for(;angle > 0; angle--){ 
          servo.write(angle); 
          delay(15); 
        }  
  }

  digitalWrite(trigPin2, HIGH);
  delay(10);
  digitalWrite(trigPin2, LOW);
 
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = ((float)(340 * duration2) / 10000) / 2;
 
  //시리얼모니터에 Echo가 HIGH인 시간 및 거리를 표시해준다.

  /*Serial.print("inner:");
  Serial.print(distance2);
  Serial.println("cm");
  delay(50);*/
  
  if(distance2 > 30){    
    printInfo(0,0);
  }
  if(distance2 < 27){
    printInfo(10,1);
  }
  if(distance2 < 24){
    printInfo(20,2);
  }
  if(distance2 < 21){
    printInfo(30,3);
  }
  if(distance2 < 18){
    printInfo(40,4);
  }
  if(distance2 < 15){
    printInfo(50,5);
  }
  if(distance2 < 12){
    printInfo(60,6);
  }
  if(distance2 < 9){
    printInfo(70,7);
  }
  if(distance2 < 6){
    printInfo(80,8);
  }
  if(distance2 < 5){
    printInfo(90,9);
  }
  if(distance2 < 3){
    printInfo(100,10);
  }
  
  lightValue = analogRead(light);
  /*Serial.print("light =  ");
  Serial.println(lightValue);*/
  if (lightValue > 50 ) {
      digitalWrite(nightled, HIGH);
     /* Serial.println("LED ON");*/
  }
  else {
      digitalWrite(nightled, LOW);
      /*Serial.println("LED OFF");*/
  }
}
