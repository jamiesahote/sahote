#ifndef SAHOTEAPP_H
#define SAHOTEAPP_H

#include "MooseApp.h"

class SahoteApp;

template<>
InputParameters validParams<SahoteApp>();

class SahoteApp : public MooseApp
{
public:
  SahoteApp(const std::string & name, InputParameters parameters);
  virtual ~SahoteApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* SAHOTEAPP_H */
