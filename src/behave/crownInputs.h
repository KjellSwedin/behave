#ifndef CROWNINPUTS_HEADER
#define CROWNINPUTS_HEADER

class CrownInputs
{
public:
    void setCanopyBaseHeight(double canopyBaseHeight);
    void setCanopyBulkDensity(double canopyBulkDensity);
    void setCanopyFlameLength(double canopyUserProvidedFlameLength);
    void setCanopyFirelineIntensity(double canopyUserProvidedFirelineIntensity);
    void setFoliarMoisture(double foliarMoisture);

    double getCanopyBaseHeight() const;
    double getCanopyBulkDensity() const;
    double getCanopyFlameLength() const;
    double getCanopyFirelineIntensity() const;
    double getFoliarMoisture() const;

    void updateCrownInputs(double canopyBaseHeight, double canopyBulkDensity, double foliarMoisture);

private:
    double canopyBaseHeight_; //Canopy base height(ft)
    double canopyBulkDensity_; // Canopy bulk density(lb / ft3)
    double canopyUserProvidedFlameLength_; // flame length(ft)
    double canopyUserProvidedFirelineIntensity_; // fireline intensity(ft)
    double foliarMoisture_; // foliar moisture(%)

};

#endif // CROWNINPUTS_HEADER
