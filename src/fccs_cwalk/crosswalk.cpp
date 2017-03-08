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
    cout << "Model#," << "SpreadRate," << "FlameLength" << endl;
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
        UpdateInputs(behave, fuelModelNumber, si);
        behave.doSurfaceRunInDirectionOfMaxSpread();
        cout << fuelModelNumber << ","
             << behave.getSurfaceFireSpreadRate(SpeedUnits::MILES_PER_HOUR) << ","
             << behave.getSurfaceFlameLength(LengthUnits::FEET)
             << endl;
    }
 }
