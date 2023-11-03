#include <SoftwareSerial.h>

//Defines comunicación serial
#define RxPin 10
#define TxPin 11

//Defines de diodos
#define D1 4
#define D2 5
#define D3 6
#define D4 7

//Define del motor
#define MOTOR 9

//Variables globales
char contador = 0;
const unsigned char nivel[] = {0, 13, 26, 40, 53, 67, 80, 93, 107, 120, 134, 147, 161, 174, 187, 201, 214, 228, 241, 255};
char button;
SoftwareSerial bluetooth = SoftwareSerial(RxPin, TxPin);

void setup(){ 
  //Configuración comunicación serial
  pinMode(RxPin, INPUT);
  pinMode(TxPin, OUTPUT);
  Serial.begin(9600, SERIAL_8N1);
  bluetooth.begin(9600);

  //Configuración de salida e inicialización para diodos
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);

  //Configuración de salida e inicialización para el motor
  pinMode(MOTOR, OUTPUT);
  analogWrite(MOTOR, nivel[contador]);
}

void loop() {
  if(contador == 0){
    titilar(D1,2);
  }else{
    digitalWrite(D1, LOW);
  }


  if (Serial.available()) button = Serial.readStringUntil(",").charAt(0);
  else if (bluetooth.available()) button = bluetooth.readStringUntil(",").charAt(0);
  else return;

  Serial.write(button);

  switch (button) {
    case 'P':
      parada();
      break;
    case 'A':
      arranque();
      break;
    case 'I':
      incremento();
      break;
    case 'R':
      decremento();
      break;
    case 'C':
      ciclo();
      break;
    case 'O':
      oprimido();
      break;
  }
}

//Función de titilar, recibe el pin del diodo y la veces que lo hará
void titilar(char diodo, char n) {
  for (int i = 0; i < n; i++) {
    delay(250);
    digitalWrite(diodo, !digitalRead(diodo)); 
  }
}

//Función de parada
void parada() {
  analogWrite(MOTOR, nivel[0]);
}

//Función de arranque
void arranque() {
  analogWrite(MOTOR, nivel[contador]);
}

void incremento() {
  titilar(D2,4);
  contador++;
  if(contador > 19){
    contador = 19;
  }
  analogWrite(MOTOR, nivel[contador]);
}

void decremento() {
  titilar(D4,4);
  contador--;
  if(contador < 0){
    contador = 0;
  }
  analogWrite(MOTOR, nivel[contador]);
}

void ciclo() {
  if(MOTOR == 0) {
    for(char i = 0; i < 19; i++) {
      titilar(D2, 6);
      analogWrite(MOTOR, nivel[i]);
    }
  }
  titilar(D3, 60);
  for(char i = 19; i > 0; i--) {
      titilar(D4, 8);
      analogWrite(MOTOR, nivel[i]);
    }
  contador = 0;
}

void oprimido(){
  
}