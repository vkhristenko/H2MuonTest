#ifndef CSTEPPINGACTION_H
#define CSTEPPINGACTION_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"

#include "H2Defs.hh"

class H2SteppingAction : public G4UserSteppingAction
{
  public:
    H2SteppingAction(RunParams);
    virtual ~H2SteppingAction();

    virtual void UserSteppingAction(const G4Step*);

	RunParams runParams;
};

#endif

