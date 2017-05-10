#include "DAMICStackingAction.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>
#include <vector>
#include "G4DecayTable.hh"
#include "G4RunManager.hh"

DAMICStackingAction::DAMICStackingAction()
:G4UserStackingAction(),PartName("ez"), PartEnergyKin(0.), PartEnergyTot(0.)
{
  ParticlesKill = {};
  LimitNucleus = -1;
  Messenger = new DAMICStackingActionMessenger(this);
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

void DAMICStackingAction::SetLimitNucleus(G4int pdgenco){
  LimitNucleus = pdgenco;
}

void DAMICStackingAction::AddParticlesKill(G4String Particle){
  G4ParticleDefinition* Part = G4ParticleTable::GetParticleTable()->FindParticle(Particle);

  ParticlesKill.push_back(Part->GetPDGEncoding());
}

G4bool DAMICStackingAction::DoKill(G4int PartPDG){
  G4bool Kill = false;
  G4int entries = ParticlesKill.size();
  for (int i = 0; i< entries; i++){
    if (PartPDG == ParticlesKill[i]){
      Kill = true;
    }
  }
  return Kill;
}


G4bool DAMICStackingAction::DoKillNucleus(G4int PartPDG){
  if (LimitNucleus == -1){
    return false;
  }
  if (PartPDG < 1000000000){
    return false;
  }
  if (PartPDG == 1000020040){
    return false;
  }
  //G4cout << PartPDG << G4endl;
  int Z = floor(PartPDG/10000)- 100000;
  int A = floor(PartPDG/10)-100000000 - Z*1000 ;
  int Zbase = floor(LimitNucleus/10000)- 100000;
  int Abase = floor(LimitNucleus/10)- 100000000 - Zbase*1000;
  int unity = PartPDG - 1000000000 - Z *10000 - A *10;
  G4bool alphaC = A >= Abase+4;
  G4bool firstC = A < Abase;
  G4bool secondC = Z < Zbase-1;
  G4bool thirdC = Z > Zbase +1;
  G4bool sameZ = Z ==Zbase;
  G4bool sameA = A == Abase;
  G4bool nulUnity = unity ==0 ;
  if (alphaC){
    return false;
  }
  if (firstC){
    return true;
  }
  else if (secondC || thirdC)
  {
    return true;
  }
  else if(sameZ && sameA && nulUnity){
    return true;
  }
  else{
    return false;
  }

}

G4bool DAMICStackingAction::DoOneDecay(G4int PartPDG, G4int IDpart){ // construction
  if (PartPDG < 1000000000){
    return false;
  }
  if (IDpart == 0){
    return false;
  }
  if((PartPDG % 10) == 0){
    return true;
  }

}

void DAMICStackingAction::ResetNewRun(){
  ParticlesKill = {};
  LimitNucleus = -1;
}


G4ClassificationOfNewTrack DAMICStackingAction::ClassifyNewTrack(const G4Track* aTrack)
{

    G4String Name = aTrack->GetDefinition()->GetParticleName();
    SetPartName(Name);
    //G4cout << "je rentre Stack" << G4endl;
    G4double energy = aTrack->GetTotalEnergy();
    G4double energykin = aTrack->GetKineticEnergy();
    SetPartEnergyKin(energykin);
    SetPartEnergyTot(energy);
    G4int IDpart = aTrack->GetParentID();
    G4int ProcessCreatorSub = -1;
    G4int ProcessCreatorType = -1;
    G4String ProcessName = "NULL";
    G4String nameVolume = "NULL";

    /* Test */

    G4int PDGEnco = aTrack->GetDefinition()->GetPDGEncoding();
    //G4cout << Name << G4endl;
    //G4cout << aTrack->GetDefinition()->GetPDGEncoding() << G4endl;
    if (DoKill(PDGEnco)){
      return fKill;
    }
    if (DoKillNucleus(PDGEnco)){
      return fKill;
    }
    /*if (DoOneDecay(PDGEnco, IDpart)){
      return fKill;
    }*/

    //G4cout << Name << G4endl;
    if (IDpart != 0){
      ProcessCreatorSub = aTrack->GetCreatorProcess()->GetProcessSubType();
      ProcessCreatorType = aTrack->GetCreatorProcess()->GetProcessType();
      //ProcessName= aTrack->GetCreatorProcess()->GetProcessName();

    }
    else {
      ProcessCreatorSub = -1;
      ProcessCreatorType = -1;
      nameVolume = "NULL";
    }

    // Kill electrons produced by ioni below 20 keV
    if (ProcessCreatorSub == 2 && ProcessCreatorType == 2 && energykin < 50*keV){
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
    if ( ProcessCreatorSub == 3  && energykin < 1*keV && nameVolume != "CCDSensor" && ProcessCreatorType == 2)
    {
      return fKill;
    }

    if (energykin<1*eV && Name=="e-"){ // Kill particles with less than 1 eV  kinetic energy
        return fKill;
    }

    /*if (Name =="gamma"){
      G4cout << energykin  << "   " << ProcessName << G4endl;
    }*/

    //G4cout << Name << G4endl;

    //G4cout << "je sors Stack" << G4endl;
    //G4RunManager::GetRunManager()->rndmSaveThisEvent();
    return fUrgent;
}
