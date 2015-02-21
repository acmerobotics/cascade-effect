const tSensors GyroSensor = (tSensors) S2;

#define offset 598

long gyro_value, time, newTime;
float degree_value;
bool turning = false;

task main()
{
	while (true)
	{
		gyro_value = SensorValue(GyroSensor) - offset;
		displayTextLine(1, "Gyro reading: %d", gyro_value);
    //wait1Msec(2);
	}
}
