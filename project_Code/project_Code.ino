#include "LiquidCrystal.h"

LiquidCrystal lcd(0,1,10,11,12,13);


byte h=0,v=0;   
const unsigned long period=50; 
unsigned long kdelay=0;      
const byte rows=4;     
const byte columns=4;           
const byte Output[rows]={2,3,4,5}; 
const byte Input[columns]={6,7,8,9}; 

String inString="";
int amount = 0;
bool reIndicator = true;
int time =0;

//Measuring Voltage
#define NUM_SAMPLES 10
int sum = 0;                  
unsigned char sample_count = 0; 
float voltage = 0.0;     


byte keypad() 
{
 static bool no_press_flag=0;  
  for(byte x=0;x<columns;x++)  
  {
     if (digitalRead(Input[x])==HIGH);   
     else
     break;
     if(x==(columns-1))   
     {
      no_press_flag=1;
      h=0;
      v=0;
     }
  }
  if(no_press_flag==1)
  {
    for(byte r=0;r<rows;r++) 
    digitalWrite(Output[r],LOW);
    for(h=0;h<columns;h++)  
    {
      if(digitalRead(Input[h])==HIGH)
      continue;
      else    
      {
          for (v=0;v<rows;v++)   
          {
          digitalWrite(Output[v],HIGH);   
          if(digitalRead(Input[h])==HIGH)  
          {
            no_press_flag=0;               
            for(byte w=0;w<rows;w++)
            digitalWrite(Output[w],LOW);
            return v*4+h; 
          }
          }
      }
    }
  }
 return 50;
}
void setup() 
{
  
  for(byte i=0;i<rows;i++) 
  {
  pinMode(Output[i],OUTPUT);
  }
  for(byte s=0;s<columns;s++)  
  {
    pinMode(Input[s],INPUT_PULLUP);
  }
  //Serial.begin(9600); 
  lcd.begin(16,2);
}
void loop()
{ 


     while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A2);
        sample_count++;
        delay(10);
    }
  
    voltage = ((float)sum / (float)NUM_SAMPLES * 5.015) / 1024.0;
  
    Serial.print(voltage * 11.132);
    //Serial.println (" V");
    lcd.print("(");
    lcd.print(voltage * 11.132);
    lcd.print("V)");
    //delay(500);
    sample_count = 0;
    sum = 0;


  
    
  if(reIndicator == true)
  {
   
    lcd.setCursor(0,0);
    lcd.print("Entr Bt%:");
    
    if(millis()-kdelay>period) 
      {
        kdelay=millis();  
    switch (keypad())  
       {
                case 0:
               // Serial.println(1);
                inString=inString+"1";
                lcd.setCursor(0,1);
                lcd.print(inString);
           break;  
                case 1:
               // Serial.println(2);
                inString=inString+"2";
                lcd.setCursor(0,1);
                lcd.print(inString);
           break;
                case 2:
               // Serial.println(3);
                inString=inString+"3";
                lcd.setCursor(0,1);
                lcd.print(inString);
           break;
                case 3:
               // Serial.println("F1");
                amount = inString.toInt();
                reIndicator = false;           
           break;
                case 4:
               // Serial.println(4);
                inString=inString+"4";
                lcd.setCursor(0,1);
                lcd.print(inString);
           break;
                case 5:
             //   Serial.println(5);
                inString=inString+"5";
                lcd.setCursor(0,1);
                lcd.print(inString);
           break;
                case 6:
             //   Serial.println(6);
                inString=inString+"6";
                lcd.setCursor(0,1);
                lcd.print(inString);
           break;
                case 7:
            //    Serial.println("F2");
           break;
                case 8:
             //   Serial.println(7);
                inString=inString+"7";
                lcd.setCursor(0,1);
                lcd.print(inString);
           break;
                case 9:
             //   Serial.println(8);
                inString=inString+"8";
                lcd.setCursor(0,1);
                lcd.print(inString);
           break;
                case 10:
            //    Serial.println(9);
                inString=inString+"9";
                lcd.setCursor(0,1);
                lcd.print(inString);
           break;
                case 11:
             //   Serial.println("F3");
           break;
                case 12:
              //  Serial.println("Mode");
           break;
                case 13:
              //  Serial.println(0);
                inString=inString+"0";
                lcd.setCursor(0,1);
                lcd.print(inString);
           break;
                case 14:
               // Serial.println("Cancel");
           break;
                case 15:
               // Serial.println("Enter");
           break;
                default:
                ;
        }
      }    
  }
  else{
     lcd.clear();    
     lcd.setCursor(0,0);
     lcd.print("Batry%:");
     lcd.print(amount);
    
     time = 166 - (1.66*amount);
     lcd.setCursor(0,1);
     lcd.print("Time Rem:");
     lcd.print(time);
     delay(1000);
  }  
}
