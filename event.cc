#include "event.hh"
#include "G4Event.hh"
#include "G4RootAnalysisManager.hh"
extern double fedep;
extern int Nphoton1;

MyEventAction::MyEventAction(MyRunAction* runAction)
 : G4UserEventAction(),
 fRunAction(runAction)
{
	fedep=0.;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
	//Nphoton1=0;
	fedep=0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
	G4cout << "Energy deposition: " << fedep << G4endl;
	G4RootAnalysisManager *analysisManager = G4RootAnalysisManager::Instance();
	
	//G4cout << Nphoton1 << G4endl;
	
	if (fedep > 0){
	//analysisManager->FillNtupleIColumn(0, 0, Nphoton1);
	//analysisManager->FillH1(0, Nphoton1);
	
	analysisManager->FillNtupleDColumn(1, 0, (fedep));
	analysisManager->AddNtupleRow(1);
	
	analysisManager->AddNtupleRow(0);
	}
}
