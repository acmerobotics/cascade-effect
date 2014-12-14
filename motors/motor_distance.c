#pragma config(Hubs,  S1, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S4,     ,               sensorTouch)
#pragma config(Motor,  mtr_S1_C2_1,     leftMotor,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     rightMotor,    tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)

void driveForward(int feet)
{
	int milliSec = round(1000 * ((float) feet) / PI);
	motor[leftMotor] = 80;
	motor[rightMotor] = 80;
	wait1Msec(milliSec);
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

task main()
{
	driveForward(5);
}
