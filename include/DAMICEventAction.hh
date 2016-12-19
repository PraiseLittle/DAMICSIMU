#ifndef DAMICEventAction_h
#define DAMICEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class DAMICRunAction;

class DAMICEventAction : public G4UserEventAction
{
  public:
    DAMICEventAction(DAMICRunAction* runAction);
    virtual ~DAMICEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

  private:
    DAMICRunAction* fRunAction;
};

#endif
