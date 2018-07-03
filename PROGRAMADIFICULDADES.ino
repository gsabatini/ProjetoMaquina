#include <AFMotor.h>// Carrega a biblioteca AFMotor 
#include <Servo.h>
double passos_total = 2048;     //  Numero de passos para 1 rotacao total
int porta_motor_1 = 1;          // Define as portas para os motores - M1/M2 é em Y, M3/M4 é em x 
int porta_motor_2 = 2;// Valor 1 para motor em M1/M2 e 2 para motor em M3/M4
int numero_de_passos_total = 0;
AF_Stepper motorY(passos_total, porta_motor_1); // Define os parametros dos motores de passo
AF_Stepper motorX(passos_total, porta_motor_2);
double numero_de_passos = 0;    // Armazena o numero de passos que o motor vai girar
int anguloPercorrido = 0;
int contador_Y = 0;
int contador_X = 0;

#define Bot0 A15              // Define Bot0 port digitalico A15 - botao que mexe em Y
#define Bot1 A14             // Define Bot1 port digitalico A14 - botao que mexe em X
#define Bot2 A13
#define VAiQUETUa 45// Define Bot2 port D2
#define VOLTOCOMTUDO 44
bool Flag0 = LOW;             // Define Flag0 LOW
bool Flag1 = LOW;             // Define Flag1 LOW
bool Flag2 = LOW;             // Define Flag2 LOW
int angulo = 30;
int dificuldade = 0;
int controle = 0;

