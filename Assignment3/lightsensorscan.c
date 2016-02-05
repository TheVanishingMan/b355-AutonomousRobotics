#pragma config(Sensor, in5,    LightIn,        sensorReflection)
#pragma config(Motor,  port5,  Servo,          tmotorServoContinuousRotation, openLoop)
#pragma config(Sensor, in1,    POT,            sensorPotentiometer)

task main()
{

while(true) {

int x,y,potsensor;
x = SensorValue[LightIn];
potsensor = SensorValue[POT];

writeDebugStreamLine("%d",x);
y = -127;
motor[Servo] = y;
wait1Msec(1000);

for(int i= -127; i<127; i=i+4) {

	motor[Servo] = i;
	wait1Msec(50);
	writeDebugStreamLine("The current position is %d", i);

	if (x >= SensorValue[LightIn]) {
		x = SensorValue[LightIn];
		//motor[Servo] = y - 20;
		y = i;
		wait1Msec(150);
		//writeDebugStreamLine("The value of the brightest light is: %d. The brightest position is %d \n", x,y);
	}
}

motor[Servo] = y;
writeDebugStreamLine("Now facing brightest position");
wait1Msec(3000);

}

}
/*
while(true)
{
	int x,y;

	motor[Servo] = -127;  //positions the servo motor to one of the extremes; range : -127  to 127
	wait1Msec(5000); // wait a long time at first to avoid damage
  x = SensorValue[LightIn]; //change x to be the value of the light at the area
  writeDebugStreamLine("The value of the light sensor is: %d", x);
  y = -127;

  motor[Servo] = -107; //rotate to new position
  wait1Msec(500); //wait to avoid damage
  if (x <= SensorValue[LightIn]){ //only mark this location as the brightest if it is the brightest
  	x = LightIn; //new brighest location
  	writeDebugStreamLine("The value of the light sensor is: %d", x);
  	y = -107; //if we change this to the brighest remember it for next time
  	}

  motor[Servo] = -87;
  wait1Msec(500);
  if(x <= SensorValue[LightIn]){
  	x = LightIn;
  	writeDebugStreamLine("The value of the light sensor is: %d", x);
  	y = -87;
  	}


  motor[Servo] = -67;
  wait1Msec(500);
  if(x <= SensorValue[LightIn]){
  	x = LightIn;
  	writeDebugStreamLine("The value of the light sensor is: %d", x);
  	y = -67;
  	}


  motor[Servo] = -47;
  wait1Msec(500);
  if(x <= SensorValue[LightIn]){
  	x = LightIn;
  	writeDebugStreamLine("The value of the light sensor is: %d", SensorValue[LightIn]);
  	y = -47;
  	}


  motor[Servo] = -27;
  wait1Msec(500);
  if(x <= SensorValue[LightIn]){
  	x = LightIn;
  	writeDebugStreamLine("The value of the light sensor is: %d", SensorValue[LightIn]);
  	y = -27;
  	}


  motor[Servo] = -7;
  wait1Msec(500);
  if(x <= SensorValue[LightIn]){
  	x = LightIn;
  	y = -7;
  	writeDebugStreamLine("The value of the light sensor is: %d", SensorValue[LightIn]);
  	}


  motor[Servo] = 17;
  wait1Msec(500);
  if(x <= SensorValue[LightIn]){
  	x = LightIn;
  	writeDebugStreamLine("The value of the light sensor is: %d", SensorValue[LightIn]);
  	y = 17;
  	}


  motor[Servo] = 37;
  wait1Msec(500);
  if(x <= SensorValue[LightIn]){
  	x = LightIn;
  	y = 37;
  	writeDebugStreamLine("The value of the light sensor is: %d", SensorValue[LightIn]);
  	}


  motor[Servo] = 57;
  wait1Msec(500);
  if(x <= SensorValue[LightIn]){
  	x = LightIn;
  	writeDebugStreamLine("The value of the light sensor is: %d", SensorValue[LightIn]);
  	y = 127;
  	}


  motor[Servo] = 77;
  wait1Msec(500);
  if(x <= SensorValue[LightIn]){
  	x = LightIn;
  	writeDebugStreamLine("The value of the light sensor is: %d", SensorValue[LightIn]);
  	y = 127;
  	}


  motor[Servo] = 97;
  wait1Msec(500);
  if(x <= SensorValue[LightIn]){
  	x = LightIn;
  	writeDebugStreamLine("The value of the light sensor is: %d", SensorValue[LightIn]);
  	y = 97;
  	}


  motor[Servo] = 117;
  wait1Msec(500);
  if(x <= SensorValue[LightIn]){
  	x = LightIn;
  	writeDebugStreamLine("The value of the light sensor is: %d", SensorValue[LightIn]);
  	y = 117;
  	}
  	//now look go back to the position where we found the brighest light
  	motor[Servo] = y;
  	wait1Msec(1500);
}

}
*/
