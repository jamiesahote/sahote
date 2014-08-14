#include "SahoteApp.h"
#include "Moose.h"
#include "AppFactory.h"

// Include kernel header files
#include "RadiationHeatSource.h"
#include "MatPropDiffusion.h"
#include "Convection.h"

// Include auxkernel header files
#include "BeamHeating.h"
#include "MaterialHeatAux.h"
#include "VelocityAux.h"

// Next come the materials
#include "SahoteMaterial.h"

// Next come the boundary conditions
#include "CRUDCoolantNeumannBC.h"
#include "CoolantNeumannBC.h"

template<>
InputParameters validParams<SahoteApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

SahoteApp::SahoteApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  SahoteApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  SahoteApp::associateSyntax(_syntax, _action_factory);
}

SahoteApp::~SahoteApp()
{
}

void
SahoteApp::registerApps()
{
  registerApp(SahoteApp);
}

void
SahoteApp::registerObjects(Factory & factory)
{
  // Register kernels
  registerKernel(RadiationHeatSource);
  registerKernel(MatPropDiffusion);
  registerKernel(Convection);

  // Register auxkernels
  registerAux(BeamHeating);
  registerAux(MaterialHeatAux);
  registerAux(VelocityAux); 

  // Register materials classes
  registerMaterial(SahoteMaterial);

  // Register boundary conditions
  registerBoundaryCondition(CRUDCoolantNeumannBC);
  registerBoundaryCondition(CoolantNeumannBC);
}

void
SahoteApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
