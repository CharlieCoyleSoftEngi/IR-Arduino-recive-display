#include <IRremote.h>
#include <IRremoteInt.h>

#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9         
#define SS_PIN          10
//Libary for RFID https://github.com/miguelbalboa/rfid
//Wireing https://tutorial.cytron.io/wp-content/uploads/2017/08/Photo-3-2.png
//Setting pins for input 
int RECV_PIN = 13;
IRrecv receiver(RECV_PIN);
decode_results results;
int mode = 1;
const int redLed = 3;
const int greenLed = 8;
LiquidCrystal lcd(9, 2, 4, 5, 6, 7);
//Replace later with NFC input
int numOfMins = 10;
String Lable = "Test";
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  receiver.enableIRIn();
  lcd.begin(16,2);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  open();
}

void loop() {
//https://tutorial.cytron.io/2017/08/10/getting-started-mifare-rc522-rfid-kit-rfid-rc522/

    //if reader detects card DO ↓
    if(receiver.decode(&results)){
       receiver.enableIRIn();
    String Message;
    Serial.println(results.value);
    switch(mode) {
      case 1: 
      switch(results.value) {
      case 539956009: Message = "''Short use''"; numOfMins = 2; break; 
      case     1271936904: Message = "''Long use''"; numOfMins = 10; break; 
      case 489623152: Message = "Shower"; numOfMins = 30; break;
      case 2606613234: Modeswitch(); Message = "Mode changed"; numOfMins = 0; break; 
      default: Message = "NullCode"; numOfMins = 1; break;
      }
      break;
       
    
    case 2:
      switch(results.value) {
      case 539956009: Message = "Short Meeting"; numOfMins = 30; break; 
      case     1271936904: Message = "Meeting"; numOfMins = 60; break; 
      case 489623152: Message = "Long Meeting"; numOfMins = 120; break;
      case 2606613234: Modeswitch(); break; 
      default: Message = "NullCode"; numOfMins = 1; break;    
    }
    break;
    
    }
    
    countdown(numOfMins, Message);
    receiver.enableIRIn();//↓
//    int minsCounter = numberOfMins;
//      for (int m = 1; m <= minsCounter; m++) { //m is Minutes
//          for (int i = 1; i <= 60; i++) {//i is seconds
//            lcd.clear();
//            lcd.print(lable + " ");
//            lcd.print(numberOfMins -m );//Time left mins
//            lcd.print(" :");
//            if (i > 50){
//              lcd.print(0);
//              lcd.print(60 - i);
//              }else{
//            lcd.print(60 - i);//Time left Seconds
//              }
//            delay(1000);
//          }
//      }
    }
}
//Number1 = 0x7771
//
//
//
//
//
//

void Modeswitch(){
  switch(mode){
    case 1: mode = 2; break;
    case 2: mode = 1; break; 
    }
  
  }

void countdown(int numberOfMins,String lable){
  digitalWrite(greenLed, LOW);//Change to Read Led
  digitalWrite(redLed, HIGH);
  int minsCounter = numberOfMins;
  int km = 60;
    for (int m = 1; m <= minsCounter; m++) {//m is Minutes
            for (int i = 1; i <= km; i++) {//i is seconds
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(lable + " ");
              lcd.setCursor(0, 1);
              lcd.print(numberOfMins -m );//Time left mins
              lcd.print(":");
              if (i > 50){
                lcd.print(0);
                lcd.print(km - i);
                }else{
              lcd.print(km - i);//Time left Seconds
                }
                if(receiver.decode(&results)){
                numberOfMins = 1;
                minsCounter = 0;
                km = 5;
                lable = "Canceled"; 
                }
              delay(200);
              if(receiver.decode(&results)){
                numberOfMins = 1;
                minsCounter = 0;
                lable = "Canceled"; 
                }
              delay(200);
              if(receiver.decode(&results)){
                numberOfMins = 1;
                minsCounter = 0;
                lable = "Canceled"; 
                }
                delay(200);
              if(receiver.decode(&results)){
                numberOfMins = 1;
                minsCounter = 0;
                lable = "Canceled"; 
                }
                delay(200);
              if(receiver.decode(&results)){
                numberOfMins = 1;
                minsCounter = 0;
                lable = "Canceled"; 
                }
                delay(200);
              if(receiver.decode(&results)){
                numberOfMins = 1;
                minsCounter = 0;
                lable = "Canceled"; 
                }
            }
        }
        open();//↓
//          lcd.clear();
//          lcd.print("Open");
//          digitalWrite(greenLed, HIGH);
//          digitalWrite(redLed, LOW);
//          
}

void open(){//Changes display to open
  lcd.clear();
  switch(mode){
    case 1: lcd.print("Toilet ");break;
    case 2: lcd.print("Meeting room ");break;
    }
  lcd.setCursor(0, 1);
  lcd.print("Open");
  lcd.setCursor(0, 0);
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  delay(1000);
}
