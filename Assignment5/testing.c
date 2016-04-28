
#pragma config(Sensor, dgtl8,  botMotorButton, sensorNone)
#pragma config(Sensor, dgtl9,  topMotorButton, sensorNone)
#pragma config(Sensor, dgtl3,  rearArmBotSense,     sensorNone)
#pragma config(Sensor, dgtl4,  rearArmTopSense,     sensorNone)
#pragma config(Motor,  port10, botMotor,     tmotorVex393, openLoop)

/*******************************************************************************/

int speed = 0;

task main() {
	while(true){
		if ((!SensorValue(botMotorButton)) && (!SensorValue(topMotorButton))){ //|| (!SensorValue(rearArmSense))) {
		while(true){
				motor(botMotor) = 0;
		}
	}

	bool lowTouch = !SensorValue(rearArmBotSense);
	bool highTouch = !SensorValue(rearArmTopSense);

	if (lowTouch) {
			speed = -120;
	}
	else if (highTouch) {
			speed = 120;
	}
	else {
			speed = 120;
	}

	while((SensorValue(lowTouch)) || (SensorValue(highTouch))) {
			motor(botMotor) = speed;
		}
	}
}
