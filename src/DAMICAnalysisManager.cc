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

    G4int CCDInfo = man->CreateNtuple("CCDInfo", "CCDInfo");
    man->CreateNtupleDColumn(CCDInfo,"Thick");
    man->CreateNtupleDColumn(CCDInfo,"sizeX");
    man->CreateNtupleDColumn(CCDInfo,"sizeY");
    man->CreateNtupleIColumn(CCDInfo,"CCDConfiguration");
    man->FinishNtuple(CCDInfo);

    G4int OutPutFile = man->CreateNtuple("OutPut", "OutPut");
    man->CreateNtupleDColumn(OutPutFile,"XCoord");
    man->CreateNtupleDColumn(OutPutFile,"YCoord");
    man->CreateNtupleDColumn(OutPutFile,"ZCoord");
    man->CreateNtupleIColumn(OutPutFile,"TopBot");
    man->CreateNtupleDColumn(OutPutFile,"EnergyDeposit");
    man->CreateNtupleIColumn(OutPutFile,"PartIDElec");
    man->CreateNtupleIColumn(OutPutFile,"IDPrim");
    man->CreateNtupleSColumn(OutPutFile,"Process");
    man->CreateNtupleIColumn(OutPutFile,"CCDNum");
    man->FinishNtuple(OutPutFile);

    G4int InfoAna = man->CreateNtuple("InfoAna", "InfoAna");
    // Electron on CCD

    // Particle that created the Electron
    man->CreateNtupleIColumn(InfoAna,"PDGNumber");
    man->CreateNtupleIColumn(InfoAna,"PartID");
    man->CreateNtupleSColumn(InfoAna,"ProdVolume");
    man->CreateNtupleDColumn(InfoAna,"Energy");
    // Time ionIoni
    man->CreateNtupleDColumn(InfoAna,"Time");
    //Primary Nucleus
    man->CreateNtupleIColumn(InfoAna,"PDGPrimaryNuc");
    man->CreateNtupleDColumn(InfoAna,"X");
    man->CreateNtupleDColumn(InfoAna,"Y");
    man->CreateNtupleDColumn(InfoAna,"Z");

    //Secondary Nucleus
    man->CreateNtupleIColumn(InfoAna,"PDGSecondaryNuc");
    // Part after Secondary
    man->CreateNtupleIColumn(InfoAna,"PDGPartASecond");
    man->CreateNtupleDColumn(InfoAna,"EnergyPartASecond");

    man->FinishNtuple(InfoAna);

    G4int PositionPrim = man->CreateNtuple("PosPrim", "PosPrim");
    man->CreateNtupleDColumn(PositionPrim,"X");
    man->CreateNtupleDColumn(PositionPrim,"Y");
    man->CreateNtupleDColumn(PositionPrim,"Z");
    man->FinishNtuple(PositionPrim);




}
