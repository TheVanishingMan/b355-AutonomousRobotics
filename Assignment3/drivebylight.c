#pragma config(Sensor, dgtl10, bump1,          sensorTouch)
#pragma config(Sensor, dgtl11, bump2,          sensorTouch)
#pragma config(Motor,  port2,           rightMotor,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorVex393, openLoop)
#pragma config(Motor,  port5,  Servo,          tmotorServoContinuousRotation, openLoop)
#pragma config(Sensor, in5,    LightIn,        sensorReflection)
#pragma config(Sensor, in1,    POT,            sensorPotentiometer)

// Potentiometer value to degrees
int PtoD(int value) {
	return ((0.07 * value) + 11.13);
}

bool threshold = false;

void wait(int value){

	while(value > 0){
		if (SensorValue[bump1] || SensorValue[bump2]) {
	  	writeDebugStreamLine("bumped-backing up");
	    motor[leftMotor] = -25; //fullspeed backwards
	    motor[rightMotor] = -25; //fullspeed backwards
	    wait1Msec(1000);  // keep backing up for 1000ms (1 sec)
    	motor[leftMotor] = -75; //fullspeed backwards
	    motor[rightMotor] = 75; //fullspeed backwards
	    wait1Msec(1000);  // keep backing up for 1000ms (1 sec)
	    motor[leftMotor]  = 0;  //stop motors
	    motor[rightMotor] = 0;  //stop motors
	    wait1Msec(100);
	    break;
		}
		value--;
	}
}




void wander(int value) {
	while(value > 0) {
		motor[leftMotor] = (random(10) * 10);
		motor[rightMotor] = (random(10) * 10);
		wait(300);

	/*	if (SensorValue[bump1] || SensorValue[bump2]) {
	    writeDebugStreamLine("bumped-backing up");
	    motor[leftMotor] = -25; //fullspeed backwards
	    motor[rightMotor] = -25; //fullspeed backwards
	    wait1Msec(1000);  // keep backing up for 1000ms (1 sec)
    	motor[leftMotor] = -75; //fullspeed backwards
	    motor[rightMotor] = 75; //fullspeed backwards
	    wait1Msec(1000);  // keep backing up for 1000ms (1 sec)

	    motor[leftMotor]  = 0;  //stop motors
	    motor[rightMotor] = 0;  //stop motors
	    wait1Msec(3000);
 		} */
 		wait1Msec(2000);

		value--;
	}
}



int towardLight() {

	int x,y,ptsens;
	x = SensorValue[LightIn];

	writeDebugStreamLine("%d",SensorValue[POT]);
	y = -127; // value of e'y'e
	motor[Servo] = y;
	wait1Msec(1000);

	for(int i= -127; i<127; i=i+4) {

		motor[Servo] = i;
		wait1Msec(100);
		if (x >= SensorValue[LightIn]) {
			x = SensorValue[LightIn];
			ptsens = SensorValue[POT];
			y = i;
		}
	}

	motor[Servo] = y;
	writeDebugStreamLine("Now facing brightest position, potentiometer value is %d, the angle is: %d",ptsens,PtoD(ptsens));
	wait1Msec(2000);
	return PtoD(y);
}


void turnleft(int turntimes){
turntimes = turntimes/5;
while(turntimes > 0) {
	motor[leftMotor] =  30;
	motor[rightMotor]= -30;
	wait1Msec(25);
	motor[leftMotor] =  0;
	motor[rightMotor]=  0;
	turntimes = turntimes - 1;
	writeDebugStreamLine("the turn time says: %d", turntimes);
}
}

void turnright(int turntimes){
turntimes = turntimes/5;
while(turntimes > 0) {
	motor[leftMotor] = - 30;
	motor[rightMotor]= 30;
	wait1Msec(25);
	motor[leftMotor] =  0;
	motor[rightMotor]=  0;
	turntimes = turntimes - 1;
	writeDebugStreamLine("the turn time says: %d", turntimes);
}
}


