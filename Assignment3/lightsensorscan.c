#pragma config(Sensor, in5,    LightIn,        sensorReflection)
#pragma config(Motor,  port5,  Servo,          tmotorServoContinuousRotation, openLoop)
#pragma config(Sensor, in1,    POT,            sensorPotentiometer)

int PtoD(int value) {
	return ((0.07 * value) + 11.13);
}

task main()
{

while(true) {

int x,y,ptsens; // x corresponds to the light sensor, y is the servo position corresopnding to the highest value of x, ptsens is the Potentiometer
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
}

motor[Servo] = y;
writeDebugStreamLine("Now facing brightest position, potentiometer value is %d, the angle is: %d",ptsens,PtoD(ptsens));
wait1Msec(3000);

}

}
