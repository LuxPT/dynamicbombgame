#define Password_Length 8 // Tamanho da password, deve ser preservado.
// Leds da sequencia
#define LED1 48 // Pin do led1
#define LED2 46 // Pin do led2
#define LED3 53 // Pin do led3
#define LEDR 38
#define LEDG 39
// RGB
#define RGBR 29
#define RGBG 31
#define RGBB 33

#define PIEZO 45

#define BAUD_RATE 9600


int defuse = false;
int boom = false;
int ciclo_clock = 1000;
unsigned long tempoinicial, clockatual;
unsigned long minutos = 4, segundos = 59;
char timeline[16]; // No fundo é uma linha do LCD

// RFID
/*
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Inicia o MFRC522
*/
// Keypad e LCD
#include <Keypad.h>
#include <LiquidCrystal.h>

int led[] = {LED1, LED2, LED3}; // Leds relativos à sequência

int random_val = 0;
char Master[4][Password_Length] = { "123A456", "2020ACB", "BC2876#", "#A95C06"}; // 4 possibilidades parecem suficientes.
char Data[Password_Length];

byte data_count = 0, master_count = 0;
bool password_correta; // Não se encontra em uso.
char customKey;

const byte ROWS = 4;
const byte COLS = 4;


char hexaKeys[ROWS][COLS] = { // Inicialização da matriz 4x4
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//byte rowPins[ROWS] = {9, 8, 7, 6}; // Pins do keypad
//byte colPins[COLS] = {5, 4, 3, 2}; // Pins do keypad

// Keypad:
//byte rowPins[ROWS] = {A5, A4, A3, A2}; // Pinos que utilizei para o simulador
//byte colPins[COLS] = {A1, 13, 10, 9}; // Pinos que utilizei para o simulador

byte rowPins[ROWS] = {A10, A9, A8, A7}; // Pinos que utilizei para o simulador
byte colPins[COLS] = {A5, A4, A3, A2}; // Pinos que utilizei para o simulador
// LCD
const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5; // Pinos do LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Inicio do LCD
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); // Inicio do Keypad

void printlcd() {
  lcd.setCursor(7, 0);
  lcd.print(minutos);
  lcd.print(":");

  switch (segundos) {

    case 0 ... 9:
      lcd.print("0");
      lcd.print(segundos);
      break;

    default:
      lcd.print(segundos);
      break;
  }
}

void timer() {
  if (millis() - tempoinicial >= ciclo_clock) { // Clock de um segundo;
    if (minutos >= 0) {
      segundos--;
      Serial.println(segundos);
      tempoinicial = millis(); // Novo tempo inicial

      // Piezo:
      tone(PIEZO, 1036, 200);
    }
  }

  if (minutos > 0 && segundos == 0) {
    minutos--;
    segundos = 59;
    Serial.print("Minutos:");
    Serial.println(minutos);
  }

  else if (minutos <= 0 && segundos == 0) {
    minutos = 0;
    segundos = 0;
    Serial.print("Minutos: ");
    Serial.print(minutos);
    Serial.print(" Segundos: ");
    Serial.println(segundos);
  }
}

//////////////////////////
//      Modo final      //
//////////////////////////

void defusecheck() {
  if (defuse == true) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Defused");
    delay(500);
    digitalWrite(LEDG, HIGH);
    delay(500);
  }
}
void boomcheck() {
  if (minutos == 0 && segundos <= 0) {
    boom = true;

    minutos = 0;
    segundos = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game over!");

    lcd.setCursor(0, 1);
    lcd.print("Boom!");
    delay(500);
    digitalWrite(LEDR, HIGH);
    delay(500);

  }
}

void rgbcor(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(RGBR, red_light_value);
  analogWrite(RGBG, green_light_value);
  analogWrite(RGBB, blue_light_value);
}

