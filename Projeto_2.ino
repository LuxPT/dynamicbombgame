#define MIN_VAL 4
#define SEG_VAL 59

////////////////////////////////////////////////
//                   LCD                      //
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // Pins do LCD, o LED fica ligado a VCC porque queremos que a luz esteja sempre on
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Inicio do LCD
char timeline[16];

////////////////////////////////////////////////
//               Outras variáveis             //

signed short minutos = MIN_VAL, segundos = SEG_VAL; // Declaracao dos minutos e dos segundos
unsigned long clock_inicial;

////////////////////////////////////////////////
//                  Timer                     //

void timer() {
if(millis() - clock_inicial >= 1000)
segundos--;


lcd.setCursor(0, 1);
sprintf(timeline, "%0.2d : %0.2d ", minutos, segundos);
lcd.print(timeline);
}


void setup() {
  lcd.begin(16, 2); // Inicia e define a dimensão do LCD
  lcd.print("Time:"); // Imprime "Time"

Serial.begin(9600);
////////////////////////////////////////////////
//               Tempo inicial                //

  
  clock_inicial = millis();
  
}
// lcd.setCursor(0, 1); // Coluna zero, primeira linha
// sprintf(timeline,"%0.2d : %0.2d ", minutos, segundos);
// lcd.print(timeline);


void loop() {
timer();


}
