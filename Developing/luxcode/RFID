#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Inicia o MFRC522

void rfidcheck() {
  // Deteção de novos cartões
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
    
  }

  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
    
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
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
  if (content.substring(1) == "77 60 D5 B5") // ID do cartão
  {
    Serial.println("Acesso autorizado");
    Serial.println();
    delay(3000);
  }

  else   {
    Serial.println("Acesso negado");
    delay(3000);
  }

}
void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop()
{
rfidcheck();
}
