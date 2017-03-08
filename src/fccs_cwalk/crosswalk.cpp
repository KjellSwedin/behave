//  =============================================================================
// 
//  Author:	Kjell Swedin
//  Purpose:	Generate spreadrate and flamelength data from fuel models
// 
//  =============================================================================

#include "fuelModelSet.h"
#include "behaveRun.h"

#include <iostream>
#include <iomanip>

using std::vector;
using std::cout;
using std::setprecision;
using std::endl;

void process()
{
    FuelModelSet   models;
    
    vector<int> modelIds;
    models.getModelIds(modelIds);
    int counter = 0;
    for(auto i : modelIds)
    {
        printf("%d\n", i);
        counter++;
    }
    printf("----------------\n%d\n", counter);
    
    double moistureOneHour = 6;
    double moistureTenHour = 7;
    double moistureHundredHour = 8;
    double moistureLiveHerbaceous = 60;
    double moistureLiveWoody = 90;
    double windSpeed = 5;
    double windDirection = 42;
    double slope = 30;
    double aspect = 291;
    double directionOfInterest = 63;
 
    double canopyCover = 0.50; // 50%
    double canopyHeight = 6;
    double crownRatio = 0.50;
    
    BehaveRun behave(models);
    for(auto fuelModelNumber : modelIds)
    {
        // Single fuel model test
        behave.updateSurfaceInputs(fuelModelNumber, moistureOneHour, moistureTenHour, moistureHundredHour,
            moistureLiveHerbaceous, moistureLiveWoody, MoistureUnits::PERCENT, windSpeed, windDirection,
            slope, SlopeUnits::DEGREES, aspect, canopyCover, canopyHeight, crownRatio);
        behave.doSurfaceRunInDirectionOfInterest(directionOfInterest);
        double spreadRate = behave.getSurfaceFireSpreadRate(SpeedUnits::CHAINS_PER_HOUR);
        double flameLength = behave.getSurfaceFlameLength(LengthUnits::FEET);
        std::cout << "Spread rate for fuel model " << fuelModelNumber << " is " << std::setprecision(3) << spreadRate << " ch/hr" << std::endl;
        std::cout << "Flame length for fuel model " << fuelModelNumber << " is " << std::setprecision(3) << flameLength << " ft" << std::endl << std::endl;    
    }
 }


int
main(void)
{
    process();
    return 0;
}