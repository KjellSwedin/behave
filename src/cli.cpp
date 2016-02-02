#include <iostream>
#include <iomanip>
#include "behave.h"
#include <time.h>
#include <cmath>

#include <stdlib.h>
#include <stdio.h>
#include "behave.h"

#define EQUAL(a,b) (strcmp(a,b)==0)

const int REQUIRED_ARG_COUNT = 10;

enum 
{
	FUEL_MODEL_NUMBER,
	ONE_HOUR,
	TEN_HOUR,
	HUNDRED_HOUR,
	LIVE_HERB,
	LIVE_WOODY,
	WIND_SPEED,
	WIND_DIRECTION,
	SLOPE,
	ASPECT
};

void Usage()
{
	printf("Usage:\n");
	printf("behave_cli [--fuel_model_number number]      Required\n");
	printf("           [--1hr percent]                   Required\n");
	printf("           [--10hr percent]                  Required\n");
	printf("           [--100hr percent]                 Required\n");
	printf("           [--live_herb percent]             Required\n");
	printf("           [--live_woody percent]            Required\n");
	printf("           [--wind_speed speed]              Required\n");
	printf("           [--wind_direction degrees]        Required\n");
	printf("           [--slope degrees]                 Required\n");
	printf("           [--aspect degrees]                Required\n");
	printf("           [--direction-of-interest degrees] Optional\n");
	printf("           [--output-to-file]                Optional\n");
	printf("           [--file-name name]                Optional\n");
	printf("           [--append]                        Optional\n");
	printf("           [--run-identifier name]           Optional\n");
	//printf("           [--verbose]\n");
	printf("\n");
	printf("Arguments:\n");
	printf("\n");
	printf("--fuel-model-number <number>        Required: The fuel model number \n");
	printf("--1hr <percent>                     Required: 1-hr fuel moisture\n");
	printf("--10hr <percent>                    Required: 10-hr fuel moisture\n");
	printf("--100hr <percent>                   Required: 100-hr fuel moisture\n");
	printf("--live-herb <percent>               Required: Live herbacious fuel moisture\n");
	printf("--live-woody <percent>              Required: Live woody fuel moisture\n");
	printf("--wind-speed <speed>                Required: Mid-flame wind speed\n");
	printf("--wind-direction <degrees>          Required: Wind direction\n");
	printf("--slope <degrees>                   Required: Slope\n");
	printf("--aspect <degrees>                  Required: Aspect\n");
	printf("--direction-of-interest <degrees>   Optional: calculate spread rate in a\n");
	printf("                                       direction other than max\n");
	printf("--output-to-file                    Optional: output to a txt file\n");
	printf("                                       default file name: output.txt\n");
	printf("--file-name <name>                  Optional: specify output file name\n");
	printf("--output-to-file                    Optional: append run to output file\n");
	printf("--run-identifier <name>             Optional: specify identifier for run");
	exit(1);
}

int parseInteger(int i, std::string argString)
{
	int retVal = -1;
	if (argString.c_str() != NULL)
	{
		char* end;
		long val = strtol(argString.c_str(), &end, 10);
		if (!end[0] && val >= 0)
		{
			retVal = val;
		}
	}
	return retVal;
}

double parseDouble(int i, std::string argString)
{
	double retVal = -1;
	if (argString.c_str() != NULL)
	{
		char* end;
		double val = strtod(argString.c_str(), &end);
		if (!end[0] && val >= 0)
		{
			retVal = val;
		}
	}
	return retVal;
}

void checkMoistureBound(double moisture)
{
	if ((moisture < 0.0) || (moisture > 300.00))
	{
		//throw std::runtime_error("ERROR: Moisture cannot negative or greater than 300.\n");
		printf("ERROR: Moisture cannot negative or greater than 300.\n");
		exit(1);
	}
}

