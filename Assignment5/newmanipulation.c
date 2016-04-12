#pragma config(Sensor, dgtl3,  rearArmBotSense, sensorNone)
#pragma config(Sensor, dgtl4,  rearArmTopSense, sensorNone)
#pragma config(Sensor, dgtl8,  botMotorButton, sensorNone)
#pragma config(Sensor, dgtl9,  topMotorButton, sensorNone)
#pragma config(Sensor, dgtl11, boten,          sensorQuadEncoder)
#pragma config(Motor,  port9, baseMotor,      tmotorVex393, openLoop)

//---------------------------------------------------------------------------
// move down takes an encoder distance and moves until that distance is met or
//the button behind the arm is pressed to prevent damage.
//---------------------------------------------------------------------------
void movedown(int encoderdis) {
	motor(baseMotor) = 0;
	SensorValue[boten] = 0;
	while((SensorValue(rearArmBotSense)) && (abs(SensorValue(boten)) <= encoderdis)){
			motor(baseMotor) = 120;
	}
	motor(baseMotor) = 0;
}
//---------------------------------------------------------------------------
// move up takes an encoder distance and moves until that distance is met or
//the button below the arm is pressed to prevent damage.
//---------------------------------------------------------------------------
void moveup(int encoderdis) {
	motor(baseMotor) = 0;
	SensorValue[boten] = 0;
	while((SensorValue(rearArmTopSense)) && (abs(SensorValue(boten)) <= encoderdis)){
			motor(baseMotor) = -120;
	}
	motor(baseMotor) = 0;
}

//---------------------------------------------------------------------------
// should move the arm up and down forever bouncing between buttons
//---------------------------------------------------------------------------

float thetatwo(float x, float y, float l1, float l2) {
	return (acos(((x*x)+(y*y)-(l1*l1)-(l2*l2))/(2*l1*l2)) *57.3);
}

//writeDebugStreamLine("Output is: %f",thetatwo(55,0,37,18));

task main()
{
	while(true){
	moveup(9999);
	movedown(9999);
	}
}
