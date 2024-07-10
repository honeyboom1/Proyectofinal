// Incluimos librerías
#include <SoftwareSerial.h>
#include <Servo.h>

Servo motor;
int posicion = 0;
// Instanciamos objeto SoftwareSerial para controlar el bluetooth
SoftwareSerial hc06(2, 3);
// Definición pines EnA y EnB para el control de la velocidad
int VelocidadMotor1 = 5; 
int VelocidadMotor2 = 6;

// Definición de los pines de control de giro de los motores In1, In2, In3 e In4  , los In son los pines del puente H el cosito del voltaje 
int Motor1A = 13; 
int Motor1B = 12;  
int Motor2C = 8; 
int Motor2D = 10;

// Definición de la velocidad inicial de los motores
int speedMotor = 80;
int motorpump = 4;
// Variable para capturar el comando que llega desde la app, esto estaba en internet
String cmd = "";
// declarar el servo para que funciono
Servo servoMotor;

void setup() {
  Serial.begin(9600);
  hc06.begin(9600);
  motor.attach(11);
  pinMode(Motor1A, OUTPUT);
  pinMode(Motor1B, OUTPUT);
  pinMode(Motor2C, OUTPUT);
  pinMode(Motor2D, OUTPUT);
  pinMode(VelocidadMotor1, OUTPUT);
  pinMode(VelocidadMotor2, OUTPUT);
  pinMode(motorpump, OUTPUT);
  analogWrite(VelocidadMotor1, speedMotor); 
  analogWrite(VelocidadMotor2, speedMotor); 
  servoMotor.attach(9);
}

void loop() {
  motor.write(90);
  delay(500);
  motor.write(135);
  delay(500);
  motor.write(90);
  delay(500);
  
  
  // Leemos los datos recibidos 
  while (hc06.available() > 0) {
    cmd += (char)hc06.read();
  }

  // Programamos cada una de las acciones a realizar según el comando recibido
  if (cmd != "") {
    cmd = cmd[0];
    if (cmd == "S") {
      stopCar();
    } else if (cmd == "F") {
      moveForwardCar();
    } else if (cmd == "B") {
      moveBackwardsCar();
    } else if (cmd == "L") {
      turnLeftCar();
    } else if (cmd == "R") {
      turnRightCar();
    } else if (cmd == "G") {
      moveForwardLeft();
    } else if (cmd == "I") {
      moveForwardRight();
    } else if (cmd == "H") {
      moveBackwardsLeft();
    } else if (cmd == "J") {
      moveBackwardsRight();
    } else if (cmd == "0") {
      speedMotor = 80;
      analogWrite(VelocidadMotor1, speedMotor); 
      analogWrite(VelocidadMotor2, speedMotor);
    } else if (cmd == "1") {
      speedMotor = 90;
      analogWrite(VelocidadMotor1, speedMotor); 
      analogWrite(VelocidadMotor2, speedMotor);
    } else if (cmd == "2") {      
      speedMotor = 100;
      analogWrite(VelocidadMotor1, speedMotor); 
      analogWrite(VelocidadMotor2, speedMotor);
    } else if (cmd == "3") {
      speedMotor = 110;
      analogWrite(VelocidadMotor1, speedMotor); 
      analogWrite(VelocidadMotor2, speedMotor);
    } else if (cmd == "4") {
      speedMotor = 120;
      analogWrite(VelocidadMotor1, speedMotor); 
      analogWrite(VelocidadMotor2, speedMotor);
    } else if (cmd == "5") {
      speedMotor = 130;
      analogWrite(VelocidadMotor1, speedMotor); 
      analogWrite(VelocidadMotor2, speedMotor);
    } else if (cmd == "6") {
      speedMotor = 140;
      analogWrite(VelocidadMotor1, speedMotor); 
      analogWrite(VelocidadMotor2, speedMotor);
    } else if (cmd == "7") {
      speedMotor = 150;
      analogWrite(VelocidadMotor1, speedMotor); 
      analogWrite(VelocidadMotor2, speedMotor);
    } else if (cmd == "8") {
      speedMotor = 160;
      analogWrite(VelocidadMotor1, speedMotor); 
      analogWrite(VelocidadMotor2, speedMotor);
    } else if (cmd == "9") {
      speedMotor = 170;
      analogWrite(VelocidadMotor1, speedMotor); 
      analogWrite(VelocidadMotor2, speedMotor);
    } else if (cmd == "q") {
      speedMotor = 180;
      analogWrite(VelocidadMotor1, speedMotor); 
      analogWrite(VelocidadMotor2, speedMotor);
     //////////comandos para controlar el servo estos los metio gpt el 180° son los grados de movimiento del servo es posible que tengas que ajustarlo para que no choque con el puente H
    } else if (cmd == "X") {
      analogWrite(motorpump,255);
      delay(5000);
      analogWrite(motorpump,0);
      delay(1000);
    }

    // basti aqui hacemos que el codigo ejecute la orden por ejemplo que se mueva a la izquierda y despues hacemos que quede esperando el receptor la siguiente orden 
    cmd = ""; 
  }
}

void stopCar() {
  // Paramos el carrito
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, LOW); 
}

void turnRightCar() {
  // Configuramos sentido de giro para girar a la derecha
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, LOW); 
}

void turnLeftCar() {
  // Configuramos sentido de giro para girar a la izquierda
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, HIGH); 
}

void moveForwardCar() {
  // Configuramos sentido de giro para avanzar
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, HIGH); 
}

void moveBackwardsCar() {
  // Configuramos sentido de giro para retroceder
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);                       
  digitalWrite(Motor2C, HIGH);
  digitalWrite(Motor2D, LOW); 
}

void moveForwardLeft() {  
  // Giramos a la izquierda mientras avanza
  analogWrite(VelocidadMotor2, speedMotor + 60);
  
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, HIGH); 

  delay(20);
  analogWrite(VelocidadMotor2, speedMotor);
}

void moveForwardRight() {
  // Giramos a la derecha mientras avanza
  analogWrite(VelocidadMotor1, speedMotor + 60);
    
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, HIGH); 
  
  delay(20);
  analogWrite(VelocidadMotor1, speedMotor);
}

void moveBackwardsLeft() {
  // Giramos a la izquierda mientras retrocede
  analogWrite(VelocidadMotor2, speedMotor + 60);
    
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);                       
  digitalWrite(Motor2C, HIGH);
  digitalWrite(Motor2D, LOW); 

  delay(20);
  analogWrite(VelocidadMotor2, speedMotor);
}

void moveBackwardsRight() {
  // Giramos a la derecha mientras retrocede
  analogWrite(VelocidadMotor1, speedMotor + 60);
    
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);                       
  digitalWrite(Motor2C, HIGH);
  digitalWrite(Motor2D, LOW); 

  delay(20);
  analogWrite(VelocidadMotor1, speedMotor);
}

