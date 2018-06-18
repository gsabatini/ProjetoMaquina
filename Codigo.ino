// Programa : Controlando 2 motores de passo 28BYJ-48 e 2 motores servo Micro servo 9G com
// Arduino Motor Shield L293D + Arduino Uno
// Autor : Francisco Ribeiro Junior - Equipe Annimar

#include <AFMotor.h>            // Carrega a biblioteca AFMotor 
#include <Servo.h>
double passos_total = 2048;     //  Numero de passos para 1 rotacao total
int porta_motor_1 = 1;          // Define as portas para os motores
int porta_motor_2 = 2;          // Valor 1 para motor em M1/M2 e 2 para motor em M3/M4
Servo servo1;                   // Define os parametros dos motores servo
Servo servo2;
AF_Stepper passo1(passos_total, porta_motor_1); // Define os parametros dos motores de passo
AF_Stepper passo2(passos_total, porta_motor_2);
double numero_de_passos = 0;    // Armazena o numero de passos que o motor vai girar
int anguloPercorrido = 0;

# define Bot0 A0              // Define Bot0 port analogico A0
# define Bot1 A1              // Define Bot1 port analogico A1
# define Bot2 2               // Define Bot2 port D2
bool Flag0 = LOW;             // Define Flag0 LOW
bool Flag1 = LOW;             // Define Flag1 LOW
bool Flag2 = LOW;             // Define Flag2 LOW
//-------------------------------------------
void setup()
{
  passo1.setSpeed(10);  // Define a velocidade de rotacao do motor 1
  passo2.setSpeed(10);  // Define a velocidade de rotacao do motor 2
  servo1.attach(10);    // Indica que o servo1 esta ligado ao pino 10
  servo2.attach(9);  // Indica que o servo2 esta ligado ao pino 9

  Serial.begin(9600);  // Inicializa a serial
  pinMode(Bot0, INPUT_PULLUP);
  pinMode(Bot1, INPUT_PULLUP);
  pinMode(Bot2, INPUT_PULLUP);
  attachInterrupt(0, SaidaAcionada, FALLING);
}
//-------------------------------------------
void loop()
{
  if (digitalRead(Bot0) == 0)               // Se Bot0 foi pressionado
  {
    delay(20);                              // Aguarda 20 ms para evitar bouncing
    if (digitalRead(Bot0) == 0)             // Se Bot0 continua pressionado
    {
      Flag0 = HIGH;                         // Liga flag0  Liga
      Flag2 = LOW;                          // Desabilita subir
      Serial.println(Flag0);
    }
  }
  if (Flag0 == LOW)                         // Se Inicio estiver desabilitado
  {
    if (digitalRead(Bot1) == 0)             // Se Bot1 foi pressionado
    {
      delay(20);                            // Aguarda 20 ms para evitar bouncing
      if (digitalRead(Bot1) == 0)           // Se Bot2 continua pressionado
      {
        Flag2 = HIGH;                       // Liga flag2  Sobe
      }
    }
  }
  //  int teste =  passo1.currentstep;
  // -------------------***************************************************
  if (Flag2 == HIGH)                        //  Subir esta habilitado
  {
    //    Aqui voce coloca sua logica de comandar o motor pra subir
    Serial.println(Flag2);
  }
  // -------------------***************************************************
  anguloPercorrido = 0;                        //  Zera o angulo
  servo1.write(0);
  servo2.write(0);
  delay(100);
  while (Flag0 == HIGH)
  {
    Serial.println("Loop Flg0 = HIGH");
    while (anguloPercorrido < 360)
    {
      Serial.println(anguloPercorrido);
      ClickServos();                // Desce 35(passo 0)
      delay(100);
      CameraVertical(35, false);
      //    Serial.println(passo1.currentstep);
      delay(100);
      ClickServos();                // Desce 35(passo 1)
      delay(100);
      CameraVertical(35, false);
      //    Serial.println(passo1.currentstep);
      delay(100);
      ClickServos();                // Desce 35(passo 2)
      delay(100);
      CameraVertical(35, false);
      //    Serial.println(passo1.currentstep);
      delay(100);
      ClickServos();                // Desce 35(passo 3)
      delay(100);
      CameraVertical(35, false);
      //    Serial.println(passo1.currentstep);
      delay(100);
      ClickServos();                // Desce 35(passo 4)
      delay(100);
      CameraVertical(140, true);    // Desce 35(passo 5)
      //    Serial.println(passo1.currentstep);
      delay(100);
      CameraHorizontal(15);
      delay(100);
      anguloPercorrido += 15;
    }
  }
}
//-------------------------------------------
void ClickServos()
{
  servo1.write(7);
  servo2.write(7);
  delay(2400);
  servo1.write(15);
  servo2.write(15);
  delay(100);
  servo1.write(0);
  servo2.write(0);
  delay(100);
}
//-------------------------------------------
void CameraVertical(int Angulo, bool positivo)
{
  numero_de_passos = Angulo / (360 / passos_total);
  if (positivo)                                       // se o valor de positivo for verdadeiro, a camera ir� virar para cima, sen�o, vira para baixo
  {
    passo1.step(numero_de_passos, FORWARD, SINGLE);
    passo1.release();
  }
  else
  {
    passo1.step(numero_de_passos, BACKWARD, SINGLE);
    passo1.release();
  }
}
//-------------------------------------------
void CameraHorizontal(int Angulo)
{
  numero_de_passos = Angulo / (360 / passos_total);
  passo2.step(numero_de_passos, FORWARD, SINGLE);
  passo2.release();
}
//--------------------------------------------
void SaidaAcionada()
{
  Flag0 = LOW;
}

