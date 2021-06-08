#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int buzzer = 6;

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  lcd.begin();
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
   lcd.setCursor(0,0);
   lcd.print("Absensi Mhs");
   lcd.setCursor(0,1);
   lcd.print("Prabu Fath Ilham");
   delay(4000);
   lcd.clear();
   delay(1000);  

}
void loop() 
{
   lcd.setCursor(0,0);
   lcd.print("Sistem Absensi");
   lcd.setCursor(1,1);
   lcd.print("ON");
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "B7 CB 09 D9") //change here the UID of the card/cards that you want to give access
  {
    lcd.clear();
    Serial.println("Authorized access");
    lcd.setCursor(0,0);
    lcd.print("Prabu Fath");
    lcd.setCursor(1,1);
    lcd.print("Hadir");
    tone(buzzer,800);
    Serial.println();
    delay(2000);
  }

   else if (content.substring(1) == "75 73 93 37") //change here the UID of the card/cards that you want to give access
  {
    lcd.clear();
    Serial.println("Authorized access");
    lcd.setCursor(0,0);
    lcd.print("Muh. Fadhil");
    lcd.setCursor(1,1);
    lcd.print("Hadir");
    tone(buzzer,800);
    Serial.println();
    delay(2000);
  }
  
 else   {
    lcd.clear();
    Serial.println(" Access denied");
    lcd.setCursor(0,0);
    lcd.print("Akses Kartu");
    lcd.setCursor(1,1);
    lcd.print("Salah");
    tone(buzzer,800);
    delay(300);
    noTone(buzzer);
  }
// delay(3000);
  lcd.clear();
  noTone(buzzer);
  
}
