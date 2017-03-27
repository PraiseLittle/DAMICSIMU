#include <fstream>
#include <iomanip>

#include "DAMICStackingActionMessenger.hh"
#include "DAMICStackingAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4Geantino.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"
#include <cmath>

DAMICStackingActionMessenger::DAMICStackingActionMessenger(DAMICStackingAction* fStackSource): fStackAction(fStackSource){

  particleTable = G4ParticleTable::GetParticleTable();

  stackDirectory = new G4UIdirectory("/damic/stack/");
  stackDirectory->SetGuidance("Stacking action control commands.");

  ListCmd = new G4UIcmdWithoutParameter("/damic/stack/list", this);
  ListCmd->SetGuidance("List available particles.");
  ListCmd->SetGuidance(" Invoke G4ParticleTable.");

  ResetCmd = new G4UIcmdWithoutParameter("/damic/stack/reset", this);
  ResetCmd->SetGuidance("To use in a macro file with several runs");

  IonLimitCmd = new G4UIcommand("/damic/stack/ionlimit",this);
  IonLimitCmd->SetGuidance("Set properties of ion to be generated.");
  IonLimitCmd->SetGuidance("[usage] /stack/ionlimit Z A");
  IonLimitCmd->SetGuidance("        Z:(int) AtomicNumber");
  IonLimitCmd->SetGuidance("        A:(int) AtomicMass");


  G4UIparameter* parami;
  parami = new G4UIparameter("Z",'i',true);
  parami->SetDefaultValue("1");
  IonLimitCmd->SetParameter(parami);
  parami = new G4UIparameter("A",'i',true);
  parami->SetDefaultValue("1");
  IonLimitCmd->SetParameter(parami);

  AddPartKillCmd = new G4UIcmdWithAString("/damic/stack/partkill", this);
  AddPartKillCmd->SetGuidance("Add particles to kill during the run");
  AddPartKillCmd->SetParameterName("Particule", true, true);
}


DAMICStackingActionMessenger::~DAMICStackingActionMessenger(){

  delete ListCmd;
  delete IonLimitCmd;
  delete AddPartKillCmd;
  delete ResetCmd;

  delete stackDirectory;


}

void DAMICStackingActionMessenger::SetNewValue(G4UIcommand *command, G4String newValues){
  //G4cout << "SetNew "  << G4endl;
  if (command == ListCmd){
    particleTable->DumpTable();
  }// SPECS
  else if(command == IonLimitCmd){

    G4Tokenizer next( newValues );
    // check argument
    G4int fAtomicNumber = StoI(next());
    G4int fAtomicMass = StoI(next());

    G4ParticleDefinition* ion;
    ion =  G4IonTable::GetIonTable()->GetIon(fAtomicNumber,fAtomicMass);
    if (ion==0) {
	    G4cout << "Ion with Z=" << fAtomicNumber;
	    G4cout << " A=" << fAtomicMass << "is not well defined" << G4endl;
    }
    else {
	    fStackAction->SetLimitNucleus(ion->GetPDGEncoding());
    }
  }
  else if ( command == AddPartKillCmd){
    fStackAction->AddParticlesKill(newValues);
  }
  else if (command == ResetCmd){
    fStackAction->ResetNewRun();
  }
}