int scanner(int scantimes){
	int x,y,ptsens; // x corresponds to the light sensor, y is the servo position corresopnding to the highest value of x, ptsens is the Potentiometer
	while(scantimes > 0) {


		x = SensorValue[LightIn]; // take an initial reading of the Light, this will be comared in the for loop
		//ptsens = SensorValue[POT];// set ptsens to the value of the Potentiometer

		//writeDebugStreamLine("%d",x); //print the current position of the Servo, mostly for visually representing what is happening in real life.
		writeDebugStreamLine("%d",SensorValue[POT]); //print value of the potentiometer.
		y = -127; // set the initial y value to -127 (minimum), later the for loop will increment this value by 4 each time
		motor[Servo] = y; // set the motor position to be y
		wait1Msec(1000); // wait a second (this is important when the "eye" is reseting)

		for(int i= -127; i<127; i=i+4) { // start at -127, increments by 4, "stops at 127" (technically 125)

			motor[Servo] = i; // set Servo to the value of i (-127, -123, -119, ... 121, 125)
			wait1Msec(100); // wait a bit in between the values (for accurate readings)
			//writeDebugStreamLine("The current position is %d", i);
			//writeDebugStreamLine("potentiometer value is %d", SensorValue[POT]); // print the potentiometer values
			if (x >= SensorValue[LightIn]) { // compare the initial reading to the
				x = SensorValue[LightIn];
				ptsens = SensorValue[POT];
				y = i;
				//wait1Msec(150);
			}
			scantimes = scantimes - 1;
		}
	}


motor[Servo] = y;
writeDebugStreamLine("Now facing brightest position, potentiometer value is %d, the angle is: %d",ptsens,PtoD(ptsens));
wait1Msec(2000);
scantimes = scantimes - 1;
if(SensorValue[LightIn] > 900){
	threshold = true;
}
return PtoD(ptsens);
}


task main(){

  wait1Msec(2000);    					// give stuff time to turn on
  while(true){
  	int x = 0;
  	int y = 0;
  if(!threshold){
  	 x =	(random(10) * 10);
  	 y = (random(10) * 10);
  }
  else{
  	 x = 100;
  	 y = 100;
}
  int z = 8000;
  while(z > 0){

  	//int lightVal = SensorValue(LightIn);   -----wha does this do
  	//float speed = (float)lightVal*(-127.0/970.0) + 12700.0/97.0;

		//writeDebugStream("Speed = %d\n", (int)speed);
		//writeDebugStream("Light Sensor = %d\n", lightVal);

		motor[leftMotor] = x;
		motor[rightMotor] = y;

    //If the bumper is press, automatically backup
    while(SensorValue[bump1] || SensorValue[bump2])
    {
	    writeDebugStreamLine("bumped-backing up");
	    motor[leftMotor] = -25; //fullspeed backwards
	    motor[rightMotor] = -25; //fullspeed backwards
	    wait1Msec(1000);  // keep backing up for 1000ms (1 sec)
    	motor[leftMotor] = -75; //fullspeed backwards
	    motor[rightMotor] = 75; //fullspeed backwards
	    wait1Msec(1000);  // keep backing up for 1000ms (1 sec)

	    motor[leftMotor]  = 0;  //stop motors
	    motor[rightMotor] = 0;  //stop motors
	    wait1Msec(1000);

   }
   z= z-1;
  	}

  if(threshold){
  	int wheretoturn = scanner(1);
  	if (wheretoturn < 88){
  		turnleft(wheretoturn);

  	}
  	if (wheretoturn > 92){
  		wheretoturn = 180 - wheretoturn;
  		turnright(wheretoturn);

  	}
  }
  	writeDebugStreamLine("Im moving forward");

  	motor[Servo] = 0;
  	wait1Msec(2000);
	}
}
