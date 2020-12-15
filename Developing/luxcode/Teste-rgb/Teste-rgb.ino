#define R 29
#define G 31
#define B 33
int contaR,contaG,contaB;

void setup()
{
    pinMode(R, OUTPUT); //Configuração dos pinos como saída
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
  
}

void loop()
{
   
  for(contaG=0;contaG<=255;contaG++)
  {
    analogWrite(R,255); //Ligando as portas PWM com valor aleatório de duty cicle
    analogWrite(G, contaG);
  analogWrite(B, 0);
    delay(10);
  }  
  delay(10);
  for(contaR=255;contaR>=0;contaR--)
  {
    analogWrite(R,contaR); //Ligando as portas PWM com valor aleatório de duty cicle
    analogWrite(G, 255);
  analogWrite(B, 0);
    delay(10);
   }
  delay(10);
  for(contaB=0;contaB<=255;contaB++)
  {
    analogWrite(R,0);
    analogWrite(B, contaB);
  analogWrite(G, 255);
    delay(10);
  } 
  delay(10);
  
  for(contaG=255;contaG>=0;contaG--)
  {
    analogWrite(G,contaG); //Ligando as portas PWM com valor aleatório de duty cicle
    analogWrite(B, 255);
  analogWrite(R, 0);
    delay(10);
    
   }
  delay(10);
 for(contaR=0;contaR<=255;contaR++)
  {
    analogWrite(G,0);
    analogWrite(R, contaR);
  analogWrite(B, 255);
   delay(10);
  } 
  delay(10);
  
  for(contaB=255;contaB>=0;contaB--);
  {
    analogWrite(B,contaB); //Ligando as portas PWM com valor aleatório de duty cicle
    analogWrite(R, 255);
  analogWrite(G, 0);
    delay(10);
    
   }
  delay(10);}
