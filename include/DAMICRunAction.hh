#ifndef DAMICRunAction_h
#define DAMICRunAction_h

#include "G4UserRunAction.hh"
#include "G4Parameter.hh"
#include "globals.hh"

class G4Run;


class DAMICRunAction : public G4UserRunAction
{
  public:
    DAMICRunAction();
    virtual ~DAMICRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep);

};

#endif
