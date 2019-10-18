#define leftCenterSensor 1
#define frontCenterSensor 2
#define leftFarSensor 3
#define rightFarSensor 4
#define leftBackSensor 5
#define rightBackSensor 6
#define rightNearSensor 7
#define leftNearSensor 8


int leftCenterReading;
int frontCenterReading;
int leftFarReading;
int rightFarReading;
int leftBackReading;
int rightBackReading;
int leftNearReading;
int rightNearReading;

int mot1 = 9;
int mot2 = 10;
int leftMotor1 = A0;
int leftMotor2 = A1;
int rightMotor1 = A2;
int rightMotor2 = A3;

void setup ()
{

  pinMode(leftCenterSensor, INPUT);
  pinMode(frontCenterSensor, INPUT);
  pinMode(leftFarSensor, INPUT);
  pinMode(rightFarSensor, INPUT);
  pinMode(leftBackSensor, INPUT);
  pinMode(rightBackSensor, INPUT);
  pinMode(leftNearSensor, INPUT);
  pinMode(rightNearSensor, INPUT);

  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);


}
void loop ()
{
  readSensors ();
 if( rightBackReading == LOW  && leftBackReading == LOW && frontCenterReading == LOW && rightNearReading == HIGH && leftNearReading == HIGH && rightFarReading == HIGH && leftFarReading == HIGH)
  {
    finalstop();
  }
  else if (frontCenterReading == HIGH && leftFarReading == HIGH  && leftNearReading == HIGH && (rightFarReading == LOW || rightNearReading == LOW))
  { do
    {
      turnLeft();//pure left
    } while (digitalRead(frontCenterSensor) == LOW);
  }
  else if (leftCenterReading == HIGH && (frontCenterReading == LOW || rightNearReading == HIGH || leftNearReading == HIGH) && (leftBackReading == HIGH || rightBackReading == HIGH))
  {
    straight();
  }
  else if (frontCenterReading == HIGH && rightFarReading == HIGH && rightNearReading == HIGH && (leftFarReading == LOW || leftNearReading == LOW))
  {
    do
    {
      turnRight();//pure right
    } while (digitalRead(frontCenterSensor) == LOW);
  }
  else if (leftCenterReading == HIGH && frontCenterReading == LOW && (leftFarReading == HIGH || leftNearReading == HIGH || rightNearReading == LOW) && rightFarReading == LOW)
  { do
    {
      turnLeft();//left node
    } while (digitalRead(frontCenterSensor) == LOW);
  }
  else if (leftCenterReading == HIGH && frontCenterReading == LOW  && (rightFarReading == HIGH || rightNearReading == HIGH) && leftNearReading == LOW && leftFarReading == LOW)
  {
    straight();//right node T
  }
  else if (leftCenterReading == LOW && frontCenterReading == HIGH && leftFarReading == LOW && rightFarReading == LOW && rightNearReading == LOW && leftNearReading == LOW)
    {
      turnAround();//reverse
    }
  
  else if (frontCenterReading == HIGH && (leftCenterReading == HIGH && rightNearReading == HIGH) || (leftNearReading == HIGH && leftCenterReading == HIGH) || (leftFarReading == HIGH && leftNearReading == HIGH) || (rightFarReading == HIGH && rightNearReading == HIGH))
  { do
    {
      turnLeft();// plus
    } while (digitalRead(frontCenterSensor) == LOW);
  }
  else if (frontCenterReading == LOW && (leftCenterReading == HIGH && rightNearReading == HIGH) || (leftNearReading == HIGH && leftCenterReading == HIGH) || (leftFarReading == HIGH && leftNearReading == HIGH) || (rightFarReading == HIGH && rightNearReading == HIGH))
  {
    do
    {turnLeft();// T
  }while(digitalRead(frontCenterSensor)== LOW);
  }
  
  }
void readSensors()
{

  leftCenterReading = digitalRead(leftCenterSensor);
  leftBackReading = digitalRead(leftBackSensor);
  leftFarReading = digitalRead(leftFarSensor);
  frontCenterReading = digitalRead(frontCenterSensor);
  rightBackReading = digitalRead(rightBackSensor);
  rightFarReading = digitalRead(rightFarSensor);
  leftNearReading = digitalRead(leftNearSensor);
  rightNearReading = digitalRead(rightNearSensor);
}

void straight()
{
  analogWrite(mot1, 95);
  analogWrite(mot2, 95);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}
void turnLeft()
{ 
  analogWrite(mot1, 255);
  analogWrite(mot2, 150);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  delay(100);
}
void turnRight()
{
  analogWrite(mot1, 150);
  analogWrite(mot2, 255);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  delay(100);
}
void turnAround()
{ 
  analogWrite(mot1, 150);
  analogWrite(mot2, 150);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, HIGH );
  digitalWrite(rightMotor2, LOW);
}
void finalstop()
{
  analogWrite(mot1, 0);
  analogWrite(mot2, 0);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}
