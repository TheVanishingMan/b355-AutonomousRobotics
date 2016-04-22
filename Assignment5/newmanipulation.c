#pragma config(Sensor, dgtl1,  topen,          sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rearArmBotSense, sensorNone)
#pragma config(Sensor, dgtl4,  rearArmTopSense, sensorNone)
#pragma config(Sensor, dgtl7,  armChanger,     sensorNone)
#pragma config(Sensor, dgtl8,  botMotorButton, sensorNone)
#pragma config(Sensor, dgtl9,  topMotorButton, sensorNone)
#pragma config(Sensor, dgtl11, boten,          sensorQuadEncoder)
#pragma config(Motor,  port8,           baseMotor,     tmotorVex393, openLoop)
#pragma config(Motor,  port9,           elbowMotor,    tmotorVex393, openLoop)

//---------------------------------------------------------------------------
// move arm takes an encoder distance and moves until that distance is met or
// a button is pressed to prevent damage.
//---------------------------------------------------------------------------
void moveArm(int encoderdis, int dir) { // dir will either be 1 for down or -1 for up
	motor(baseMotor) = 0;
	SensorValue[boten] = 0;
	while((SensorValue(rearArmBotSense)) && (abs(SensorValue(boten)) <= encoderdis)){
			motor(baseMotor) = (120 * dir);
	}
	motor(baseMotor) = 0;
}

//---------------------------------------------------------------------------
// should move the arm up and down forever bouncing between buttons
//---------------------------------------------------------------------------

float thetaTwo(float x, float y, float l1, float l2) {
	return (acos(((x*x)+(y*y)-(l1*l1)-(l2*l2))/(2*l1*l2)) *57.3);
}

float thetaOne(float x, float y, float theta, float l2) {
	return (atan((y/x) - (asin((l2 * (sin(theta)))/sqrt((x*x) + (y*y))))) *57.3);
}

//writeDebugStreamLine("Output is: %f",thetatwo(55,0,37,18));

task main()
{
	while(true){
	moveArm(9999,-1);
	moveArm(9999,1);
	}
}
