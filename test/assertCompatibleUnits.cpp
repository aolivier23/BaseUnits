//File: assertCompatibleUnits.cpp
//Brief: An executable that should NOT compile if BaseUnits works
//       as intended.  Only used by built-in test system.
//Author: Andrew Olivier aolivier@ur.rochester.edu

#include "core/units.h"

DECLARE_UNIT(MeV)
DECLARE_RELATED_UNIT(GeV, MeV, 1000, 1)

DECLARE_UNIT(cm)
DECLARE_RELATED_UNIT(mm, cm, 1, 10)

DECLARE_UNIT_WITH_TYPE(events, int)

int main(const int /*argc*/, const char** /*argv*/)
{
  //Do math with MeV
  const MeV protonMass = 938.3;
  const auto protonEnergy = 1.034_GeV; //literal value example
  const auto ke = protonEnergy - protonMass;
  
  //Test derived units
  cm dx = 10.;
  const auto dEdx = (protonEnergy - protonMass)/dx;

  //These lines of code shoulnd't compile:
  const auto mixUnits = dx + ke;
  const auto mixDerived = ke - dEdx;
  dx.in<GeV>();

  return 0;
}
