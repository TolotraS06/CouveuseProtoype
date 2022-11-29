
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define MAX_TEMP 37.5
#define MAX_HUM  50

#define LUM_PORT 10
#define DHT_PORT 5

DHT dht (DHT_PORT,DHT11);
LiquidCrystal_I2C lcd (0x27,16,2);

float hum_ = NAN;
float temp_= NAN;

void setup() {
  // put your setup code here, to run once:
  pinMode(LUM_PORT,OUTPUT);

  lcd.init();
  lcd.begin(16,2,13);
  lcd.backlight ();
  lcd.cursor();
  dht.begin ();  
   
  Serial.begin(9600);
}

void loop() {
 // put your main code here, to run repeatedly:
  Dht_sensor();
  display_data();
}

void Dht_sensor (){
    temp_ = dht.readTemperature (false);
    hum_ = dht.readHumidity ();
    
    Serial.print("temp: ");
    Serial.println(temp_);
    
    Serial.print(" hum: ");
    Serial.println(hum_);
    
    if (temp_ != NAN)  {                     
      if (temp_ > MAX_TEMP)
        digitalWrite (LUM_PORT,LOW);
      else
        digitalWrite (LUM_PORT,HIGH);
    } 
}

void display_data (){
   for (int i = 0; i < 10; i++)  { 

      if (temp_ != NAN){
        lcd.setCursor(0, 0);
        lcd.print("temp : ");
        lcd.print (temp_);
      }
      else{
        lcd.setCursor(0,0);
        lcd.print("TEMP READ ERROR");
      }
      
      if (hum_ != NAN){                 
        lcd.setCursor(0,1);
        lcd.print("hum  : ");
        lcd.print (hum_);   
      } 
      else{
        lcd.setCursor(0,1);
        lcd.print("HUM READ ERROR");
      }
      delay (100);
      
    }
}






