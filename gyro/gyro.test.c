const tSensors GyroSensor = (tSensors) S4;

#define offset 598

long gyro_value, time, newTime;
float degree_value;
bool turning = false;

task main()
{
	while (true)
	{
		gyro_value = SensorValue(GyroSensor)-offset;
		if (abs(gyro_value) > 15)
		{
			if (!turning)
			{
				time = nSysTime;
				turning = true;
				degree_value = 0;
			}
			else
			{
				newTime = nSysTime;
				degree_value += (((float) newTime - time) / 1000.0) * gyro_value;
				displayTextLine(2, "Turned %f degrees", degree_value);
				displayTextLine(3, "Timer: %d", newTime-time);
				time = newTime;
			}
		}
		else
		{
			turning = false;
		}
		displayTextLine(1, "Gyro reading: %d", gyro_value);
    //wait1Msec(2);
	}
}
