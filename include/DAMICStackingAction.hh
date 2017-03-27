#ifndef DAMICStackingAction_hh
#define DAMICStackingAction_hh

#include <stdio.h>

#include "G4UserStackingAction.hh"
#include "globals.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "DAMICStackingActionMessenger.hh"
#include <vector>

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
    void SetLimitNucleus(G4int);
    G4int GetLimitNucleus() const{return LimitNucleus;}
    void AddParticlesKill(G4String);
    std::vector<G4int> GetParticlesKill () const{return ParticlesKill;}

    void ResetNewRun();
    G4bool DoKill(G4int);
    G4bool DoKillNucleus(G4int);

private:
    G4String PartName;
    G4double PartEnergyKin;
    G4double PartEnergyTot;
    std::vector<G4int> ParticlesKill;
    G4int LimitNucleus;
    DAMICStackingActionMessenger* Messenger;
};

#endif
