// Interface for Behave application based on the Facade OOP Design Pattern
// It is used to tie together the modules and objects used by Behave - WMC 10/2015

#ifndef BEHAVE_HEADER
#define BEHAVE_HEADER

#include "fuelModels.h"
#include "surface.h"

class Behave
{
public:
	Behave();
	explicit Behave(SurfaceInputs &surfaceInputs);
	Behave(int fuelModelNumber, double moistureOneHour, double moistureTenHour,
		double moistureHundredHour, double moistureLiveHerbaceous, double moistureLiveWoody,
		double midflameWindSpeed, double windDirection, double slope, double slopeAspect = 0);
	~Behave();
	
	// SURFACE Module 
	void updateSurfaceInputs(int fuelModelNumber, double moistureOneHour, double moistureTenHour,
		double moistureHundredHour, double moistureLiveHerbaceous, double moistureLiveWoody,
		double midflameWindSpeed, double windDirection, double slope, double slopeAspect = 0);
	double calculateSurfaceFireForwardSpreadRate(double directionOfInterest = -1.0);
	double getDirectionOfMaxSpread() const;
	double getFlameLength() const;
	double getFireLengthToWidthRatio() const;
	double getFireEccentricity() const;
	bool isFuelModelDefined(int fuelModelNumber) const;
	bool isWindAndSpreadAngleRelativeToNorth() const;
	bool isWindAndSpreadAngleRelativeToUpslope() const;
	bool isSlopeInDegrees() const;
	bool isSlopeInPercent() const;
	
	void setWindAndSpreadAnglesRelativeToNorth();
	void setWindAndSpreadAnglesRelativeToUpslope();
	void setSlopeInputToPercent();
	void setSlopeInputToDegrees();

private:
	enum WindAndSpreadDirectionEnumType {
		RELATIVE_TO_UPSLOPE = 0,	// Wind and spread direction are clockwise relative to upslope
		RELATIVE_TO_NORTH = 1		// Wind direction direction are clockwise relative to compass north
	};

	enum SlopeInputModeEnumType {
		SLOPE_IN_PERCENT = 0,	// Slope is input as a percent
		SLOPE_IN_DEGREES = 1	// Slope is input as degrees
	};

	void setSlopeInputMode(SlopeInputModeEnumType mode);
	void setWindAndSpreadDirectionMode(WindAndSpreadDirectionEnumType mode);

	FuelModels fuelModels_;										// Object containing data for fuel models
	Surface surface_;											// SURFACE Moduel object
	SurfaceInputs surfaceInputs_;								// Object that manages user input to SURFACE Module
};

#endif //BEHAVE_HEADER