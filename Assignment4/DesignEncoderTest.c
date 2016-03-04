#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  sonar,          sensorSONAR_cm)
#pragma config(Sensor, dgtl6,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  bumpFrontRight, sensorNone)
#pragma config(Sensor, dgtl9,  bumpFrontLeft,  sensorNone)
#pragma config(Sensor, dgtl11, followBump,     sensorNone)
#pragma config(Motor,  port1,           rightMotor,    tmotorVex393, openLoop)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex393, openLoop)

/*******************************************************************************/
bool wallTermin = (!SensorValue(bumpFrontLeft) || !SensorValue(bumpFrontRight));

void turnLeft90(int distance) {
	motor[leftMotor]   =  0;
  motor[rightMotor]  =  0;
  wait1Msec(500);
  SensorValue[rightEncoder] = 0;
	while((SensorValue(rightEncoder) < distance) || wallTermin){ //141.3  or  141.3 - 30
	//	if (!SensorValue(followBump) || !SensorValue(bumpFrontRight) || !SensorValue(bumpFrontLeft)) { //Alexander was here
	//		break;
	//	}
		motor[leftMotor] = 30;
		motor[rightMotor] = 30;
	}
		motor[leftMotor]   =  0;
		motor[rightMotor]  =  0;
}

void turnRight90(int distance) {
	motor[leftMotor]   =  0;
  motor[rightMotor]  =  0;
  wait1Msec(500);
  SensorValue[leftEncoder] = 0;
	while(SensorValue(leftEncoder) < distance || wallTermin){ //141.3  or  141.3 - 30

		motor[leftMotor] = -30;
		motor[rightMotor] = -30;
	}
		motor[leftMotor]   =  0;
		motor[rightMotor]  =  0;
}

void moveForward(int distance) {
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(1000);
	SensorValue[rightEncoder] = 0;
	while(SensorValue(rightEncoder) < distance || wallTermin) { //robot length around 160
		motor[leftMotor] = -30;
		motor[rightMotor] = 30;
	}
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

void moveBackward(int distance) {
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	wait1Msec(1000);
	SensorValue[rightEncoder] = 0;
	while(abs(SensorValue(rightEncoder)) < distance || wallTermin) {
		motor[leftMotor] = 30;
		motor[rightMotor] = -30;
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
	bool highWindow = SensorValue(sonar) > 9 && SensorValue(sonar) < 20;
	bool noWall = (SensorValue(sonar) == -1) || SensorValue(sonar) > 20 ;
	bool isWall = !SensorValue(followBump);
	bool frontWall = (!SensorValue(bumpFrontLeft) || !SensorValue(bumpFrontRight));
	//bool was4 = (previousBehavior == 4);


	//behavior decision based on prevouis state
	//bool outDriftCont;

	if (frontWall) { // back up, turn 90 degrees right
		behavior = 5;
	}

	else if (isWall && !lowWindow) {
		behavior = 6;
	}
	else if (lowWindow || isWall){ // (... || isWall) ? veer right
		behavior = 1;
	}
	else if (butterZone && !isWall){ // go forward
		behavior = 2;
	}
	else if (highWindow && !isWall){ // veer left
		behavior = 3;
	}
	else if (noWall) { // turn 90 degrees left
		behavior = 4;
	}


	writeDebugStreamLine("Sonar says: %d", SensorValue(sonar));
	writeDebugStreamLine("the behavior is: %d", behavior);

	switch(behavior){
		case 1:
			writeDebugStreamLine("veer right, no wall");
			motor[leftMotor]   =  -30;
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
				previousBehavior = 4;
				moveForward(120);
				turnLeft90(140);
				moveForward(320);
				if (SensorValue(sonar) > 30) {
					turnLeft90(120);
					moveForward(200);
					break;
				}
				else break;

		case 5:
			writeDebugStreamLine("Wall in front of me.");
				previousBehavior = 5;
				moveBackward(80);
				turnRight90(120);
				break;

		case 6:
			writeDebugStreamLine("Help I'm being oppressed.");
				previousBehavior = 6;
				moveBackward(20);
				turnRight90(30);
				break;
	}

}

task main(){
	//moveForward(160);
	while (true) {
		follow();
	/*
		wait1Msec(1000);
		bool isWall = !SensorValue(followBump);
		bool lowWindow = SensorValue(sonar) < 5 && SensorValue(sonar) > 0;
		bool makeFix = isWall && lowWindow;
		writeDebugStreamLine("Value is %d", makeFix);
*/
		//wait1Msec(1000);
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
