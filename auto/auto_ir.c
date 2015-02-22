#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     left1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     left2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     right1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     right2,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    hook,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define SERVO_UP 230
#define SERVO_DOWN 180

#include "JoystickDriver.c"
#include "hitechnic-irseeker-v2.h"

tHTIRS2 irSeeker;

const int gyroOffset = SensorValue(gyro);

int targetRight = 0,
		actualRight = 0,
		targetLeft = 0,
		actualLeft = 0;

bool motorsEnabled = true;

void init()
{
	initSensor(&irSeeker, S3);

	servo[hook] = SERVO_UP;

	return;
}

void setDriveMotors(int left, int right)
{
	targetLeft = left;
	targetRight = right;
}

void setDriveMotorsDirect(int left, int right)
{
	targetLeft = left;
	actualLeft = left;
	targetRight = right;
	actualRight = right;
}

void stopDriveMotors()
{
	targetLeft = 0;
	targetRight = 0;
	actualLeft = 0;
	actualRight = 0;
}

float readGyro()
{
	return -((float) (SensorValue(gyro) - gyroOffset));
}

int readIR()
{
	readSensor(&irSeeker);
	return irSeeker.acDirection;
}

int readSonar()
{
	int reading = SensorValue(sonar);
	return reading;
}

void turnLeft(float degrees)
{
	setDriveMotors(-20, 20);
	while (degrees > 0)
	{
		nxtDisplayTextLine(1, "%d", degrees);
		degrees -= 0.001 * readGyro();
		wait1Msec(1);
	}
	stopDriveMotors();
}

void turnRight(float degrees)
{
	setDriveMotors(20, -20);
	while (degrees > 0)
	{
		degrees += 0.001 * readGyro();
		wait1Msec(1);
	}
	stopDriveMotors();
}

task motorManagement()
{
	while (true)
	{
		if (actualLeft < targetLeft)
		{
			actualLeft++;
		}
		else if (actualLeft > targetLeft)
		{
			actualLeft--;
		}

		if (actualRight < targetRight)
		{
			actualRight++;
		}
		else if (actualRight > targetRight)
		{
			actualRight--;
		}
		if (motorsEnabled)
		{
			motor[left1] = actualLeft;
			motor[left2] = actualLeft;
			motor[right1] = -actualRight;
			motor[right2] = actualRight;
		}
		else
		{
			motor[left1] = 0;
			motor[left2] = 0;
			motor[right1] = 0;
			motor[right2] = 0;
		}
		wait1Msec(5);
	}
}

task main()
{
	bDisplayDiagnostics = false;

	startTask(motorManagement);

	init();

	waitForStart();

	setDriveMotors(80, 80);

	//if the sonar sensor is operational, it is preferable to use it instead of a delay
	//while (readSonar() < 100) { }

	wait1Msec(1000);

	stopDriveMotors();

	int ir = readIR();

	if (ir == 5)
	{
		turnLeft(40);
	}
	else if (ir == 6)
	{
		turnLeft(70);
	}

	wait1Msec(500);

	setDriveMotorsDirect(100, 100);
	wait1Msec(1000);
	stopDriveMotors();

	nxtDisplayTextLine(0, "%d", readIR());
	nxtDisplayTextLine(1, "%d", readSonar());

	while (true) { }
}
