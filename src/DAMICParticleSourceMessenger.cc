#include <fstream>
#include <iomanip>

#include "DAMICParticleSourceMessenger.hh"
#include "DAMICParticleSource.hh"

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


DAMICParticleSourceMessenger::DAMICParticleSourceMessenger(DAMICParticleSource* fPartSource): fParticleGun(fPartSource), fShootIon(false){

  particleTable = G4ParticleTable::GetParticleTable();

  gunDirectory = new G4UIdirectory("damic/gun/");
  gunDirectory->SetGuidance("Particle Source control commands.");

  DoVolumeCmd = new G4UIcmdWithoutParameter("/damic/gun/doVolume",this);
  DoVolumeCmd->SetGuidance("Set to only use volumes source");

  DoSourceCmd = new G4UIcmdWithoutParameter("/damic/gun/doSource",this);
  DoSourceCmd->SetGuidance("Set to only use point source");

  DoMaterialCmd = new G4UIcmdWithoutParameter("/damic/gun/doMaterial",this);
  DoMaterialCmd->SetGuidance("Set to only use material source");

  ListCmd = new G4UIcmdWithoutParameter("/damic/gun/list", this);
  ListCmd->SetGuidance("List available particles.");
  ListCmd->SetGuidance(" Invoke G4ParticleTable.");

  ParticleCmd = new G4UIcmdWithAString("/damic/gun/particle", this);
  ParticleCmd->SetGuidance("Set particle to be generated. ");
  ParticleCmd->SetGuidance(" (geantino is default) ");
  ParticleCmd->SetGuidance(" (ion can be specified for shooting ions)");
  ParticleCmd->SetParameterName("particleName",true);
  ParticleCmd->SetDefaultValue("geantino");
  G4String candidateList;
  G4int nPtcl = particleTable->entries();
  for(G4int i=0;i<nPtcl;i++)
    {
      candidateList += particleTable->GetParticleName(i);
      candidateList += " ";
    }
  candidateList += "ion ";
  ParticleCmd->SetCandidates(candidateList);

  MomentumCmd = new G4UIcmdWith3Vector("/damic/gun/momentum", this);
  MomentumCmd->SetGuidance("Set momentum direction.");
  MomentumCmd->SetGuidance("Direction needs not to be a unit vector.");
  MomentumCmd->SetParameterName("Px","Py","Pz",true,true);
  MomentumCmd->SetRange("Px != 0 || Py != 0 || Pz != 0");

  EnergyCmd = new G4UIcmdWithADoubleAndUnit("/damic/gun/energy", this);
  EnergyCmd->SetGuidance("Set Kinetic Energy.");
  EnergyCmd->SetParameterName("Energy", true, true);
  EnergyCmd->SetDefaultUnit("MeV");

  PositionSourceCmd = new G4UIcmdWith3VectorAndUnit("/damic/gun/position",this);
  PositionSourceCmd->SetGuidance("Set starting position of the particle.");
  PositionSourceCmd->SetParameterName("X","Y","Z",true,true);
  PositionSourceCmd->SetDefaultUnit("mm");

  //ION
  IonCmd = new G4UIcommand("/damic/gun/ion",this);
  IonCmd->SetGuidance("Set properties of ion to be generated.");
  IonCmd->SetGuidance("[usage] /gun/ion Z A Q E");
  IonCmd->SetGuidance("        Z:(int) AtomicNumber");
  IonCmd->SetGuidance("        A:(int) AtomicMass");
  IonCmd->SetGuidance("        Q:(int) Charge of Ion (in unit of e)");
  IonCmd->SetGuidance("        E:(double) Excitation energy (in keV)");


  G4UIparameter* param;
  param = new G4UIparameter("Z",'i',false);
  param->SetDefaultValue("1");
  IonCmd->SetParameter(param);
  param = new G4UIparameter("A",'i',false);
  param->SetDefaultValue("1");
  IonCmd->SetParameter(param);
  param = new G4UIparameter("Q",'i',true);
  param->SetDefaultValue("0");
  IonCmd->SetParameter(param);
  param = new G4UIparameter("E",'d',true);
  param->SetDefaultValue("0.0");
  IonCmd->SetParameter(param);

  ChargeCmd= new G4UIcmdWithADouble("/damic/gun/charge", this);
  ChargeCmd->SetGuidance("Set charge of the particle.");
  ChargeCmd->SetParameterName("Charge", true);

  VolumeSourceCmd = new G4UIcmdWithAString("/damic/gun/volume", this);
  VolumeSourceCmd->SetGuidance("Set Volume of the source");
  VolumeSourceCmd->SetParameterName("Volume", true);

  MaterialSourceCmd = new G4UIcmdWithAString("/damic/gun/material", this);
  MaterialSourceCmd->SetGuidance("Set Material of the source");
  MaterialSourceCmd->SetParameterName("Material", true);

  MotherSourceCmd = new G4UIcmdWithAString("/damic/gun/mother", this);
  MotherSourceCmd->SetGuidance("Set Mother of the source");
  MotherSourceCmd->SetParameterName("Mother", true);


}