void checkAngleBound(double angle)
{
	if ((angle < 0.0) || (angle > 360.00))
	{
		//throw std::runtime_error("ERROR: Angles cannot negative or greater than 360.\n");
		printf("ERROR: Angles cannot negative or greater than 360.\n");
		exit(1);
	}
}

std::string getArgumentName(int argIndex)
{
	std::string retString = "";
	if (argIndex == ASPECT)
	{
		retString = "aspect";
	}
	if (argIndex == FUEL_MODEL_NUMBER)
	{
		retString = "fuel model number";
	}
	if (argIndex == HUNDRED_HOUR)
	{
		retString = "100-hr moisture";
	}
	if (argIndex == LIVE_HERB)
	{
		retString = "live herbaceous moisture";
	}
	if (argIndex == LIVE_WOODY)
	{
		retString = "live woody moisture";
	}
	if (argIndex == ONE_HOUR)
	{
		retString = "1-hr moisture";
	}
	if (argIndex == SLOPE)
	{
		retString = "slope";
	}
	if (argIndex == TEN_HOUR)
	{
		retString = "10-hr moisture";
	}
	if (argIndex == WIND_DIRECTION)
	{
		retString = "wind direction";
	}
	if (argIndex == WIND_SPEED)
	{
		retString = "wind speed";
	}
	return retString;
}

