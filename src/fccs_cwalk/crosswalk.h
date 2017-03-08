//  =============================================================================
// 
//  Author:	    Kjell Swedin
//  Purpose:    Generate spreadrate and flamelength data from fuel models
// 
//  =============================================================================
#ifndef CROSSWALK_H
#define CROSSWALK_H

#include "behaveUnits.h"


class SurfaceInputsShort
{
public:
    
    double mOneHour;
    double mTenHour;
    double mHundredHour;
    double mLiveHerbaceous;
    double mLiveWoody;
    double windSpeed;
    double windDirection;
    double slope;
    double aspect;
    double directionOfInterest;
    double canopyCover;
    double canopyHeight;
    double crownRatio;
    
    enum MoistureUnits::MoistureUnitsEnum mUnits;
    enum SlopeUnits::SlopeUnitsEnum sUnits;
    
    SurfaceInputsShort():
        mOneHour(6),
        mTenHour(7),
        mHundredHour(8),
        mLiveHerbaceous(60),
        mLiveWoody(90),
        windSpeed(4),
        windDirection(0),
        slope(0),
        aspect(0),
        directionOfInterest(0),
        canopyCover(0.50),
        canopyHeight(6),
        crownRatio(0.50)
    {
        mUnits = MoistureUnits::PERCENT;
        sUnits= SlopeUnits::DEGREES;
    }
    
};

void process();

#endif // CROSSWALK_H