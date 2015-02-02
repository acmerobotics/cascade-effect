#include "hitechnic-irseeker-v2.h"

tHTIRS2 irSeeker;

task main()
{

	initSensor(&irSeeker, S3);
	while (true)
	{
		readSensor(&irSeeker);
		nxtDisplayTextLine(1, "%d", irSeeker.acDirection);
	}

}