int main(int argc, char *argv[])
{
	const int MAX_ARG_INDEX = argc - 1;

	bool requiredArgArray[REQUIRED_ARG_COUNT];
	bool isOutputtingToFile = false;
	bool hasSpecifiedFileName = false;
	bool isAppending = false;
	bool hasDirectionOfInterest = false;
	bool hasRunIdentifier = false;
	int i;
	std::string fileName = "output.txt"; // default output file name
	std::string runIdentifier = "";

	// Surface Fire Inputs;
	int fuelModelNumber = -1;
	double moistureOneHr = -1.0;
	double moistureTenHr = -1.0;
	double moistureHundredHr = -1.0;
	double moistureLiveHerb = -1.0;
	double moistureLiveWoody = -1.0;
	double windSpeed = -1.0;
	double windDirection = -1.0;
	double slope = -1.0;
	double aspect = -1.0;
	double directionOfMaxSpread = -1.0;
	double flameLength = -1.0;
	double directionOfInterest = -1.0; 
	double spreadRate = 0;

	for (int index = 0; index < REQUIRED_ARG_COUNT; index++)
	{
		requiredArgArray[index] = false;
	}

	Behave behave;
	behave.setSlopeInputToDegrees();
	behave.setWindAndSpreadAnglesRelativeToNorth();

	// Parse command line arguments
	if (argc == 1)
	{
		Usage();
	}
	i = 1;

	while(i < argc)
	{
		if (EQUAL(argv[i], "--fuel-model-number"))
		{
			if ((i + 1) <= MAX_ARG_INDEX)
			{
				std::string argString = argv[++i];
				fuelModelNumber = parseInteger(i, argString);
			}
			if (fuelModelNumber <= 0)
			{
				printf("ERROR: No valid value entered for fuelModelNumber");
				Usage();
				exit(1);
			}
			else if (!behave.isFuelModelDefined(fuelModelNumber))
			{
				printf("ERROR: Fuel model %d is undefined.\n", fuelModelNumber);
				Usage();
				exit(1);
			}
			requiredArgArray[FUEL_MODEL_NUMBER] = true;
		}
		else if(EQUAL(argv[i], "--1hr"))
		{
			if ((i + 1) <= MAX_ARG_INDEX)
			{
				std::string argString = argv[++i];
				moistureOneHr = parseDouble(i, argString);
			}
			if (moistureOneHr < 0)
			{
				printf("ERROR: No valid value entered for 1-hr moisture\n");
				Usage();
				exit(1);
			}
			checkMoistureBound(moistureOneHr);
			moistureOneHr /= 100;
			requiredArgArray[ONE_HOUR] = true;
		}
		else if(EQUAL(argv[i], "--10hr"))
		{
			if ((i + 1) <= MAX_ARG_INDEX)
			{
				std::string argString = argv[++i];
				moistureTenHr = parseDouble(i, argString);
			}
			if (moistureTenHr < 0)
			{
				printf("ERROR: No valid value entered for 10-hr moisture\n");
				Usage();
				exit(1);
			}
			checkMoistureBound(moistureTenHr);
			moistureTenHr /= 100;
			requiredArgArray[TEN_HOUR] = true;
		}
		else if(EQUAL(argv[i], "--100hr"))
		{
			if ((i + 1) <= MAX_ARG_INDEX)
			{
				std::string argString = argv[++i];
				moistureHundredHr = parseDouble(i, argString);
			}
			if (moistureHundredHr < 0)
			{
				printf("ERROR: No valid value entered for 100-hr moisture\n");
				Usage();
				break;
			}
			checkMoistureBound(moistureHundredHr);
			moistureHundredHr /= 100;
			requiredArgArray[HUNDRED_HOUR] = true;
		}
		else if(EQUAL(argv[i], "--live-herb"))
		{
			if ((i + 1) <= MAX_ARG_INDEX)
			{
				std::string argString = argv[++i];
				moistureLiveHerb = parseDouble(i, argString);
			}
			if (moistureLiveHerb < 0)
			{
				printf("ERROR: No valid value entered for live herbaceous moisture\n");
				Usage();
				break;
			}
			checkMoistureBound(moistureLiveHerb);
			moistureLiveHerb /= 100;
			requiredArgArray[LIVE_HERB] = true;
		}
		else if(EQUAL(argv[i], "--live-woody"))
		{
			if ((i + 1) <= MAX_ARG_INDEX)
			{
				std::string argString = argv[++i];
				moistureLiveWoody = parseDouble(i, argString);
			}
			if (moistureLiveWoody < 0)
			{
				printf("ERROR: No valid value entered for live woody moisture\n");
				Usage();
				break;
			}
			checkMoistureBound(moistureLiveWoody);
			moistureLiveWoody /= 100;
			requiredArgArray[LIVE_WOODY] = true;
		}
		else if(EQUAL(argv[i], "--wind-speed"))
		{
			if ((i + 1) <= MAX_ARG_INDEX)
			{
				std::string argString = argv[++i];
				windSpeed = parseDouble(i, argString);
			}
			if (windSpeed < 0)
			{
				printf("ERROR: No valid value entered for wind speed\n");
				Usage();
				break;
			}
			requiredArgArray[WIND_SPEED] = true;
		}
		else if(EQUAL(argv[i], "--wind-direction"))
		{
			if ((i + 1) <= MAX_ARG_INDEX)
			{
				std::string argString = argv[++i];
				windDirection = parseDouble(i, argString);
			}
			if (windDirection < 0)
			{
				printf("ERROR: No valid value entered for wind direction\n");
				Usage();
				break;
			}
			checkAngleBound(windDirection);
			requiredArgArray[WIND_DIRECTION] = true;
		}
		else if(EQUAL(argv[i], "--slope"))
		{
			if ((i + 1) <= MAX_ARG_INDEX)
			{
				std::string argString = argv[++i];
				slope = parseDouble(i, argString);
			}
			if (slope < 0)
			{
				printf("ERROR: No valid value entered for slope\n");
				Usage();
				break;
			}
			checkAngleBound(slope);
			requiredArgArray[SLOPE] = true;
		}
		else if (EQUAL(argv[i], "--aspect"))
		{
			if ((i + 1) <= MAX_ARG_INDEX)
			{
				std::string argString = argv[++i];
				aspect = parseDouble(i, argString);
			}
			if (aspect < 0)
			{
				printf("ERROR: No valid value entered for aspect\n");
				Usage();
				break;
			}
			checkAngleBound(aspect);
			requiredArgArray[ASPECT] = true;
		}
		else if (EQUAL(argv[i], "--direction-of-interest"))
		{
			if ((i + 1) <= MAX_ARG_INDEX)
			{
				std::string argString = argv[++i];
				directionOfInterest = parseDouble(i, argString);
			}
			if (directionOfInterest < 0)
			{
				printf("ERROR: No valid value entered for direction of interest\n");
				Usage();
				break;
			}
			checkAngleBound(directionOfInterest);
			hasDirectionOfInterest = true;
		}
		else if(EQUAL(argv[i], "--output-to-file"))
		{
			isOutputtingToFile = true;
		}
		else if (EQUAL(argv[i], "--file-name"))
		{
			if (argv[++i] < 0)
			{
				printf("ERROR: No file name entered\n");
				Usage();
				break;
			}
			hasSpecifiedFileName = true;
			fileName = argv[++i];
		}
		else if (EQUAL(argv[i], "--append"))
		{
			isAppending = true;
		}
		else if (EQUAL(argv[i], "--run-identifier"))
		{
			if (argv[++i] == NULL)
			{
				printf("ERROR: No run identifier entered\n");
				Usage();
				break;
			}
			hasRunIdentifier = true;
			runIdentifier = argv[++i];
		}
		//else if(EQUAL(argv[i], "--verbose"))
		//{
		//	verbose = true;
		//}
		else
		{
			Usage();
		}
		i++;
	}
	
	// Check for required arguments
	int argID;
	for (int i = 0; i < REQUIRED_ARG_COUNT; i++)
	{
		if (requiredArgArray[i] == false)
		{
			std::string errorString = "ERROR: Missing required argument ";
			argID = i;
			errorString += getArgumentName(argID);
			//throw std::runtime_error(errorString);
			printf(errorString.c_str());
			printf("\n");
		}
	}

	if (!isOutputtingToFile && hasSpecifiedFileName)
	{
		//throw std::runtime_error("Must be printing a file to specify a file name\n");
	}

	if (!isOutputtingToFile && hasRunIdentifier)
	{
		//throw std::runtime_error("Must be printing a file to specify a run identifer\n");
	}

	behave.updateSurfaceInputs(fuelModelNumber, moistureOneHr, moistureTenHr, moistureHundredHr, moistureLiveHerb, moistureLiveWoody, windSpeed, windDirection, slope, aspect);

	if (hasDirectionOfInterest)
	{
		spreadRate = behave.calculateSurfaceFireForwardSpreadRate(directionOfInterest);
	}
	else
	{
		spreadRate = behave.calculateSurfaceFireForwardSpreadRate();
	}

	flameLength = behave.getFlameLength();
	directionOfMaxSpread = behave.getDirectionOfMaxSpread();

	if (isOutputtingToFile)
	{
		FILE *fout;
		if (isAppending)
		{
			//fopen_s(&fout, fileName.c_str(), "at");
			fout = fopen(fileName.c_str(), "at");
		}
		else
		{
			//fopen_s(&fout, fileName.c_str(), "wt");
			fout = fopen(fileName.c_str(), "wt");
		}
		if (hasRunIdentifier)
		{
			fprintf(fout, runIdentifier.c_str());
			fprintf(fout,"\t");
		}
		fprintf(fout, "Spread_rate_(ch/hr)\t %lf\t" \
			"Flame_length(ft)\t %lf\t" \
			"Direction_of_max_spread(degrees)\t %lf\n", 
			spreadRate, flameLength, directionOfMaxSpread);
		fclose(fout);
	}

	printf("Spread_rate_(ch/hr)\t\t\t%lf\n", spreadRate);
	printf("Flame_length(ft)\t\t\t%lf\n", flameLength);
	printf(	"Direction_of_max_spread(degrees)\t%lf\n", directionOfMaxSpread);

	return 0;
}

