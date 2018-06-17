#define R_MOTOR 5
#define L_MOTOR 6
#define L_SENSOR 14
#define M_SENSOR 15
#define R_SENSOR 16
#define RED 12
#define BLUE 11
#define GREEN 10
#define WHEEL_IR 17

//global speed constants
const int R_BASESPEED = 170;
const int L_BASESPEED = 160;
const int STOP = 0;

//base calibration values
long L_BASE = 0;
long M_BASE = 0;
long R_BASE = 0;

//thresholds for guard rail approach
int L_THRESHOLD = -30;
int R_THRESHOLD = -30;

//used for flashing the lights when wheel is forcefully stoppped
int counter1 = 0;
unsigned long counter2 = 0;
int value = 0;
bool left_on = false;
bool stopped = false;

void setup()
{
  Serial.begin(9600);
  
  pinMode(L_MOTOR, OUTPUT);
  pinMode(R_MOTOR, OUTPUT);
  
  pinMode(L_SENSOR, INPUT);
  pinMode(M_SENSOR, INPUT);
  pinMode(R_SENSOR, INPUT);
  pinMode(WHEEL_IR, INPUT);

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

//calibrate the sensors
  for (int i = 0; i < 100; i++)
  {
    L_BASE += (analogRead(L_SENSOR));
    M_BASE += (analogRead(M_SENSOR));
    R_BASE += (analogRead(R_SENSOR));
  }

  L_BASE /= 100;
  M_BASE /= 100;
  R_BASE /= 100;

//kick start the wheels
  analogWrite(L_MOTOR, 250);
  analogWrite(R_MOTOR, 250);
}
void loop()
{   

  //calibrate readings
  int L_LED = analogRead(L_SENSOR) - L_BASE;
  int M_LED = analogRead(M_SENSOR) - M_BASE;
  int R_LED = analogRead(R_SENSOR) - R_BASE;

  //blinking code
  if(counter1 >= 500)
  {
    //restart the clock
    if(counter2 == 0)
      counter2 = millis();

    //average the total value
    value /= counter1;
    counter1 = 0;

    //detect that the car has stopped and wants to move
    if((value < 20 || value > 100) && left_on)
    { 
      stopped = true;

      //elapsed time
      unsigned long diff = millis() - counter2;

      //Flash off
      if(diff >= 400)
      {
        digitalWrite(GREEN, LOW);
        digitalWrite(RED, LOW);
        digitalWrite(BLUE, LOW);
        counter2 = 0;
      }

      //Flash on
      else if(diff >= 200)
      {
        digitalWrite(GREEN, HIGH);
        digitalWrite(RED, HIGH);
        digitalWrite(BLUE, HIGH);
      }
    }

    //Restart the lights after the car moves again
    else
    {
      stopped = false;
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, LOW);
      digitalWrite(BLUE, LOW);
    }
    value = 0;
  }

  //Average and sum the readings from the wheel IR Sensor
  else
  {
    value += analogRead(WHEEL_IR);
    counter1++;
  }


//STOP
  if (L_LED < -60 && R_LED < -60)
  {
    analogWrite(L_MOTOR, STOP);
    analogWrite(R_MOTOR, STOP);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, HIGH);

    //keep the car stopped
    while (true) {}
    
  }

//RIGHT
  if(R_LED < R_THRESHOLD)
  {
    left_on = true;
    analogWrite(L_MOTOR, L_BASESPEED);
    analogWrite(R_MOTOR, 0);

    if(!stopped)
    {
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, LOW);
    }
  }

//LEFT
  if(L_LED < L_THRESHOLD)
  {

    left_on = false;    
    analogWrite(L_MOTOR, 0);
    analogWrite(R_MOTOR, R_BASESPEED);

    if(!stopped)
    {
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, HIGH);
    }
  }

//STRAIGHT
  else 
  {
    left_on = true;
    analogWrite(L_MOTOR, L_BASESPEED);
    analogWrite(R_MOTOR, R_BASESPEED);

    if(!stopped)
    {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, LOW);
    }
  }
}


