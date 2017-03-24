#include "DAMICStackingAction.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


DAMICStackingAction::DAMICStackingAction()
:G4UserStackingAction(),PartName("ez"), PartEnergyKin(0.), PartEnergyTot(0.)
{
}

DAMICStackingAction::~DAMICStackingAction()
{ }

void DAMICStackingAction::SetPartName(G4String name)
{
    PartName = name;
}

void DAMICStackingAction::SetPartEnergyKin(G4double nrj)
{
    PartEnergyKin = nrj;
}

void DAMICStackingAction::SetPartEnergyTot(G4double nrj)
{
    PartEnergyTot = nrj;
}


G4ClassificationOfNewTrack DAMICStackingAction::ClassifyNewTrack(const G4Track* aTrack)
{
    G4String Name = aTrack->GetDefinition()->GetParticleName();
    SetPartName(Name);
    G4cout << "je rentre ClassifyNewTrack" << G4endl;
    G4double energy = aTrack->GetTotalEnergy();
    G4double energykin = aTrack->GetKineticEnergy();
    SetPartEnergyKin(energykin);
    SetPartEnergyTot(energy);
    G4int IDpart = aTrack->GetParentID();
    G4int ProcessCreatorSub = -1;
    G4int ProcessCreatorType = -1;

    G4String nameVolume = "NULL";
    G4cout << Name<< G4endl;


    if (IDpart != 0){
      ProcessCreatorSub = aTrack->GetCreatorProcess()->GetProcessSubType();
      ProcessCreatorType = aTrack->GetCreatorProcess()->GetProcessType();
    }
    else {
      ProcessCreatorSub = -1;
      ProcessCreatorType = -1;
      nameVolume = "NULL";
    }

    // Kill electrons produced by ioni below 20 keV
    if (ProcessCreatorSub == 2 && ProcessCreatorType == 2 && energykin < 20*keV){
      return fKill;
    }
    // Check volume from particles not produced by ioni.
    if (IDpart != 0 && ProcessCreatorSub != 2 && ProcessCreatorType != 2 ){
      nameVolume = aTrack->GetVolume()->GetName();
    }
    // Kill Brem in CCD
    if ( ProcessCreatorSub == 3  && energykin < 1*keV && nameVolume == "CCDSensor" && ProcessCreatorType == 2)
    {
      return fKill;
    }
    // Kill Brem not in CCD
    if ( ProcessCreatorSub == 3  && energykin < 10*keV && nameVolume != "CCDSensor" && ProcessCreatorType == 2)
    {
      return fKill;
    }

    if (energykin<1*eV && Name=="e-"){ // Kill particles with less than 1 eV  kinetic energy
        return fKill;
    }
    G4cout << "je sors ClassifyNewTrack" << G4endl;
    return fUrgent;
}
