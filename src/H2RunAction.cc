#include "H2RunAction.hh"

H2RunAction::H2RunAction()
{
	timer = new G4Timer;
}

H2RunAction::~H2RunAction()
{
	delete timer;
}

void H2RunAction::BeginOfRunAction(const G4Run* aRun)
{
	G4cout << "### Run " << aRun->GetRunID() << " start. " << G4endl;
	timer->Start();
}

void H2RunAction::EndOfRunAction(const G4Run *aRun)
{
	timer->Stop();
	G4cout << "Number of Events: " << aRun->GetNumberOfEvent()
		<< " took " << *timer << G4endl;
}
