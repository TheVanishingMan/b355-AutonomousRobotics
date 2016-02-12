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
		x = SensorValue[LightIn]; // initial reading of the Light
		writeDebugStreamLine("%d",SensorValue[POT]); //print value of the potentiometer.
		y = -127; // set the initial y value to -127 (minimum), later the for loop will increment this value by 4 each time
		motor[Servo] = y; // set the motor position to be y
		wait1Msec(1000); // wait a second (this is important when the "eye" is reseting)

		for(int i= -120; i<120; i=i+4) { // start at -127, increments by 4, "stops at 127" (technically 125)
			writeDebugStreamLine("Pot. is: %d",SensorValue[POT]);
			motor[Servo] = i; // set Servo to the value of i (-127, -123, -119, ... 121, 125)
			wait1Msec(100); // wait a bit in between the values (for accurate readings)
			if (x >= SensorValue[LightIn]) { // compare the initial reading to the
				x = SensorValue[LightIn];
				ptsens = SensorValue[POT];
				y = i;
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
	writeDebugStreamLine("We need to turn to the position: %d",PtoD(ptsens));
return PtoD(ptsens);
}

task main() {
	int threshold = 1000;

	while(true) {
  	int wheretoturn = scanner(1);
  	if ((wheretoturn < 82) && threshold) {
  			turnleft(90 - wheretoturn);
		}
  	if ((wheretoturn > 98) && threshold) {
  			turnright(180 - wheretoturn);
  	}
  	if ((wheretoturn >= 82) && (wheretoturn <= 98) && threshold) {
  			while(!SensorValue[bump1] && !SensorValue[bump2]) {
	   			 motor[leftMotor]  = 50;  //stop motors
	   			 motor[rightMotor] = 50;  //stop motors
	   		}
	   		motor[leftMotor] = -25; //for funsies
	   		motor[rightMotor] = -25;
	   		wait1Msec(300);
	   		motor[leftMotor] = -120;
	   		motor[rightMotor] = 120;
	   		wait1Msec(1000);
	   		break;
  	}
  	else { turnleft(50);
  	}
  	wait1Msec(1000);

	}
}
