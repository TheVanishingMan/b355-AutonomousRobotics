#pragma config(Sensor, dgtl3,  sonar,          sensorSONAR_cm)
#pragma config(Sensor, dgtl6,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl11, followBump,          sensorNone)
#pragma config(Sensor, dgtl12, bump2,          sensorNone)
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393, openLoop)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393, openLoop)

/*******************************************************************************/
void turnLeft90(){
	motor[leftMotor]   =  0;
  motor[rightMotor]  =  0;
  wait1Msec(1000);
  SensorValue[rightEncoder] = 0;
	while(SensorValue(rightEncoder) < 141.3 - 30){
		motor[leftMotor] = 30;
		motor[rightMotor] = 30;
		}
		motor[leftMotor]   =  0;
		motor[rightMotor]  =  0;
}

void moveForward(int distance) {
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(1000);
	SensorValue[rightEncoder] = 0;
	while(SensorValue(rightEncoder) < distance) { //robot length around 160
		motor[leftMotor] = -30;
		motor[rightMotor] = 30;
	}
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

int previousBehavior = 0;

void follow() {
	int behavior = 2;

	// Sonar distance windows
	bool lowWindow = SensorValue(sonar) < 5 && SensorValue(sonar) > 0;
	bool butterZone = SensorValue(sonar) < 7 && SensorValue(sonar) > 5;
	bool highWindow = SensorValue(sonar) > 9 && SensorValue(sonar) < 13;
	bool noWall = (SensorValue(sonar) == -1) || SensorValue(sonar) > 13;
	bool isWall = !SensorValue(followBump);
	bool was4 = (previousBehavior == 4);

	//behavior decision based on prevouis state
	//bool outDriftCont;

	if (lowWindow || isWall){ // veer right
		behavior = 1;
	}
	if (butterZone){ // go forward
		behavior = 2;
	}
	if (highWindow && !isWall){ // veer left
		behavior = 3;
	}

	if (noWall || was4) { // turn 90 degrees left
		behavior = 4;
	}


	writeDebugStreamLine("the behavior is: %d", behavior);

	switch(behavior){
		case 1:
			writeDebugStreamLine("veer right");
			motor[leftMotor]   =  -40;
  		motor[rightMotor]  =  25;
  		previousBehavior = 1;
			break;

		case 2:
			writeDebugStreamLine("go forward");
			motor[leftMotor]   =  -30;
  		motor[rightMotor]  =  30;
  		previousBehavior = 2;
			break;

		case 3:
			writeDebugStreamLine("veer left");
			motor[leftMotor]   =  -30;
  		motor[rightMotor]  =  35;
  		previousBehavior = 3;
			break;

		case 4:
			writeDebugStreamLine("Make turn");
			//moveForward(160);
			//turnLeft90();
			if (previousBehavior == 4) {
				previousBehavior = 2;
				moveForward(160);
				turnLeft90();
			}
			else {
				previousBehavior = 4;
				moveForward(80);
				turnLeft90();
			}
			break;
	}

}

task main(){
	while (true) {
		follow();
	}
}

/*task main()
{
//  int bumper = 1;	              // normal bumper state = 1; when pressed = 0

  wait1Msec(2000);    					// give stuff time to turn on
	int Dist = 0;
	SensorValue[rightEncoder] = 0;
  while(SensorValue(rightEncoder) < 361)
  {
    //Joystick control of the motors
  	Dist = SensorValue(rightEncoder);
    //motor[leftMotor]   =  -vexRT[Ch3];       // up = CW
   //motor[rightMotor]  =  vexRT[Ch2];       // up = CCW

   motor[leftMotor]   =  -20;       // up = CW
   motor[rightMotor]  =  20;       // up = CCW

     writeDebugStreamLine("The Encoder says: %d", SensorValue(rightEncoder));
  }
}*/
