#include "DAMICAnalysisManager.hh"


#include "G4UnitsTable.hh"

DAMICAnalysisManager::DAMICAnalysisManager()
: fFileName("test")
{
    Book();

}


DAMICAnalysisManager::~DAMICAnalysisManager()
{
    delete G4AnalysisManager::Instance();
}

void DAMICAnalysisManager::Book()
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->SetFileName(fFileName);
    man->SetVerboseLevel(1);
    man->SetActivation(true);


    G4int OutPutFile = man->CreateNtuple("OutPut", "OutPut");
    // Electron on CCD
    man->CreateNtupleDColumn(OutPutFile,"XCoord");
    man->CreateNtupleDColumn(OutPutFile,"YCoord");
    man->CreateNtupleDColumn(OutPutFile,"ZCoord");
    man->CreateNtupleIColumn(OutPutFile,"TopBot");
    man->CreateNtupleDColumn(OutPutFile,"EnergyDeposit");
    man->CreateNtupleIColumn(OutPutFile,"PartIDElec");
    man->CreateNtupleSColumn(OutPutFile,"Process");
    // Particle that created the Electron
    man->CreateNtupleIColumn(OutPutFile,"PDGNumber");
    man->CreateNtupleIColumn(OutPutFile,"PartID");
    man->CreateNtupleSColumn(OutPutFile,"ProdVolume");
    man->CreateNtupleDColumn(OutPutFile,"Energy");

    // Primary
    man->CreateNtupleDColumn(OutPutFile,"Time");
    man->CreateNtupleIColumn(OutPutFile,"PDGPrimaryNuc");
    man->CreateNtupleIColumn(OutPutFile,"IDEvent");

    //Secondary Nucleus
    man->CreateNtupleIColumn(OutPutFile,"PDGSecondaryNuc");
    // Part after Secondary
    man->CreateNtupleIColumn(OutPutFile,"PDGPartASecond");
    man->CreateNtupleDColumn(OutPutFile,"EnergyPartASecond");
    // CCD number
    man->CreateNtupleIColumn(OutPutFile,"CCDNum");

    man->FinishNtuple(OutPutFile);




}
