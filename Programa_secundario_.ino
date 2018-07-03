
#include <AFMotor.h>
double passos_total = 2048; 
int porta_motor = 2;
int numero_de_passos_total = 0;
AF_Stepper motorZ(passos_total, porta_motor);
double numero_de_passos = 0;    
int anguloPercorrido = 0;
int contador = 0;
#define VOOUNESZA 2
#define HORADAVOLTA 13
int angulo = 30;

//-------------------------------------------
void setup()
{
  motorZ.setSpeed(5);
  Serial.begin(9600);
  pinMode(VOOUNESZA, INPUT);
  pinMode(HORADAVOLTA, OUTPUT);
  digitalWrite(HORADAVOLTA, LOW);
  
}
void loop()
{
  Serial.println(digitalRead(VOOUNESZA));
  if(digitalRead(VOOUNESZA) == HIGH)
  {
    delay(3000);
    for (int i = 0; i < 5; i++)
    {
      delay(10);
      numero_de_passos = angulo / (360/passos_total);
      motorZ.step(numero_de_passos, FORWARD, SINGLE);
      contador++;
      motorZ.release();
    }
    delay(100);
    for (; contador > 0; contador--){
      delay(10);
      numero_de_passos = angulo / (360/passos_total);
      motorZ.step(numero_de_passos, BACKWARD, SINGLE);
      motorZ.release();
    }
    digitalWrite(HORADAVOLTA, HIGH);
    delay(5000);
    digitalWrite(HORADAVOLTA, LOW);
  }
 }

