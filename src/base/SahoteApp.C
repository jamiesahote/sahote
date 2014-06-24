#include "SahoteApp.h"
#include "Moose.h"
#include "AppFactory.h"

// Include kernel header files
#include "RadiationHeatSource.h"
#include "MatPropDiffusion.h"

// Next come the materials
#include "RadiationMaterial.h"

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

  // Register materials classes
  registerMaterial(RadiationMaterial);
}

void
SahoteApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
