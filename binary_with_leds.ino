/*
 * File:        binary-with-leds.ino
 * Author:      Emre Kızılelma
 * Date:        2025-01-14
 * Description: An Arduino project that displays the 
 *				      given decimal number as an 8-bit value 
 *              in base 2 with Red LED's.
 * Version:     1.0
 * License:     MIT
 */


#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x20,16,2);


const uint8_t led_pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};


void setup() {
  
  for(int i = 0; i < 8; i++) {
    pinMode(led_pins[i], OUTPUT);
    digitalWrite(led_pins[i], LOW);
  }
  
  Serial.begin(9600);
  Serial.println("Lutfen 0-255 arasinda bir sayi giriniz: ");
  
 
  lcd.init();
  lcd.clear();         
  lcd.backlight();   
  
}

void loop() {
  if(Serial.available() >0) {
    int input_number = Serial.parseInt();
    
    if(input_number >= 0 && input_number <= 255) {
      Serial.print("Girilen sayı:  ");
      Serial.println(input_number);
      uint8_to_binary(input_number);
      
  	  lcd.setCursor(1, 0);   
  	  lcd.print("Girdiginiz sayi:");
  	  lcd.setCursor(2,1);
  	  lcd.print(input_number);
      delay(5000);
   	  lcd.clear();
      
    } else {
      Serial.println("Hata!");
    }
  }
}

void uint8_to_binary(uint8_t number) {
  for(int i = 0; i < 8; i++) {
    int bit_value = (number >> i) & 0x01;
    digitalWrite(led_pins[i], bit_value);
  }
}