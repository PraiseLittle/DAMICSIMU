#include "DAMICRunAction.hh"
#include "DAMICPrimaryGeneratorAction.hh"
#include "DAMICDetectorConstruction.hh"
#include "DAMICAnalysisManager.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4ParameterManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

DAMICRunAction::DAMICRunAction(): G4UserRunAction()
{  fAnalysisManager = new DAMICAnalysisManager();}

DAMICRunAction::~DAMICRunAction()
{ delete fAnalysisManager;}

void DAMICRunAction::BeginOfRunAction(const G4Run*)
{

  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->OpenFile();

  G4ParameterManager* parameterManager = G4ParameterManager::Instance();
  parameterManager->Reset();
}


void DAMICRunAction::EndOfRunAction(const G4Run* run)
{

  // Merge parameters
  G4ParameterManager* parameterManager = G4ParameterManager::Instance();
  parameterManager->Merge();
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->Write();
  man->CloseFile();
  // Complete clean-up

}
