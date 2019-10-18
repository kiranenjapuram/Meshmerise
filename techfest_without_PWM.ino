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

int leftMotor1 = 9;
int leftMotor2 = 10;
int rightMotor1 = 11;
int rightMotor2 = 12;

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


}
void loop ()
{
  readSensors();
  if ((leftCenterReading == LOW || frontCenterReading == LOW) && rightNearReading == HIGH && leftNearReading == HIGH && leftBackReading == HIGH && rightBackReading == HIGH)
  {
    straight();
  }
  else
  {
    leftHandWall();
  }
}

void leftHandWall()
{
  if (leftCenterReading == LOW && frontCenterReading == LOW && leftFarReading == LOW && leftNearReading == LOW && rightFarReading == HIGH && rightNearReading == HIGH)
  {
    turnLeft();//left node
  }
  else if (leftCenterReading == LOW && frontCenterReading == LOW && leftFarReading == HIGH && rightFarReading == LOW && rightNearReading == LOW && leftNearReading == HIGH)
  {
    straight();//right node T
  }
  else if (leftCenterReading == LOW && frontCenterReading == HIGH && leftFarReading == HIGH && rightFarReading == LOW && rightNearReading == LOW && leftNearReading == HIGH)
  {
    do
    {
      turnRight();//pure right
    } while (digitalRead(frontCenterSensor) == LOW);
  }
  else if (leftCenterReading == HIGH && frontCenterReading == HIGH && leftFarReading == HIGH && rightFarReading == HIGH && rightNearReading == HIGH && leftNearReading == HIGH)
  {
    turnAround();//reverse
  }
  else if (leftCenterReading == LOW && frontCenterReading == HIGH && leftFarReading == LOW && rightFarReading == HIGH && rightNearReading == HIGH && leftNearReading == LOW)
  { do
    {
      turnLeft();//pure left
    } while (digitalRead(frontCenterSensor) == LOW);
  }
  else if (leftCenterReading == LOW && frontCenterReading == LOW && leftFarReading == LOW && rightFarReading == LOW && rightNearReading == LOW && leftNearReading == LOW)
  {
    turnLeft();// plus
  }

  else if (leftCenterReading == LOW && frontCenterReading == HIGH && leftFarReading == LOW && rightFarReading == LOW && rightNearReading == LOW && leftNearReading == LOW)
  {
    turnLeft();// T
  }

  else if (leftCenterReading == LOW && frontCenterReading == LOW  && leftFarReading == LOW && rightFarReading == LOW  && rightBackReading == HIGH  && leftBackReading == HIGH)
  {
    finalstop();
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
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}
void turnLeft()
{
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}
void turnRight()
{

  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}
void turnAround()
{

  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
}
void finalstop()
{
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}

