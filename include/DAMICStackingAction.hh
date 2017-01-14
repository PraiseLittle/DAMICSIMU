#ifndef DAMICStackingAction_hh
#define DAMICStackingAction_hh

#include <stdio.h>

#include "G4UserStackingAction.hh"
#include "globals.hh"
#include "G4ClassificationOfNewTrack.hh"

class G4Track;

class DAMICStackingAction : public G4UserStackingAction
{
public:
    DAMICStackingAction();
    ~DAMICStackingAction();

    void SetPartName(G4String );
    void SetPartEnergyKin(G4double);
    void SetPartEnergyTot(G4double);
    G4double GetPartEnergyKin() const {return PartEnergyKin;}
    G4double GetPartEnergyTot() const{return PartEnergyTot;}
    G4String GetPartName () const { return PartName;}
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);

private:
    G4String PartName;
    G4double PartEnergyKin;
    G4double PartEnergyTot;
};

#endif
