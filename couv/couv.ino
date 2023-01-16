#include <DHT.h>


#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>

/**
     constante      
*/
#define MAX_TEMP 37.9
#define MIN_TEMP 37.7
#define MAX_HUM  70
#define MIN_HUM  50

#define RELAYS 10
#define DHT_PORT 5

/**
     variable et objet
*/
DHT dht (DHT_PORT,DHT11);
LiquidCrystal_I2C lcd (0x27,16,2);

float hum_ = 0;
float temp_= 0;
float ltemp_ = temp_;
float lhum_ = hum_;

bool  lightUP_ = false;


void setup() {
  pinMode(RELAYS,OUTPUT);

/**
    initialisation de lcd
*/
  lcd.init();
  lcd.begin(16,2,13);
  lcd.backlight ();
  lcd.cursor();
  dht.begin ();  
   
  Serial.begin(9600);
}

void loop() {

/**
     declenchement du relays
*/
  if (((temp_ - 2) > MIN_TEMP) && ((temp_ + 2) > MAX_TEMP) && lightUP_ || ((hum_ - 10) <= MIN_HUM) && ((hum_ + 10) < MAX_HUM ))
    {
      digitalWrite(RELAYS,LOW);
      lightUP_ = false;                        
    }
    else if (((temp_ - 2) <= MIN_TEMP) && ((temp_ + 2) < MAX_TEMP ) && !lightUP_ || ((hum_ - 10) > MIN_HUM) && ((hum_ + 10) > MAX_HUM))
    {
      digitalWrite(RELAYS,HIGH);
      lightUP_ = true;            
    }  
    
 /**
    affichage des donnees du dht sur le LCD      
*/   
   if (hum_ == NAN || temp_ == NAN){
     lcd.clear ();
     lcd.setCursor(0,0);
     lcd.print("ERREUR LORS DE ");
     lcd.setCursor(0,1);    
     lcd.print("LA LECTURE");  
     delay (2000);
     return;                       
  }
  else {
    if (ltemp_ != temp_){
      lcd.setCursor(0, 0);
      lcd.print("temp : ");
      lcd.print (temp_);    
    }
  
    if (lhum_ != hum_){        
      lcd.setCursor(0,1);
      lcd.print("hum  : ");
      lcd.print (hum_);     
    } 
  }    
      
  delay(2000);
  
/**
    lecture des donnees (temperature et humidite) du dht
    et declenchement du relays
*/
  if (temp_ != NAN){
    temp_ = dht.readTemperature (false);
    hum_ = dht.readHumidity ();
    
    Serial.print("temp: ");
    Serial.println(temp_);
    
    Serial.print(" hum: ");
    Serial.println(hum_);
    
  }   
}





