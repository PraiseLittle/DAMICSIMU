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


    G4int end0 = man->CreateNtuple("tree1", "Particle Info");
    man->CreateNtupleSColumn(end0,"NamePrimary");
    man->CreateNtupleDColumn(end0,"EnergyPrimary");
    man->CreateNtupleIColumn(end0,"IDEvent");
    man->CreateNtupleSColumn(end0,"ParticleConcerned");
    man->CreateNtupleIColumn(end0,"IDParticle");
    man->CreateNtupleDColumn(end0,"EnergyLoss");
    man->CreateNtupleDColumn(end0,"EnergyBeforeInter");
    man->CreateNtupleDColumn(end0,"EnergyAfterInter");
    man->CreateNtupleSColumn(end0,"NameOfTheInter");
    man->CreateNtupleDColumn(end0,"PositionXbeginn");
    man->CreateNtupleDColumn(end0,"PositionYbeginn");
    man->CreateNtupleDColumn(end0,"PositionZbeginn");
    man->CreateNtupleDColumn(end0,"PositionXend");
    man->CreateNtupleDColumn(end0,"PositionYend");
    man->CreateNtupleDColumn(end0,"PositionZend");
    man->CreateNtupleDColumn(end0,"LenghtStep");
    man->CreateNtupleSColumn(end0,"NameOfVolume");
    man->CreateNtupleSColumn(end0,"NameMaterial");
    man->CreateNtupleIColumn(end0,"NumberSecondaries");
    man->FinishNtuple(end0);



}
