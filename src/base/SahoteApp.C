#include "SahoteApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

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
  ModulesApp::registerObjects(_factory);
  SahoteApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
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
}

void
SahoteApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
