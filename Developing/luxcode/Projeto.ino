#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // Pins do LCD, o LED fica ligado a VCC porque queremos que a luz esteja sempre on

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Inicio do LCD

signed short minutos, seconds; // Declaracao dos minutos e dos segundos
char timeline[16]; // No fundo é uma linha do LCD

void setup() {

  lcd.begin(16, 2); // Colunas, linhas (col/row); Inicializa o LCD e especifica as dimensões
  lcd.print("Time:"); // Imprime "Time" no display


}

void loop() {

}
