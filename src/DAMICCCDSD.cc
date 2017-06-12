#include "DAMICCCDSD.hh"
#include "DAMICCCDHit.hh"
#include "DAMICTrackInformation.hh"
#include "DAMICAnalysisManager.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4TouchableHandle.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "Randomize.hh"
#include <cmath>


DAMICCCDSD::DAMICCCDSD(G4String name)
: G4VSensitiveDetector(name), fHitsCollection(0), fHitID(-1)
{
    G4String HCname = "CCDColl";
    collectionName.insert(HCname);
    fPositionCCD = {-298.886, -292.367, -285.848, -279.329, -272.81, -266.291, -259.772, -220.974 };
    fThickCCD = 0.675*mm;
}


DAMICCCDSD::~DAMICCCDSD()
{}


void DAMICCCDSD::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection = new DAMICCCDHitsCollection
    (SensitiveDetectorName,collectionName[0]);
    if (fHitID<0)
    { fHitID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection); }
    hce->AddHitsCollection(fHitID,fHitsCollection);
}


G4bool DAMICCCDSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    //G4cout << "je rentre DAMICCCDSD" << G4endl;
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    G4int subProcess =step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessSubType();
    G4int typeProcess = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessType();
    G4TouchableHandle theTouchablePre = step->GetPreStepPoint()->GetTouchableHandle();
    G4TouchableHandle theTouchable = step->GetPostStepPoint()->GetTouchableHandle();
    G4String volumeNname = theTouchable->GetVolume()->GetLogicalVolume()->GetName();
    G4String volumeNnname = theTouchablePre->GetVolume()->GetLogicalVolume()->GetName();

    G4ThreeVector preWorldPostion = step->GetPreStepPoint()->GetPosition();
    G4ThreeVector worldPosition = step->GetPostStepPoint()->GetPosition();
    G4ThreeVector localPosition = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPosition);

    G4TouchableHistory* touchable
      = (G4TouchableHistory*)(step->GetPreStepPoint()->GetTouchable());
    //G4int copyNo = GetCCDNumber(worldPosition.getZ());
    G4VPhysicalVolume* motherPhysical = touchable->GetVolume(3); // mother
    G4int copyNo = motherPhysical->GetCopyNo()+1;
    G4ThreeVector tesVector = G4ThreeVector(3,-38.667+60.045+1, fPositionCCD[copyNo-1]);
    G4ThreeVector localTest = theTouchable->GetHistory()->GetTopTransform().TransformPoint(tesVector);
    G4int TopBot = 0;
    G4ThreeVector Position = localPosition;
    if (worldPosition.getZ()>preWorldPostion.getZ()){
      TopBot = 1;
    }
    else if(worldPosition.getZ()<preWorldPostion.getZ()){
      TopBot = 0;
    }
    else{
      TopBot = 2;
    }
    G4int PDGEMI = 0;
    G4double EnergyDep = 0;
    G4int PartIDElec = step->GetTrack()->GetParentID();
    G4String Process = "NULL";
    G4int PDGNumber = 0;
    G4int PartID = 0;
    G4String ProdVolume = "NULL";
    G4double Energy = 0;
    G4double Time = 0;
    G4int PDGPrimaryNuc = 0;
    G4int EventID = 0;
    G4ThreeVector PositionPrim;
    G4int PDGSecondaryNuc = 0;
    G4int PDGPartASecond = 0;
    G4double EnergyPartASecond = 0;
    G4int CCDNum = copyNo;
    G4String ProcessCreatorName = "NULL";

    if (PartIDElec != 0){
      ProcessCreatorName = step->GetTrack()->GetCreatorProcess()->GetProcessName();
    }
    else{
      ProcessCreatorName ="Prim";
    }

    DAMICTrackInformation* info = (DAMICTrackInformation*)(step->GetTrack()->GetUserInformation());

    const std::vector<const G4Track*>*  SecondariesB =step->GetSecondaryInCurrentStep() ;
    const std::vector<const G4Track*> Secondaries = *SecondariesB ;

    if ((subProcess == 2 || subProcess == 3) && typeProcess == 2)
    {
      //G4RunManager::GetRunManager()->rndmSaveThisEvent();
      if (PartIDElec == 0){
        Time = step->GetPostStepPoint()->GetGlobalTime()/s;
        std::vector<G4int> Particles = info->GetPDGParticle();
        G4int Lenght = Particles.size();
        PDGNumber = Particles[Lenght-1];
        PartID = info->GetParticleID()[Lenght-1];
        ProdVolume = info->GetMaterialProd()[Lenght-1];
        Energy = info->GetEnergyParticle()[Lenght-1];
        // Primary
        Time=step->GetPostStepPoint()->GetGlobalTime()/s;
        PDGPrimaryNuc = -1;
        PositionPrim = G4ThreeVector(-1,-1,-1);
        //Secondary Nucleus
        PDGSecondaryNuc = -1;
        //Part after Secodary
        PDGPartASecond = -1;
        EnergyPartASecond = -1;
        PDGEMI = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
      }
      else {
        Time = step->GetPostStepPoint()->GetGlobalTime()/s;
        std::vector<G4int> Particles = info->GetPDGParticle();

        G4int Lenght = Particles.size();
        Process = ProcessCreatorName;
        PDGNumber = Particles[Lenght-2];
        PartID = info->GetParticleID()[Lenght-2];
        ProdVolume = info->GetMaterialProd()[Lenght-2];
        Energy = info->GetEnergyParticle()[Lenght-2];
        PDGPrimaryNuc = Particles[0];
        PositionPrim = info->GetStartPosition()[0];
        PDGEMI = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
        G4int PosSecondNuc = -1;
        for (G4int i = 0; i <Lenght; i++){
          G4int result = Particles[i] - 1000000000;
          if (result > 0){
            PosSecondNuc = i;
          }
        }
        if (PosSecondNuc >=0){
          PDGSecondaryNuc = Particles[PosSecondNuc];
          PDGPartASecond = Particles[PosSecondNuc+1];
          EnergyPartASecond = info->GetEnergyParticle()[PosSecondNuc+1];
        }
        else{
          PDGPartASecond = -1;
          PDGSecondaryNuc = -1;
          EnergyPartASecond = -1;
        }

      }


      EventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();


      G4int NumberSecond = step->GetNumberOfSecondariesInCurrentStep();
      for (G4int i =0; i<NumberSecond; i++){
        G4double nrjSecond = Secondaries[i]->GetKineticEnergy();
        G4int PDGSaries = Secondaries[i]->GetParticleDefinition()->GetPDGEncoding();
        if ((PDGSaries== 11 && nrjSecond < 20*keV) || (PDGSaries == 22 && nrjSecond < 1*keV)){
          EnergyDep += nrjSecond;
        }
      }
      EnergyDep += step->GetTotalEnergyDeposit();


      DAMICCCDHit* hit = new DAMICCCDHit(copyNo);

      hit->SetPos(Position);
      hit->SetTopBot(TopBot);
      hit->SetEnergyDeposit(EnergyDep);
      hit->SetProcess(Process);
      hit->SetPartIDElec(PartIDElec);
      //
      hit->SetPDGNumber(PDGNumber);
      hit->SetPartID(PartID);
      hit->SetProdVolume(ProdVolume);
      hit->SetEnergy(Energy);
      //
      hit->SetTime(Time);
      hit->SetPDGPrimaryNuc(PDGPrimaryNuc);
      hit->SetEventID(EventID);
      //
      hit->SetPDGSecondaryNuc(PDGSecondaryNuc);
      //
      hit->SetPDGPartASecond(PDGPartASecond);
      hit->SetEnergyPartASecond(EnergyPartASecond);
      //
      hit->SetCCDNum(CCDNum);
      fHitsCollection->insert(hit);

      G4double XCoord = Position.getX() + 61.74/2;
      G4double YCoord = Position.getY() + 62.22/2;
      G4double ZCoord = -(Position.getZ()-0.675/2);
      // Elec deposit
      man->FillNtupleDColumn(1,0,XCoord/10);
      man->FillNtupleDColumn(1,1,YCoord/10);
      man->FillNtupleDColumn(1,2,ZCoord/10);
      man->FillNtupleIColumn(1,3,TopBot);
      man->FillNtupleDColumn(1,4,EnergyDep*1000);
      man->FillNtupleIColumn(1,5,PartIDElec);
      man->FillNtupleIColumn(1,6,EventID);
      man->FillNtupleSColumn(1,7,Process);
      man->FillNtupleIColumn(1,8,CCDNum);
      man->AddNtupleRow(1);

      man->FillNtupleIColumn(2,0,PDGEMI);

      //Particle that created Elec or Ion or Muon



      man->FillNtupleIColumn(2,1, PDGNumber);
      man->FillNtupleIColumn(2,2,PartID);
      man->FillNtupleSColumn(2,3,ProdVolume);
      man->FillNtupleDColumn(2,4,Energy);
      // Primary
      man->FillNtupleDColumn(2,5,Time);
      man->FillNtupleIColumn(2,6,PDGPrimaryNuc);

      man->FillNtupleDColumn(2,7,PositionPrim.getX());
      man->FillNtupleDColumn(2,8,PositionPrim.getY());
      man->FillNtupleDColumn(2,9,PositionPrim.getZ());
      //Secondary Nucleus
      man->FillNtupleIColumn(2,10,PDGSecondaryNuc);
      //Part after Secodary
      man->FillNtupleIColumn(2,11,PDGPartASecond);
      man->FillNtupleDColumn(2,12,EnergyPartASecond);
      // CCD Num

      man->AddNtupleRow(2);
    }

    //G4cout << "je sors DAMICCCDSD" << G4endl;
    return true;
}

G4int DAMICCCDSD::GetCCDNumber(G4double globZ)
{
  G4int numberCCD = fPositionCCD.size();
  G4int CCDnum = 0;
  for (G4int i = 0;i <=numberCCD;i++){
    G4double space = fabs(globZ) - fabs(fPositionCCD[i]);
    if (fabs(space) <= fThickCCD/2){
      CCDnum = i+1;
      break;
    }
  }
  return CCDnum;
}
