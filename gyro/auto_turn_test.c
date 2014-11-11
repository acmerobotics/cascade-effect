#pragma config(Hubs,  S1, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C2_1,     rightMotor,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     leftMotor,    tmotorTetrix, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const tSensors GyroSensor = (tSensors) S2;

const int offset = SensorValue(GyroSensor);

float normal = 1.2;

void turnLeft(int degrees)
{
	if (degrees > 0)
	{
		motor[leftMotor] = -80;
		motor[rightMotor] = 80;
	}
	else
	{
		motor[leftMotor] = 80;
		motor[rightMotor] = -80;
	}
	long gyro_value;
	long time = nSysTime, newTime;
	float degree_value = 0;
	while (true)
	{
		gyro_value = (SensorValue(GyroSensor)-offset) * normal;
		newTime = nSysTime;
		degree_value += (((float) newTime - time) / 1000.0) * gyro_value;
		displayTextLine(2, "Turned %f degrees", degree_value);
		displayTextLine(3, "Timer: %d", newTime-time);
		displayTextLine(1, "Gyro reading: %d", gyro_value);
		time = newTime;
		if (abs(degree_value) > abs(degrees))
		{
			motor[leftMotor] = 0;
			motor[rightMotor] = 0;
			return;
		}
	}
}

void turnRight(int degrees)
{
	turnLeft(-degrees);
}

#include "JoystickDriver.c"

task main()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if (joy1Btn(5) == 1)
		{
			normal += 0.25;
		}
		else if (joy1Btn(6) == 1)
		{
			normal -= 0.25;
		}
		displayTextLine(5, "Normal is %f", normal);
		turnLeft(90);
		wait1Msec(1500);
	}
}
