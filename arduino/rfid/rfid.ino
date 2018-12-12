/* This code was taken from hackster.io. Very little has been changed
 *  in this code. The changes and additions are in a comment at the bottom
 *  of this code. This sketch requires the RFID master library located
 *  in the data folder for this sketch before it can be uploaded. All of 
 *  the changes and additions were made by Willy
 */

/*
 * 
 * All the resources for this project: https://www.hackster.io/Aritro
 * Modified by Aritro Mukherjee
 * 
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Tap your SHARE Card below");
  Serial.println();

}
void loop() 
{
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
  Serial.print("Thank you for using SHARE! ");
  content.toUpperCase();
  if (content.substring(1) == "46 6F 24 D9") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("We will be tracking your location for the next 24 hours");
    Serial.println();
    delay(3000);
  }
  if (content.substring(1) == "84 9E DA 1E") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("We will be watching your smartphone usage for the next 2 years");
    Serial.println();
    delay(3000);
  }
  if (content.substring(1) == "97 EB D7 73") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("We will be evaluating your driving");
    Serial.println();
    delay(3000);
  }
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
} 

/* We added 2 additional substrings to detect the 2 additional cards that we had available. 
 *  Each of these cards have a specific ID and message tied to the card. Other changes 
 *  that we made was removing the serialprint of the ID when a card is read due to being
 *  uncessesary for our purposes.
 */
