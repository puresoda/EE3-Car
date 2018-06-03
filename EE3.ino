#define R_MOTOR 5
#define L_MOTOR 6
#define L_SENSOR 14
#define M_SENSOR 15
#define R_SENSOR 16
#define RED 12
#define BLUE 11
#define GREEN 10
#define WHEEL_IR 17

const int R_BASESPEED = 170;
const int L_BASESPEED = 160;
const int STOP = 0;
long L_BASE = 0;
long M_BASE = 0;
long R_BASE = 0;

int THRESHOLD = -30;

void setup()
{
  Serial.begin(9600);
  pinMode(L_MOTOR, OUTPUT);
  pinMode(R_MOTOR, OUTPUT);
  pinMode(L_SENSOR, INPUT);
  pinMode(M_SENSOR, INPUT);
  pinMode(R_SENSOR, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(WHEEL_IR, INPUT);

  for (int i = 0; i < 100; i++)
  {
    L_BASE += (analogRead(L_SENSOR));
    M_BASE += (analogRead(M_SENSOR));
    R_BASE += (analogRead(R_SENSOR));
  }

  L_BASE /= 100;
  M_BASE /= 100;
  R_BASE /= 100;

//  analogWrite(L_MOTOR, L_BASESPEED);
//  analogWrite(R_MOTOR, R_BASESPEED);
}
void loop()
{ 
  int L_LED = analogRead(L_SENSOR) - L_BASE;
  int M_LED = analogRead(M_SENSOR) - M_BASE;
  int R_LED = analogRead(R_SENSOR) - R_BASE;

Serial.println(String(analogRead(WHEEL_IR)));
//  if (L_LED < -50 && R_LED < -50)
//  {
//    analogWrite(L_MOTOR, STOP);
//    analogWrite(R_MOTOR, STOP);
//    digitalWrite(GREEN, LOW);
//    digitalWrite(RED, HIGH);
//    digitalWrite(BLUE, HIGH);
//
//    while (true) {}
//    
//  }
//  
//  if(R_LED < THRESHOLD)
//  {
//    analogWrite(L_MOTOR, L_BASESPEED);
//    analogWrite(R_MOTOR, 0);
//
//    digitalWrite(GREEN, LOW);
//    digitalWrite(RED, HIGH);
//    digitalWrite(BLUE, LOW);
//  }
//
//  else if(L_LED < THRESHOLD)
//  {
//    analogWrite(L_MOTOR, 0);
//    analogWrite(R_MOTOR, R_BASESPEED);
//
//    digitalWrite(GREEN, LOW);
//    digitalWrite(RED, LOW);
//    digitalWrite(BLUE, HIGH);
//  }
//
//  else 
//  {
//    analogWrite(L_MOTOR, L_BASESPEED);
//    analogWrite(R_MOTOR, R_BASESPEED);
//
//    digitalWrite(GREEN, HIGH);
//    digitalWrite(RED, LOW);
//    digitalWrite(BLUE, LOW);
//  }
//  
}

