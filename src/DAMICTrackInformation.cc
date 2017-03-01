#include "DAMICTrackInformation.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


DAMICTrackInformation::DAMICTrackInformation(G4int VPDGParticle, G4double VEnergyParticle, G4int VParticleID, G4String VMaterialProd, G4ThreeVector VPosition, G4double  VTime):G4VUserTrackInformation()
{
  PDGParticle = {VPDGParticle};
  EnergyParticle = {VEnergyParticle};
  ParticleID = {VParticleID};
  MaterialProd = {VMaterialProd};
  StartPosition = {VPosition};
  Time = {VTime};

}

DAMICTrackInformation::DAMICTrackInformation(const DAMICTrackInformation* InfoTrack): G4VUserTrackInformation()
{
  PDGParticle = InfoTrack->PDGParticle;
  EnergyParticle = InfoTrack->EnergyParticle;
  ParticleID = InfoTrack->ParticleID;
  MaterialProd = InfoTrack->MaterialProd;
  StartPosition = InfoTrack->StartPosition;
  Time = InfoTrack->Time;

}

DAMICTrackInformation::DAMICTrackInformation(const DAMICTrackInformation* InfoTrack, G4int VPDGParticle, G4double VEnergyParticle, G4int VParticleID, G4String VMaterialProd, G4ThreeVector VPosition, G4double  VTime): G4VUserTrackInformation()
{
  PDGParticle = InfoTrack->PDGParticle;
  EnergyParticle = InfoTrack->EnergyParticle;
  ParticleID = InfoTrack->ParticleID;
  MaterialProd = InfoTrack->MaterialProd;
  StartPosition = InfoTrack->StartPosition;
  Time = InfoTrack->Time;
  AddPDGParticle(VPDGParticle);
  AddEnergyParticle(VEnergyParticle);
  AddParticleID(VParticleID);
  AddMaterialProd(VMaterialProd);
  AddStartPosition(VPosition);
  AddTime(VTime);
}
DAMICTrackInformation::~DAMICTrackInformation()
{}