void passdetect() {
  lcd.setCursor(0, 1);
  lcd.print("PW:");

  customKey = customKeypad.getKey();
  if (customKey) {
    Data[data_count] = customKey;

    lcd.setCursor(data_count + 3, 1); // Aqui tem que ser +3 dado que "PW:" ocupa 3 digitos
    lcd.print(Data[data_count]);
    data_count++;
    tone(PIEZO, 1600, 100);
  }

  if (data_count == Password_Length - 1) {
    lcd.clear();

    if (!strcmp(Data, Master[random_val])) {

      defuse = true;
      lcd.setCursor(0, 1);
      lcd.print("Correct");
      digitalWrite(LEDG, 1);
      digitalWrite(LEDR, 0);
      tone(PIEZO, 2036, 200);
      delay(300);
      tone(PIEZO, 2036, 200);
      //digitalWrite(signalPin, HIGH); // Não é necessário
      delay(500); // Não é necessário
      //digitalWrite(signalPin, LOW); // Não é necessário
      digitalWrite(LEDG, 0);
    }
    else {
      // Caso o código esteja incorreto
      if (ciclo_clock > 250)
        ciclo_clock = ciclo_clock - 250;

      lcd.setCursor(0, 1);
      lcd.print("Incorrect");
      digitalWrite(LEDG, 0);
      digitalWrite(LEDR, 1);
      tone(PIEZO, 90, 200);
      delay(300);
      tone(PIEZO, 90, 200);

      delay(600);
      digitalWrite(LEDR, 0);


    }

    lcd.clear();
    clearData();

    lcd.setCursor(0, 0);
    lcd.print("Timer:");
  }
}

void clearData() {
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}

/* void rfidcheck() {
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
  if (content.substring(1) == "77 60 D5 B5") // ID do cartão branco
  {
    Serial.println("Acesso autorizado");
    Serial.println();
    delay(1500);
    start = true;
  }

  else   {
    Serial.println("Acesso negado");
    delay(1500);
  }
}
*/
  void setup() {
    tempoinicial = millis(); // Regista o tempo inicial
    clockatual = millis();

    Serial.begin(BAUD_RATE);
    
    // RFID
    /*
    SPI.begin();   // Inicia o SPI
    mfrc522.PCD_Init();   // Initiate MFRC522
    
    Serial.println("Approximate your card to the reader..."); // Mensagem de feedback para o serial
    Serial.println();                                         // Mensagem de feedback para o serial
    */
    
    lcd.begin(16, 2); // Inicialização do LCD
    lcd.print("Timer:"); // Imprime "Time" no display


    // RGB
    pinMode(RGBR, OUTPUT);
    pinMode(RGBG, OUTPUT);
    pinMode(RGBB, OUTPUT);

    // Leds azuis
    for (int i = 0; i <= 2; i++) {
      pinMode(led[i], OUTPUT);
      digitalWrite(led[i], LOW);
    }

    // Led vermelho e led verde
    digitalWrite(LEDR, 0);
    digitalWrite(LEDG, 0);

    randomSeed(analogRead(A0));
    random_val = random(0, 4); // Faz com que random_val assuma um valor aleatório entre 0 e 3;

    switch (random_val) {

      case 0: // Primeira led acessa -> Password 0
        digitalWrite(led[0], HIGH);
        break;

      case 1: // Primeira e última led acessa -> Password 1
        digitalWrite(led[0], HIGH);
        digitalWrite(led[2], HIGH);
        break;

      case 2: // Segunda led acessa -> Password 2
        digitalWrite(led[1], HIGH);
        break;

      case 3: // Todas acessas -> Password 3
        digitalWrite(led[0], HIGH);
        digitalWrite(led[1], HIGH);
        digitalWrite(led[2], HIGH);
        break;
    } // Fim do switch

  }

  void loop() {
  
    //rfidcheck();
    if (boom == false && defuse == false) { // Quando a bomba não chegou a 0, continuar com o clock a funcionar.
      passdetect();
      timer();
      printlcd();
      //rfidcheck();
    }

    // A partir daqui apenas corre o código do modo final.
    boomcheck();
    defusecheck();
    

  }
