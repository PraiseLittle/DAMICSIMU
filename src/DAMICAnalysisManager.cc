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
    man->CreateNtupleDColumn(OutPutFile,"XCoord");
    man->CreateNtupleDColumn(OutPutFile,"YCoord");
    man->CreateNtupleDColumn(OutPutFile,"ZCoord");
    man->CreateNtupleIColumn(OutPutFile,"TopBot");
    man->CreateNtupleDColumn(OutPutFile,"Energy");
    man->CreateNtupleDColumn(OutPutFile,"EnergyDeposit");
    man->CreateNtupleIColumn(OutPutFile,"PDGNumber");
    man->CreateNtupleIColumn(OutPutFile,"PartID");
    man->CreateNtupleSColumn(OutPutFile,"Process");
    man->CreateNtupleDColumn(OutPutFile,"Time");
    man->CreateNtupleIColumn(OutPutFile,"CCDNum");
    man->CreateNtupleIColumn(OutPutFile,"PDGMother");
    man->CreateNtupleIColumn(OutPutFile,"IDMother");
    man->CreateNtupleDColumn(OutPutFile,"MotherEnergy");
    man->CreateNtupleSColumn(OutPutFile,"ProdVolume");
    man->CreateNtupleIColumn(OutPutFile,"APrimary");
    man->CreateNtupleIColumn(OutPutFile,"ZPrimary");
    man->CreateNtupleIColumn(OutPutFile,"IDPrimary");
    man->FinishNtuple(OutPutFile);




}