DAMICParticleSourceMessenger::~DAMICParticleSourceMessenger(){

  delete EnergyCmd;
  delete ChargeCmd;
  delete MomentumCmd;
  delete ParticleCmd;
  delete PositionSourceCmd;
  delete VolumeSourceCmd;
  delete MaterialSourceCmd;
  delete MotherSourceCmd;
  delete DoVolumeCmd;
  delete DoMaterialCmd;
  delete DoSourceCmd;
  delete IonCmd;
  delete ListCmd;

  delete gunDirectory;

}

void DAMICParticleSourceMessenger::SetNewValue(G4UIcommand *command, G4String newValues){

  if (command == ListCmd){
    particleTable->DumpTable();
  }
  else if(command == IonCmd){

    if (fShootIon) {
      G4Tokenizer next( newValues );
      // check argument
      fAtomicNumber = StoI(next());
      fAtomicMass = StoI(next());
      G4String sQ = next();
      if (sQ.isNull()) {
  	    fIonCharge = fAtomicNumber;
      }
      else {
  	    fIonCharge = StoI(sQ);
  	    sQ = next();
  	    if (sQ.isNull()) {
  	        fIonExciteEnergy = 0.0;
  	      }
          else {
  	         fIonExciteEnergy = StoD(sQ) * keV;
           }
      }

      G4ParticleDefinition* ion;
      ion =  G4IonTable::GetIonTable()->GetIon(fAtomicNumber,fAtomicMass,fIonExciteEnergy);
      if (ion==0) {
  	    G4cout << "Ion with Z=" << fAtomicNumber;
  	    G4cout << " A=" << fAtomicMass << "is not well defined" << G4endl;
      }
      else {
  	    fParticleGun->SetParticleDefinition(ion);
  	    fParticleGun->SetParticleCharge(fIonCharge*eplus);
      }
      }
      else {
        G4cout<<"Set /damic/gun/particle to ion before using /damic/gun/ion command";
        G4cout<<G4endl;
      }
    }
    else if(command == DoSourceCmd){
      fParticleGun->DoSource();
    }
    else if(command == DoVolumeCmd){
      fParticleGun->DoVolume();
    }
    else if(command == DoMaterialCmd){
      fParticleGun->DoMaterial();
    }
    else if(command == MotherSourceCmd){
      fParticleGun->SetMotherVolume(newValues);
    }
    else if(command == VolumeSourceCmd){
      fParticleGun->SetVolumeSource(newValues);
    }
    else if (command == MaterialSourceCmd){
      fParticleGun->SetMaterialSource(newValues);
    }
    else if (command == PositionSourceCmd){
      fParticleGun->SetSourcePosition(PositionSourceCmd->GetNew3VectorValue(newValues));
    }
    else if(command == ParticleCmd){
      if (newValues == "ion"){
        fShootIon = true;
      }
      else{
        fShootIon = false;
        G4ParticleDefinition* pd = particleTable->FindParticle(newValues);
        if (pd != NULL){
          fParticleGun->SetParticleDefinition(pd);
        }
      }
    }
    else if (command == MomentumCmd){
      fParticleGun->SetParticleMomentumDirection(MomentumCmd->GetNew3VectorValue(newValues));
    }
    else if (command == ChargeCmd){
      fParticleGun->SetParticleCharge(ChargeCmd->GetNewDoubleValue(newValues));
    }
    else if (command == EnergyCmd){
      fParticleGun->SetParticleEnergy(EnergyCmd->GetNewDoubleValue(newValues));
    }


}
