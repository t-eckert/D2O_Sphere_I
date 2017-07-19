
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4VProcess.hh"
#include "G4Track.hh"

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
    const DetectorConstruction* detectorConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();
  }

  // get volume of the current step
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  // Get the name of the process in the step
  //G4String process_name = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  //G4cout << process_name;
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
<<<<<<< HEAD

  // Collect Kinetic Energy of the particle
  G4Track* track = step->GetTrack();
  G4double kinetic_energy = track->GetKineticEnergy();
  G4cout << kinetic_energy;
=======
  G4Track* track = step->GetTrack();
  G4double kineticEnergy = track->GetKineticEnergy();
  G4cout << kineticEnergy;
>>>>>>> 23b47b6d774256241e10640d906cb81dcdc8dd54
  // G4ThreeVector hit_position = step->GetPosition();
  fEventAction->Collect(edepStep, kinetic_energy);
}
