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

#define SERVO_UP 225
#define SERVO_DOWN 110

#define LEFT_TRIGGER 5
#define RIGHT_TRIGGER 6

#include "JoystickDriver.c"

int targetRight = 0,
		actualRight = 0,
		targetLeft = 0,
		actualLeft = 0;

bool motorsEnabled = true;

void init()
{
	bDisplayDiagnostics = false;

	servo[hook] = SERVO_UP;

	return;
}

void setDriveMotors(int left, int right)
{
	targetLeft = left;
	targetRight = right;
}

void stopDriveMotors()
{
	targetLeft = 0;
	targetRight = 0;
	actualLeft = 0;
	actualRight = 0;
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
	init();

	startTask(motorManagement);

	waitForStart();

	int joy1 = 0, joy2 = 0;

	while (true)
	{
		getJoystickSettings(joystick);

		joy1 = joystick.joy1_y1 * 0.75;
		joy2 = joystick.joy1_x2 * 0.75;

		nxtDisplayTextLine(1, "%d", joy1);
		nxtDisplayTextLine(2, "%d", joy2);
		nxtDisplayTextLine(3, "%d", SensorValue(sonar));

		if (abs(joy1) > 10)
		{
			setDriveMotors(joy1, joy1);
		}
		else if (abs(joy2) > 10)
		{
			setDriveMotors(joy2, -joy2);
		}
		else
		{
			stopDriveMotors();
		}

		if (joy1Btn(LEFT_TRIGGER) == 1)
		{
			servo[hook] = SERVO_DOWN;
		}

		if (joy1Btn(RIGHT_TRIGGER) == 1)
		{
			servo[hook] = SERVO_UP;
		}

		if (SensorValue(sonar) < 10 && servo[hook] == SERVO_UP && SensorValue(sonar) != 0)
		{
			motorsEnabled = false;
			stopDriveMotors();
			servo[hook] = SERVO_DOWN;
			//wait1Msec(250);
			motorsEnabled = true;
		}

		//if (SensorValue(sonar) > 20 && servo[hook] == SERVO_DOWN)
		//{
		//	servo[hook] = SERVO_UP;
		//}
	}
}
