#BaseUnits
A compile-time unit checking and conversion library for c++.

#Description and Usage
##Overview
BaseUnits enables a c++ compiler to check for expressions that mix
quantities in different unit systems.  Numbers are associated with
compile-time tags that are unique to each base unit.  Quantities 
associated with units can be printed in their base units, added to
other quantities with the same base unit, and converted into basic
arithmetic types in a particular prefix.

Prefix system inspired by the design of the c++11 standard library's
std::chrono header.  I've probably be influenced by GenVector, Geant4
and CLHEP.

##Key Features
 - Compiler-checked units for expressions with no runtime performance
   penalty.

 - Header-only library.  Copy into your own project to avoid external
   dependencies.  CMake build system used only for tests.

 - Automatic conversions between prefixed units.

 - Easy to use with external libraries: just use `quantity<>::in<>()` for
   self-documenting unit conversions into ordinary arithmetic types.

 - Full support for derived units.  Derived unit tags automatically
   generated at compile-time.

 - Support for printing quantities with unit names in their base units.

 - Easy to use with `memcpy()`-style semantics for GPU programming and
   ROOT I/O.  All quantities with units are aligned as their underlying
   arithmetic types.

##Central Components
 - `quantity<>`: A number associated with a user-defined unit.  See quantity.h.
                 Units with a metric (or otherwise) prefix applied are related
                 by `std::ratio<>`.

 - `quantity<>::operator +()`: Basic arithmetic operations supported on
                               `quantity<>`s.  Multiplication and division
                               generate derived units.

 - `quantity<>::in<>()`: Unit system exit point for interface to external
                         libraries.

 - `productTag<>` and `ratioTag<>`: Represent derived units as arbitrary combinations
                                    of basic units.

 - `operator <<`: `quantity<>`s can be printed in their base units with unit names.

 - `DECLARE_UNIT()` and `DECLARE_RELATED_UNIT()`: User creation of a unit tag.  Also
                                                  generates literal conversion operators.

##Usage
1. `#include "units.h"`

2. Define a system of units: `DECLARE_UNIT(MeV)`

3. Create MeV objects where you would have used doubles with comments before.
   Use them as if they were still doubles.  You can create MeV literals like: `938.3_MeV`
 
4. When you need to pass a `quantity<>`'s value to another library that doesn't
   know about BaseUnits, convert back to double with `number.in<MeV>()`.

##Testing
After installation, make test.

**TODO**: Explain tests run

##Example
```c++
//Set up a system of units based on MeV.  GeV are related to MeV by a prefix.
DECLARE_UNIT(MeV)
DECLARE_RELATED_UNIT(GeV, MeV, 1000, 1)

//Set up another, unrelated, system of units.  cm can be added to mm, but not
//to MeV or GeV.
DECLARE_UNIT(cm)
DECLARE_RELATED_UNIT(mm, cm, 1, 10)

//You don't have to use doubles with units
DECLARE_UNIT_WITH_TYPE(events, int)

//Do math with MeV
const MeV protonMass = 938.3;
const auto protonEnergy = 1.034_GeV; //literal value based on the DECLARE_RELATED_UNIT() macro above

//MeV and GeV are compatible.  The compiler keeps track of the conversion. 
const auto ke = protonEnergy - protonMass;
  
//Of course, ROOT wouldn't like it very much if you gave it an MeV.
//So, do this:
yourHistogram.Fill(ke.in<MeV>());
  
//If you multiply or divide two quantity<>s, the compiler
//will generate a new name for the resulting derived units
//for you.
cm dx = 10.;
const auto dEdx = (protonEnergy - protonMass)/dx;
 
//quantity<>s get printed with their unit names.
std::cout << "protonMass is " << protonMass << "\n";
std::cout << "protonEnergy is " << protonEnergy << "\n";
std::cout << "ke is " << ke << "\n";
std::cout << "dEdx is " << dEdx << "\n";
std::cout << "ke + protonMass is " << ke + protonMass << "\n";

//You can request a quantity<> in specific units like the histogram example above.
//This usually does some multiplication and division while the program is running.
std::cout << "Proton energy, which is " << protonEnergy << ", is " << protonEnergy.in<MeV>() << " in MeV\n";

//See test_units.cpp for more examples.
```

#Installation
 - Copy the contents of the core directory to your project.  I like to put them in
   a directory called units.

  **OR** Build and find this package with CMake.  On a UNIX-based platform with CMake
         and git installed:
  1. `mkdir BaseUnits`
  2. `cd BaseUnits && mkdir src && cd src`
  3. `git clone TODO #clone from github`
  4. `cd .. && mkdir opt #Prepare for an out-of-source build`
  5. `cd opt`
  6. `cmake ../../src -DCMAKE\_INSTALL\_PREFIX=`pwd`/.. #Install to current directory instead of /usr on UNIX`
  7. `make install`
  8. `make test #Make sure everything works`

  **THEN**

 - Use CMake to find this package in your CMakeLists.txt: find\_package(BaseUnits).
   You might have to tell CMake where to look to:
   `cmake /path/to/your/project -DBaseUnits\_DIR=/another/path/to/BaseUnits/opt/lib`.

 - **OR** Tell g++ to include files from BaseUnits in something like a Makefile.  You need to
   include files from `/another/path/to/BaseUnits/opt/include`.