//-------------------------------------------
void setup()
{
  motorY.setSpeed(10);  // Define a velocidade de rotacao do motor 1
  motorX.setSpeed(10);  // Define a velocidade de rotacao do motor 2
 
  Serial.begin(9600);  // Inicializa a serial
  pinMode(Bot0, INPUT_PULLUP);
  pinMode(Bot1, INPUT_PULLUP);
  pinMode(Bot2, INPUT_PULLUP);
  pinMode(VAiQUETUa, OUTPUT);
  pinMode(VOLTOCOMTUDO, INPUT);
  digitalWrite(VAiQUETUa, LOW);
  
  
}
void loop()
{ 
  Serial.println(digitalRead(VAiQUETUa));
  if (Flag2 == LOW)
  {
    if (analogRead(Bot0) <= 500)
    {
      delay(20);
      if (analogRead(Bot0) <= 500)
      {
        dificuldade = 1;
        Flag2 = HIGH;
        delay(2000);
      }
    }
    if (analogRead(Bot1) <= 500)
    {
      delay(20);
      if (analogRead(Bot1) <= 500)
      {
        dificuldade = 2;
        Flag2 = HIGH;
        delay(2000);
      }
    }
    if (analogRead(Bot2) <= 500)
    {
      delay(20);
      if (analogRead(Bot2) <= 500)
      {
        dificuldade = 3;
        Flag2 = HIGH;
        delay(2000);
      }
    }
  }
  if (dificuldade == 1){
  if (Flag0 == LOW && Flag2 == HIGH)
  {
    while(analogRead(Bot0) <= 500)
  {
    Flag0 = HIGH;
    delay(5);
    numero_de_passos = angulo / (360/passos_total);
    motorY.step(numero_de_passos, FORWARD, SINGLE);
    motorY.release();
    contador_Y++;
    Flag0 = HIGH;
  }
  
  }
  if (Flag1 == LOW && Flag0 == HIGH)
  {
    while(analogRead(Bot1) <= 500)
  {
    delay(5);
    Serial.println(analogRead(Bot1));
    numero_de_passos = angulo / (360 / passos_total);
    

    motorX.step(numero_de_passos, FORWARD, SINGLE);
    motorX.release();
    contador_X++;
    Flag1 = HIGH;
    digitalWrite(VAiQUETUa, HIGH);
    
  }
  }
  
 
  if(digitalRead(VOLTOCOMTUDO) == HIGH){
    Serial.println(digitalRead(VAiQUETUa));
    digitalWrite(VAiQUETUa, LOW);
    for ( ;contador_Y > 0; contador_Y--)
    {
      for (;contador_X > 0; contador_X--)
      {
        motorX.step(numero_de_passos, BACKWARD, SINGLE);
        motorX.release();
      }
      motorY.step(numero_de_passos, BACKWARD, SINGLE);
      motorY.release();
      Flag0 = LOW;
      Flag1 = LOW;
      Flag2 = LOW;
      dificuldade = 0;
    }

  }
  }
  if (dificuldade == 2)
  {
    if (Flag0 == LOW && Flag2 == HIGH)
  {
    while(analogRead(Bot0) <= 500)
  {
    delay(5);
    numero_de_passos = angulo / (360/passos_total);
    motorY.step(numero_de_passos, FORWARD, SINGLE);
    motorY.release();
    contador_Y++;
  }
    if (analogRead(Bot2) <= 500)
    {
      delay(20);
      if (analogRead(Bot2) <= 500)
      {
        Flag0 = HIGH;
        digitalWrite(VAiQUETUa, HIGH);
      }
    }
    while(analogRead(Bot1) <= 500)
  {
    delay(20);
    Serial.println(analogRead(Bot1));
    numero_de_passos = angulo / (360 / passos_total);
    motorX.step(numero_de_passos, FORWARD, SINGLE);
    motorX.release();
    contador_X++;
  }
  }
  if(digitalRead(VOLTOCOMTUDO) == HIGH){
    Serial.println(digitalRead(VAiQUETUa));
    digitalWrite(VAiQUETUa, LOW);
    for ( ;contador_Y > 0; contador_Y--)
    {
      for (;contador_X > 0; contador_X--)
      {
        motorX.step(numero_de_passos, BACKWARD, SINGLE);
        motorX.release();
      }
      motorY.step(numero_de_passos, BACKWARD, SINGLE);
      motorY.release();
      Flag0 = LOW;
      Flag1 = LOW;
      Flag2 = LOW;
      dificuldade = 0;
    }
  }
  }
  if (dificuldade == 3)
  {
    if (Flag0 == LOW && Flag2 == HIGH)
  {
    while(analogRead(Bot0) <= 500)
  {
    delay(5);
    numero_de_passos = angulo / (360/passos_total);
    motorY.step(numero_de_passos, FORWARD, SINGLE);
    motorY.release();
    contador_Y++;
  }
  }
  if (Flag0 == LOW && Flag2 == HIGH)
  {
    while(analogRead(Bot1) <= 500)
  {
    if (contador_Y > 0)
    {
    delay(5);
    numero_de_passos = angulo / (360/passos_total);
    motorY.step(numero_de_passos, BACKWARD, SINGLE);
    motorY.release();
    contador_Y--;
    }
  }
  }
  if (Flag0 == HIGH && Flag1 == LOW)
  {
    while(analogRead(Bot0) <= 500)
  {
    delay(5);
    numero_de_passos = angulo / (360/passos_total);
    motorX.step(numero_de_passos, FORWARD, SINGLE);
    motorX.release();
    contador_X++;
    controle = 0;
  }
    while(analogRead(Bot1) <= 500)
  {
    if (contador_X > 0)
    {
    delay(5);
    numero_de_passos = angulo / (360/passos_total);
    motorX.step(numero_de_passos, BACKWARD, SINGLE);
    motorX.release();
    contador_X--;
    }
  }
  }
  if (analogRead(Bot2) <=500)
  {
    delay(20);
    if (analogRead(Bot2) <=500 && controle == 0)
    {
    if (Flag0 == LOW && Flag2 == HIGH)
    {
      Flag0 = HIGH;
      controle = 1;
      delay(1000);
    }
    if (Flag0 == HIGH && Flag1 == LOW && controle == 0)
    {
      Flag1 = HIGH;
      digitalWrite(VAiQUETUa, HIGH);
      delay(1000);
    }
  }
  }
  if(digitalRead(VOLTOCOMTUDO) == HIGH){
    Serial.println(digitalRead(VAiQUETUa));
    digitalWrite(VAiQUETUa, LOW);
    for ( ;contador_Y > 0; contador_Y--)
    {
      for (;contador_X > 0; contador_X--)
      {
        motorX.step(numero_de_passos, BACKWARD, SINGLE);
        motorX.release();
      }
      motorY.step(numero_de_passos, BACKWARD, SINGLE);
      motorY.release();
      Flag0 = LOW;
      Flag1 = LOW;
      Flag2 = LOW;
      dificuldade = 0;
    }
  }
  }

  




  

}
