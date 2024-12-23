#include "stepping.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RootAnalysisManager.hh"
#include "construction.hh"
#include "G4Step.hh"
#include <G4VProcess.hh>

#include "G4UserRunAction.hh"
#include "G4Run.hh"

int Nphoton1=0;
double fedep=0;

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
 : G4UserSteppingAction(),
  fEventAction(eventAction)
{
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
      G4Track *track = step->GetTrack();
      G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

      // collect energy deposited in this step
	  //if (track->GetDefinition()->GetParticleName() == "mu-")
    if (track->GetDefinition()->GetParticleName() == "e")
	{
	  // G4cout << "volume->GetName() " << volume->GetName() << G4endl;

       if (volume->GetName()=="logicGeDetector") 
	    {	  
              G4double edepStep = step->GetTotalEnergyDeposit();
              fedep = fedep + edepStep;
	    }
	}

}
