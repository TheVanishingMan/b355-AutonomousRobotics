#pragma config(Sensor, in3,    light3,         sensorReflection)
#pragma config(Sensor, dgtl11, bump1,          sensorNone)
#pragma config(Sensor, dgtl12, bump2,          sensorNone)
#pragma config(Motor,  port2,           rightMotor,    tmotorVex393, openLoop)
#pragma config(Motor,  port3,          leftMotor,     tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*******************************************************************************
*
*  This file is meant as an introduction and as a template for developing
*  programs to run on the Vex controller.
*
*******************************************************************************/

/*******************************************************************************
*
*	main
*
*******************************************************************************/
task main()
{
//  int bumper = 1;	              // normal bumper state = 1; when pressed = 0

  wait1Msec(2000);    					// give stuff time to turn on

  while(true)
  {
  	// For testing purposes print the raw value of the light sensor
  	//writeDebugStreamLine("The value of the light sensor is: %d", SensorValue[light3]);


    int motorspeed; // declare a variable that will be the eventual speed of the motors

    //invert the raw sensor value by subtracting from max sensor value (1023)
    motorspeed = ((1023 - SensorValue[light3]) * .12414); //multiply inverted raw by the max motorspeed over the max sensorvalue

    motor[leftMotor] = -motorspeed; // this motor is mirrored of the right so set to negative motorspeed
    motor[rightMotor] = motorspeed; // set value of right motor to motorspeed

    //print value of motorspeed for testing purposes
    //writeDebugStreamLine("The value of the motorspeed is: %d", motorspeed);



  }
}