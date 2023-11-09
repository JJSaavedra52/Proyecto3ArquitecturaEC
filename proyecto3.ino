// Imports
#include <SoftwareSerial.h>

// Defines comunicación serial
#define RxPin 10
#define TxPin 11

// Defines de diodos
#define D1 4
#define D2 5
#define D3 6
#define D4 7

// Define del motor
#define MOTOR 9

// Variables globales
char contador = 0;
const unsigned char nivel[] = {0, 13, 26, 40, 53, 67, 80, 93, 107, 120, 134, 147, 161, 174, 187, 201, 214, 228, 241, 255};
bool estadoMotor = true;
char accion;
SoftwareSerial bluetooth = SoftwareSerial(RxPin, TxPin);

void setup()
{
  // Configuración comunicación serial
  pinMode(RxPin, INPUT);
  pinMode(TxPin, OUTPUT);
  Serial.begin(9600, SERIAL_8N1);
  bluetooth.begin(9600);

  // Configuración de salida e inicialización para diodos
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);

  // Configuración de salida e inicialización para el motor
  pinMode(MOTOR, OUTPUT);
  analogWrite(MOTOR, nivel[contador]);
}

void loop()
{
  if (estadoMotor == false || contador == 0)
  {
    titilar(D1, 1);
  }
  else
  {
    digitalWrite(D1, LOW);
  }

  if (Serial.available())
  {
    accion = Serial.read();
  }
  else if (bluetooth.available())
  {
    accion = bluetooth.read();
  }
  else
  {
    return;
  }

  switch (accion)
  {
  case 'P':
    parada();
    accion = 0;
    break;
  case 'A':
    arranque();
    accion = 0;
    break;
  case 'I':
    incremento();
    accion = 0;
    break;
  case 'R':
    decremento();
    accion = 0;
    break;
  case 'C':
    ciclo();
    accion = 0;
    break;
  default:
    accion = 0;
    break;
  }
}

// Función de titilar, recibe el pin del diodo y la veces que lo hará
void titilar(char diodo, char n)
{
  for (int i = 0; i < n * 2; i++)
  {
    delay(250);
    digitalWrite(diodo, !digitalRead(diodo));
  }
}

// Función de parada
void parada()
{
  analogWrite(MOTOR, nivel[0]);
  estadoMotor = false;
  Serial.println("Detenido");
}

// Función de arranque
void arranque()
{
  analogWrite(MOTOR, nivel[contador]);
  estadoMotor = true;
  Serial.println("Funcionando");
  Serial.print("Nivel: ");
  Serial.println("Reestablecido");
}

// Función de incremento de velocidad
void incremento()
{
  if (estadoMotor == true)
  {
    titilar(D2, 2);
    contador++;

    if (contador > 19)
    {
      contador = 19;
      Serial.print("Nivel: ");
      Serial.println("Maximo");
    }
    else
    {
      Serial.print("Nivel: ");
      Serial.println("Aumento");
    }
    analogWrite(MOTOR, nivel[contador]);
  }
}

// Función de decremento de velocidad
void decremento()
{
  if (estadoMotor == true)
  {
    titilar(D4, 2);
    contador--;

    if (contador < 0)
    {
      contador = 0;
      Serial.print("Nivel: ");
      Serial.println("Minimo");
    }
    else
    {
      Serial.print("Nivel: ");
      Serial.println("Decremento");
    }
    analogWrite(MOTOR, nivel[contador]);
  }
}

void ciclo()
{
  if (estadoMotor == false || contador == 0)
  {
    Serial.println("Ciclo");
    for (char i = 0; i <= 19; i++)
    {
      titilar(D2, 3);
      analogWrite(MOTOR, nivel[i]);
    }

    titilar(D3, 30);

    for (char i = 19; i >= 0; i--)
    {
      titilar(D4, 4);
      analogWrite(MOTOR, nivel[i]);
    }
    contador = 0;
    estadoMotor = true;
    Serial.println("Fin ciclo");
    Serial.print("Nivel: ");
    Serial.println("0");
  }
}