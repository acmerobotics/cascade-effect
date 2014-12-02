#pragma config(Sensor, S3,     HTIRS2,              sensorI2CCustom)

#include "hitechnic-irseeker-v2.h"

task main()
{
	initSensor((tHTIRS2Ptr) HTIRS2, (tMUXSensor) S3);
}
