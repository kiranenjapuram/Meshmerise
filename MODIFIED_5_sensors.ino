/* Thi
 *  s is the code for the Arduino Uno Microcontroller
   Input: the sensor array at the front of the vehicle
   Outputs signals to the motors to control movement
   Algorithm: "Left-Hand-on-Wall" Algorithm to solve maze (priorities of checking movements are Left, Straight, Right, Back)
*/


#define leftCenterSensor   3
#define leftNearSensor     4
#define leftFarSensor      5
#define rightNearSensor    1
#define rightFarSensor     12

int leftCenterReading;
int leftNearReading;
int leftFarReading;
int rightNearReading;
int rightFarReading;

int leftNudge;
int replaystage;
int rightNudge;

#define leapTime 200

#define leftMotor1  10
#define leftMotor2  9

#define rightMotor1 6
#define rightMotor2 7

#define led 13

char path[30] = {};
int pathLength;
int readLength;

void setup() {

  pinMode(leftCenterSensor, INPUT);
  pinMode(leftNearSensor, INPUT);
  pinMode(leftFarSensor, INPUT);
  pinMode(rightNearSensor, INPUT);
  pinMode(rightFarSensor, INPUT);

  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(led, OUTPUT);
  //Serial.begin(115200);
  digitalWrite(led, HIGH);
  delay(1000);
}


void loop() {

  readSensors();

  if (leftFarReading == HIGH && rightFarReading == HIGH && leftCenterReading == LOW ) //if only the middle two sensors can see the black line
  {
    straight();//Moves straight
  }
  else//otherwise goes to the leftHandWall method
  {
    leftHandWall();
  }

}

void readSensors()//accepts input from sensors
{

  leftCenterReading  = digitalRead(leftCenterSensor);
  leftNearReading    = digitalRead(leftNearSensor);
  leftFarReading     = digitalRead(leftFarSensor);
  rightNearReading   = digitalRead(rightNearSensor);
  rightFarReading    = digitalRead(rightFarSensor);

}


void leftHandWall() {


  if ( leftFarReading == LOW && rightFarReading == LOW) //indicates either 3way intersection or end of maze
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  
    readSensors();

    if (leftFarReading == LOW || rightFarReading == LOW) //if it moves forward and still sees all black, maze is done
    {
      done();
    }
    if (leftFarReading == HIGH && rightFarReading == HIGH) //otherwise it turns left
    {
      turnLeft();
    }

  }

  if (leftFarReading == LOW) //indicates that a left turn is possible
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
   
    readSensors();

    if (leftFarReading == HIGH && rightFarReading == HIGH) //checks to make sure maze isn't done
    {
      turnLeft();
    }
    else
    {
      done();
    }
  }

  if (rightFarReading == LOW) //indicates a right turn is possible
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(10);//CHANGED FROM 30 to 10
    readSensors();

    if (leftFarReading == LOW) //left turn is also possible
    {
    
      readSensors();

      if (rightFarReading == LOW && leftFarReading == LOW) //end of maze
      {
        done();
      }
      else//make the left turn
      {
        turnLeft();
        return;
      }
    }
   
    readSensors();
    if (leftFarReading == HIGH && leftCenterReading == HIGH && rightFarReading == HIGH)
    {
      turnRight();
      return;
    }
    path[pathLength] = 'S';
    // Serial.println("s");
    pathLength++;
    //Serial.print("Path length: ");
    Serial.println(pathLength);
    if (path[pathLength - 2] == 'B') {
      Serial.println("shortening path");
      shortPath();
    }
    straight();
  }
  readSensors();
  if (leftFarReading == HIGH && leftCenterReading == HIGH && rightFarReading == HIGH && leftNearReading == HIGH && rightNearReading == HIGH)\
  {
    turnAround();
  }

}
void done() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  replaystage = 1;
  path[pathLength] = 'D';
  pathLength++;
  while (digitalRead(leftFarSensor) == LOW) {
    digitalWrite(led, LOW);
    delay(150);
    digitalWrite(led, HIGH);
    delay(150);
  }
  delay(500);
  replay();
}

