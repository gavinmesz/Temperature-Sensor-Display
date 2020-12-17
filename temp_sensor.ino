//All code is written by Gavin Mesz
#include <LiquidCrystal.h> 
//lcd library
LiquidCrystal lcd(12,11,5,4,3,2);//initalizes LCD
// numbers mean (rs,enable,d4,d5,d6,d7)
int c=0;
int l=0;
bool done=false; //checks whether it has already printed the temp
bool isF=true;
int F=8;
void setup()
{
  lcd.begin(16,1);
  pinMode(A0,INPUT);
  pinMode(F,INPUT);
  Serial.begin(9600);
}

void loop()
{
  delay(100);
  if(digitalRead(F)==LOW){ //is it fahrenheit?
    isF=false;
    Serial.println("LOW");
  } else{
   isF=true; 
   Serial.println("HIGH");
  }
  Serial.print(analogRead(A0));
  c = map(analogRead(A0),20,358,-40,125);
  if(isF){
    c=c*(9/5)+32;
 }
  //reads temp and turns signal into actual temperature we can measure
  // low: 0,high: 1023 > low: -40,high: 125
  //this is to celsius, thats why the variable is "c"
  if(done==true){
    if(l==c){
    } else{
      lcd.clear();
      done=false;
    }
  }else if(l==c){
    lcd.print("Temp: ");
    lcd.print(c);
    Serial.print("Temp: ");
    Serial.print(c);
    if(isF){
      lcd.print("F");
      Serial.println("F"); 
    }else{
      lcd.print("C");
      Serial.println("C");
    }
    done=true;
  }
  l=c; //records current temp to compare with the next temp
  //sees if it changes
}
