//  =============================================================================
// 
//  Author:	    Kjell Swedin
//  Purpose:    Generate spreadrate and flamelength data from fuel models
// 
//  =============================================================================

#include "crosswalk.h"

#include "fuelModelSet.h"
#include "behaveRun.h"

#include <iostream>
#include <iomanip>

using std::vector;
using std::cout;
using std::setprecision;
using std::endl;

const int SLOPE_MAX = 40;
const int SLOPE_STEP = 2;

const int WIND_MAX = 40;
const int WIND_STEP = 2;


void UpdateInputs(BehaveRun& behave, int modelId, SurfaceInputsShort si)
{
    behave.updateSurfaceInputs(
        modelId,
        si.mOneHour,
        si.mTenHour,
        si.mHundredHour,
        si.mLiveHerbaceous,
        si.mLiveWoody,
        si.mUnits,
        si.windSpeed,
        si.windDirection,
        si.slope,
        si.sUnits,
        si.aspect,
        si.canopyCover,
        si.canopyHeight,
        si.crownRatio);
}

void PrintHeader()
{
    cout << "Model#," << "SpreadRate," << "FlameLength," << "Slope," << "Windspeed" << endl;
}

void process()
{
    FuelModelSet   models;
    
    vector<int> modelIds;
    models.getModelIds(modelIds);
    
    BehaveRun behave(models);
    SurfaceInputsShort si;
    PrintHeader();
    for(auto fuelModelNumber : modelIds)
    {
        for(int slope = 0; slope < SLOPE_MAX; slope += SLOPE_STEP)
        {
            for(int windspeed = 0; windspeed < WIND_MAX; windspeed += WIND_STEP)
            {
                si.slope = slope;
                si.windSpeed = windspeed;
                UpdateInputs(behave, fuelModelNumber, si);
                behave.doSurfaceRunInDirectionOfMaxSpread();
                cout << fuelModelNumber << ","
                     << behave.getSurfaceFireSpreadRate(SpeedUnits::FEET_PER_MINUTE) << ","
                     << behave.getSurfaceFlameLength(LengthUnits::FEET) << ","
                     << slope << ","
                     << windspeed
                     << endl;
            }
        }
    }
 }
