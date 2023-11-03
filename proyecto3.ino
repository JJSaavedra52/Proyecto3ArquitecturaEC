//Defines de botones
#define P 13
#define	A 12
#define	I 11
#define	R 10
#define	C 9
#define OP 1

//Defines de diodos
#define D1 8
#define D2 7
#define D3 6
#define D4 5

//Define del motor
#define MOTOR 3

//Variables globales
char contador = 0;
const unsigned char nivel[] = {0, 13, 26, 40, 53, 67, 80, 93, 107, 120, 134, 147, 161, 174, 187, 201, 214, 228, 241, 255};

void setup()
{
  //Configuración de entrada para botones
  pinMode(P, INPUT);
  pinMode(A, INPUT);
  pinMode(I, INPUT);
  pinMode(R, INPUT);
  pinMode(C, INPUT);

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
  analogWrite(MOTOR, nivel[0]);
}

void loop()
{
  if(MOTOR == nivel[0]){
    titilar(D1,2);
  }

  if(P == OP){
    parada();
  }

  if(A == OP){
    arranque();
  }

  if(I == OP){
    incremento();
  }

  if(R == OP){
    decremento();
  }

  if(C == OP){
    ciclo();
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
    for(char = 0; i < 19; i++) {
      titilar(D2, 6);
      analogWrite(MOTOR, nivel[i]);
    }
  }
  titilar(D3, 60);
  for(char = 19; i > 0; i--) {
      titilar(D4, 8);
      analogWrite(MOTOR, nivel[i]);
    }
  contador = 0;
}