void turnLeft() {



  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  delay(1075);

  /*
    while(digitalRead(rightCenterSensor)==0||digitalRead(leftCenterSensor)==0)
    {
      digitalWrite(leftMotor1, LOW);
     digitalWrite(leftMotor2, HIGH);
     digitalWrite(rightMotor1, LOW);
     digitalWrite(rightMotor2, LOW);
     delay(2);
      digitalWrite(leftMotor1, LOW);
     digitalWrite(leftMotor2, LOW);
     digitalWrite(rightMotor1, LOW);
     digitalWrite(rightMotor2, LOW);
     delay(1);
    }

    while(digitalRead(rightCenterSensor)==1){
     digitalWrite(leftMotor1, LOW);
     digitalWrite(leftMotor2, HIGH);
     digitalWrite(rightMotor1, HIGH);
     digitalWrite(rightMotor2, LOW);
     delay(2);
     digitalWrite(leftMotor1, LOW);
     digitalWrite(leftMotor2, LOW);
     digitalWrite(rightMotor1, LOW);
     digitalWrite(rightMotor2, LOW);
     delay(1);
    }*/

  if (replaystage == 0) {
    path[pathLength] = 'L';
    Serial.println("l");
    pathLength++;
    Serial.print("Path length: ");
    Serial.println(pathLength);
    if (path[pathLength - 2] == 'B') {
      Serial.println("shortening path");
      shortPath();
    }
  }
}

void turnRight() {


  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  delay(1075);


  /*
    while(digitalRead(rightCenterSensor)==0){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    }
    while(digitalRead(rightCenterSensor)==1){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    }
    while(digitalRead(leftCenterSensor)==1){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    }
  */

  if (replaystage == 0) {
    path[pathLength] = 'R';
    Serial.println("r");
    pathLength++;
    //Serial.print("Path length: ");
    Serial.println(pathLength);
    if (path[pathLength - 2] == 'B') {
       Serial.println("shortening path");
      shortPath();
    }
  }

}

void straight() {
  if ( digitalRead(leftCenterSensor) == HIGH) {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(5);
    return;
  }
  
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  delay(4);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  delay(1);

}

void turnAround()
{ /*
    {
     digitalWrite(leftMotor1, HIGH);
     digitalWrite(leftMotor2, LOW);
     digitalWrite(rightMotor1, HIGH);
     digitalWrite(rightMotor2, LOW);
     delay(150);
    while(digitalRead(leftCenterSensor)==1){
      digitalWrite(leftMotor1, LOW);
     digitalWrite(leftMotor2, HIGH);
     digitalWrite(rightMotor1, HIGH);
     digitalWrite(rightMotor2, LOW);
     delay(2);
      digitalWrite(leftMotor1, LOW);
     digitalWrite(leftMotor2, LOW);
     digitalWrite(rightMotor1, LOW);
     digitalWrite(rightMotor2, LOW);
     delay(1);
    }
  */

  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  delay(900);

  path[pathLength] = 'B';
  pathLength++;
  straight();
  Serial.println("b");
  Serial.print("Path length: ");
  Serial.println(pathLength);
}

void shortPath() {
  int shortDone = 0;
  if (path[pathLength - 3] == 'L' && path[pathLength - 1] == 'R') {
    pathLength -= 3;
    path[pathLength] = 'B';
    Serial.println("test1");
    shortDone = 1;
  }

  if (path[pathLength - 3] == 'L' && path[pathLength - 1] == 'S' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'R';
    Serial.println("test2");
    shortDone = 1;
  }

  if (path[pathLength - 3] == 'R' && path[pathLength - 1] == 'L' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'B';
    Serial.println("test3");
    shortDone = 1;
  }


  if (path[pathLength - 3] == 'S' && path[pathLength - 1] == 'L' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'R';
    Serial.println("test4");
    shortDone = 1;
  }

  if (path[pathLength - 3] == 'S' && path[pathLength - 1] == 'S' && shortDone == 0) {
  
    pathLength -= 3;
    path[pathLength] = 'B';
    Serial.println("test5");
    shortDone = 1;
  }
  if (path[pathLength - 3] == 'L' && path[pathLength - 1] == 'L' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'S';
    Serial.println("test6");
    shortDone = 1;
  }

  path[pathLength + 1] = 'D';
  path[pathLength + 2] = 'D';
  pathLength++;
  Serial.print("Path length: ");
  Serial.println(pathLength);
  //printPath();
}




void printPath() {
  Serial.println("+++++++++++++++++");
  int x;
  while (x <= pathLength) {
    Serial.println(path[x]);
    x++;
  }
    Serial.println("+++++++++++++++++");
}


void replay() {
  readSensors();
  if (leftFarReading == HIGH && rightFarReading == HIGH) {
    straight();
  }
  else {
    if (path[readLength] == 'D') {
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      delay(100);
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, LOW);
      endMotion();
    }
    if (path[readLength] == 'L') {
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      delay(leapTime);
      turnLeft();
    }
    if (path[readLength] == 'R') {
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      delay(leapTime);
      turnRight();
    }
    if (path[readLength] == 'S') {
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      delay(leapTime);
      straight();
    }

    readLength++;
  }

  replay();

}

void endMotion() {
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(500);
  endMotion();
}

