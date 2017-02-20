#ifndef DAMICCCDSD_h
#define DAMICCCDSD_h 1

#include "G4VSensitiveDetector.hh"
#include "DAMICCCDHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class DAMICCCDSD : public G4VSensitiveDetector
{
public:
    DAMICCCDSD(G4String name);
    virtual ~DAMICCCDSD();

    virtual void Initialize(G4HCofThisEvent*HCE);
    virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);

private:
    DAMICCCDHitsCollection* fHitsCollection;
    G4int fHitID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
